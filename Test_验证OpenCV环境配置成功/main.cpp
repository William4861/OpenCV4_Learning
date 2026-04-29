#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//验证OpenCV环境配置成功

int main(int argc, char** argv) {
	Mat src = imread("D:/logo.png");
	if (src.empty()) {
		printf("could not find image file");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);
	waitKey(0);
	destroyAllWindows();

	return 0;
}