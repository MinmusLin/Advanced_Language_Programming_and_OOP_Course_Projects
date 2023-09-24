/****************************************************************
 * Project Name:  Tetris
 * File Name:     tetris_main.cpp
 * File Function: ���庯����ʵ��
 * Author:        Jishen Lin (�ּ���)
 * Update Date:   2023/9/25
 ****************************************************************/

#include <ctime>
#include "tetris.h"
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

    /* Process initialization work */
    initialize_graphics();

    system("pause");

    /* Program ends */
    return 0;
}