/****************************************************************
 * Project Name:  Popstar
 * File Name:     popstar_tools.cpp
 * File Function: 工具函数的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/9/24
 ****************************************************************/

#include <iostream>
#include <conio.h>
#include "..\common\cmd_console_tools.h"
#include "popstar.h"
using namespace std;

/*
 * Function Name:    parameters_input
 * Function:         Enter the number of rows and columns
 * Input Parameters: int& row
 *                   int& column
 * Return Value:     void
 */
void parameters_input(int& row, int& column)
{
    /* Enter the number of rows */
    while (1) {
        cout << "请输入行数(" << ROW_MIN << "-" << ROW_MAX << ")：" << endl;
        cin >> row;
        if (cin.good()) {
            if (row >= ROW_MIN && row <= ROW_MAX)
                break;
            else
                continue;
        }
        else {
            cin.clear();
            cin.ignore(65536, '\n');
        }
    }

    /* Enter the number of columns */
    while (1) {
        cout << "请输入列数(" << COLUMN_MIN << "-" << COLUMN_MAX << ")：" << endl;
        cin >> column;
        if (cin.good()) {
            if (column >= ROW_MIN && column <= ROW_MAX)
                break;
            else
                continue;
        }
        else {
            cin.clear();
            cin.ignore(65536, '\n');
        }
    }

    /* Clear internal error status flags and characters in the buffer */
    cin.clear();
    cin.ignore(65536, '\n');
}

/*
 * Function Name:    matrix_initialize
 * Function:         Initialize the matrix
 * Input Parameters: int matrix[][10]
 *                   int row
 *                   int column
 * Return Value:     void
 */
void matrix_initialize(int matrix[][10], int row, int column)
{
    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
            matrix[i][j] = rand() % BLOCK_NUMBER + 1;
}

/*
 * Function Name:    judgment_continuity
 * Function:         Count the number of consecutive identical values at the input matrix coordinates
 * Input Parameters: int matrix[][10]
 *                   int judgment_array[][12]
 *                   int row
 *                   int column
 *                   int select_r
 *                   int select_c
 * Return Value:     The number of consecutive identical values
 */
int judgment_continuity(int matrix[][10], int judgment_array[][12], int row, int column, int select_r, int select_c)
{
    /* Initialize the judging array */
    for (int i = 1; i < row + 1; i++)
        for (int j = 1; j < column + 1; j++)
            judgment_array[i][j] = matrix[i - 1][j - 1];

    /* Use the flood fill algorithm to find consecutive identical values in the array */
    flood_fill(judgment_array, select_r + 1, select_c + 1);

    /* Count the number of consecutive identical values */
    int num = 0;
    for (int i = 1; i < row + 1; i++)
        for (int j = 1; j < column + 1; j++)
            if (judgment_array[i][j] == '*')
                num++;
    return num;
}

/*
 * Function Name:    flood_fill
 * Function:         Use the flood fill algorithm to find consecutive identical values in the array
 * Input Parameters: int array[][12]
 *                   int x
 *                   int y
 * Return Value:     void
 */
void flood_fill(int array[][12], int x, int y)
{
    /* Save the color of the current position */
    int color = array[x][y];

    /* Mark the positions that have been traversed */
    array[x][y] = '*';

    /* Traverse in the four directions recursively */
    if (array[x][y - 1] == color)
        flood_fill(array, x, y - 1);
    if (array[x][y + 1] == color)
        flood_fill(array, x, y + 1);
    if (array[x - 1][y] == color)
        flood_fill(array, x - 1, y);
    if (array[x + 1][y] == color)
        flood_fill(array, x + 1, y);
}

/*
 * Function Name:    wait_for_end
 * Function:         Enter "End" to return to the menu
 * Input Parameters: void
 * Return Value:     void
 */
void wait_for_end(void)
{
    /* Print the prompt message */
    cout << endl << "请输入End返回菜单：";

    /* Get the current position coordinates */
    int get_x, get_y;
    cct_getxy(get_x, get_y);

    /* Input */
    while (1) {
        /* Clear the input content */
        cct_showch(get_x, get_y, ' ', COLOR_BLACK, COLOR_WHITE, 3);
        cct_gotoxy(get_x, get_y);

        /* Read a single character without displaying it */
        char input[4] = { 0 };
        for (int i = 0; i < 4; i++) {
            while (1) {
                char ch = _getch();
                if (ch == 0 || ch == -32)
                    ch = _getch();
                else if (ch == '\r') {
                    i = 4;
                    break;
                }
                else if (ch >= 33 && ch <= 126) {
                    if (i != 3) {
                        cout << ch;
                        input[i] = ch;
                    }
                    break;
                }
                else
                    continue;
            } // end of while (1)
        } // end of for

        /* Validate the correctness of the input */
        if (strcasecmp(input, "End")) {
            cct_showstr(0, get_y + 1, "输入错误，请重新输入", COLOR_BLACK, COLOR_HRED, 1, -1);
            cct_setcolor();
        }
        else
            break;
    } // end of while (1)
}

/*
 * Function Name:    wait_for_enter
 * Function:         Press the Enter key to continue
 * Input Parameters: const char prompt[]
 * Return Value:     void
 */
void wait_for_enter(const char prompt[])
{
    cout << endl << prompt;
    while (_getch() != '\r')
        continue;
    cout << endl;
}

/*
 * Function Name:    strcasecmp
 * Function:         Comparing the sizes of strings s1 and s2, ignoring case for English letters
 * Input Parameters: const char s1[]
 *                   const char s2[]
 * Return Value:     0/The ASCII difference between the first non-equal characters
 * Notes:            If the characters at the non-equal position are different case letters, convert them to lowercase and then compare
 *                   If the characters at the non-equal position are an uppercase letter and another character, return the difference between the corresponding lowercase letter and the other character
 */
int strcasecmp(const char s1[], const char s2[])
{
    int i = 0;
    char a, b;
    while (1) {
        a = s1[i];
        b = s2[i];
        if (a >= 'A' && a <= 'Z')
            a += 32;
        if (b >= 'A' && b <= 'Z')
            b += 32;
        if (a == b) {
            if (a)
                i++;
            else
                return 0;
        }
        else
            return a - b;
    } // end of while (1)
}

/*
 * Function Name:    array_incorporate
 * Function:         Merge identical values in the array
 * Input Parameters: int matrix[][10]
 *                   int judgment_array[][12]
 *                   int row
 *                   int column
 * Return Value:     void
 */
void array_incorporate(int matrix[][10], int judgment_array[][12], int row, int column)
{
    for (int i = 1; i < row + 1; i++)
        for (int j = 1; j < column + 1; j++)
            if (judgment_array[i][j] == '*')
                matrix[i - 1][j - 1] = 0;
}

/*
 * Function Name:    array_translation
 * Function:         Shift zero values in the array
 * Input Parameters: int matrix[][10]
 *                   int row
 *                   int column
 *                   int graphical_or_not
 *                   int divider_or_not
 * Return Value:     void
 */
void array_translation(int matrix[][10], int row, int column, int graphical_or_not, int divider_or_not)
{
    /* Clear the prompt message */
    if (divider_or_not)
        clear_information(row, column, divider_or_not);

    /* Shift zero values vertically in the array */
    for (int i = 0; i < column; i++) {
        for (int j = row - 1; j >= 0; j--) {
            int len = 0;
            if (matrix[j][i]) {
                for (int k = j; k < row; k++)
                    if (matrix[k][i] == 0)
                        len++;
                if (len) {
                    matrix[j + len][i] = matrix[j][i];
                    matrix[j][i] = 0;
                    if (graphical_or_not)
                        print_move_vertical(matrix, j, i, len, divider_or_not);
                }
            } // end of if (matrix[j][i])
        } // end of for
    } // end of for

    /* Shift zero values horizontally in the array */
    for (int i = 0; i < column; i++) {
        int len = 0;
        if (matrix[row - 1][i]) {
            for (int j = i; j >= 0; j--)
                if (matrix[row - 1][j] == 0)
                    len++;
            if (len)
                for (int k = row - 1; k >= 0; k--) {
                    if (matrix[k][i]) {
                        matrix[k][i - len] = matrix[k][i];
                        matrix[k][i] = 0;
                        if (graphical_or_not)
                            print_move_horizontal(matrix, k, i, len, divider_or_not);
                    }
                }
        } // end of if (matrix[row - 1][i])
    } // end of for
}

/*
 * Function Name:    array_judgment
 * Function:         Determine if the array has consecutive identical values
 * Input Parameters: int matrix[][10]
 *                   int row
 *                   int column
 * Return Value:     -1 (Level completed) / Remaining count of items that cannot be eliminated (Level not completed)
 *                   
 */
int array_judgment(int matrix[][10], int row, int column)
{
    /* Initialize the judging array */
    int judgment_array[12][12] = { 0 }, n = 0;
    for (int i = 1; i < row + 1; i++)
        for (int j = 1; j < column + 1; j++)
            judgment_array[i][j] = matrix[i - 1][j - 1];

    /* Determine if the array has consecutive identical values */
    for (int i = 1; i < row + 1; i++)
        for (int j = 1; j < column + 1; j++)
            if (judgment_array[i][j]) {
                n++;
                if (judgment_array[i][j] == judgment_array[i + 1][j] || judgment_array[i][j] == judgment_array[i][j + 1] || judgment_array[i][j] == judgment_array[i - 1][j] || judgment_array[i][j] == judgment_array[i][j - 1])
                    return -1;
            }
    return n;
}