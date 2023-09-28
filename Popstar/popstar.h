/****************************************************************
 * Project Name:  Popstar
 * File Name:     popstar.h
 * File Function: 菜单函数、内部数组方式函数、伪图形界面方式函数、工具函数的头文件
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/9/28
 ****************************************************************/

#pragma once

/* Define print delay time */
#define SLEEP_TIME_FRAME 1
#define SLEEP_TIME_BLOCK 1

/* Define the number of colors */
#define BLOCK_NUMBER 5

/* Define the width and height of the color blocks */
#define BLOCK_WIDTH 6
#define BLOCK_HEIGHT 3

/* Define the range of rows and columns */
#define ROW_MIN 8
#define ROW_MAX 10
#define COLUMN_MIN 8
#define COLUMN_MAX 10

/* Define the parameters of the relevant functions */
#define WITHOUT_DIVIDER 0
#define WITH_DIVIDER 1
#define NON_GRAPHICAL_INTERFACE 0
#define GRAPHICAL_INTERFACE 1
#define NON_TRANSFORMATION 0
#define TRANSFORMATION 1
#define COORDINATE_UNLOCK 0
#define COORDINATE_LOCK 1
#define FULLVERSION 1
#define NON_FULLVERSION 0
#define END_GAME 0
#define CONTINUE_GAME 1
#define NON_ELIMINATION 0
#define ELIMINATION 1

/* Function declarations in popstar_base.cpp */
void base_mark(void);
void base_eliminate(void);
void base_level(void);
void print_array(int matrix[][10], int judgment_array[][12], int row, int column, int prompt);
int coordinate_input(int matrix[][10], int judgment_array[][12], int row, int column, int& dst_r, int& dst_c);
int eliminate_confirm(int dst_r, int dst_c);
void sameValue_elimination(int matrix[][10], int judgment_array[][12], int row, int column, int score_bound, int score_total);

/* Function declarations in popstar_console.cpp */
void console_select(int divider_or_not);
void console_eliminate(int divider_or_not);
void console_fullVersion(int divider_or_not);
void print_frame(int row, int column, int divider_or_not);
void print_block_initial(int matrix[][10], int row, int column, int divider_or_not, int width, int height);
void print_block(int matrix[][10], int i, int j, int divider_or_not, int color, int width, int height, int x, int y, int lock_or_not);
int mouse_and_keyboard_operations(int matrix[][10], int row, int column, int& X, int& Y, int& select_r, int& select_c, int divider_or_not, int eliminate_or_not);
void clear_information(int row, int column, int divider_or_not);
int judgment_legality(int matrix[][10], int row, int column, int X, int Y, int& select_r, int& select_c, int divider_or_not, int trans_or_not);
void print_current(int matrix[][10], int row, int column, int X, int Y, int select_r, int select_c, const char prompt[], int divider_or_not);
void synthesize_drop(int matrix[][10], int judgment_array[][12], int row, int column, int divider_or_not, int fullVersion_or_not);
void print_move_vertical(int matrix[][10], int src_r, int src_c, int len, int divider_or_not);
void print_move_horizontal(int matrix[][10], int src_r, int src_c, int len, int divider_or_not);
void move_coordinate_keyboard(int matrix[][10], int row, int column, int select_r, int select_c, int ret, int keycode1, int keycode2, int& X, int& Y, int divider_or_not);
void get_row_column(int row, int column, int X, int Y, int& select_r, int& select_c, int divider_or_not);
int print_selected_or_exit(int row, int column, int select_r, int select_c, int divider_or_not, int continue_or_not);
void graphical_initialize(int matrix[][10], int row, int column, int divider_or_not);
void judgment_synthesis(int matrix[][10], int judgment_array[][12], int row, int column, int select_r, int select_c, int divider_or_not);
void calculate_print_score(int matrix[][10], int judgment_array[][12], int row, int column, int select_r, int select_c, int& score_bound, int& score_total, int& num, int& loop1, int& loop2, int divider_or_not);
void print_nonReverse_current(int matrix[][10], int judgment_array[][12], int row, int column, int ret, int keycode1, int keycode2, int X, int Y, int& select_r, int& select_c, int _select_r, int _select_c, int& loop2, int divider_or_not, int trans_or_not);
int print_score_level(int matrix[][10], int row, int column, int& score_reward, int& score_total, int divider_or_not);

/* Function declarations in popstar_tools.cpp */
void parameters_input(int& row, int& column);
void matrix_initialize(int matrix[][10], int row, int column);
int judgment_continuity(int matrix[][10], int judgment_array[][12], int row, int column, int select_r, int select_c);
void flood_fill(int array[][12], int x, int y);
void wait_for_end(void);
void wait_for_enter(const char prompt[]);
int strcasecmp(const char s1[], const char s2[]);
void array_incorporate(int matrix[][10], int judgment_array[][12], int row, int column);
void array_translation(int matrix[][10], int row, int column, int graphical_or_not, int divider_or_not);
int array_judgment(int matrix[][10], int row, int column);