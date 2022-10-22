// ------------------------------------------------------------------------------- //
#include <iostream>
#include <opencv2/imgproc.hpp>				// this was imported to add circles BTW
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
// ------------------------------------------------------------------------------- //


// --------------------------------------------------------------------------------------------------- //
// Example of a callback function --> this one returns the coordinates of the mouse click, as soon as the image appearing is clicked at some arb axis
void onMouse(int event, int x, int y, int flags, void* param)
{
	// a good source on discussion on reinterpret_cast Vs static cast --> https://stackoverflow.com/questions/573294/when-to-use-reinterpret-cast
	// it basically used to preserve memory address during conversion of pointers
	// here it stores the image matrix of type cv::Mat as a pointer "im" from the input "param", WHICH BTW IS NOT THE IMAGE IN MATRIX, IT IS THE MEMORY ADDRESS OF THE IMAGE
	// now this leaves the question, why use "reinterpret_cast" instead of a static cast ??
	cv::Mat *im = reinterpret_cast<cv::Mat*>(param);

	// setup a switch function for the event type, there can be different cases for this event for eg. detect mouse movement or check speed of movement, but for us it is just one event which check if it is pressed and if so get the co-ordinate of the press
	switch (event)
	{
		// for the case of the left button pressed down
	case cv::EVENT_LBUTTONDOWN:
		// display the pixel value at the x and yth value, why use a static_cast, because we cannot simply use the variable "im" which is a pointer to the type cv::Mat, we need to access the pointer using ->, then we want to obtain a character that stores the coordinates of mouse using "at<uchar>", this is a module for cv::Mat
		std::cout << "at (" << x << "," << y << ") value is : " << static_cast<int>(im->at<uchar>(cv::Point(x, y))) << std::endl;
		break;
	}
}
// --------------------------------------------------------------------------------------------------- //





// ------------------------------------------------------------------------------- //
void ShowPixelPosition()
{
	// now create an empty image
	cv::Mat image;		// create an empty image
	cv::Mat transHorImage;  // create a result image that is rotated horizontally

	// read an image file and allocate the memory
	image = cv::imread("../teahub.io-4k-hd-wallpapers-76956.jpg", cv::IMREAD_COLOR);

	// the image above made should be 0x0 sized, you can print out the size this way
	// use this template to output messages :: std::cout <<  << std::endl
	std::cout << "This image is " << image.rows << " x " << image.cols << std::endl;
	std::cout << "Channels of the image is " << image.channels() << std::endl;

	// check if the image does exist and just simply an empty output, the .empty returns true if the image is empty
	if (image.empty())
	{
		// error handling begins
		// no image has been created
		std::cout << "[Info] Error no image was made";
	}

	// define a separate window optionally
	cv::namedWindow("Original Window");
	// show the image
	cv::resize(image, image, cv::Size(600, 300));

	// use the set mouse callback function
	// why do we use &image, this is because we are using the void pointer to store the address of the input image
	cv::setMouseCallback("Original Window", onMouse, reinterpret_cast<void*>(&image));

	// draw a circle on the image, cv::Point is used to specify a pixel coordinate
	cv::circle(image, //
		cv::Point(115, 110),			// center of the circle
		65,								// the radius
		cv::Scalar(255, 255, 255),		// the color "white" chosen
		10);							// the thickness

	// next to draw a text
	cv::putText(image, //
		cv::String("This is my first imgproc in C++"),			// the text itself
		cv::Point(10, 20),										// where to place it
		cv::FONT_HERSHEY_PLAIN,									// what font to use
		2.0,													// scale of font :)
		cv::Scalar(255, 255, 255),								// which color
		2);														// how thick


// ------------------------------------------------------------------------------- //
	cv::imshow("Original Window", image);
	cv::waitKey(0);
	// ------------------------------------------------------------------------------- //
}