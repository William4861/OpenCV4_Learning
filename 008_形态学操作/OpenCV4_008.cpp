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
	dilate(src, dilateRes, kernel);//进行膨胀
	imshow("dilateResult", dilateRes);

	//开运算操作 效果：消除噪点
	Mat openSample = imread("D:/code_work/opencv/sources/samples/data/MyPhotos/OpenSample.png");
	Mat kernel1 = (Mat_<uchar>::ones(Size(20, 20)));//先创建20*20的核结构
	Mat openRes;
	morphologyEx(openSample, openRes, MORPH_OPEN ,kernel1);//进行开运算
	imshow("openSample", openSample);
	imshow("openResult", openRes);
	
	//闭运算 效果：填充孔洞
	Mat closeSample = imread("D:/code_work/opencv/sources/samples/data/MyPhotos/CloseSample.png");
	Mat closeRes;
	morphologyEx(closeSample, closeRes, MORPH_CLOSE, kernel1);//进行闭运算
	imshow("closeSample", closeSample);
	imshow("closeResult", closeRes);

	waitKey(0);
	destroyAllWindows();
	return 0;
}