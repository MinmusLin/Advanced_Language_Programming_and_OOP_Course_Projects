/****************************************************************
 * Project Name:  2048_Game
 * File Name:     2048_game.h
 * File Function: 主体函数、工具函数的头文件
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/9/30
 ****************************************************************/

#pragma once

/* Macro definitions */
#define BOUNDARY 1
#define GAME_TARGET 2048

/* Define constant variable */
const BLOCK_DISPLAY_INFO bdi[] = {
    {BDI_VALUE_BLANK, -1, -1, NULL},
    {2, COLOR_HYELLOW, COLOR_BLACK, NULL},
    {4, COLOR_YELLOW, COLOR_BLACK, NULL},
    {8, COLOR_HCYAN, COLOR_BLACK, NULL},
    {16, COLOR_CYAN, COLOR_BLACK, NULL},
    {32, COLOR_HBLUE, COLOR_BLACK, NULL},
    {64, COLOR_BLUE, COLOR_BLACK, NULL},
    {128, COLOR_HGREEN, COLOR_BLACK, NULL},
    {256, COLOR_GREEN, COLOR_BLACK, NULL},
    {512, COLOR_HRED, COLOR_BLACK, NULL},
    {1024, COLOR_HPINK, COLOR_BLACK, NULL},
    {2048, COLOR_RED, COLOR_BLACK, NULL},
    {BDI_VALUE_END, -1, -1, NULL}
};

/* Define GAME class */
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

/* Function declarations in 2048_game_tools.cpp */
void menu(int& row, int& col);
int enter_digit(int x, int y, const char* prompt);
void initialize_CGI(CONSOLE_GRAPHICS_INFO* pCGI, int row, int col);
bool print_prompt(int score, int status);