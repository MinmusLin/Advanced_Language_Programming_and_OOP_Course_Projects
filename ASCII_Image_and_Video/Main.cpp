/****************************************************************
 * Project Name:  ASCII_Image_and_Video
 * File Name:     Main.cpp
 * File Function: 菜单函数的实现
 * Author:        Jishen Lin (林继申)
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
    cct_setfontsize("新宋体", 16);
    cct_setconsoleborder(120, 40, 120, 9000);

    /* Display menu items */
    cout << "                ASCII图像查看器和视频播放器" << endl;
    cout << "            ASCII Image Viewer and Video Player" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "  1.逐元素矩阵运算（运算符重载方式）" << endl;
    cout << "    Element-wise Matrix Operations (Operator Overloading)" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "  2.ASCII图像查看器（灰度图像）" << endl;
    cout << "    ASCII Image Viewer (Grayscale Image)" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "  3.ASCII图像查看器（彩色图像）" << endl;
    cout << "    ASCII Image Viewer (Color Image)" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "  4.ASCII图像查看器（彩色图像）（反显模式）" << endl;
    cout << "    ASCII Image Viewer (Color Image) (Inverse Mode)" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "  5.ASCII视频播放器（灰度视频）" << endl;
    cout << "    ASCII Video Player (Grayscale Video)" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "  6.ASCII视频播放器（彩色视频）" << endl;
    cout << "    ASCII Video Player (Color Video)" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "  7.ASCII视频播放器（彩色视频）（反显模式）" << endl;
    cout << "    ASCII Video Player (Color Video) (Inverse Mode)" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "  8.退出" << endl;
    cout << "    Quit" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "  [请选择:] ";

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