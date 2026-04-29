#include <iostream>
#include<opencv2/opencv.hpp>
#include<vector>

using namespace std;
using namespace cv;

//颜色空间转换 & 获取图像总像素数量

int main(int argc, char** argv) {
	Mat img = imread("D:/code_work/opencv/sources/samples/data/lena.jpg", IMREAD_UNCHANGED);

	//获取图像总像素数量
	long t = img.total(); 
	cout << t << endl;

	//分割通道操作
	vector<Mat> dst;
	split(img, dst);
	imshow("dst[0]", dst[0]);
	imshow("dst[1]", dst[1]);
	imshow("dst[2]", dst[2]);

	//合并通道操作
	Mat dst1;
	merge(dst, dst1);
	imshow("dst1", dst1);

	//转换颜色模式操作
	Mat dstGrey, dstHSV;
	cvtColor(img, dstGrey, COLOR_BGR2GRAY);
	cvtColor(img, dstHSV, COLOR_BGR2HSV);
	imshow("dstGrey", dstGrey);
	imshow("dstHSV", dstHSV);


	waitKey(0);
	destroyAllWindows();

	return 0;
}