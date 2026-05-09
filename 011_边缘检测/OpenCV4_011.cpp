#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

//边缘检测

int main(int argc, char** argv) {
	Mat horse = imread("D:/code_work/opencv/sources/samples/data/MyPhotos/Horse.png",0);
	imshow("horse", horse);

	//Sobel边缘检测
	Mat x,y;
	Sobel(horse, x, CV_16S, 1, 0);//水平方向计算
	Sobel(horse, y, CV_16S, 0, 1);//竖直方向计算
	Mat absX, absY;
	convertScaleAbs(x, absX);//数据转换
	convertScaleAbs(y, absY);
	Mat horseSobelRes;
	addWeighted(absX, 0.5, absY, 0.5, 0, horseSobelRes);//合并
	imshow("horseSobelRes", horseSobelRes);

	//Schar边缘检测
	Sobel(horse, x, CV_16S, 1, 0,-1);//水平方向计算
	Sobel(horse, y, CV_16S, 0, 1,-1);//竖直方向计算
	convertScaleAbs(x, absX);//数据转换
	convertScaleAbs(y, absY);
	Mat horseScharRes;
	addWeighted(absX, 0.5, absY, 0.5, 0, horseScharRes);//合并
	imshow("horseScharRes", horseScharRes);


	waitKey(0);
	destroyAllWindows();

	return 0;
}