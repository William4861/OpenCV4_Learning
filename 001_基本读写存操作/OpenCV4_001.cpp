#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//基本读写存操作

int main(int argc, char** argv) {
	Mat src = imread("D:/opencv-logo.png", -1);//加载图片
	if (src.empty()) {
		printf("could not find image file");
		return -1;
	}
	namedWindow("Demo_001", WINDOW_FREERATIO);
	imshow("Demo_001", src);//显示图片
	imwrite("D:/test.png", src);//保存图片
	waitKey(0);
	destroyAllWindows();

	return 0;
}

/************************* OpenCV函数详解 *************************
 * 1. imread() - 读取图像文件
 *    功能：从指定路径加载图像到Mat对象中
 *    原型：Mat imread(const string& filename, int flags=IMREAD_COLOR)
 *    参数：
 *      - filename: 图像文件的完整路径（支持jpg、png、bmp等格式）
 *      - flags: 读取模式
 *        * IMREAD_COLOR(1): 以彩色模式读取（默认，忽略alpha通道）
 *        * IMREAD_GRAYSCALE(0): 以灰度模式读取
 *        * IMREAD_UNCHANGED(-1): 读取原始图像（包含alpha透明通道）
 *    调整建议：处理带透明效果的PNG必须用-1；灰度处理用0可节省内存
 *
 * 2. namedWindow() - 创建显示窗口
 *    功能：提前创建一个用于显示图像的窗口
 *    原型：void namedWindow(const string& winname, int flags=WINDOW_AUTOSIZE)
 *    参数：
 *      - winname: 窗口唯一名称（后续imshow需对应此名称）
 *      - flags: 窗口属性标志
 *        * WINDOW_AUTOSIZE: 窗口大小自动适应图像（默认，不可手动缩放）
 *        * WINDOW_FREERATIO: 窗口可自由缩放，图像比例随窗口变化
 *        * WINDOW_KEEPRATIO: 窗口可缩放，但保持图像原始比例
 *    注意：不调用此函数时，imshow会自动创建WINDOW_AUTOSIZE窗口
 *
 * 3. imshow() - 显示图像
 *    功能：在指定窗口中显示Mat图像
 *    原型：void imshow(const string& winname, InputArray mat)
 *    参数：
 *      - winname: 要显示的窗口名称（需与namedWindow一致）
 *      - mat: 要显示的Mat图像对象
 *    注意：必须配合waitKey()使用，否则窗口会一闪而过
 *
 * 4. imwrite() - 保存图像文件
 *    功能：将Mat图像保存到指定路径
 *    原型：bool imwrite(const string& filename, InputArray img, const vector<int>& params=vector<int>())
 *    参数：
 *      - filename: 保存文件的完整路径（后缀决定保存格式）
 *      - img: 要保存的Mat图像对象
 *      - params: 可选编码参数（格式为{参数ID, 值}）
 *        * JPEG: {IMWRITE_JPEG_QUALITY, 0-100}（默认95，值越大质量越高）
 *        * PNG: {IMWRITE_PNG_COMPRESSION, 0-9}（默认3，值越大压缩率越高）
 *    返回值：保存成功返回true，失败返回false
 *
 * 5. waitKey() - 等待按键输入
 *    功能：暂停程序执行，等待用户按键，并返回按键ASCII码
 *    原型：int waitKey(int delay=0)
 *    参数：
 *      - delay: 等待时间（毫秒）
 *        * 0: 无限等待直到用户按下任意键
 *        * >0: 等待指定毫秒数，超时自动返回-1
 *    注意：是OpenCV窗口系统的核心，必须调用才能正常显示和交互
 *
 * 6. destroyAllWindows() - 销毁所有窗口
 *    功能：关闭并释放所有由OpenCV创建的显示窗口
 *    原型：void destroyAllWindows()
 *    说明：程序结束时系统会自动释放，但显式调用是良好编程习惯
 *******************************************************************/