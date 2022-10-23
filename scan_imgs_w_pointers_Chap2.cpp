// ------------------------------------------------------------------------------- //
#include <iostream>
#include <opencv2/imgproc.hpp>				// this was imported to add circles BTW
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
// ------------------------------------------------------------------------------- //

/*
 some times scanning the entire image is necessary in some image processing tasks
 imp. you do this efficiently
 this recipe, instead of the simple for loop used in "manip_pixels.cpp",
 each of the pixel intensities take on values 1-255, which is "8-bit Unsigned Integer"
 storing alot of colour information in channels is expensive, instead what we do is drop down sizes
 this is the base colour reduction algorithm
 an image of width 'W' and height 'H' would require memory block of size "W x H x 3 uchars"
 sometimes images will be padded extra to increase row size for better computation since some chips for e.g. Intel MMX work best images of sizes 4x or 8x, just because of architecture reasons
 1) the "step" attribute of image gives the number of bytes in one row
 2) elemSize : size of a pixel element
 3) nchannels : how many channels in an image
 4) total : total number of pixels in the image (all the element entries in image matrix)
 */

 // ------------------------------------------------------------------------------- //
void colourReduce(cv::Mat image, int div = 64)
{
	// @desc: reduce the colour intensity of an image by reduction factor div
	std::cout << "Step for this rows : " << image.step << "\n compared with image.cols : " << image.cols << " and image.rows : " << image.rows;

	// loop through and scan the rows and store the pDointer of the row image data
	for (int j = 0; j < image.rows; j++)
	{
		// get the address of the row "j"
		uchar* data = image.ptr<uchar>(j);

		// the number of pixel values per row
		int nc = image.cols * image.channels();

		// second loop will go through each of the row pointer and apply the colour reduction formula
		for (int i = 0; i < nc; i++)
		{
			// process each pixel data
			data[i] = data[i] / div * div + div / 2;
		}
	}

}

// ------------------------------------------------------------------------------- //

void solvingWBitShift(cv::Mat image, int n, int div)
{
	// masking by limiting reduction factor "n" to power of 2, i.e. div=pow(2,n)
	// masking the first n bits allows us "lower multiple of div"
	uchar mask = 0xFF << n;

	// loop through and scan the rows and store the pDointer of the row image data
	for (int j = 0; j < image.rows; j++)
	{
		// get the address of the row "j"
		uchar* data = image.ptr<uchar>(j);

		// the number of pixel values per row
		int nc = image.cols * image.channels();

		// second loop will go through each of the row pointer and apply the colour reduction formula
		for (int i = 0; i < nc; i++)
		{
			// process each pixel data, 1) mask  2) add div/2
			*data &= mask;
			*data = *data + *data + div >> 1;
		}
	}

}

// ------------------------------------------------------------------------------- //

void preservingColourReduce(const cv::Mat &image, cv::Mat &result, int div = 64)
{
	/*
	@desc:: * doing colour reduce but preserving the original image with pointers and refs
	passing as reference allows the original image to be unchanged. Allows preservation and efficiency in image processing, I personally think it is because we added "const" but ah hell !

	* The output image is also sent as reference so that when func is evoked, you can see the output

	* In "in-place processing" ... the input is the same as output

	* If you re unsure whether you have allocated a separate data buffer for the image, you can use the "create()" function of cv::Mat to ensure a new image with new memory is ceated, **SEE BELOW**
	*/

	for (int j = 0; j < image.rows; j++)
	{
		// store the pointer address of the image at row 'j', we use const to make sure input is unchanged 
		const uchar* data_in = image.ptr<uchar>(j);
		uchar* data_out = result.ptr<uchar>(j);

		// the number of pixel values per row
		int nc = image.cols * image.channels();

		// loop through the columns for the jth row
		for (int i = 0; i < nc; i++)
		{
			data_out[i] = data_out[i] / div * div + div / 2;
		}


	}

}

// ------------------------------------------------------------------------------- //

int scanImages()
{
	// load image
	cv::Mat inputImage = cv::imread("../../../../ANGIE_PICS/teahub.io-4k-hd-wallpapers-76956.jpg");
	cv::resize(inputImage, inputImage, cv::Size(600, 300));

	// you can use the "clone()" method to save the original copy
	cv::Mat cloneImage = inputImage.clone();

	// or use "create()" to ensure a seperate copy has been confirmed with a seperate "data buffer allocation"
	cv::Mat result;
	result.create(inputImage.rows, inputImage.cols, inputImage.type());

	// check if size of this image equals step() * elementSize()
	std::cout << "The result size : " << result.size << " should equal total * elemSize : " << result.elemSize() * result.total() << "\n";

	// REDUCE # 1 == reduce the colour both standard way or preserving memory way
	colourReduce(inputImage, 25);
	cv::namedWindow("Original Window");
	cv::imshow("Original Window", inputImage);
	cv::waitKey(0);

	/*cv::namedWindow("Original Window");
	cv::imshow("Original Window", cloneImage);
	cv::waitKey(0);*/

	// REDUCE #2 == reduce with conservation of input
	preservingColourReduce(inputImage, result, 25);
	cv::namedWindow("Original Window");
	cv::imshow("Original Window", inputImage);
	cv::waitKey(0);

	return 0;
}