/****************************************************************
 * Project Name:  Mine_Sweeper
 * File Name:     mine_sweeper_menu.cpp
 * File Function: 菜单函数的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/11/21
 ****************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "../common/cmd_console_tools.h"
#include "../common/lib_gmw_tools.h"
#include "mine_sweeper.h"

using namespace std;

/*
 * Function Name:    menu
 * Function:         Display menu items and read the correct option
 * Input Parameters: int& row
 *                   int& col
 *                   int& mine
 * Return Value:     option
 */
int menu(int& row, int& col, int& mine)
{
    /* Define menu_content structure array */
    struct menu_content menu_display[5] = { {'A',"经典","Classic",8,8,8,COLOR_HCYAN},{'B',"简单","Simple",9,9,10,COLOR_HGREEN},{'C',"中等","Medium",16,16,40,COLOR_HYELLOW},{'D',"专家","Expert",16,30,99,COLOR_HRED},{'E',"自定义","Custom",0,0,0,COLOR_HPINK} };

    /* Set the console */
    cct_setcursor(CURSOR_VISIBLE_NORMAL);
    cct_setcolor();
    cct_setconsoletitle("Mine Sweeper - Menu");
    cct_setfontsize("新宋体", 24);
    cct_setconsoleborder(82, 16, 82, 16);

    /* Display menu items */
    cct_showstr(37, 1, "扫雷游戏", COLOR_BLACK, COLOR_HWHITE);
    cct_showstr(35, 2, "Mine Sweeper", COLOR_BLACK, COLOR_HWHITE);
    for (int i = 0; i < 5; i++)
        print_option(menu_display, i, 2 + 16 * i, 4);
    cct_showstr(69, 12, "(按Q/q退出)", COLOR_BLACK, COLOR_HWHITE);
    cct_showstr(2, 12, "[请选择难度:] ", COLOR_BLACK, COLOR_HWHITE);

    /* Read the option */
    char optn = read_option();

    /* Read the custom mode parameters */
    if (optn == 'E' || optn == 'e') {
        do {
            menu_display[4].row = enter_digit("[请输入自定义模式行数(10~16):]");
        } while (menu_display[4].row > 16);
        do {
            menu_display[4].col = enter_digit("[请输入自定义模式列数(10~32):]");
        } while (menu_display[4].col > 32);
        menu_display[4].mine = enter_digit("[请输入自定义模式雷数(10~99):]");
        cct_setcursor(CURSOR_INVISIBLE);
        cct_setcolor(COLOR_BLACK, COLOR_HPINK);
        cct_gotoxy(69, 8);
        cout << menu_display[4].row << "*" << menu_display[4].col;
        cct_gotoxy(69, 9);
        cout << menu_display[4].mine << "颗雷";
        Sleep(1000);
    }

    /* Set the console and return the option and parameters */
    if (optn != 'Q' && optn != 'q') {
        char title[28] = { 0 };
        strcat(title, "Mine Sweeper - ");
        strcat(title, menu_display[(optn >= 'A' && optn <= 'E') ? optn - 'A' : optn - 'a'].mode_en);
        strcat(title, " Mode");
        cct_setconsoletitle(title);
        cct_setcursor(CURSOR_INVISIBLE);
        row = menu_display[(optn >= 'A' && optn <= 'E') ? optn - 'A' : optn - 'a'].row;
        col = menu_display[(optn >= 'A' && optn <= 'E') ? optn - 'A' : optn - 'a'].col;
        mine = menu_display[(optn >= 'A' && optn <= 'E') ? optn - 'A' : optn - 'a'].mine;
    }

    /* Print the game instructions */
    if (optn != 'Q' && optn != 'q') {
        cct_showstr(2, 12, "[游戏方法:] 左键进行消除 右键进行标记 ESC键返回菜单        ", COLOR_BLACK, COLOR_HWHITE);
        system("pause");
    }

    /* Return the option */
    return optn;
}

/*
 * Function Name:    print_option
 * Function:         Print a menu item
 * Input Parameters: struct menu_content menu_display[]
 *                   int optn
 *                   int X
 *                   int Y
 *                   int bg_color
 * Return Value:     void
 */
void print_option(struct menu_content menu_display[], int optn, int X, int Y, int bg_color)
{
    /* Print frame */
    cct_showstr(X, Y, "┏━━━━━┓", bg_color, menu_display[optn].color);
    for (int i = 1; i <= 5; i++)
        cct_showstr(X, Y + i, "┃          ┃", bg_color, menu_display[optn].color);
    cct_showstr(X, Y + 6, "┗━━━━━┛", bg_color, menu_display[optn].color);

    /* Print content */
    cct_showch(X + 3, Y + 1, menu_display[optn].no, bg_color, menu_display[optn].color);
    cct_showstr(X + 3, Y + 3, menu_display[optn].mode_ch, bg_color, menu_display[optn].color);
    if (menu_display[optn].row || menu_display[optn].col) {
        cct_gotoxy(X + 3, Y + 4);
        cout << menu_display[optn].row << "*" << menu_display[optn].col;
    }
    if (menu_display[optn].mine) {
        cct_gotoxy(X + 3, Y + 5);
        cout << menu_display[optn].mine << "颗雷";
    }
}

/*
 * Function Name:    enter_digit
 * Function:         Input a two digit number
 * Input Parameters: const char* prompt
 * Return Value:     a two digit number
 * Notes:            The range of the two digit number: 10~99
 */
int enter_digit(const char* prompt)
{
    /* Print the prompt message */
    cct_showstr(2, 12, prompt, COLOR_BLACK, COLOR_HWHITE);
    cout << " ";

    /* Input a ten-digit number */
    int num2;
    while (true) {
        char input = _getch();
        if (input == 0 || input == -32)
            input = _getch();
        else if (input >= '1' && input <= '9') {
            cout << input;
            num2 = input - '0';
            break;
        }
        else
            continue;
    }

    /* Input the units digit */
    int num1;
    while (true) {
        char input = _getch();
        if (input == 0 || input == -32)
            input = _getch();
        else if (input >= '0' && input <= '9') {
            cout << input;
            num1 = input - '0';
            break;
        }
        else
            continue;
    }

    /* Clear the prompt message */
    Sleep(300);
    cct_showch(2, 12, ' ', COLOR_BLACK, COLOR_HWHITE, 43);

    /* Return a two digit number */
    return 10 * num2 + num1;
}

/*
 * Function Name:    read_option
 * Function:         Read the option
 * Input Parameters: void
 * Return Value:     option
 */
char read_option(void)
{
    /* Read the option */
    while (true) {
        char optn = _getch();
        if (optn == 0 || optn == -32)
            optn = _getch();
        else if ((optn >= 'A' && optn <= 'E') || (optn >= 'a' && optn <= 'e') || optn == 'Q' || optn == 'q') {
            cout << optn;
            Sleep(300);
            return optn;
        }
        else
            continue;
    }
}