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

/************************* 新增OpenCV函数 & 类型详解 *************************
 * 1. Point类 - 二维坐标点类型
 *    功能：表示图像上的一个像素坐标点
 *    用法：Point(x, y)
 *    参数：x=横坐标（列数），y=纵坐标（行数）
 *    说明：OpenCV中坐标原点在图像左上角，x向右增加，y向下增加
 *
 * 2. Scalar类 - 颜色值类型
 *    功能：表示图像像素的颜色值
 *    用法：Scalar(B, G, R)（三通道BGR格式）；Scalar(gray)（单通道灰度）
 *    说明：OpenCV默认彩色图像为BGR顺序，不是RGB
 *
 * 3. line() - 绘制直线
 *    功能：在图像上绘制连接两个点的直线段
 *    用法：line(img, pt1, pt2, color, thickness=1, lineType=LINE_8, shift=0);
 *    参数：
 *      - img: 要绘制的目标图像
 *      - pt1: 直线起点坐标
 *      - pt2: 直线终点坐标
 *      - color: 线条颜色
 *      - thickness: 线条宽度（像素，默认1）
 *      - lineType: 线条类型
 *        * LINE_8: 8连通线（默认，速度快）
 *        * LINE_AA: 抗锯齿线（更平滑，适合文字和曲线）
 *      - shift: 坐标小数位数（默认0，整数坐标）
 *    调整建议：绘制细线条用LINE_8，粗线条或需要美观时用LINE_AA
 * 4. rectangle() - 绘制矩形
 *    功能：在图像上绘制矩形框
 *    原型：void rectangle(InputOutputArray img, Point pt1, Point pt2, const Scalar& color, int thickness=1)
 *    参数：
 *      - img: 要绘制的图像
 *      - pt1: 矩形左上角坐标
 *      - pt2: 矩形右下角坐标
 *      - color: 线条颜色（BGR格式，如Scalar(0,255,0)表示绿色）
 *      - thickness: 线条宽度（-1表示填充矩形）
 *
 * 5. circle() - 绘制圆形
 *    功能：在图像上绘制空心圆或实心圆
 *    用法：circle(img, center, radius, color, thickness=1, lineType=LINE_8, shift=0);
 *    参数：
 *      - img: 要绘制的目标图像
 *      - center: 圆心坐标
 *      - radius: 圆的半径（像素）
 *      - color: 圆的颜色
 *      - thickness: 线条宽度（像素，-1表示填充整个圆）
 *      - lineType: 线条类型（同line()）
 *      - shift: 坐标小数位数
 *    调整建议：thickness=-1可绘制实心圆；大半径圆建议用LINE_AA抗锯齿
 *
 * 6. putText() - 绘制文本
 *    功能：在图像上绘制指定字体的英文文本
 *    用法：putText(img, text, org, fontFace, fontScale, color, thickness=1, lineType=LINE_8);
 *    参数：
 *      - img: 要绘制的目标图像
 *      - text: 要绘制的文本（仅支持ASCII字符，不支持中文）
 *      - org: 文本左下角的坐标
 *      - fontFace: 字体类型
 *        * FONT_HERSHEY_SIMPLEX: 普通无衬线字体（最常用）
 *        * FONT_HERSHEY_COMPLEX: 复杂无衬线字体（代码中使用）
 *        * FONT_HERSHEY_SCRIPT_SIMPLEX: 手写体
 *      - fontScale: 字体缩放因子（1为标准大小，>1放大，<1缩小）
 *      - color: 文本颜色
 *      - thickness: 文本线条宽度（像素）
 *      - lineType: 线条类型（建议用LINE_AA抗锯齿）
 *    注意：OpenCV原生不支持中文，绘制中文需使用FreeType等扩展库
 *******************************************************************/