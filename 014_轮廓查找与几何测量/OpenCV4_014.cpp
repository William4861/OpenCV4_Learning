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

	//通过计算轮廓面积过滤噪点
	Mat res2 = lena.clone();
	for (auto& cnt : contours) {
		double area = contourArea(cnt);
		if (area < 100) continue;
		drawContours(res2, cnt, 0, Scalar(255, 0, 0), 2);
	}
	imshow("lena过滤噪点轮廓", res2);

	//获取并绘制轮廓的正外接矩形
	Mat res3 = lena.clone();
	for (auto& cot : contours) {
		double area = contourArea(cot);
		if (area < 100) continue;
		Rect r = boundingRect(cot);
		drawContours(res3, cot, 0, Scalar(0, 0, 255), 2);
		rectangle(res3, r, Scalar(0, 0, 0), 2);
	}
	imshow("lena过滤轮廓的正外接矩形", res3);

	//获取并绘制轮廓的外接矩形（带角度）
	Mat res4 = lena.clone();
	for (auto& cot : contours) {
		double area = contourArea(cot);
		if (area < 100) continue;
		RotatedRect rRect = minAreaRect(cot);
		Point2f ptrs[4];
		rRect.points(ptrs);
		drawContours(res4, cot, 0, Scalar(0, 255, 0), 2);
		for (int i = 0; i < 4; i++) {
			line(res4, ptrs[i], ptrs[(i + 1) % 4], Scalar(255, 0, 0), 2);
		}

	}
	imshow("lena过滤轮廓的外接矩形（带角度）", res4);

	//计算轮廓矩并画出轮廓中心
	Mat res5 = lena.clone();
	for (auto& cot : contours) {
		double area = contourArea(cot);
		if (area < 100) continue;
		//1.计算轮廓矩
		Moments m = moments(cot);
		//2.求重心
		int cx = m.m10 / m.m00;
		int cy = m.m01 / m.m00;
		//3.画中心点
		circle(res5, Point(cx, cy), 2, Scalar(255, 0, 0), 2);

		drawContours(res5, cot, 0, Scalar(0, 255, 0), 1);
	}
	imshow("lena过滤轮廓的中心", res5);

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
 * 4. contourArea() - 计算轮廓面积
 *    功能：计算单个轮廓的像素面积大小，常用于过滤小噪点轮廓
 *    原型：double contourArea(
 *        InputArray contour,
 *        bool oriented = false
 *    );
 *    参数：
 *      - contour: 单个轮廓（vector<Point>）
 *      - oriented: 方向相关，默认 false 即可
 *    返回值：
 *      - 轮廓包围的面积（double 类型）
 *    调整建议：
 *      - 噪点轮廓面积通常很小，设置最小面积阈值（如 100）即可过滤
 * 
 * 5. boundingRect() - 计算轮廓的正外接矩形（无角度、轴对齐）
 *    功能：输入一个轮廓，返回**不旋转、水平竖直对齐**的最小包围矩形
 *    原型：Rect boundingRect( InputArray points );
 *    参数：
 *      - points: 输入轮廓（单个 vector<Point>）
 *    返回值：
 *      - Rect 类型，包含 x, y, width, height
 *
 * 
 * 6. minAreaRect() - 寻找轮廓的最小外接矩形（带旋转角度）
 *    功能：根据输入轮廓，计算能包围该轮廓的**最小面积矩形**（带旋转角度）
 *    原型：RotatedRect minAreaRect(InputArray points);
 *    参数：
 *      - points: 输入轮廓（单个 vector<Point>）
 *    返回值：
 *      - RotatedRect 类型，包含：中心坐标 center、尺寸 size、旋转角度 angle
 *
 * 7. RotatedRect::points() - 获取最小外接矩形的四个顶点
 *    功能：从 RotatedRect 中取出矩形的 4 个角点坐标（Point2f 类型）
 *    用法：rRect.points(ptrs);
 *    参数：
 *      - ptrs: 用于接收 4 个顶点的数组（Point2f ptrs[4]）
 *
 * 8. moments() - 计算轮廓的图像矩
 *    功能：计算轮廓/区域的几何矩（零阶矩、一阶矩、二阶矩等），用于求重心、面积、方向等
 *    原型：Moments moments(InputArray array, bool binaryImage = false);
 *    参数：
 *      - array: 输入轮廓（单个 vector<Point>）
 *    返回值：
 *      - Moments 结构体，包含 m00、m10、m01 等矩信息
 *
 * 9. 轮廓重心计算公式
 *    功能：通过图像矩计算轮廓的中心坐标
 *    公式：
 *      cx = m10 / m00
 *      cy = m01 / m00
 *    说明：
 *      m00：零阶矩 = 轮廓面积
 *      m10：一阶矩（x 方向）
 *      m01：一阶矩（y 方向）
 *******************************************************************/