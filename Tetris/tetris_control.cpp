/****************************************************************
 * Project Name:  Tetris
 * File Name:     tetris_control.cpp
 * File Function: Control类的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/11/21
 ****************************************************************/

#include "tetris.h"

/* Namespace */
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

    /* Complete the preparations */
    resetCurrentRowAndCol();
    printEliminatedLines(0, true);
    printScore(0, true);
    refreshMap();
    printHoldBlock();
    printNextBlocks();
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
 * Function Name:    getScore
 * Function:         Get private score variable
 * Input Parameters: void
 * Return Value:     private score variable
 * Notes:            Class external implementation of member functions
 */
const int& Control::getScore(void) const
{
    return score;
}

/*
 * Function Name:    getCurrentRow
 * Function:         Get private current row variable
 * Input Parameters: void
 * Return Value:     private current row variable
 * Notes:            Class external implementation of member functions
 */
const int& Control::getCurrentRow(void) const
{
    return currentRow;
}

/*
 * Function Name:    getCurrentCol
 * Function:         Get private current column variable
 * Input Parameters: void
 * Return Value:     private current column variable
 * Notes:            Class external implementation of member functions
 */
const int& Control::getCurrentCol(void) const
{
    return currentCol;
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
 * Function Name:    refreshBlock
 * Function:         Refresh block
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void Control::refreshBlock(int row, int col)
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
    swap(current, hold);
}

/*
 * Function Name:    eliminateLines
 * Function:         Eliminate lines
 * Input Parameters: void
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
bool Control::eliminateLines(void)
{
    /* Set whether to refresh the map flag */
    bool flag = false;

    /* Eliminate lines */
    int lines = 0;
    for (int i = gridRow - 1; i >= 0; i--) {
        bool is_true = true;
        for (int j = 0; j < gridCol; j++)
            if (!map[i][j]) {
                is_true = false;
                break;
            }
        if (is_true) {
            eliminatedLines++;
            lines++;
            flag = true;
            for (int j = 0; j < gridCol; j++) {
                map[i][j] = false;
                color[i][j] = GRID_BLANK_COLOR;
            }
        }
    }

    /* Allocate dynamic memory for line status */
    bool* lineStatus = new(nothrow) bool[gridRow] {false};
    if (lineStatus == NULL)
        exit(-1);

    /* Calculate line status */
    for (int i = 0; i < gridRow; i++)
        for (int j = 0; j < gridCol; j++)
            if (map[i][j]) {
                lineStatus[i] = true;
                break;
            }

    /* Drop lines */
    for (int i = gridRow - 1; i >= 0; i--)
        if (lineStatus[i]) {
            int dropCount = 0;
            for (int j = i + 1; j < gridRow; j++) {
                if (!lineStatus[j])
                    dropCount++;
                else
                    break;
            }
            if (dropCount > 0)
                swap(lineStatus[i], lineStatus[i + dropCount]);
                for (int j = 0; j < gridCol; j++) {
                    swap(map[i][j], map[i + dropCount][j]);
                    swap(color[i][j], color[i + dropCount][j]);
                }
        }

    /* Update score */
    switch (lines) {
        case 0:
            break;
        case 1:
            score += oneLineScore;
            break;
        case 2:
            score += twoLinesScore;
            break;
        case 3:
            score += threeLinesScore;
            break;
        case 4:
            score += fourLinesScore;
            break;
        default:
            exit(-1);
    }

    /* Free dynamic memory */
    delete[] lineStatus;

    /* Return whether to refresh the map flag */
    return flag;
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
    printEliminatedLines(eliminatedLines);
    printScore(score);
    for (int i = 0; i < gridRow; i++)
        for (int j = 0; j < gridCol; j++)
            printGridStatus(i, j, color[i][j]);
}

/*
 * Function Name:    resetCurrentRowAndCol
 * Function:         Reset current row and column
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void Control::resetCurrentRowAndCol(void)
{
    currentRow = -blockLimits[getCurrentBlock().getCategory()][getCurrentBlock().getDirection()][0][0];
    currentCol = gridCol / 2 - 2;
}

/*
 * Function Name:    rotateRight
 * Function:         Rotate right
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void Control::rotateRight(void)
{
    printBlock(currentRow, currentCol, true);
    rotateCurrentClockwise();
    if (!printBlock(currentRow, currentCol)) {
        rotateCurrentAnticlockwise();
        printBlock(currentRow, currentCol);
    }
}

/*
 * Function Name:    softDrop
 * Function:         Soft drop
 * Input Parameters: void
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
bool Control::softDrop(void)
{
    printBlock(currentRow, currentCol, true);
    currentRow++;
    if (!printBlock(currentRow, currentCol)) {
        currentRow--;
        printBlock(currentRow, currentCol);
        refreshBlock(currentRow, currentCol);
        return true;
    }
    return false;
}

/*
 * Function Name:    moveLeft
 * Function:         Move left
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void Control::moveLeft(void)
{
    if (currentCol >= 1 - blockLimits[getCurrentBlock().getCategory()][getCurrentBlock().getDirection()][0][1]) {
        printBlock(currentRow, currentCol, true);
        currentCol--;
        if (!printBlock(currentRow, currentCol)) {
            currentCol++;
            printBlock(currentRow, currentCol);
        }
    }
}

/*
 * Function Name:    moveRight
 * Function:         Move Right
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void Control::moveRight(void)
{
    if (currentCol <= gridCol - blockLimits[getCurrentBlock().getCategory()][getCurrentBlock().getDirection()][1][1] - 2) {
        printBlock(currentRow, currentCol, true);
        currentCol++;
        if (!printBlock(currentRow, currentCol)) {
            currentCol--;
            printBlock(currentRow, currentCol);
        }
    }
}

/*
 * Function Name:    changeHold
 * Function:         Change hold
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void Control::changeHold(void)
{
    printBlock(currentRow, currentCol, true);
    changeCurrentAndHold();
    printBlock(currentRow, currentCol);
    printHoldBlock();
}

/*
 * Function Name:    rotateLeft
 * Function:         Rotate left
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void Control::rotateLeft(void)
{
    printBlock(currentRow, currentCol, true);
    rotateCurrentAnticlockwise();
    if (!printBlock(currentRow, currentCol)) {
        rotateCurrentClockwise();
        printBlock(currentRow, currentCol);
    }
}

/*
 * Function Name:    hardDrop
 * Function:         Hard drop
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void Control::hardDrop(void)
{
    while (true) {
        printBlock(currentRow, currentCol, true);
        currentRow++;
        if (!printBlock(currentRow, currentCol)) {
            currentRow--;
            printBlock(currentRow, currentCol);
            refreshBlock(currentRow, currentCol);
            break;
        }
    }
}