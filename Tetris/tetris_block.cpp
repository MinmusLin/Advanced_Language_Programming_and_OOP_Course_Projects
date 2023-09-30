/****************************************************************
 * Project Name:  Tetris
 * File Name:     tetris_block.cpp
 * File Function: Block类的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/10/1
 ****************************************************************/

#include "tetris.h"

using namespace std;

/*
 * Function Name:    Block
 * Function:         Constructed function
 * Notes:            Class external implementation of member functions
 */
Block::Block()
{
    category = rand() % blockCategory.size();
    direction = rand() % blockCategory[category].size();
    color = Color[rand() % colorNum];
    block = blockCategory[category][direction];
}

/*
 * Function Name:    getBlock
 * Function:         Get private block variable
 * Input Parameters: void
 * Return Value:     private block variable
 * Notes:            Class external implementation of member functions
 */
const vector<vector<int>>& Block::getBlock(void) const
{
    return block;
}

/*
 * Function Name:    getColor
 * Function:         Get private color variable
 * Input Parameters: void
 * Return Value:     private color variable
 * Notes:            Class external implementation of member functions
 */
const COLORREF Block::getColor(void) const
{
    return color;
}

/*
 * Function Name:    rotate
 * Function:         Rotate the current direction clockwise
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void Block::rotate(void)
{
    if (direction + 1 == blockCategory[category][direction].size())
        direction = 0;
    else
        direction++;
    block = blockCategory[category][direction];
}