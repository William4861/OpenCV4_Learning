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

/************************* 新增OpenCV函数 & 属性详解 *************************
* 1. Mat::cols
*    功能：获取图像的**宽度（列数）**
*    用法：int width = mat.cols;
*    说明：返回图像水平方向的像素数量，只读属性

* 2. Mat::rows
*    功能：获取图像的**高度（行数）**
*    用法：int height = mat.rows;
*    说明：返回图像垂直方向的像素数量，只读属性

* 3. Mat::channels()
*    功能：获取图像的**通道数**
*    用法：int ch = mat.channels();
*    说明：灰度图=1，彩色图=3，带透明通道=4

* 4. Mat::depth()
*    功能：获取图像**单个通道的像素数据类型深度**
*    用法：int d = mat.depth();
*    返回值对应：0=CV_8U(8位无符号)，1=CV_8S，2=CV_16U等
*    作用：判断像素存储位数，决定取值范围（如8位0-255）

* 5. Mat::type()
*    功能：获取图像**完整数据类型（深度+通道数）**
*    用法：int t = mat.type();
*    常用值：CV_8UC1(灰度图)、CV_8UC3(彩色图)
*    作用：判断图像格式，决定像素遍历方式

* 6. Mat::zeros()
*    功能：创建指定大小、全黑（值为0）的Mat图像
*    用法：Mat m = Mat::zeros(Size(w,h), type);
*    参数：Size尺寸，type图像类型
*    特点：自动初始化所有像素为0，适合创建黑色画布

* 7. Mat::clone()
*    功能：**深拷贝**图像，创建完全独立的新图像（修改互不影响）
*    用法：Mat m = src.clone();
*    特点：复制全部数据，新图像和原图无关联

* 8. Mat::copyTo()
*    功能：**深拷贝**图像到目标Mat，功能同clone()
*    用法：src.copyTo(dst);
*    特点：目标图像会自动分配内存，数据完全独立

* 9. Mat::at<T>()
*    功能：**数组方式访问/修改指定位置像素**
*    用法：mat.at<类型>(行,列)
*    类型：CV_8UC1用uchar，CV_8UC3用Vec3b
*    特点：语法直观，适合随机访问像素，效率略低

* 10. Mat::ptr<T>()
*    功能：**指针方式获取图像某一行的首地址**
*    用法：uchar* rowPtr = mat.ptr<uchar>(行);
*    特点：访问速度最快，适合批量遍历整行像素，性能最优

* 11. Vec3b
*    功能：OpenCV定义的**三通道像素类型**（8位无符号）
*    结构：[0]蓝、[1]绿、[2]红，对应BGR顺序
*    用法：Vec3b pix = mat.at<Vec3b>(row,col);

* 12. uchar
*    功能：OpenCV定义的**单通道像素类型**（8位无符号，0-255）
*    用法：uchar p = mat.at<uchar>(row,col);
*    说明：专门用于灰度图像素操作
*************************************************************************/