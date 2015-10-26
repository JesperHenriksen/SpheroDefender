#include "Minimap.h"
#include "opencv2\opencv.hpp"
#include "CameraFeed.h"

using namespace std;
using namespace cv;

Minimap::Minimap()
{
}

Minimap::~Minimap()
{
}

Mat Minimap::segmentImage(CameraFeed camfeed){ 
	Mat inputArrow, outputArrow, imageThreshold;
	inputArrow = camfeed.getImageFromWebcam();
	outputArrow = camfeed.getImageFromWebcam();
	inputArrow = camfeed.convertRGBtoGS(inputArrow);
	outputArrow = camfeed.convertRGBtoGS(outputArrow);
	camfeed.thresholdImage(inputArrow, outputArrow, 60, 255, 0);
	camfeed.thresholdImage(outputArrow, outputArrow, 0, 60, 255);
	medianBlur(outputArrow, outputArrow, 5);
	imshow("MiniMap", outputArrow);
	return outputArrow;
}

void Minimap::placeSpell(Mat inputImage, int thresholdMin, int thresholdMax){
	double xCoord = 0, yCoord = 0;
	int collectiveX = 0, collectiveY = 0;
	int totalPixels = 0;
	for (int x = 0; x < inputImage.cols; x++) {
		for (int y = 0; y < inputImage.rows; y++) { //runs through the pixels
			if (inputImage.at<uchar>(y, x) > thresholdMin && inputImage.at<uchar>(y, x) < thresholdMax) { //if there is informations in the input pixel
				collectiveX += x;
				collectiveY += y;
				totalPixels++;
			}
		}
	}
	xCoord = collectiveX/totalPixels;
	yCoord = collectiveY/totalPixels;
	cout << xCoord << "," << yCoord << " ";
}

void Minimap::thresholdImageArrow(Mat inputImage, Mat outputImage, int minThresholdRed, int maxThresholdRed, int newValueRed,
	int minThresholdGreen, int maxThresholdGreen,
	int minThresholdBlue, int maxThresholdBlue){
	for (int r = 0; r < inputImage.rows; r++){
		for (int c = 0; c < inputImage.cols; c++){
			if (inputImage.at<Vec3b>(r, c)[0] > minThresholdBlue && inputImage.at<Vec3b>(r, c)[0] < maxThresholdBlue)
				if (inputImage.at<Vec3b>(r, c)[1] >minThresholdGreen && inputImage.at<Vec3b>(r, c)[1] < maxThresholdGreen)
					if (inputImage.at<Vec3b>(r, c)[2] > minThresholdRed && inputImage.at<Vec3b>(r, c)[2] < maxThresholdRed){
						outputImage.at<Vec3b>(r, c)[2] = newValueRed;
						outputImage.at<Vec3b>(r, c)[1] = newValueRed;
						outputImage.at<Vec3b>(r, c)[0] = newValueRed;
					}
					else
						outputImage.at<Vec3b>(r, c)[2] = inputImage.at<Vec3b>(r, c)[2];
		}
	}
}

int getDirection(Mat inputImage, CameraFeed camfeed){
	
	//camfeed.thresholdImage(inputImage, inputImage, 0, 60, 255);
	//camfeed.thresholdImage(inputImage, inputImage, 200, 255, 0);
	//camfeed.thresholdImage(inputImage, inputImage, 60, 200, 125);

	return 0;
}

