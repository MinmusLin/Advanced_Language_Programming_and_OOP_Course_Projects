/****************************************************************
 * Project Name:  Popstar
 * File Name:     popstar_base.cpp
 * File Function: 内部数组方式函数的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/11/21
 ****************************************************************/

#include <iostream>
#include <iomanip>
#include <conio.h>
#include "..\common\cmd_console_tools.h"
#include "popstar.h"

/* Namespace */
using namespace std;

/*
 * Function Name:    base_mark
 * Function:         Executing menu item A
 * Input Parameters: void
 * Return Value:     void
 */
void base_mark(void)
{
    /* Initialize */
    int row, column, select_r, select_c, matrix[10][10] = { 0 }, judgment_array[12][12] = { 0 };

    /* Enter the number of rows and columns */
    parameters_input(row, column);

    /* Initialize the matrix */
    matrix_initialize(matrix, row, column);

    /* Print the current array */
    print_array(matrix, judgment_array, row, column, 0);

    /* Enter the coordinates of the matrix */
    coordinate_input(matrix, judgment_array, row, column, select_r, select_c);

    /* Print the search result array and the current array (with different colors for identification) */
    print_array(matrix, judgment_array, row, column, 1);
    print_array(matrix, judgment_array, row, column, 2);
}

/*
 * Function Name:    base_eliminate
 * Function:         Executing menu item B
 * Input Parameters: void
 * Return Value:     void
 */
void base_eliminate(void)
{
    /* Initialize */
    int row, column, select_r, select_c, matrix[10][10] = { 0 }, judgment_array[12][12] = { 0 }, score_bound = 0, score_total = 0;

    /* Enter the number of rows and columns */
    parameters_input(row, column);

    /* Initialize the matrix */
    matrix_initialize(matrix, row, column);

    /* Print the current array */
    print_array(matrix, judgment_array, row, column, 0);

    /* Calculate the score for this round and the total score */
    score_bound = coordinate_input(matrix, judgment_array, row, column, select_r, select_c);
    score_total += score_bound;

    /* Print the search result array and the current array (with different colors for identification) */
    print_array(matrix, judgment_array, row, column, 1);
    print_array(matrix, judgment_array, row, column, 2);

    /* Confirm whether to eliminate the matrix coordinates and the surrounding positions with the same value */
    if (eliminate_confirm(select_r, select_c) == 2)
        sameValue_elimination(matrix, judgment_array, row, column, score_bound, score_total);
}

/*
 * Function Name:    base_level
 * Function:         Executing menu item C
 * Input Parameters: void
 * Return Value:     void
 */
void base_level(void)
{
    /* Initialize */
    int row, column, select_r, select_c, matrix[10][10] = { 0 }, judgment_array[12][12] = { 0 }, score_bound = 0, score_total = 0;

    /* Enter the number of rows and columns */
    parameters_input(row, column);

    /* Initialize the matrix */
    matrix_initialize(matrix, row, column);

    /* Complete one level */
    while (true) {
        /* Print the current array */
        print_array(matrix, judgment_array, row, column, 0);

        /* Determine if the array has consecutive identical values */
        int remain = array_judgment(matrix, row, column);
        if (remain >= 0) {
            cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
            cout << endl << "剩余" << remain << "个不可消除项，本关结束" << endl;
            cct_setcolor();
            break;
        }

        /* Calculate the score for this round and the total score */
        score_bound = coordinate_input(matrix, judgment_array, row, column, select_r, select_c);

        /* Print the search result array and the current array (with different colors for identification) */
        print_array(matrix, judgment_array, row, column, 1);
        print_array(matrix, judgment_array, row, column, 2);

        /* Confirm whether to eliminate the matrix coordinates and the surrounding positions with the same value */
        int confirm = eliminate_confirm(select_r, select_c);
        if (confirm == 2) {
            score_total += score_bound;
            sameValue_elimination(matrix, judgment_array, row, column, score_bound, score_total);
        }
        else if (confirm == 1)
            continue;
        else
            break;

        /* Press the Enter key to continue */
        wait_for_enter("本次消除结束，按回车键继续新一次的消除...");
    } // end of while (true)
}

/*
 * Function Name:    print_array
 * Function:         Print array
 * Input Parameters: int matrix[][10]
 *                   int judgment_array[][12]
 *                   int row
 *                   int column
 *                   int prompt: 0 - Current array
 *                               1 - Result array
 *                               2 - Current array (with different colors for identification)
 *                               3 - Merged array (with different colors for identification)
 *                               4 - Array after the fall
 * Return Value:     void
 */
void print_array(int matrix[][10], int judgment_array[][12], int row, int column, int prompt)
{
    /* Print the prompt message */
    cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
    switch (prompt) {
        case 1:
            cout << endl << "查找结果数组：" << endl;
            break;
        case 2:
            cout << endl << "当前数组(不同色标识)：" << endl;
            break;
        case 3:
            cout << endl << "相同值归并后的数组(不同色标识)：" << endl;
            break;
        case 4:
            cout << endl << "下落后的数组：" << endl;
            break;
        default:
            cout << endl << "当前数组：" << endl;
            break;
    } // end of switch (prompt)
    cct_setcolor();

    /* Print array */
    cout << "  |";
    for (int i = 0; i < column; i++)
        cout << setw(3) << i;
    cout << endl << "--+" << setfill('-') << setw(3 * column + 1) << "" << setfill(' ') << endl;
    for (int i = 0; i < row; i++) {
        cout << char('A' + i) << " |";
        for (int j = 0; j < column; j++) {
            cout << "  ";
            switch (prompt) {
                case 1: // Result array
                    if (judgment_array[i + 1][j + 1] == '*')
                        cout << "*";
                    else
                        cout << "0";
                    break;
                case 2: // Current array
                case 3: // Merged array (with different colors for identification)
                    if (judgment_array[i + 1][j + 1] == '*')
                        cct_setcolor(COLOR_HYELLOW, COLOR_BLACK);
                    cout << matrix[i][j];
                    if (judgment_array[i + 1][j + 1] == '*')
                        cct_setcolor();
                    break;
                case 4: // Array after the fall
                default: // Current array
                    if (matrix[i][j] == 0)
                        cct_setcolor(COLOR_HYELLOW, COLOR_BLACK);
                    cout << matrix[i][j];
                    if (matrix[i][j] == 0)
                        cct_setcolor();
                    break;
            } // end of switch (prompt)
        } // end of for
        cout << endl;
    } // end of for
}

/*
 * Function Name:    coordinate_input
 * Function:         Enter the matrix coordinates
 * Input Parameters: int matrix[][10]
 *                   int judgment_array[][12]
 *                   int row
 *                   int column
 *                   int& dst_r
 *                   int& dst_c
 * Return Value:     Score for this round
 */
int coordinate_input(int matrix[][10], int judgment_array[][12], int row, int column, int& dst_r, int& dst_c)
{
    /* Print the prompt message */
    cout << endl << "请以字母和数字形式输入矩阵坐标[例：C2]：";

    /* Get the current position coordinates */
    int get_x, get_y;
    cct_getxy(get_x, get_y);

    /* Input */
    while (true) {
        /* Clear the input content */
        cct_showch(get_x, get_y, ' ', COLOR_BLACK, COLOR_WHITE, 2);
        cct_gotoxy(get_x, get_y);

        /* Read a single character without displaying it */
        char input[3] = { 0 };
        for (int i = 0; i < 3; i++) {
            while (true) {
                char ch = _getch();
                if (ch == 0 || ch == -32)
                    ch = _getch();
                else if (ch == '\r') {
                    i = 3;
                    break;
                }
                else if (ch >= 33 && ch <= 126) {
                    if (i != 2) {
                        cout << ch;
                        input[i] = ch;
                    }
                    break;
                }
                else
                    continue;
            } //end of while (true)
        } //end of for

        /* Clear the prompt message */
        cct_showch(0, get_y + 1, ' ', COLOR_BLACK, COLOR_WHITE, 67);
        cct_gotoxy(0, get_y + 1);

        /* Validate the correctness of the input */
        if (((input[0] >= 'a' && input[0] < 'a' + row) || (input[0] >= 'A' && input[0] < 'A' + row)) && (input[1] >= '0' && input[1] < '0' + column)) {
            /* Save the current coordinates */
            dst_r = input[0] - ((input[0] >= 'a' && input[0] < 'a' + row) ? 'a' : 'A');
            dst_c = input[1] - '0';

            /* Check if the coordinate position is illegal */
            if (matrix[dst_r][dst_c] == 0) {
                cct_setcolor(COLOR_BLACK, COLOR_HRED);
                cout << "输入为" << char(dst_r + 'A') << "行" << dst_c << "列，输入的矩阵坐标位置为0（非法位置），请重新输入";
                cct_setcolor();
                continue;
            }

            /* Confirm whether to eliminate the matrix coordinates and the surrounding positions with the same value */
            int num = judgment_continuity(matrix, judgment_array, row, column, dst_r, dst_c);
            if (num == 1) {
                cct_setcolor(COLOR_BLACK, COLOR_HRED);
                cout << "输入为" << char(dst_r + 'A') << "行" << dst_c << "列，输入的矩阵坐标位置处无连续相同值，请重新输入";
                cct_setcolor();
                continue;
            }
            else {
                cct_setcolor(COLOR_BLACK, COLOR_HGREEN);
                cout << "输入为" << char(dst_r + 'A') << "行" << dst_c << "列" << endl;
                cct_setcolor();
                return num * num * 5;
            }
        } // end of if (((input[0] >= 'a' && input[0] < 'a' + row) || (input[0] >= 'A' && input[0] < 'A' + row)) && (input[1] >= '0' && input[1] < '0' + column))
        else {
            cct_setcolor(COLOR_BLACK, COLOR_HRED);
            cout << "输入错误，请重新输入";
            cct_setcolor();
        } // end of else
    } // end of while (true)
}

/*
 * Function Name:    eliminate_confirm
 * Function:         Confirm whether to eliminate the matrix coordinates and the surrounding positions with the same value
 * Input Parameters: int dst_r
 *                   int dst_c
 * Return Value:     0 - Quit
 *                   1 - Abort the current operation
 *                   2 - Complete the current operation
 */
int eliminate_confirm(int dst_r, int dst_c)
{
    /* Print the prompt message */
    cout << endl << "请确认是否把" << char('A' + dst_r) << dst_c << "及周围的相同值消除(Y/N/Q)：";

    /* Input */
    char input;
    while (true) {
        input = _getch();
        if (input == 0 || input == -32)
            input = _getch();
        else if (input == 'Y' || input == 'y' || input == 'N' || input == 'n' || input == 'Q' || input == 'q') {
            cout << input << endl;
            switch (input) {
                case 'Y': // Complete the current operation
                case 'y':
                    return 2;
                case 'N': // Abort the current operation
                case 'n':
                    return 1;
                default: // Quit
                    return 0;
            }
        }
        else
            continue;
    } // end of while (true)
}

/*
 * Function Name:    sameValue_elimination
 * Function:         Eliminate identical values
 * Input Parameters: int matrix[][10]
 *                   int judgment_array[][12]
 *                   int row
 *                   int column
 *                   int score_bound
 *                   int score_total
 * Return Value:     void
 */
void sameValue_elimination(int matrix[][10], int judgment_array[][12], int row, int column, int score_bound, int score_total)
{
    /* Merge identical values in the array */
    array_incorporate(matrix, judgment_array, row, column);

    /* Print the search result array and the current array (with different colors for identification) */
    print_array(matrix, judgment_array, row, column, 3);

    /* Print the score for this round and the total score */
    cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
    cout << endl << "本次得分：" << score_bound << " 总得分：" << score_total << endl;
    cct_setcolor();

    /* Press the Enter key to continue */
    wait_for_enter("按回车键进行数组下落操作...");

    /* Shift the array */
    array_translation(matrix, row, column, NON_GRAPHICAL_INTERFACE, WITHOUT_DIVIDER);

    /* Print the array after the downward movement */
    print_array(matrix, judgment_array, row, column, 4);
}