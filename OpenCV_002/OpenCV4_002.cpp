#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//Mat类型各项属性 && Mat类型构造方法 && 像素的遍历

int main(int argc, char** argv) {
	Mat src = imread("D:/apple.jpg",IMREAD_COLOR);
	if (src.empty()) {
		printf("could not find image file");
		return -1;
	}
	namedWindow("Apple", WINDOW_AUTOSIZE);
	imshow("Apple", src);
	int wid = src.cols;
	int high = src.rows;
	int channel = src.channels();
	int depth = src.depth();
	int t = src.type();
	if (t == CV_8UC3) {
		printf("width = %d, hige = %d, channel = %d, depth = %d, t = %d \n", wid, high, channel, depth, t);
	}

	//Create Method 1
	Mat t1 = Mat(256, 256, CV_8UC3);
	t1 = Scalar(0, 0, 0);
	imshow("t1",t1);

	//Create Method 2
	Mat t2 = Mat(Size(256, 256), CV_8UC3);
	t2 = Scalar(0, 255, 0);
	imshow("t2", t2);

	//Create Method 3
	Mat t3 = Mat::zeros(Size(256, 256), CV_8UC3);
	imshow("t3", t3);

	//Create Method 4 (From Source)
	Mat t4 = src;
	imshow("t4", t4);
	Mat t5;
	t5 = src.clone();
	imshow("t5", t5);
	Mat t6;
	src.copyTo(t6);
	imshow("t6", t6);
	Mat t7 = Mat(src.size(), src.type());
	imshow("t7", t7);

	//Visit Each Pixel in array
	for (int row = 0; row < high; row++) {
		for (int colum = 0; colum < wid; colum++) {
			if (src.type() == CV_8UC3) {
				Vec3b pixel = src.at<Vec3b>(row, colum); //三通道图片每个像素点的类型是 Vec3b
				int blue = pixel[0];
				int green = pixel[1];
				int red = pixel[2];
				src.at<Vec3b>(row,colum)[0] = 255 - blue;
				src.at<Vec3b>(row,colum)[1] = 255 - green;
				src.at<Vec3b>(row,colum)[2] = 255 - red;
			}
			if (src.type() == CV_8UC1) {
				uchar p = src.at<uchar>(row, colum); //单通道图片每个像素点的类型是 uchar
				src.at<uchar>(row, colum) = 255 - p;
			}
		}
	}
	imshow("VisitEachPixel_Sample_1", src);

	//Visit Each Pixel in pointer
	Mat result = Mat(src.size(), src.type());
	for (int row = 0; row < high; row++) {
		uchar* curren_row = src.ptr<uchar>(row);
		uchar* result_row = result.ptr<uchar>(row);
		for (int colum = 0; colum < wid; colum++) {
			if (src.type() == CV_8UC3) {
				int blue = *curren_row++;
				int green = *curren_row++;
				int red = *curren_row++;
				*result_row++ = blue;
				*result_row++ = green;
				*result_row++ = red;
			}
			if (src.type() == CV_8UC1) {
				uchar pv = *curren_row++;
				*result_row++ = pv;
			}
		}
	}
	imshow("VisitEachPixel_Sample_2", result);

	waitKey(0);
	destroyAllWindows();

	return 0;
}