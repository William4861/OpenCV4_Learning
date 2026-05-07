#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

//图像平滑

int main(int argc, char** argv) {
	Mat dogSp = imread("D:/code_work/opencv/sources/samples/data/MyPhotos/SpicySaltSample.png");//图像路径必须全英文，否则会读取空图像，后续报错
	imshow("dogSp", dogSp);
	Mat dogGaus = imread("D:/code_work/opencv/sources/samples/data/MyPhotos/GaussianSample.png");//输入参数：输入图像、输出图像、核大小
	imshow("dogGaus", dogGaus);

	//均值滤波
	Mat dogSpRes;
	blur(dogSp, dogSpRes, Size(5, 5)); // 输入参数：输入图像、输出图像、核大小
	imshow("dogSpRes", dogSpRes);

	//高斯滤波
	Mat dogGausRes;
	GaussianBlur(dogGaus, dogGausRes, Size(5, 5), 1);//输入参数：输入图像、输出图像、核大小、Sigma大小
	imshow("dogGausRes", dogGausRes);

	//中值滤波：对椒盐噪声尤其有效
	Mat dogSpMedianRes;
	medianBlur(dogSp, dogSpMedianRes, 5);// 输入参数：输入图像、输出图像、核半径
	imshow("dogSpMedianRes", dogSpMedianRes);

	waitKey(0);
	destroyAllWindows();

	return 0;
}