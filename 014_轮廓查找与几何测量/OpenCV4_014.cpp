#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>
#include<Windows.h>

using namespace std;
using namespace cv;

//轮廓查找与几何测量

int main(int argc, char** argv) {
	SetConsoleOutputCP(936);//GBK

	Mat lena = imread("D:/code_work/VisualStudio_Project/OpenCV_Learning/MyPhotos/lena.jpg");
	imshow("lena", lena);
	Mat gray;
	cvtColor(lena, gray, COLOR_BGR2GRAY);
	imshow("lenaGray", gray);
	//1.二值化
	Mat bin;
	threshold(gray, bin, 0, 255, THRESH_OTSU);
	imshow("lenaBinary", bin);
	//2.定义轮廓容器
	vector<vector<Point>> contours;
	vector<Vec4i> heirachy;
	//3.查找轮廓（固定参数）
	findContours(bin, contours, heirachy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	//4.画轮廓
	Mat res = lena.clone();
	drawContours(res, contours, -1, Scalar(0, 255, 0), 2);//-1:画所有轮廓
	imshow("lena轮廓", res);


	waitKey(0);
	destroyAllWindows();

	return 0;
}

/************************* OpenCV 新函数详解 *************************
 * 1. threshold() - 图像二值化
 *    功能：将灰度图转为黑白二值图像，像素大于阈值为白色，否则为黑色
 *    原型：double threshold(
 *        InputArray src,
 *        OutputArray dst,
 *        double thresh,
 *        double maxval,
 *        int type
 *    );
 *    参数：
 *      - src: 输入灰度图像
 *      - dst: 输出二值图像
 *      - thresh: 手动设置的阈值（使用 OTSU 时填 0 即可，自动计算）
 *      - maxval: 最大值，一般填 255
 *      - type: 二值化方式
 *        THRESH_BINARY     : 大于阈值为 maxval，否则为 0
 *        THRESH_OTSU       : 自动计算最佳阈值（最常用）
 *    调整建议：
 *      找轮廓前必须二值化，OTSU 全自动最省心
 *
 * 2. findContours() - 查找图像轮廓
 *    功能：从二值图像中提取所有物体的轮廓
 *    原型：void findContours(
 *        InputArray image,
 *        OutputArray contours,
 *        OutputArray hierarchy,
 *        int mode,
 *        int method,
 *        Point offset = Point()
 *    );
 *    参数：
 *      - image: 输入二值图像（黑底白物体）
 *      - contours: 输出轮廓集合 vector<vector<Point>>
 *      - hierarchy: 输出轮廓层级信息 vector<Vec4i>
 *      - mode: 轮廓检索模式
 *        RETR_EXTERNAL : 只提取最外层轮廓（最常用）
 *        RETR_TREE     : 提取所有轮廓及层级
 *      - method: 轮廓逼近方法
 *        CHAIN_APPROX_SIMPLE : 压缩水平/垂直/斜线段，节省内存（推荐）
 *
 * 3. drawContours() - 绘制轮廓
 *    功能：在原图上画出检测到的轮廓
 *    原型：void drawContours(
 *        InputOutputArray image,
 *        InputArray contours,
 *        int contourIdx,
 *        const Scalar& color,
 *        int thickness = 1,
 *        int lineType = LINE_8
 *    );
 *    参数：
 *      - image: 要画轮廓的图像
 *      - contours: 轮廓集合
 *      - contourIdx: 要画第几个轮廓，-1 = 画全部
 *      - color: 轮廓颜色
 *      - thickness: 线条宽度
 *
 *******************************************************************/