#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

//边缘检测

int main(int argc, char** argv) {
	Mat horse = imread("D:/code_work/VisualStudio_Project/OpenCV_Learning/MyPhotos/Horse.png",0);
	imshow("horse", horse);

	//Sobel边缘检测
	Mat x,y;
	Sobel(horse, x, CV_16S, 1, 0);//水平方向计算
	Sobel(horse, y, CV_16S, 0, 1);//竖直方向计算
	Mat absX, absY;
	convertScaleAbs(x, absX);//数据转换
	convertScaleAbs(y, absY);
	Mat horseSobelRes;
	addWeighted(absX, 0.5, absY, 0.5, 0, horseSobelRes);//合并
	imshow("horseSobelRes", horseSobelRes);

	//Schar边缘检测
	Sobel(horse, x, CV_16S, 1, 0,-1);//水平方向计算
	Sobel(horse, y, CV_16S, 0, 1,-1);//竖直方向计算
	convertScaleAbs(x, absX);//数据转换
	convertScaleAbs(y, absY);
	Mat horseScharRes;
	addWeighted(absX, 0.5, absY, 0.5, 0, horseScharRes);//合并
	imshow("horseScharRes", horseScharRes);

	//Laplacian边缘检测
	Mat horseLaplacianRes;
	Laplacian(horse, horseLaplacianRes, CV_16S);
	convertScaleAbs(horseLaplacianRes, horseLaplacianRes);
	imshow("horseLaplacianRes",horseLaplacianRes);

	//Canny边缘检测：效果最好
	Mat horseCannyRes;
	Canny(horse, horseCannyRes, 0, 100);
	imshow("horseCannyRes", horseCannyRes);


	waitKey(0);
	destroyAllWindows();

	return 0;
}

/************************* 新增OpenCV函数详解 *************************
 * 1. Sobel() - Sobel一阶导数边缘检测
 *    功能：计算图像在水平/垂直方向的一阶梯度，检测对应方向的边缘
 *    用法：Sobel(src, dst, ddepth, dx, dy, ksize=3, scale=1, delta=0);
 *    参数：
 *      - src: 输入8位单通道灰度图像
 *      - dst: 输出梯度图像
 *      - ddepth: 输出图像深度（**必须用CV_16S**，因为梯度有正负，8位会截断负数）
 *      - dx: X方向导数阶数（1=计算水平梯度，检测垂直边缘）
 *      - dy: Y方向导数阶数（1=计算垂直梯度，检测水平边缘）
 *      - ksize: Sobel核大小（1,3,5,7；**-1表示使用Schar算子**，精度更高）
 *    特点：对噪声有一定抑制作用，计算速度快；需分别计算x和y方向后合并
 *    注意：不能直接用CV_8U深度，否则负梯度会被截断为0，丢失一半边缘
 *
 * 2. convertScaleAbs() - 梯度值转换为可显示图像
 *    功能：对图像元素取绝对值，再缩放转换为8位无符号图像
 *    用法：convertScaleAbs(src, dst, alpha=1, beta=0);
 *    参数：
 *      - src: 输入任意深度的图像（如CV_16S梯度图）
 *      - dst: 输出8位单通道图像
 *      - alpha: 缩放因子（默认1）
 *      - beta: 亮度偏移量（默认0）
 *    公式：dst(x,y) = saturate_cast<uchar>(|src(x,y)| * alpha + beta)
 *    作用：将Sobel/Laplacian输出的有符号梯度转换为可显示的灰度图
 *
 * 3. Laplacian() - Laplacian二阶导数边缘检测
 *    功能：计算图像的二阶导数，同时检测所有方向的边缘
 *    用法：Laplacian(src, dst, ddepth, ksize=1, scale=1, delta=0);
 *    参数：
 *      - src: 输入8位单通道灰度图像
 *      - dst: 输出拉普拉斯图像
 *      - ddepth: 输出图像深度（**必须用CV_16S**）
 *      - ksize: 核大小（1,3,5,7，默认1）
 *    特点：无需分方向计算，直接得到全方向边缘；但对噪声极其敏感
 *    建议：使用前先对图像进行高斯平滑，减少噪声影响
 * 4. Canny() - Canny边缘检测
 *    功能：检测图像中的边缘
 *    原型：void Canny(InputArray image, OutputArray edges, double threshold1, double threshold2, int apertureSize=3, bool L2gradient=false)
 *    参数：
 *      - image: 输入灰度图像
 *      - edges: 输出二值边缘图像
 *      - threshold1: 低阈值（低于此值的边缘被丢弃）
 *      - threshold2: 高阈值（高于此值的边缘被保留）
 *      - apertureSize: Sobel算子孔径大小（3,5,7）
 *      - L2gradient: 是否使用L2范数计算梯度（false用L1范数，更快）
 *    调整建议：高低阈值比例通常为1:2或1:3；阈值越高，检测到的边缘越少
 *
 * 补充：Schar算子说明
 *    Schar是3x3 Sobel的高精度改进版，通过Sobel(..., ksize=-1)调用
 *    比标准3x3 Sobel边缘定位更准确，计算速度相当，推荐优先使用
 *******************************************************************/