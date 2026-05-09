#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

//模板匹配和霍夫变换

int main(int argc, char** argv) {
	Mat wulin = imread("D:/code_work/opencv/sources/samples/data/MyPhotos/Wulin.png");
	Mat wulinTemplate = imread("D:/code_work/opencv/sources/samples/data/MyPhotos/WulinTemplate.png");
	imshow("wulin", wulin);
	imshow("wulinTemplate", wulinTemplate);

	//模板匹配
	Mat wulinMatchTemp;
	matchTemplate(wulin, wulinTemplate, wulinMatchTemp,TM_SQDIFF);
	double minval, maxval;
	Point minLoc, maxLoc;
	Mat wulinMatchTemp2;
	minMaxLoc(wulinMatchTemp, &minval, &maxval, &minLoc, &maxLoc);
	Point topLeft = minLoc;
	Point buttomRight = Point(topLeft.x + wulinTemplate.cols , topLeft.y + wulinTemplate.rows);
	rectangle(wulin, topLeft, buttomRight, Scalar(0, 255, 0));
	imshow("wulinMatchRes", wulin);

	waitKey(0);
	destroyAllWindows();

	return 0;
}