/****************************************************************
 * Project Name:  Tic_Tac_Toe
 * File Name:     tic_tac_toe.h
 * File Function: �㷨���������庯�������ߺ�����ͷ�ļ�
 * Author:        Jishen Lin (�ּ���)
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