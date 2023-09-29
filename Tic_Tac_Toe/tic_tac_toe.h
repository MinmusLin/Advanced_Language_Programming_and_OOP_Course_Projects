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

/* Function declarations in tic_tac_toe_tools.cpp */
int menu(void);
void print_grid_status(GridStatus gridStatus[][BOARD_SIZE]);
int input_digit(int lowerLimit, int upperLimit);