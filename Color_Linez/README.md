# Color Linez

## 项目名称

Color_Linez

## 项目实现功能

彩球游戏

## 项目文件组成

### 头文件

* `cmd_console_tools.h`
伪图形界面函数工具集的头文件

* `color_linez.h`
主体函数、工具函数的头文件

* `lib_gmw_tools.h`
消除类游戏通用函数工具集的头文件

### 源文件

* `cmd_console_tools.cpp`
伪图形界面函数工具集的实现

* `color_linez_classes.cpp`
类的成员函数的体外实现

* `color_linez_main.cpp`
主体函数的实现

* `color_linez_tools.cpp`
工具函数的实现

* `lib_gmw_tools.cpp`
消除类游戏通用函数工具集的实现

### 资源文件

* `lib_gmw_tools.lib`
消除类游戏通用函数工具集的静态链接库

## 项目技术细节

### `GAME` 类的实现

#### 概述

`GAME` 类是一个用于实现彩球游戏的C++类。该类管理游戏的核心逻辑，包括生成游戏棋盘、计算消除、更新统计数据等功能。

#### 类定义

```cpp
class GAME {
private:
    int matrix[row + 2][col + 2] = { 0 };
    int score = 0;
    int next_generate[3] = { 0 };
    struct statistic data[7];
public:
    GAME();
    void generate(CONSOLE_GRAPHICS_INFO* pCGI, int n, bool initialize = false);
    bool is_empty(int r, int c);
    int get_value(int r, int c);
    void set_value(int r, int c, int value);
    void calculate(void);
    void print_statistic(void);
    bool is_eliminate(int eliminate_matrix[][col + 2], int targetRow, int targetCol);
    void statistic_deleted_plus(int n);
    void print_score(void);
    int get_blank(void);
};
```

#### 私有数据成员

```cpp
int matrix[row + 2][col + 2] = { 0 }; // 游戏矩阵的二维数组
```

```cpp
int score = 0; // 游戏得分
```

```cpp
int next_generate[3] = { 0 }; // 下一轮生成的球的种类
```

```cpp
struct statistic data[7]; // 不同球的统计数据
```

#### 构造函数

```cpp
GAME();
```
初始化游戏棋盘，并将边界标记为 `BOUNDARY`。

#### 公有成员函数

```cpp
void generate(CONSOLE_GRAPHICS_INFO* pCGI, int n, bool initialize = false);
```
生成指定数量的随机球。

```cpp
bool is_empty(int r, int c);
```
判断指定位置是否为空。

```cpp
int get_value(int r, int c);
```
获取指定位置上球的值。

```cpp
void set_value(int r, int c, int value);
```
设置指定位置上球的值。

```cpp
void calculate(void);
```
统计各个球值的数量和比例。

```cpp
void print_statistic(void);
```
打印统计信息表格，包括球的数量、比例和被消除数量。

```cpp
bool is_eliminate(int eliminate_matrix[][col + 2], int targetRow, int targetCol);
```
判断指定位置的球是否可以被消除。

```cpp
void statistic_deleted_plus(int n);
```
更新特定球的被消除数量。

```cpp
void print_score(void);
```
打印游戏得分，并根据消除情况增加分数。

```cpp
int get_blank(void);
```
统计空白位置的数量。

### 游戏主体架构

```cpp
while (1) {
    /* Initialize GAME and CONSOLE_GRAPHICS_INFO class */
    class GAME game;
    CONSOLE_GRAPHICS_INFO CGI;

    /* Initialize graphical interface */
    initialize_CGI(&CGI);
    game.generate(&CGI, 5, true);
    game.calculate();
    game.print_statistic();

    /* Set loop flag */
    bool loop_flag = true;

    /* Define starting row and column and target row and column */
    int startRow, startCol, targetRow, targetCol;

    /* Perform one operation */
    while (1) {
        /* Determine if the game is over */
        if (!game.get_blank()) {
            cct_showstr(2, 5 + row * 2, "游戏结束! 按回车键重新开始游戏", COLOR_BLACK, COLOR_HYELLOW);
            cout << setw(42) << " ";
            while (1) {
                char optn = _getch();
                if (optn == 0 || optn == -32)
                    optn = _getch();
                else if (optn == '\r')
                    break;
            }
            break;
        }

        /* Set break flag */
        bool loop_break = false;

        /* Select the starting point */
        while (loop_flag) {
            /* Read keyboard and mouse events */
            int MAction, MRow, MCol, KeyCode1 = 0, KeyCode2 = 0;
            gmw_read_keyboard_and_mouse(&CGI, MAction, MRow, MCol, KeyCode1, KeyCode2);

            /* Determine whether to restart the game or exit */
            if (KeyCode1 == 'Q' || KeyCode1 == 'q')
                return 0;
            else if (KeyCode1 == 'R' || KeyCode1 == 'r') {
                loop_break = true;
                break;
            }

            /* Print the selected ball */
            if ((MAction == MOUSE_LEFT_BUTTON_CLICK || MAction == MOUSE_LEFT_BUTTON_DOUBLE_CLICK) && !game.is_empty(MRow, MCol)) {
                startRow = MRow;
                startCol = MCol;
                gmw_draw_block(&CGI, startRow, startCol, 10 * game.get_value(startRow, startCol), bdi);
                break;
            }
        }

        /* Determine whether to restart the game */
        if (loop_break)
            break;

        /* Select the target point */
        while (1) {
            /* Read keyboard and mouse events */
            int MAction, MRow, MCol, KeyCode1 = 0, KeyCode2 = 0;
            gmw_read_keyboard_and_mouse(&CGI, MAction, MRow, MCol, KeyCode1, KeyCode2);

            /* Determine whether to restart the game or exit */
            if (KeyCode1 == 'Q' || KeyCode1 == 'q')
                return 0;
            else if (KeyCode1 == 'R' || KeyCode1 == 'r') {
                loop_break = true;
                break;
            }

            /* Print the selected ball or print the movement process */
            if ((MAction == MOUSE_LEFT_BUTTON_CLICK || MAction == MOUSE_LEFT_BUTTON_DOUBLE_CLICK)) {
                /* Check if the selected point is empty */
                if (game.is_empty(MRow, MCol)) {
                    /* Save the target row and column */
                    targetRow = MRow;
                    targetCol = MCol;

                    /* Initialize path */
                    struct point path[row * col];
                    for (int i = 0; i < row * col; i++) {
                        path[i].x = -1;
                        path[i].y = -1;
                    }

                    /* Initialize BFS_matrix */
                    int BFS_matrix[row][col];
                    for (int i = 0; i < row; i++)
                        for (int j = 0; j < col; j++)
                            BFS_matrix[i][j] = (game.get_value(i, j) > 0 ? 1 : 0);

                    /* Save the value of the selected ball */
                    int selectd_value = game.get_value(startRow, startCol);
                    game.set_value(startRow, startCol, 0);

                    /* Breadth-First Search */
                    if (BFS(BFS_matrix, startRow, startCol, targetRow, targetCol, path) == -1) {
                        /* Set the value of the starting ball */
                        game.set_value(startRow, startCol, selectd_value);

                        /* Set loop flag */
                        loop_flag = false;
                    }
                    else {
                        /* Print moving path */
                        print_moving_path(&CGI, path, startRow, startCol, selectd_value);

                        /* Set the value of the target ball */
                        game.set_value(targetRow, targetCol, selectd_value);

                        /* Eliminate lines of five or more balls */
                        int eliminate_matrix[row + 2][col + 2] = { 0 };
                        if (game.is_eliminate(eliminate_matrix, targetRow, targetCol)) {
                            /* Print the blinking effect of elimination */
                            for (int d = 0; d < 7; d++) {
                                Sleep(100);
                                for (int i = 1; i <= row; i++)
                                    for (int j = 1; j <= col; j++)
                                        if (eliminate_matrix[i][j])
                                            gmw_draw_block(&CGI, i - 1, j - 1, (d == 6 ? 0 : (d % 2 ? 1 : 100)) * game.get_value(i - 1, j - 1), bdi);
                            }

                            /* Update statistic */
                            for (int i = 1; i <= row; i++)
                                for (int j = 1; j <= col; j++)
                                    if (eliminate_matrix[i][j]) {
                                        game.statistic_deleted_plus(game.get_value(i - 1, j - 1) - 1);
                                        game.set_value(i - 1, j - 1, 0);
                                        game.print_score();
                                    }
                        }

                        /* Generate the balls for the next round */
                        game.generate(&CGI, game.get_blank() > 3 ? 3 : game.get_blank());

                        /* Set loop flag */
                        loop_flag = true;
                    }
                }
                else {
                    /* Print the selected ball */
                    gmw_draw_block(&CGI, startRow, startCol, game.get_value(startRow, startCol), bdi);
                    startRow = MRow;
                    startCol = MCol;
                    gmw_draw_block(&CGI, startRow, startCol, 10 * game.get_value(startRow, startCol), bdi);

                    /* Set loop flag */
                    loop_flag = false;
                }

                /* Break the loop */
                break;
            }
        }

        /* Determine whether to restart the game */
        if (loop_break)
            break;

        /* Calculate and print statistic */
        game.calculate();
        game.print_statistic();
    }
}
```

### 广度优先搜索算法

```cpp
struct point {
    int x;
    int y;
};

class queue {
private:
    struct point data[row * col];
    int front = 0;
    int rear = 0;
public:
    bool empty(void);
    void push(point p);
    struct point pop(void);
};

int BFS(int grid[][col], int startRow, int startCol, int targetRow, int targetCol, struct point path[])
{
    /* Define offsets for four directions to traverse adjacent nodes */
    int dx[] = { 0, 0, 1, -1 };
    int dy[] = { 1, -1, 0, 0 };

    /* Define a queue to store nodes to be explored */
    queue q;

    /* Define a 2D array to record visited nodes */
    bool visited[row][col] = { false };

    /* Define a 2D array to record the predecessor node for backtracking the path */
    point pre[row][col] = { {0, 0} };

    /* Enqueue the starting node and mark it as visited */
    q.push({ startRow, startCol });
    visited[startRow][startCol] = true;

    /* Start Breadth-First Search */
    while (!q.empty()) {
        /* If the current node is the target node, backtrack to record the path */
        point curr = q.pop();
        if (curr.x == targetRow && curr.y == targetCol) {
            int steps = 0;
            while (curr.x != startRow || curr.y != startCol) {
                path[row * col - 1 - steps].x = curr.x;
                path[row * col - 1 - steps].y = curr.y;
                steps++;
                curr = pre[curr.x][curr.y];
            }
            path[row * col - 1 - steps].x = startRow;
            path[row * col - 1 - steps].y = startCol;
            return steps;
        }

        /* Traverse adjacent nodes in four directions */
        for (int i = 0; i < 4; i++) {
            /* Check if the adjacent node is valid, unvisited, and not an obstacle (assuming obstacles are represented by 1) */
            int nextX = curr.x + dx[i];
            int nextY = curr.y + dy[i];
            bool is_valid = (nextX >= 0 && nextX < row && nextY >= 0 && nextY < col);
            if (is_valid && !visited[nextX][nextY] && grid[nextX][nextY] != 1) {
                /* Enqueue the adjacent node and mark it as visited */
                q.push({ nextX, nextY });
                visited[nextX][nextY] = true;

                /* Record the predecessor node for backtracking the path */
                pre[nextX][nextY] = curr;
            }
        }
    }

    /* If the path is not found, return -1 to indicate that the target point is unreachable */
    return -1;
}
```

## 集成开发环境

* Microsoft Visual Studio

## 编译运行环境

* 本项目仅适用于x86架构

* Windows控制台主机的旧版控制台运行（取消选项“快速编辑模式”和“插入模式”）

## 文档更新日期

2023年9月30日