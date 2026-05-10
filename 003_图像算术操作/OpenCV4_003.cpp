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

/************************* 新增OpenCV函数详解 *************************
 * 1. add() - 图像逐像素加法运算
 *    功能：对两个相同大小和类型的图像进行逐像素相加
 *    用法：add(src1, src2, dst);
 *    公式：dst(x,y) = saturate_cast<uchar>(src1(x,y) + src2(x,y))
 *    参数：
 *      - src1: 第一个输入图像
 *      - src2: 第二个输入图像（或Scalar常数）
 *      - dst: 输出图像（与输入同大小同类型）
 *    特点：自动截断超出0-255的像素值（不会溢出）
 *    调整建议：加正数提高亮度，加负数降低亮度
 *
 * 2. subtract() - 图像逐像素减法运算
 *    功能：对两个相同大小和类型的图像进行逐像素相减
 *    用法：subtract(src1, src2, dst);
 *    公式：dst(x,y) = saturate_cast<uchar>(src1(x,y) - src2(x,y))
 *    参数：同add()
 *    特点：自动截断小于0的像素值为0
 *    调整建议：减去常数降低亮度，减去背景图像可实现前景提取
 *
 * 3. addWeighted() - 图像加权加法（融合）
 *    功能：计算两个图像的加权和，实现图像融合或亮度对比度调整
 *    用法：addWeighted(src1, alpha, src2, beta, gamma, dst);
 *    公式：dst(x,y) = saturate_cast<uchar>(src1(x,y)*alpha + src2(x,y)*beta + gamma)
 *    参数：
 *      - src1: 第一个输入图像
 *      - alpha: src1的权重系数（0.0~1.0用于融合，>1用于提高对比度）
 *      - src2: 第二个输入图像
 *      - beta: src2的权重系数（通常alpha+beta=1用于融合）
 *      - gamma: 亮度偏移量（正数提亮，负数变暗）
 *      - dst: 输出图像
 *    调整建议：
 *      - 亮度调整：src2设为全黑，beta=0，gamma控制亮度
 *      - 对比度调整：src2设为全灰，beta=1-alpha，alpha>1提高对比度
 *      - 图像融合：alpha+beta=1，调整alpha控制两张图的透明度
 *******************************************************************/