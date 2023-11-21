# Conway Life Game

## 项目名称

Conway_Life_Game

## 项目实现功能

康威生命游戏

## 项目文件组成

### 头文件

* `conway.h`
`Conway` 类、图形化界面函数、主体函数的头文件

### 源文件

* `conway_graphics.cpp`
图形化界面函数的实现

* `conway_main.cpp`
主体函数的实现

## 项目技术细节

### `Conway` 类的实现

#### 概述

`Conway` 类是康威生命游戏的实现类，包含了保存细胞地图、计算存活细胞数以及刷新地图状态等功能。

#### 类定义

```cpp
class Conway {
private:
    bool** map;
    int countAlive(int row, int col);
public:
    Conway(int initAlive);
    ~Conway();
    void refreshMap(void);
};
```

#### 私有数据成员

```cpp
bool** map; // 细胞地图的首地址
```

#### 构造函数

```cpp
Conway(int initAlive);
```
分配内存空间、初始化细胞状态、生成初始存活细胞。

#### 析构函数

```cpp
~Conway();
```
释放内存。

#### 私有成员函数

```cpp
int countAlive(int row, int col);
```
计算给定位置周围的存活细胞数。

#### 公有成员函数

```cpp
void refreshMap(void);
```
刷新地图状态，进行下一步的细胞演变过程。

### 细胞演变过程的实现

```cpp
void refreshMap(void)
{
    for (int i = 0; i < gridRow; i++)
        for (int j = 0; j < gridCol; j++) {
            int n = countAlive(i, j);
            if (map[i][j]) {
                if (n < 2 || n > 3) {
                    map[i][j] = false;
                    print_grid_status(i, j, false);
                }
            }
            else {
                if (n == 3) {
                    map[i][j] = true;
                    print_grid_status(i, j, true);
                }
            }
        }
}
```

## 集成开发环境

* Microsoft Visual Studio 2022

## 编译运行环境

* 本项目适用于x86和x64架构

## 库依赖

* `EasyX`

  * ```cpp
    #include <graphics.h>
    ```

## 相关资料

* [EasyX Documentation](https://docs.easyx.cn)

* 康威生命游戏

  * 康威生命游戏是一种基于细胞自动机的零玩家游戏，由数学家约翰·康威在1970年创造，它模拟了细胞在一个离散的二维网格上的演变过程。

  * 规则和演进过程

    * 规则
    
      * 游戏开始时，二维网格上的每个格子称为一个细胞，可以是活的（有生命）或死的（无生命）。
      
      * 每个细胞有两种状态：活（true）或死（false）。当前时刻的每个细胞根据其周围八个细胞的状态来决定下一个时刻的状态。

    * 演进过程

      * 活细胞周围活细胞数量少于2个时，该细胞死亡（下一代为死细胞）。

      * 活细胞周围活细胞数量为2或3个时，该细胞存活到下一代。

      * 活细胞周围活细胞数量超过3个时，该细胞死亡（下一代为死细胞）。

      * 死细胞周围活细胞数量为3个时，该细胞变为活细胞。

  * 应用和特性

    * 康威生命游戏展示了简单规则下的复杂行为和结构的产生，具有计算机科学、生命科学、数学等领域的研究价值。

    * 它被用作研究复杂系统的模型，探讨自然界和人工生命的行为规律。

    * 生命游戏还可以用来创建有趣的艺术图案和模拟生命演变的动画。

## 文档更新日期

2023年11月21日