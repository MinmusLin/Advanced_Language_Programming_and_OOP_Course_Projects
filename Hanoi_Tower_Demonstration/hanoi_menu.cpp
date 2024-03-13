/****************************************************************
 * Project Name:  Hanoi_Tower_Demonstration
 * File Name:     hanoi_menu.cpp
 * File Function: �˵�������ʵ��
 * Author:        Jishen Lin (�ּ���)
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
    cout << "                           ��ŵ���ۺ���ʾ�������" << endl;
    cout << "                          Hanoi Tower Demonstration" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "  1.������" << endl;
    cout << "    Basic Solution" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "  2.�����⣨������¼��" << endl;
    cout << "    Basic Solution (Step Count)" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "  3.�ڲ�������ʾ������" << endl;
    cout << "    Display Internal Array (Horizontal)" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "  4.�ڲ�������ʾ������ + ����" << endl;
    cout << "    Display Internal Array (Vertical + Horizontal)" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "  5.ͼ�ν⣨Ԥ����������Բ����" << endl;
    cout << "    Graphic Solution (Preparation: Draw Three Cylinders)" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "  6.ͼ�ν⣨Ԥ��������ʼ���ϻ�n�����ӣ�" << endl;
    cout << "    Graphic Solution (Preparation: Place n Discs on the Starting Cylinder)" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "  7.ͼ�ν⣨Ԥ������һ���ƶ���" << endl;
    cout << "    Graphic Solution (Preparation: First Move)" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "  8.ͼ�ν⣨�Զ��ƶ��汾��" << endl;
    cout << "    Graphic Solution (Automatic Move Version)" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "  9.ͼ�ν⣨��Ϸ�棩" << endl;
    cout << "    Graphic Solution (Game Version)" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "  0.�˳�" << endl;
    cout << "    Quit" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "  [��ѡ��:] ";
    char optn;
    while (true) {
        optn = _getch();
        if (optn >= '0' && optn <= '9') {
            cout << optn << endl << endl << endl;
            return optn;
        }
    }
}