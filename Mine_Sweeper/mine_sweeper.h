/****************************************************************
 * Project Name:  Mine_Sweeper
 * File Name:     mine_sweeper.h
 * File Function: 主体函数、菜单函数、工具函数的头文件
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/9/28
 ****************************************************************/

#pragma once

/* Macro definitions */
#define UNKNOWN 0
#define KNOWN 1
#define MARKED_MINE 2
#define MARKED_QUESTION 3

/* Define constant variable */
const BLOCK_DISPLAY_INFO bdi[] = {
    {BDI_VALUE_BLANK,COLOR_HYELLOW,COLOR_HYELLOW,NULL},
    {1,COLOR_HYELLOW,COLOR_CYAN,NULL},
    {2,COLOR_HYELLOW,COLOR_GREEN,NULL},
    {3,COLOR_HYELLOW,COLOR_YELLOW,NULL},
    {4,COLOR_HYELLOW,COLOR_RED,NULL},
    {5,COLOR_HYELLOW,COLOR_BLUE,NULL},
    {6,COLOR_HYELLOW,COLOR_PINK,NULL},
    {7,COLOR_HYELLOW,COLOR_HGREEN,NULL},
    {8,COLOR_HYELLOW,COLOR_HPINK,NULL},
    {'*',COLOR_HRED,COLOR_BLACK,"*"},
    {'#',COLOR_HGREEN,COLOR_BLACK,"#"},
    {'?',COLOR_HBLUE,COLOR_BLACK,"?"},
    {' ',COLOR_HBLACK,COLOR_BLACK," "},
    {BDI_VALUE_END,-1,-1,NULL}
};

/* Define structure types */
struct menu_content {
    const char no;
    const char mode_ch[10];
    const char mode_en[8];
    int row;
    int col;
    int mine;
    const int color;
};

struct unit {
    int value = 0;
    int status = UNKNOWN;
};

/* Function declarations in mine_sweeper_menu.cpp */
int menu(int& row, int& col, int& mine);
void print_option(struct menu_content menu_display[], int optn, int X, int Y, int bg_color = COLOR_BLACK);
int enter_digit(const char* prompt);
char read_option(void);

/* Function declarations in mine_sweeper_tools.cpp */
void initialize_CGI(CONSOLE_GRAPHICS_INFO* pCGI, int row, int col);
void draw_block(const CONSOLE_GRAPHICS_INFO* const pCGI, const int row_no, const int col_no, struct unit matrix[][34], const BLOCK_DISPLAY_INFO* const bdi); void initialize_matrix(struct unit matrix[][34], int row, int col, int mine);
void initialize_matrix(struct unit matrix[][34], int row, int col, int mine);
void flood_fill(const CONSOLE_GRAPHICS_INFO* const pCGI, const int row_no, const int col_no, struct unit matrix[][34], int array[][34], const BLOCK_DISPLAY_INFO* const bdi);
void print_continuity(const CONSOLE_GRAPHICS_INFO* const pCGI, const int row_no, const int col_no, struct unit matrix[][34], const BLOCK_DISPLAY_INFO* const bdi, int row, int col);
bool game_judgment(struct unit matrix[][34], int row, int col);
void print_prompt(time_t start_time, bool is_success);