/****************************************************************
 * Project Name:  Conway_Life_Game
 * File Name:     conway_main.cpp
 * File Function: 主体函数的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/11/21
 ****************************************************************/

#include <Windows.h>
#include <ctime>
#include <conio.h>
#include <graphics.h>
#include "conway.h"

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

    /* Initialize the graphical interface */
    initialize_graphics();

    /* Initialize conway object */
    Conway conway(initialAliveCount);

    /* Play Conway life game */
    while (true) {
        conway.refreshMap();
        Sleep(delayTime);
        if (_kbhit())
            return 0;
    }
}