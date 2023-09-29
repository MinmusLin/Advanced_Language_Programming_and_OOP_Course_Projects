/****************************************************************
 * Project Name:  Simulated_LED_Screen
 * File Name:     LED_main.cpp
 * File Function: �˵�������ʵ��
 * Author:        Jishen Lin (�ּ���)
 * Update Date:   2023/9/30
 ****************************************************************/

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "../common/cmd_console_tools.h"

using namespace std;

/* Function declarations in LED_simulated_screen.cpp */
void simulated_screen(bool is_simplified);
void simulated_screen(void);

/* Function declaration in LED_retrieve_bitinfo.cpp */
void retrieve_bitinfo(bool is_simplified, char _highByte = 0, char _lowByte = 0, bool _bitmap[][16] = { 0 });

/*
 * Function Name:    menu
 * Function:         Display menu items and read the correct option
 * Input Parameters: void
 * Return Value:     option
 */
static int menu(void)
{
    /* Generate random number seed */
    srand((unsigned int)(time(0)));

    /* Set the console */
    cct_setconsoletitle("Simulated LED Screen");
    cct_setfontsize("������", 16);
    cct_setcolor();
    cct_setconsoleborder(120, 40, 120, 9000);

    /* Display menu items */
    cout << "                    ģ��LED��ʾ��" << endl;
    cout << "                 Simulated LED Screen" << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "  1.��GB2312��Ӧ�ļ������ĺ��ֿ��ж�ȡ16*16������Ϣ" << endl;
    cout << "    Retrieve 16*16 bitmap information from HZK16" << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "  2.��GB2312��Ӧ�ķ������ĺ��ֿ��ж�ȡ16*16������Ϣ" << endl;
    cout << "    Retrieve 16*16 bitmap information from HZK16F" << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "  3.ģ��LED��ʾ�����������ģ�" << endl; 
    cout << "    Simulated LED Screen (Simplified Chinese)" << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "  4.ģ��LED��ʾ�����������ģ�" << endl;
    cout << "    Simulated LED Screen (Traditional Chinese)" << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "  5.ģ��LED��ʾ������ǰ���ں�ʱ�䣩" << endl;
    cout << "    Simulated LED Screen (Current Date and Time)" << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "  6.�˳�" << endl;
    cout << "    Quit" << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "  [��ѡ��:] ";

    /* Read the correct option */
    while (true) {
        char optn = _getch();
        if (optn == 0 || optn == -32)
            optn = _getch();
        else if (optn >= '1' && optn <= '6') {
            cout << optn << endl << endl;
            Sleep(300);
            return optn;
        }
        else
            continue;
    }
}

/*
 * Function Name:    main
 * Function:         Main function
 * Return Value:     0
 */
int main()
{
    while (true) {
        switch (menu()) {
            case '1':
                cct_setconsoletitle("Retrieve 16*16 bitmap information from HZK16");
                retrieve_bitinfo(true);
                break;
            case '2':
                cct_setconsoletitle("Retrieve 16*16 bitmap information from HZK16F");
                retrieve_bitinfo(false);
                break;
            case '3':
                cct_setconsoletitle("Simulated LED Screen (Simplified Chinese)");
                simulated_screen(true);
                break;
            case '4':
                cct_setconsoletitle("Simulated LED Screen (Traditional Chinese)");
                simulated_screen(false);
                break;
            case '5':
                cct_setconsoletitle("Simulated LED Screen (Current Date and Time)");
                simulated_screen();
                break;
            default:
                return 0;
        }
    }
}