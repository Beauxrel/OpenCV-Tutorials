#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat imgGrey, imgGaussian, imgCanny, imgDilation;

void getContours(Mat, Mat);

int main() {

	string path = "Resources/shapes.jpg";
	Mat img = imread(path);

	//Pre-processing
		/*
		Use Canny Image
		greyscale --> gaussian blur --> Canny Edge Detector
		*/
	cvtColor(img, imgGrey, COLOR_BGR2GRAY);
	GaussianBlur(imgGrey, imgGaussian, Size(3, 3), 3, 0);
	Canny(imgGaussian, imgCanny, 25, 75);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDilation, kernel); //Dilates edges of shapes (Fills gaps)

	getContours(imgDilation, img);

	imshow("Original", img);
	//imshow("Grey", imgGrey);
	//imshow("Gaussian", imgGaussian);
	//imshow("Canny", imgCanny);
	//imshow("Dilated", imgDilation);
	waitKey(0);



	return 0;
}

void getContours(Mat imgDilation, Mat img) {

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	

	//Find contours of Dilated
	findContours(imgDilation, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//Draw on original image
		//drawContours(img, contours, -1, Scalar(255,0,255), 2 );

	vector<vector<Point>> conPoly(contours.size()); //cannot be larger than contours.size
	vector<Rect> boundRect(contours.size());
	string objType;

	//Seperation of Area
	for (int i = 0; i < contours.size(); i++) {
		int area = contourArea(contours[i]);
		cout << area << endl;



		if (area > 1000) {
			//finding bounding boxes
			float Perimeter = arcLength(contours[i], true);
			//count number of curves to idntify shape
			approxPolyDP(contours[i], conPoly[i], 0.02 * Perimeter, true); //conPoly is output
			
			

			//bounding rectangles
			boundRect[i] = boundingRect(conPoly[i]);
			


			int objCorner = (int)conPoly[i].size();

			if (objCorner == 3) { objType = "Triangle"; }
			if (objCorner == 4) { 
				float aspectRatio = (float)boundRect[i].width / (float)boundRect[i].height; //w / h = 0.9 to 1 makes a square
				cout << aspectRatio << endl;
				if (aspectRatio > 0.90 && aspectRatio < 2)
				{
					objType = "Square";
				}
				else
				objType = "Rectangle"; }
			if (objCorner > 4) { objType = "Circle"; }

			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
			cout << conPoly[i].size() << endl; //3 triangle 4 square +circle
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
			putText(img, objType, { boundRect[i].x,boundRect[i].y - 5 }, FONT_HERSHEY_PLAIN, 1.00, Scalar(0, 69, 255), 1);
		}
	}
}
