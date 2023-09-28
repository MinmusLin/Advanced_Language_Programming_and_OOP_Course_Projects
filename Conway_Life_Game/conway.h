/****************************************************************
 * Project Name:  Conway_Life_Game
 * File Name:     conway.h
 * File Function: Conway类、图形化界面函数、主体函数的头文件
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/9/28
 ****************************************************************/

#pragma once
#include <iostream>

/* Define RGB color */
#define GRID_LINE_COLOR RGB(210, 210, 210)
#define GRID_BLANK_COLOR RGB(255, 255, 255)
#define GRID_ALIVE_COLOR RGB(130, 130, 130)

/* Define constant int variables */
const int gridRow = 75;
const int gridCol = 150;
const int gridSideLength = 10;
const int gridSpace = 1;
const int topGridMargin = 0;
const int bottomGridMargin = 0;
const int leftGridMargin = 0;
const int rightGridMargin = 0;
const int delayTime = 50;
const int initialAliveCount = gridRow * gridCol / 15;

/* Function declarations in conway_graphics.cpp */
void initialize_graphics(void);
void print_grid_status(int row, int col, bool is_alive);

/* Define Conway class */
class Conway {
private:
    /* Define private data member */
    bool** map;

    /*
     * Function Name:    countAlive
     * Function:         Count alive grids
     * Input Parameters: int row
     *                   int col
     * Return Value:     the number of alive grids
     */
    int countAlive(int row, int col)
    {
        /* Define the eight possible directions */
        int directions[8][2] = { {-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1} };

        /* Check if the element at the new position is true */
        int count = 0;
        for (int i = 0; i < 8; i++) {
            int newRow = row + directions[i][0], newCol = col + directions[i][1];
            if (newRow >= 0 && newRow < gridRow && newCol >= 0 && newCol < gridCol && map[newRow][newCol])
                count++;
        }
        return count;
    }

public:
    /*
     * Function Name:    Conway
     * Function:         Constructed function
     * Input Parameters: int initAlive
     */
    Conway(int initAlive)
    {
        /* Allocate dynamic memory for map */
        map = new(std::nothrow) bool* [gridRow];
        if (map == NULL)
            exit(-1);
        for (int i = 0; i < gridRow; i++) {
            map[i] = new(std::nothrow) bool[gridCol];
            if (map[i] == NULL)
                exit(-1);
        }

        /* Set all elements to false */
        for (int i = 0; i < gridRow; i++)
            memset(map[i], 0, sizeof(bool) * gridCol);

        /* Generate initial alive grids */
        int count = 0;
        while (true) {
            int r = rand() % gridRow, c = rand() % gridCol;
            if (!map[r][c]) {
                map[r][c] = true;
                count++;
                print_grid_status(r, c, true);
            }
            if (count == initAlive || count == gridRow * gridCol)
                return;
        }
    }

    /*
     * Function Name:    ~Conway
     * Function:         Destructor
     */
    ~Conway()
    {
        for (int i = 0; i < gridRow; i++)
            delete[] map[i];
        delete[] map;
    }

    /*
     * Function Name:    refreshMap
     * Function:         Count alive grids and refresh map
     * Input Parameters: void
     * Return Value:     void
     */
    void refreshMap(void)
    {
        for (int i = 0; i < gridRow; i++)
            for (int j = 0; j < gridCol; j++) {
                int n = countAlive(i, j);
                if (map[i][j]) {
                    if (n < 2 || n > 3) {
                        map[i][j] = false;
                        print_grid_status(i, j, false);
                    }
                }
                else {
                    if (n == 3) {
                        map[i][j] = true;
                        print_grid_status(i, j, true);
                    }
                }
            }
    }
};