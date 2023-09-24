/****************************************************************
 * Project Name:  Color_Linez
 * File Name:     color_linez_main.cpp
 * File Function: 主体函数的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/9/24
 ****************************************************************/

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <iomanip>
#include "../common/cmd_console_tools.h"
#include "../common/lib_gmw_tools.h"
#include "color_linez.h"
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

    /* Play color linez game */
    while (1) {
        /* Initialize GAME and CONSOLE_GRAPHICS_INFO class */
        class GAME game;
        CONSOLE_GRAPHICS_INFO CGI;

        /* Initialize graphical interface */
        initialize_CGI(&CGI);
        game.generate(&CGI, 5, true);
        game.calculate();
        game.print_statistic();

        /* Set loop flag */
        bool loop_flag = true;

        /* Define starting row and column and target row and column */
        int startRow, startCol, targetRow, targetCol;

        /* Perform one operation */
        while (1) {
            /* Determine if the game is over */
            if (!game.get_blank()) {
                cct_showstr(2, 5 + row * 2, "游戏结束! 按回车键重新开始游戏", COLOR_BLACK, COLOR_HYELLOW);
                cout << setw(42) << " ";
                while (1) {
                    char optn = _getch();
                    if (optn == 0 || optn == -32)
                        optn = _getch();
                    else if (optn == '\r')
                        break;
                }
                break;
            } //end of if (!game.get_blank())

            /* Set break flag */
            bool loop_break = false;

            /* Select the starting point */
            while (loop_flag) {
                /* Read keyboard and mouse events */
                int MAction, MRow, MCol, KeyCode1 = 0, KeyCode2 = 0;
                gmw_read_keyboard_and_mouse(&CGI, MAction, MRow, MCol, KeyCode1, KeyCode2);

                /* Determine whether to restart the game or exit */
                if (KeyCode1 == 'Q' || KeyCode1 == 'q')
                    return 0;
                else if (KeyCode1 == 'R' || KeyCode1 == 'r') {
                    loop_break = true;
                    break;
                }

                /* Print the selected ball */
                if ((MAction == MOUSE_LEFT_BUTTON_CLICK || MAction == MOUSE_LEFT_BUTTON_DOUBLE_CLICK) && !game.is_empty(MRow, MCol)) {
                    startRow = MRow;
                    startCol = MCol;
                    gmw_draw_block(&CGI, startRow, startCol, 10 * game.get_value(startRow, startCol), bdi);
                    break;
                }
            } //end of while (loop_flag)

            /* Determine whether to restart the game */
            if (loop_break)
                break;

            /* Select the target point */
            while (1) {
                /* Read keyboard and mouse events */
                int MAction, MRow, MCol, KeyCode1 = 0, KeyCode2 = 0;
                gmw_read_keyboard_and_mouse(&CGI, MAction, MRow, MCol, KeyCode1, KeyCode2);

                /* Determine whether to restart the game or exit */
                if (KeyCode1 == 'Q' || KeyCode1 == 'q')
                    return 0;
                else if (KeyCode1 == 'R' || KeyCode1 == 'r') {
                    loop_break = true;
                    break;
                }

                /* Print the selected ball or print the movement process */
                if ((MAction == MOUSE_LEFT_BUTTON_CLICK || MAction == MOUSE_LEFT_BUTTON_DOUBLE_CLICK)) {
                    /* Check if the selected point is empty */
                    if (game.is_empty(MRow, MCol)) {
                        /* Save the target row and column */
                        targetRow = MRow;
                        targetCol = MCol;

                        /* Initialize path */
                        struct point path[row * col];
                        for (int i = 0; i < row * col; i++) {
                            path[i].x = -1;
                            path[i].y = -1;
                        }

                        /* Initialize BFS_matrix */
                        int BFS_matrix[row][col];
                        for (int i = 0; i < row; i++)
                            for (int j = 0; j < col; j++)
                                BFS_matrix[i][j] = (game.get_value(i, j) > 0 ? 1 : 0);

                        /* Save the value of the selected ball */
                        int selectd_value = game.get_value(startRow, startCol);
                        game.set_value(startRow, startCol, 0);

                        /* Breadth-First Search */
                        if (BFS(BFS_matrix, startRow, startCol, targetRow, targetCol, path) == -1) {
                            /* Set the value of the starting ball */
                            game.set_value(startRow, startCol, selectd_value);

                            /* Set loop flag */
                            loop_flag = false;
                        } //end of if (BFS(BFS_matrix, startRow, startCol, targetRow, targetCol, path) == -1)
                        else {
                            /* Print moving path */
                            print_moving_path(&CGI, path, startRow, startCol, selectd_value);

                            /* Set the value of the target ball */
                            game.set_value(targetRow, targetCol, selectd_value);

                            /* Eliminate lines of five or more balls */
                            int eliminate_matrix[row + 2][col + 2] = { 0 };
                            if (game.is_eliminate(eliminate_matrix, targetRow, targetCol)) {
                                /* Print the blinking effect of elimination */
                                for (int d = 0; d < 7; d++) {
                                    Sleep(100);
                                    for (int i = 1; i <= row; i++)
                                        for (int j = 1; j <= col; j++)
                                            if (eliminate_matrix[i][j])
                                                gmw_draw_block(&CGI, i - 1, j - 1, (d == 6 ? 0 : (d % 2 ? 1 : 100)) * game.get_value(i - 1, j - 1), bdi);
                                }

                                /* Update statistic */
                                for (int i = 1; i <= row; i++)
                                    for (int j = 1; j <= col; j++)
                                        if (eliminate_matrix[i][j]) {
                                            game.statistic_deleted_plus(game.get_value(i - 1, j - 1) - 1);
                                            game.set_value(i - 1, j - 1, 0);
                                            game.print_score();
                                        }
                            } //end of if (game.is_eliminate(eliminate_matrix, targetRow, targetCol))

                            /* Generate the balls for the next round */
                            game.generate(&CGI, game.get_blank() > 3 ? 3 : game.get_blank());

                            /* Set loop flag */
                            loop_flag = true;
                        } //end of else
                    } //end of if (game.is_empty(MRow, MCol))
                    else {
                        /* Print the selected ball */
                        gmw_draw_block(&CGI, startRow, startCol, game.get_value(startRow, startCol), bdi);
                        startRow = MRow;
                        startCol = MCol;
                        gmw_draw_block(&CGI, startRow, startCol, 10 * game.get_value(startRow, startCol), bdi);

                        /* Set loop flag */
                        loop_flag = false;
                    } //end of else

                    /* Break the loop */
                    break;
                } //end of if ((MAction == MOUSE_LEFT_BUTTON_CLICK || MAction == MOUSE_LEFT_BUTTON_DOUBLE_CLICK))
            } //end of while (1)

            /* Determine whether to restart the game */
            if (loop_break)
                break;

            /* Calculate and print statistic */
            game.calculate();
            game.print_statistic();
        } //end of while (1)
    } //end of while (1)
}