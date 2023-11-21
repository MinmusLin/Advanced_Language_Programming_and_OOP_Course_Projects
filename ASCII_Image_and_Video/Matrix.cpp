/****************************************************************
 * Project Name:  ASCII_Image_and_Video
 * File Name:     Matrix.cpp
 * File Function: ��Ԫ�ؾ������㺯����ʵ��
 * Author:        Jishen Lin (�ּ���)
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
    cout << ">>> ����" << name << "���뿪ʼ" << endl << endl;
    cout << "���������" << name << "��ά��(������" << HIGHEST_DIMENSION << "): ";
    cin >> arr.axisNum;
    if (arr.axisNum > HIGHEST_DIMENSION)
        exit(-1);
    arr.nowAxis = arr.axisNum;
    for (int i = 0; i < arr.axisNum; i++) {
        cout << "���������" << name << "��" << i + 1 << "ά�ȵĴ�С: ";
        cin >> arr.shape[i];
    }
    for (int i = 0; i < arr.axisNum; i++)
        arr.len *= arr.shape[i];
    delete[] arr.data;
    arr.data = new(nothrow) int[arr.len];
    if (arr.data == NULL)
        exit(-1);
    cout << "���������" << name << "��" << arr.len << "��Ԫ�ص�ֵ: ";
    for (int i = 0; i < arr.len; i++)
        cin >> arr.data[i];
    cout << endl << ">>> ����" << name << "�������" << endl;
}

/*
 * Function Name:    matrixOperation
 * Function:         Element-wise matrix operation
 * Input Parameters: void
 * Return Value:     void
 */
void matrixOperation(void)
{
    cout << ">>> �������������ӦΪͬ�;���" << endl << endl;
    cout << ">>> ����Գ���Ϊ������������" << endl << endl;
    cout << ">>> ����Ϊ��֤�������ݵ���ȷ��" << endl << endl;
    Array A;
    input(A, 'A');
    cout << endl << "����A = " << A << endl << endl;
    Array B;
    input(B, 'B');
    cout << endl << "����B = " << B << endl << endl;
    cout << ">>> ϵ�����뿪ʼ" << endl << endl;
    int k;
    cout << "������ϵ��: ";
    cin >> k;
    cout << endl << ">>> ϵ���������" << endl << endl;
    cout << ">>> ��Ԫ�ؾ������㿪ʼ" << endl << endl;
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
    cout << "C = A = " << C << " (����ĸ���)" << endl;
    C = B;
    cout << "C = B = " << C << " (����ĸ�ֵ)" << endl;
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
    cout << endl << ">>> ��Ԫ�ؾ����������" << endl << endl;
    system("pause");
}