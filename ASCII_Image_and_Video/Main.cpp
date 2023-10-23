/****************************************************************
 * Project Name:  ASCII_Image_and_Video
 * File Name:     Main.cpp
 * File Function: �˵�������ʵ��
 * Author:        Jishen Lin (�ּ���)
 * Update Date:   2023/10/23
 ****************************************************************/

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "../common/cmd_console_tools.h"

using namespace std;

/* Function declaration in Matrix.cpp */
void matrixOperation(void);

/* Function declaration in Image.cpp */
void imageViewer(bool is_color, bool is_inverse = false, bool is_video = false, int frame = 0, int _reductionFactor = 0, int _total = 0);

/* Function declaration in Video.cpp */
void videoPlayer(bool is_color, bool is_inverse = false);

/*
 * Function Name:    menu
 * Function:         Display menu items and read the correct option
 * Input Parameters: void
 * Return Value:     option
 */
static int menu(void)
{
    /* Set the console */
    cct_setconsoletitle("ASCII Image Viewer and Video Player");
    cct_setfontsize("������", 16);
    cct_setconsoleborder(120, 40, 120, 9000);

    /* Display menu items */
    cout << "                ASCIIͼ��鿴������Ƶ������" << endl;
    cout << "            ASCII Image Viewer and Video Player" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "  1.��Ԫ�ؾ������㣨��������ط�ʽ��" << endl;
    cout << "    Element-wise Matrix Operations (Operator Overloading)" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "  2.ASCIIͼ��鿴�����Ҷ�ͼ��" << endl;
    cout << "    ASCII Image Viewer (Grayscale Image)" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "  3.ASCIIͼ��鿴������ɫͼ��" << endl;
    cout << "    ASCII Image Viewer (Color Image)" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "  4.ASCIIͼ��鿴������ɫͼ�񣩣�����ģʽ��" << endl;
    cout << "    ASCII Image Viewer (Color Image) (Inverse Mode)" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "  5.ASCII��Ƶ���������Ҷ���Ƶ��" << endl;
    cout << "    ASCII Video Player (Grayscale Video)" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "  6.ASCII��Ƶ����������ɫ��Ƶ��" << endl;
    cout << "    ASCII Video Player (Color Video)" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "  7.ASCII��Ƶ����������ɫ��Ƶ��������ģʽ��" << endl;
    cout << "    ASCII Video Player (Color Video) (Inverse Mode)" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "  8.�˳�" << endl;
    cout << "    Quit" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "  [��ѡ��:] ";

    /* Read the correct option */
    while (true) {
        char optn = _getch();
        if (optn == 0 || optn == -32)
            optn = _getch();
        else if (optn >= '1' && optn <= '8') {
            cout << optn << endl << endl;
            Sleep(300);
            return optn;
        }
        else
            continue;
    }
}

/*
 * Function Name:    main
 * Function:         Main function
 * Return Value:     0
 */
int main()
{
    while (true) {
        switch (menu()) {
            case '1':
                cct_setconsoletitle("Element-wise Matrix Operations (Operator Overloading)");
                matrixOperation();
                break;
            case '2':
                cct_setconsoletitle("ASCII Image Viewer (Grayscale Image)");
                imageViewer(false);
                break;
            case '3':
                cct_setconsoletitle("ASCII Image Viewer (Color Image)");
                imageViewer(true);
                break;
            case '4':
                cct_setconsoletitle("ASCII Image Viewer (Color Image) (Inverse Mode)");
                imageViewer(true, true);
                break;
            case '5':
                cct_setconsoletitle("ASCII Video Player (Grayscale Video)");
                videoPlayer(false);
                break;
            case '6':
                cct_setconsoletitle("ASCII Video Player (Color Video)");
                videoPlayer(true);
                break;
            case '7':
                cct_setconsoletitle("ASCII Video Player (Color Video) (Inverse Mode)");
                videoPlayer(true, true);
                break;
            default:
                return 0;
        }
    }
}