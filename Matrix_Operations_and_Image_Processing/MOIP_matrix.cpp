/****************************************************************
 * Project Name:  Matrix_Operations_and_Image_Processing
 * File Name:     MOIP_matrix.cpp
 * File Function: 矩阵运算函数的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/9/27
 ****************************************************************/

#include <iostream>
#include <iomanip>
#include "..\common\cmd_console_tools.h"
#include "MOIP.h"

using namespace std;

/*
 * Function Name:    Matrix_Determinant
 * Function:         Matrix determinant calculation
 * Input Parameters: void
 * Return Value:     void
 */
void Matrix_Determinant(void)
{
    double A[maxRow][maxCol];
    int n = enter_digit(4, 6, "请输入方阵阶数: ");
    if (!input_matrix(A, n, n, 4, 8))
        return;
    cct_gotoxy(4, 12 + n);
    cout << n << "阶方阵行列式值 = " << setiosflags(ios::fixed) << calculate_determinant(A, n) << resetiosflags(ios::fixed);
    print_prompt("计算完成! ", COLOR_HWHITE, COLOR_GREEN);
    system("pause");
}

/*
 * Function Name:    Matrix_Addition
 * Function:         Matrix addition operation
 * Input Parameters: void
 * Return Value:     void
 */
void Matrix_Addition(void)
{
    double A[maxRow][maxCol], B[maxRow][maxCol], C[maxRow][maxCol];
    int row = enter_digit(4, 6, "请输入矩阵行数: ");
    int col = enter_digit(4, 7, "请输入矩阵列数: ");
    if (!input_matrix(A, row, col, 4, 9, "A"))
        return;
    if (!input_matrix(B, row, col, 4, 13 + row, "B"))
        return;
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            C[i][j] = A[i][j] + B[i][j];
    output_matrix(C, row, col, 4, 17 + row * 2, "C = A+B");
    print_prompt("计算完成! ", COLOR_HWHITE, COLOR_GREEN);
    system("pause");
}

/*
 * Function Name:    Matrix_Scalar_Multiplication
 * Function:         Scalar multiplication of matrices
 * Input Parameters: void
 * Return Value:     void
 */
void Matrix_Scalar_Multiplication(void)
{
    double A[maxRow][maxCol], B[maxRow][maxCol], k;
    int row = enter_digit(4, 6, "请输入矩阵行数: ");
    int col = enter_digit(4, 7, "请输入矩阵列数: ");
    cct_showstr(4, 8, "请输入矩阵k倍数乘: ", COLOR_HWHITE, COLOR_BLACK);
    cin >> k;
    if (!cin.good()) {
        cin.clear();
        cin.ignore(65536, '\n');
        print_prompt("输入错误! ", COLOR_HWHITE, COLOR_RED);
        system("pause");
        return;
    }
    if (!input_matrix(A, row, col, 4, 10, "A"))
        return;
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            B[i][j] = k * A[i][j];
    output_matrix(B, row, col, 4, 14 + row, "B = k×A");
    print_prompt("计算完成! ", COLOR_HWHITE, COLOR_GREEN);
    system("pause");
}

/*
 * Function Name:    Matrix_Transposition
 * Function:         Matrix transposition operation
 * Input Parameters: void
 * Return Value:     void
 */
void Matrix_Transposition(void)
{
    double A[maxRow][maxCol], AT[maxRow][maxCol];
    int row = enter_digit(4, 6, "请输入矩阵行数: ");
    int col = enter_digit(4, 7, "请输入矩阵列数: ");
    if (!input_matrix(A, row, col, 4, 9, "A"))
        return;
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            AT[j][i] = A[i][j];
    output_matrix(AT, col, row, 4, 13 + row, "A^T");
    print_prompt("计算完成! ", COLOR_HWHITE, COLOR_GREEN);
    system("pause");
}

/*
 * Function Name:    Matrix_Multiplication
 * Function:         Matrix multiplication operation
 * Input Parameters: void
 * Return Value:     void
 */
void Matrix_Multiplication(void)
{
    double A[maxRow][maxCol], B[maxRow][maxCol], C[maxRow][maxCol];
    int row_A = enter_digit(4, 6, "请输入矩阵A行数: ");
    int col_A = enter_digit(4, 7, "请输入矩阵A列数(矩阵B行数): ");
    int row_B = col_A;
    int col_B = enter_digit(4, 8, "请输入矩阵B列数: ");
    if (!input_matrix(A, row_A, col_A, 4, 10, "A"))
        return;
    if (!input_matrix(B, row_B, col_B, 4, 14 + row_A, "B"))
        return;
    for (int i = 0; i < row_A; i++)
        for (int j = 0; j < col_B; j++) {
            C[i][j] = 0.0;
            for (int k = 0; k < col_A; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
    output_matrix(C, row_A, col_B, 4, 18 + row_A + row_B, "C = A×B");
    print_prompt("计算完成! ", COLOR_HWHITE, COLOR_GREEN);
    system("pause");
}

/*
 * Function Name:    Matrix_Hadamard
 * Function:         Hadamard product of matrices
 * Input Parameters: void
 * Return Value:     void
 */
void Matrix_Hadamard(void)
{
    double A[maxRow][maxCol], B[maxRow][maxCol], C[maxRow][maxCol];
    int row = enter_digit(4, 6, "请输入矩阵行数: ");
    int col = enter_digit(4, 7, "请输入矩阵列数: ");
    if (!input_matrix(A, row, col, 4, 9, "A"))
        return;
    if (!input_matrix(B, row, col, 4, 13 + row, "B"))
        return;
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            C[i][j] = A[i][j] * B[i][j];
    output_matrix(C, row, col, 4, 17 + row * 2, "C = A☉B");
    print_prompt("计算完成! ", COLOR_HWHITE, COLOR_GREEN);
    system("pause");
}

/*
 * Function Name:    Matrix_Convolution
 * Function:         Matrix convolution operation
 * Input Parameters: void
 * Return Value:     void
 * Notes:            KernelSize = 3，Padding = 1，Dilation = 1，Stride = 1
 */
void Matrix_Convolution(void)
{
    double A[maxRow][maxCol], B[maxRow + 2][maxCol + 2] = { 0 }, C[maxRow][maxCol] = { 0 }, kernel[kernelSize][kernelSize];
    cct_showstr(4, 6, "请输入待卷积矩阵(", COLOR_HWHITE, COLOR_BLACK);
    cout << maxRow << "阶方阵):";
    if (!input_matrix(A, maxRow, maxCol, 4, 6, "", false))
        return;
    cct_showstr(4, 10 + maxCol, "请输入卷积核矩阵(", COLOR_HWHITE, COLOR_BLACK);
    cout << kernelSize << "阶方阵):";
    print_matrix(4, 11 + maxCol, kernelSize, kernelSize);
    for (int i = 0; i < kernelSize; i++)
        for (int j = 0; j < kernelSize; j++) {
            cct_gotoxy(7 + 10 * j, 12 + maxCol + i);
            cin >> kernel[i][j];
            if (!cin.good()) {
                cin.clear();
                cin.ignore(65536, '\n');
                print_prompt("输入错误! ", COLOR_HWHITE, COLOR_RED);
                system("pause");
                return;
            }
        }
    for (int i = 0; i < maxRow; i++)
        for (int j = 0; j < maxCol; j++)
            B[i + 1][j + 1] = A[i][j];
    for (int i = 0; i < maxRow; i++)
        for (int j = 0; j < maxCol; j++)
            for (int m = 0; m < kernelSize; m++)
                for (int n = 0; n < kernelSize; n++)
                    C[i][j] += B[i + m][j + n] * kernel[m][n];
    cct_showstr(4, 14 + maxRow + kernelSize, "卷积矩阵(", COLOR_HWHITE, COLOR_BLACK);
    cout << maxRow << "阶方阵) =";
    output_matrix(C, maxRow, maxCol, 4, 14 + maxRow + kernelSize, "", false);
    print_prompt("计算完成! ", COLOR_HWHITE, COLOR_GREEN);
    system("pause");
}