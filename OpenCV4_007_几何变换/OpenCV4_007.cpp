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