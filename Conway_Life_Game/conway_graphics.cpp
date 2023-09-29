/****************************************************************
 * Project Name:  Conway_Life_Game
 * File Name:     conway_graphics.cpp
 * File Function: 图形化界面函数的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/9/30
 ****************************************************************/

#include <graphics.h>
#include "conway.h"

using namespace std;

/*
 * Function Name:    initialize_graphics
 * Function:         Initialize the graphical interface
 * Input Parameters: void
 * Return Value:     void
 */
void initialize_graphics(void)
{
    /* Initialize the graphical interface */
    initgraph(leftGridMargin + rightGridMargin + gridCol * (gridSideLength + gridSpace) + gridSpace, topGridMargin + bottomGridMargin + gridRow * (gridSideLength + gridSpace) + gridSpace);
    HWND hwnd = GetHWnd();
    SetWindowText(hwnd, _T("Conway Life Game"));
    setbkcolor(GRID_BLANK_COLOR);
    setlinecolor(GRID_LINE_COLOR);
    cleardevice();

    /* Print borders */
    for (int i = 0; i <= gridRow; i++)
        for (int j = 0; j < gridSpace; j++) {
            int y = topGridMargin + i * (gridSideLength + gridSpace) + j;
            line(leftGridMargin, y, leftGridMargin + gridCol * (gridSideLength + gridSpace) + gridSpace - 1, y);
        }
    for (int i = 0; i <= gridCol; i++)
        for (int j = 0; j < gridSpace; j++) {
            int x = leftGridMargin + i * (gridSideLength + gridSpace) + j;
            line(x, topGridMargin, x, topGridMargin + gridRow * (gridSideLength + gridSpace) + gridSpace - 1);
        }
}

/*
 * Function Name:    print_grid_status
 * Function:         Print grid status
 * Input Parameters: int row
 *                   int col
 *                   bool is_alive
 * Return Value:     void
 */
void print_grid_status(int row, int col, bool is_alive)
{
    /* Calculate coordinates */
    int x = leftGridMargin + col * (gridSideLength + gridSpace) + gridSpace, y = topGridMargin + row * (gridSideLength + gridSpace) + gridSpace;

    /* Print grid status */
    setfillcolor(is_alive ? GRID_ALIVE_COLOR : GRID_BLANK_COLOR);
    solidrectangle(x, y, x + gridSideLength - 1, y + gridSideLength - 1);
}