# OpenCV常用函数速查手册

> 整合了 OpenCV 基础到进阶的常用函数详解，按功能分类整理，方便快速查阅
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

11. [重要注意事项](#重要注意事项汇总)

---

## 1. 基本图像操作

### 1.1 imread () - 读取图像文件

- **功能**：从指定路径加载图像到 Mat 对象中

- **原型**：`Mat imread(const string& filename, int flags=IMREAD_COLOR)`

- **参数**：

    - `filename`: 图像文件的完整路径（支持 jpg、png、bmp 等格式）

    - `flags`: 读取模式

        - `IMREAD_COLOR(1)`: 以彩色模式读取（默认，忽略 alpha 通道）

        - `IMREAD_GRAYSCALE(0)`: 以灰度模式读取

        - `IMREAD_UNCHANGED(-1)`: 读取原始图像（包含 alpha 透明通道）

- **调整建议**：处理带透明效果的 PNG 必须用 - 1；灰度处理用 0 可节省内存

### 1.2 namedWindow () - 创建显示窗口

- **功能**：提前创建一个用于显示图像的窗口

- **原型**：`void namedWindow(const string& winname, int flags=WINDOW_AUTOSIZE)`

- **参数**：

    - `winname`: 窗口唯一名称（后续 imshow 需对应此名称）

    - `flags`: 窗口属性标志

        - `WINDOW_AUTOSIZE`: 窗口大小自动适应图像（默认，不可手动缩放）

        - `WINDOW_FREERATIO`: 窗口可自由缩放，图像比例随窗口变化

        - `WINDOW_KEEPRATIO`: 窗口可缩放，但保持图像原始比例

- **注意**：不调用此函数时，imshow 会自动创建 WINDOW_AUTOSIZE 窗口

### 1.3 imshow () - 显示图像

- **功能**：在指定窗口中显示 Mat 图像

- **原型**：`void imshow(const string& winname, InputArray mat)`

- **参数**：

    - `winname`: 要显示的窗口名称

    - `mat`: 要显示的 Mat 图像对象

- **注意**：必须配合 waitKey () 使用，否则窗口会一闪而过

### 1.4 imwrite () - 保存图像文件

- **功能**：将 Mat 图像保存到指定路径

- **原型**：`bool imwrite(const string& filename, InputArray img, const vector<int>& params=vector<int>())`

- **参数**：

    - `filename`: 保存文件的完整路径（后缀决定保存格式）

    - `img`: 要保存的 Mat 图像对象

    - `params`: 可选编码参数（格式为 {参数 ID, 值}）

        - JPEG: `{IMWRITE_JPEG_QUALITY, 0-100}`（默认 95，值越大质量越高）

        - PNG: `{IMWRITE_PNG_COMPRESSION, 0-9}`（默认 3，值越大压缩率越高）

- **返回值**：保存成功返回 true，失败返回 false

### 1.5 waitKey () - 等待按键输入

- **功能**：暂停程序执行，等待用户按键，并返回按键 ASCII 码

- **原型**：`int waitKey(int delay=0)`

- **参数**：

    - `delay`: 等待时间（毫秒）

        - `0`: 无限等待直到用户按下任意键

        - `>0`: 等待指定毫秒数，超时自动返回 - 1

- **注意**：是 OpenCV 窗口系统的核心，必须调用才能正常显示和交互

### 1.6 destroyAllWindows () - 销毁所有窗口

- **功能**：关闭并释放所有由 OpenCV 创建的显示窗口

- **原型**：`void destroyAllWindows()`

- **说明**：程序结束时系统会自动释放，但显式调用是良好编程习惯

---

## 2. Mat 类型核心操作

### 2.1 Mat 属性

|属性 / 方法|功能|用法|说明|
|---|---|---|---|
|`Mat::cols`|获取图像宽度（列数）|`int width = mat.cols;`|只读属性，返回水平方向像素数量|
|`Mat::rows`|获取图像高度（行数）|`int height = mat.rows;`|只读属性，返回垂直方向像素数量|
|`Mat::channels()`|获取图像通道数|`int ch = mat.channels();`|灰度图 = 1，彩色图 = 3，带透明通道 = 4|
|`Mat::depth()`|获取单通道像素数据类型深度|`int d = mat.depth();`|0=CV_8U (8 位无符号)，1=CV_8S 等|
|`Mat::type()`|获取完整数据类型（深度 + 通道数）|`int t = mat.type();`|常用值：CV_8UC1 (灰度图)、CV_8UC3 (彩色图)|
|`Mat::total()`|获取总像素数量|`long total = mat.total();`|返回值 = 行数 × 列数，与通道数无关|
### 2.2 Mat 构造方法

- **方法 1**：指定尺寸和类型

    ```cpp
    
    Mat m(rows, cols, type);
    Mat m(Size(width, height), type);
    ```

- **方法 2**：创建特殊值矩阵

    ```cpp
    
    Mat m = Mat::zeros(Size(w,h), type); // 全黑
    Mat m = Mat::ones(Size(w,h), type);  // 全1
    Mat m = Mat::eye(Size(w,h), type);   // 单位矩阵
    ```

- **方法 3**：快速初始化小矩阵

    ```cpp
    
    Mat m = (Mat_<float>(2,3) << 1,0,100, 0,1,50);
    ```

- **方法 4**：图像拷贝

    ```cpp
    
    Mat m = src;          // 浅拷贝（共享数据）
    Mat m = src.clone();  // 深拷贝（完全独立）
    src.copyTo(m);        // 深拷贝（功能同clone()）
    ```

### 2.3 像素遍历方法

- **数组方式（直观，随机访问）**

    ```cpp
    
    // 三通道图像
    Vec3b pixel = mat.at<Vec3b>(row, col);
    int blue = pixel[0], green = pixel[1], red = pixel[2];
    
    // 单通道图像
    uchar p = mat.at<uchar>(row, col);
    ```

- **指针方式（最快，批量遍历）**

    ```cpp
    
    uchar* rowPtr = mat.ptr<uchar>(row);
    for (int col=0; col<mat.cols; col++) {
        uchar blue = *rowPtr++;
        uchar green = *rowPtr++;
        uchar red = *rowPtr++;
    }
    ```

### 2.4 像素类型

- `uchar`: 单通道 8 位无符号像素（0-255）

- `Vec3b`: 三通道 8 位无符号像素（BGR 顺序）

- `Vec4b`: 四通道 8 位无符号像素（BGRA 顺序）

---

## 3. 图像算术与位操作

### 3.1 add () - 逐像素加法

- **功能**：对两个相同大小和类型的图像进行逐像素相加

- **用法**：`add(src1, src2, dst);`

- **公式**：`dst(x,y) = saturate_cast<uchar>(src1(x,y) + src2(x,y))`

- **特点**：自动截断超出 0-255 的像素值（不会溢出）

- **应用**：加正数提高亮度，加负数降低亮度

### 3.2 subtract () - 逐像素减法

- **功能**：对两个相同大小和类型的图像进行逐像素相减

- **用法**：`subtract(src1, src2, dst);`

- **公式**：`dst(x,y) = saturate_cast<uchar>(src1(x,y) - src2(x,y))`

- **特点**：自动截断小于 0 的像素值为 0

- **应用**：减去常数降低亮度，减去背景图像提取前景

### 3.3 addWeighted () - 加权加法（融合）

- **功能**：计算两个图像的加权和，实现图像融合或亮度对比度调整

- **用法**：`addWeighted(src1, alpha, src2, beta, gamma, dst);`

- **公式**：`dst(x,y) = saturate_cast<uchar>(src1(x,y)*alpha + src2(x,y)*beta + gamma)`

- **参数**：

    - `alpha`: src1 的权重系数

    - `beta`: src2 的权重系数（通常 alpha+beta=1 用于融合）

    - `gamma`: 亮度偏移量

- **调整建议**：

    - 亮度调整：src2 设为全黑，beta=0，gamma 控制亮度

    - 对比度调整：src2 设为全灰，beta=1-alpha，alpha>1 提高对比度

### 3.4 bitwise_not () - 按位取反

- **功能**：对图像每个像素的二进制位进行取反操作

- **用法**：`bitwise_not(src, dst, mask=noArray());`

- **效果**：8 位图像中 0→255，255→0，实现图像颜色反转

- **应用**：生成反色图像、反转掩码区域

### 3.5 bitwise_and () - 按位与

- **功能**：对两个图像对应像素的二进制位进行与操作

- **用法**：`bitwise_and(src1, src2, dst, mask=noArray());`

- **核心应用**：**掩码抠图 / ROI 提取**（src1=src2 = 原图时，仅保留 mask 为 255 的区域）

- **特点**：只有两个输入对应位都为 1 时，输出位才为 1

### 3.6 bitwise_or () - 按位或

- **功能**：对两个图像对应像素的二进制位进行或操作

- **用法**：`bitwise_or(src1, src2, dst, mask=noArray());`

- **特点**：只要有一个输入对应位为 1，输出位就为 1

- **应用**：合并两个图像的非零区域、添加水印、叠加图形

---

## 4. 绘图与文字绘制

### 4.1 基础类型

- **Point 类**：表示二维坐标点 `Point(x, y)`（x = 列，y = 行，原点在左上角）

- **Scalar 类**：表示颜色值 `Scalar(B, G, R)`（OpenCV 默认 BGR 顺序）

### 4.2 line () - 绘制直线

- **功能**：在图像上绘制连接两个点的直线段

- **用法**：`line(img, pt1, pt2, color, thickness=1, lineType=LINE_8);`

- **参数**：

    - `pt1`: 直线起点坐标

    - `pt2`: 直线终点坐标

    - `thickness`: 线条宽度（像素）

    - `lineType`: 线条类型（LINE_8=8 连通线，LINE_AA = 抗锯齿线）

### 4.3 rectangle () - 绘制矩形

- **功能**：在图像上绘制矩形框

- **用法**：`rectangle(img, pt1, pt2, color, thickness=1);`

- **参数**：

    - `pt1`: 矩形左上角坐标

    - `pt2`: 矩形右下角坐标

    - `thickness`: 线条宽度（-1 表示填充矩形）

### 4.4 circle () - 绘制圆形

- **功能**：在图像上绘制空心圆或实心圆

- **用法**：`circle(img, center, radius, color, thickness=1);`

- **参数**：

    - `center`: 圆心坐标

    - `radius`: 圆的半径（像素）

    - `thickness`: 线条宽度（-1 表示填充整个圆）

### 4.5 putText () - 绘制文本

- **功能**：在图像上绘制指定字体的英文文本

- **用法**：`putText(img, text, org, fontFace, fontScale, color, thickness=1);`

- **参数**：

    - `text`: 要绘制的文本（仅支持 ASCII 字符，不支持中文）

    - `org`: 文本左下角的坐标

    - `fontFace`: 字体类型（FONT_HERSHEY_SIMPLEX 最常用）

    - `fontScale`: 字体缩放因子（1 为标准大小）

- **注意**：OpenCV 原生不支持中文，绘制中文需使用 FreeType 扩展库

---

## 5. 颜色空间与通道操作

### 5.1 split () - 通道分割

- **功能**：将多通道图像按通道顺序分割为多个单通道图像

- **用法**：`split(src, dst);`

- **参数**：

    - `src`: 输入多通道图像

    - `dst`: 输出 vector容器，每个元素对应一个单通道图像

- **说明**：对于 BGR 彩色图像，dst [0]= 蓝色通道，dst [1]= 绿色通道，dst [2]= 红色通道

### 5.2 merge () - 通道合并

- **功能**：将多个同大小同类型的单通道图像合并为一个多通道图像

- **用法**：`merge(src, dst);`

- **参数**：

    - `src`: 输入 vector容器，所有图像必须尺寸和类型一致

    - `dst`: 输出多通道图像，通道数等于输入 vector 的元素个数

### 5.3 cvtColor () - 颜色空间转换

- **功能**：将图像从一个颜色空间转换到另一个

- **用法**：`cvtColor(src, dst, code);`

- **常用转换代码**：

    - `COLOR_BGR2GRAY`: BGR 彩色转灰度（最常用）

    - `COLOR_BGR2HSV`: BGR 转 HSV（适合颜色识别，受光照影响小）

    - `COLOR_BGR2RGB`: BGR 转 RGB（用于与其他库 / 工具交互）

    - `COLOR_GRAY2BGR`: 灰度转 BGR 彩色

---

## 6. 几何变换

### 6.1 resize () - 图像缩放

- **功能**：调整图像到指定尺寸或按比例缩放

- **用法 1**：指定目标尺寸 `resize(src, dst, Size(dst_width, dst_height));`

- **用法 2**：指定缩放因子 `resize(src, dst, Size(), fx, fy);`

- **参数**：

    - `Size(dst_width, dst_height)`: 目标尺寸（**宽在前，高在后！**）

    - `fx`: 水平方向缩放因子

    - `fy`: 垂直方向缩放因子

    - `interpolation`: 插值方法

        - `INTER_LINEAR`: 双线性插值（默认，适合放大）

        - `INTER_AREA`: 区域插值（适合缩小，效果最好）

        - `INTER_CUBIC`: 双三次插值（放大效果好但速度慢）

- **⚠️ 常见错误**：Size 参数顺序是 (宽，高) 即 (cols,rows)，不是 (rows,cols)

### 6.2 warpAffine () - 仿射变换

- **功能**：对图像执行任意仿射变换（平移、旋转、缩放、剪切）

- **用法**：`warpAffine(src, dst, M, dsize);`

- **参数**：

    - `M`: 2x3 仿射变换矩阵（float 类型）

    - `dsize`: 输出图像尺寸 (宽，高)

### 6.3 getRotationMatrix2D () - 获取旋转缩放矩阵

- **功能**：生成绕指定点旋转并缩放的仿射变换矩阵

- **用法**：`Mat M = getRotationMatrix2D(center, angle, scale);`

- **参数**：

    - `center`: 旋转中心坐标 (Point (x,y))，**x=cols, y=rows**

    - `angle`: 旋转角度（度，逆时针为正）

    - `scale`: 缩放比例（1.0 = 不变）

- **⚠️ 常见错误**：旋转中心坐标是 (x,y) 即 (cols,rows)，不是 (rows,cols)

### 6.4 getAffineTransform () - 获取三点仿射变换矩阵

- **功能**：根据三对对应点计算仿射变换矩阵

- **用法**：`Mat M = getAffineTransform(srcPoints, dstPoints);`

- **参数**：

    - `srcPoints`: 源图像中 3 个不共线的点

    - `dstPoints`: 目标图像中对应的 3 个点

### 6.5 getPerspectiveTransform () - 获取四点透视变换矩阵

- **功能**：根据四对对应点计算透视变换矩阵

- **用法**：`Mat M = getPerspectiveTransform(srcPoints, dstPoints);`

- **参数**：

    - `srcPoints`: 源图像中 4 个不共线的点

    - `dstPoints`: 目标图像中对应的 4 个点

### 6.6 warpPerspective () - 透视变换

- **功能**：对图像执行透视变换（纠正倾斜、鸟瞰图生成）

- **用法**：`warpPerspective(src, dst, M, dsize);`

- **参数**：同 warpAffine ()，但 M 是 3x3 透视变换矩阵

### 6.7 pyrUp ()/pyrDown () - 图像金字塔采样

- **pyrUp()**：上采样（放大 2 倍，先放大再高斯模糊）

- **pyrDown()**：下采样（缩小 2 倍，先高斯模糊再丢弃偶数行和列）

- **用法**：

    ```cpp
    
    pyrUp(src, dst);   // 放大2倍
    pyrDown(src, dst); // 缩小2倍
    ```

---

## 7. 形态学操作

### 7.1 形态学核创建

- **全 1 矩形核**：`Mat kernel = Mat_<uchar>::ones(Size(width, height));`

- **推荐方法**：`getStructuringElement(shape, ksize)`（支持矩形、椭圆、十字形）

### 7.2 erode () - 腐蚀操作

- **功能**：用核扫描图像，取核覆盖区域的最小值作为输出像素

- **效果**：缩小白色 (亮) 区域，扩大黑色 (暗) 区域；消除小的亮噪点，断开细连接

- **用法**：`erode(src, dst, kernel, iterations=1);`

- **参数**：`iterations`为腐蚀迭代次数（次数越多效果越强）

### 7.3 dilate () - 膨胀操作

- **功能**：用核扫描图像，取核覆盖区域的最大值作为输出像素

- **效果**：扩大白色 (亮) 区域，缩小黑色 (暗) 区域；填充小的暗孔洞，连接断裂区域

- **用法**：`dilate(src, dst, kernel, iterations=1);`

### 7.4 morphologyEx () - 通用形态学操作

- **功能**：执行各种高级形态学操作

- **用法**：`morphologyEx(src, dst, op, kernel, iterations=1);`

- **核心操作类型**：

    - `MORPH_OPEN`: 开运算（先腐蚀后膨胀）→ 消除小白噪点、分离粘连物体

    - `MORPH_CLOSE`: 闭运算（先膨胀后腐蚀）→ 填充小黑孔洞、连接断裂物体

    - `MORPH_TOPHAT`: 礼帽运算（原图 - 开运算）→ 提取比原图亮的小区域

    - `MORPH_BLACKHAT`: 黑帽运算（闭运算 - 原图）→ 提取比原图暗的小区域

- **调整建议**：核的大小决定了能处理的噪点 / 孔洞的最大尺寸

---

## 8. 图像平滑滤波

### 8.1 blur () - 均值滤波

- **功能**：用核覆盖区域内所有像素的平均值替换中心像素

- **用法**：`blur(src, dst, ksize);`

- **参数**：`ksize`为滤波核尺寸（必须为正奇数，如 Size (3,3)）

- **特点**：计算速度最快，但会严重模糊图像边缘

### 8.2 GaussianBlur () - 高斯滤波

- **功能**：用高斯核进行加权平均，中心像素权重最高，边缘权重递减

- **效果**：比均值滤波更自然，能较好保留边缘细节，专门用于去除高斯噪声

- **用法**：`GaussianBlur(src, dst, ksize, sigmaX);`

- **参数**：

    - `sigmaX`: X 方向高斯标准差（值越大平滑效果越强）

    - `sigmaX`设为 0 时，OpenCV 会根据核大小自动计算最优值

### 8.3 medianBlur () - 中值滤波

- **功能**：用核覆盖区域内所有像素的中值替换中心像素

- **效果**：对椒盐噪声（黑白点噪声）效果极佳，几乎不模糊图像边缘

- **用法**：`medianBlur(src, dst, ksize);`

- **参数**：`ksize`为核边长（必须为大于 1 的正奇数，如 3、5、7，**注意是单个整数**）

- **特点**：非线性滤波，边缘保留能力强，但计算速度比线性滤波慢

---

## 9. 直方图操作

### 9.1 calcHist () - 计算图像直方图

- **功能**：统计图像中每个灰度级的像素数量，生成直方图

- **用法**：`calcHist(&src, 1, &channels, mask, hist, 1, &histSize, &ranges);`

- **参数**：

    - `&src`: 输入图像地址

    - `1`: 输入图像数量

    - `&channels`: 要统计的通道索引（灰度图用 {0}）

    - `mask`: 可选掩码（空 Mat 表示统计整个图像）

    - `hist`: 输出直方图（单通道 float 类型 Mat）

    - `1`: 直方图维度（灰度图 = 1）

    - `&histSize`: 灰度级数量（通常 256）

    - `&ranges`: 灰度值范围（灰度图 {0,256}，左闭右开）

### 9.2 equalizeHist () - 全局直方图均衡化

- **功能**：通过拉伸灰度分布，增强图像全局对比度

- **用法**：`equalizeHist(src, dst);`

- **参数**：`src`必须是 8 位单通道灰度图像

- **特点**：计算简单速度快，但会过度放大噪声，且对局部对比度改善有限

### 9.3 createCLAHE () - 创建自适应直方图均衡化对象

- **功能**：创建对比度受限的自适应直方图均衡化 (CLAHE) 对象

- **用法**：`Ptr<CLAHE> clahe = createCLAHE(clipLimit=40.0, tileGridSize=Size(8,8));`

- **参数**：

    - `clipLimit`: 对比度限制阈值（通常设为 2.0-4.0，值越大对比度越强）

    - `tileGridSize`: 图像分块大小（默认 8x8）

### 9.4 CLAHE::apply () - 执行自适应直方图均衡化

- **功能**：对输入图像应用 CLAHE 算法

- **用法**：`clahe->apply(src, dst);`

- **优点**：解决了全局均衡化过度放大噪声的问题，能更好保留图像局部细节

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

## 重要注意事项汇总

1. **坐标系统**：OpenCV 中坐标原点在图像左上角，x 向右（列），y 向下（行）

2. **颜色顺序**：OpenCV 默认彩色图像为 BGR 顺序，不是 RGB

3. **Size 参数**：所有 Size (width, height) 都是**宽在前，高在后**，对应 (cols, rows)

4. **梯度深度**：Sobel 和 Laplacian 输出必须用 CV_16S 深度，否则会丢失负梯度

5. **图像路径**：imread 的路径必须全英文，否则会读取空图像导致后续报错
> （注：文档部分内容可能由 AI 生成）