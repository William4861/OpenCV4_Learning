#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

//形态学操作

int main(int argc, char** argv) {
	Mat src = imread("D:/code_work/opencv/sources/samples/data/ellipses.jpg");
	imshow("src", src);

	//腐蚀操作
	Mat kernel = (Mat_<uchar>::ones(Size(3, 3)));//先创建核结构
	Mat eroRes;
	erode(src, eroRes, kernel);//进行腐蚀
	imshow("erodeResult", eroRes);

	//膨胀操作
	Mat dilateRes;
	dilate(src, dilateRes, kernel);
	imshow("dilateResult", dilateRes);



	waitKey(0);
	destroyAllWindows();
	return 0;
}