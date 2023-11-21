/****************************************************************
 * Project Name:  ASCII_Image_and_Video
 * File Name:     Matrix.cpp
 * File Function: 逐元素矩阵运算函数的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/11/21
 ****************************************************************/

#include <iostream>
#include "Array.h"

/* Namespace */
using namespace std;

/*
 * Function Name:    input
 * Function:         Input matrix
 * Input Parameters: Array& arr
 *                   char name
 * Return Value:     void
 */
static void input(Array& arr, char name)
{
    cout << ">>> 矩阵" << name << "输入开始" << endl << endl;
    cout << "请输入矩阵" << name << "的维数(不超过" << HIGHEST_DIMENSION << "): ";
    cin >> arr.axisNum;
    if (arr.axisNum > HIGHEST_DIMENSION)
        exit(-1);
    arr.nowAxis = arr.axisNum;
    for (int i = 0; i < arr.axisNum; i++) {
        cout << "请输入矩阵" << name << "第" << i + 1 << "维度的大小: ";
        cin >> arr.shape[i];
    }
    for (int i = 0; i < arr.axisNum; i++)
        arr.len *= arr.shape[i];
    delete[] arr.data;
    arr.data = new(nothrow) int[arr.len];
    if (arr.data == NULL)
        exit(-1);
    cout << "请输入矩阵" << name << "共" << arr.len << "个元素的值: ";
    for (int i = 0; i < arr.len; i++)
        cin >> arr.data[i];
    cout << endl << ">>> 矩阵" << name << "输入完成" << endl;
}

/*
 * Function Name:    matrixOperation
 * Function:         Element-wise matrix operation
 * Input Parameters: void
 * Return Value:     void
 */
void matrixOperation(void)
{
    cout << ">>> 输入的两个矩阵应为同型矩阵" << endl << endl;
    cout << ">>> 程序对除数为零情况不做检查" << endl << endl;
    cout << ">>> 请人为保证输入数据的正确性" << endl << endl;
    Array A;
    input(A, 'A');
    cout << endl << "矩阵A = " << A << endl << endl;
    Array B;
    input(B, 'B');
    cout << endl << "矩阵B = " << B << endl << endl;
    cout << ">>> 系数输入开始" << endl << endl;
    int k;
    cout << "请输入系数: ";
    cin >> k;
    cout << endl << ">>> 系数输入结束" << endl << endl;
    cout << ">>> 逐元素矩阵运算开始" << endl << endl;
    cout << "-A = " << -A << endl;
    cout << "A + B = " << A + B << endl;
    cout << "A - B = " << A - B << endl;
    cout << "A * B = " << A * B << endl;
    cout << "A / B = " << A / B << endl;
    cout << "A * k = " << A * k << endl;
    cout << "k * A = " << k * A << endl;
    cout << "A / k = " << A / k << endl;
    cout << "k / A = " << k / A << endl;
    Array C(A);
    cout << "C = A = " << C << " (对象的复制)" << endl;
    C = B;
    cout << "C = B = " << C << " (对象的赋值)" << endl;
    C = -A;
    cout << "C = -A = " << C << endl;
    C = A + B;
    cout << "C = A + B = " << C << endl;
    C = A - B;
    cout << "C = A - B = " << C << endl;
    C = A * B;
    cout << "C = A * B = " << C << endl;
    C = A / B;
    cout << "C = A / B = " << C << endl;
    C = A * k;
    cout << "C = A * k = " << C << endl;
    C = k * A;
    cout << "C = k * A = " << C << endl;
    C = A / k;
    cout << "C = A / k = " << C << endl;
    C = k / A;
    cout << "C = k / A = " << C << endl;
    cout << endl << ">>> 逐元素矩阵运算结束" << endl << endl;
    system("pause");
}