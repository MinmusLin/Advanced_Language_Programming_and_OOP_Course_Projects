/****************************************************************
 * Project Name:  Gluttonous_Snake
 * File Name:     gluttonous_snake_main.cpp
 * File Function: ���庯����ʵ��
 * Author:        Jishen Lin (�ּ���)
 * Update Date:   2023/9/28
 ****************************************************************/

#include <ctime>
#include "gluttonous_snake.h"

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

    /* Display starting page */
    startPage();

    /* Play gluttonous snake game */
    while (true) {
        Mode mode = menu();
        if (mode == Quit) {
            closegraph();
            return 0;
        }
        else if (mode == ResetHighestScore)
            continue;
        else
            gluttonous_snake(mode);
    }
}