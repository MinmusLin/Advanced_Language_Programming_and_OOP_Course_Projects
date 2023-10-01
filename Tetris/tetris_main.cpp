/****************************************************************
 * Project Name:  Tetris
 * File Name:     tetris_main.cpp
 * File Function: 主体函数的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/10/2
 ****************************************************************/

#include <ctime>
#include <conio.h>
#include "tetris.h"

using namespace std;

/*
 * Function Name:    main
 * Function:         Main function
 * Return Value:     0
 */
int main()
{
    /* Generate random number seed */
    srand((unsigned int)(time(0)));

    /* Process initialization work */
    initializeGraphics();

    /* Define control object */
    Control control;

    /* Play Tetris game */
    DWORD startTime = GetTickCount();
    int count = 1;
    while (true) {
        if (count > 1) {
            control.refreshBlocks();
            count++;
        }
        control.printHoldBlock();
        control.printNextBlocks();
        int row = -blockLimits[control.getCurrentBlock().getCategory()][control.getCurrentBlock().getDirection()][0][0], col = gridCol / 2 - 2;
        control.printBlock(row, col);
        while (true) {
            if (_kbhit()) {
                int key = _getch();
                if (key == 0 || key == 0xE0) {
                    key = _getch();
                    if (key == 'H') { // Rotate right
                        control.printBlock(row, col, true);
                        control.rotateCurrentClockwise();
                        if (!control.printBlock(row, col)) {
                            control.rotateCurrentAnticlockwise();
                            control.printBlock(row, col);
                        }
                    }
                    else if (key == 'P') { // Soft drop
                        control.printBlock(row, col, true);
                        row++;
                        if (!control.printBlock(row, col)) {
                            row--;
                            control.printBlock(row, col);
                            control.refreshMap(row, col);
                            break;
                        }
                    }
                    else if (key == 'K') { // Move left
                        if (col >= 1 - blockLimits[control.getCurrentBlock().getCategory()][control.getCurrentBlock().getDirection()][0][1]) {
                            control.printBlock(row, col, true);
                            col--;
                            if (!control.printBlock(row, col)) {
                                col++;
                                control.printBlock(row, col);
                            }
                        }
                    }
                    else if (key == 'M') { // Move Right
                        if (col <= gridCol - blockLimits[control.getCurrentBlock().getCategory()][control.getCurrentBlock().getDirection()][1][1] - 2) {
                            control.printBlock(row, col, true);
                            col++;
                            if (!control.printBlock(row, col)) {
                                col--;
                                control.printBlock(row, col);
                            }
                        }
                    }
                }
                else {
                    if (key == 'W' || key == 'w') { // Rotate right
                        control.printBlock(row, col, true);
                        control.rotateCurrentClockwise();
                        if (!control.printBlock(row, col)) {
                            control.rotateCurrentAnticlockwise();
                            control.printBlock(row, col);
                        }
                    }
                    else if (key == 'S' || key == 's') { // Soft drop
                        control.printBlock(row, col, true);
                        row++;
                        if (!control.printBlock(row, col)) {
                            row--;
                            control.printBlock(row, col);
                            control.refreshMap(row, col);
                            break;
                        }
                    }
                    else if (key == 'A' || key == 'a') { // Move left
                        if (col >= 1 - blockLimits[control.getCurrentBlock().getCategory()][control.getCurrentBlock().getDirection()][0][1]) {
                            control.printBlock(row, col, true);
                            col--;
                            if (!control.printBlock(row, col)) {
                                col++;
                                control.printBlock(row, col);
                            }
                        }
                    }
                    else if (key == 'D' || key == 'd') { // Move Right
                        if (col <= gridCol - blockLimits[control.getCurrentBlock().getCategory()][control.getCurrentBlock().getDirection()][1][1] - 2) {
                            control.printBlock(row, col, true);
                            col++;
                            if (!control.printBlock(row, col)) {
                                col--;
                                control.printBlock(row, col);
                            }
                        }
                    }
                    else if (key == 'C' || key == 'c') { // Hold
                        control.printBlock(row, col, true);
                        control.changeCurrentAndHold();
                        control.printBlock(row, col);
                        control.printHoldBlock();
                    }
                    else if (key == 'Z' || key == 'z') { // Rotate left
                        control.printBlock(row, col, true);
                        control.rotateCurrentAnticlockwise();
                        if (!control.printBlock(row, col)) {
                            control.rotateCurrentClockwise();
                            control.printBlock(row, col);
                        }
                    }
                    else if (key == ' ') { // Hard drop
                        while (true) {
                            control.printBlock(row, col, true);
                            row++;
                            if (!control.printBlock(row, col)) {
                                row--;
                                control.printBlock(row, col);
                                control.refreshMap(row, col);
                                break;
                            }
                        }
                    }
                    else if (key == KEYBOARD_ESC) { // Quit
                        return 0;
                    }
                }
            }
            if (static_cast<int>(GetTickCount() - startTime) >= 500 * count) {
                control.printBlock(row, col, true);
                row++;
                if (!control.printBlock(row, col)) {
                    row--;
                    control.printBlock(row, col);
                    control.refreshMap(row, col);
                    break;
                }
                count++;
            }
        }
    }
}