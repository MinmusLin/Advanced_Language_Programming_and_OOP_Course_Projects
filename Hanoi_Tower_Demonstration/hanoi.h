/****************************************************************
 * Project Name:  Hanoi_Tower_Demonstration
 * File Name:     hanoi.h
 * File Function: 主体函数、菜单函数、汉诺塔综合演示解决方案函数的头文件
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/11/21
 ****************************************************************/

#pragma once
#ifndef HANOI_H
#define HANOI_H

/* Macro definition */
#define stack_top 10

/* Function declaration in hanoi_menu.cpp */
int menu(void);

/* Function declarations in hanoi_solution.cpp */
int strcasecmp(const char s1[], const char s2[]);
void wait_for_enter(int prompt_output);
void delay(int delay_optn, int singleStepDemo_or_not, int printMoveProcess_or_not);
void parameters_input(int* p_n, char* p_src, char* p_tmp, char* p_dst, int* p_delay_optn, int delay_or_not);
void initialize(void);
void stack_initialize(int n, char src);
void stack_move(char src, char dst, int roll_back);
void print_stack_horizontal(void);
void print_stack_vertical_initial(int n, char src, char dst, int printMoveProcess_or_not);
void print_stack_vertical(char src, char dst, int printMoveProcess_or_not);
void print_horizontal_vertical_moveProcess(int n, char src, char dst, int printSteps_or_not, int printHorizontal_or_not, int printVertical_or_not, int singleStepDemo_or_not, int printMoveProcess_or_not);
void print_horizontal(int n, char src, char dst, int printSteps_or_not, int printHorizontal_or_not);
void hanoi(int n, char src, char tmp, char dst, int printSteps_or_not, int printHorizontal_or_not, int printVertical_or_not, int singleStepDemo_or_not, int printMoveProcess_or_not);
int color_match(int n);
void print_cylinders(void);
void print_plates(void);
void print_moveProcess_all(int n, char src, char dst, int num, int firstMove_or_not);
void print_moveProcess_vertical(char src_or_dst, int num, int up_or_dowm);
void print_moveProcess_horizontal(char src, char dst, int num);
void print_moveProcess_game(int n, char src, char dst);
void optn_1_fundamentSolution_base(void);
void optn_2_fundamentSolution_stepRecord(void);
void optn_3_arrayDisplay_horizontal(void);
void optn_4_arrayDisplay_horizontalVertical(void);
void optn_5_graphicalSolution_printCylinders(void);
void optn_6_graphicalSolution_printPlates(void);
void optn_7_graphicalSolution_firstMove(void);
void optn_8_graphicalSolution_autoMove(void);
void optn_9_graphicalSolution_game(void);

#endif // !HANOI_H