# OpenCV4_Learning

个人 OpenCV4 学习实践记录 —— **14 个主题，每个主题一个独立可运行的示例**，代码带中文注释与函数说明。

> 📌 这是**学习记录**仓库：每个章节是一份独立的示例工程（`vcxproj`），可单独打开运行，不是完整项目。

## 学习内容

| # | 主题 | 主要用到的 API |
|---|------|---------------|
| **001** | 基本读写存操作 | `imread` · `imshow` · `imwrite` · `namedWindow` |
| **002** | Mat 类的属性、构造、遍历 | `Mat` 构造 · `clone` · `copyTo` · `at<>` 像素访问 |
| **003** | 图像算术操作 | `add` · `subtract` |
| **004** | 图像位操作 | `bitwise_and` · `bitwise_or` · `bitwise_not` · `at<>` |
| **005** | 画图和写字操作 | `line` · `rectangle` · `circle` · `putText` |
| **006** | 颜色空间转换 | `cvtColor` · `split` · `merge` |
| **007** | 几何变换 | `resize` · `warpAffine` · `getRotationMatrix2D` · `warpPerspective` |
| **008** | 形态学操作 | `erode` · `dilate` · `getStructuringElement` · `morphologyEx` |
| **009** | 图像平滑操作 | `blur` · `GaussianBlur` · `medianBlur` · `bilateralFilter` |
| **010** | 直方图 | `calcHist` · `equalizeHist` · `at<>` |
| **011** | 边缘检测 | `Sobel` · `Laplacian` · `Canny` |
| **012** | 模板匹配和霍夫变换 | `matchTemplate` · `minMaxLoc` · `HoughLines` |
| **013** | 图像特征提取与描述 | `SIFT` · `ORB` · `minMaxLoc` |
| **014** | 轮廓查找与几何测量 | `threshold` · `findContours` · `drawContours` · `contourArea` · `boundingRect` |

## 环境要求

| 项 | 值 |
|---|---|
| 语言 | C++ |
| 图像库 | **OpenCV 4.x**（本地链接的是 `opencv_world4130*`） |
| IDE | Visual Studio（工程工具集 **`v145`**） |
| 平台 | **x64**（示例链接的是 `x64/vc16` 版本的 OpenCV，**选 Win32 会链接失败**） |
| 系统 | Windows（运行时需要 `opencv_world*.dll`） |

## 怎么跑

⚠️ 这是**个人学习环境**的工程，直接 clone 下来需要改 **两处** 才能编译：

**① 改 OpenCV 路径**

每个 `.vcxproj` 里的 include / lib 路径指向本机目录（`D:\code_work\opencv\build\...`）
→ 改成**你自己的 OpenCV 路径**（项目属性 → VC++ 目录 → 包含目录 / 库目录）

**② 改测试图片路径**

示例里读图用的是**绝对路径**（如 `D:/opencv-logo.png`）
→ 改成你自己的图片路径，或把图片放到对应目录

**然后：**

1. 用 Visual Studio 打开**对应章节的 `.vcxproj`**（本仓库没有总 `.sln`，每章独立）
2. 解决方案平台选 **x64**
3. F5 运行

## 代码风格

- 每个示例**顶部注释列出本次用到的 OpenCV 函数**
- 关键调用带**行内中文注释**
- 每章**独立工程、互不依赖**，可单独打开运行

## 说明

本仓库为个人学习记录，代码仅供学习参考。
