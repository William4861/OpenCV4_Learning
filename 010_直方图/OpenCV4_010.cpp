#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

//直方图操作

int main(int argc, char** argv) {
	Mat equalSample = imread("D:/code_work/opencv/sources/samples/data/MyPhotos/EualizeHistSample.png",IMREAD_GRAYSCALE);
	imshow("equalSample", equalSample);

	//绘制图像直方图
	Mat hist;
	int histSize = 256;
	float range[] = { 0,256 };
	const float* histRange = range;

	calcHist(&equalSample, 1, 0, Mat(), hist, 1, &histSize, &histRange);//输入参数：输入图像地址、输入图片数量、第几通道、掩膜、输出直方图、直方图维度、灰度级数量、灰度值范围

	for (int i = 0; i < 256; i++) {
		cout << "灰度" << i << "像素数：" << hist.at<float>(i) << endl;
	}



	//直方图均衡化：灰度图专用
	Mat equalRes;
	equalizeHist(equalSample, equalRes);
	imshow("equalRes", equalRes);

	//对比度受限的自适应直方图均衡化：灰度图专用
	Ptr<CLAHE> clahe = createCLAHE(2.0, Size(8, 8));
	Mat claheEqualRes;
	clahe->apply(equalSample, claheEqualRes);
	imshow("claheEqualRes",claheEqualRes);


	waitKey(0);
	destroyAllWindows();

	return 0;
}

/************************* 新增OpenCV函数 & 类详解 *************************
 * 1. calcHist() - 计算图像直方图
 *    功能：统计图像中每个灰度级的像素数量，生成直方图
 *    用法：calcHist(images, nimages, channels, mask, hist, dims, histSize, ranges, uniform=true, accumulate=false);
 *    参数：
 *      - images: 输入图像数组的首地址（&src）
 *      - nimages: 输入图像的数量（通常为1）
 *      - channels: 要统计的通道索引数组（灰度图用{0}）
 *      - mask: 可选掩码（空Mat表示统计整个图像）
 *      - hist: 输出直方图（单通道float类型Mat）
 *      - dims: 直方图维度（灰度图=1，彩色图=3）
 *      - histSize: 每个维度的灰度级数量（灰度图通常256）
 *      - ranges: 每个维度的灰度值范围（灰度图{0,256}，左闭右开）
 *    说明：输出直方图hist的每个元素hist.at<float>(i)表示灰度值i的像素总数
 *
 * 2. equalizeHist() - 全局直方图均衡化
 *    功能：通过拉伸灰度分布，增强图像全局对比度
 *    用法：equalizeHist(src, dst);
 *    参数：
 *      - src: 输入8位单通道灰度图像
 *      - dst: 输出均衡化后的图像
 *    特点：计算简单速度快，但会过度放大噪声，且对局部对比度改善有限
 *    限制：仅支持8位单通道灰度图像
 *
 * 3. createCLAHE() - 创建自适应直方图均衡化对象
 *    功能：创建对比度受限的自适应直方图均衡化(CLAHE)对象
 *    用法：Ptr<CLAHE> clahe = createCLAHE(clipLimit=40.0, tileGridSize=Size(8,8));
 *    参数：
 *      - clipLimit: 对比度限制阈值（默认40.0，通常设为2.0-4.0）
 *        值越大，对比度增强效果越强，但噪声也会被放大
 *      - tileGridSize: 图像分块大小（默认8x8，将图像分成多个小块分别均衡化）
 *    返回值：指向CLAHE对象的智能指针Ptr<CLAHE>
 *
 * 4. CLAHE::apply() - 执行自适应直方图均衡化
 *    功能：对输入图像应用CLAHE算法
 *    用法：clahe->apply(src, dst);
 *    参数：
 *      - src: 输入8位单通道灰度图像
 *      - dst: 输出均衡化后的图像
 *    优点：解决了全局均衡化过度放大噪声的问题，能更好保留图像局部细节
 *******************************************************************/