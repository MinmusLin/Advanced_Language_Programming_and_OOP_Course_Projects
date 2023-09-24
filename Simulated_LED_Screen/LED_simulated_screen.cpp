/****************************************************************
 * Project Name:  Simulated_LED_Screen
 * File Name:     LED_simulated_screen.cpp
 * File Function: ģ��LED��ʾ��������ʵ��
 * Author:        Jishen Lin (�ּ���)
 * Update Date:   2023/9/24
 ****************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <cstring>
#include "../common/cmd_console_tools.h"
#include "../common/lib_hdc_tools.h"
using namespace std;

/* Macro definition */
#define DELAY_TIME 10

/* Function declaration in LED_retrieve_bitinfo.cpp */
void retrieve_bitinfo(bool is_simplified, char _highByte = 0, char _lowByte = 0, bool _bitmap[][16] = { 0 });

/*
 * Function Name:    is_error
 * Function:         Check if the input is correct
 * Input Parameters: condition
 * Return Value:     void
 */
static void is_error(bool condition)
{
    if (cin.fail() || !condition) {
        MessageBoxA(NULL, "Error: �������", "Error", MB_ICONINFORMATION | MB_OK);
        exit(-1);
    }
}

/*
 * Function Name:    shuffle
 * Function:         Rearrange elements in a random order
 * Input Parameters: int arr[]
 *                   int n
 * Return Value:     void
 */
static void shuffle(int arr[], int n)
{
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(arr[i], arr[j]);
    }
}

/*
 * Function Name:    concatenate_numeric_characters
 * Function:         Concatenate full-width numeric characters to a string
 * Input Parameters: char prompt[]
 *                   int num
 * Return Value:     void
 */
static void concatenate_numeric_characters(char prompt[], int num)
{
    switch (num) {
        case 0:
            strcat(prompt, "��");
            break;
        case 1:
            strcat(prompt, "��");
            break;
        case 2:
            strcat(prompt, "��");
            break;
        case 3:
            strcat(prompt, "��");
            break;
        case 4:
            strcat(prompt, "��");
            break;
        case 5:
            strcat(prompt, "��");
            break;
        case 6:
            strcat(prompt, "��");
            break;
        case 7:
            strcat(prompt, "��");
            break;
        case 8:
            strcat(prompt, "��");
            break;
        case 9:
            strcat(prompt, "��");
            break;
        default:
            exit(-1);
    }
}

/*
 * Function Name:    convert_date_and_time
 * Function:         Convert the current date and time into full-width characters
 * Input Parameters: char prompt[]
 * Return Value:     void
 */
static void convert_date_and_time(char prompt[])
{
    struct tm* tt;
    time_t current_time = time(0);
    tt = localtime(&current_time);
    concatenate_numeric_characters(prompt, (tt->tm_year + 1900) / 1000);
    concatenate_numeric_characters(prompt, (tt->tm_year + 1900) % 1000 / 100);
    concatenate_numeric_characters(prompt, (tt->tm_year + 1900) % 100 / 10);
    concatenate_numeric_characters(prompt, (tt->tm_year + 1900) % 10);
    strcat(prompt, "��");
    concatenate_numeric_characters(prompt, (tt->tm_mon + 1) / 10);
    concatenate_numeric_characters(prompt, (tt->tm_mon + 1) % 10);
    strcat(prompt, "��");
    concatenate_numeric_characters(prompt, tt->tm_mday / 10);
    concatenate_numeric_characters(prompt, tt->tm_mday % 10);
    strcat(prompt, "�ա�");
    concatenate_numeric_characters(prompt, tt->tm_hour / 10);
    concatenate_numeric_characters(prompt, tt->tm_hour % 10);
    strcat(prompt, "ʱ");
    concatenate_numeric_characters(prompt, tt->tm_min / 10);
    concatenate_numeric_characters(prompt, tt->tm_min % 10);
    strcat(prompt, "��");
    concatenate_numeric_characters(prompt, tt->tm_sec / 10);
    concatenate_numeric_characters(prompt, tt->tm_sec % 10);
    strcat(prompt, "��");
}

/*
 * Function Name:    simulated_screen
 * Function:         Simulated LED Screen (Simplified Chinese and Traditional Chinese)
 * Input Parameters: bool is_simplified
 * Return Value:     void
 */
void simulated_screen(bool is_simplified)
{
    /* Print prompt information */
    int row, col, diameter, R, G, B;
    cout << ">>> ���������ǿ���˳�����" << endl << endl;
    cout << ">>> ����Ϊ��֤������������ʼ���Ŀ���̨���ڴ�С��������Ļ��С" << endl << endl;

    /* Input number of characters displayed per row */
    cout << "������ÿ����ʾ��������: ";
    cin >> col;
    is_error(col >= 1);

    /* Input number of characters displayed per column */
    cout << "������ÿ����ʾ��������: ";
    cin >> row;
    is_error(row >= 1);

    /* Input font size */
    cout << "������ÿ�����ص��ֱ��: ";
    cin >> diameter;
    is_error(diameter >= 1);

    /* Input RGB color */
    cout << "��������ɫ�ĺ�ɫͨ��ֵ: ";
    cin >> R;
    is_error(R >= 0 && R <= 255);
    cout << "��������ɫ����ɫͨ��ֵ: ";
    cin >> G;
    is_error(G >= 0 && G <= 255);
    cout << "��������ɫ����ɫͨ��ֵ: ";
    cin >> B;
    is_error(B >= 0 && B <= 255);

    /* Input full-width string */
    cout << "������GB2312ȫ���ַ���: ";
    string str;
    cin >> str;
    int strLen = strlen(str.c_str());
    char* prompt = new char[row * col * 2 + 1] {0};
    if (prompt == NULL)
        exit(-1);
    for (int i = 0; i < row * col * 2; i++) {
        prompt[i] = str.c_str()[i];
        if (i + 1 == strLen)
            break;
    }

    /* Input Display Effects */
    char optn;
    cout << endl << ">>> A.�ҿ����Զ�����" << endl;
    cout << ">>> B.�ҿ����Եײ���" << endl;
    cout << ">>> C.�ҿ�������ࣩ" << endl;
    cout << ">>> D.�ҿ������Ҳࣩ" << endl;
    cout << ">>> E.���루�Զ�����" << endl;
    cout << ">>> F.���루�Եײ���" << endl;
    cout << ">>> G.���루����ࣩ" << endl;
    cout << ">>> H.���루���Ҳࣩ" << endl;
    cout << ">>> I.�������Զ�����" << endl;
    cout << ">>> J.�������Եײ���" << endl;
    cout << ">>> K.����������ࣩ" << endl;
    cout << ">>> L.���������Ҳࣩ" << endl;
    cout << ">>> M.�ָ����������չ����" << endl;
    cout << ">>> N.�ָ����������չ����" << endl;
    cout << ">>> O.�ָ����������������" << endl;
    cout << ">>> P.�ָ����������������" << endl;
    cout << ">>> Q.�����������ֱ��" << endl;
    cout << ">>> R.���������ˮƽ��" << endl;
    cout << ">>> S.�ܽ�" << endl;
    cout << ">>> T.���ÿ����ɫ" << endl;
    cout << ">>> U.���ÿ����ɫ" << endl;
    cout << ">>> V.��˸" << endl;
    cout << endl << "��ѡ����ʾ��Ч: ";
    while (1) {
        optn = _getch();
        if (optn == 0 || optn == -32)
            optn = _getch();
        else if ((optn >= 'a' && optn <= 'v') || (optn >= 'A' && optn <= 'V')) {
            if (optn >= 'a')
                optn -= 32;
            cout << optn;
            Sleep(300);
            break;
        }
        else
            continue;
    }

    /* Initialize printer */
    hdc_init(COLOR_BLACK, COLOR_WHITE, (col * 16) * diameter, (row * 16) * diameter + 32);
    cout << "���س�����ʼ��ʾ";
    while (_getch() != '\r')
        continue;

    /* Allocate dynamic memory for bitmaps */
    int** bitmaps = new(nothrow) int* [row * 16] {0};
    if (bitmaps == NULL)
        exit(-1);
    for (int i = 0; i < row * 16; i++) {
        bitmaps[i] = new(nothrow) int[col * 16] {0};
        if (bitmaps[i] == NULL)
            exit(-1);
    }

    /* Iterate over rows and columns */
    int highByteIndex = -2, lowByteIndex = -1;
    bool is_loop = true;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            highByteIndex += 2;
            lowByteIndex += 2;
            if (!prompt[highByteIndex]) {
                is_loop = false;
                break;
            }
            int start_row = i * 16, start_col = j * 16, end_row = (i + 1) * 16, end_col = (j + 1) * 16;
            bool bitmap[16][16];
            retrieve_bitinfo(is_simplified, prompt[highByteIndex], prompt[lowByteIndex], bitmap);
            for (int m = start_row, y = 0; m < end_row; m++, y++)
                for (int n = start_col, x = 0; n < end_col; n++, x++)
                    bitmaps[m][n] = bitmap[y][x];
        }
        if (!is_loop)
            break;
    }

    /* Display the bitmaps on the screen */
    switch (optn) {
        case 'A':
            for (int i = 0; i < row * 16; i++) {
                for (int j = 0; j < col * 16; j++)
                    if (bitmaps[i][j])
                        hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(R, G, B));
                Sleep(DELAY_TIME);
            }
            break;
        case 'B':
            for (int i = row * 16 - 1; i >= 0; i--) {
                for (int j = 0; j < col * 16; j++)
                    if (bitmaps[i][j])
                        hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(R, G, B));
                Sleep(DELAY_TIME);
            }
            break;
        case 'C':
            for (int j = 0; j < col * 16; j++) {
                for (int i = 0; i < row * 16; i++)
                    if (bitmaps[i][j])
                        hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(R, G, B));
                Sleep(DELAY_TIME);
            }
            break;
        case 'D':
            for (int j = col * 16 - 1; j >= 0; j--) {
                for (int i = 0; i < row * 16; i++)
                    if (bitmaps[i][j])
                        hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(R, G, B));
                Sleep(DELAY_TIME);
            }
            break;
        case 'E':
            for (int k = 0; k < row * 16; k++) {
                for (int i = 0; i < k + 1; i++)
                    for (int j = 0; j < col * 16; j++)
                        hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, bitmaps[i - k + row * 16 - 1][j] ? RGB(R, G, B) : RGB(12, 12, 12));
                Sleep(DELAY_TIME);
            }
            break;
        case 'F':
            for (int k = 0; k < row * 16; k++) {
                for (int i = row * 16 - 1; i >= row * 16 - 1 - k; i--)
                    for (int j = 0; j < col * 16; j++)
                        hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, bitmaps[i + k - row * 16 + 1][j] ? RGB(R, G, B) : RGB(12, 12, 12));
                Sleep(DELAY_TIME);
            }
            break;
        case 'G':
            for (int k = 0; k < col * 16; k++) {
                for (int i = 0; i < row * 16; i++)
                    for (int j = 0; j < k + 1; j++)
                        hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, bitmaps[i][j - k + col * 16 - 1] ? RGB(R, G, B) : RGB(12, 12, 12));
                Sleep(DELAY_TIME);
            }
            break;
        case 'H':
            for (int k = 0; k < col * 16; k++) {
                for (int i = 0; i < row * 16; i++)
                    for (int j = col * 16 - 1; j >= col * 16 - 1 - k; j--)
                        hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, bitmaps[i][j + k - col * 16 + 1] ? RGB(R, G, B) : RGB(12, 12, 12));
                Sleep(DELAY_TIME);
            }
            break;
        case 'I':
            for (int i = 0; i < row * 16; i++)
                for (int j = 0; j < col * 16; j++)
                    if (bitmaps[i][j])
                        hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(R, G, B));
            for (int i = 0; i < row * 16; i++) {
                for (int j = 0; j < col * 16; j++)
                    if (bitmaps[i][j])
                        hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(12, 12, 12));
                Sleep(DELAY_TIME);
            }
            break;
        case 'J':
            for (int i = 0; i < row * 16; i++)
                for (int j = 0; j < col * 16; j++)
                    if (bitmaps[i][j])
                        hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(R, G, B));
            for (int i = row * 16 - 1; i >= 0; i--) {
                for (int j = 0; j < col * 16; j++)
                    if (bitmaps[i][j])
                        hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(12, 12, 12));
                Sleep(DELAY_TIME);
            }
            break;
        case 'K':
            for (int i = 0; i < row * 16; i++)
                for (int j = 0; j < col * 16; j++)
                    if (bitmaps[i][j])
                        hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(R, G, B));
            for (int j = 0; j < col * 16; j++) {
                for (int i = 0; i < row * 16; i++)
                    if (bitmaps[i][j])
                        hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(12, 12, 12));
                Sleep(DELAY_TIME);
            }
            break;
        case 'L':
            for (int i = 0; i < row * 16; i++)
                for (int j = 0; j < col * 16; j++)
                    if (bitmaps[i][j])
                        hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(R, G, B));
            for (int j = col * 16 - 1; j >= 0; j--) {
                for (int i = 0; i < row * 16; i++)
                    if (bitmaps[i][j])
                        hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(12, 12, 12));
                Sleep(DELAY_TIME);
            }
            break;
        case 'M':
            for (int i = row * 8; i >= 0; i--) {
                for (int j = 0; j < col * 16; j++) {
                    if (bitmaps[i][j])
                        hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(R, G, B));
                    if (bitmaps[row * 16 - i - 1][j])
                        hdc_point(j * diameter + diameter / 2, (row * 16 - i - 1) * diameter + diameter / 2 + 16, diameter, RGB(R, G, B));
                }
                Sleep(DELAY_TIME);
            }
            break;
        case 'N':
            for (int j = col * 8; j >= 0; j--) {
                for (int i = 0; i < row * 16; i++) {
                    if (bitmaps[i][j])
                        hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(R, G, B));
                    if (bitmaps[i][col * 16 - j - 1])
                        hdc_point((col * 16 - j - 1) * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(R, G, B));
                }
                Sleep(DELAY_TIME);
            }
            break;
        case 'O':
            for (int i = 0; i < row * 8; i++) {
                for (int j = 0; j < col * 16; j++) {
                    if (bitmaps[i][j])
                        hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(R, G, B));
                    if (bitmaps[row * 16 - i - 1][j])
                        hdc_point(j * diameter + diameter / 2, (row * 16 - i - 1) * diameter + diameter / 2 + 16, diameter, RGB(R, G, B));
                }
                Sleep(DELAY_TIME);
            }
            break;
        case 'P':
            for (int j = 0; j < col * 8; j++) {
                for (int i = 0; i < row * 16; i++) {
                    if (bitmaps[i][j])
                        hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(R, G, B));
                    if (bitmaps[i][col * 16 - j - 1])
                        hdc_point((col * 16 - j - 1) * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(R, G, B));
                }
                Sleep(DELAY_TIME);
            }
            break;
        case 'Q': {
            int* elements = new int[col * 16];
            if (elements == NULL)
                exit(-1);
            for (int i = 0; i < col * 16; i++)
                elements[i] = i;
            shuffle(elements, col * 16);
            for (int j = 0; j < col * 16; j++) {
                for (int i = 0; i < row * 16; i++)
                    if (bitmaps[i][elements[j]])
                        hdc_point(elements[j] * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(R, G, B));
                Sleep(DELAY_TIME);
            }
            delete[] elements;
            break;
        }
        case 'R': {
            int* elements = new int[row * 16];
            if (elements == NULL)
                exit(-1);
            for (int i = 0; i < row * 16; i++)
                elements[i] = i;
            shuffle(elements, row * 16);
            for (int i = 0; i < row * 16; i++) {
                for (int j = 0; j < col * 16; j++)
                    if (bitmaps[elements[i]][j])
                        hdc_point(j * diameter + diameter / 2, elements[i] * diameter + diameter / 2 + 16, diameter, RGB(R, G, B));
                Sleep(DELAY_TIME);
            }
            delete[] elements;
            break;
        }
        case 'S': {
            int* allPoints = new int[row * col * 256];
            for (int i = 0; i < row * col * 256; i++)
                allPoints[i] = i;
            shuffle(allPoints, row * col * 256);
            for (int count = 0; count < row * col * 256; count++) {
                int i = allPoints[count] / (col * 16);
                int j = allPoints[count] % (col * 16);
                if (bitmaps[i][j])
                    hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(R, G, B));
            }
            delete[] allPoints;
            break;
        }
        case 'T': {
            int* allPoints = new int[row * col * 256];
            for (int i = 0; i < row * col * 256; i++)
                allPoints[i] = i;
            shuffle(allPoints, row * col * 256);
            for (int count = 0; count < row * col * 256; count++) {
                int i = allPoints[count] / (col * 16);
                int j = allPoints[count] % (col * 16);
                if (bitmaps[i][j])
                    hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(rand() % 256, rand() % 256, rand() % 256));
            }
            delete[] allPoints;
            break;
        }
        case 'U': {
            int** allCharacters = new(nothrow) int* [row * col] {0};
            if (allCharacters == NULL)
                exit(-1);
            for (int i = 0; i < row * col; i++) {
                allCharacters[i] = new(nothrow) int[3] {rand() % 256, rand() % 256, rand() % 256};
                if (allCharacters[i] == NULL)
                    exit(-1);
            }
            for (int i = 0; i < row * 16; i++)
                for (int j = 0; j < col * 16; j++)
                    if (bitmaps[i][j]) {
                        int index = (i / 16) * col + (j / 16);
                        hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(allCharacters[index][0], allCharacters[index][1], allCharacters[index][2]));
                    }
            for (int i = 0; i < row * col; i++)
                delete[] allCharacters[i];
            delete[] allCharacters;
            break;
        }
        case 'V':
            for (int i = 0; i < row * 16; i++)
                for (int j = 0; j < col * 16; j++)
                    if (bitmaps[i][j]) {
                        hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(R, G, B));
                        Sleep(1);
                        hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(255 - R, 255 - G, 255 - B));
                        Sleep(1);
                        hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(R, G, B));
                        Sleep(1);
                    }
            break;
        default:
            exit(-1);
    }

    /* Free dynamic memory */
    for (int i = 0; i < row * 16; i++)
        delete[] bitmaps[i];
    delete[] bitmaps;
    delete[] prompt;

    /* Wait for enter to continue */
    cct_gotoxy(0, 0);
    cout << "���س������ز˵�";
    while (_getch() != '\r')
        continue;
}

/*
 * Function Name:    simulated_screen
 * Function:         Simulated LED Screen (Current Date and Time)
 * Input Parameters: void
 * Return Value:     void
 */
void simulated_screen(void)
{
    /* Print prompt information */
    int row = 2, col = 11, diameter = 4, R, G, B;
    cout << ">>> ���������ǿ���˳�����" << endl << endl;
    cout << ">>> ����Ϊ��֤������������ʼ���Ŀ���̨���ڴ�С��������Ļ��С" << endl << endl;

    /* Input RGB color */
    cout << "��������ɫ�ĺ�ɫͨ��ֵ: ";
    cin >> R;
    is_error(R >= 0 && R <= 255);
    cout << "��������ɫ����ɫͨ��ֵ: ";
    cin >> G;
    is_error(G >= 0 && G <= 255);
    cout << "��������ɫ����ɫͨ��ֵ: ";
    cin >> B;
    is_error(B >= 0 && B <= 255);

    /* Allocate dynamic memory for bitmaps */
    int** bitmaps = new(nothrow) int* [row * 16] {0};
    if (bitmaps == NULL)
        exit(-1);
    for (int i = 0; i < row * 16; i++) {
        bitmaps[i] = new(nothrow) int[col * 16] {0};
        if (bitmaps[i] == NULL)
            exit(-1);
    }

    /* Initialize printer */
    hdc_init(COLOR_BLACK, COLOR_WHITE, (col * 16) * diameter, (row * 16) * diameter + 32);
    cout << "���س�����ʼ��ʾ";
    while (_getch() != '\r')
        continue;
    cct_gotoxy(0, 0);
    cout << "���س������ز˵�";

    /* Display current date and time */
    while (true) {
        /* Wait for enter to continue */
        if (_kbhit() && _getch() == '\r')
            break;

        /* Convert the current date and time into full-width characters */
        char prompt[128] = { 0 };
        convert_date_and_time(prompt);

        /* Iterate over rows and columns */
        int highByteIndex = -2, lowByteIndex = -1;
        bool is_loop = true;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                highByteIndex += 2;
                lowByteIndex += 2;
                if (!prompt[highByteIndex]) {
                    is_loop = false;
                    break;
                }
                int start_row = i * 16, start_col = j * 16, end_row = (i + 1) * 16, end_col = (j + 1) * 16;
                bool bitmap[16][16];
                retrieve_bitinfo(true, prompt[highByteIndex], prompt[lowByteIndex], bitmap);
                for (int m = start_row, y = 0; m < end_row; m++, y++)
                    for (int n = start_col, x = 0; n < end_col; n++, x++)
                        bitmaps[m][n] = bitmap[y][x];
            }
            if (!is_loop)
                break;
        }

        /* Display the bitmaps on the screen */
        for (int i = 0; i < row * 16; i++)
            for (int j = 0; j < col * 16; j++)
                hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, bitmaps[i][j] ? RGB(R, G, B) : RGB(12, 12, 12));
    }

    /* Free dynamic memory */
    for (int i = 0; i < row * 16; i++)
        delete[] bitmaps[i];
    delete[] bitmaps;
}