#include <iostream>
#include<opencv2/opencv.hpp>
#include<vector>

using namespace std;
using namespace cv;

//颜色空间转换 & 获取图像总像素数量

int main(int argc, char** argv) {
	Mat img = imread("D:/code_work/opencv/sources/samples/data/lena.jpg", IMREAD_UNCHANGED);

	//获取图像总像素数量
	long t = img.total(); 
	cout << t << endl;

	//分割通道操作
	vector<Mat> dst;
	split(img, dst);
	imshow("dst[0]", dst[0]);
	imshow("dst[1]", dst[1]);
	imshow("dst[2]", dst[2]);

	//合并通道操作
	Mat dst1;
	merge(dst, dst1);
	imshow("dst1", dst1);

	//转换颜色模式操作
	Mat dstGrey, dstHSV;
	cvtColor(img, dstGrey, COLOR_BGR2GRAY);
	cvtColor(img, dstHSV, COLOR_BGR2HSV);
	imshow("dstGrey", dstGrey);
	imshow("dstHSV", dstHSV);


	waitKey(0);
	destroyAllWindows();

	return 0;
}

/************************* 新增OpenCV函数 & 属性详解 *************************
 * 1. Mat::total()
 *    功能：获取图像的**总像素数量**（行数×列数）
 *    用法：long total_pixels = mat.total();
 *    说明：返回值与通道数无关，仅计算像素点的个数
 *    应用：计算图像内存占用、像素遍历的总循环次数
 *
 * 2. split() - 图像通道分割
 *    功能：将多通道图像按通道顺序分割为多个单通道图像
 *    用法：split(src, dst);
 *    参数：
 *      - src: 输入多通道图像（如CV_8UC3、CV_8UC4）
 *      - dst: 输出vector<Mat>容器，每个元素对应一个单通道图像
 *    说明：对于BGR彩色图像，dst[0]=蓝色通道，dst[1]=绿色通道，dst[2]=红色通道
 *    应用：单独处理某个颜色通道、基于通道的图像增强
 *
 * 3. cvtColor() - 颜色空间转换
 *    功能：将图像从一个颜色空间转换到另一个
 *    原型：void cvtColor(InputArray src, OutputArray dst, int code, int dstCn=0)
 *    参数：
 *      - src: 输入图像
 *      - dst: 输出图像
 *      - code: 转换代码
 *        * COLOR_BGR2GRAY: BGR彩色转灰度
 *        * COLOR_BGR2HSV: BGR转HSV
 *        * COLOR_GRAY2BGR: 灰度转BGR彩色
 *      - dstCn: 输出图像通道数（0表示自动）
 *    注意：OpenCV默认彩色图像是BGR格式，不是RGB
 * 4. merge() - 图像通道合并
 *    功能：将多个同大小同类型的单通道图像合并为一个多通道图像
 *    用法：merge(src, dst);
 *    参数：
 *      - src: 输入vector<Mat>容器，所有图像必须尺寸和类型一致
 *      - dst: 输出多通道图像，通道数等于输入vector的元素个数
 *    说明：合并顺序与vector中元素的顺序完全一致
 *    应用：通道合并、自定义多通道图像创建
 *
 * 补充：常用颜色空间转换代码（cvtColor函数参数）
 *    - COLOR_BGR2GRAY: BGR彩色转灰度（最常用）
 *    - COLOR_BGR2HSV: BGR转HSV（适合颜色识别，受光照影响小）
 *    - COLOR_BGR2RGB: BGR转RGB（用于与其他库/工具交互）
 *    - COLOR_GRAY2BGR: 灰度转BGR彩色
 *******************************************************************/