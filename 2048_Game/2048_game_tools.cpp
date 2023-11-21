/****************************************************************
 * Project Name:  2048_Game
 * File Name:     2048_game_tools.cpp
 * File Function: ���ߺ�����ʵ��
 * Author:        Jishen Lin (�ּ���)
 * Update Date:   2023/11/21
 ****************************************************************/

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <iomanip>
#include "../common/cmd_console_tools.h"
#include "../common/lib_gmw_tools.h"
#include "2048_game.h"

/* Namespace */
using namespace std;

/*
 * Function Name:    menu
 * Function:         Show the menu and input the parameters
 * Input Parameters: int& row
 *                   int& col
 * Return Value:     void
 */
void menu(int& row, int& col)
{
    /* Set the console title */
    cct_setconsoletitle("2048 Game");

    /* Show the menu */
    CONSOLE_GRAPHICS_INFO menuCGI;
    gmw_init(&menuCGI);
    gmw_set_rowcol(&menuCGI, 2, 5);
    gmw_set_font(&menuCGI, "������", 24);
    gmw_set_ext_rowcol(&menuCGI, 3, 1, 2, 1);
    gmw_set_frame_style(&menuCGI, 10, 5);
    gmw_set_frame_color(&menuCGI, COLOR_HWHITE, COLOR_BLACK);
    gmw_set_block_border_switch(&menuCGI, true);
    gmw_set_status_line_switch(&menuCGI, TOP_STATUS_LINE, false);
    gmw_set_status_line_switch(&menuCGI, LOWER_STATUS_LINE, false);
    gmw_draw_frame(&menuCGI);
    int menu_matrix[2][5] = { 2,4,8,16,32,64,128,256,512,1024 };
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 5; j++)
            gmw_draw_block(&menuCGI, i, j, menu_matrix[i][j], bdi);
    cct_showstr(29, 1, "2048��Ϸ", COLOR_BLACK, COLOR_HWHITE);

    /* Set the cursor state */
    cct_setcursor(CURSOR_VISIBLE_NORMAL);

    /* Input the parameters */
    row = enter_digit(2, 17, "[����������(4~8):]");
    col = enter_digit(2, 18, "[����������(4~8):]");

    /* Set the cursor state */
    cct_setcursor(CURSOR_INVISIBLE);
}

/*
 * Function Name:    enter_digit
 * Function:         Input a number
 * Input Parameters: int x
 *                   int y
 *                   const char* prompt
 * Return Value:     a number
 * Notes:            The range of the number: 4~8
 */
int enter_digit(int x, int y, const char* prompt)
{
    /* Print the prompt message */
    cct_showstr(x, y, prompt, COLOR_BLACK, COLOR_HWHITE);
    cout << " ";

    /* Input a number */
    char input;
    while (true) {
        input = _getch();
        if (input == 0 || input == -32)
            input = _getch();
        else if (input >= '4' && input <= '8') {
            cout << input;
            Sleep(300);
            return input - '0';
        }
        else
            continue;
    }
}

/*
 * Function Name:    initialize_CGI
 * Function:         Initialize CONSOLE_GRAPHICS_INFO structure
 * Input Parameters: CONSOLE_GRAPHICS_INFO* pCGI
 *                   int row
 *                   int col
 * Return Value:     void
 */
void initialize_CGI(CONSOLE_GRAPHICS_INFO* pCGI, int row, int col)
{
    gmw_init(pCGI);
    gmw_set_rowcol(pCGI, row, col);
    gmw_set_font(pCGI, "������");
    gmw_set_frame_style(pCGI, 10, 5);
    gmw_set_frame_color(pCGI, COLOR_HWHITE, COLOR_BLACK);
    gmw_set_block_border_switch(pCGI, true);
    gmw_set_rowno_switch(pCGI, true);
    gmw_set_colno_switch(pCGI, true);
    gmw_draw_frame(pCGI);
    gmw_status_line(pCGI, LOWER_STATUS_LINE, "[��Ϸ����:] ���������ҷ���������ƶ� ��ESC�����ز˵�");
    gmw_status_line(pCGI, TOP_STATUS_LINE, "Ŀ��ϳ�: 2048  ��ǰ����: 0");
}

/*
 * Function Name:    print_prompt
 * Function:         Print prompt
 * Input Parameters: int score
 *                   int status
 * Return Value:     Whether to return to the menu
 */
bool print_prompt(int score, int status)
{
    if (status == 2)
        return false;
    cct_showstr(0, 0, status == 1 ? "��Ϸ�ɹ�! ��Ϸ�÷�: " : "��Ϸʧ��! ��Ϸ�÷�: ", COLOR_BLACK, COLOR_HYELLOW);
    cout << setiosflags(ios::left) << setw(32) << score << resetiosflags(ios::left);
    cct_gotoxy(0, 29);
    system("pause");
    return true;
}