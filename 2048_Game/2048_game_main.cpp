/****************************************************************
 * Project Name:  2048_Game
 * File Name:     2048_game_main.cpp
 * File Function: 主体函数的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/9/24
 ****************************************************************/

#include <iostream>
#include "../common/cmd_console_tools.h"
#include "../common/lib_gmw_tools.h"
#include "2048_game.h"
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

    /* Play 2048 game */
    while (1) {
        /* Initialize GAME and CONSOLE_GRAPHICS_INFO class */
        int row, col;
        menu(row, col);
        class GAME game = { row, col };
        CONSOLE_GRAPHICS_INFO CGI;
        initialize_CGI(&CGI, row, col);

        /* Randomly generate initial color blocks */
        game.generate(&CGI);
        game.generate(&CGI);

        /* Read keyboard and mouse events */
        while (1) {
            /* Determine if the game is over */
            if (print_prompt(game.get_score(), game.gameover_judgment()))
                break;

            /* Read keyboard and mouse events */
            int MAction, MRow, MCol, KeyCode1 = 0, KeyCode2 = 0;
            gmw_read_keyboard_and_mouse(&CGI, MAction, MRow, MCol, KeyCode1, KeyCode2, false);

            /* Determine whether to quit the game */
            if (KeyCode1 == 27)
                break;

            /* Move coordinates using keyboard arrow keys */
            if (KeyCode1 == 224 && (KeyCode2 == KB_ARROW_UP || KeyCode2 == KB_ARROW_DOWN || KeyCode2 == KB_ARROW_LEFT || KeyCode2 == KB_ARROW_RIGHT)) {
                switch (KeyCode2) {
                    case KB_ARROW_UP:
                        game.move_down_to_up(&CGI);
                        break;
                    case KB_ARROW_DOWN:
                        game.move_up_to_down(&CGI);
                        break;
                    case KB_ARROW_LEFT:
                        game.move_right_to_left(&CGI);
                        break;
                    case KB_ARROW_RIGHT:
                        game.move_left_to_right(&CGI);
                        break;
                    default:
                        break;
                } //end of switch (KeyCode2)
                cct_showint(26, 0, game.get_score());
                if (game.gameover_judgment() == 2)
                    game.generate(&CGI);
            } //end of if (KeyCode1 == 224 && (KeyCode2 == KB_ARROW_UP || KeyCode2 == KB_ARROW_DOWN || KeyCode2 == KB_ARROW_LEFT || KeyCode2 == KB_ARROW_RIGHT))
        } //end of while (1)
    } //end of while (1)
}