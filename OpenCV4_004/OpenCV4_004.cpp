#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//图像位操作

int main(int argc, char** argv) {
	Mat src = imread("D:/code_work/opencv/sources/samples/data/butterfly.jpg",IMREAD_UNCHANGED);
	if (src.empty()) {
		printf("could not find image file");
		return -1;
	}
	imshow("input", src);

	Mat dst;
	bitwise_not(src, dst);  //取反 图像反转
	imshow("dst", dst);

	Mat dst1;
	Mat mask = Mat::zeros(src.size(), CV_8UC1);
	for (int row = 100; row < 100 + (mask.rows) * 0.5; row++) {
		/*uchar* curren_row = mask.ptr<uchar>(row);*/
		for (int colum = 100; colum < 100 + (mask.cols) * 0.5; colum++) {
			
			/**curren_row++ = 255;*/
			mask.at<uchar>(row, colum) = 255;
		}
	}
	bitwise_and(src, src, dst1,mask); //与运算 mask是参考图
	imshow("mask", mask);
	imshow("dst1", dst1);

	Mat dst2;
	bitwise_or(src, src, dst2, mask); //或运算
	imshow("dst2", dst2);

	waitKey(0);
	destroyAllWindows();

	return 0;
}