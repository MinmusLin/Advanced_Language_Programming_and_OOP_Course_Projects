/****************************************************************
 * Project Name:  Hanoi_Tower_Demonstration
 * File Name:     hanoi_menu.cpp
 * File Function: 菜单函数的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/11/21
 ****************************************************************/

#include <iostream>
#include <conio.h>
#include "../common/cmd_console_tools.h"
#include "hanoi.h"

/* Namespace */
using namespace std;

/*
 * Function Name:    menu
 * Function:         Display menu items and read the correct option
 * Input Parameters: void
 * Return Value:     option
 */
int menu(void)
{
    cout << "                           汉诺塔综合演示解决方案" << endl;
    cout << "                          Hanoi Tower Demonstration" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "  1.基本解" << endl;
    cout << "    Basic Solution" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "  2.基本解（步数记录）" << endl;
    cout << "    Basic Solution (Step Count)" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "  3.内部数组显示（横向）" << endl;
    cout << "    Display Internal Array (Horizontal)" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "  4.内部数组显示（纵向 + 横向）" << endl;
    cout << "    Display Internal Array (Vertical + Horizontal)" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "  5.图形解（预备：画三个圆柱）" << endl;
    cout << "    Graphic Solution (Preparation: Draw Three Cylinders)" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "  6.图形解（预备：在起始柱上画n个盘子）" << endl;
    cout << "    Graphic Solution (Preparation: Place n Discs on the Starting Cylinder)" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "  7.图形解（预备：第一次移动）" << endl;
    cout << "    Graphic Solution (Preparation: First Move)" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "  8.图形解（自动移动版本）" << endl;
    cout << "    Graphic Solution (Automatic Move Version)" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "  9.图形解（游戏版）" << endl;
    cout << "    Graphic Solution (Game Version)" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "  0.退出" << endl;
    cout << "    Quit" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "  [请选择:] ";
    char optn;
    while (true) {
        optn = _getch();
        if (optn >= '0' && optn <= '9') {
            cout << optn << endl << endl << endl;
            return optn;
        }
    }
}