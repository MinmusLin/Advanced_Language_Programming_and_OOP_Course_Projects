/****************************************************************
 * Project Name:  Color_Linez
 * File Name:     color_linez_classes.cpp
 * File Function: 类的成员函数的体外实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/9/27
 ****************************************************************/

#include <iostream>
#include <iomanip>
#include "../common/cmd_console_tools.h"
#include "../common/lib_gmw_tools.h"
#include "color_linez.h"

using namespace std;

/*
 * Function Name:    GAME
 * Function:         Constructed function
 * Notes:            Class external implementation of member functions
 */
GAME::GAME()
{
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
 * Function:         Generate balls randomly
 * Input Parameters: CONSOLE_GRAPHICS_INFO* pCGI
 *                   int n
 *                   bool initialize
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void GAME::generate(CONSOLE_GRAPHICS_INFO* pCGI, int n, bool initialize)
{
    for (int i = 0; i < n; i++)
        while (1) {
            int r = rand() % row + 1, c = rand() % col + 1;
            if (matrix[r][c])
                continue;
            else {
                matrix[r][c] = initialize ? (rand() % 7 + 1) : next_generate[i];
                gmw_draw_block(pCGI, r - 1, c - 1, matrix[r][c], bdi);
                break;
            }
        }
    for (int i = 0; i < 3; i++) {
        next_generate[i] = rand() % 7 + 1;
        cct_showstr(30 + col * 4 + i * 2, 4, "●", COLOR_HWHITE, bdi[next_generate[i]].fgcolor);
    }
}

/*
 * Function Name:    is_empty
 * Function:         Determine if it is empty
 * Input Parameters: int r
 *                   int c
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
bool GAME::is_empty(int r, int c)
{
    return matrix[r + 1][c + 1] == 0;
}

/*
 * Function Name:    get_value
 * Function:         Get value
 * Input Parameters: int r
 *                   int c
 * Return Value:     value
 * Notes:            Class external implementation of member functions
 */
int GAME::get_value(int r, int c)
{
    return matrix[r + 1][c + 1];
}

/*
 * Function Name:    set_value
 * Function:         Set value
 * Input Parameters: int r
 *                   int c
 *                   int value
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void GAME::set_value(int r, int c, int value)
{
    matrix[r + 1][c + 1] = value;
}

/*
 * Function Name:    calculate
 * Function:         Calculate number and proportion
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void GAME::calculate(void)
{
    for (int i = 0; i < 7; i++)
        data[i].number = 0;
    for (int i = 1; i <= row; i++)
        for (int j = 1; j <= col; j++)
            if (matrix[i][j])
                data[matrix[i][j] - 1].number++;
    for (int i = 0; i < 7; i++)
        data[i].proportion = (double)data[i].number * 100 / (row * col);
}

/*
 * Function Name:    print_statistic
 * Function:         Print statistic in the chart
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void GAME::print_statistic(void)
{
    cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
    for (int i = 0; i < 7; i++) {
        cct_gotoxy(16 + col * 4, 8 + i * 2);
        cout << setw(2) << data[i].number;
        cct_gotoxy(19 + col * 4, 8 + i * 2);
        cout << setw(2) << (int)data[i].proportion;
        cct_gotoxy(22 + col * 4, 8 + i * 2);
        cout << (int)(data[i].proportion * 10) % 10;
        cct_gotoxy(34 + col * 4, 8 + i * 2);
        cout << setw(2) << (int)data[i].deleted;
    }
}

/*
 * Function Name:    is_eliminate
 * Function:         Determine whether to eliminate
 * Input Parameters: int eliminate_matrix[][col + 2]
 *                   int targetRow
 *                   int targetCol
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
bool GAME::is_eliminate(int eliminate_matrix[][col + 2], int targetRow, int targetCol)
{
    eliminate_matrix[targetRow + 1][targetCol + 1] = 1;
    int num = matrix[targetRow + 1][targetCol + 1], directions[8][2] = { {1,0},{-1,0},{0,1},{0,-1},{-1,-1},{1,1},{1,-1},{-1,1} }, len[8] = { 0 };
    bool judgment[4] = { true,true,true,true };
    for (int d = 0; d < 8; d++) {
        int row_offset = directions[d][0], col_offset = directions[d][1], i = 1;
        while (matrix[targetRow + 1 + i * row_offset][targetCol + 1 + i * col_offset] == num) {
            eliminate_matrix[targetRow + 1 + i * row_offset][targetCol + 1 + i * col_offset] = 1;
            len[d]++;
            i++;
        }
        if (d % 2 && len[d - 1] + len[d] < 4) {
            judgment[d / 2] = false;
            for (int k = 0; k < 2; k++) {
                int _row_offset = directions[d - k][0], _col_offset = directions[d - k][1], j = 1;
                while (matrix[targetRow + 1 + j * _row_offset][targetCol + 1 + j * _col_offset] == num) {
                    eliminate_matrix[targetRow + 1 + j * _row_offset][targetCol + 1 + j * _col_offset] = 0;
                    j++;
                }
            }
        }
    }
    return (judgment[0] || judgment[1] || judgment[2] || judgment[3]);
}

/*
 * Function Name:    statistic_deleted_plus
 * Function:         Update the number of eliminated balls
 * Input Parameters: int n
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void GAME::statistic_deleted_plus(int n)
{
    data[n].deleted++;
}

/*
 * Function Name:    print_score
 * Function:         Print score
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void GAME::print_score(void)
{
    score += 10;
    cct_gotoxy(14 + col * 4, 4);
    cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
    cout << setw(3) << score;
}

/*
 * Function Name:    get_blank
 * Function:         Get blank
 * Input Parameters: void
 * Return Value:     the number of blank balls
 * Notes:            Class external implementation of member functions
 */
int GAME::get_blank(void)
{
    int blank = 0;
    for (int i = 1; i <= row; i++)
        for (int j = 1; j <= col; j++)
            if (!matrix[i][j])
                blank++;
    return blank;
}

/*
 * Function Name:    empty
 * Function:         Empty
 * Input Parameters: void
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
bool queue::empty(void)
{
    return front == rear;
}

/*
 * Function Name:    push
 * Function:         Push
 * Input Parameters: point p
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void queue::push(point p)
{
    data[rear++] = p;
}

/*
 * Function Name:    pop
 * Function:         Pop
 * Input Parameters: void
 * Return Value:     struct point
 * Notes:            Class external implementation of member functions
 */
struct point queue::pop(void)
{
    return data[front++];
}