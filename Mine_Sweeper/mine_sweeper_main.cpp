/****************************************************************
 * Project Name:  Mine_Sweeper
 * File Name:     mine_sweeper_main.cpp
 * File Function: 主体函数的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/9/28
 ****************************************************************/

#include <iostream>
#include <Windows.h>
#include "../common/cmd_console_tools.h"
#include "../common/lib_gmw_tools.h"
#include "mine_sweeper.h"

using namespace std;

/*
 * Function Name:    main
 * Function:         Main function
 * Return Value:     0
 */
int main()
{
    /* Generate random number seed */
    srand((unsigned int)(time(0)));

    /* Play Minesweeper game */
    while (1) {
        /* Call the menu function */
        int row, col, mine;
        int optn = menu(row, col, mine);
        if (optn == 'Q' || optn == 'q')
            return 0;

        /* Initialize unit and CONSOLE_GRAPHICS_INFO structure */
        CONSOLE_GRAPHICS_INFO CGI;
        initialize_CGI(&CGI, row, col);
        struct unit matrix[18][34];
        initialize_matrix(matrix, row, col, mine);

        /* Print all color blocks */
        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++)
                draw_block(&CGI, i, j, matrix, bdi);

        /* Save the start time */
        time_t start_time = clock();

        /* Read keyboard and mouse events */
        while (1) {
            /* Print the number of mines */
            cct_showint(10, 0, mine, COLOR_BLACK, COLOR_HYELLOW);

            /* Determine if the game is over */
            if (game_judgment(matrix, row, col)) {
                print_prompt(start_time, true);
                break;
            }

            /* Read keyboard and mouse events */
            int MAction, MRow, MCol, KeyCode1 = 0, KeyCode2 = 0;
            gmw_read_keyboard_and_mouse(&CGI, MAction, MRow, MCol, KeyCode1, KeyCode2);

            /* Determine whether to quit the game */
            if (KeyCode1 == 27)
                break;

            /* Print a color block */
            if (MAction == MOUSE_LEFT_BUTTON_CLICK || MAction == MOUSE_LEFT_BUTTON_DOUBLE_CLICK) {
                if (matrix[MRow + 1][MCol + 1].status == UNKNOWN && matrix[MRow + 1][MCol + 1].status != MARKED_MINE && matrix[MRow + 1][MCol + 1].status != MARKED_QUESTION) {
                    if (matrix[MRow + 1][MCol + 1].value == '*') {
                        matrix[MRow + 1][MCol + 1].status = KNOWN;
                        draw_block(&CGI, MRow, MCol, matrix, bdi);
                        Sleep(300);
                        for (int i = 1; i <= row; i++) {
                            for (int j = 1; j <= col; j++) {
                                if (matrix[i][j].value == '*') {
                                    matrix[i][j].status = KNOWN;
                                    Sleep(50);
                                    draw_block(&CGI, i - 1, j - 1, matrix, bdi);
                                } // end of if (matrix[i][j].value == '*')
                            } // end of for
                        } // end of for
                        print_prompt(start_time, false);
                        break;
                    } // end of if (matrix[MRow + 1][MCol + 1].value == '*')
                    else if (matrix[MRow + 1][MCol + 1].value) {
                        matrix[MRow + 1][MCol + 1].status = KNOWN;
                        draw_block(&CGI, MRow, MCol, matrix, bdi);
                    } // end of else if (matrix[MRow + 1][MCol + 1].value)
                    else {
                        print_continuity(&CGI, MRow, MCol, matrix, bdi, row, col);
                    } // end of else
                } // end of if (matrix[MRow + 1][MCol + 1].status == UNKNOWN && matrix[MRow + 1][MCol + 1].status != MARKED_MINE && matrix[MRow + 1][MCol + 1].status != MARKED_QUESTION)
            } // end of if (MAction == MOUSE_LEFT_BUTTON_CLICK || MAction == MOUSE_LEFT_BUTTON_DOUBLE_CLICK)
            else if (MAction == MOUSE_RIGHT_BUTTON_CLICK || MAction == MOUSE_RIGHT_BUTTON_DOUBLE_CLICK) {
                if (matrix[MRow + 1][MCol + 1].status == UNKNOWN) {
                    matrix[MRow + 1][MCol + 1].status = MARKED_MINE;
                    cct_showch(10, 0, ' ', COLOR_BLACK, COLOR_BLACK, 4);
                    cct_showint(10, 0, --mine, COLOR_BLACK, COLOR_HYELLOW);
                    draw_block(&CGI, MRow, MCol, matrix, bdi);
                } // end of if (matrix[MRow + 1][MCol + 1].status == UNKNOWN)
                else if (matrix[MRow + 1][MCol + 1].status == MARKED_MINE) {
                    matrix[MRow + 1][MCol + 1].status = MARKED_QUESTION;
                    cct_showch(10, 0, ' ', COLOR_BLACK, COLOR_BLACK, 4);
                    cct_showint(10, 0, ++mine, COLOR_BLACK, COLOR_HYELLOW);
                    draw_block(&CGI, MRow, MCol, matrix, bdi);
                } // else if (matrix[MRow + 1][MCol + 1].status == MARKED_MINE)
                else if (matrix[MRow + 1][MCol + 1].status == MARKED_QUESTION) {
                    matrix[MRow + 1][MCol + 1].status = UNKNOWN;
                    draw_block(&CGI, MRow, MCol, matrix, bdi);
                } // end of else if (matrix[MRow + 1][MCol + 1].status == MARKED_QUESTION)
            } // end of else if (MAction == MOUSE_RIGHT_BUTTON_CLICK || MAction == MOUSE_RIGHT_BUTTON_DOUBLE_CLICK)
        } // end of while (1)
    } // end of while (1)
}