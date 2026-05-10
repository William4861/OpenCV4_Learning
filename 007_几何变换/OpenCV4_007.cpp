#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>

using namespace std;
using namespace cv;

//几何变换操作

int main(int argc, char** argv) {

	Mat src = imread("D:/code_work/opencv/sources/samples/data/lena.jpg");
	imshow("src", src);
	
	//放大图像
	Mat dst;
	resize(src, dst, Size(src.rows * 2, src.cols * 2));
	imshow("dst", dst);
	//缩小图像
	Mat dst1;
	resize(src, dst1, Size(), 0.5, 0.5);
	imshow("dst1", dst1);

	//利用"<<"重载运算符快速创建平移矩阵
	Mat m = (Mat_<float>(2, 3) <<
		1, 0, 100,
		0, 1, 50
		);
	cout << m << endl;
	//平移图像
	Mat dst2;
	warpAffine(src, dst2, m, Size(src.rows*1.5,src.cols*1.5));
	imshow("dst2", dst2);

	//获取旋转矩阵
	Mat rotation = getRotationMatrix2D(Point(1 / 2 * (src.rows), 1 / 2 * (src.cols)), 45, 0.5); //参数顺序：旋转中心位置、旋转角度、缩放比例
	//旋转图像
	Mat dst3;
	warpAffine(src, dst3, rotation, src.size());
	imshow("dst3",dst3);

	//先获取仿射变换前后对应的点数组，然后获取仿射变换矩阵
	vector<Point2f> pts1 = { {50,50},{200,50},{50,200}}; //"{x,y}"为C++默认初始化写法，Point2f类自带双参数构造函数，自动隐式转换成"Point2f(x,y)"
	vector<Point2f> pts2 = { {100,100},{200,50},{100,250}}; //"{x,y}"为C++默认初始化写法，Point2f类自带双参数构造函数，自动隐式转换成"Point2f(x,y)"
	Mat affinMatrix = getAffineTransform(pts1, pts2);
	//进行仿射变换
	Mat dst4;
	warpAffine(src, dst4, affinMatrix, src.size());
	imshow("dst4", dst4);

	//先获取透视（投射）变换前后对应的点数组，然后获取透视（投射）变换矩阵
	vector<Point2f> pts3 = { {12,15},{9,88},{99,17},{95,97} };
	vector<Point2f> pts4 = { {10,10},{10,100},{100,10},{100,100} };
	Mat perspectiveMatrix = getPerspectiveTransform(pts3, pts4);
	//进行投射变换
	Mat dst5;
	warpPerspective(src, dst5, perspectiveMatrix, src.size());
	imshow("dst5", dst5);

	//向上/向下采样操作
	Mat dst6,dst7;
	pyrUp(src, dst6);
	pyrDown(src, dst7);
	imshow("dst6", dst6);
	imshow("dst7", dst7);

	waitKey(0);
	destroyAllWindows();
	return 0;
}

/************************* 新增OpenCV函数 & 语法详解 *************************
 * 1. Mat_<T>::operator<< - 便捷创建小矩阵
 *    功能：快速初始化小尺寸数值矩阵（常用于变换矩阵）
 *    用法：Mat m = (Mat_<float>(rows, cols) << v1, v2, ..., vn);
 *    说明：按行优先顺序填充矩阵元素，适合创建2x3、3x3等小矩阵
 *
 * 2. resize() - 图像缩放
 *    功能：调整图像到指定尺寸或按比例缩放
 *    用法1：resize(src, dst, Size(dst_width, dst_height), interpolation=INTER_LINEAR);
 *    用法2：resize(src, dst, Size(), fx, fy, interpolation=INTER_LINEAR);
 *    参数：
 *      - src: 输入图像
 *      - dst: 输出图像
 *      - Size(dst_width, dst_height): 目标尺寸（注意：宽在前，高在后！）
 *      - fx: 水平方向缩放因子（0.5=缩小一半，2=放大一倍）
 *      - fy: 垂直方向缩放因子
 *      - interpolation: 插值方法
 *        * INTER_LINEAR: 双线性插值（默认，适合放大）
 *        * INTER_AREA: 区域插值（适合缩小，效果最好）
 *        * INTER_CUBIC: 双三次插值（放大效果好但速度慢）
 *    ⚠️ 常见错误：Size参数顺序是(宽,高)即(cols,rows)，不是(rows,cols)
 *
 * 3. warpAffine() - 仿射变换
 *    功能：对图像执行任意仿射变换（平移、旋转、缩放、剪切）
 *    用法：warpAffine(src, dst, M, dsize, flags=INTER_LINEAR, borderMode=BORDER_CONSTANT, borderValue=Scalar());
 *    参数：
 *      - src: 输入图像
 *      - dst: 输出图像
 *      - M: 2x3仿射变换矩阵（float类型）
 *      - dsize: 输出图像尺寸(宽,高)
 *      - flags: 插值方法（同resize）
 *      - borderMode: 边界填充模式
 *      - borderValue: 边界填充颜色（默认黑色）
 *    说明：所有仿射变换（平移、旋转、缩放）都通过此函数执行
 *
 * 4. getRotationMatrix2D() - 获取旋转缩放矩阵
 *    功能：生成绕指定点旋转并缩放的仿射变换矩阵
 *    用法：Mat M = getRotationMatrix2D(center, angle, scale);
 *    参数：
 *      - center: 旋转中心坐标(Point(x,y))，x=cols, y=rows
 *      - angle: 旋转角度（度，逆时针为正）
 *      - scale: 缩放比例（1.0=不变，0.5=缩小一半）
 *    返回值：2x3 float类型仿射变换矩阵
 *    ⚠️ 常见错误：旋转中心坐标是(x,y)即(cols,rows)，不是(rows,cols)
 *
 * 5. getAffineTransform() - 获取三点仿射变换矩阵
 *    功能：根据三对对应点计算仿射变换矩阵
 *    用法：Mat M = getAffineTransform(srcPoints, dstPoints);
 *    参数：
 *      - srcPoints: 源图像中3个不共线的点（vector<Point2f>）
 *      - dstPoints: 目标图像中对应的3个点
 *    返回值：2x3 float类型仿射变换矩阵
 *    说明：3个不共线的点唯一确定一个仿射变换
 *
 * 6. getPerspectiveTransform() - 获取四点透视变换矩阵
 *    功能：根据四对对应点计算透视变换矩阵
 *    用法：Mat M = getPerspectiveTransform(srcPoints, dstPoints);
 *    参数：
 *      - srcPoints: 源图像中4个不共线的点
 *      - dstPoints: 目标图像中对应的4个点
 *    返回值：3x3 float类型透视变换矩阵
 *    说明：4个不共线的点唯一确定一个透视变换
 *
 * 7. warpPerspective() - 透视变换
 *    功能：对图像执行透视变换（纠正倾斜、鸟瞰图生成）
 *    用法：warpPerspective(src, dst, M, dsize, flags=INTER_LINEAR, borderMode=BORDER_CONSTANT, borderValue=Scalar());
 *    参数：同warpAffine()，但M是3x3透视变换矩阵
 *
 * 8. pyrUp() - 图像上采样（放大）
 *    功能：先将图像放大2倍，再进行高斯模糊
 *    用法：pyrUp(src, dst, dstsize=Size(src.cols*2, src.rows*2));
 *    说明：构建高斯金字塔的向上采样操作
 *
 * 9. pyrDown() - 图像下采样（缩小）
 *    功能：先对图像进行高斯模糊，再丢弃偶数行和列（缩小2倍）
 *    用法：pyrDown(src, dst, dstsize=Size(src.cols/2, src.rows/2));
 *    说明：构建高斯金字塔的向下采样操作，比直接resize缩小效果更好
 *******************************************************************/