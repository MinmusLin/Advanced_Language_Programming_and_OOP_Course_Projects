/****************************************************************
 * Project Name:  Hanoi_Tower_Demonstration
 * File Name:     hanoi_solution.cpp
 * File Function: 汉诺塔综合演示解决方案函数的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/9/24
 ****************************************************************/

#include <iostream>
#include <conio.h>
#include <iomanip>
#include <Windows.h>
#include "..\common\cmd_console_tools.h"
#include "hanoi.h"
using namespace std;

/* Define static global variables */
static int counter = 0;
static int stack[3][stack_top] = { 0 };
static int top[3] = { 0 };
static int delay_optn = 0;

/*
 * Function Name:    strcasecmp
 * Function:         Comparing the sizes of strings s1 and s2, ignoring case for English letters
 * Input Parameters: const char s1[]
 *                   const char s2[]
 * Return Value:     0/The ASCII difference between the first non-equal characters
 * Notes:            If the characters at the non-equal position are different case letters, convert them to lowercase and then compare
 *                   If the characters at the non-equal position are an uppercase letter and another character, return the difference between the corresponding lowercase letter and the other character
 */
int strcasecmp(const char s1[], const char s2[])
{
    int i = 0;
    char a, b;
    while (1) {
        a = s1[i];
        b = s2[i];
        if (a >= 'A' && a <= 'Z')
            a += 32;
        if (b >= 'A' && b <= 'Z')
            b += 32;
        if (a == b) {
            if (a)
                i++;
            else
                return 0;
        }
        else
            return a - b;
    }
}

/*
 * Function Name:    wait_for_enter
 * Function:         Press the Enter key to continue
 * Input Parameters: int prompt_output：0 - Not displaying any prompt message
 *                                      1 - Displaying a prompt message
 * Return Value:     void
 */
void wait_for_enter(int prompt_output)
{
    if (prompt_output)
        cout << endl << "按回车键继续";
    while (_getch() != '\r')
        continue;
}

/*
 * Function Name:    delay
 * Function:         Delay function
 * Input Parameters: int delay_optn
 *                   int singleStepDemo_or_not：0 - Not performing a step-by-step demonstration
 *                                              1 - Performing a step-by-step demonstration
 *                   int printMoveProcess_or_not：0 - Not printing the movement process
 *                                                1 - Printing the movement process
 * Return Value:     void
 */
void delay(int delay_optn, int singleStepDemo_or_not, int printMoveProcess_or_not)
{
    switch (delay_optn) {
        case 1:
            Sleep(1000);
            break;
        case 2:
            Sleep(500);
            break;
        case 3:
            Sleep(100);
            break;
        case 4:
            Sleep(10);
            break;
        case 5:
            break;
        default:
            if (singleStepDemo_or_not)
                wait_for_enter(0);
            if (printMoveProcess_or_not)
                Sleep(50);
            break;
    }
}

/*
 * Function Name:    parameters_input
 * Function:         Getting the Tower of Hanoi parameters
 * Input Parameters: int* p_n
 *                   char* p_src
 *                   char* p_tmp
 *                   char* p_dst
 *                   int* p_delay_optn
 *                   int delay_or_not
 * Return Value:     void
 */
void parameters_input(int* p_n, char* p_src, char* p_tmp, char* p_dst, int* p_delay_optn, int delay_or_not)
{
    while (1) {
        cout << "请输入汉诺塔的层数(1-10)" << endl;
        cin >> *p_n;
        if (cin.good() && (*p_n >= 1 && *p_n <= 10)) {
            cin.clear();
            cin.ignore(65536, '\n');
            break;
        }
        else {
            cin.clear();
            cin.ignore(65536, '\n');
        }
    }
    while (1) {
        cout << "请输入起始柱(A-C)" << endl;
        cin >> *p_src;
        if (cin.good() && ((*p_src >= 'A' && *p_src <= 'C') || (*p_src >= 'a' && *p_src <= 'c'))) {
            cin.clear();
            cin.ignore(65536, '\n');
            if (*p_src == 'a')
                *p_src = 'A';
            if (*p_src == 'b')
                *p_src = 'B';
            if (*p_src == 'c')
                *p_src = 'C';
            break;
        }
        else {
            cin.clear();
            cin.ignore(65536, '\n');
        }
    }
    while (1) {
        cout << "请输入目标柱(A-C)" << endl;
        cin >> *p_dst;
        if (cin.good() && ((*p_dst >= 'A' && *p_dst <= 'C') || (*p_dst >= 'a' && *p_dst <= 'c'))) {
            cin.clear();
            cin.ignore(65536, '\n');
            if (*p_dst == 'a')
                *p_dst = 'A';
            if (*p_dst == 'b')
                *p_dst = 'B';
            if (*p_dst == 'c')
                *p_dst = 'C';
            if (*p_dst == *p_src) {
                cout << "目标柱(" << *p_dst << ")不能与起始柱(" << *p_src << ")相同" << endl;
                continue;
            }
            else
                break;
        }
        else {
            cin.clear();
            cin.ignore(65536, '\n');
        }
    }
    *p_tmp = 'A' + 'B' + 'C' - *p_src - *p_dst;
    if (delay_or_not) {
        while (1) {
            cout << "请输入移动速度(0-5: 0-按回车单步演示 1-延时最长 5-延时最短) ";
            cin >> *p_delay_optn;
            if (cin.good() && (*p_delay_optn >= 0 && *p_delay_optn <= 5)) {
                cin.clear();
                cin.ignore(65536, '\n');
                break;
            }
            else {
                cin.clear();
                cin.ignore(65536, '\n');
            }
        }
    }
    stack_initialize(*p_n, *p_src);
}

/*
 * Function Name:    initialize
 * Function:         Initializing the step counter variable, stack, and stack pointe
 * Input Parameters: void
 * Return Value:     void
 */
void initialize(void)
{
    counter = 0;
    delay_optn = 0;
    for (int i = 0; i < 3; i++)
        top[i] = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < stack_top; j++)
            stack[i][j] = 0;
}

/*
 * Function Name:    stack_initialize
 * Function:         Initializing the stack and the stack pointer
 * Input Parameters: int n
 *                   char src
 * Return Value:     void
 */
void stack_initialize(int n, char src)
{
    for (int i = 0; i < 3; i++)
        if (src == 'A' + i) {
            for (int j = 0; j < n; j++)
                stack[i][j] = n - j;
            top[i] = n;
        }
}

/*
 * Function Name:    stack_move
 * Function:         Moving a stack
 * Input Parameters: char src
 *                   char dst
 *                   int roll_back: 0 - Not rolling back the previous stack
 *                                  1 - Rolling back the previous stack
 * Return Value:     void
 */
void stack_move(char src, char dst, int roll_back)
{
    if (roll_back) {
        stack[src - 'A'][top[src - 'A']++] = stack[dst - 'A'][--top[dst - 'A']];
        stack[dst - 'A'][top[dst - 'A']] = 0;
    }
    else {
        stack[dst - 'A'][top[dst - 'A']++] = stack[src - 'A'][--top[src - 'A']];
        stack[src - 'A'][top[src - 'A']] = 0;
    }
}


/*
 * Function Name:    print_stack_horizontal
 * Function:         Printing the internal arrays in a horizontal format
 * Input Parameters: void
 * Return Value:     void
 */
void print_stack_horizontal(void)
{
    for (int i = 0; i < 3; i++) {
        cout << " " << char('A' + i) << ":";
        for (int j = 0; j < stack_top; j++)
            if (stack[i][j] != 0)
                cout << setw(2) << stack[i][j];
            else
                cout << "  ";
    }
    cout << endl;
}

/*
 * Function Name:    print_stack_vertical_initial
 * Function:         Printing the initial internal array in a vertical format
 * Input Parameters: int n
 *                   char src
 *                   char dst
 *                   int printMoveProcess_or_not：0 - Not printing the movement process
 *                                                1 - Printing the movement process
 * Return Value:     void
 */
void print_stack_vertical_initial(int n, char src, char dst, int printMoveProcess_or_not)
{
    cct_gotoxy(9, 12 + printMoveProcess_or_not * 15);
    cout << "=========================";
    cct_gotoxy(11, 13 + printMoveProcess_or_not * 15);
    cout << "A         B         C";
    for (int i = 0; i < 3; i++)
        if (stack[i][0])
            for (int j = 0, y = 12 + printMoveProcess_or_not * 15; j < top[i]; j++) {
                cct_gotoxy(10 * (i + 1), --y);
                cout << setw(2) << stack[i][j];
            }
    cct_gotoxy(0, 17 + printMoveProcess_or_not * 15);
    cout << "初始: ";
    print_stack_horizontal();
}

/*
 * Function Name:    print_stack_vertical
 * Function:         Printing the internal arrays in a vertical format
 * Input Parameters: char src
 *                   char dst
 *                   int printMoveProcess_or_not：0 - Not printing the movement process
 *                                                1 - Printing the movement process
 * Return Value:     void
 */
void print_stack_vertical(char src, char dst, int printMoveProcess_or_not)
{
    for (int i = 0; i < 3; i++)
        if (src == i + 'A')
            cct_gotoxy(10 * (i + 1), 11 - top[i] + printMoveProcess_or_not * 15);
    cout << "  ";
    for (int i = 0; i < 3; i++)
        if (dst == i + 'A') {
            cct_gotoxy(10 * (i + 1), 12 - top[i] + printMoveProcess_or_not * 15);
            cout << setw(2) << stack[i][top[i] - 1];
        }
}

/*
 * Function Name:    print_horizontal_vertical_moveProcess
 * Function:         Printing the internal arrays and movement process in both horizontal and vertical formats
 * Input Parameters: int n
 *                   char src
 *                   char dst
 *                   int printSteps_or_not：0 - Not printing the number of moves
 *                                          1 - Printing the number of moves
 *                   int printHorizontal_or_not：0 - Not printing the internal array structure horizontally
 *                                               1 - Printing the internal array structure horizontally
 *                   int printVertical_or_not：0 - Not printing the internal array structure vertically
 *                                             1 - Printing the internal array structure vertically
 *                   int singleStepDemo_or_not：0 - Not performing a step-by-step demonstration
 *                                              1 - Performing a step-by-step demonstration
 *                   int printMoveProcess_or_not：0 - Not printing the movement process
 *                                                1 - Printing the movement process
 * Return Value:     void
 */
void print_horizontal_vertical_moveProcess(int n, char src, char dst, int printSteps_or_not, int printHorizontal_or_not, int printVertical_or_not, int singleStepDemo_or_not, int printMoveProcess_or_not)
{
    if (printVertical_or_not)
        cct_gotoxy(0, 17 + printMoveProcess_or_not * 15);
    print_horizontal(n, src, dst, printSteps_or_not, printHorizontal_or_not);
    if (printVertical_or_not)
        print_stack_vertical(src, dst, printMoveProcess_or_not);
    if (printMoveProcess_or_not) {
        stack_move(src, dst, 1);
        print_moveProcess_all(n, src, dst, stack[src - 'A'][top[src - 'A'] - 1], 0);
        stack_move(src, dst, 0);
    }
    delay(delay_optn, singleStepDemo_or_not, printMoveProcess_or_not);
}

/*
 * Function Name:    print_horizontal
 * Function:         Printing the movement steps in a horizontal format
 * Input Parameters: int n
 *                   char src
 *                   char dst
 *                   int printSteps_or_not：0 - Not printing the number of moves
 *                                          1 - Printing the number of moves
 *                   int printHorizontal_or_not：0 - Not printing the internal array structure horizontally
 *                                               1 - Printing the internal array structure horizontally
 * Return Value:     void
 */
void print_horizontal(int n, char src, char dst, int printSteps_or_not, int printHorizontal_or_not)
{
    if (printSteps_or_not) {
        cout << "第" << setw(4) << ++counter << " 步(" << setw(2) << n << "#: " << src << "-->" << dst << ")";
        if (printHorizontal_or_not) {
            stack_move(src, dst, 0);
            cout << " ";
            print_stack_horizontal();
        }
        else
            cout << endl;
    }
    else
        cout << n << "# " << src << "---->" << dst << endl;
}

/*
 * Function Name:    hanoi
 * Function:         Recursive function for the Tower of Hanoi problem
 * Input Parameters: int n
 *                   char src
 *                   char tmp
 *                   char dst
 *                   int printSteps_or_not：0 - Not printing the number of moves
 *                                          1 - Printing the number of moves
 *                   int printHorizontal_or_not：0 - Not printing the internal array structure horizontally
 *                                               1 - Printing the internal array structure horizontally
 *                   int printVertical_or_not：0 - Not printing the internal array structure vertically
 *                                             1 - Printing the internal array structure vertically
 *                   int singleStepDemo_or_not：0 - Not performing a step-by-step demonstration
 *                                              1 - Performing a step-by-step demonstration
 *                   int printMoveProcess_or_not：0 - Not printing the movement process
 *                                                1 - Printing the movement process
 * Return Value:     void
 */
void hanoi(int n, char src, char tmp, char dst, int printSteps_or_not, int printHorizontal_or_not, int printVertical_or_not, int singleStepDemo_or_not, int printMoveProcess_or_not)
{
    if (n > 1)
        hanoi(n - 1, src, dst, tmp, printSteps_or_not, printHorizontal_or_not, printVertical_or_not, singleStepDemo_or_not, printMoveProcess_or_not);
    print_horizontal_vertical_moveProcess(n, src, dst, printSteps_or_not, printHorizontal_or_not, printVertical_or_not, singleStepDemo_or_not, printMoveProcess_or_not);
    if (n > 1)
        hanoi(n - 1, tmp, src, dst, printSteps_or_not, printHorizontal_or_not, printVertical_or_not, singleStepDemo_or_not, printMoveProcess_or_not);
}

/*
 * Function Name:    color_match
 * Function:         Matching colors based on the size of the plate
 * Input Parameters: int n
 * Return Value:     color
 */
int color_match(int n)
{
    switch (n) {
        case 1:
            return COLOR_BLUE;
        case 2:
            return COLOR_GREEN;
        case 3:
            return COLOR_CYAN;
        case 4:
            return COLOR_RED;
        case 5:
            return COLOR_PINK;
        case 6:
            return COLOR_YELLOW;
        case 7:
            return COLOR_HWHITE;
        case 8:
            return COLOR_HBLACK;
        case 9:
            return COLOR_HBLUE;
        case 10:
            return COLOR_HGREEN;
        default:
            return COLOR_BLACK;
    }
}

/*
 * Function Name:    print_cylinders
 * Function:         Printing the three cylinders
 * Input Parameters: void
 * Return Value:     void
 */
void print_cylinders(void)
{
    cct_setcolor(COLOR_HYELLOW, COLOR_WHITE);
    for (int i = 1; i <= 3; i++) {
        cct_gotoxy(32 * i - 31, 15);
        cout << setw(23) << "";
    }
    for (int i = 14; i >= 3; i--)
        for (int j = 1; j <= 3; j++) {
            cct_gotoxy(32 * j - 20, i);
            Sleep(50);
            cout << " ";
        }
    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
}

/*
 * Function Name:    print_plates
 * Function:         Printing the discs on the source column
 * Input Parameters: void
 * Return Value:     void
 */
void print_plates(void)
{
    for (int i = 0; i < 3; i++)
        if (stack[i][0])
            for (int j = 0; j < top[i]; j++) {
                Sleep(50);
                cct_showch(12 + 32 * i - stack[i][j], 14 - j, ' ', color_match(stack[i][j]), COLOR_WHITE, 2 * stack[i][j] + 1);
            }
    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
}

/*
 * Function Name:    print_moveProcess_all
 * Function:         Printing the overall movement process
 * Input Parameters: int n
 *                   char src
 *                   char dst
 *                   int num
 *                   int firstMove_or_not: 0 - Not printing the movement process for the first move
 *                                         1 - Printing the movement process for the first move
 * Return Value:     void
 */
void print_moveProcess_all(int n, char src, char dst, int num, int firstMove_or_not)
{
    if (n % 2 == 0 && firstMove_or_not)
        dst = 'A' + 'B' + 'C' - src - dst;
    print_moveProcess_vertical(src, num, 0);
    print_moveProcess_horizontal(src, dst, num);
    print_moveProcess_vertical(dst, num, 1);
    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
}

/*
 * Function Name:    print_moveProcess_vertical
 * Function:         Printing the vertical movement process
 * Input Parameters: char src_or_dst
 *                   int num
 *                   int up_or_down: 0 - Moving upwards when src_or_dst is the starting column
 *                                   1 - Moving downwards when src_or_dst is the target column
 * Return Value:     void
 */
void print_moveProcess_vertical(char src_or_dst, int num, int up_or_down)
{
    if (up_or_down)
        for (int y = 1; y < 14 - top[src_or_dst - 'A']; y++) {
            delay(delay_optn, 0, 1);
            if (y > 0) {
                cct_showch(12 + 32 * (src_or_dst - 'A') - num, y, ' ', COLOR_BLACK, COLOR_WHITE, 2 * num + 1);
                if (y > 2)
                    cct_showch(12 + 32 * (src_or_dst - 'A'), y, ' ', COLOR_HYELLOW, COLOR_WHITE, 1);
            }
            cct_showch(12 + 32 * (src_or_dst - 'A') - num, y + 1, ' ', color_match(num), COLOR_WHITE, 2 * num + 1);
        }
    else
        for (int y = 14 - top[src_or_dst - 'A']; y > 0; y--) {
            delay(delay_optn, 0, 1);
            if (y > 0) {
                cct_showch(12 + 32 * (src_or_dst - 'A') - num, y + 1, ' ', COLOR_BLACK, COLOR_WHITE, 2 * num + 1);
                if (y > 1)
                    cct_showch(12 + 32 * (src_or_dst - 'A'), y + 1, ' ', COLOR_HYELLOW, COLOR_WHITE, 1);
            }
            cct_showch(12 + 32 * (src_or_dst - 'A') - num, y, ' ', color_match(num), COLOR_WHITE, 2 * num + 1);
        }
}

/*
 * Function Name:    print_moveProcess_horizontal
 * Function:         Printing the horizontal movement process
 * Input Parameters: char src
 *                   char dst
 *                   int num
 * Return Value:     void
 */
void print_moveProcess_horizontal(char src, char dst, int num)
{
    if (src < dst)
        for (int x = 12 + 32 * (src - 'A') - num; x < 12 + 32 * (dst - 'A') - num; x++) {
            delay(delay_optn, 0, 1);
            if (x < 12 + 32 * (dst - 'A') - num)
                cct_showch(x, 1, ' ', COLOR_BLACK, COLOR_WHITE, 2 * num + 1);
            cct_showch(x + 1, 1, ' ', color_match(num), COLOR_WHITE, 2 * num + 1);
        }
    else
        for (int x = 12 + 32 * (src - 'A') - num; x > 12 + 32 * (dst - 'A') - num; x--) {
            delay(delay_optn, 0, 1);
            if (x > 12 + 32 * (dst - 'A') - num)
                cct_showch(x, 1, ' ', COLOR_BLACK, COLOR_WHITE, 2 * num + 1);
            cct_showch(x - 1, 1, ' ', color_match(num), COLOR_WHITE, 2 * num + 1);
        }
}

/*
 * Function Name:    print_moveProcess_game
 * Function:         Printing the game movement process
 * Input Parameters: int n
 *                   char src
 *                   char dst
 * Return Value:     void
 */
void print_moveProcess_game(int n, char src, char dst)
{
    if (!top[src - 'A']) {
        cout << endl << "源柱为空!";
        Sleep(500);
    }
    else if (stack[src - 'A'][top[src - 'A'] - 1] > stack[dst - 'A'][top[dst - 'A'] - 1] && top[dst - 'A']) {
        cout << endl << "大盘压小盘，非法移动!";
        Sleep(500);
    }
    else
        print_horizontal_vertical_moveProcess(n, src, dst, 1, 1, 1, 0, 1);
}

/*
 * Function Name:    optn_1_fundamentSolution_base
 * Function:         Executing menu item 1
 * Input Parameters: void
 * Return Value:     void
 */
void optn_1_fundamentSolution_base(void)
{
    initialize();
    int n;
    char src, tmp, dst;
    parameters_input(&n, &src, &tmp, &dst, &delay_optn, 0);
    hanoi(n, src, tmp, dst, 0, 0, 0, 0, 0);
    wait_for_enter(1);
    cct_cls();
}

/*
 * Function Name:    optn_2_fundamentSolution_stepRecord
 * Function:         Executing menu item 2
 * Input Parameters: void
 * Return Value:     void
 */
void optn_2_fundamentSolution_stepRecord(void)
{
    initialize();
    int n;
    char src, tmp, dst;
    parameters_input(&n, &src, &tmp, &dst, &delay_optn, 0);
    hanoi(n, src, tmp, dst, 1, 0, 0, 0, 0);
    wait_for_enter(1);
    cct_cls();
}

/*
 * Function Name:    optn_3_arrayDisplay_horizontal
 * Function:         Executing menu item 3
 * Input Parameters: void
 * Return Value:     void
 */
void optn_3_arrayDisplay_horizontal(void)
{
    initialize();
    int n;
    char src, tmp, dst;
    parameters_input(&n, &src, &tmp, &dst, &delay_optn, 0);
    hanoi(n, src, tmp, dst, 1, 1, 0, 0, 0);
    wait_for_enter(1);
    cct_cls();
}

/*
 * Function Name:    optn_4_arrayDisplay_horizontalVertical
 * Function:         Executing menu item 4
 * Input Parameters: void
 * Return Value:     void
 */
void optn_4_arrayDisplay_horizontalVertical(void)
{
    initialize();
    int n;
    char src, tmp, dst;
    parameters_input(&n, &src, &tmp, &dst, &delay_optn, 1);
    cct_cls();
    cct_setcursor(CURSOR_INVISIBLE);
    cout << "从 " << src << " 移动到 " << dst << "，共 " << n << " 层，延时设置为 " << delay_optn << endl;
    print_stack_vertical_initial(n, src, dst, 0);
    delay(delay_optn, delay_optn ? 0 : 1, 0);
    hanoi(n, src, tmp, dst, 1, 1, 1, delay_optn ? 0 : 1, 0);
    cct_gotoxy(0, 37);
    cct_setcursor(CURSOR_VISIBLE_NORMAL);
    wait_for_enter(1);
    cct_cls();
}

/*
 * Function Name:    optn_5_graphicalSolution_printCylinders
 * Function:         Executing menu item 5
 * Input Parameters: void
 * Return Value:     void
 */
void optn_5_graphicalSolution_printCylinders(void)
{
    cct_cls();
    cct_setcursor(CURSOR_INVISIBLE);
    print_cylinders();
    cct_setcursor(CURSOR_VISIBLE_NORMAL);
    cct_gotoxy(0, 37);
    wait_for_enter(1);
    cct_cls();
}

/*
 * Function Name:    optn_6_graphicalSolution_printPlates
 * Function:         Executing menu item 6
 * Input Parameters: void
 * Return Value:     void
 */
void optn_6_graphicalSolution_printPlates(void)
{
    initialize();
    int n;
    char src, tmp, dst;
    parameters_input(&n, &src, &tmp, &dst, &delay_optn, 0);
    cct_cls();
    cct_setcursor(CURSOR_INVISIBLE);
    cout << "从 " << src << " 移动到 " << dst << "，共 " << n << " 层" << endl;
    print_cylinders();
    print_plates();
    cct_setcursor(CURSOR_VISIBLE_NORMAL);
    cct_gotoxy(0, 37);
    wait_for_enter(1);
    cct_cls();
}

/*
 * Function Name:    optn_7_graphicalSolution_firstMove
 * Function:         Executing menu item 7
 * Input Parameters: void
 * Return Value:     void
 */
void optn_7_graphicalSolution_firstMove(void)
{
    initialize();
    int n;
    char src, tmp, dst;
    parameters_input(&n, &src, &tmp, &dst, &delay_optn, 0);
    cct_cls();
    cct_setcursor(CURSOR_INVISIBLE);
    cout << "从 " << src << " 移动到 " << dst << "，共 " << n << " 层" << endl;
    print_cylinders();
    print_plates();
    print_moveProcess_all(n, src, dst, stack[src - 'A'][top[src - 'A'] - 1], 1);
    cct_setcursor(CURSOR_VISIBLE_NORMAL);
    cct_gotoxy(0, 37);
    wait_for_enter(1);
    cct_cls();
}

/*
 * Function Name:    optn_8_graphicalSolution_autoMove
 * Function:         Executing menu item 8
 * Input Parameters: void
 * Return Value:     void
 */
void optn_8_graphicalSolution_autoMove(void)
{
    initialize();
    int n;
    char src, tmp, dst;
    parameters_input(&n, &src, &tmp, &dst, &delay_optn, 1);
    cct_cls();
    cct_setcursor(CURSOR_INVISIBLE);
    cout << "从 " << src << " 移动到 " << dst << "，共 " << n << " 层，延时设置为 " << delay_optn << endl;
    print_stack_vertical_initial(n, src, dst, 1);
    print_cylinders();
    print_plates();
    if (!delay_optn)
        wait_for_enter(0);
    hanoi(n, src, tmp, dst, 1, 1, 1, delay_optn ? 0 : 1, 1);
    cct_setcursor(CURSOR_VISIBLE_NORMAL);
    cct_gotoxy(0, 37);
    wait_for_enter(1);
    cct_cls();
}

/*
 * Function Name:    optn_9_graphicalSolution_game
 * Function:         Executing menu item 9
 * Input Parameters: void
 * Return Value:     void
 */
void optn_9_graphicalSolution_game(void)
{
    initialize();
    int n;
    char src, tmp, dst, _src, _tmp, _dst;
    parameters_input(&n, &src, &tmp, &dst, &delay_optn, 0);
    _src = src;
    _tmp = tmp;
    _dst = dst;
    cct_cls();
    cct_setcursor(CURSOR_INVISIBLE);
    cout << "从 " << src << " 移动到 " << dst << "，共 " << n << " 层" << endl;
    print_stack_vertical_initial(n, src, dst, 1);
    print_cylinders();
    print_plates();
    cct_setcursor(CURSOR_VISIBLE_NORMAL);
    cct_gotoxy(0, 34);
    cout << "请输入移动的柱号(命令形式：AC=A顶端的盘子移动到C，Q=退出) ：";
    int exit_or_not = 1;
    while (exit_or_not) {
        cct_gotoxy(60, 34);
        cout << "  " << endl << "                     ";
        cct_gotoxy(60, 34);
        while (1) {
            char input[20] = { 0 };
            if (!top[_src - 'A'] && !top[_tmp - 'A'] && top[_dst - 'A']) {
                cout << endl << "游戏结束!!!!!";
                exit_or_not = 0;
                break;
            }
            for (int i = 0; i < 20; i++)
                while (1) {
                    char ch = _getch();
                    if (ch == 0 || ch == -32)
                        ch = _getch();
                    else if (ch == '\r') {
                        i = 20;
                        break;
                    }
                    else if (ch >= 33 && ch <= 126) {
                        if (i != 19) {
                            cout << ch;
                            input[i] = ch;
                        }
                        break;
                    }
                    else
                        continue;
                }
            if (!strcasecmp(input, "Q")) {
                cout << endl << "游戏中止!!!!!";
                exit_or_not = 0;
                break;
            }
            else if (!strcasecmp(input, "AB")) {
                src = 'A';
                dst = 'B';
                tmp = 'C';
                print_moveProcess_game(n, src, dst);
                break;
            }
            else if (!strcasecmp(input, "AC")) {
                src = 'A';
                dst = 'C';
                tmp = 'B';
                print_moveProcess_game(n, src, dst);
                break;
            }
            else if (!strcasecmp(input, "BA")) {
                src = 'B';
                dst = 'A';
                tmp = 'C';
                print_moveProcess_game(n, src, dst);
                break;
            }
            else if (!strcasecmp(input, "BC")) {
                src = 'B';
                dst = 'C';
                tmp = 'A';
                print_moveProcess_game(n, src, dst);
                break;
            }
            else if (!strcasecmp(input, "CA")) {
                src = 'C';
                dst = 'A';
                tmp = 'B';
                print_moveProcess_game(n, src, dst);
                break;
            }
            else if (!strcasecmp(input, "CB")) {
                src = 'C';
                dst = 'B';
                tmp = 'A';
                print_moveProcess_game(n, src, dst);
                break;
            }
            else {
                cct_gotoxy(60, 34);
                cout << "                   ";
                cct_gotoxy(60, 34);
                continue;
            }
        }
    }
    cct_gotoxy(0, 37);
    wait_for_enter(1);
    cct_cls();
}