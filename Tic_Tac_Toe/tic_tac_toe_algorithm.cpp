/****************************************************************
 * Project Name:  Tic_Tac_Toe
 * File Name:     tic_tac_toe_algorithm.cpp
 * File Function: 算法函数的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/11/21
 ****************************************************************/

#include <Windows.h>
#include "tic_tac_toe.h"

using namespace std;

/*
 * Function Name:    find_next_move_to_win
 * Function:         Find next move to win
 * Input Parameters: const GridStatus gridStatus[][BOARD_SIZE]
 *                   int& row
 *                   int& col
 * Return Value:     next winning grid status
 */
GridStatus find_next_move_to_win(const GridStatus gridStatus[][BOARD_SIZE], int& row, int& col)
{
    /* Initialize temporary grid to simulate moves */
    GridStatus tmpGridStatus[BOARD_SIZE][BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            tmpGridStatus[i][j] = gridStatus[i][j];

    /* Iterate over empty positions to simulate possible moves */
    for (int k = 1; k <= 2; k++)
        for (int i = 0; i < BOARD_SIZE; i++)
            for (int j = 0; j < BOARD_SIZE; j++)
                if (tmpGridStatus[i][j] == Empty) {
                    tmpGridStatus[i][j] = static_cast<GridStatus>(k);
                    GridStatus winner = check_win(tmpGridStatus);
                    if (winner == Empty) {
                        tmpGridStatus[i][j] = Empty;
                        continue;
                    }
                    else {
                        row = i;
                        col = j;
                        return winner;
                    }
                }

    /* If no winning or blocking move is found, choose a empty position */
    const int preferredPositions[BOARD_SIZE * BOARD_SIZE][2] = {
        {1, 1}, // Center
        {0, 1}, // Middle row
        {1, 0}, // Middle column
        {2, 1}, // Bottom row
        {1, 2}, // Rightmost column
        {0, 0}, // Top left corner
        {0, 2}, // Top right corner
        {2, 0}, // Bottom left corner
        {2, 2}  // Bottom right corner
    };
    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
        int r = preferredPositions[i][0], c = preferredPositions[i][1];
        if (tmpGridStatus[r][c] == Empty) {
            row = r;
            col = c;
            break;
        }
    }
    return Empty;
}