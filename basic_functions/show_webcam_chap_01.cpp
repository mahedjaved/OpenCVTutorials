#include <opencv2\opencv.hpp>

using namespace cv;

/*
This function is mainly used to show input from webcam
*/
int DisplayWebcam()
{
	// a video capture device
	VideoCapture cap(0);

	if (!cap.isOpened())
		return -1;

	// this sets an infinite loop
	for (;;)
	{
		Mat frame;
		cap >> frame;
		imshow("Webcam Frame", frame);

		// break out from infinite loop
		if (waitKey(30) >= 0)
			break;
	}
	return 0;
}