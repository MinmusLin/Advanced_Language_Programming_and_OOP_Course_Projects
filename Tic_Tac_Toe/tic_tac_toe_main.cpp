/****************************************************************
 * Project Name:  Tic_Tac_Toe
 * File Name:     tic_tac_toe_main.cpp
 * File Function: 主体函数的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/11/21
 ****************************************************************/

#include <iostream>
#include "..\common\cmd_console_tools.h"
#include "tic_tac_toe.h"

/* Namespace */
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

    /* Set the console */
    cct_setconsoletitle("Tic Tac Toe");
    cct_setfontsize("新宋体", 16);
    cct_setconsoleborder(120, 40, 120, 9000);

    /* Print menu and play Tic-Tac-Toe game */
    while (true) {
        int optn = menu();
        switch (optn) {
            case 1:
            case 2:
            case 3:
            case 4: {
                GridStatus gridStatus[BOARD_SIZE][BOARD_SIZE] = { Empty };
                for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
                    cout << ">>> 第 " << i + 1 << " 轮" << endl << endl;
                    while (true) {
                        int r, c;
                        switch (optn) {
                            case 1:
                                cout << (i % 2 ? "后手(○)" : "先手(×)") << "请输入本轮落子行数: ";
                                r = input_digit(1, BOARD_SIZE);
                                cout << (i % 2 ? "后手(○)" : "先手(×)") << "请输入本轮落子列数: ";
                                c = input_digit(1, BOARD_SIZE);
                                break;
                            case 2:
                                if (i % 2) {
                                    cout << "后手(○)请输入本轮落子行数: ";
                                    r = input_digit(1, BOARD_SIZE);
                                    cout << "后手(○)请输入本轮落子列数: ";
                                    c = input_digit(1, BOARD_SIZE);
                                }
                                else {
                                    find_next_move_to_win(gridStatus, r, c);
                                    cout << "先手(×)请输入本轮落子行数: " << ++r << endl;
                                    cout << "先手(×)请输入本轮落子列数: " << ++c << endl;
                                }
                                break;
                            case 3:
                                if (i % 2) {
                                    find_next_move_to_win(gridStatus, r, c);
                                    cout << "后手(○)请输入本轮落子行数: " << ++r << endl;
                                    cout << "后手(○)请输入本轮落子列数: " << ++c << endl;
                                }
                                else {
                                    cout << "先手(×)请输入本轮落子行数: ";
                                    r = input_digit(1, BOARD_SIZE);
                                    cout << "先手(×)请输入本轮落子列数: ";
                                    c = input_digit(1, BOARD_SIZE);
                                }
                                break;
                            case 4:
                                find_next_move_to_win(gridStatus, r, c);
                                cout << (i % 2 ? "后手(○)" : "先手(×)") << "请输入本轮落子行数: " << ++r << endl;
                                cout << (i % 2 ? "后手(○)" : "先手(×)") << "请输入本轮落子列数: " << ++c << endl;
                                break;
                            default:
                                exit(-1);
                        }
                        if (gridStatus[r - 1][c - 1] == Empty) {
                            gridStatus[r - 1][c - 1] = (i % 2 ? SecondPlayer : FirstPlayer);
                            cout << endl;
                            print_grid_status(gridStatus);
                            cout << endl;
                            break;
                        }
                        else
                            cout << endl << ">>> 该位置已被占用，请重新输入!" << endl << endl;
                    }
                    GridStatus winner = check_win(gridStatus);
                    if (winner == FirstPlayer || winner == SecondPlayer) {
                        print_winner(winner);
                        break;
                    }
                    else if (winner == Empty && i == BOARD_SIZE * BOARD_SIZE - 1)
                        cout << ">>> 游戏结束! 平局!" << endl << endl;
                }
                system("pause");
                break;
            }
            default:
                return 0;
        }
    }
}