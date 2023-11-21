/****************************************************************
 * Project Name:  Simulated_LED_Screen
 * File Name:     LED_retrieve_bitinfo.cpp
 * File Function: 读取点阵信息函数的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/11/21
 ****************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <iomanip>
#include "../common/cmd_console_tools.h"

using namespace std;

/*
 * Function Name:    is_GB2312
 * Function:         Determine whether a character is a valid GB2312 character
 * Input Parameters: char highByte
 *                   char lowByte
 * Return Value:     true / false
 */
inline
bool is_GB2312(char highByte, char lowByte)
{
    BYTE hb = BYTE(highByte), lb = BYTE(lowByte);
    return (hb >= 0xA1 && hb <= 0xFE && lb >= 0xA1 && lb <= 0xFE);
}

/*
 * Function Name:    calculate_offset
 * Function:         Calculate offset
 * Input Parameters: char highByte
 *                   char lowByte
 * Return Value:     offset
 */
inline
int calculate_offset(char highByte, char lowByte)
{
    return 32 * (94 * (highByte - 1) + lowByte - 1);
}

/*
 * Function Name:    readArrayFromFile
 * Function:         Read array from file
 * Input Parameters: const char* filename
 *                   T* array
 *                   size_t size
 *                   int offset
 * Return Value:     void
 */
template <typename T>
static void readArrayFromFile(const char* filename, T* array, size_t size, int offset)
{
    FILE* file = fopen(filename, "rb");
    if (file == NULL)
        exit(-1);
    fseek(file, offset, SEEK_SET);
    fread(array, sizeof(T), size, file);
    fclose(file);
}

/*
 * Function Name:    retrieve_bitinfo
 * Function:         Retrieve 16*16 bitmap information from HZK16 or HZK16F
 * Input Parameters: bool is_simplified
 *                   char _highByte
 *                   char _lowByte
 *                   bool _bitmap[][16]
 * Return Value:     void
 */
void retrieve_bitinfo(bool is_simplified, char _highByte, char _lowByte, bool _bitmap[][16])
{
    /* Enter a valid GB2312 full-width character and check for correctness */
    char character[3] = { 0 };
    if (!_highByte && !_lowByte) {
        cout << "请输入一个合法的GB2312全角字符: ";
        cin >> character;
    }
    int highByte = (_highByte ? _highByte : character[0]), lowByte = (_lowByte ? _lowByte : character[1]);
    if (!(highByte && lowByte && !character[2]) || !is_GB2312(highByte, lowByte)) {
        MessageBoxA(NULL, "Error: 请输入一个合法的GB2312全角字符", "Error", MB_ICONINFORMATION | MB_OK);
        exit(-1);
    }

    /* Retrieve 16*16 bitmap information */
    int offset = calculate_offset(highByte + 96, lowByte + 96), index = 0;
    char bitinfo[4][8];
    bool bitmap[16][16], * p = ((!_highByte && !_lowByte) ? &bitmap[0][0] : &_bitmap[0][0]);
    readArrayFromFile(is_simplified ? "HZK/HZK16.dat" : "HZK/HZK16F.dat", *bitinfo, 32, offset);
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 8; j++)
            for (int k = 0; k < 8; k++)
                p[index++] = (bitinfo[i][j] >> (7 - k)) & 0x1;

    /* Output 16*16 bitmap information */
    if (!_highByte && !_lowByte) {
        cout << endl << ">>> 全角字符: " << character << endl << setfill('0') << setiosflags(ios::uppercase);
        cout << ">>> 区 位 码: " << setw(2) << highByte + 96 << setw(2) << lowByte + 96 << endl;
        cout << ">>> 内 部 码: " << hex << setw(2) << (highByte & 0xFF) << setw(2) << (lowByte & 0xFF) << endl;
        cout << ">>> 偏 移 值: " << dec << offset << endl << hex;
        for (int i = 0; i < 4; i++) {
            cout << (i ? "              " : ">>> 点阵信息: ");
            for (int j = 0; j < 8; j++)
                cout << setw(2) << (bitinfo[i][j] & 0xFF) << " ";
            cout << endl;
        }
        cout << setfill(' ') << dec;
        for (int i = 0; i < 16; i++) {
            cout << (i ? "              " : ">>> 点 阵 值: ");
            for (int j = 0; j < 16; j++)
                cout << bitmap[i][j] << " ";
            cout << endl;
        }
        cout << ">>> 点阵可视:   " << hex;
        for (int i = 0; i < 16; i++)
            cout << setw(2) << i;
        cout << endl;
        for (int i = 0; i < 16; i++) {
            cout << "              " << i << " ";
            cct_setcolor(COLOR_WHITE, COLOR_BLACK);
            for (int j = 0; j < 16; j++)
                cout << (bitmap[i][j] ? "●" : "  ");
            cct_setcolor();
            cout << endl;
        }
        cout << dec << resetiosflags(ios::uppercase) << endl;
        system("pause");
    }
}