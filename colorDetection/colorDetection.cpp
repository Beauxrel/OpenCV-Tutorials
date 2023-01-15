#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>


using namespace std;
using namespace cv;


Mat imgHSV, mask;

// int hueMin = 0, saturationMin = 110, valueMin = 153;
// int hueMax = 19, saturationMax = 240, valueMax = 255;


// img, mask and hsv

// int main(){
// 	string path = "Resources/car.jpeg";
// 	Mat img = imread(path);
// 	cvtColor(img, imgHSV, COLOR_BGR2HSV);

// 	Scalar lower(hueMin, saturationMin, valueMin);
// 	Scalar upper(hueMax, saturationMax, valueMax);
// 	inRange(imgHSV,lower,upper,mask);
	
// 	imshow("Image", img);
// 	imshow("Image HSV", imgHSV);
// 	imshow("Image mask", mask);
// 	waitKey(0);
// return 0;
// //hsv space hue-saturation-value
// }

//trackbar
// max for hue is 180
// max value , saturation 255


int hueMin = 0, saturationMin = 50, valueMin = 182;
int hueMax = 50, saturationMax = 255, valueMax = 255;

int main(){
	string path = "Resources/car.jpeg";
	Mat img = imread(path);
	cvtColor(img, imgHSV, COLOR_BGR2HSV);

	namedWindow("trackbars",(640,200));

	createTrackbar("hue min","trackbars",&hueMin,179);
	createTrackbar("hue max","trackbars",&hueMax,179);
	createTrackbar("sat min","trackbars",&saturationMin,255);
	createTrackbar("sat max","trackbars",&saturationMax,255);
	createTrackbar("val min","trackbars",&valueMin,255);
	createTrackbar("val max","trackbars",&valueMax,255);

	while(true){
	Scalar lower(hueMin, saturationMin, valueMin);
	Scalar upper(hueMax, saturationMax, valueMax);
	inRange(imgHSV,lower,upper,mask);
	imshow("Image", img);
	imshow("Image HSV", imgHSV);
	imshow("Image mask", mask);
	waitKey(1);
	}
	return 0;
}

//hsv space hue-saturation-value
