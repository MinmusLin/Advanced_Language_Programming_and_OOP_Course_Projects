/****************************************************************
 * Project Name:  Matrix_Operations_and_Image_Processing
 * File Name:     MOIP_tools.cpp
 * File Function: 工具函数的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/9/24
 ****************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "..\common\cmd_console_tools.h"
#include "MOIP.h"
using namespace std;

/*
 * Function Name:    menu
 * Function:         Display menu items and read the correct option
 * Input Parameters: void
 * Return Value:     option
 */
int menu(void)
{
    /* Set the console */
    cct_setconsoletitle("矩阵运算与图像处理");
    cct_setfontsize("新宋体", 16);
    cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
    cct_setconsoleborder(consoleCol, consoleRow, consoleCol, consoleRow);

    /* Print menu items */
    print_framework();
    cct_showstr(4, 2, "菜单界面", COLOR_HWHITE, COLOR_BLACK);
    char items[][42] = { "A.矩阵行列式运算","B.矩阵加法运算","C.矩阵数乘运算","D.矩阵转置运算","E.矩阵乘法运算","F.矩阵Hadamard(哈达马)乘积运算","G.矩阵卷积运算","H.矩阵卷积运算应用","I.Otsu算法(大津算法)","J.Segmentation算法(传统分割算法)","[请选择:] " };
    for (int i = 0; i < 11; i++)
        cct_showstr(4, 6 + 2 * i, items[i], COLOR_HWHITE, COLOR_BLACK);

    /* Read the option */
    while (1) {
        char optn = _getch();
        if (optn == 0 || optn == -32)
            optn = _getch();
        else if ((optn >= 'A' && optn <= 'J') || (optn >= 'a' && optn <= 'j') || optn == 'Q' || optn == 'q') {
            optn = (optn >= 'a' ? optn - 32 : optn);
            cout << optn;
            if (optn != 'Q' && optn != 'q') {
                cct_showstr(4, 2, &items[optn - 'A'][2], COLOR_HWHITE, COLOR_BLACK);
                char title[69] = "矩阵运算与图像处理 - ";
                strcat(title, &items[optn - 'A'][2]);
                cct_setconsoletitle(title);
            }
            Sleep(300);
            clear_content();
            return optn;
        }
        else
            continue;
    }
}

/*
 * Function Name:    print_prompt
 * Function:         Print the prompt
 * Input Parameters: const char prompt[]
 *                   int bg_color
 *                   int fg_color
 * Return Value:     void
 */
void print_prompt(const char prompt[], int bg_color, int fg_color)
{
    cct_showch(40, 2, ' ', COLOR_HWHITE, COLOR_BLACK, consoleCol - 44);
    cct_showstr(40, 2, prompt, bg_color, fg_color);
}

/*
 * Function Name:    clear_content
 * Function:         Clear the content
 * Input Parameters: void
 * Return Value:     void
 */
void clear_content(void)
{
    for (int i = 5; i <= consoleRow - 4; i++)
        cct_showch(2, i, ' ', COLOR_HWHITE, COLOR_BLACK, consoleCol - 4);
}

/*
 * Function Name:    print_framework
 * Function:         Print interface framework
 * Input Parameters: void
 * Return Value:     void
 */
void print_framework(void)
{
    cct_cls();
    cout << "╔";
    for (int i = 0; i < consoleCol / 2 - 2; i++)
        cout << ((i == 17) ? "╦" : "═");
    cout << "╗";
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < consoleCol / 2; j++)
            cout << ((j == 0 || j == 18 || j == consoleCol / 2 - 1) ? "║" : "  ");
    cout << "╠";
    for (int i = 0; i < consoleCol / 2 - 2; i++)
        cout << ((i == 17) ? "╩" : "═");
    cout << "╣";
    clear_content();
    for (int i = 0; i < consoleRow - 8; i++) {
        cct_showstr(0, 5 + i, "║", COLOR_HWHITE, COLOR_BLACK);
        cct_showstr(consoleCol - 2, 5 + i, "║", COLOR_HWHITE, COLOR_BLACK);
    }
    cout << "╚";
    for (int i = 0; i < consoleCol / 2 - 2; i++)
        cout << "═";
    cout << "╝ [注意事项:] (1)矩阵行数和列数范围为2~5 (2)输入错误则返回菜单 (3)在菜单界面按Q/q键退出程序";
}

/*
 * Function Name:    enter_digit
 * Function:         Input a number
 * Input Parameters: int x
 *                   int y
 *                   const char* prompt
 * Return Value:     a number
 * Notes:            The range of the number: 2~5
 */
int enter_digit(int x, int y, const char* prompt)
{
    cct_showstr(x, y, prompt, COLOR_HWHITE, COLOR_BLACK);
    while (1) {
        char input = _getch();
        if (input == 0 || input == -32)
            input = _getch();
        else if (input >= '2' && input <= '5') {
            cout << input;
            Sleep(300);
            return input - '0';
        }
        else
            continue;
    }
}

/*
 * Function Name:    print_matrix
 * Function:         Print matrix
 * Input Parameters: int x
 *                   int y
 *                   int r
 *                   int c
 * Return Value:     void
 */
void print_matrix(int x, int y, int r, int c)
{
    cct_showstr(x, y, "┌", COLOR_HWHITE, COLOR_BLACK);
    cct_showstr(x + 10 * c + 2, y, "┐", COLOR_HWHITE, COLOR_BLACK);
    for (int i = 1; i <= r; i++) {
        cct_showstr(x, y + i, "│", COLOR_HWHITE, COLOR_BLACK);
        cct_showstr(x + 10 * c + 2, y + i, "│", COLOR_HWHITE, COLOR_BLACK);
    }
    cct_showstr(x, y + r + 1, "└", COLOR_HWHITE, COLOR_BLACK);
    cct_showstr(x + 10 * c + 2, y + r + 1, "┘", COLOR_HWHITE, COLOR_BLACK);
}

/*
 * Function Name:    enter_element
 * Function:         Input a matrix element
 * Input Parameters: double matrix[][maxCol]
 *                   int r
 *                   int c
 *                   int x
 *                   int y
 * Return Value:     true / false
 */
bool enter_element(double matrix[][maxCol], int r, int c, int x, int y)
{
    cct_gotoxy(x + 3 + 10 * c, y + 1 + r);
    cin >> matrix[r][c];
    bool ret = cin.good() ? true : false;
    cin.clear();
    cin.ignore(65536, '\n');
    return ret;
}

/*
 * Function Name:    input_matrix
 * Function:         Input matrix
 * Input Parameters: double matrix[][maxCol]
 *                   int row
 *                   int col
 *                   int x
 *                   int y
 *                   const char sign[]
 *                   bool is_prompt
 * Return Value:     true / false
 */
bool input_matrix(double matrix[][maxCol], int row, int col, int x, int y, const char sign[], bool is_prompt)
{
    if (is_prompt) {
        cct_showstr(x, y, "请输入", COLOR_HWHITE, COLOR_BLACK);
        if (row == col)
            cout << row << "阶方阵" << sign << ":";
        else
            cout << row << "阶×" << col << "阶矩阵" << sign << ":";
    }
    print_matrix(x, y + 1, row, col);
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            if (!enter_element(matrix, i, j, x, y + 1)) {
                print_prompt("输入错误! ", COLOR_HWHITE, COLOR_RED);
                system("pause");
                return false;
            }
    return true;
}

/*
 * Function Name:    output_matrix
 * Function:         Output matrix
 * Input Parameters: double matrix[][maxCol]
 *                   int row
 *                   int col
 *                   int x
 *                   int y
 *                   const char sign[]
 *                   bool is_prompt
 * Return Value:     void
 */
void output_matrix(double matrix[][maxCol], int row, int col, int x, int y, const char sign[], bool is_prompt)
{
    if (is_prompt) {
        cct_gotoxy(x, y);
        if (row == col)
            cout << row << "阶方阵" << sign << " =";
        else
            cout << row << "阶×" << col << "阶矩阵" << sign << " =";
    }
    print_matrix(x, y + 1, row, col);
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++) {
            cct_gotoxy(x + 3 + 10 * j, y + 2 + i);
            cout << matrix[i][j];
        }
}

/*
 * Function Name:    calculate_determinant
 * Function:         Calculate determinant
 * Input Parameters: double matrix[][maxCol]
 *                   int n
 * Return Value:     determinant
 */
double calculate_determinant(double matrix[][maxCol], int n)
{
    if (n == 1)
        return matrix[0][0];
    else if (n == 2)
        return matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
    else {
        double determinant = 0.0, minor[maxRow][maxCol] = { 0 };
        for (int i = 0; i < n; i++) {
            int minorRow = 0;
            for (int j = 1; j < n; j++) {
                int minorCol = 0;
                for (int k = 0; k < n; k++) {
                    if (k == i)
                        continue;
                    minor[minorRow][minorCol] = matrix[j][k];
                    minorCol++;
                }
                minorRow++;
            }
            determinant += matrix[0][i] * (i % 2 ? -1 : 1) * calculate_determinant(minor, n - 1);
        }
        return determinant;
    }
}

/*
 * Function Name:    get_kernel
 * Function:         Get kernel matrix and kernel sum
 * Input Parameters: int kernel[][kernelSize]
 *                   int& kernel_sum
 * Return Value:     true / false
 */
bool get_kernel(int kernel[][kernelSize], int& kernel_sum)
{
    /* Initialize kernel matrixs */
    int kernel_matrixs[][kernelSize][kernelSize] = {
        {1,1,1,1,1,1,1,1,1},
        {1,2,1,2,4,2,1,2,1},
        {-1,-1,-1,-1,9,-1,-1,-1,-1},
        {-1,-2,-1,0,0,0,1,2,1},
        {-1,0,1,-2,0,2,-1,0,1},
        {-1,-1,0,-1,0,1,0,1,1},
    };

    /* Output kernel matrixs */
    for (int k = 0; k < 6; k++) {
        cct_gotoxy(k % 2 ? 42 : 4, 6 + k / 2 * 7);
        cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
        cout << ((k == 0 || k == 1) ? "模糊" : (k == 2 ? "锐化" : "边缘")) << "卷积核矩阵" << char('A' + k) << " =";
        print_matrix(k % 2 ? 42 : 4, 7 + k / 2 * 7, kernelSize, kernelSize);
        for (int i = 0; i < kernelSize; i++)
            for (int j = 0; j < kernelSize; j++) {
                cct_gotoxy(7 + 10 * j + (k % 2) * 38, 8 + i + k / 2 * 7);
                cout << kernel_matrixs[k][i][j];
            }
    }

    /* Select or input a kernel matrix */
    cct_showstr(4, 6 + 3 * (kernelSize + 4), "请选择卷积核矩阵(选择G输入自定义卷积核矩阵): ", COLOR_HWHITE, COLOR_BLACK);
    while (1) {
        char optn = _getch();
        if (optn == 0 || optn == -32)
            optn = _getch();
        else if ((optn >= 'A' && optn <= 'G') || (optn >= 'a' && optn <= 'g')) {
            optn = (optn >= 'a' ? optn - 32 : optn);
            cout << optn;
            Sleep(300);
            if (optn == 'G') {
                cct_showstr(4, 8 + 3 * (kernelSize + 4), "请输入自定义卷积核矩阵G:", COLOR_HWHITE, COLOR_BLACK);
                print_matrix(4, 9 + 3 * (kernelSize + 4), kernelSize, kernelSize);
                for (int i = 0; i < kernelSize; i++)
                    for (int j = 0; j < kernelSize; j++) {
                        cct_gotoxy(7 + 10 * j, 10 + 3 * (kernelSize + 4) + i);
                        cin >> kernel[i][j];
                        if (!cin.good()) {
                            cin.clear();
                            cin.ignore(65536, '\n');
                            print_prompt("输入错误! ", COLOR_HWHITE, COLOR_RED);
                            system("pause");
                            return false;
                        }
                    }
            }
            else {
                for (int i = 0; i < kernelSize; i++)
                    for (int j = 0; j < kernelSize; j++)
                        kernel[i][j] = kernel_matrixs[optn - 'A'][i][j];
            }
            kernel_sum = 0;
            for (int i = 0; i < kernelSize; i++)
                for (int j = 0; j < kernelSize; j++)
                    kernel_sum += kernel[i][j];
            clear_content();
            return true;
        }
        else
            continue;
    }
}

/*
 * Function Name:    calculate_Otsu_threshold
 * Function:         calculate Otsu threshold
 * Input Parameters: Mat grayImage
 *                   int height
 *                   int width
 * Return Value:     Otsu threshold
 */
int calculate_Otsu_threshold(Mat grayImage, int height, int width)
{
    /* Calculate histogram */
    int histogram[256] = { 0 };
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            histogram[grayImage.at<uchar>(i, j)]++;

    /* Calculate Otsu threshold */
    int bestThreshold = 0, Otsu_threshold = 0;
    double maxVariance = 0.0;
    for (int k = 0; k < 256; k++) {
        double p1 = 0.0, p2 = 0.0, m1 = 0.0, m2 = 0.0;
        for (int i = 0; i <= k; i++) {
            p1 += histogram[i] / double(width * height);
            m1 += i * histogram[i] / double(width * height);
        }
        if (p1 != 0.0)
            m1 /= p1;
        for (int i = k + 1; i <= 255; i++) {
            p2 += histogram[i] / double(width * height);
            m2 += i * histogram[i] / double(width * height);
        }
        if (p2 != 0.0)
            m2 /= p2;
        double m = p1 * m1 + p2 * m2;
        double variance = p1 * (m1 - m) * (m1 - m) + p2 * (m2 - m) * (m2 - m);
        if (variance > maxVariance) {
            maxVariance = variance;
            Otsu_threshold = k;
        }
    }

    /* Return Otsu threshold */
    return Otsu_threshold;
}