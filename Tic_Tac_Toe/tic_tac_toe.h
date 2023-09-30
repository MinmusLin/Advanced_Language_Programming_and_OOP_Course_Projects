/****************************************************************
 * Project Name:  Tic_Tac_Toe
 * File Name:     tic_tac_toe.h
 * File Function: 算法函数、主体函数、工具函数的头文件
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/9/30
 ****************************************************************/

#pragma once

/* Macro definition */
#define BOARD_SIZE 3

/* Define constant enum variable */
const enum GridStatus { Empty, FirstPlayer, SecondPlayer };

/* Function declaration in tic_tac_toe_algorithm.cpp */
GridStatus find_next_move_to_win(const GridStatus gridStatus[][BOARD_SIZE], int& row, int& col);

/* Function declarations in tic_tac_toe_tools.cpp */
int menu(void);
void print_grid_status(const GridStatus gridStatus[][BOARD_SIZE]);
int input_digit(int lowerLimit, int upperLimit);
GridStatus check_win(const GridStatus grid[][BOARD_SIZE]);
void print_winner(GridStatus winner);