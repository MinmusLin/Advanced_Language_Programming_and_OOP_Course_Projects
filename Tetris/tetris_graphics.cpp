/****************************************************************
 * Project Name:  Tetris
 * File Name:     tetris_graphics.cpp
 * File Function: 图形化界面函数的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/11/21
 ****************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include "tetris.h"

/* Namespace */
using namespace std;

/*
 * Function Name:    printSpecifiedGrid
 * Function:         Print a grid with specified number of rows and columns
 * Input Parameters: int startRow
 *                   int startCol
 *                   int row
 *                   int col
 * Return Value:     void
 */
static void printSpecifiedGrid(int startRow, int startCol, int row = gridRow, int col = gridCol)
{
    int offsetX = startCol * (gridSideLength + gridSpace), offsetY = startRow * (gridSideLength + gridSpace);
    for (int i = 0; i <= row; i++)
        for (int j = 0; j < gridSpace; j++) {
            int y = topGridMargin + i * (gridSideLength + gridSpace) + j;
            line(leftGridMargin + offsetX, y + offsetY, leftGridMargin + col * (gridSideLength + gridSpace) + gridSpace - 1 + offsetX, y + offsetY);
        }
    for (int i = 0; i <= col; i++)
        for (int j = 0; j < gridSpace; j++) {
            int x = leftGridMargin + i * (gridSideLength + gridSpace) + j;
            line(x + offsetX, topGridMargin + offsetY, x + offsetX, topGridMargin + row * (gridSideLength + gridSpace) + gridSpace - 1 + offsetY);
        }
}

/*
 * Function Name:    printFrame
 * Function:         Print frame
 * Input Parameters: int startRow
 *                   int startCol
 *                   int endRow
 *                   int endCol
 * Return Value:     void
 */
static void printFrame(int startRow, int startCol, int endRow, int endCol)
{
    /* Set line color */
    setlinecolor(BLACK);

    /* Calculate offsets */
    int offsetX = startCol * (gridSideLength + gridSpace), offsetY = startRow * (gridSideLength + gridSpace);

    /* Print frame */
    for (int i = 0; i < gridSpace; i++) {
        int y = topGridMargin + i;
        line(leftGridMargin + offsetX, y + offsetY, leftGridMargin + (endCol - startCol) * (gridSideLength + gridSpace) + gridSpace - 1 + offsetX, y + offsetY);
    }
    for (int i = 0; i < gridSpace; i++) {
        int x = leftGridMargin + i;
        line(x + offsetX, topGridMargin + offsetY, x + offsetX, topGridMargin + (endRow - startRow) * (gridSideLength + gridSpace) + gridSpace - 1 + offsetY);
    }
    for (int i = 0; i < gridSpace; i++) {
        int y = topGridMargin + (endRow - startRow) * (gridSideLength + gridSpace) + i;
        line(leftGridMargin + offsetX, y + offsetY, leftGridMargin + (endCol - startCol) * (gridSideLength + gridSpace) + gridSpace - 1 + offsetX, y + offsetY);
    }
    for (int i = 0; i < gridSpace; i++) {
        int x = leftGridMargin + (endCol - startCol) * (gridSideLength + gridSpace) + i;
        line(x + offsetX, topGridMargin + offsetY, x + offsetX, topGridMargin + (endRow - startRow) * (gridSideLength + gridSpace) + gridSpace - 1 + offsetY);
    }
}

/*
 * Function Name:    initializeGraphics
 * Function:         Initialize the graphical interface
 * Input Parameters: void
 * Return Value:     void
 */
void initializeGraphics(void)
{
    /* Initialize the graphical interface */
    initgraph(leftGridMargin + rightGridMargin + (gridCol + displayGridSideLength + 1) * (gridSideLength + gridSpace) + gridSpace, topGridMargin + bottomGridMargin + gridRow * (gridSideLength + gridSpace) + gridSpace);
    HWND hwnd = GetHWnd();
    SetWindowText(hwnd, _T("Tetris"));
    setbkcolor(GRID_BLANK_COLOR);
    setlinecolor(GRID_LINE_COLOR);
    cleardevice();

    /* Print specified grids */
    printSpecifiedGrid(0, 0);
    printSpecifiedGrid(4, gridCol + 1, displayGridSideLength, displayGridSideLength);
    printSpecifiedGrid(5 + 1 * (displayGridSideLength + 1), gridCol + 1, displayGridSideLength, displayGridSideLength);
    printSpecifiedGrid(5 + 2 * (displayGridSideLength + 1), gridCol + 1, displayGridSideLength, displayGridSideLength);
    printSpecifiedGrid(5 + 3 * (displayGridSideLength + 1), gridCol + 1, displayGridSideLength, displayGridSideLength);

    /* Print frames */
    printFrame(0, 0, gridRow, gridCol);
    printFrame(4, gridCol + 1, 4 + displayGridSideLength, gridCol + 1 + displayGridSideLength);
    printFrame(5 + 1 * (displayGridSideLength + 1), gridCol + 1, 5 + 1 * (displayGridSideLength + 1) + displayGridSideLength, gridCol + 1 + displayGridSideLength);
    printFrame(5 + 2 * (displayGridSideLength + 1), gridCol + 1, 5 + 2 * (displayGridSideLength + 1) + displayGridSideLength, gridCol + 1 + displayGridSideLength);
    printFrame(5 + 3 * (displayGridSideLength + 1), gridCol + 1, 5 + 3 * (displayGridSideLength + 1) + displayGridSideLength, gridCol + 1 + displayGridSideLength);

    /* Print prompt information */
    TCHAR infoText[16];
    settextcolor(BLACK);
    settextstyle(&Font_EN);
    _stprintf(infoText, _T("Lines:"));
    outtextxy(leftGridMargin + (gridCol + 1) * (gridSideLength + gridSpace), topInfoMargin + 1 * (gridSideLength + gridSpace) + infoOffset, infoText);
    _stprintf(infoText, _T("Hold:"));
    outtextxy(leftGridMargin + (gridCol + 1) * (gridSideLength + gridSpace), topInfoMargin + 4 * (gridSideLength + gridSpace) + infoOffset, infoText);
    _stprintf(infoText, _T("Next:"));
    outtextxy(leftGridMargin + (gridCol + 1) * (gridSideLength + gridSpace), topInfoMargin + (6 + displayGridSideLength) * (gridSideLength + gridSpace) + infoOffset, infoText);

    /* Print game rules */
    IMAGE img;
    loadimage(&img, _T("data/game_rules.png"));
    putimage(gameRulesX, gameRulesY, &img);
}

/*
 * Function Name:    printGridStatus
 * Function:         Print grid status
 * Input Parameters: int row
 *                   int col
 *                   COLORREF color
 * Return Value:     void
 */
void printGridStatus(int row, int col, COLORREF color)
{
    /* Calculate coordinates */
    int x = leftGridMargin + col * (gridSideLength + gridSpace) + gridSpace, y = topGridMargin + row * (gridSideLength + gridSpace) + gridSpace;

    /* Print grid status */
    setfillcolor(color);
    solidrectangle(x, y, x + gridSideLength - 1, y + gridSideLength - 1);
}

/*
 * Function Name:    printEliminatedLines
 * Function:         Print eliminated lines
 * Input Parameters: int eliminatedLines
 *                   bool is_first
 * Return Value:     void
 */
void printEliminatedLines(int eliminatedLines, bool is_first)
{
    TCHAR infoText[16];
    if (is_first)
        _stprintf(infoText, _T("%d        "), eliminatedLines);
    else
        _stprintf(infoText, _T("%d"), eliminatedLines);
    settextcolor(BLACK);
    settextstyle(&Font_EN);
    outtextxy(leftGridMargin + (gridCol + 1) * (gridSideLength + gridSpace), topInfoMargin + 1 * (gridSideLength + gridSpace) + 6 * infoOffset, infoText);
}

/*
 * Function Name:    printScore
 * Function:         Print score
 * Input Parameters: int score
 *                   bool is_first
 * Return Value:     void
 */
void printScore(int score, bool is_first)
{
    TCHAR infoText[32];
    if (is_first)
        _stprintf(infoText, _T("游戏得分：%d         "), score);
    else
        _stprintf(infoText, _T("游戏得分：%d"), score);
    settextcolor(BLACK);
    settextstyle(&Font_CN);
    outtextxy(leftGridMargin, topInfoMargin, infoText);
}