/****************************************************************
 * Project Name:  Color_Linez
 * File Name:     color_linez.h
 * File Function: 主体函数、工具函数的头文件
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/11/21
 ****************************************************************/

#pragma once
#ifndef COLOR_LINEZ_H
#define COLOR_LINEZ_H

/* Macro definition */
#define BOUNDARY 8

/* Define constant variables */
const int row = 9;
const int col = 9;
const BLOCK_DISPLAY_INFO bdi[] = {
    {BDI_VALUE_BLANK, -1, -1, NULL},
    {1, -1, COLOR_HRED, "●"},
    {2, -1, COLOR_YELLOW, "●"},
    {3, -1, COLOR_HGREEN, "●"},
    {4, -1, COLOR_HCYAN, "●"},
    {5, -1, COLOR_CYAN, "●"},
    {6, -1, COLOR_BLUE, "●"},
    {7, -1, COLOR_HPINK, "●"},
    {10, -1, COLOR_HRED, "◎"},
    {20, -1, COLOR_YELLOW, "◎"},
    {30, -1, COLOR_HGREEN, "◎"},
    {40, -1, COLOR_HCYAN, "◎"},
    {50, -1, COLOR_CYAN, "◎"},
    {60, -1, COLOR_BLUE, "◎"},
    {70, -1, COLOR_HPINK, "◎"},
    {100, -1, COLOR_HRED, "〇"},
    {200, -1, COLOR_YELLOW, "〇"},
    {300, -1, COLOR_HGREEN, "〇"},
    {400, -1, COLOR_HCYAN, "〇"},
    {500, -1, COLOR_CYAN, "〇"},
    {600, -1, COLOR_BLUE, "〇"},
    {700, -1, COLOR_HPINK, "〇"},
    {BDI_VALUE_END, -1, -1, NULL}
};

/* Define structure types */
struct point {
    int x;
    int y;
};

struct statistic {
    int number = 0;
    int deleted = 0;
    double proportion = 0;
};

/* Define GAME class */
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

/* Define queue class */
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

/* Function declarations in color_linez_tools.cpp */
void initialize_CGI(CONSOLE_GRAPHICS_INFO* pCGI);
void print_statistic_chart(void);
int BFS(int grid[][col], int startRow, int startCol, int targetRow, int targetCol, struct point path[]);
void print_moving_path(CONSOLE_GRAPHICS_INFO* pCGI, struct point path[], int startRow, int startCol, int value);

#endif // !COLOR_LINEZ_H