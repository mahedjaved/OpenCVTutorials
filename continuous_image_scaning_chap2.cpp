#include <iostream>
#include <opencv2/imgproc.hpp>				
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "HelperFunctions.h"
// ------------------------------------------------------------------------------- //

/**
* this tutorial mainly focuses on how to check if an image is padded or not the method "isContinuous()" allows us to measure if the image is padded or not this should return true if it is indeed padded
* another way to check if image is padded or not, is to inspect the "CONTINUITY" of the image
* this involves doing "image.step == image.cols * image.elemSize()"
 */

void colourReduceWContinCheck(cv::Mat &image, int div = 64)
{
	// setup rows and cols limits
	int nl = image.rows;
	int nc = image.cols * image.channels();

	// check if image is continuous
	if (image.isContinuous())
	{
		// when the image is unpadded, this one can also be seen as a long one dimensional array of "WxH" pixels
		nc = nc * nl;
		nl = 1;
	}
}

// ------------------------------------------------------------------------------- //

int main()
{

}