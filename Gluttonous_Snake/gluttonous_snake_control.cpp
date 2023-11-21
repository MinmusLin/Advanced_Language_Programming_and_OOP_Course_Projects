/****************************************************************
 * Project Name:  Gluttonous_Snake
 * File Name:     gluttonous_snake_control.cpp
 * File Function: Control类的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/11/21
 ****************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "gluttonous_snake.h"

using namespace std;

/*
 * Function Name:    allocateAndInitialize
 * Function:         Allocate dynamic memory for an integer pointer and initialize it to 0
 * Input Parameters: int*& p
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void Control::allocateAndInitialize(int*& p)
{
    p = new(nothrow) int;
    if (p == NULL)
        exit(-1);
    *p = 0;
}

/*
 * Function Name:    setObstacles
 * Function:         Set map obstacles
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void Control::setObstacles(void)
{
    for (int i = 0; i < gridRow; i++) {
        map[i][0] = GridWall;
        print_grid_status(i, 0, GridWall);
        map[i][gridCol - 1] = GridWall;
        print_grid_status(i, gridCol - 1, GridWall);
    }
    for (int i = 0; i < gridCol; i++) {
        map[0][i] = GridWall;
        print_grid_status(0, i, GridWall);
        map[gridRow - 1][i] = GridWall;
        print_grid_status(gridRow - 1, i, GridWall);
    }
}

/*
 * Function Name:    count
 * Function:         Count specific grid condition
 * Input Parameters: GridCondition gridCondition
 * Return Value:     the number of specific grid condition
 * Notes:            Class external implementation of member functions
 */
int Control::count(GridCondition gridCondition)
{
    int blanks = 0;
    for (int i = 1; i < gridRow - 1; i++)
        for (int j = 1; j < gridCol - 1; j++)
            if (map[i][j] == gridCondition)
                blanks++;
    return blanks;
}

/*
 * Function Name:    Control
 * Function:         Constructed function
 * Input Parameters: Mode _mode
 * Notes:            Class external implementation of member functions
 */
Control::Control(Mode _mode)
{
    /* Set snake category */
    Snake_A.snakeCategory = SnakeA;
    Snake_B.snakeCategory = SnakeB;

    /* Get start tick count */
    startTickCount = GetTickCount();

    /* Set game mode */
    mode = _mode;

    /* Allocate dynamic memory for map */
    map = new(nothrow) GridCondition * [gridRow];
    if (map == NULL)
        exit(-1);
    for (int i = 0; i < gridRow; i++) {
        map[i] = new(nothrow) GridCondition[gridCol];
        if (map[i] == NULL)
            exit(-1);
    }

    /* Allocate dynamic memory */
    allocateAndInitialize(pGoodFood);
    allocateAndInitialize(pGreatFood);
    allocateAndInitialize(pBadFood);
    allocateAndInitialize(pBoomFood);
    allocateAndInitialize(pObstacle);

    /* Set map blanks and obstacles */
    for (int i = 1; i < gridRow - 1; i++)
        for (int j = 1; j < gridCol - 1; j++)
            map[i][j] = GridBlank;
    setObstacles();

    /* Synchronize map's starting address */
    Snake_A.map = map;
    Snake_A.pGoodFood = pGoodFood;
    Snake_A.pGreatFood = pGreatFood;
    Snake_A.pBadFood = pBadFood;
    Snake_A.pBoomFood = pBoomFood;
    Snake_A.pObstacle = pObstacle;
    Snake_B.map = map;
    Snake_B.pGoodFood = pGoodFood;
    Snake_B.pGreatFood = pGreatFood;
    Snake_B.pBadFood = pBadFood;
    Snake_B.pBoomFood = pBoomFood;
    Snake_B.pObstacle = pObstacle;
}

/*
 * Function Name:    ~Control
 * Function:         Destructor
 * Notes:            Class external implementation of member functions
 */
Control::~Control()
{
    for (int i = 0; i < gridRow; i++)
        delete[] map[i];
    delete[] map;
    delete pGoodFood;
    delete pGreatFood;
    delete pBadFood;
    delete pBoomFood;
    delete pObstacle;
}

/*
 * Function Name:    generateGrid
 * Function:         Generate specific grid condition
 * Input Parameters: GridCondition gridCondition
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void Control::generateGrid(GridCondition gridCondition)
{
    /* Calculate the number of food items that can be generated */
    int blanks = count(GridBlank), n;
    if (blanks == 0)
        return;
    switch (gridCondition) {
        case GoodFood:
            n = maxGoodFood - *pGoodFood;
            break;
        case BadFood:
            n = maxBadFood - *pBadFood;
            break;
        case GridObstacle:
            n = maxObstacle - *pObstacle;
            break;
        case GreatFood:
            n = maxGreatFood - *pGreatFood;
            break;
        case BoomFood:
            n = maxBoomFood - *pBoomFood;
            break;
        default:
            exit(-1);
    }
    if (n <= 0)
        return;
    else if (n > blanks)
        n = blanks;

    /* Generate good food or bad food randomly */
    for (int i = 0; i < n; i++)
        while (true) {
            int row = rand() % (gridRow - 2) + 1, col = rand() % (gridCol - 2) + 1;
            if (map[row][col] == GridBlank) {
                map[row][col] = gridCondition;
                print_grid_status(row, col, gridCondition);
                switch (gridCondition) {
                    case GoodFood:
                        (*pGoodFood)++;
                        break;
                    case BadFood:
                        (*pBadFood)++;
                        break;
                    case GridObstacle:
                        (*pObstacle)++;
                        break;
                    case GreatFood:
                        (*pGreatFood)++;
                        break;
                    case BoomFood:
                        (*pBoomFood)++;
                        break;
                    default:
                        exit(-1);
                }
                break;
            }
        }
}

/*
 * Function Name:    print_information
 * Function:         Print information
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void Control::print_information(void)
{
    TCHAR infoText[256];
    DWORD endTickCount = GetTickCount();
    int elapsedSeconds = (endTickCount - startTickCount) / 1000;
    switch (mode) {
        case BasicMode:
            _stprintf(infoText, _T("[基础模式]  游戏得分：%-*d蛇的长度：%-*d游戏时间：%02d:%02d"), dataLength, Snake_A.score, dataLength, Snake_A.length, elapsedSeconds / 60, elapsedSeconds % 60);
            break;
        case AdvancedMode:
            _stprintf(infoText, _T("[进阶模式]  游戏得分：%-*d蛇的长度：%-*d死亡次数：%-*d游戏时间：%02d:%02d"), dataLength, Snake_A.score, dataLength, Snake_A.length, dataLength, Snake_A.death, elapsedSeconds / 60, elapsedSeconds % 60);
            break;
        case ExpertMode:
            _stprintf(infoText, _T("[高级模式]  游戏得分：%-*d蛇的长度：%-*d死亡次数：%-*d游戏时间：%02d:%02d"), dataLength, Snake_A.score, dataLength, Snake_A.length, dataLength, Snake_A.death, elapsedSeconds / 60, elapsedSeconds % 60);
            break;
        case HumanVsHumanMode:
            _stprintf(infoText, _T("[双人对战模式]  蓝蛇得分：%-*d蓝蛇长度：%-*d粉蛇得分：%-*d粉蛇长度：%-*d游戏时间：%02d:%02d"), dataLength, Snake_A.score, dataLength, Snake_A.length, dataLength, Snake_B.score, dataLength, Snake_B.length, elapsedSeconds / 60, elapsedSeconds % 60);
            break;
        case HumanVsAIMode:
            _stprintf(infoText, _T("[人机对战模式]  蓝蛇得分：%-*d蓝蛇长度：%-*d粉蛇(AI蛇)得分：%-*d粉蛇(AI蛇)长度：%-*d游戏时间：%02d:%02d"), dataLength, Snake_A.score, dataLength, Snake_A.length, dataLength, Snake_B.score, dataLength, Snake_B.length, elapsedSeconds / 60, elapsedSeconds % 60);
            break;
        case AIVsAIMode:
            _stprintf(infoText, _T("[AI对战模式]  蓝蛇(AI蛇)得分：%-*d蓝蛇(AI蛇)长度：%-*d粉蛇(AI蛇)得分：%-*d粉蛇(AI蛇)长度：%-*d游戏时间：%02d:%02d"), dataLength, Snake_A.score, dataLength, Snake_A.length, dataLength, Snake_B.score, dataLength, Snake_B.length, elapsedSeconds / 60, elapsedSeconds % 60);
            break;
        default:
            exit(-1);
    }
    settextstyle(&Font);
    settextcolor(BLACK);
    outtextxy(leftGridMargin, topInfoMargin, infoText);
}

/*
 * Function Name:    refreshMap
 * Function:         Refresh map
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void Control::refreshMap(void)
{
    /* Set map obstacles */
    setObstacles();

    /* Refresh the number of food and obstacles */
    *pGoodFood = count(GoodFood);
    *pGreatFood = count(GreatFood);
    *pBadFood = count(BadFood);
    *pBoomFood = count(BoomFood);
    *pObstacle = count(GridObstacle);
}

/*
 * Function Name:    getHighestScore
 * Function:         Get highest score
 * Input Parameters: void
 * Return Value:     highest score
 * Notes:            Class external implementation of member functions
 */
int Control::getHighestScore(void)
{
    return max(Snake_A.score, Snake_B.score);
}