/****************************************************************
 * Project Name:  Matrix_Operations_and_Image_Processing
 * File Name:     MOIP_main.cpp
 * File Function: 菜单函数的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/9/27
 ****************************************************************/

#include <iostream>
#include "..\common\cmd_console_tools.h"
#include "MOIP.h"

using namespace std;

/*
 * Function Name:    main
 * Function:         Main function
 * Return Value:     0
 */
int main()
{
    /* Call the menu function and enter the different functions */
    while (1) {
        switch (menu()) {
            case 'A':
                Matrix_Determinant();
                break;
            case 'B':
                Matrix_Addition();
                break;
            case 'C':
                Matrix_Scalar_Multiplication();
                break;
            case 'D':
                Matrix_Transposition();
                break;
            case 'E':
                Matrix_Multiplication();
                break;
            case 'F':
                Matrix_Hadamard();
                break;
            case 'G':
                Matrix_Convolution();
                break;
            case 'H':
                Image_Convolution();
                break;
            case 'I':
                Image_Otsu();
                break;
            case 'J':
                Image_Segmentation();
                break;
            case 'Q':
                return 0;
        }
    }
}