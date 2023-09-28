/****************************************************************
 * Project Name:  Popstar
 * File Name:     popstar_main.cpp
 * File Function: �˵�������ʵ��
 * Author:        Jishen Lin (�ּ���)
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
    cct_setconsoletitle("����������Ϸ - �˵�");
    cct_setfontsize("������", 24);
    cct_setconsoleborder(54, 26, 54, 26);

    /* Display menu items */
    cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
    cout << endl;
    cout << "  ��������������������������������������������������" << endl;
    cout << "  ��                                              ��" << endl;
    cout << "  ��  ";
    cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
    cout << "  ��     ����������Ϸ     POPSTAR     ��  ";
    cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
    cout << "  ��" << endl;
    cout << "  ��                                              ��" << endl;
    cout << "  �ǩ�����������������������������������������������" << endl;
    cout << "  �� A.�������ҳ����������ʶ                   ��" << endl;
    cout << "  �ĩ�����������������������������������������������" << endl;
    cout << "  �� B.���������һ���������ֲ�����ʾ��           ��" << endl;
    cout << "  �ĩ�����������������������������������������������" << endl;
    cout << "  �� C.���������һ�أ��ֲ�����ʾ��               ��" << endl;
    cout << "  �ĩ�����������������������������������������������" << endl;
    cout << "  �� D.αͼ�ν����������ѡ��һ��ɫ�飨�޷ָ��ߣ� ��" << endl;
    cout << "  �ĩ�����������������������������������������������" << endl;
    cout << "  �� E.αͼ�ν����������ѡ��һ��ɫ�飨�зָ��ߣ� ��" << endl;
    cout << "  �ĩ�����������������������������������������������" << endl;
    cout << "  �� F.αͼ�ν������һ���������ֲ��裩           ��" << endl;
    cout << "  �ĩ�����������������������������������������������" << endl;
    cout << "  �� G.αͼ�ν���������                           ��" << endl;
    cout << "  �ĩ�����������������������������������������������" << endl;
    cout << "  �� Q.�˳�                                       ��" << endl;
    cout << "  �ǩ�����������������������������������������������" << endl;
    cout << "  �� [��ѡ��:]                                    ��" << endl;
    cout << "  ��������������������������������������������������" << endl;
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
                cct_setfontsize("������", 16);
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
                cct_setconsoletitle("����������Ϸ - �������ҳ����������ʶ");
                base_mark();
                break;
            case 'B':
            case 'b':
                cct_setconsoletitle("����������Ϸ - ���������һ���������ֲ�����ʾ��");
                base_eliminate();
                break;
            case 'C':
            case 'c':
                cct_setconsoletitle("����������Ϸ - ���������һ�أ��ֲ�����ʾ��");
                base_level();
                break;
            case 'D':
            case 'd':
                cct_setconsoletitle("����������Ϸ - αͼ�ν����������ѡ��һ��ɫ�飨�޷ָ��ߣ�");
                console_select(WITHOUT_DIVIDER);
                break;
            case 'E':
            case 'e':
                cct_setconsoletitle("����������Ϸ - αͼ�ν����������ѡ��һ��ɫ�飨�зָ��ߣ�");
                console_select(WITH_DIVIDER);
                break;
            case 'F':
            case 'f':
                cct_setconsoletitle("����������Ϸ - αͼ�ν������һ���������ֲ��裩");
                console_eliminate(WITHOUT_DIVIDER);
                break;
            case 'G':
            case 'g':
                cct_setconsoletitle("����������Ϸ - αͼ�ν���������");
                console_fullVersion(WITH_DIVIDER);
                break;
            default:
                return 0;
        } // end of switch (menu())
        wait_for_end();
    } // end of while (1)
}