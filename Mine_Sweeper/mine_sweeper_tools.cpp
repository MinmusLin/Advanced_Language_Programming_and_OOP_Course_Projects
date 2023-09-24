/****************************************************************
 * Project Name:  Mine_Sweeper
 * File Name:     mine_sweeper_tools.cpp
 * File Function: 工具函数的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/9/24
 ****************************************************************/

#include <iostream>
#include <iomanip>
#include "../common/cmd_console_tools.h"
#include "../common/lib_gmw_tools.h"
#include "mine_sweeper.h"
using namespace std;

/*
 * Function Name:    initialize_CGI
 * Function:         Initialize CONSOLE_GRAPHICS_INFO structure
 * Input Parameters: CONSOLE_GRAPHICS_INFO* pCGI
 *                   int row
 *                   int col
 * Return Value:     void
 */
void initialize_CGI(CONSOLE_GRAPHICS_INFO* pCGI, int row, int col)
{
    gmw_init(pCGI);
    gmw_set_rowcol(pCGI, row, col);
    gmw_set_font(pCGI, "新宋体");
    gmw_set_frame_style(pCGI, 4, 2);
    gmw_set_frame_color(pCGI, COLOR_HWHITE, COLOR_BLACK);
    gmw_set_rowno_switch(pCGI, true);
    gmw_set_colno_switch(pCGI, true);
    gmw_draw_frame(pCGI);
    gmw_status_line(pCGI, LOWER_STATUS_LINE, "[游戏方法:] 左键进行消除 右键进行标记 ESC键返回菜单");
    gmw_status_line(pCGI, TOP_STATUS_LINE, "", "剩余雷数: ");
}

/*
 * Function Name:    draw_block
 * Function:         draw a block
 * Input Parameters: const CONSOLE_GRAPHICS_INFO* const pCGI
 *                   const int row_no
 *                   const int col_no
 *                   struct unit matrix[][34]
 *                   const BLOCK_DISPLAY_INFO* const bdi
 * Return Value:     void
 */
void draw_block(const CONSOLE_GRAPHICS_INFO* const pCGI, const int row_no, const int col_no, struct unit matrix[][34], const BLOCK_DISPLAY_INFO* const bdi)
{
    if (matrix[row_no + 1][col_no + 1].status == UNKNOWN)
        gmw_draw_block(pCGI, row_no, col_no, ' ', bdi);
    else if (matrix[row_no + 1][col_no + 1].status == KNOWN)
        gmw_draw_block(pCGI, row_no, col_no, matrix[row_no + 1][col_no + 1].value, bdi);
    else if (matrix[row_no + 1][col_no + 1].status == MARKED_MINE)
        gmw_draw_block(pCGI, row_no, col_no, '#', bdi);
    else if (matrix[row_no + 1][col_no + 1].status == MARKED_QUESTION)
        gmw_draw_block(pCGI, row_no, col_no, '?', bdi);
    else
        return;
}

/*
 * Function Name:    initialize_matrix
 * Function:         Initialize matrix
 * Input Parameters: struct unit matrix[][34]
 *                   int row
 *                   int col
 *                   int mine
 * Return Value:     void
 */
void initialize_matrix(struct unit matrix[][34], int row, int col, int mine)
{
    /* Generate mines */
    for (int i = 0; i < mine; i++) {
        int r = rand() % row + 1, c = rand() % col + 1;
        if (matrix[r][c].value)
            i--;
        else
            matrix[r][c].value = '*';
    }

    /* Calculate the number of mines */
    for (int i = 1; i <= row; i++)
        for (int j = 1; j <= col; j++)
            if (matrix[i][j].value != '*')
                for (int m = -1; m <= 1; m++)
                    for (int n = -1; n <= 1; n++)
                        if (matrix[i + m][j + n].value == '*')
                            matrix[i][j].value++;

    /* Set the value of boundaries */
    for (int i = 0; i < row + 2; i++) {
        matrix[i][0].value = -1;
        matrix[i][col + 1].value = -1;
    }
    for (int i = 0; i < col + 2; i++) {
        matrix[0][i].value = -1;
        matrix[row + 1][i].value = -1;
    }
}

/*
 * Function Name:    flood_fill
 * Function:         Use the flood fill algorithm to find continuous blocks
 * Input Parameters: const CONSOLE_GRAPHICS_INFO* const pCGI
 *                   const int row_no
 *                   const int col_no
 *                   struct unit matrix[][34]
 *                   int array[][34]
 *                   const BLOCK_DISPLAY_INFO* const bdi
 * Return Value:     void
 */
void flood_fill(const CONSOLE_GRAPHICS_INFO* const pCGI, const int row_no, const int col_no, struct unit matrix[][34], int array[][34], const BLOCK_DISPLAY_INFO* const bdi)
{
    /* Mark the positions that have been traversed */
    array[row_no + 1][col_no + 1] = '!';

    /* Traverse in the four directions recursively */
    if (!array[row_no + 2][col_no + 1] && matrix[row_no + 2][col_no + 1].status == UNKNOWN)
        flood_fill(pCGI, row_no + 1, col_no, matrix, array, bdi);
    if (!array[row_no + 1][col_no + 2] && matrix[row_no + 1][col_no + 2].status == UNKNOWN)
        flood_fill(pCGI, row_no, col_no + 1, matrix, array, bdi);
    if (!array[row_no][col_no + 1] && matrix[row_no][col_no + 1].status == UNKNOWN)
        flood_fill(pCGI, row_no - 1, col_no, matrix, array, bdi);
    if (!array[row_no + 1][col_no] && matrix[row_no + 1][col_no].status == UNKNOWN)
        flood_fill(pCGI, row_no, col_no - 1, matrix, array, bdi);
}

/*
 * Function Name:    print_continuity
 * Function:         Draw continuous blocks
 * Input Parameters: const CONSOLE_GRAPHICS_INFO* const pCGI
 *                   const int row_no
 *                   const int col_no
 *                   struct unit matrix[][34]
 *                   const BLOCK_DISPLAY_INFO* const bdi
 *                   int row
 *                   int col
 * Return Value:     void
 */
void print_continuity(const CONSOLE_GRAPHICS_INFO* const pCGI, const int row_no, const int col_no, struct unit matrix[][34], const BLOCK_DISPLAY_INFO* const bdi, int row, int col)
{
    /* Initialize the array for traversal */
    int array[18][34] = { 0 };
    for (int i = 0; i < row + 2; i++)
        for (int j = 0; j < col + 2; j++)
            array[i][j] = matrix[i][j].value;

    /* Use the flood fill algorithm to find consecutive identical values in the array */
    flood_fill(pCGI, row_no, col_no, matrix, array, bdi);

    /* Draw continuous blocks */
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= col; j++) {
            if (array[i][j] == '!') {
                matrix[i][j].status = KNOWN;
                draw_block(pCGI, i - 1, j - 1, matrix, bdi);
                if (matrix[i + 1][j].value >= 1 && matrix[i][j].value <= 8 && matrix[i + 1][j].status == UNKNOWN) { //(1,0)
                    matrix[i + 1][j].status = KNOWN;
                    draw_block(pCGI, i, j - 1, matrix, bdi);
                }
                if (matrix[i][j + 1].value >= 1 && matrix[i][j].value <= 8 && matrix[i][j + 1].status == UNKNOWN) { //(0,1)
                    matrix[i][j + 1].status = KNOWN;
                    draw_block(pCGI, i - 1, j, matrix, bdi);
                }
                if (matrix[i - 1][j].value >= 1 && matrix[i][j].value <= 8 && matrix[i - 1][j].status == UNKNOWN) { //(-1,0)
                    matrix[i - 1][j].status = KNOWN;
                    draw_block(pCGI, i - 2, j - 1, matrix, bdi);
                }
                if (matrix[i][j - 1].value >= 1 && matrix[i][j].value <= 8 && matrix[i][j - 1].status == UNKNOWN) { //(0,-1)
                    matrix[i][j - 1].status = KNOWN;
                    draw_block(pCGI, i - 1, j - 2, matrix, bdi);
                }
                if (matrix[i - 1][j - 1].value >= 1 && matrix[i - 1][j - 1].value <= 8 && matrix[i - 1][j - 1].status == UNKNOWN && matrix[i][j - 1].status == KNOWN && matrix[i - 1][j].status == KNOWN) { //(-1,-1)
                    matrix[i - 1][j - 1].status = KNOWN;
                    draw_block(pCGI, i - 2, j - 2, matrix, bdi);
                }
                if (matrix[i - 1][j + 1].value >= 1 && matrix[i - 1][j + 1].value <= 8 && matrix[i - 1][j + 1].status == UNKNOWN && matrix[i][j + 1].status == KNOWN && matrix[i - 1][j].status == KNOWN) { //(-1,1)
                    matrix[i - 1][j + 1].status = KNOWN;
                    draw_block(pCGI, i - 2, j, matrix, bdi);
                }
                if (matrix[i + 1][j - 1].value >= 1 && matrix[i + 1][j - 1].value <= 8 && matrix[i + 1][j - 1].status == UNKNOWN && matrix[i][j - 1].status == KNOWN && matrix[i + 1][j].status == KNOWN) { //(1,-1)
                    matrix[i + 1][j - 1].status = KNOWN;
                    draw_block(pCGI, i, j - 2, matrix, bdi);
                }
                if (matrix[i + 1][j + 1].value >= 1 && matrix[i + 1][j + 1].value <= 8 && matrix[i + 1][j + 1].status == UNKNOWN && matrix[i][j + 1].status == KNOWN && matrix[i + 1][j].status == KNOWN) { //(1,1)
                    matrix[i + 1][j + 1].status = KNOWN;
                    draw_block(pCGI, i, j, matrix, bdi);
                }
            } //end of if (array[i][j] == '!')
        } //end of for
    } //end of for
}

/*
 * Function Name:    game_judgment
 * Function:         Determine if the game is over
 * Input Parameters: struct unit matrix[][34]
 *                   int row
 *                   int col
 * Return Value:     true / false
 */
bool game_judgment(struct unit matrix[][34], int row, int col)
{
    for (int i = 1; i <= row; i++)
        for (int j = 1; j <= col; j++)
            if (((matrix[i][j].status == UNKNOWN || matrix[i][j].status == MARKED_MINE) && matrix[i][j].value != '*') || matrix[i][j].status == MARKED_QUESTION)
                return false;
    return true;
}

/*
 * Function Name:    print_prompt
 * Function:         Print game over message
 * Input Parameters: time_t start_time
 *                   bool is_success
 * Return Value:     void
 */
void print_prompt(time_t start_time, bool is_success)
{
    cct_showstr(0, 0, is_success ? "游戏成功! 游戏时间:" : "游戏失败! 游戏时间:", COLOR_BLACK, COLOR_HYELLOW);
    int current_time = int(clock() - start_time) / CLOCKS_PER_SEC;
    cout << setfill('0') << setw(2) << current_time / 60 << ":" << setw(2) << current_time % 60 << setfill(' ') << " ";
    system("pause");
}