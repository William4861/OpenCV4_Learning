#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//基本读写存操作

int main(int argc, char** argv) {
	Mat src = imread("D:/opencv-logo.png", -1);//加载图片
	if (src.empty()) {
		printf("could not find image file");
		return -1;
	}
	namedWindow("Demo_001", WINDOW_FREERATIO);
	imshow("Demo_001", src);//显示图片
	imwrite("D:/test.png", src);//保存图片
	waitKey(0);
	destroyAllWindows();

	return 0;
}