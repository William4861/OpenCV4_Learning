#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

//形态学操作

int main(int argc, char** argv) {
	Mat src = imread("D:/code_work/opencv/sources/samples/data/ellipses.jpg");
	imshow("src", src);

	//腐蚀操作 
	Mat kernel = (Mat_<uchar>::ones(Size(3, 3)));//先创建核结构
	Mat eroRes;
	erode(src, eroRes, kernel);//进行腐蚀
	imshow("erodeResult", eroRes);

	//膨胀操作
	Mat dilateRes;
	dilate(src, dilateRes, kernel);//进行膨胀
	imshow("dilateResult", dilateRes);

	//开运算操作 效果：消除白噪点
	Mat openSample = imread("D:/code_work/VisualStudio_Project/OpenCV_Learning/MyPhotos/OpenSample.png");
	Mat kernel1 = (Mat_<uchar>::ones(Size(20, 20)));//先创建20*20的核结构
	Mat openRes;
	morphologyEx(openSample, openRes, MORPH_OPEN ,kernel1);//进行开运算
	imshow("openSample", openSample);
	imshow("openResult", openRes);
	
	//闭运算 效果：填充孔洞
	Mat closeSample = imread("D:/code_work/VisualStudio_Project/OpenCV_Learning/MyPhotos/CloseSample.png");
	Mat closeRes;
	morphologyEx(closeSample, closeRes, MORPH_CLOSE, kernel1);//进行闭运算
	imshow("closeSample", closeSample);
	imshow("closeResult", closeRes);

	//礼帽运算 效果：筛选白噪点
	Mat tophatRes;
	morphologyEx(openSample, tophatRes, MORPH_TOPHAT,kernel1);
	imshow("TophatResult", tophatRes);

	//黑帽运算 效果：筛选暗噪点
	Mat blackhatRes;
	morphologyEx(closeSample, blackhatRes, MORPH_BLACKHAT, kernel1);
	imshow("BlackhatResult", blackhatRes);

	waitKey(0);
	destroyAllWindows();
	return 0;
}

/************************* 新增OpenCV函数详解 *************************
 * 1. Mat_<T>::ones() - 创建全1矩阵（用于生成形态学核）
 *    功能：创建指定大小、所有元素值为1的矩阵
 *    用法：Mat kernel = Mat_<uchar>::ones(Size(width, height));
 *    参数：Size(width, height)为核的尺寸（宽×高）
 *    说明：形态学核越大，操作效果越明显；通常使用奇数尺寸(3×3,5×5)
 *    补充：推荐使用getStructuringElement()创建不同形状的核
 *
 * 2. erode() - 图像腐蚀操作
 *    功能：用核扫描图像，取核覆盖区域的最小值作为输出像素
 *    效果：缩小白色(亮)区域，扩大黑色(暗)区域；消除小的亮噪点，断开细连接
 *    用法：erode(src, dst, kernel, anchor=Point(-1,-1), iterations=1);
 *    参数：
 *      - src: 输入图像
 *      - dst: 输出图像
 *      - kernel: 形态学核
 *      - anchor: 核的锚点（默认(-1,-1)表示中心）
 *      - iterations: 腐蚀迭代次数（默认1，次数越多效果越强）
 *
 * 3. dilate() - 图像膨胀操作
 *    功能：用核扫描图像，取核覆盖区域的最大值作为输出像素
 *    效果：扩大白色(亮)区域，缩小黑色(暗)区域；填充小的暗孔洞，连接断裂区域
 *    用法：dilate(src, dst, kernel, anchor=Point(-1,-1), iterations=1);
 *    参数：同erode()
 *
 * 4. morphologyEx() - 通用形态学操作函数
 *    功能：执行各种高级形态学操作（开、闭、礼帽、黑帽等）
 *    用法：morphologyEx(src, dst, op, kernel, anchor=Point(-1,-1), iterations=1);
 *    参数：
 *      - src: 输入图像
 *      - dst: 输出图像
 *      - op: 形态学操作类型（核心参数）
 *        * MORPH_OPEN: 开运算（先腐蚀后膨胀）→ 消除小白噪点、分离粘连物体
 *        * MORPH_CLOSE: 闭运算（先膨胀后腐蚀）→ 填充小黑孔洞、连接断裂物体
 *        * MORPH_TOPHAT: 礼帽运算（原图-开运算）→ 提取比原图亮的小区域
 *        * MORPH_BLACKHAT: 黑帽运算（闭运算-原图）→ 提取比原图暗的小区域
 *      - kernel: 形态学核
 *      - iterations: 操作迭代次数
 *    调整建议：核的大小决定了能处理的噪点/孔洞的最大尺寸
 *******************************************************************/