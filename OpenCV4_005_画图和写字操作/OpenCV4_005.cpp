#include<iostream>
#include<opencv2/opencv.hpp>

using namespace  std;
using namespace cv;

//画图和写字操作：绘制直线、方形、圆形、写字

int main(int argc, char** argv) 
{
	//绘制全黑图像
	Mat black = Mat::zeros(Size(512, 512), CV_8UC3); //1代表彩色图 0 代表灰度图 -1代表扩展通道

	//绘制直线
	line(black, Point(0, 0), Point(511, 511), Scalar(255, 0, 0), 5);//参数顺序：操作的图像对象、位置(起点和终点）、颜色、厚度
	//绘制方形
	rectangle(black, Point(200, 200), Point(400, 300), Scalar(0, 255, 0), 10);//参数顺序：操作的图像对象、位置(左上角和右下角）、颜色、厚度
	//绘制圆形
	circle(black, Point(200, 300), 150, Scalar(0, 0, 255), 20);//参数顺序：操作的图像对象、位置(圆心）、半径、颜色、厚度
	//写字
	putText(black, "Hello,OpenCV", Point(50, 400), FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255),3);//参数顺序：操作的图像对象、写入的内容、位置、字体、字体大小、颜色、厚度

	//显示图像
	imshow("black", black);

	//等待
	waitKey(0);//参数空为等待图像完成，参数0代表一直等待键盘输入

	//销毁所有窗口
	destroyAllWindows();

	return 0;
}