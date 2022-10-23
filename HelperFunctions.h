#pragma once
#include <iostream>
#include <opencv2/imgproc.hpp>				
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


cv::Mat loadExampleImage(std::string path = "../../../../ANGIE_PICS/teahub.io-4k-hd-wallpapers-76956.jpg", cv::Size resize = cv::Size(600, 300))
{
	// load image
	cv::Mat inputImage = cv::imread(path);
	cv::resize(inputImage, inputImage, resize);

	return inputImage;
}

void showImage(cv::Mat image, std::string name = "Original Window")
{
	cv::namedWindow(name);
	cv::imshow(name, image);
	cv::waitKey(0);
}
