#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

//图像平滑

int main(int argc, char** argv) {
	Mat dogSp = imread("D:/code_work/VisualStudio_Project/OpenCV_Learning/MyPhotos/SpicySaltSample.png");//图像路径必须全英文，否则会读取空图像，后续报错
	imshow("dogSp", dogSp);
	Mat dogGaus = imread("D:/code_work/VisualStudio_Project/OpenCV_Learning/MyPhotos/GaussianSample.png");//输入参数：输入图像、输出图像、核大小
	imshow("dogGaus", dogGaus);

	//均值滤波
	Mat dogSpRes;
	blur(dogSp, dogSpRes, Size(5, 5)); // 输入参数：输入图像、输出图像、核大小
	imshow("dogSpRes", dogSpRes);

	//高斯滤波
	Mat dogGausRes;
	GaussianBlur(dogGaus, dogGausRes, Size(5, 5), 1);//输入参数：输入图像、输出图像、核大小、Sigma大小
	imshow("dogGausRes", dogGausRes);

	//中值滤波：对椒盐噪声尤其有效
	Mat dogSpMedianRes;
	medianBlur(dogSp, dogSpMedianRes, 5);// 输入参数：输入图像、输出图像、核半径
	imshow("dogSpMedianRes", dogSpMedianRes);

	//双边滤波
	Mat dogBilRes;
	bilateralFilter(dogGaus, dogBilRes, 5, 50, 50);
	imshow("dogBilRes", dogBilRes);

	waitKey(0);
	destroyAllWindows();

	return 0;
}

/************************* 新增OpenCV函数详解 *************************
 * 1. blur() - 均值滤波（线性平滑）
 *    功能：用核覆盖区域内所有像素的平均值替换中心像素，实现图像模糊
 *    用法：blur(src, dst, ksize, anchor=Point(-1,-1), borderType=BORDER_DEFAULT);
 *    参数：
 *      - src: 输入图像
 *      - dst: 输出图像（与输入同大小同类型）
 *      - ksize: 滤波核尺寸（必须为正奇数，如Size(3,3)、Size(5,5)）
 *      - anchor: 核的锚点（默认(-1,-1)表示中心）
 *      - borderType: 边界像素处理方式
 *    特点：计算速度最快，但会严重模糊图像边缘
 *    调整建议：核越大，平滑效果越强，边缘丢失越严重
 *
 * 2. GaussianBlur() - 高斯滤波（线性平滑）
 *    功能：用高斯核进行加权平均，中心像素权重最高，边缘权重递减
 *    效果：比均值滤波更自然，能较好保留边缘细节，专门用于去除高斯噪声
 *    用法：GaussianBlur(src, dst, ksize, sigmaX, sigmaY=0, borderType=BORDER_DEFAULT);
 *    参数：
 *      - src: 输入图像
 *      - dst: 输出图像
 *      - ksize: 高斯核尺寸（必须为正奇数，如Size(3,3)、Size(5,5)）
 *      - sigmaX: X方向高斯标准差（值越大平滑效果越强）
 *      - sigmaY: Y方向高斯标准差（默认0表示与sigmaX相同）
 *    调整建议：sigmaX设为0时，OpenCV会根据核大小自动计算最优值
 *
 * 3. medianBlur() - 中值滤波（非线性平滑）
 *    功能：用核覆盖区域内所有像素的中值替换中心像素
 *    效果：对椒盐噪声（黑白点噪声）效果极佳，几乎不模糊图像边缘
 *    用法：medianBlur(src, dst, ksize);
 *    参数：
 *      - src: 输入图像
 *      - dst: 输出图像
 *      - ksize: 核边长（必须为大于1的正奇数，如3、5、7，注意这里是单个整数）
 *    特点：非线性滤波，边缘保留能力强，但计算速度比线性滤波慢
 *    调整建议：核越大，去噪能力越强，但会丢失更多图像细节
 * 
 * 4. bilateralFilter() - 双边滤波
 *    功能：**保边去噪**滤波，既能去除噪声，又能保留图像边缘（不会模糊边界）
 *    原型：void bilateralFilter(
 *        InputArray src,
 *        OutputArray dst,
 *        int d,
 *        double sigmaColor,
 *        double sigmaSpace,
 *        int borderType = BORDER_DEFAULT
 *    );
 *    参数：
 *      - src: 输入图像（彩色/灰度均可）
 *      - dst: 输出滤波后图像
 *      - d: 滤波核直径，推荐 5~9（太大速度变慢）
 *      - sigmaColor: 颜色相似度阈值，越大越会把更多颜色视为同类
 *      - sigmaSpace: 空间距离阈值，越大滤波范围越广
 *    调整建议：
 *      - 人像磨皮、保边去噪首选双边滤波
 *      - 常用参数：d=5，sigmaColor=50，sigmaSpace=50
 *      - sigma 值越大，模糊效果越强，但边缘依然保留
 *******************************************************************/