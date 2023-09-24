# Love Code

## 项目名称

Love_Code

## 项目实现功能

爱心代码

## 项目文件组成

### 头文件

* `cmd_console_tools.h`
伪图形界面函数工具集的头文件

* `lovecode.h`
主体函数、工具函数的头文件

* `pixel_matrixs.h`
存放点阵信息的头文件

### 源文件

* `cmd_console_tools.cpp`
伪图形界面函数工具集的实现

* `lovecode_classes.cpp`
类的成员函数的体外实现

* `lovecode_main.cpp`
主体函数的实现

* `lovecode_tools.cpp`
工具函数的实现

## 项目技术细节

### `point_set` 类的实现

#### 概述

`point_set` 类是用于管理一组点并提供功能来初始化和显示心形图案。

#### 类定义

```cpp
class point_set {
private:
    struct point points[MAXIMUN_OF_POINTS];
    int number_of_points;
public:
    void point_initialize(int precision, double factor, int fullfit_or_not = 0);
    void print_heart(int bg_color, int fg_color);
};
```

#### 私有数据成员

```cpp
struct point points[MAXIMUN_OF_POINTS]; // 点的位置信息
```

```cpp
int number_of_points; // 点的数量信息
```

#### 公有成员函数

```cpp
void point_initialize(int precision, double factor, int fullfit_or_not = 0);
```
根据给定的参数初始化点集。

```cpp
void print_heart(int bg_color, int fg_color);
```
根据初始化的点集，将心形图案渲染到控制台中。

### `pixel_characters` 类的实现

#### 概述

`pixel_characters` 类负责处理基于像素的字符渲染和显示。

#### 类定义

```cpp
class pixel_characters {
private:
    int pixel_matrix[16][16];
public:
    pixel_characters(const int character[][16]);
    void print_character(int x, int y, int bg_color, int fg_color);
};
```

#### 私有数据成员

```cpp
int pixel_matrix[16][16]; // 基于像素的字符渲染和显示矩阵
```

#### 构造函数

```cpp
pixel_characters(const int character[][16]);
```
初始化像素矩阵，将字符图案表示为像素值的集合。

#### 公有成员函数

```cpp
void print_character(int x, int y, int bg_color, int fg_color);
```
指定位置和颜色，在控制台中绘制像素矩阵表示的字符图案。

### `pixel_ASCIIs` 类的实现

#### 概述

`pixel_ASCIIs` 类用于处理基于像素的ASCII字符渲染和显示。

#### 类定义

```cpp
class pixel_ASCIIs {
private:
    int pixel_matrix[95][16][8];
public:
    pixel_ASCIIs(const int ASCII[][16][8]);
    void print_ASCII(int x, int y, int ASCII, int bg_color, int fg_color);
};
```

#### 私有数据成员

```cpp
int pixel_matrix[95][16][8]; // 基于像素的ASCII字符渲染和显示矩阵
```

#### 构造函数

```cpp
pixel_characters(const int character[][16]);
```
初始化像素矩阵，将ASCII字符图案表示为像素矩阵的集合。

#### 公有成员函数

```cpp
void print_character(int x, int y, int bg_color, int fg_color);
```
指定位置和颜色，在控制台中绘制像素矩阵表示的ASCII字符图案。

## 集成开发环境

* Microsoft Visual Studio

## 编译运行环境

* 本项目仅适用于x86架构

* Windows控制台主机的旧版控制台运行（取消选项“快速编辑模式”和“插入模式”）

## 文档更新日期

2023年9月25日