/****************************************************************
 * Project Name:  Love_Code
 * File Name:     lovecode_classes.cpp
 * File Function: 类的成员函数的体外实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/9/30
 ****************************************************************/

#include <iostream>
#include "..\common\cmd_console_tools.h"
#include "lovecode.h"
#include "pixel_matrixs.h"

using namespace std;

/*
 * Function Name:    point_initialize
 * Function:         Initialized function
 * Input Parameters: int precision
 *                   double factor
 *                   int fullfit_or_not
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void point_set::point_initialize(int precision, double factor, int fullfit_or_not)
{
    number_of_points = precision;
    double probability = factor * PROBABILITY_FACTOR;
    for (int i = 0; i < number_of_points; i++) {
        double t = i * 2 * PI / number_of_points;
        if (fullfit_or_not ? true : (rand() % 100 < probability && rand() % 100 > probability)) {
            points[i].x = factor * (16 * sin(t) * sin(t) * sin(t));
            points[i].y = factor * (13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t));
        }
    }
}

/*
 * Function Name:    print_heart
 * Function:         Print heart shape
 * Input Parameters: int bg_color
 *                   int fg_color
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void point_set::print_heart(int bg_color, int fg_color)
{
    for (int i = 0; i < number_of_points; i++)
        if (points[i].x || points[i].y)
            cct_showstr(int(2 * (points[i].x + ORIGIN_OF_ABSCISSA)), int(-points[i].y + ORIGIN_OF_ORDINATE - CORRECTION_FACTOR), "  ", bg_color, fg_color);
}

/*
 * Function Name:    pixel_character
 * Function:         Constructed function
 * Input Parameters: const int character[][16]
 * Notes:            Class external implementation of member functions
 */
pixel_characters::pixel_characters(const int character[][16])
{
    for (int i = 0; i < 16; i++)
        for (int j = 0; j < 16; j++)
            pixel_matrix[i][j] = character[i][j];
}

/*
 * Function Name:    print_character
 * Function:         Print pixel character
 * Input Parameters: int x
 *                   int y
 *                   int bg_color
 *                   int fg_color
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void pixel_characters::print_character(int x, int y, int bg_color, int fg_color)
{
    for (int i = 0; i < 16; i++) {
        cct_gotoxy(x * 2, y + i);
        for (int j = 0; j < 16; j++) {
            pixel_matrix[i][j] ? cct_setcolor(bg_color, fg_color) : cct_setcolor();
            cout << "  ";
        }
    }
}

/*
 * Function Name:    pixel_ASCIIs
 * Function:         Constructed function
 * Input Parameters: const int ASCII[][16][8]
 * Notes:            Class external implementation of member functions
 */
pixel_ASCIIs::pixel_ASCIIs(const int ASCII[][16][8])
{
    for (int i = 0; i < 95; i++)
        for (int j = 0; j < 16; j++)
            for (int k = 0; k < 8; k++)
                pixel_matrix[i][j][k] = ASCII[i][j][k];
}

/*
 * Function Name:    print_ASCII
 * Function:         Print pixel ASCII
 * Input Parameters: int x
 *                   int y
 *                   int ASCII
 *                   int bg_color
 *                   int fg_color
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void pixel_ASCIIs::print_ASCII(int x, int y, int ASCII, int bg_color, int fg_color)
{
    for (int i = 0; i < 16; i++) {
        cct_gotoxy(x * 2, y + i);
        for (int j = 0; j < 8; j++) {
            pixel_matrix[ASCII][i][j] ? cct_setcolor(bg_color, fg_color) : cct_setcolor();
            cout << "  ";
        }
    }
}