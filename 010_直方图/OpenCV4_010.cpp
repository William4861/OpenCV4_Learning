#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

//直方图操作

int main(int argc, char** argv) {
	Mat equalSample = imread("D:/code_work/opencv/sources/samples/data/MyPhotos/EualizeHistSample.png",IMREAD_GRAYSCALE);
	imshow("equalSample", equalSample);

	//绘制图像直方图
	Mat hist;
	int histSize = 256;
	float range[] = { 0,256 };
	const float* histRange = range;

	calcHist(&equalSample, 1, 0, Mat(), hist, 1, &histSize, &histRange);//输入参数：输入图像地址、输入图片数量、第几通道、掩膜、输出直方图、直方图维度、灰度级数量、灰度值范围

	for (int i = 0; i < 256; i++) {
		cout << "灰度" << i << "像素数：" << hist.at<float>(i) << endl;
	}



	//直方图均衡化：灰度图专用
	Mat equalRes;
	equalizeHist(equalSample, equalRes);
	imshow("equalRes", equalRes);

	//对比度受限的自适应直方图均衡化：灰度图专用
	Ptr<CLAHE> clahe = createCLAHE(2.0, Size(8, 8));
	Mat claheEqualRes;
	clahe->apply(equalSample, claheEqualRes);
	imshow("claheEqualRes",claheEqualRes);


	waitKey(0);
	destroyAllWindows();

	return 0;
}