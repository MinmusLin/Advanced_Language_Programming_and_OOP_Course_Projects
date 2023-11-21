/****************************************************************
 * Project Name:  2048_Game
 * File Name:     2048_game_classes.cpp
 * File Function: 类的成员函数的体外实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/11/21
 ****************************************************************/

#include <iostream>
#include "../common/cmd_console_tools.h"
#include "../common/lib_gmw_tools.h"
#include "2048_game.h"

using namespace std;

/*
 * Function Name:    GAME
 * Function:         Constructed function
 * Input Parameters: int r
 *                   int c
 * Notes:            Class external implementation of member functions
 */
GAME::GAME(int r, int c)
{
    row = r;
    col = c;
    for (int i = 0; i < row + 2; i++) {
        matrix[i][0] = BOUNDARY;
        matrix[i][col + 1] = BOUNDARY;
    }
    for (int i = 0; i < col + 2; i++) {
        matrix[0][i] = BOUNDARY;
        matrix[row + 1][i] = BOUNDARY;
    }
}

/*
 * Function Name:    generate
 * Function:         Generate a color block randomly
 * Input Parameters: CONSOLE_GRAPHICS_INFO* pCGI
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void GAME::generate(CONSOLE_GRAPHICS_INFO* pCGI)
{
    while (true) {
        int r = rand() % row + 1, c = rand() % col + 1;
        if (matrix[r][c])
            continue;
        else {
            matrix[r][c] = rand() % 2 ? 2 : 4;
            gmw_draw_block(pCGI, r - 1, c - 1, matrix[r][c], bdi);
            return;
        }
    }
}

/*
 * Function Name:    move_down_to_up
 * Function:         Move color blocks from down to up
 * Input Parameters: CONSOLE_GRAPHICS_INFO* pCGI
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void GAME::move_down_to_up(CONSOLE_GRAPHICS_INFO* pCGI)
{
    for (int i = 1; i <= col; i++)
        for (int j = 1; j <= row; j++) {
            if (matrix[j][i]) {
                int num = matrix[j][i], len = 0;
                while (!matrix[j - len - 1][i]) {
                    matrix[j - len - 1][i] = matrix[j - len][i];
                    matrix[j - len][i] = 0;
                    len++;
                }
                bool is_merge = (matrix[j - len - 1][i] == matrix[j - len][i]);
                if (is_merge) {
                    matrix[j - len - 1][i] *= 2;
                    matrix[j - len][i] = 0;
                    len++;
                }
                gmw_move_block(pCGI, j - 1, i - 1, num, BDI_VALUE_BLANK, bdi, DOWN_TO_UP, len);
                if (is_merge) {
                    gmw_draw_block(pCGI, j - len - 1, i - 1, 2 * num, bdi);
                    score += calculate_score(2 * num);
                }
            }
        }
}

/*
 * Function Name:    move_up_to_down
 * Function:         Move color blocks from up to down
 * Input Parameters: CONSOLE_GRAPHICS_INFO* pCGI
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void GAME::move_up_to_down(CONSOLE_GRAPHICS_INFO* pCGI)
{
    for (int i = 1; i <= col; i++)
        for (int j = row; j >= 1; j--)
            if (matrix[j][i]) {
                int num = matrix[j][i], len = 0;
                while (!matrix[j + len + 1][i]) {
                    matrix[j + len + 1][i] = matrix[j + len][i];
                    matrix[j + len][i] = 0;
                    len++;
                }
                bool is_merge = (matrix[j + len + 1][i] == matrix[j + len][i]);
                if (is_merge) {
                    matrix[j + len + 1][i] *= 2;
                    matrix[j + len][i] = 0;
                    len++;
                }
                gmw_move_block(pCGI, j - 1, i - 1, num, BDI_VALUE_BLANK, bdi, UP_TO_DOWN, len);
                if (is_merge) {
                    gmw_draw_block(pCGI, j + len - 1, i - 1, 2 * num, bdi);
                    score += calculate_score(2 * num);
                }
            }
}

/*
 * Function Name:    move_right_to_left
 * Function:         Move color blocks from right to left
 * Input Parameters: CONSOLE_GRAPHICS_INFO* pCGI
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void GAME::move_right_to_left(CONSOLE_GRAPHICS_INFO* pCGI)
{
    for (int i = 1; i <= row; i++)
        for (int j = 1; j <= col; j++)
            if (matrix[i][j]) {
                int num = matrix[i][j], len = 0;
                while (!matrix[i][j - len - 1]) {
                    matrix[i][j - len - 1] = matrix[i][j - len];
                    matrix[i][j - len] = 0;
                    len++;
                }
                bool is_merge = (matrix[i][j - len - 1] == matrix[i][j - len]);
                if (is_merge) {
                    matrix[i][j - len - 1] *= 2;
                    matrix[i][j - len] = 0;
                    len++;
                }
                gmw_move_block(pCGI, i - 1, j - 1, num, BDI_VALUE_BLANK, bdi, RIGHT_TO_LEFT, len);
                if (is_merge) {
                    gmw_draw_block(pCGI, i - 1, j - len - 1, 2 * num, bdi);
                    score += calculate_score(2 * num);
                }
            }
}

/*
 * Function Name:    move_left_to_right
 * Function:         Move color blocks from left to right
 * Input Parameters: CONSOLE_GRAPHICS_INFO* pCGI
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void GAME::move_left_to_right(CONSOLE_GRAPHICS_INFO* pCGI)
{
    for (int i = 1; i <= row; i++)
        for (int j = col; j >= 1; j--)
            if (matrix[i][j]) {
                int num = matrix[i][j], len = 0;
                while (!matrix[i][j + len + 1]) {
                    matrix[i][j + len + 1] = matrix[i][j + len];
                    matrix[i][j + len] = 0;
                    len++;
                }
                bool is_merge = (matrix[i][j + len + 1] == matrix[i][j + len]);
                if (is_merge) {
                    matrix[i][j + len + 1] *= 2;
                    matrix[i][j + len] = 0;
                    len++;
                }
                gmw_move_block(pCGI, i - 1, j - 1, num, BDI_VALUE_BLANK, bdi, LEFT_TO_RIGHT, len);
                if (is_merge) {
                    gmw_draw_block(pCGI, i - 1, j + len - 1, 2 * num, bdi);
                    score += calculate_score(2 * num);
                }
            }
}

/*
 * Function Name:    gameover_judgment
 * Function:         Determine if the game is over
 * Input Parameters: void
 * Return Value:     1 - Game success
 *                   2 - Game continues
 *                   3 - Game failed
 * Notes:            Class external implementation of member functions
 */
int GAME::gameover_judgment(void)
{
    for (int i = 1; i <= row; i++)
        for (int j = 1; j <= col; j++)
            if (matrix[i][j] == GAME_TARGET)
                return 1;
    for (int i = 1; i <= row; i++)
        for (int j = 1; j <= col; j++)
            if (matrix[i][j] == 0)
                return 2;
    return 3;
}

/*
 * Function Name:    calculate_score
 * Function:         Calculate score
 * Input Parameters: int num
 * Return Value:     score
 * Notes:            Class external implementation of member functions
 */
int GAME::calculate_score(int num)
{
    switch (num) {
        case 4:
            return 4;
        case 8:
            return 16;
        case 16:
            return 48;
        case 32:
            return 128;
        case 64:
            return 320;
        case 128:
            return 768;
        case 256:
            return 1792;
        case 512:
            return 4096;
        case 1024:
            return 9216;
        case 2048:
            return 20480;
        default:
            return 0;
    }
}

/*
 * Function Name:    get_score
 * Function:         Get score
 * Input Parameters: void
 * Return Value:     score
 * Notes:            Class external implementation of member functions
 */
int GAME::get_score(void)
{
    return score;
}