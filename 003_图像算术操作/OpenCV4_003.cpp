#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//图像算术操作

int main(int argc, char** argv) {
	Mat src = imread("D:/code_work/opencv/sources/samples/data/butterfly.jpg");
	if (src.empty()) {
		printf("could not find image file");
		return -1;
	}
	imshow("input", src);

	Mat black = Mat::zeros(src.size(), src.type());
	black = Scalar(127, 127, 127);
	Mat dst;
	add(src, black, dst); //dst = src + black 提高亮度
	imshow("dst", dst);

	Mat dst1;
	subtract(src, black, dst1); //dst1 = src - black 降低亮度
	imshow("dst1", dst1);

	Mat dst2;
	addWeighted(src, 1.5, black, 0.2, 0.0, dst2); //dst2 = (src * 1.5 + black * 0.2) + 0.0 提高亮度和对比度
	imshow("dst2", dst2);

	waitKey(0);
	destroyAllWindows();

	return 0;
}