/****************************************************************
 * Project Name:  Popstar
 * File Name:     popstar_main.cpp
 * File Function: 菜单函数的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/9/28
 ****************************************************************/

#include <iostream>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include "..\common\cmd_console_tools.h"
#include "popstar.h"

using namespace std;

/*
 * Function Name:    menu
 * Function:         Display menu items and read the correct option
 * Input Parameters: void
 * Return Value:     option
 */
static int menu(void)
{
    /* Set the console title and size */
    cct_setconsoletitle("消灭星星游戏 - 菜单");
    cct_setfontsize("新宋体", 24);
    cct_setconsoleborder(54, 26, 54, 26);

    /* Display menu items */
    cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
    cout << endl;
    cout << "  ┏━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
    cout << "  ┃                                              ┃" << endl;
    cout << "  ┃  ";
    cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
    cout << "  ★     消灭星星游戏     POPSTAR     ★  ";
    cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
    cout << "  ┃" << endl;
    cout << "  ┃                                              ┃" << endl;
    cout << "  ┣━━━━━━━━━━━━━━━━━━━━━━━┫" << endl;
    cout << "  ┃ A.命令行找出可消除项并标识                   ┃" << endl;
    cout << "  ┠┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┨" << endl;
    cout << "  ┃ B.命令行完成一次消除（分步骤显示）           ┃" << endl;
    cout << "  ┠┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┨" << endl;
    cout << "  ┃ C.命令行完成一关（分步骤显示）               ┃" << endl;
    cout << "  ┠┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┨" << endl;
    cout << "  ┃ D.伪图形界面下用鼠标选择一个色块（无分隔线） ┃" << endl;
    cout << "  ┠┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┨" << endl;
    cout << "  ┃ E.伪图形界面下用鼠标选择一个色块（有分隔线） ┃" << endl;
    cout << "  ┠┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┨" << endl;
    cout << "  ┃ F.伪图形界面完成一次消除（分步骤）           ┃" << endl;
    cout << "  ┠┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┨" << endl;
    cout << "  ┃ G.伪图形界面完整版                           ┃" << endl;
    cout << "  ┠┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┈┨" << endl;
    cout << "  ┃ Q.退出                                       ┃" << endl;
    cout << "  ┣━━━━━━━━━━━━━━━━━━━━━━━┫" << endl;
    cout << "  ┃ [请选择:]                                    ┃" << endl;
    cout << "  ┗━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
    cct_setcolor();
    cct_gotoxy(15, 22);

    /* Read the correct option */
    while (1) {
        char optn = _getch();
        if (optn == 0 || optn == -32)
            optn = _getch();
        else if ((optn >= 'A' && optn <= 'G') || (optn >= 'a' && optn <= 'g') || optn == 'Q' || optn == 'q') {
            cout << optn << endl;
            Sleep(300);
            if (optn != 'Q' && optn != 'q') {
                cct_setfontsize("新宋体", 16);
                cct_setconsoleborder(85, 47, 85, 9000);
            }
            return optn;
        }
        else
            continue;
    } // end of while (1)
}

/*
 * Function Name:    main
 * Function:         Main function
 * Return Value:     0
 */
int main()
{
    /* Generate random number seed */
    srand((unsigned int)(time(0)));

    /* Call the corresponding execution functions for each menu item */
    while (1) {
        switch (menu()) {
            case 'A':
            case 'a':
                cct_setconsoletitle("消灭星星游戏 - 命令行找出可消除项并标识");
                base_mark();
                break;
            case 'B':
            case 'b':
                cct_setconsoletitle("消灭星星游戏 - 命令行完成一次消除（分步骤显示）");
                base_eliminate();
                break;
            case 'C':
            case 'c':
                cct_setconsoletitle("消灭星星游戏 - 命令行完成一关（分步骤显示）");
                base_level();
                break;
            case 'D':
            case 'd':
                cct_setconsoletitle("消灭星星游戏 - 伪图形界面下用鼠标选择一个色块（无分隔线）");
                console_select(WITHOUT_DIVIDER);
                break;
            case 'E':
            case 'e':
                cct_setconsoletitle("消灭星星游戏 - 伪图形界面下用鼠标选择一个色块（有分隔线）");
                console_select(WITH_DIVIDER);
                break;
            case 'F':
            case 'f':
                cct_setconsoletitle("消灭星星游戏 - 伪图形界面完成一次消除（分步骤）");
                console_eliminate(WITHOUT_DIVIDER);
                break;
            case 'G':
            case 'g':
                cct_setconsoletitle("消灭星星游戏 - 伪图形界面完整版");
                console_fullVersion(WITH_DIVIDER);
                break;
            default:
                return 0;
        } // end of switch (menu())
        wait_for_end();
    } // end of while (1)
}