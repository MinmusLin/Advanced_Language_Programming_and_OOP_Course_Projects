/****************************************************************
 * Project Name:  Gluttonous_Snake
 * File Name:     gluttonous_snake_game.cpp
 * File Function: 游戏函数的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/9/24
 ****************************************************************/

#include <conio.h>
#include "gluttonous_snake.h"
using namespace std;

/*
 * Function Name:    getDirection
 * Function:         Read keyboard events to get direction
 * Input Parameters: Direction& direction_A
 *                   Direction& direction_B
 * Return Value:     void
 */
static void getDirection(Direction& direction_A, Direction& direction_B)
{
    if (_kbhit()) {
        int key = _getch();
        if (key == 0 || key == 0xE0) {
            key = _getch();
            if (key == 'H' && direction_B != Down)
                direction_B = Up;
            else if (key == 'P' && direction_B != Up)
                direction_B = Down;
            else if (key == 'K' && direction_B != Right)
                direction_B = Left;
            else if (key == 'M' && direction_B != Left)
                direction_B = Right;
        }
        else {
            if ((key == 'W' || key == 'w') && direction_A != Down)
                direction_A = Up;
            else if ((key == 'S' || key == 's') && direction_A != Up)
                direction_A = Down;
            else if ((key == 'A' || key == 'a') && direction_A != Right)
                direction_A = Left;
            else if ((key == 'D' || key == 'd') && direction_A != Left)
                direction_A = Right;
        }
    }
}

/*
 * Function Name:    gluttonous_snake
 * Function:         Play gluttonous snake game
 * Input Parameters: Mode mode
 * Return Value:     void
 */
void gluttonous_snake(Mode mode)
{
    /* Process initialization work */
    initialize_graphics(mode);
    Control control(mode);
    EndPageCategory endPageCategory = PageDefault;
    bool flag = true;
    int lastLength = 1;

    /* Play gluttonous snake game */
    if (mode == BasicMode || mode == AdvancedMode || mode == ExpertMode) {
        while (flag) {
            /* Check if the snake has been successfully generated */
            bool is_generate = control.Snake_A.generateSnake();
            if (!is_generate) {
                if (mode == AdvancedMode)
                    control.Snake_A.correct(lastLength);
                break;
            }
            Sleep(timeThreshold);

            /* Move the snake */
            while (true) {
                /* Check if the screen has no space to generate food */
                if (control.Snake_A.getLength() == (gridRow - 2) * (gridCol - 2)) {
                    flag = false;
                    break;
                }

                /* Generate specific grid condition */
                for (int i = GoodFood; i <= GridObstacle; i++)
                    control.generateGrid((GridCondition)i);

                /* Print information */
                control.print_information();

                /* Get snake head direction */
                Direction direction = control.Snake_A.getSnakeDirection();
                getDirection(direction, direction);

                /* Change snake direction */
                if (!control.Snake_A.changeDirection(direction)) {
                    control.print_information();
                    break;
                }
                Sleep(timeThreshold);
            }

            /* Handle tasks after the snake's death */
            switch (mode) {
                case BasicMode:
                    flag = false;
                    break;
                case AdvancedMode:
                    control.Snake_A.changeGridCondition(GridWall);
                    control.refreshMap();
                    lastLength = control.Snake_A.getLength();
                    control.Snake_A.refreshSnake();
                    flag = true;
                    break;
                case ExpertMode:
                    control.Snake_A.changeGridCondition(GoodFood);
                    control.refreshMap();
                    lastLength = control.Snake_A.getLength();
                    control.Snake_A.refreshSnake();
                    if (control.Snake_A.getDeath() >= deathCountMaximum) {
                        control.Snake_A.correct(lastLength);
                        flag = false;
                    }
                    else
                        flag = true;
                    break;
                default:
                    exit(-1);
            }
        }
    }
    else if (mode == HumanVsHumanMode || mode == HumanVsAIMode || mode == AIVsAIMode) {
        while (flag) {
            /* Check if the snakes have been successfully generated */
            bool is_generate_A = control.Snake_A.generateSnake(true);
            bool is_generate_B = control.Snake_B.generateSnake(true);
            if (!is_generate_A || !is_generate_B)
                break;
            Sleep(mode == AIVsAIMode ? timeAIThreshold : timeThreshold);

            /* Move the snakes */
            while (true) {
                /* Check if the screen has no space to generate food */
                if (control.Snake_A.getLength() + control.Snake_B.getLength() == (gridRow - 2) * (gridCol - 2)) {
                    flag = false;
                    break;
                }

                /* Generate specific grid condition */
                for (int i = GoodFood; i <= GridObstacle; i++)
                    control.generateGrid((GridCondition)i);

                /* Print information */
                control.print_information();

                /* Get snake head direction */
                Direction direction_A = control.Snake_A.getSnakeDirection();
                Direction direction_B = control.Snake_B.getSnakeDirection();
                switch (mode) {
                    case HumanVsHumanMode:
                        getDirection(direction_A, direction_B);
                        break;
                    case HumanVsAIMode:
                        getDirection(direction_A, direction_A);
                        direction_B = control.Snake_B.BFS();
                        break;
                    case AIVsAIMode:
                        direction_A = control.Snake_A.BFS();
                        direction_B = control.Snake_B.BFS();
                        break;
                    default:
                        exit(-1);
                }

                /* Change snake direction */
                if (!control.Snake_A.changeDirection(direction_A)) {
                    control.print_information();
                    flag = false;
                    switch (mode) {
                        case HumanVsHumanMode:
                            endPageCategory = PageHumanSnakeB;
                            break;
                        case HumanVsAIMode:
                            endPageCategory = PageAISnakeB;
                            break;
                        case AIVsAIMode:
                            endPageCategory = PageAISnakeB;
                            break;
                        default:
                            exit(-1);
                    }
                    break;
                }
                if (!control.Snake_B.changeDirection(direction_B)) {
                    control.print_information();
                    flag = false;
                    switch (mode) {
                        case HumanVsHumanMode:
                            endPageCategory = PageHumanSnakeA;
                            break;
                        case HumanVsAIMode:
                            endPageCategory = PageHumanSnakeA;
                            break;
                        case AIVsAIMode:
                            endPageCategory = PageAISnakeA;
                            break;
                        default:
                            exit(-1);
                    }
                    break;
                }
                Sleep(mode == AIVsAIMode ? timeAIThreshold : timeThreshold);
            }
        }
    }
    else
        exit(-1);

    /* Print information */
    control.print_information();

    /* Update highest score */
    if (control.getHighestScore() > readHighestScore(mode))
        updateHighestScore(mode, control.getHighestScore());

    /* Display end page */
    endPage(endPageCategory);
}