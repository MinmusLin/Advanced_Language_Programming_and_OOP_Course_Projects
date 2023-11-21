/****************************************************************
 * Project Name:  Tetris
 * File Name:     tetris_main.cpp
 * File Function: ���庯����ʵ��
 * Author:        Jishen Lin (�ּ���)
 * Update Date:   2023/11/21
 ****************************************************************/

#include <ctime>
#include "tetris.h"

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

    /* Process initialization work */
    initializeGraphics();

    /* Play Tetris game */
    while (true) {
        bool flag = tetris();
        if (flag)
            continue;
        else
            return 0;
    }
}