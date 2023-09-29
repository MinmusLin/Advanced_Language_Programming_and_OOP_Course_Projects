# Matrix Operations and Image Processing

## 项目名称

Matrix_Operations_and_Image_Processing

## 项目实现功能

矩阵运算与图像处理

1. 矩阵行列式运算

1. 矩阵加法运算

1. 矩阵数乘运算

1. 矩阵转置运算

1. 矩阵乘法运算

1. 矩阵Hadamard(哈达马)乘积运算

1. 矩阵卷积运算

1. 矩阵卷积运算应用

1. Otsu算法(大津算法)

1. Segmentation算法(传统分割算法)

## 项目文件组成

### 头文件

* `cmd_console_tools.h`
伪图形界面函数工具集的头文件

* `MOIP.h`
图像处理函数、菜单函数、矩阵运算函数、工具函数的头文件

### 源文件

* `cmd_console_tools.cpp`
伪图形界面函数工具集的实现

* `MOIP_image.cpp`
图像处理函数的实现

* `MOIP_main.cpp`
菜单函数的实现

* `MOIP_matrix.cpp`
矩阵运算函数的实现

* `MOIP_tools.cpp`
工具函数的实现

### 资源文件

* `images文件夹`
存放图像处理的示例图像

  * `demo.jpg`
  示例图像

## 项目技术细节

### 矩阵卷积的计算

```cpp
void Matrix_Convolution(void)
{
    double A[maxRow][maxCol], B[maxRow + 2][maxCol + 2] = { 0 }, C[maxRow][maxCol] = { 0 }, kernel[kernelSize][kernelSize];
    cct_showstr(4, 6, "请输入待卷积矩阵(", COLOR_HWHITE, COLOR_BLACK);
    cout << maxRow << "阶方阵):";
    if (!input_matrix(A, maxRow, maxCol, 4, 6, "", false))
        return;
    cct_showstr(4, 10 + maxCol, "请输入卷积核矩阵(", COLOR_HWHITE, COLOR_BLACK);
    cout << kernelSize << "阶方阵):";
    print_matrix(4, 11 + maxCol, kernelSize, kernelSize);
    for (int i = 0; i < kernelSize; i++)
        for (int j = 0; j < kernelSize; j++) {
            cct_gotoxy(7 + 10 * j, 12 + maxCol + i);
            cin >> kernel[i][j];
            if (!cin.good()) {
                cin.clear();
                cin.ignore(65536, '\n');
                print_prompt("输入错误! ", COLOR_HWHITE, COLOR_RED);
                system("pause");
                return;
            }
        }
    for (int i = 0; i < maxRow; i++)
        for (int j = 0; j < maxCol; j++)
            B[i + 1][j + 1] = A[i][j];
    for (int i = 0; i < maxRow; i++)
        for (int j = 0; j < maxCol; j++)
            for (int m = 0; m < kernelSize; m++)
                for (int n = 0; n < kernelSize; n++)
                    C[i][j] += B[i + m][j + n] * kernel[m][n];
    cct_showstr(4, 14 + maxRow + kernelSize, "卷积矩阵(", COLOR_HWHITE, COLOR_BLACK);
    cout << maxRow << "阶方阵) =";
    output_matrix(C, maxRow, maxCol, 4, 14 + maxRow + kernelSize, "", false);
    print_prompt("计算完成! ", COLOR_HWHITE, COLOR_GREEN);
    system("pause");
}
```

### Otsu阈值的计算

```cpp
int calculate_Otsu_threshold(Mat grayImage, int height, int width)
{
    /* Calculate histogram */
    int histogram[256] = { 0 };
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            histogram[grayImage.at<uchar>(i, j)]++;

    /* Calculate Otsu threshold */
    int bestThreshold = 0, Otsu_threshold = 0;
    double maxVariance = 0.0;
    for (int k = 0; k < 256; k++) {
        double p1 = 0.0, p2 = 0.0, m1 = 0.0, m2 = 0.0;
        for (int i = 0; i <= k; i++) {
            p1 += histogram[i] / double(width * height);
            m1 += i * histogram[i] / double(width * height);
        }
        if (p1 != 0.0)
            m1 /= p1;
        for (int i = k + 1; i <= 255; i++) {
            p2 += histogram[i] / double(width * height);
            m2 += i * histogram[i] / double(width * height);
        }
        if (p2 != 0.0)
            m2 /= p2;
        double m = p1 * m1 + p2 * m2;
        double variance = p1 * (m1 - m) * (m1 - m) + p2 * (m2 - m) * (m2 - m);
        if (variance > maxVariance) {
            maxVariance = variance;
            Otsu_threshold = k;
        }
    }

    /* Return Otsu threshold */
    return Otsu_threshold;
}
```

## 集成开发环境

* Microsoft Visual Studio

## 编译运行环境

* 本项目仅适用于x64架构

* Windows控制台主机的旧版控制台运行（取消选项“快速编辑模式”和“插入模式”）

## 库依赖

* `OpenCV`

  * `配置属性` - `VC++ 目录` - `常规` - `包含目录`

    * `...\opencv\build\include\opencv2`

    * `...\opencv\build\include\opencv`

    * `...\opencv\build\include`

  * `配置属性` - `VC++ 目录` - `常规` - `库目录`

    * `...\opencv\build\x64\vc15\lib`

  * `配置属性` - `链接器` - `输入` - `附加依赖项`

    * `...\opencv\build\x64\vc15\lib\opencv_world341d.lib`

  * ```cpp
    #include <opencv2/opencv.hpp>
    ```

## 相关资料

* [OpenCV Documentation](https://docs.opencv.org)

* [Convolution Visualizer](https://ezyang.github.io/convolution-visualizer/index.html)
这个交互式可视化演示了不同的卷积参数如何影响输入、权重和输出矩阵之间的形状和数据依赖关系。当鼠标悬停在输入/输出上时，将突出显示相应的输出/输入；当鼠标悬停在权重上时，将突出显示用于计算输出的相应输入。

## 文档更新日期

2023年9月30日