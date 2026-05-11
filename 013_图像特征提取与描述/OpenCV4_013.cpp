#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

//图像特征提取与描述

int main(int argc, char** argv) {
	Mat checkBoard = imread("D:/code_work/VisualStudio_Project/OpenCV_Learning/MyPhotos/checkBoard.png");
	if (checkBoard.empty()) {
		return -1;
	}
	imshow("checkBoard", checkBoard);

	Mat gray,dst;
	cvtColor(checkBoard, gray, COLOR_BGR2GRAY);
	cornerHarris(gray, dst, 3, 3, 0.04);
	for (int i = 0; i < dst.cols; i++) {
		double min, max;
		minMaxLoc(dst, &min, &max);
		for (int j = 0; j < dst.rows; j++)
		{
			
			if (dst.at<float>(i, j) > 0.01 * max ){
				circle(checkBoard,Point(i,j),1,Scalar(0,255,0),1);
			}
		}
	}
	imshow("checkBoardHarrisRes", checkBoard);

	waitKey(0);
	destroyAllWindows();

	return 0;
}

/************************* OpenCV 新函数详解 *************************
 * 1. cornerHarris() - Harris 角点检测
 *    功能：在灰度图像中检测角点（交点、突出点），是经典的角点提取算法
 *    原型：void cornerHarris(
 *        InputArray src,
 *        OutputArray dst,
 *        int blockSize,
 *        int ksize,
 *        double k,
 *        int borderType = BORDER_DEFAULT
 *    );
 *    参数：
 *      - src: 输入图像，必须是 8位 或 32位 单通道灰度图
 *      - dst: 输出角点响应图（类型为 CV_32FC1，值越大表示越可能是角点）
 *      - blockSize: 邻域窗口大小（一般设 2、3、5，越大越稳定）
 *      - ksize: Sobel 导数核大小（必须是奇数，一般 3）
 *      - k: 自由参数，取值范围 0.04 ~ 0.06（固定 0.04 即可）
 *    调整建议：
 *      - blockSize 越大，检测越稳定，但角点定位精度下降
 *      - k 越小越敏感，一般固定 0.04
 *      - 输出 dst 需要通过阈值筛选才能得到最终角点
 *
 * 2. 关于 dst.at<float>(i,j)
 *    功能：访问 Harris 响应图矩阵的值
 *    说明：cornerHarris 输出是 CV_32F 浮点型图像，必须用 <float> 访问
 *
 *******************************************************************/