#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

//直方图操作

int main(int argc, char** argv) {
	Mat equalSample = imread("D:/code_work/opencv/sources/samples/data/MyPhotos/EualizeHistSample.png",IMREAD_GRAYSCALE);
	imshow("equalSample", equalSample);

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