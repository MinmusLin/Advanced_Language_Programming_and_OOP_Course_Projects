# ASCII Image and Video

## 项目名称

ASCII_Image_and_Video

## 项目实现功能

ASCII图像查看器和视频播放器

1. 逐元素矩阵运算（运算符重载方式）

1. ASCII图像查看器（灰度图像）

1. ASCII图像查看器（彩色图像）

1. ASCII图像查看器（彩色图像）（反显模式）

1. ASCII视频播放器（灰度视频）

1. ASCII视频播放器（彩色视频）

1. ASCII视频播放器（彩色视频）（反显模式）

## 项目文件组成

### 头文件

* `Array.h`
`Array` 类的头文件

* `cmd_console_tools.h`
伪图形界面函数工具集的头文件

* `FastPrinter.h`
底层控制台绘制函数工具集的头文件

* `PicReader.h`
读取图像文件函数工具集的头文件

### 源文件

* `Array.cpp`
`Array` 类的实现

* `cmd_console_tools.cpp`
伪图形界面函数工具集的实现

* `FastPrinter.cpp`
底层控制台绘制函数工具集的实现

* `Image.cpp`
图像查看函数的实现

* `Main.cpp`
菜单函数的实现

* `Matrix.cpp`
逐元素矩阵运算函数的实现

* `PicReader.cpp`
读取图像文件函数工具集的实现

* `Video.cpp`
视频播放函数的实现

### 资源文件

* `images文件夹`
存放图像查看的示例图像

  * `demo.jpg`
  示例图像

* `videos文件夹`
存放视频播放的示例视频

  * `complete_demo.mp4`
  完整示例视频

  * `simplified_demo.mp4`
  简化示例视频

  * `bgm.wav`
  示例视频的背景音乐

## 项目技术细节

### `Array` 类的实现

#### 概述

`Array` 类是一个用于操作和处理多维整数数组的C++类。它提供了各种操作，包括元素访问、数学运算、重塑和元素级别操作。该类允许您创建和管理多维整数数组，并支持多种数组操作。

#### 类定义

```cpp
const enum Operation {
    Add,
    Sub,
    Mul,
    Div,
    Opp,
    MatMulNum,
    NumMulMat,
    MatDivNum,
    NumDivMat
};

class Array {
private:
    int* data = NULL;
    int shape[HIGHEST_DIMENSION] = { 0 };
    int axisNum = 0;
    int nowAxis = 0;
    int index = 0;
    int len = 1;
    bool check = true;
    void checkTypes(bool is_index);
    int calculateOffset(int indexs[]);
    bool is_homogeneous_matrix(Array& a, Array& b);
    Array elementwiseOperation(Array& arr, Operation optn);
    template <typename T1, typename T2> bool isTypeSame(T1, T2);
    template <typename T> bool isTypeSame(T, T);
    template <typename T> void checkType(bool is_index, const T& arg);
    template <typename T, typename... Args> void checkTypes(bool is_index, const T& arg, const Args&... args);
public:
    Array();
    Array(const Array& other);
    template <typename... Args> Array(Args... args);
    ~Array();
    void set(int value);
    int* get_content(void);
    template <typename... Args> Array& at(Args... args);
    template <typename... Args> void reshape(Args... args);
    Array operator[](int n);
    Array& operator=(int value);
    Array operator+(Array& arr);
    Array operator-(void);
    Array operator-(Array& arr);
    Array operator*(Array& arr);
    Array operator/(Array& arr);
    operator int(void);
    friend ostream& operator<<(ostream& out, const Array& arr);
    friend istream& operator>>(istream& in, Array& arr);
    friend Array elementwiseOperation(Array& arr, int n, Operation optn);
    friend Array operator*(Array& arr, int n);
    friend Array operator*(int n, Array& arr);
    friend Array operator/(Array& arr, int n);
    friend Array operator/(int n, Array& arr);
    friend void input(Array& arr, char name);
};
```

#### 私有数据成员

```cpp
int* data = NULL; // 数据首地址
```

```cpp
int shape[HIGHEST_DIMENSION] = { 0 }; // 维度大小
```

```cpp
int axisNum = 0; // 维数
```

```cpp
int nowAxis = 0; // 当前维数
```

```cpp
int index = 0; // 索引
```

```cpp
int len = 1; // 数据个数
```

```cpp
bool check = true; // 是否在析构函数中释放内存
```

#### 构造函数

```cpp
Array();
```
创建一个空 `Array` 对象。

```cpp
Array(const Array& other);
```
复制构造函数用于创建一个新的对象，该对象的属性和值与另一个已存在的对象完全相同。

```cpp
template <typename... Args> Array(Args... args);
```
使用提供的参数构造一个数组对象，参数应该是整数，表示每个维度的大小。

#### 析构函数

```cpp
~Array();
```
释放内存。

#### 私有成员函数

```cpp
void checkTypes(bool is_index);
```
递归检查一系列参数的类型是否匹配函数的终止函数。

```cpp
int calculateOffset(int indexs[]);
```
根据给定的索引数组，计算出在一维数据中的偏移量。

```cpp
bool is_homogeneous_matrix(Array& a, Array& b);
```
判断两个矩阵是否具有相同的形状，即是否可以进行元素级别的操作。

```cpp
Array elementwiseOperation(Array& arr, Operation optn);
```
根据提供的操作类型，对两个具有相同形状的矩阵进行逐元素操作，返回结果矩阵。

```cpp
template <typename T1, typename T2> bool isTypeSame(T1, T2);
```
比较两个不同类型的参数是否不同。

```cpp
template <typename T> bool isTypeSame(T, T);
```
比较两个不同类型的参数是否相同。

```cpp
template <typename T> void checkType(bool is_index, const T& arg);
```
检查给定参数的类型是否与预期相符，同时检查参数是否满足特定条件。

```cpp
template <typename T, typename... Args> void checkTypes(bool is_index, const T& arg, const Args&... args);
```
递归检查一系列参数的类型是否匹配。

#### 公有成员函数

```cpp
void set(int value);
```
设置数组中当前索引位置的值为指定值。

```cpp
int* get_content(void);
```
返回数组内部数据的指针。

```cpp
template <typename... Args> Array& at(Args... args);
```
设置数组中指定索引位置的值，并返回数组本身。

```cpp
template <typename... Args> void reshape(Args... args);
```
重新定义数组的维度，将其重新塑造为指定大小。

#### 运算符重载

```cpp
Array operator[](int n);
```
重载 `[]` 运算符，用于访问数组中的元素。

```cpp
Array& operator=(int value);
```
重载 `=` 运算符，用于将指定值赋给数组中的元素。

```cpp
Array operator+(Array& arr);
```
重载 `+` 运算符，执行数组元素之间的逐元素相加操作。

```cpp
Array operator-(void);
```
重载一元 `-` 运算符，执行数组元素的逐元素取反操作。

```cpp
Array operator-(Array& arr);
```
重载 `-` 运算符，执行数组元素之间的逐元素相减操作。

```cpp
Array operator*(Array& arr);
```
重载 `*` 运算符，执行数组元素之间的逐元素相乘操作。

```cpp
Array operator/(Array& arr);
```
重载 `/` 运算符，执行数组元素之间的逐元素相除操作。

```cpp
operator int(void);
```
将数组当前索引位置的值转换为 `int` 类型。

#### 友元函数

```cpp
friend ostream& operator<<(ostream& out, const Array& arr);
```
重载流输出运算符 `<<`，用于将数组打印到输出流。

```cpp
friend istream& operator>>(istream& in, Array& arr);
```
重载流插入运算符 `>>`，用于从输入流中读取数据并填充数组。

```cpp
friend Array elementwiseOperation(Array& arr, int n, Operation optn);
```
根据提供的操作类型，对两个具有相同形状的矩阵进行逐元素操作，返回结果矩阵。

```cpp
friend Array operator*(Array& arr, int n);
```
重载 `*` 运算符，执行数组元素与标量之间的逐元素相乘操作。

```cpp
friend Array operator*(int n, Array& arr);
```
重载 `*` 运算符，执行标量与数组元素之间的逐元素相乘操作。

```cpp
friend Array operator/(Array& arr, int n);
```
重载 `/` 运算符，执行数组元素与标量之间的逐元素相除操作。

```cpp
friend Array operator/(int n, Array& arr);
```
重载 `/` 运算符，执行标量与数组元素之间的逐元素相除操作。

```cpp
friend void input(Array& arr, char name);
```
允许外部代码访问 `Array` 类的私有数据成员，允许外部代码对传入的 `Array` 对象进行输入操作。

### 图像文件和视频文件每一帧的读取

#### 图像文件的读取

```cpp
PicReader imread;
BYTE* data = nullptr;
UINT x, y;
imread.readPic(path);
imread.getData(data, x, y);
...
delete[] data;
```

从位图复制的数据，每4个为一组代表一个像素，数据为一个长度为图像的（宽度×高度×4通道）的一维数组，数据排布为 `R G B A R G B A R G B A ...` 由于 `getData` 函数是使用在函数内动态申请的内存实现的，所以每次都需要释放内存。

#### 视频文件每一帧的读取

```cpp
VideoCapture cap(path);
if (!cap.isOpened())
    exit(-1);
Mat frame;
int frameNumber = 0;
while (true) {
    cap >> frame;
    if (frame.empty())
        break;
    snprintf(path, sizeof(path), "videos/frame_%d.jpg", frameNumber);
    imwrite(path, frame);
    cout << ">>> Saved frame" << setw(5) << ++frameNumber << " as " << &path[7] << endl;
}
int x = int(cap.get(CAP_PROP_FRAME_WIDTH));
int y = int(cap.get(CAP_PROP_FRAME_HEIGHT));
double frameRate = cap.get(cv::CAP_PROP_FPS);
cap.release();
```

### 以二进制方式读写数组数据的实现

#### 将数组数据以二进制方式保存到文件的实现

```cpp
template <typename T>
static void saveArrayToFile(const char* filename, T* array, size_t size)
{
    FILE* file = fopen(filename, "wb");
    if (file == NULL)
        exit(-1);
    fwrite(array, sizeof(T), size, file);
    fclose(file);
}
```

#### 从文件中以二进制方式读取数组数据的实现

```cpp
template <typename T>
static void readArrayFromFile(const char* filename, T* array, size_t size)
{
    FILE* file = fopen(filename, "rb");
    if (file == NULL)
        exit(-1);
    fread(array, sizeof(T), size, file);
    fclose(file);
}
```

### 降采样操作的实现

#### 降采样操作的方法

* 平均池化（Average Pooling）：在这种方法中，将图像分割成不重叠的块，然后计算每个块内像素的平均值，用这个平均值代替整个块的像素，这样就减少了图像中的像素数量。

* 最大池化（Max Pooling）：类似于平均池化，但是将块内的像素值替换为块内像素的最大值，而不是平均值。

* 子采样（Subsampling）：这是一种经典的降采样方法，它通过跳过一些像素来减少图像的分辨率，通过每隔一定数量的像素采样一个像素，从而降低图像的分辨率。

本程序使用平均池化方法进行降采样操作。

#### 降采样因子的计算

```cpp
reductionFactor = (max(x, y) - 1) / consoleWindowsSize + 1;
```

#### 降采样操作的过程

```cpp
for (int i = 0; i < y; i++)
    for (int j = 0; j < x; j++) {
        int start_x = j * reductionFactor, start_y = i * reductionFactor, end_x = start_x + reductionFactor, end_y = start_y + reductionFactor;
        int sum[4] = { 0 };
        for (int m = start_y; m < end_y; m++)
            for (int n = start_x; n < end_x; n++)
                for (int k = 0; k < 4; k++)
                    sum[k] += originalImage[m][n][k];
        for (int k = 0; k < 4; k++)
            reductionImage.get_content()[(i * x + j) * 4 + k] = int(sum[k] / double(reductionFactor * reductionFactor) + 0.5);
    }
```

### 灰度值到ASCII字符的映射的实现

#### 灰度值的计算

```cpp
grayscale = ((306 * R + 601 * G + 116 * B) >> 10);
```

整数运算速度快于浮点数运算，移位运算速度快于整数运算。

#### 灰度值到ASCII字符的映射

```cpp
const char asciiStrength[] = { '@','M','N','H','Q','$','O','C','?','7','1','>','!',':','-','.' };
for (int i = 0; i < total; i++)
    dataBuffer[i] = asciiStrength[int(grayscale[i] / 16.0 + 0.5)];
```

### 图像的查看

```cpp
FastPrinter printer(width, height, fontSize);
printer.cleanSrceen();
printer.setData(dataBuffer, frontColorBuffer, backColorBuffer);
printer.draw(true);
```

### 连续帧的播放

```cpp
/* Play video */
int nowFrame = 0;
QueryPerformanceFrequency(&tick);
FastPrinter printer(width, height, fontSize);
printer.cleanSrceen();
QueryPerformanceCounter(&begin);
while (true) {
    /* Calculate frame */
    QueryPerformanceCounter(&end);
    nowFrame = int((end.QuadPart - begin.QuadPart) * frameRate / tick.QuadPart);

    /* Read array from file */
    snprintf(path, sizeof(path), "videos/frame_%d_dataBuffer.dat", nowFrame);
    readArrayFromFile(path, dataBuffer, total * 2);
    snprintf(path, sizeof(path), "videos/frame_%d_frontColorBuffer.dat", nowFrame);
    readArrayFromFile(path, frontColorBuffer, total * 6);
    snprintf(path, sizeof(path), "videos/frame_%d_backColorBuffer.dat", nowFrame);
    readArrayFromFile(path, backColorBuffer, total * 6);

    /* Draw image */
    printer.setData(dataBuffer, frontColorBuffer, backColorBuffer);
    printer.draw(true);
    
    /* Check if video ends */
    if (nowFrame == frameNumber - 1)
        break;
}
```

### 背景音乐的播放

```cpp
#pragma comment(lib, "winmm.lib")
PlaySoundA(filename, NULL, SND_FILENAME | SND_ASYNC);
```

## 集成开发环境

* Microsoft Visual Studio

## 编译运行环境

* 本项目仅适用于x64架构

* Windows控制台主机的新版控制台运行（取消选项“快速编辑模式”和“插入模式”）

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

## 相关资料

* [OpenCV Documentation](https://docs.opencv.org)

## 文档更新日期

2023年9月25日