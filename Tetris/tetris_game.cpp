/****************************************************************
 * Project Name:  Tetris
 * File Name:     tetris_game.cpp
 * File Function: 游戏函数的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/11/21
 ****************************************************************/

#include <conio.h>
#include "tetris.h"

using namespace std;

/*
 * Function Name:    tetris
 * Function:         Play Tetris game
 * Input Parameters: void
 * Return Value:     true / false
 */
bool tetris(void)
{
    Control control;
    while (true)
        if (_kbhit()) {
            int key = _getch();
            if (key != 0 && key != 0xE0 && key == '\r')
                break;
            else if (key != 0 && key != 0xE0 && key == KEYBOARD_ESC)
                return false;
        }
    DWORD startTime = GetTickCount();
    int count = 1;
    while (true) {
        if (count > 1) {
            control.refreshBlocks();
            control.printHoldBlock();
            control.printNextBlocks();
            count++;
        }
        if (control.eliminateLines())
            control.refreshMap();
        control.resetCurrentRowAndCol();
        if (!control.printBlock(control.getCurrentRow(), control.getCurrentCol())) {
            while (true)
                if (_kbhit()) {
                    int key = _getch();
                    if (key != 0 && key != 0xE0 && (key == 'R' || key == 'r'))
                        return true;
                    else if (key != 0 && key != 0xE0 && key == KEYBOARD_ESC)
                        return false;
                }
        }
        while (true) {
            if (_kbhit()) {
                int key = _getch();
                if (key == 0 || key == 0xE0) {
                    key = _getch();
                    if (key == 'H')
                        control.rotateRight();
                    else if (key == 'P') {
                        if (control.softDrop())
                            break;
                    }
                    else if (key == 'K')
                        control.moveLeft();
                    else if (key == 'M')
                        control.moveRight();
                }
                else {
                    if (key == 'W' || key == 'w')
                        control.rotateRight();
                    else if (key == 'S' || key == 's') {
                        if (control.softDrop())
                            break;
                    }
                    else if (key == 'A' || key == 'a')
                        control.moveLeft();
                    else if (key == 'D' || key == 'd')
                        control.moveRight();
                    else if (key == 'C' || key == 'c')
                        control.changeHold();
                    else if (key == 'Z' || key == 'z')
                        control.rotateLeft();
                    else if (key == ' ') {
                        control.hardDrop();
                        break;
                    }
                    else if (key == 'R' || key == 'r')
                        return true;
                    else if (key == KEYBOARD_ESC)
                        return false;
                }
            }
            if (static_cast<int>(GetTickCount() - startTime) >= delayTime * count) {
                count++;
                if (control.softDrop())
                    break;
            }
        }
    }
}