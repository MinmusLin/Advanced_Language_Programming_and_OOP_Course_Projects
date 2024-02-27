# Tetris

## 项目名称

Tetris

## 项目实现功能

俄罗斯方块游戏

## 项目文件组成

### 头文件

* `tetris.h`
`Block` 类、 `Control` 类、游戏函数、图形化界面函数、主体函数的头文件

### 源文件

* `tetris_block.cpp`
`Block` 类的实现

* `tetris_control.cpp`
`Control` 类的实现

* `tetris_game.cpp`
游戏函数的实现

* `tetris_graphics.cpp`
图形化界面函数的实现

* `tetris_main.cpp`
主体函数的实现

### 资源文件

* `/data`
存放项目所需的资源文件

  * `game_rules.png`
  游戏规则与游戏方法

## 项目技术细节

### `Block` 类的实现

#### 概述

`Block` 类是俄罗斯方块游戏中方块的实现类，包含了方块的形状、颜色、种类和方向等属性，以及旋转和获取属性的方法。

#### 类定义

```cpp
class Block {
private:
    std::vector<std::vector<int>> block;
    COLORREF color;
    int category;
    int direction;
public:
    Block();
    const std::vector<std::vector<int>>& getBlock(void) const;
    const COLORREF getColor(void) const;
    const int getCategory(void) const;
    const int getDirection(void) const;
    void rotateClockwise(void);
    void rotateAnticlockwise(void);
};
```

#### 私有数据成员

```cpp
std::vector<std::vector<int>> block; // 方块的形状
```

```cpp
COLORREF color; // 方块的颜色
```

```cpp
int category; // 方块的种类
```

```cpp
int direction; // 方块的方向
```

#### 构造函数

```cpp
Block();
```
创建 `Block` 对象并初始化其属性，包括随机选择方块种类、方向和颜色，以及初始化方块形状。

#### 公有成员函数

```cpp
const std::vector<std::vector<int>>& getBlock(void) const;
```
获取方块的形状。

```cpp
const COLORREF getColor(void) const;
```
获取方块的颜色。

```cpp
const int getCategory(void) const;
```
获取方块的种类。

```cpp
const int getDirection(void) const;
```
获取方块的方向。

```cpp
void rotateClockwise(void);
```
将方块顺时针旋转。

```cpp
void rotateAnticlockwise(void);
```
将方块逆时针旋转。

### `Control` 类的实现

#### 概述

`Control` 类是俄罗斯方块游戏中游戏逻辑的实现类，包含了地图、得分、当前方块、保持方块、下一轮方块等属性，以及控制方块移动、旋转、消除行等方法。

#### 类定义

```cpp
class Control {
private:
    bool** map;
    int eliminatedLines = 0;
    int score = 0;
    int currentRow;
    int currentCol;
    COLORREF** color;
    Block current;
    Block hold;
    Block next[3];
public:
    Control();
    ~Control();
    const int& getScore(void) const;
    const int& getCurrentRow(void) const;
    const int& getCurrentCol(void) const;
    const Block& getCurrentBlock(void) const;
    void printHoldBlock(void);
    void printNextBlocks(void);
    void rotateCurrentClockwise(void);
    void rotateCurrentAnticlockwise(void);
    bool printBlock(int row, int col, bool is_blank = false);
    void refreshBlocks(void);
    void refreshBlock(int row, int col);
    void changeCurrentAndHold(void);
    bool eliminateLines(void);
    void refreshMap(void);
    void resetCurrentRowAndCol(void);
    void rotateRight(void);
    bool softDrop(void);
    void moveLeft(void);
    void moveRight(void);
    void changeHold(void);
    void rotateLeft(void);
    void hardDrop(void);
};
```

#### 私有数据成员

```cpp
bool** map; // 存储游戏地图中每个格子的占用状态
```

```cpp
int eliminatedLines = 0; // 消除行数
```

```cpp
int score = 0; // 游戏得分
```

```cpp
int currentRow; // 当前方块的行数
```

```cpp
int currentCol; // 当前方块的列数
```

```cpp
COLORREF** color; // 存储游戏地图中每个格子的颜色
```

```cpp
Block current; // 当前方块
```

```cpp
Block hold; // 保持方块
```

```cpp
Block next[3]; // 下一轮方块
```

#### 构造函数

```cpp
Control();
```
初始化 `Control` 对象，包括分配并初始化游戏地图、设置初始游戏状态、打印初始信息和方块等。

#### 析构函数

```cpp
~Control();
```
释放内存。

#### 公有成员函数

```cpp
const int& getScore(void) const;
```
获取游戏得分。

```cpp
const int& getCurrentRow(void) const;
```
获取当前方块的行数。

```cpp
const int& getCurrentCol(void) const;
```
获取当前方块的列数。

```cpp
const Block& getCurrentBlock(void) const;
```
获取当前方块。

```cpp
void printHoldBlock(void);
```
打印保持方块。

```cpp
void printNextBlocks(void);
```
打印下一轮方块。

```cpp
void rotateCurrentClockwise(void);
```
将当前方块顺时针旋转。

```cpp
void rotateCurrentAnticlockwise(void);
```
将当前方块逆时针旋转。

```cpp
bool printBlock(int row, int col, bool is_blank = false);
```
打印方块。

```cpp
void refreshBlocks(void);
```
刷新当前方块和下一轮方块。

```cpp
void refreshBlock(int row, int col);
```
刷新当前方块在游戏地图中每个格子的占用状态和颜色。

```cpp
void changeCurrentAndHold(void);
```
交换当前方块和保持方块。

```cpp
bool eliminateLines(void);
```
消除已满的行并更新得分。

```cpp
void refreshMap(void);
```
刷新游戏地图。

```cpp
void resetCurrentRowAndCol(void);
```
重置当前方块的位置。

```cpp
void rotateRight(void);
```
向右旋转当前方块。

```cpp
bool softDrop(void);
```
进行软下落。

```cpp
void moveLeft(void);
```
向左移动当前方块。

```cpp
void moveRight(void);
```
向右移动当前方块。

```cpp
void changeHold(void);
```
改变保持方块。

```cpp
void rotateLeft(void);
```
向左旋转当前方块。

```cpp
void hardDrop(void);
```
进行硬下落。

### 游戏主体架构

```cpp
bool tetris(void)
{
    Control control;
    while (true)
        if (_kbhit()) {
            int key = _getch();
            if (key != 0 && key != 0xE0 && key == '\r')
                break;
            else if (key != 0 && key != 0xE0 && key == KEYBOARD_ESC)
                return false;
        }
    DWORD startTime = GetTickCount();
    int count = 1;
    while (true) {
        if (count > 1) {
            control.refreshBlocks();
            control.printHoldBlock();
            control.printNextBlocks();
            count++;
        }
        if (control.eliminateLines())
            control.refreshMap();
        control.resetCurrentRowAndCol();
        if (!control.printBlock(control.getCurrentRow(), control.getCurrentCol())) {
            while (true)
                if (_kbhit()) {
                    int key = _getch();
                    if (key != 0 && key != 0xE0 && (key == 'R' || key == 'r'))
                        return true;
                    else if (key != 0 && key != 0xE0 && key == KEYBOARD_ESC)
                        return false;
                }
        }
        while (true) {
            if (_kbhit()) {
                int key = _getch();
                if (key == 0 || key == 0xE0) {
                    key = _getch();
                    if (key == 'H')
                        control.rotateRight();
                    else if (key == 'P') {
                        if (control.softDrop())
                            break;
                    }
                    else if (key == 'K')
                        control.moveLeft();
                    else if (key == 'M')
                        control.moveRight();
                }
                else {
                    if (key == 'W' || key == 'w')
                        control.rotateRight();
                    else if (key == 'S' || key == 's') {
                        if (control.softDrop())
                            break;
                    }
                    else if (key == 'A' || key == 'a')
                        control.moveLeft();
                    else if (key == 'D' || key == 'd')
                        control.moveRight();
                    else if (key == 'C' || key == 'c')
                        control.changeHold();
                    else if (key == 'Z' || key == 'z')
                        control.rotateLeft();
                    else if (key == ' ') {
                        control.hardDrop();
                        break;
                    }
                    else if (key == 'R' || key == 'r')
                        return true;
                    else if (key == KEYBOARD_ESC)
                        return false;
                }
            }
            if (static_cast<int>(GetTickCount() - startTime) >= delayTime * count) {
                count++;
                if (control.softDrop())
                    break;
            }
        }
    }
}
```

### 方块元素的实现

方块种类通过常变量 `blockCategory` 定义。意义为： `blockCategory[种类][方向][位置][行数/列数]` 。

```cpp
const std::vector<std::vector<std::vector<std::vector<int>>>> blockCategory = {
    { { {1,1},{1,2},{2,1},{2,2} }                                                                                     }, // "O" shape
    { { {0,1},{1,1},{2,1},{3,1} },{ {1,0},{1,1},{1,2},{1,3} }                                                         }, // "I" shape
    { { {1,1},{1,2},{2,0},{2,1} },{ {0,1},{1,1},{1,2},{2,2} }                                                         }, // "S" shape
    { { {1,0},{1,1},{2,1},{2,2} },{ {0,2},{1,1},{1,2},{2,1} }                                                         }, // "Z" shape
    { { {0,1},{1,1},{2,1},{2,2} },{ {1,1},{1,2},{1,3},{2,1} },{ {1,1},{1,2},{2,2},{3,2} },{ {1,2},{2,0},{2,1},{2,2} } }, // "L" shape
    { { {0,2},{1,2},{2,2},{2,1} },{ {1,1},{2,1},{2,2},{2,3} },{ {1,1},{1,2},{2,1},{3,1} },{ {1,0},{1,1},{1,2},{2,2} } }, // "J" shape
    { { {2,1},{2,0},{1,1},{2,2} },{ {1,1},{0,1},{2,1},{1,2} },{ {1,2},{1,1},{2,2},{1,3} },{ {2,2},{2,1},{1,2},{3,2} } }  // "T" shape
};
```

方块边界通过常变量 `blockLimits` 定义。意义为： `blockLimits[种类][方向][左上角顶点/右下角顶点][上边界/左边界/下边界/右边界]` 。

```cpp
const std::vector<std::vector<std::vector<std::vector<int>>>> blockLimits = {
    { { {1,1},{2,2} }                                                 }, // "O" shape
    { { {0,1},{3,1} },{ {1,0},{1,3} }                                 }, // "I" shape
    { { {1,0},{2,2} },{ {0,1},{2,2} }                                 }, // "S" shape
    { { {1,0},{2,2} },{ {0,1},{2,2} }                                 }, // "Z" shape
    { { {0,1},{2,2} },{ {1,1},{2,3} },{ {1,1},{3,2} },{ {1,0},{2,2} } }, // "L" shape
    { { {0,1},{2,2} },{ {1,1},{2,3} },{ {1,1},{3,2} },{ {1,0},{2,2} } }, // "J" shape
    { { {1,0},{2,2} },{ {0,1},{2,2} },{ {1,1},{2,3} },{ {1,1},{3,2} } }  // "T" shape
};
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

## 文档更新日期

2024年2月27日