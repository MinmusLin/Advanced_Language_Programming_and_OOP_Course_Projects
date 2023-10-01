/****************************************************************
 * Project Name:  Tetris
 * File Name:     tetris_control.cpp
 * File Function: Control类的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/10/2
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
    /* Allocate dynamic memory for map */
    map = new(nothrow) bool* [gridRow];
    if (map == NULL)
        exit(-1);
    for (int i = 0; i < gridRow; i++) {
        map[i] = new(nothrow) bool[gridCol];
        if (map[i] == NULL)
            exit(-1);
    }

    /* Set all elements to false */
    for (int i = 0; i < gridRow; i++)
        memset(map[i], 0, sizeof(bool) * gridCol);

    /* Allocate dynamic memory for color */
    color = new(nothrow) COLORREF* [gridRow];
    if (color == NULL)
        exit(-1);
    for (int i = 0; i < gridRow; i++) {
        color[i] = new(nothrow) COLORREF[gridCol];
        if (color[i] == NULL)
            exit(-1);
    }

    /* Set all elements to GRID_BLANK_COLOR */
    for (int i = 0; i < gridRow; i++)
        for (int j = 0; j < gridCol; j++)
            color[i][j] = GRID_BLANK_COLOR;
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
    for (int i = 0; i < gridRow; i++)
        delete[] color[i];
    delete[] color;
}

/*
 * Function Name:    getCurrentBlock
 * Function:         Get private current block variable
 * Input Parameters: void
 * Return Value:     private current block variable
 * Notes:            Class external implementation of member functions
 */
const Block& Control::getCurrentBlock(void) const
{
    return current;
}

/*
 * Function Name:    printHoldBlock
 * Function:         Print hold block
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void Control::printHoldBlock(void)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            printGridStatus(i + 4, j + gridCol + 1, GRID_BLANK_COLOR);
    for (int i = 0; i < static_cast<int>(hold.getBlock().size()); i++)
        printGridStatus(hold.getBlock()[i][0] + 4, hold.getBlock()[i][1] + gridCol + 1, hold.getColor());
}

/*
 * Function Name:    printNextBlocks
 * Function:         Print next blocks
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void Control::printNextBlocks(void)
{
    for (int k = 0; k < 3; k++) {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                printGridStatus(i + 10 + 5 * k, j + gridCol + 1, GRID_BLANK_COLOR);
        for (int i = 0; i < static_cast<int>(next[k].getBlock().size()); i++)
            printGridStatus(next[k].getBlock()[i][0] + 10 + 5 * k, next[k].getBlock()[i][1] + gridCol + 1, next[k].getColor());
    }
}

/*
 * Function Name:    rotateCurrentClockwise
 * Function:         Rotate current block clockwise
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void Control::rotateCurrentClockwise(void)
{
    current.rotateClockwise();
}

/*
 * Function Name:    rotateCurrentAnticlockwise
 * Function:         Rotate current block anticlockwise
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void Control::rotateCurrentAnticlockwise(void)
{
    current.rotateAnticlockwise();
}

/*
 * Function Name:    printBlock
 * Function:         Print block
 * Input Parameters: int row
 *                   int col
 *                   bool is_blank
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
bool Control::printBlock(int row, int col, bool is_blank)
{
    /* Save temporary map */
    bool tmpMap[4][4];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            tmpMap[i][j] = true;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (row + i >= 0 && row + i < gridRow && col + j >= 0 && col + j < gridCol)
                tmpMap[i][j] = map[row + i][col + j];

    /* Check if the position is suitable for placing a block */
    for (int i = 0; i < static_cast<int>(current.getBlock().size()); i++)
        if (tmpMap[current.getBlock()[i][0]][current.getBlock()[i][1]])
            return false;

    /* If the position can accommodate a block, print the block */
    for (int i = 0; i < static_cast<int>(current.getBlock().size()); i++)
        printGridStatus(current.getBlock()[i][0] + row, current.getBlock()[i][1] + col, is_blank ? GRID_BLANK_COLOR : current.getColor());
    return true;
}

/*
 * Function Name:    refreshBlocks
 * Function:         Refresh blocks
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void Control::refreshBlocks(void)
{
    Block newBlock;
    current = next[0];
    next[0] = next[1];
    next[1] = next[2];
    next[2] = newBlock;
}

/*
 * Function Name:    refresh map
 * Function:         Refresh map
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void Control::refreshMap(int row, int col)
{
    for (int i = 0; i < static_cast<int>(current.getBlock().size()); i++) {
        map[row + current.getBlock()[i][0]][col + current.getBlock()[i][1]] = true;
        color[row + current.getBlock()[i][0]][col + current.getBlock()[i][1]] = current.getColor();
    }
}

/*
 * Function Name:    changeCurrentAndHold
 * Function:         Change current block and hold block
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void Control::changeCurrentAndHold(void)
{
    Block tmp = current;
    current = hold;
    hold = tmp;
}