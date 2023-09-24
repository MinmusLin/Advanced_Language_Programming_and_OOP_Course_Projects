/****************************************************************
 * Project Name:  Gluttonous_Snake
 * File Name:     gluttonous_snake_graphics.cpp
 * File Function: 图形化界面函数的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/9/24
 ****************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "gluttonous_snake.h"
using namespace std;

/*
 * Function Name:    initialize_graphics
 * Function:         Initialize the graphical interface
 * Input Parameters: Mode mode
 * Return Value:     void
 */
void initialize_graphics(Mode mode)
{
    /* Initialize the graphical interface */
    initgraph(leftGridMargin + rightGridMargin + gridCol * (gridSideLength + gridSpace) + gridSpace, topGridMargin + bottomGridMargin + gridRow * (gridSideLength + gridSpace) + gridSpace);
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

    /* Print highest score */
    int highestScore = readHighestScore(mode);
    TCHAR infoText[64];
    char promptInfo[64];
    sprintf(promptInfo, "[当前模式历史最高分：%d]", highestScore);
    _stprintf(infoText, _T("[当前模式历史最高分：%d]"), highestScore);
    settextstyle(&Font);
    settextcolor(BLACK);
    outtextxy(leftGridMargin + gridCol * (gridSideLength + gridSpace) + gridSpace - strlen(promptInfo) * (topGridMargin - topInfoMargin - bottomInfoMargin) / 2, topInfoMargin, infoText);
}

/*
 * Function Name:    print_grid_status
 * Function:         Print grid status
 * Input Parameters: int row
 *                   int col
 *                   GridCondition gridCondition
 *                   SnakeCategory snakeCategory
 *                   Direction direction
 * Return Value:     void
 */
void print_grid_status(int row, int col, GridCondition gridCondition, SnakeCategory snakeCategory, Direction direction)
{
    /* Calculate coordinate */
    int x = leftGridMargin + col * (gridSideLength + gridSpace) + gridSpace, y = topGridMargin + row * (gridSideLength + gridSpace) + gridSpace;

    /* Match color */
    COLORREF color;
    switch (gridCondition) {
        case GridBlank:
            color = GRID_BLANK_COLOR;
            break;
        case SnakeHead: {
            IMAGE img;
            switch (snakeCategory) {
                case SnakeA:
                    switch (direction) {
                        case Up:
                            loadimage(&img, _T("data/snake_A_head_up.png"));
                            break;
                        case Down:
                            loadimage(&img, _T("data/snake_A_head_down.png"));
                            break;
                        case Left:
                            loadimage(&img, _T("data/snake_A_head_left.png"));
                            break;
                        case Right:
                            loadimage(&img, _T("data/snake_A_head_right.png"));
                            break;
                        default:
                            exit(-1);
                    }
                    break;
                case SnakeB:
                    switch (direction) {
                        case Up:
                            loadimage(&img, _T("data/snake_B_head_up.png"));
                            break;
                        case Down:
                            loadimage(&img, _T("data/snake_B_head_down.png"));
                            break;
                        case Left:
                            loadimage(&img, _T("data/snake_B_head_left.png"));
                            break;
                        case Right:
                            loadimage(&img, _T("data/snake_B_head_right.png"));
                            break;
                        default:
                            exit(-1);
                    }
                    break;
                default:
                    exit(-1);
            }
            putimage(x, y, &img);
            return;
        }
        case SnakeBody:
            switch (snakeCategory) {
                case SnakeA:
                    color = SNAKE_A_COLOR;
                    break;
                case SnakeB:
                    color = SNAKE_B_COLOR;
                    break;
                default:
                    exit(-1);
            }
            break;
        case GridWall:
            color = GRID_WALL_COLOR;
            break;
        case GoodFood:
            color = GOOD_FOOD_COLOR;
            break;
        case BadFood:
            color = BAD_FOOD_COLOR;
            break;
        case GridObstacle:
            color = GRID_OBSTACLE_COLOR;
            break;
        case GreatFood:
            color = GREAT_FOOD_COLOR;
            break;
        case BoomFood:
            color = BOOM_FOOD_COLOR;
            break;
        default:
            exit(-1);
    }

    /* Print grid status */
    setfillcolor(color);
    solidrectangle(x, y, x + gridSideLength - 1, y + gridSideLength - 1);
}