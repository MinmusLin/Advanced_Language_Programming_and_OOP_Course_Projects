/****************************************************************
 * Project Name:  Hanoi_Tower_Demonstration
 * File Name:     hanoi_main.cpp
 * File Function: 主体函数的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/9/28
 ****************************************************************/

#include <iostream>
#include "..\common\cmd_console_tools.h"
#include "hanoi.h"

using namespace std;

/*
 * Function Name:    main
 * Function:         Main function
 * Return Value:     0
 */
int main()
{
    cct_setconsoletitle("Hanoi Tower Demonstration");
    cct_setfontsize("新宋体", 16);
    cct_setconsoleborder(120, 40, 120, 9000);
    while(1) {
        int optn = menu();
        switch (optn) {
            case '1':
                optn_1_fundamentSolution_base();
                break;
            case '2':
                optn_2_fundamentSolution_stepRecord();
                break;
            case '3':
                optn_3_arrayDisplay_horizontal();
                break;
            case '4':
                optn_4_arrayDisplay_horizontalVertical();
                break;
            case '5':
                optn_5_graphicalSolution_printCylinders();
                break;
            case '6':
                optn_6_graphicalSolution_printPlates();
                break;
            case '7':
                optn_7_graphicalSolution_firstMove();
                break;
            case '8':
                optn_8_graphicalSolution_autoMove();
                break;
            case '9':
                optn_9_graphicalSolution_game();
                break;
            default:
                cct_gotoxy(0, 37);
                return 0;
        }
    }
}