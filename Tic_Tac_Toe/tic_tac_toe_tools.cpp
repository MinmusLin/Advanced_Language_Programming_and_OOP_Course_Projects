/****************************************************************
 * Project Name:  Tic_Tac_Toe
 * File Name:     tic_tac_toe_tools.cpp
 * File Function: 工具函数的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/11/21
 ****************************************************************/

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "..\common\cmd_console_tools.h"
#include "tic_tac_toe.h"

using namespace std;

/*
 * Function Name:    check_rows_win
 * Function:         Check for a win in rows
 * Input Parameters: const GridStatus grid[][BOARD_SIZE]
 * Return Value:     winning grid status
 */
static GridStatus check_rows_win(const GridStatus grid[][BOARD_SIZE])
{
    for (int i = 0; i < BOARD_SIZE; i++)
        if (grid[i][0] != Empty && grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2])
            return grid[i][0];
    return Empty;
}

/*
 * Function Name:    check_cols_win
 * Function:         Check for a win in columns
 * Input Parameters: const GridStatus grid[][BOARD_SIZE]
 * Return Value:     winning grid status
 */
static GridStatus check_cols_win(const GridStatus grid[][BOARD_SIZE])
{
    for (int j = 0; j < BOARD_SIZE; j++)
        if (grid[0][j] != Empty && grid[0][j] == grid[1][j] && grid[1][j] == grid[2][j])
            return grid[0][j];
    return Empty;
}

/*
 * Function Name:    check_diagonals_win
 * Function:         Check for a win in diagonals
 * Input Parameters: const GridStatus grid[][BOARD_SIZE]
 * Return Value:     winning grid status
 */
static GridStatus check_diagonals_win(const GridStatus grid[][BOARD_SIZE])
{
    if (grid[0][0] != Empty && grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2])
        return grid[0][0];
    else if (grid[0][2] != Empty && grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0])
        return grid[0][2];
    else
        return Empty;
}

/*
 * Function Name:    menu
 * Function:         Display menu items and read the correct option
 * Input Parameters: void
 * Return Value:     option
 */
int menu(void)
{
    cct_cls();
    cout << "               Tic Tac Toe" << endl;
    cout << "               井字棋游戏" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "  1.双人对战模式" << endl;
    cout << "    Player vs. Player Mode" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "  2.人机对战模式（AI先手）" << endl;
    cout << "    Player vs. AI Mode (AI Goes First)" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "  3.人机对战模式（AI后手）" << endl;
    cout << "    Player vs. AI Mode (AI Goes Second)" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "  4.AI对战模式" << endl;
    cout << "    AI vs. AI Mode" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "  0.退出" << endl;
    cout << "    Quit" << endl;
    cout << "-----------------------------------------" << endl;;
    cout << "  [请选择:] ";
    char optn;
    while (true) {
        optn = _getch();
        if (optn >= '0' && optn <= '4') {
            cout << optn << endl << endl;
            Sleep(300);
            return optn - '0';
        }
    }
}

/*
 * Function Name:    print_grid_status
 * Function:         Print grid status
 * Input Parameters: const GridStatus gridStatus[][BOARD_SIZE]
 * Return Value:     void
 */
void print_grid_status(const GridStatus gridStatus[][BOARD_SIZE])
{
    cout << "     1  2  3" << endl;
    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << "   +--+--+--+" << endl << " " << i + 1 << " ";
        for (int j = 0; j < BOARD_SIZE; j++)
            cout << "|" << (gridStatus[i][j] == Empty ? "  " : (gridStatus[i][j] == FirstPlayer ? "×" : "○"));
        cout << "|" << endl;
    }
    cout << "   +--+--+--+" << endl;
}

/*
 * Function Name:    input_digit
 * Function:         Input and return a digit
 * Input Parameters: int lowerLimit
 *                   int upperLimit
 * Return Value:     digit
 */
int input_digit(int lowerLimit, int upperLimit)
{
    while (true) {
        char optn = _getch();
        if (optn >= '0' + lowerLimit && optn <= '0' + upperLimit) {
            cout << optn << endl;
            return optn - '0';
        }
    }
}

/*
 * Function Name:    check_win
 * Function:         Check if any player has won
 * Input Parameters: const GridStatus grid[][BOARD_SIZE]
 * Return Value:     winning grid status
 */
GridStatus check_win(const GridStatus grid[][BOARD_SIZE])
{
    GridStatus rowWin = check_rows_win(grid);
    GridStatus columnWin = check_cols_win(grid);
    GridStatus diagonalWin = check_diagonals_win(grid);
    if (rowWin != Empty)
        return rowWin;
    else if (columnWin != Empty)
        return columnWin;
    else if (diagonalWin != Empty)
        return diagonalWin;
    else
        return Empty;
}

/*
 * Function Name:    print_winner
 * Function:         Print winner
 * Input Parameters: GridStatus winner
 * Return Value:     void
 */
void print_winner(GridStatus winner)
{
    if (winner == FirstPlayer || winner == SecondPlayer)
        cout << "游戏结束! " << (winner == FirstPlayer ? "先手(×)" : "后手(○)") << "胜利!" << endl << endl;
}