/****************************************************************
 * Project Name:  Tetris
 * File Name:     tetris_control.cpp
 * File Function: Control类的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/10/1
 ****************************************************************/

#include "tetris.h"

using namespace std;

/*
 * Function Name:    Control
 * Function:         Constructed function
 * Notes:            Class external implementation of member functions
 */
Control::Control()
{
    print_hold_block();
    print_next_blocks();
}

/*
 * Function Name:    print_hold_block
 * Function:         Print hold block
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void Control::print_hold_block(void)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            print_grid_status(i + 4, j + gridCol + 1, GRID_BLANK_COLOR);
    for (int i = 0; i < hold.getBlock().size(); i++)
        print_grid_status(hold.getBlock()[i][0] + 4, hold.getBlock()[i][1] + gridCol + 1, hold.getColor());
}

/*
 * Function Name:    print_next_blocks
 * Function:         Print next blocks
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void Control::print_next_blocks(void)
{
    for (int k = 0; k < 3; k++) {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                print_grid_status(i + 10 + 5 * k, j + gridCol + 1, GRID_BLANK_COLOR);
        for (int i = 0; i < next[k].getBlock().size(); i++)
            print_grid_status(next[k].getBlock()[i][0] + 10 + 5 * k, next[k].getBlock()[i][1] + gridCol + 1, next[k].getColor());
    }
}

/*
 * Function Name:    rotate_current
 * Function:         Rotate current block clockwise
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void Control::rotate_current(void)
{
    current.rotate();
}