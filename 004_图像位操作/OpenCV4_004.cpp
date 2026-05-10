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

/************************* 新增OpenCV函数详解 *************************
 * 1. bitwise_not() - 图像逐像素按位取反
 *    功能：对图像每个像素的二进制位进行取反操作
 *    用法：bitwise_not(src, dst, mask=noArray());
 *    公式：dst(x,y) = ~src(x,y)（仅在mask(x,y)≠0的位置执行）
 *    参数：
 *      - src: 输入图像（任意类型）
 *      - dst: 输出图像（与输入同大小同类型）
 *      - mask: 可选操作掩码（单通道8位，非零区域才执行操作）
 *    效果：8位图像中0→255，255→0，实现图像颜色反转
 *    应用：生成反色图像、反转掩码区域
 *
 * 2. bitwise_and() - 图像逐像素按位与运算
 *    功能：对两个图像对应像素的二进制位进行与操作
 *    用法：bitwise_and(src1, src2, dst, mask=noArray());
 *    公式：dst(x,y) = src1(x,y) & src2(x,y)（仅在mask(x,y)≠0的位置）
 *    参数：
 *      - src1: 第一个输入图像
 *      - src2: 第二个输入图像（与src1同大小同类型）
 *      - dst: 输出图像
 *      - mask: 操作掩码（非零区域执行运算，零区域输出0）
 *    核心应用：**掩码抠图/ROI提取**（src1=src2=原图时，仅保留mask为255的区域）
 *    特点：只有两个输入对应位都为1时，输出位才为1
 *
 * 3. bitwise_or() - 图像逐像素按位或运算
 *    功能：对两个图像对应像素的二进制位进行或操作
 *    用法：bitwise_or(src1, src2, dst, mask=noArray());
 *    公式：dst(x,y) = src1(x,y) | src2(x,y)（仅在mask(x,y)≠0的位置）
 *    参数：同bitwise_and()
 *    特点：只要有一个输入对应位为1，输出位就为1
 *    应用：合并两个图像的非零区域、添加水印、叠加图形
 *******************************************************************/
