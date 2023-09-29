/****************************************************************
 * Project Name:  Tic_Tac_Toe
 * File Name:     tic_tac_toe_main.cpp
 * File Function: ���庯����ʵ��
 * Author:        Jishen Lin (�ּ���)
 * Update Date:   2023/9/30
 ****************************************************************/

#include <iostream>
#include "..\common\cmd_console_tools.h"
#include "tic_tac_toe.h"

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
    cct_setfontsize("������", 16);
    cct_setconsoleborder(120, 40, 120, 9000);

    /* Print menu and play Tic-Tac-Toe game */
    while (true) {
        switch (menu()) {
            case 1:
            case 2:
            case 3:
            case 4: {
                /* Initialize grid status */
                GridStatus gridStatus[BOARD_SIZE][BOARD_SIZE] = { Empty };


                for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
                    cout << ">>> �� " << i + 1 << " ��" << endl << endl;
                    while (true) {
                        cout << (i % 2 ? "����(��)" : "����(��)") << "�����뱾����������: ";
                        int r = input_digit(1, BOARD_SIZE);
                        cout << (i % 2 ? "����(��)" : "����(��)") << "�����뱾����������: ";
                        int c = input_digit(1, BOARD_SIZE);
                        if (gridStatus[r - 1][c - 1] == Empty) {
                            gridStatus[r - 1][c - 1] = (i % 2 ? SecondPlayer : FirstPlayer);
                            cout << endl;
                            print_grid_status(gridStatus);
                            cout << endl;
                            break;
                        }
                        else
                            cout << endl << ">>> ��λ���ѱ�ռ�ã�����������!" << endl << endl;
                    }
                }


                cout << "��Ϸ����!" << endl;


                cout << endl;
                system("pause");
                break;
            }
            default:
                return 0;
        }
    }
}