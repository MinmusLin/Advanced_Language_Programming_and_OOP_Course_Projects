# 2048 Game

## 项目名称

2048_Game

## 项目实现功能

2048游戏

## 项目文件组成

### 头文件

* `2048_game.h`
主体函数、工具函数的头文件

* `cmd_console_tools.h`
伪图形界面函数工具集的头文件

* `lib_gmw_tools.h`
消除类游戏通用函数工具集的头文件

### 源文件

* `2048_game_classes.cpp`
类的成员函数的体外实现

* `2048_game_main.cpp`
主体函数的实现

* `2048_game_tools.cpp`
工具函数的实现

* `cmd_console_tools.cpp`
伪图形界面函数工具集的实现

* `lib_gmw_tools.cpp`
消除类游戏通用函数工具集的实现

### 资源文件

* `lib_gmw_tools.lib`
消除类游戏通用函数工具集的静态链接库

## 项目技术细节

### `GAME` 类的实现

#### 概述

`GAME` 类是一个用于实现2048游戏的C++类。该类通过管理游戏矩阵、移动操作、生成新方块以及计分等功能，实现了经典的2048游戏。

#### 类定义

```cpp
class GAME {
private:
    int matrix[10][10] = { 0 };
    int score = 0;
    int row;
    int col;
public:
    GAME(int r, int c);
    void generate(CONSOLE_GRAPHICS_INFO* pCGI);
    void move_down_to_up(CONSOLE_GRAPHICS_INFO* pCGI);
    void move_up_to_down(CONSOLE_GRAPHICS_INFO* pCGI);
    void move_right_to_left(CONSOLE_GRAPHICS_INFO* pCGI);
    void move_left_to_right(CONSOLE_GRAPHICS_INFO* pCGI);
    int gameover_judgment(void);
    int calculate_score(int num);
    int get_score(void);
};
```

#### 私有数据成员

```cpp
int matrix[10][10] = { 0 }; // 游戏矩阵的二维数组
```

```cpp
int score = 0; // 游戏得分
```

```cpp
int row; // 游戏矩阵的行数
```

```cpp
int col; // 游戏矩阵的列数
```

#### 构造函数

```cpp
GAME(int r, int c);
```
创建一个新的 `GAME` 对象，并初始化游戏矩阵。传入参数 `r` 和 `c` 分别表示游戏矩阵的行数和列数。在初始化过程中，会设置边界以及初始化矩阵内部。

#### 公有成员函数

```cpp
void generate(CONSOLE_GRAPHICS_INFO* pCGI);
```
在游戏矩阵中随机生成一个新的方块。

```cpp
void move_down_to_up(CONSOLE_GRAPHICS_INFO* pCGI);
```
将游戏矩阵中的方块从下往上进行合并和移动操作。

```cpp
void move_up_to_down(CONSOLE_GRAPHICS_INFO* pCGI);
```
将游戏矩阵中的方块从上往下进行合并和移动操作。

```cpp
void move_right_to_left(CONSOLE_GRAPHICS_INFO* pCGI);
```
将游戏矩阵中的方块从右往左进行合并和移动操作。

```cpp
void move_left_to_right(CONSOLE_GRAPHICS_INFO* pCGI);
```
将游戏矩阵中的方块从左往右进行合并和移动操作。

```cpp
int gameover_judgment(void);
```
判断游戏是否结束。

```cpp
int calculate_score(int num);
```
根据合并后的方块值计算得分。

```cpp
int get_score(void);
```
获取当前游戏得分。

### 游戏主体架构

```cpp
while (1) {
    /* Initialize GAME and CONSOLE_GRAPHICS_INFO class */
    int row, col;
    menu(row, col);
    class GAME game = { row, col };
    CONSOLE_GRAPHICS_INFO CGI;
    initialize_CGI(&CGI, row, col);

    /* Randomly generate initial color blocks */
    game.generate(&CGI);
    game.generate(&CGI);

    /* Read keyboard and mouse events */
    while (1) {
        /* Determine if the game is over */
        if (print_prompt(game.get_score(), game.gameover_judgment()))
            break;

        /* Read keyboard and mouse events */
        int MAction, MRow, MCol, KeyCode1 = 0, KeyCode2 = 0;
        gmw_read_keyboard_and_mouse(&CGI, MAction, MRow, MCol, KeyCode1, KeyCode2, false);

        /* Determine whether to quit the game */
        if (KeyCode1 == 27)
            break;

        /* Move coordinates using keyboard arrow keys */
        if (KeyCode1 == 224 && (KeyCode2 == KB_ARROW_UP || KeyCode2 == KB_ARROW_DOWN || KeyCode2 == KB_ARROW_LEFT || KeyCode2 == KB_ARROW_RIGHT)) {
            switch (KeyCode2) {
                case KB_ARROW_UP:
                    game.move_down_to_up(&CGI);
                    break;
                case KB_ARROW_DOWN:
                    game.move_up_to_down(&CGI);
                    break;
                case KB_ARROW_LEFT:
                    game.move_right_to_left(&CGI);
                    break;
                case KB_ARROW_RIGHT:
                    game.move_left_to_right(&CGI);
                    break;
                default:
                    break;
            }
            cct_showint(26, 0, game.get_score());
            if (game.gameover_judgment() == 2)
                game.generate(&CGI);
        }
    }
}
```

## 集成开发环境

* Microsoft Visual Studio

## 编译运行环境

* 本项目仅适用于x86架构

* Windows控制台主机的旧版控制台运行（取消选项“快速编辑模式”和“插入模式”）

## 文档更新日期

2023年9月28日