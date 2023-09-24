/****************************************************************
 * Project Name:  Love_Code
 * File Name:     lovecode_main.cpp
 * File Function: ���庯����ʵ��
 * Author:        Jishen Lin (�ּ���)
 * Update Date:   2023/9/24
 ****************************************************************/

#include <iostream>
#include "..\common\cmd_console_tools.h"
#include "lovecode.h"
#include "pixel_matrixs.h"
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

    /* Set up the console */
    cct_setconsoletitle("Love Code");
    cct_setfontsize("������", 1);
    cct_setconsoleborder(ORIGIN_OF_ABSCISSA * 4, ORIGIN_OF_ORDINATE * 2 + 16 * 3);
    cct_setcursor(CURSOR_INVISIBLE);

    /* Print starting captions */
    print_starting_captions();
    cct_cls();

    /* Print heart shape */
    print_heart_shape();

    return 0;
}