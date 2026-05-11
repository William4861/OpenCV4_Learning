#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>

using namespace std;
using namespace cv;

//图像特征提取与描述

int main(int argc, char** argv) {
	//Harris角点检测
	Mat checkBoard = imread("D:/code_work/VisualStudio_Project/OpenCV_Learning/MyPhotos/checkBoard.png");
	if (checkBoard.empty()) {
		cout << "图像读取错误" << endl;
		return -1;
	}
	imshow("checkBoard", checkBoard);

	Mat gray,dst;
	cvtColor(checkBoard, gray, COLOR_BGR2GRAY);
	cornerHarris(gray, dst, 3, 3, 0.04);
	for (int i = 0; i < dst.cols; i++) {
		double min, max;
		minMaxLoc(dst, &min, &max);
		for (int j = 0; j < dst.rows; j++)
		{
			
			if (dst.at<float>(i, j) > 0.01 * max ){
				circle(checkBoard,Point(i,j),1,Scalar(0,255,0),1);
			}
		}
	}
	imshow("checkBoardHarrisRes", checkBoard);

	//Shi-Tomasi角点检测
	Mat mansion = imread("D:/code_work/VisualStudio_Project/OpenCV_Learning/MyPhotos/mansion.png");
	imshow("mansion", mansion);
	cvtColor(mansion, gray, COLOR_BGR2GRAY);
	imshow("mansionGray", gray);

	vector<Point2f> corners;
	goodFeaturesToTrack(gray, corners, 1000, 0.01, 10);
	for (auto& c : corners) {
		circle(mansion, c, 1, Scalar(0, 255, 0), 1);
	}
	imshow("mansionShi-TomasiRes", mansion);

	//SIFT图像特征提取
	Ptr<SIFT> sift = SIFT::create(0,3,0.04,10,1.6);//与默认值一致，参数空着也一样
	vector<KeyPoint> kps;
	Mat descriptors;
	sift->detectAndCompute(gray, noArray(), kps, descriptors);
	drawKeypoints(mansion, kps, mansion, Scalar(255, 0, 0),DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	imshow("mansionSIFTRes", mansion);

	//FAST角点检测
	Mat mansion2 = imread("D:/code_work/VisualStudio_Project/OpenCV_Learning/MyPhotos/mansion.png");
	cvtColor(mansion2, gray, COLOR_BGR2GRAY);
	imshow("mansion2Gray", gray);

	Ptr<FastFeatureDetector> fast = FastFeatureDetector::create();
	fast->detect(gray, kps);
	drawKeypoints(mansion2, kps, mansion2, Scalar(0, 0, 255));
	imshow("mansion2FASTRes", mansion2);

	//ORB图像特征提取
	Mat mansion3 = imread("D:/code_work/VisualStudio_Project/OpenCV_Learning/MyPhotos/mansion.png");
	cvtColor(mansion3, gray, COLOR_BGR2GRAY);
	imshow("mansion3", mansion3);

	Ptr<ORB> orb = ORB::create();
	orb->detectAndCompute(gray, noArray(), kps, descriptors);
	drawKeypoints(mansion3, kps, mansion3, Scalar(120, 120, 0));
	imshow("mansion3ORBRes", mansion3);


	waitKey(0);
	destroyAllWindows();

	return 0;
}

/************************* OpenCV 新函数详解 *************************
 * 1. cornerHarris() - Harris 角点检测
 *    功能：在灰度图像中检测角点（交点、突出点），是经典的角点提取算法
 *    原型：void cornerHarris(
 *        InputArray src,
 *        OutputArray dst,
 *        int blockSize,
 *        int ksize,
 *        double k,
 *        int borderType = BORDER_DEFAULT
 *    );
 *    参数：
 *      - src: 输入图像，必须是 8位 或 32位 单通道灰度图
 *      - dst: 输出角点响应图（类型为 CV_32FC1，值越大表示越可能是角点）
 *      - blockSize: 邻域窗口大小（一般设 2、3、5，越大越稳定）
 *      - ksize: Sobel 导数核大小（必须是奇数，一般 3）
 *      - k: 自由参数，取值范围 0.04 ~ 0.06（固定 0.04 即可）
 *    调整建议：
 *      - blockSize 越大，检测越稳定，但角点定位精度下降
 *      - k 越小越敏感，一般固定 0.04
 *      - 输出 dst 需要通过阈值筛选才能得到最终角点
 *
 * 2. 关于 dst.at<float>(i,j)
 *    功能：访问 Harris 响应图矩阵的值
 *    说明：cornerHarris 输出是 CV_32F 浮点型图像，必须用 <float> 访问
 *
 * 3. goodFeaturesToTrack() - Shi-Tomasi 角点检测
 *    功能：基于 Harris 角点改进的角点检测算法，效果更稳定、角点分布更均匀
 *    原型：void goodFeaturesToTrack(
 *        InputArray image,
 *        OutputArray corners,
 *        int maxCorners,
 *        double qualityLevel,
 *        double minDistance,
 *        InputArray mask = noArray(),
 *        int blockSize = 3,
 *        bool useHarrisDetector = false,
 *        double k = 0.04
 *    );
 *    参数：
 *      - image: 输入图像，必须是 8位 或 32位 单通道灰度图
 *      - corners: 输出检测到的角点，类型为 vector<Point2f>
 *      - maxCorners: 最多检测多少个角点（限制数量，防止太多）
 *      - qualityLevel: 质量系数，一般 0.01~0.1，值越大筛选越严格，角点越少
 *      - minDistance: 两个角点之间的最小像素距离，防止角点扎堆
 *      - mask: 可选掩码，只在掩码非零区域检测角点
 *      - blockSize: 计算局部特征的窗口大小，默认 3
 *      - useHarrisDetector: 是否使用 Harris 算法，false 表示使用 Shi-Tomasi
 *      - k: Harris 算法的自由参数，默认 0.04
 *    调整建议：
 *      - maxCorners：根据需求设置，一般 100~2000
 *      - qualityLevel：0.01 是通用值，角点太少就调小，太多就调大
 *      - minDistance：越大角点越稀疏，越小越密集，一般 5~20
 *      - Shi-Tomasi 比 Harris 更稳定，优先使用
 *
 * 4. SIFT::create() - 创建 SIFT 特征检测器
 *    功能：创建 SIFT 尺度不变特征提取器，用于提取图像关键点与描述子
 *    原型：static Ptr<SIFT> create(
 *        int nfeatures = 0,
 *        int nOctaveLayers = 3,
 *        double contrastThreshold = 0.04,
 *        double edgeThreshold = 10,
 *        double sigma = 1.6
 *    );
 *    参数：
 *      - nfeatures: 保留的最佳特征点数量（0=不限制）
 *      - nOctaveLayers: 每个金字塔组的层数，默认 3
 *      - contrastThreshold: 对比度阈值，过滤弱特征点，越大过滤越多
 *      - edgeThreshold: 边缘阈值，过滤边缘点，越大保留越多边缘特征
 *      - sigma: 第一层高斯模糊的系数，默认 1.6
 *    调整建议：
 *      - 一般直接用默认参数即可：create(0,3,0.04,10,1.6)
 *      - 特征点太多：调大 contrastThreshold
 *      - 特征点太少：调小 contrastThreshold
 *
 * 5. sift->detectAndCompute() - 检测关键点 + 计算描述子
 *    功能：一步完成特征点检测和描述子计算
 *    参数：
 *      - image: 输入灰度图像
 *      - mask: 掩码（noArray() 表示全图）
 *      - kps: 输出关键点 vector<KeyPoint>
 *      - descriptors: 输出描述子矩阵（每行一个 128 维 SIFT 描述子）
 *
 * 6. drawKeypoints() - 绘制特征点
 *    功能：在图像上画出检测到的关键点
 *    参数：
 *      - image: 原始图像
 *      - keypoints: 关键点集合
 *      - outImage: 输出绘制后的图像
 *      - color: 绘制颜色
 *      - flags: 绘制风格
 *        * DRAW_RICH_KEYPOINTS：绘制带方向、带大小的圆形特征点（最常用）
 *
 * 7. FastFeatureDetector::create() - 创建FAST角点检测器
 *    功能：创建**超高速度**的角点检测器，适合实时视频、实时检测
 *    原型：static Ptr<FastFeatureDetector> create(
 *        int threshold = 10,
 *        bool nonmaxSuppression = true
 *    );
 *    参数：
 *      - threshold: 亮度差阈值（0~255）
 *        越大 → 角点越少
 *        越小 → 角点越多（容易误检）
 *        常用：10 ~ 20
 *      - nonmaxSuppression: 是否开启非极大值抑制
 *        true = 去重，角点更均匀（默认开启）
 *        false = 保留所有候选点，会扎堆
 *
 * 8. fast->detect() - 只检测关键点（不计算描述子）
 *    功能：只提取角点位置，速度极快
 *    参数：
 *      - image: 输入灰度图
 *      - keypoints: 输出角点 vector<KeyPoint>
 *
 * 9. ORB::create() - 创建 ORB 特征检测器
 *    功能：**实时、免费、工业级最常用**的图像特征提取算法
 *          结合 FAST 角点 + 二进制描述子，速度极快、效果好
 *    原型：static Ptr<ORB> create(
 *        int nfeatures = 500,
 *        float scaleFactor = 1.2f,
 *        int nlevels = 8,
 *        int edgeThreshold = 31,
 *        int firstLevel = 0,
 *        int WTA_K = 2,
 *        int scoreType = ORB::HARRIS_SCORE,
 *        int patchSize = 31,
 *        int fastThreshold = 20
 *    );
 *    参数（重点）：
 *      - nfeatures: 最多提取多少个特征点（默认 500）
 *      - scaleFactor: 金字塔缩放系数（默认 1.2）
 *      - nlevels: 金字塔层数（默认 8）
 *      - edgeThreshold: 边缘忽略阈值（默认 31）
 *      - fastThreshold: FAST 角点阈值
 *    调整建议：
 *      - 直接 ORB::create() 用默认参数就非常好用
 *      - 想提取更多特征：把 nfeatures 改大（如 1000, 2000）
 *      - 实时场景（视频/摄像头）：ORB 是首选
 *
 * 10. orb->detectAndCompute()
 *    功能：一步检测特征点 + 计算描述子（同 SIFT）
 *******************************************************************/