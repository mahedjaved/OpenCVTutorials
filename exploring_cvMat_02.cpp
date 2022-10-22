// ------------------------------------------------------------------------------- //
#include <iostream>
#include <opencv2/imgproc.hpp>				// this was imported to add circles BTW
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
// ------------------------------------------------------------------------------- //



// --------------------------------------------------------------------------------------------------- //

// **ADD ANY HELPER FUNCS HERE **
void EmptyGuy()
{
	// ...

}

// you can tell it is "cv::Mat" then "function name" because this function returns a cv::Mat data structure which is basically a grayscale image
cv::Mat function()
{
	cv::Mat ima(500, 500, CV_8U, 50);
	return ima;
}

// --------------------------------------------------------------------------------------------------- //

int Exercise_02()
{
	// making multiple windows
	cv::namedWindow("Image 1");
	cv::namedWindow("Image 2");
	cv::namedWindow("Image 3");
	cv::namedWindow("Image 4");
	cv::namedWindow("Image 5");
	cv::namedWindow("Image");

	// create a new image made of 240 rows and 320 columns and then show it, recall greyscale images are set as 8-bit unsigned integers with no channel information, not sure how different is this from "CV_8U_C1"
	cv::Mat image1(240, 300, CV_8U, 100);
	cv::imshow("Image", image1);
	cv::waitKey(0);

	// re-allocate a new image
	image1.create(200, 200, CV_8U);
	image1 = 200;					// sets the amount of grayness
	cv::imshow("Image", image1);
	cv::waitKey(0);

	// create a red-coloured image, recall it is BGR not RGB, OpenCV standards !
	cv::Mat image2(240, 320, CV_8UC3);
	image2 = cv::Scalar(0, 0, 255);
	cv::imshow("Image", image2);
	cv::waitKey(0);

	// now we read in an image from a set folder
	cv::Mat image3 = cv::imread("../teahub.io-4k-hd-wallpapers-76956.jpg");
	cv::resize(image3, image3, cv::Size(600, 300));

	// now we are making all these images points to the same block set as image4, which is image1 and image3, so in laymen term "image1=image3=image4"
	cv::Mat image4(image3);
	image1 = image3;

	// these image are new copies of the source image, basically image3 is now a new data block
	image3.copyTo(image2);

	// the last image is a copy of image3
	cv::Mat image5 = image3.clone();

	// flip the image3 horizontally 
	cv::flip(image3, image3, 1);

	// check which images have been affected by the processing
	cv::imshow("Image 3", image3);
	cv::imshow("Image 1", image1);
	cv::imshow("Image 2", image2);
	cv::imshow("Image 4", image4);
	cv::imshow("Image 5", image5);
	cv::waitKey(0); // wait for a key pressed

	// then now we generate a grayscale image
	cv::Mat gray = function();

	// show the output image
	cv::imshow("Image", gray);
	cv::waitKey(0);

	// now we practice by loading a colour image but using IMREAD_GRAYSCALE to convert it
	image1 = cv::imread("../teahub.io-4k-hd-wallpapers-76956.jpg", cv::IMREAD_GRAYSCALE);

	// you can also change the type of this image using, USEFUL when you want some computations done on the image to a precise value than rounded
	image1.convertTo(image1, CV_32F, 1 / 255.0, 0.0);
	cv::imshow("Image", image2);
	cv::waitKey(0);



	return 0;
}

// --------------------------------------------------------------------------------------------------- //