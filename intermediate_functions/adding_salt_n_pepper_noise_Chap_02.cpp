// ------------------------------------------------------------------------------- //
#include <iostream>
#include <opencv2/imgproc.hpp>				// this was imported to add circles BTW
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
// ------------------------------------------------------------------------------- //

// each element of the matrix --> shows a single PIXEL
// for greyscale images --> pixels are "unsigned 8-bit values" ranging from 0 (black) to 255 (white)
// a cv matrix element is made up of "triplet of 8-bit" values
// hence the channels are 8-bit, 16-bit channel size is used for medical images
// CV_32U / CV_32S can be useful for storing "intermediate values" in image processing tasks
// 

// --------------------------------------------------------------------------------------------------- //

void addSaltPepperNoise(cv::Mat image, int n)
{
	/**
	 * @desc : function receives an input image and a number and adds a salt and pepper noise to the image
	 */

	 // add two variables that is used to store random position of an image
	int loc_i, loc_j;

	// loop that iterates over 'n' number of times, and overwrite white values
	for (int k = 0; k < n; k++)
	{
		// randomly store pixels locations, i stores the x-value, j stores the y-value
		// modulo operator "%" allows us to return only the values in range cols and 
		loc_i = std::rand() % image.cols;
		loc_j = std::rand() % image.rows;

		// if the image is greyscale, then set the pixel value to 255 at the location i,j
		if (image.type() == CV_8UC1)
		{
			image.at<uchar>(loc_j, loc_i) = 255;
		}
		else if (image.type() == CV_8UC3)
		{
			// if the image is colour, set the pixel value at (j,i) for each of the three channels
			image.at<cv::Vec3b>(loc_j, loc_i)[0] = 255;
			image.at<cv::Vec3b>(loc_j, loc_i)[1] = 255;
			image.at<cv::Vec3b>(loc_j, loc_i)[2] = 255;
		}
	}
}

// --------------------------------------------------------------------------------------------------- //

int addSaltPepperNoiseExample()
{

	cv::Mat inputImage = cv::imread("../../../../ANGIE_PICS/teahub.io-4k-hd-wallpapers-76956.jpg");
	cv::resize(inputImage, inputImage, cv::Size(600, 300));
	addSaltPepperNoise(inputImage, 10000);

	// defining a ROI region
	//cv::Rect roi = cv::Rect(inputImage);

	// define a separate window optionally
	cv::namedWindow("Original Window");
	cv::imshow("Original Window", inputImage);
	cv::waitKey(0);

	// accessing elements by using CV_Mat Template, alternative to using <at> 
	cv::Mat_<uchar> image_2(inputImage);
	std::cout << "Pixel info at location" << "50,100" << "is:" << image_2(50, 100);

	return 0;
}



// ------------------------------------------------------------------------------------------------- //