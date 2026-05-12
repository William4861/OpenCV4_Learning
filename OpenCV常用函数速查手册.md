# OpenCV常用函数速查手册

> 整合了 OpenCV 基础到进阶的常用函数详解，按功能分类整理，方便快速查阅
> 
> 适用于 C++ 版本 OpenCV，所有函数均附带参数说明与调优建议
> 
> 

---

## 目录

1. [基本图像操作](#1-基本图像操作)

2. [Mat 类型核心操作](#2-mat类型核心操作)

3. [图像算术与位操作](#3-图像算术与位操作)

4. [绘图与文字绘制](#4-绘图与文字绘制)

5. [颜色空间与通道操作](#5-颜色空间与通道操作)

6. [几何变换](#6-几何变换)

7. [形态学操作](#7-形态学操作)

8. [图像平滑滤波](#8-图像平滑滤波)

9. [直方图操作](#9-直方图操作)

10. [边缘检测](#10-边缘检测)

11. [模板匹配与霍夫变换](#11-模板匹配与霍夫变换)

12. [角点与特征检测](#12-角点与特征检测)

13. [重要注意事项](#重要注意事项汇总)

---

## 1. 基本图像操作

### 1.1 imread () - 读取图像

- **功能**：从文件加载图像到内存

- **用法**：`Mat img = imread("test.jpg", IMREAD_COLOR);`

- **参数**：

    - `filename`: 图像文件路径

    - `flags`: 读取模式

        - `IMREAD_COLOR`: 彩色图（忽略 Alpha 通道，默认）

        - `IMREAD_GRAYSCALE`: 灰度图

        - `IMREAD_UNCHANGED`: 包含 Alpha 通道的原图

- **注意**：OpenCV 默认读取彩色图为 BGR 顺序，不是 RGB！

### 1.2 namedWindow () - 创建窗口

- **功能**：创建一个可显示图像的窗口

- **用法**：`namedWindow("winname", WINDOW_NORMAL);`

- **参数**：

    - `winname`: 窗口标题

    - `flags`: 窗口模式

        - `WINDOW_AUTOSIZE`: 自动适应图像大小（默认）

        - `WINDOW_NORMAL`: 允许用户调整窗口大小

- **作用**：必须在 imshow 之前调用，否则会自动创建一个 AUTOSIZE 窗口

### 1.3 imshow () - 显示图像

- **功能**：在指定窗口中显示图像

- **用法**：`imshow("winname", img);`

- **注意**：显示后必须调用 waitKey () 才能让窗口刷新，否则会卡住

### 1.4 imwrite () - 保存图像

- **功能**：将 Mat 矩阵保存为图像文件

- **用法**：`imwrite("result.png", img);`

- **返回值**：成功返回 true，失败返回 false

- **注意**：

    - 支持的格式：jpg/png/bmp 等

    - 保存 png 时如果是 4 通道，会自动保存 Alpha 通道

### 1.5 waitKey () - 等待按键

- **功能**：等待用户按键，同时刷新窗口

- **用法**：`int key = waitKey(0);`

- **参数**：

    - `delay`: 等待毫秒数，0 表示无限等待

- **返回值**：按键的 ASCII 码，超时返回 -1

- **必须**：只要用了 imshow，就必须调用 waitKey，否则窗口不会刷新

### 1.6 destroyAllWindows () - 销毁窗口

- **功能**：关闭所有创建的窗口，释放资源

- **用法**：`destroyAllWindows();`

---

## 2. Mat 类型核心操作

### 2.1 基本属性

- `img.cols`: 图像宽度（列数）

- `img.rows`: 图像高度（行数）

- `img.channels()`: 通道数（3 = 彩色，1 = 灰度）

- `img.depth()`: 像素深度（0=CV_8U, 1=CV_8S, 2=CV_16U...）

- `img.type()`: 类型，例如 `CV_8UC3` 表示 8 位无符号 3 通道

- `img.total()`: 总像素数

### 2.2 Mat 构造

- `Mat(rows, cols, type)`: 创建指定大小的空矩阵

    - 例：`Mat img(480, 640, CV_8UC3);`

- `Mat::zeros(rows, cols, type)`: 创建全零矩阵

- `Mat::ones(rows, cols, type)`: 创建全一矩阵

### 2.3 像素遍历

- **指针法（最快）**：

    ```cpp
    
    for(int y=0; y<img.rows; y++){
        uchar* p = img.ptr<uchar>(y);
        for(int x=0; x<img.cols; x++){
            // p[x*3], p[x*3+1], p[x*3+2] 对应 BGR
        }
    }
    ```

- **at 方法（直观）**：

    ```cpp
    
    img.at<Vec3b>(y, x)[0] = 255; // B通道
    img.at<Vec3b>(y, x)[1] = 255; // G通道
    img.at<Vec3b>(y, x)[2] = 255; // R通道
    ```

### 2.4 像素类型

- `CV_8U`: 8 位无符号（0~255），最常用

- `CV_8S`: 8 位有符号

- `CV_16U`: 16 位无符号

- `CV_16S`: 16 位有符号（Sobel 常用）

- `CV_32F`: 32 位浮点

- `CV_64F`: 64 位浮点

---

## 3. 图像算术与位操作

### 3.1 add () - 图像相加

- **功能**：两个图像逐像素相加

- **用法**：`add(img1, img2, dst);`

- **特点**：饱和运算，超过 255 取 255

### 3.2 subtract () - 图像相减

- **功能**：两个图像逐像素相减

- **用法**：`subtract(img1, img2, dst);`

- **特点**：饱和运算，低于 0 取 0

### 3.3 addWeighted () - 加权相加

- **功能**：实现图像融合

- **公式**：`dst = alpha*img1 + beta*img2 + gamma`

- **用法**：`addWeighted(img1, 0.5, img2, 0.5, 0, dst);`

- **应用**：两张图半透明叠加

### 3.4 bitwise_not () - 按位取反

- **功能**：像素值按位取反（255 - x）

- **用法**：`bitwise_not(src, dst);`

### 3.5 bitwise_and () - 按位与

- **功能**：两个图像逐像素按位与

- **用法**：`bitwise_and(src1, src2, dst);`

- **应用**：掩码操作，提取 ROI

### 3.6 bitwise_or () - 按位或

- **功能**：两个图像逐像素按位或

- **用法**：`bitwise_or(src1, src2, dst);`

---

## 4. 绘图与文字绘制

### 4.1 Point - 点坐标

- **功能**：表示二维点

- **用法**：`Point p(100, 200);` // x, y

### 4.2 Scalar - 颜色值

- **功能**：表示 BGR 颜色

- **用法**：`Scalar(255, 0, 0)` 表示蓝色

- **注意**：顺序是 B, G, R

### 4.3 line () - 画线

- **功能**：在图像上画直线

- **用法**：`line(img, p1, p2, color, thickness=1);`

- **参数**：

    - `thickness`: 线宽，-1 表示填充

### 4.4 rectangle () - 画矩形

- **功能**：画矩形框

- **用法**：`rectangle(img, p1, p2, color, thickness=1);`

- **参数**：p1 左上角，p2 右下角

### 4.5 circle () - 画圆

- **功能**：画圆

- **用法**：`circle(img, center, radius, color, thickness=1);`

### 4.6 putText () - 绘制文字

- **功能**：在图像上绘制文字

- **用法**：`putText(img, "Hello", Point(50,50), FONT_HERSHEY_SIMPLEX, 1, color, 2);`

- **参数**：

    - `fontFace`: 字体，常用 `FONT_HERSHEY_SIMPLEX`

    - `fontScale`: 字体缩放因子

- **注意**：只支持英文，不支持中文

---

## 5. 颜色空间与通道操作

### 5.1 split () - 通道分离

- **功能**：将多通道图像分离为单通道

- **用法**：`vector<Mat> channels; split(img, channels);`

- **结果**：channels[0]=B, channels[1]=G, channels[2]=R

### 5.2 merge () - 通道合并

- **功能**：将多个单通道合并为多通道

- **用法**：`merge(channels, dst);`

### 5.3 cvtColor () - 颜色空间转换

- **功能**：转换图像的颜色空间

- **用法**：`cvtColor(src, dst, COLOR_BGR2GRAY);`

- **常用 code**：

    - `COLOR_BGR2GRAY`: 彩色转灰度

    - `COLOR_BGR2HSV`: 转 HSV 空间（用于颜色分割）

    - `COLOR_BGR2YCrCb`: 转 YCrCb 空间

    - `COLOR_GRAY2BGR`: 灰度转彩色

---

## 6. 几何变换

### 6.1 resize () - 图像缩放

- **功能**：改变图像大小

- **用法**：`resize(src, dst, Size(new_w, new_h), 0, 0, interpolation);`

- **插值方法**：

    - `INTER_LINEAR`: 双线性插值（默认，放大推荐）

    - `INTER_NEAREST`: 最近邻（最快，低质量）

    - `INTER_CUBIC`: 双三次插值（放大效果最好，慢）

    - `INTER_AREA`: 区域插值（缩小推荐，避免混叠）

### 6.2 warpAffine () - 仿射变换

- **功能**：执行 2x3 变换矩阵的仿射变换

- **用法**：`warpAffine(src, dst, M, dsize);`

- **应用**：平移、旋转、缩放、剪切

### 6.3 getRotationMatrix2D () - 旋转矩阵

- **功能**：计算旋转的仿射变换矩阵

- **用法**：`Mat M = getRotationMatrix2D(center, angle, scale);`

- **参数**：

    - `center`: 旋转中心

    - `angle`: 旋转角度（度），正数表示逆时针

    - `scale`: 缩放因子

### 6.4 getAffineTransform () - 三点求变换

- **功能**：通过 3 对对应点计算仿射变换矩阵

- **用法**：`Mat M = getAffineTransform(srcPoints, dstPoints);`

### 6.5 getPerspectiveTransform () - 透视变换

- **功能**：通过 4 对对应点计算透视变换矩阵

- **用法**：`Mat M = getPerspectiveTransform(srcPoints, dstPoints);`

- **应用**：矫正倾斜的文档，鸟瞰图

### 6.6 warpPerspective () - 透视变换

- **功能**：执行 3x3 变换矩阵的透视变换

- **用法**：`warpPerspective(src, dst, M, dsize);`

### 6.7 pyrUp () - 上采样

- **功能**：图像放大 2 倍

- **用法**：`pyrUp(src, dst);`

### 6.8 pyrDown () - 下采样

- **功能**：图像缩小 2 倍

- **用法**：`pyrDown(src, dst);`

---

## 7. 形态学操作

### 7.1 getStructuringElement () - 创建形态学核

- **功能**：创建形态学操作的结构元素

- **用法**：`Mat kernel = getStructuringElement(MORPH_RECT, Size(3,3));`

- **形状**：

    - `MORPH_RECT`: 矩形核

    - `MORPH_ELLIPSE`: 椭圆核

    - `MORPH_CROSS`: 十字核

### 7.2 erode () - 腐蚀

- **功能**：消除小亮点，收缩图像

- **用法**：`erode(src, dst, kernel);`

### 7.3 dilate () - 膨胀

- **功能**：消除小黑点，扩张图像

- **用法**：`dilate(src, dst, kernel);`

### 7.4 morphologyEx () - 高级形态学

- **功能**：执行各种形态学操作

- **用法**：`morphologyEx(src, dst, op, kernel);`

- **操作类型**：

    - `MORPH_OPEN`: 开运算（腐蚀 -> 膨胀），去除小亮点

    - `MORPH_CLOSE`: 闭运算（膨胀 -> 腐蚀），去除小黑点

    - `MORPH_GRADIENT`: 形态学梯度，提取轮廓

    - `MORPH_TOPHAT`: 顶帽，提取亮细节

    - `MORPH_BLACKHAT`: 黑帽，提取暗细节

---

## 8. 图像平滑滤波

### 8.1 blur () - 均值滤波

- **功能**：邻域平均，简单模糊

- **用法**：`blur(src, dst, Size(3,3));`

- **特点**：速度快，会模糊边缘

### 8.2 GaussianBlur () - 高斯滤波

- **功能**：高斯加权模糊，效果最自然

- **用法**：`GaussianBlur(src, dst, Size(5,5), sigmaX);`

- **参数**：

    - `sigmaX`: X 方向标准差，0 表示自动计算

- **应用**：最常用的去噪方法

### 8.3 medianBlur () - 中值滤波

- **功能**：取邻域中值，去除椒盐噪声

- **用法**：`medianBlur(src, dst, ksize);`

- **特点**：对椒盐噪声效果最好，能保留边缘

---

## 9. 直方图操作

### 9.1 calcHist () - 计算直方图

- **功能**：计算图像的直方图

- **用法**：`calcHist(&src, 1, channels, mask, hist, dims, histSize, ranges);`

- **应用**：统计像素分布

### 9.2 equalizeHist () - 直方图均衡化

- **功能**：自动增强对比度

- **用法**：`equalizeHist(src, dst);`

- **特点**：全局均衡，可能会放大噪声

### 9.3 createCLAHE () - 自适应均衡化

- **功能**：创建 CLAHE 均衡化对象

- **用法**：`Ptr<CLAHE> clahe = createCLAHE(clipLimit, tileGridSize);`

- **参数**：

    - `clipLimit`: 对比度限制，防止噪声放大

    - `tileGridSize`: 分块大小

### 9.4 CLAHE::apply () - 应用均衡化

- **功能**：对图像执行 CLAHE 均衡化

- **用法**：`clahe->apply(src, dst);`

- **优势**：比全局均衡化效果更好，不会过度增强噪声

---

## 10. 边缘检测

### 10.1 Sobel () - Sobel 一阶导数边缘检测

- **功能**：计算图像在水平 / 垂直方向的一阶梯度，检测对应方向的边缘

- **用法**：`Sobel(src, dst, ddepth, dx, dy, ksize=3);`

- **参数**：

    - `ddepth`: 输出图像深度（**必须用 CV_16S**，因为梯度有正负，8 位会截断负数）

    - `dx`: X 方向导数阶数（1 = 计算水平梯度，检测垂直边缘）

    - `dy`: Y 方向导数阶数（1 = 计算垂直梯度，检测水平边缘）

    - `ksize`: Sobel 核大小（1,3,5,7；**-1 表示使用 Schar 算子**，精度更高）

- **注意**：不能直接用 CV_8U 深度，否则负梯度会被截断为 0，丢失一半边缘

### 10.2 convertScaleAbs () - 梯度值转换

- **功能**：对图像元素取绝对值，再缩放转换为 8 位无符号图像

- **用法**：`convertScaleAbs(src, dst);`

- **公式**：`dst(x,y) = saturate_cast<uchar>(|src(x,y)|)`

- **作用**：将 Sobel/Laplacian 输出的有符号梯度转换为可显示的灰度图

### 10.3 Laplacian () - Laplacian 二阶导数边缘检测

- **功能**：计算图像的二阶导数，同时检测所有方向的边缘

- **用法**：`Laplacian(src, dst, ddepth, ksize=1);`

- **参数**：`ddepth`必须用 CV_16S

- **特点**：无需分方向计算，直接得到全方向边缘；但对噪声极其敏感

- **建议**：使用前先对图像进行高斯平滑，减少噪声影响

### 10.4 Canny () - Canny 边缘检测

- **功能**：多阶段边缘检测算法，效果最好

- **用法**：`Canny(src, dst, threshold1, threshold2);`

- **参数**：

    - `threshold1`: 低阈值（低于此值的边缘被丢弃）

    - `threshold2`: 高阈值（高于此值的边缘被保留）

- **调整建议**：高低阈值比例通常为 1:2 或 1:3；阈值越高，检测到的边缘越少

---

## 11. 模板匹配与霍夫变换

### 11.1 matchTemplate () - 模板匹配

- **功能**：在输入图像中查找与模板最相似的区域

- **原型**：`void matchTemplate(InputArray image, InputArray templ, OutputArray result, int method)`

- **参数**：

    - `image`: 输入图像（待搜索图像）

    - `templ`: 模板图像（需小于输入图像）

    - `result`: 输出匹配结果矩阵（大小为 image.cols-templ.cols+1 × image.rows-templ.rows+1）

    - `method`: 匹配方法

        - `TM_SQDIFF`: 平方差匹配（值越小匹配度越高）

        - `TM_CCORR`: 相关匹配（值越大匹配度越高）

        - `TM_CCOEFF`: 相关系数匹配（值越大匹配度越高）

- **调整建议**：TM_SQDIFF 计算最快但对光照敏感；TM_CCOEFF 效果最好但计算最慢

### 11.2 minMaxLoc () - 查找矩阵极值

- **功能**：在单通道矩阵中找到最小值、最大值及其对应的坐标

- **原型**：`void minMaxLoc(InputArray src, double* minVal, double* maxVal=0, Point* minLoc=0, Point* maxLoc=0, InputArray mask=noArray())`

- **参数**：

    - `src`: 输入单通道矩阵

    - `minVal`: 输出最小值（不需要传 NULL）

    - `maxVal`: 输出最大值（不需要传 NULL）

    - `minLoc`: 输出最小值坐标（不需要传 NULL）

    - `maxLoc`: 输出最大值坐标（不需要传 NULL）

    - `mask`: 可选掩码，指定要处理的区域

- **注意**：只能处理单通道矩阵；对于 TM_SQDIFF 方法取 minLoc，其他方法取 maxLoc

### 11.3 HoughLines () - 标准霍夫线变换

- **功能**：在二值图像中检测直线

- **原型**：`void HoughLines(InputArray image, OutputArray lines, double rho, double theta, int threshold)`

- **参数**：

    - `image`: 输入二值边缘图像（通常是 Canny 输出）

    - `lines`: 输出直线参数（每个元素是 Vec2f (rho, theta)）

    - `rho`: 距离分辨率（单位：像素，通常设为 1）

    - `theta`: 角度分辨率（单位：弧度，通常设为 CV_PI/180 即 1 度）

    - `threshold`: 累加器阈值（只有投票数超过此值的直线才被检测到）

- **调整建议**：threshold 是最关键参数，值越高检测到的直线越少但越准确

### 11.4 HoughCircles () - 霍夫圆检测

- **功能**：在灰度图像中检测圆形轮廓，自动找到图像中所有符合条件的圆

- **原型**：`void HoughCircles(InputArray image, OutputArray circles, int method, double dp, double minDist, double param1, double param2, int minRadius=0, int maxRadius=0)`

- **参数**：

    - `image`: 输入灰度图像（建议先做模糊去噪，否则噪声会导致大量误检测）

    - `circles`: 输出检测到的圆，每个元素是 Vec3f (x, y, radius)，分别是圆心坐标和半径

    - `method`: 检测方法，目前仅支持 `HOUGH_GRADIENT`

    - `dp`: 累加器分辨率，1 表示与原图同分辨率，2 表示累加器是原图的 1/2 大小

    - `minDist`: 检测到的两个圆心之间的最小距离，小于这个值的两个圆会被合并

    - `param1`: Canny 边缘检测的高阈值，低阈值自动设为它的一半

    - `param2`: 累加器阈值，值越小检测到的圆越多（包含假阳性），值越大检测越严格

    - `minRadius`: 检测圆的最小半径，小于这个值的圆会被忽略

    - `maxRadius`: 检测圆的最大半径，大于这个值的圆会被忽略

- **调整建议**：

    1. 输入前必须对图像做模糊去噪（比如 medianBlur），否则噪声会产生大量误检

    2. `minDist`是关键参数，要根据你要检测的圆的实际间距来设置，太小会检测到重复的圆，太大会漏检

    3. `param2`控制检测严格度，先从大往小调，直到检测到所有目标圆

    4. 如果知道目标圆的半径范围，一定要设置`minRadius`和`maxRadius`，可以大幅减少误检

---

## 12. 角点与特征检测

### 12.1 cornerHarris () - Harris 角点检测

- **功能**：在灰度图像中检测角点（交点、突出点），是经典的角点提取算法

- **原型**：`void cornerHarris(InputArray src, OutputArray dst, int blockSize, int ksize, double k, int borderType = BORDER_DEFAULT)`

- **参数**：

    - `src`: 输入图像，必须是 8 位 或 32 位 单通道灰度图

    - `dst`: 输出角点响应图（类型为 CV_32FC1，值越大表示越可能是角点）

    - `blockSize`: 邻域窗口大小（一般设 2、3、5，越大越稳定）

    - `ksize`: Sobel 导数核大小（必须是奇数，一般 3）

    - `k`: 自由参数，取值范围 0.04 ~ 0.06（固定 0.04 即可）

    - `borderType`: 边界填充模式，默认即可

- **调整建议**：

    - blockSize 越大，检测越稳定，但角点定位精度下降

    - k 越小越敏感，一般固定 0.04

    - 输出 dst 需要通过阈值筛选才能得到最终角点

    - 访问 dst 时必须用 `<float>` 类型，因为输出是 CV_32F 浮点型

### 12.2 goodFeaturesToTrack () - Shi-Tomasi 角点检测

- **功能**：基于 Harris 角点改进的角点检测算法，效果更稳定、角点分布更均匀

- **原型**：`void goodFeaturesToTrack(InputArray image, OutputArray corners, int maxCorners, double qualityLevel, double minDistance, InputArray mask = noArray(), int blockSize = 3, bool useHarrisDetector = false, double k = 0.04)`

- **参数**：

    - `image`: 输入图像，必须是 8 位 或 32 位 单通道灰度图

    - `corners`: 输出检测到的角点，类型为 vector

    - `maxCorners`: 最多检测多少个角点（限制数量，防止太多）

    - `qualityLevel`: 质量系数，一般 0.01~0.1，值越大筛选越严格，角点越少

    - `minDistance`: 两个角点之间的最小像素距离，防止角点扎堆

    - `mask`: 可选掩码，只在掩码非零区域检测角点

    - `blockSize`: 计算局部特征的窗口大小，默认 3

    - `useHarrisDetector`: 是否使用 Harris 算法，false 表示使用 Shi-Tomasi

    - `k`: Harris 算法的自由参数，默认 0.04

- **调整建议**：

    - maxCorners：根据需求设置，一般 100~2000

    - qualityLevel：0.01 是通用值，角点太少就调小，太多就调大

    - minDistance：越大角点越稀疏，越小越密集，一般 5~20

    - Shi-Tomasi 比 Harris 更稳定，优先使用

### 12.3 SIFT::create () - 创建 SIFT 特征检测器

- **功能**：创建 SIFT 尺度不变特征提取器，用于提取图像关键点与描述子

- **原型**：`static Ptr<SIFT> create(int nfeatures = 0, int nOctaveLayers = 3, double contrastThreshold = 0.04, double edgeThreshold = 10, double sigma = 1.6)`

- **参数**：

    - `nfeatures`: 保留的最佳特征点数量（0 = 不限制）

    - `nOctaveLayers`: 每个金字塔组的层数，默认 3

    - `contrastThreshold`: 对比度阈值，过滤弱特征点，越大过滤越多

    - `edgeThreshold`: 边缘阈值，过滤边缘点，越大保留越多边缘特征

    - `sigma`: 第一层高斯模糊的系数，默认 1.6

- **调整建议**：

    - 一般直接用默认参数即可：create (0,3,0.04,10,1.6)

    - 特征点太多：调大 contrastThreshold

    - 特征点太少：调小 contrastThreshold

### 12.4 detectAndCompute () - 检测关键点 + 计算描述子

- **功能**：一步完成特征点检测和描述子计算（SIFT/ORB 等通用接口）

- **参数**：

    - `image`: 输入灰度图像

    - `mask`: 掩码（noArray () 表示全图）

    - `kps`: 输出关键点 vector

    - `descriptors`: 输出描述子矩阵（每行一个特征描述子）

### 12.5 drawKeypoints () - 绘制特征点

- **功能**：在图像上画出检测到的关键点

- **参数**：

    - `image`: 原始图像

    - `keypoints`: 关键点集合

    - `outImage`: 输出绘制后的图像

    - `color`: 绘制颜色

    - `flags`: 绘制风格

        - `DRAW_RICH_KEYPOINTS`：绘制带方向、带大小的圆形特征点（最常用）

### 12.6 FastFeatureDetector::create () - 创建 FAST 角点检测器

- **功能**：创建**超高速度**的角点检测器，适合实时视频、实时检测

- **原型**：`static Ptr<FastFeatureDetector> create(int threshold = 10, bool nonmaxSuppression = true)`

- **参数**：

    - `threshold`: 亮度差阈值（0~255）
    越大 → 角点越少
    越小 → 角点越多（容易误检）
    常用：10 ~ 20

    - `nonmaxSuppression`: 是否开启非极大值抑制
    true = 去重，角点更均匀（默认开启）
    false = 保留所有候选点，会扎堆

### 12.7 fast->detect () - 只检测关键点（不计算描述子）

- **功能**：只提取角点位置，速度极快

- **参数**：

    - `image`: 输入灰度图

    - `keypoints`: 输出角点 vector

### 12.8 ORB::create () - 创建 ORB 特征检测器

- **功能**：**实时、免费、工业级最常用**的图像特征提取算法，结合 FAST 角点 + 二进制描述子，速度极快、效果好

- **原型**：`static Ptr<ORB> create(int nfeatures = 500, float scaleFactor = 1.2f, int nlevels = 8, int edgeThreshold = 31, int firstLevel = 0, int WTA_K = 2, int scoreType = ORB::HARRIS_SCORE, int patchSize = 31, int fastThreshold = 20)`

- **参数（重点）**：

    - `nfeatures`: 最多提取多少个特征点（默认 500）

    - `scaleFactor`: 金字塔缩放系数（默认 1.2）

    - `nlevels`: 金字塔层数（默认 8）

    - `edgeThreshold`: 边缘忽略阈值（默认 31）

    - `fastThreshold`: FAST 角点阈值

- **调整建议**：

    - 直接 ORB::create () 用默认参数就非常好用

    - 想提取更多特征：把 nfeatures 改大（如 1000, 2000）

    - 实时场景（视频 / 摄像头）：ORB 是首选

---

## 13. 重要注意事项汇总

1. **BGR 顺序**：OpenCV 读取的彩色图是 BGR 顺序，不是 RGB，和其他库对接时要注意转换

2. **坐标顺序**：OpenCV 中坐标是 `(x, y)`，对应 `(列, 行)`，访问 Mat 时是 `at(y, x)`

3. **有符号梯度**：Sobel/Laplacian 必须用 CV_16S 深度，否则会丢失负梯度

4. **waitKey 必须**：imshow 之后必须调用 waitKey，否则窗口不会刷新

5. **模板匹配极值**：不同的匹配方法，要取不同的极值位置（SQDIFF 取 min，其他取 max）
> （注：文档部分内容可能由 AI 生成）