#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>

using namespace std;
using namespace cv;

//模板匹配和霍夫变换

int main(int argc, char** argv) {
	//模板匹配
	Mat wulin = imread("D:/code_work/VisualStudio_Project/OpenCV_Learning/MyPhotos/Wulin.png");
	Mat wulinTemplate = imread("D:/code_work/VisualStudio_Project/OpenCV_Learning/MyPhotos/WulinTemplate.png");
	imshow("wulin", wulin);
	imshow("wulinTemplate", wulinTemplate);

	Mat wulinMatchTemp;
	matchTemplate(wulin, wulinTemplate, wulinMatchTemp,TM_SQDIFF);
	double minval, maxval;
	Point minLoc, maxLoc;
	Mat wulinMatchTemp2;
	minMaxLoc(wulinMatchTemp, &minval, &maxval, &minLoc, &maxLoc);
	Point topLeft = minLoc;
	Point buttomRight = Point(topLeft.x + wulinTemplate.cols , topLeft.y + wulinTemplate.rows);
	rectangle(wulin, topLeft, buttomRight, Scalar(0, 255, 0));
	imshow("wulinMatchRes", wulin);

	//霍夫线检测
	Mat calendar = imread("D:/code_work/VisualStudio_Project/OpenCV_Learning/MyPhotos/Calendar.png");
	imshow("Calendar", calendar);
	Mat gray;
	cvtColor(calendar, gray, COLOR_BGR2GRAY);
	Mat edge;
	Canny(gray, edge, 50, 150);
	imshow("edge", edge);
	vector<Vec2f> lines;
	HoughLines(edge, lines, 0.8, CV_PI / 180, 150);
	for (auto& i : lines) {
		float rho = i[0];
		float theta = i[1];
		float a = cos(theta);
		float b = sin(theta);
		double x = rho * a;
		double y = rho * b;
		Point p1(cvRound(x + 1000 * (-b)), cvRound(y + 1000 * a));
		Point p2(cvRound(x - 1000 * (-b)), cvRound(y - 1000 * a));
		line(calendar, p1, p2, Scalar(0, 0, 255), 2);
	}
	imshow("calendarHoughRes", calendar);

	//霍夫圆检测
	Mat planets = imread("D:/code_work/VisualStudio_Project/OpenCV_Learning/MyPhotos/Planets.png");
	cvtColor(planets, gray, COLOR_BGR2GRAY);
	Mat temp;
	medianBlur(gray, temp, 3);
	imshow("planetsMedianBlur", temp);
	vector<Vec3f> circles;
	HoughCircles(temp, circles, HOUGH_GRADIENT, 1, 200, 100, 50, 0, 150);
	for (auto& i : circles) {
		circle(planets, Point(i[0], i[1]), i[2], Scalar(0, 255, 0), 2);
	}
	imshow("planetsHoughCircles", planets);

	waitKey(0);
	destroyAllWindows();

	return 0;
}

/************************* OpenCV函数详解 *************************
 * 1. matchTemplate() - 模板匹配
 *    功能：在输入图像中查找与模板最相似的区域
 *    原型：void matchTemplate(InputArray image, InputArray templ, OutputArray result, int method)
 *    参数：
 *      - image: 输入图像（待搜索图像）
 *      - templ: 模板图像（需小于输入图像）
 *      - result: 输出匹配结果矩阵（大小为image.cols-templ.cols+1 × image.rows-templ.rows+1）
 *      - method: 匹配方法
 *        * TM_SQDIFF: 平方差匹配（值越小匹配度越高）
 *        * TM_CCORR: 相关匹配（值越大匹配度越高）
 *        * TM_CCOEFF: 相关系数匹配（值越大匹配度越高）
 *    调整建议：TM_SQDIFF计算最快但对光照敏感；TM_CCOEFF效果最好但计算最慢
 *
 * 2. minMaxLoc() - 查找矩阵极值
 *    功能：在单通道矩阵中找到最小值、最大值及其对应的坐标
 *    原型：void minMaxLoc(InputArray src, double* minVal, double* maxVal=0, Point* minLoc=0, Point* maxLoc=0, InputArray mask=noArray())
 *    参数：
 *      - src: 输入单通道矩阵
 *      - minVal: 输出最小值（不需要传NULL）
 *      - maxVal: 输出最大值（不需要传NULL）
 *      - minLoc: 输出最小值坐标（不需要传NULL）
 *      - maxLoc: 输出最大值坐标（不需要传NULL）
 *      - mask: 可选掩码，指定要处理的区域
 *    注意：只能处理单通道矩阵；对于TM_SQDIFF方法取minLoc，其他方法取maxLoc
 *
 *
 * 3. HoughLines() - 标准霍夫线变换
 *    功能：在二值图像中检测直线
 *    原型：void HoughLines(InputArray image, OutputArray lines, double rho, double theta, int threshold)
 *    参数：
 *      - image: 输入二值边缘图像（通常是Canny输出）
 *      - lines: 输出直线参数（每个元素是Vec2f(rho, theta)）
 *      - rho: 距离分辨率（单位：像素，通常设为1）
 *      - theta: 角度分辨率（单位：弧度，通常设为CV_PI/180即1度）
 *      - threshold: 累加器阈值（只有投票数超过此值的直线才被检测到）
 *    调整建议：threshold是最关键参数，值越高检测到的直线越少但越准确
 *
 * 4. HoughCircles() - 霍夫圆检测
 *    功能：在灰度图像中检测圆形轮廓，自动找到图像中所有符合条件的圆
 *    原型：void HoughCircles(InputArray image, OutputArray circles, int method, double dp, double minDist, double param1, double param2, int minRadius=0, int maxRadius=0)
 *    参数：
 *      - image: 输入灰度图像（建议先做模糊去噪，否则噪声会导致大量误检测）
 *      - circles: 输出检测到的圆，每个元素是Vec3f(x, y, radius)，分别是圆心坐标和半径
 *      - method: 检测方法，目前仅支持 HOUGH_GRADIENT
 *      - dp: 累加器分辨率，1表示与原图同分辨率，2表示累加器是原图的1/2大小
 *      - minDist: 检测到的两个圆心之间的最小距离，小于这个值的两个圆会被合并
 *      - param1: Canny边缘检测的高阈值，低阈值自动设为它的一半
 *      - param2: 累加器阈值，值越小检测到的圆越多（包含假阳性），值越大检测越严格
 *      - minRadius: 检测圆的最小半径，小于这个值的圆会被忽略
 *      - maxRadius: 检测圆的最大半径，大于这个值的圆会被忽略
 *    调整建议：
 *      1. 输入前必须对图像做模糊去噪（比如代码里的medianBlur），否则噪声会产生大量误检
 *      2. minDist是关键参数，要根据你要检测的圆的实际间距来设置，太小会检测到重复的圆，太大会漏检
 *      3. param2控制检测严格度，先从大往小调，直到检测到所有目标圆
 *      4. 如果知道目标圆的半径范围，一定要设置minRadius和maxRadius，可以大幅减少误检
 *******************************************************************/