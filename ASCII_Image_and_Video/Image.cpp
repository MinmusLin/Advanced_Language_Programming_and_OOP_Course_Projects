/****************************************************************
 * Project Name:  ASCII_Image_and_Video
 * File Name:     Image.cpp
 * File Function: 图像查看函数的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/9/24
 ****************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <iomanip>
#include "../common/cmd_console_tools.h"
#include "../common/FastPrinter.h"
#include "../common/PicReader.h"
#include "Array.h"
using namespace std;

/*
 * Function Name:    saveArrayToFile
 * Function:         Save array to file
 * Input Parameters: const char* filename
 *                   T* array
 *                   size_t size
 * Return Value:     void
 */
template <typename T>
static void saveArrayToFile(const char* filename, T* array, size_t size)
{
    FILE* file = fopen(filename, "wb");
    if (file == NULL)
        exit(-1);
    fwrite(array, sizeof(T), size, file);
    fclose(file);
}

/*
 * Function Name:    imageViewer
 * Function:         ASCII image viewer
 * Input Parameters: bool is_color
 *                   bool is_inverse
 *                   bool is_video
 *                   int frame
 *                   int _reductionFactor
 *                   int _total
 * Return Value:     void
 */
void imageViewer(bool is_color, bool is_inverse, bool is_video, int frame, int _reductionFactor, int _total)
{
    /* Input image file */
    char path[64] = "images/";
    if (is_video)
        snprintf(path, sizeof(path), "videos/frame_%d.jpg", frame);
    else {
        cout << "请输入要打开的图像文件: ";
        cin >> &path[7];
    }

    /* Start image processing */
    if (!is_video)
        cout << endl << ">>> 图像处理开始" << endl;
    LARGE_INTEGER tick, begin, end;
    QueryPerformanceFrequency(&tick);
    QueryPerformanceCounter(&begin);

    /* Read image file */
    PicReader imread;
    BYTE* data = nullptr;
    UINT _x, _y;
    imread.readPic(path);
    imread.getData(data, _x, _y);
    int x = _x, y = _y;
    
    /* Save the image file data as an Array class with dimensions (width * height * 4 channels) */
    Array originalImage(x * y * 4);
    for (int i = 0; i < x * y * 4; i++)
        originalImage.get_content()[i] = data[i];
    delete[] data;
    originalImage.reshape(y, x, 4);
    
    /* Calculate reduction factor */
    int reductionFactor, total;
    if (!is_video) {
        reductionFactor = (max(x, y) - 1) / consoleWindowsSize + 1;
        cout << endl << ">>> 降采样因子: " << reductionFactor << endl;
        x /= reductionFactor;
        y /= reductionFactor;
        total = x * y;
    }
    else {
        reductionFactor = _reductionFactor;
        x /= reductionFactor;
        y /= reductionFactor;
        total = _total;
    }

    /* Process image reduction */
    Array reductionImage(y, x, 4);
    for (int i = 0; i < y; i++)
        for (int j = 0; j < x; j++) {
            int start_x = j * reductionFactor, start_y = i * reductionFactor, end_x = start_x + reductionFactor, end_y = start_y + reductionFactor;
            int sum[4] = { 0 };
            for (int m = start_y; m < end_y; m++)
                for (int n = start_x; n < end_x; n++)
                    for (int k = 0; k < 4; k++)
                        sum[k] += originalImage[m][n][k];
            for (int k = 0; k < 4; k++)
                reductionImage.get_content()[(i * x + j) * 4 + k] = int(sum[k] / double(reductionFactor * reductionFactor) + 0.5);
        }

    /* Convert four-channel color data to grayscale values */
    BYTE* grayscale = new BYTE[x * y];
    if (grayscale == NULL)
        exit(-1);
    int* p = reductionImage.get_content();
    for (int i = 0; i < y; i++)
        for (int j = 0; j < x; j++) {
            int index = i * x + j;
            grayscale[index] = ((306 * p[index * 4] + 601 * p[index * 4 + 1] + 116 * p[index * 4 + 2]) >> 10);
        }

    /* Allocate memory for data buffers */
    char* dataBuffer = new(nothrow) char[total * 2];
    if (dataBuffer == NULL)
        exit(-1);
    BYTE* frontColorBuffer = new(nothrow) BYTE[total * 6];
    if (frontColorBuffer == NULL)
        exit(-1);
    BYTE* backColorBuffer = new(nothrow) BYTE[total * 6];
    if (backColorBuffer == NULL)
        exit(-1);

    /* Convert grayscale values to ASCII characters */
    for (int i = 0; i < total * 2; i++)
        dataBuffer[i] = asciiStrength[int(grayscale[i / 2] / 16.0 + 0.5)];
    delete[] grayscale;

    /* Set foreground color and background color */
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            int index = (i * x + j) * 2;
            if (is_color) {
                for (int k = 0; k < 2; k++) {
                    int _index = index / 2 * 4;
                    int __index = index * 3;
                    if (is_inverse) {
                        frontColorBuffer[__index] = 255;
                        frontColorBuffer[__index + 1] = 255;
                        frontColorBuffer[__index + 2] = 255;
                        backColorBuffer[__index] = reductionImage.get_content()[_index];
                        backColorBuffer[__index + 1] = reductionImage.get_content()[_index + 1];
                        backColorBuffer[__index + 2] = reductionImage.get_content()[_index + 2];
                    }
                    else {
                        frontColorBuffer[__index] = reductionImage.get_content()[_index];
                        frontColorBuffer[__index + 1] = reductionImage.get_content()[_index + 1];
                        frontColorBuffer[__index + 2] = reductionImage.get_content()[_index + 2];
                        backColorBuffer[__index] = 255;
                        backColorBuffer[__index + 1] = 255;
                        backColorBuffer[__index + 2] = 255;
                    }
                    index++;
                }
            }
            else {
                for (int k = 0; k < 2; k++) {
                    for (int d = 0; d < 3; d++) {
                        frontColorBuffer[index * 3 + d] = 0;
                        backColorBuffer[index * 3 + d] = 255;
                    }
                    index++;
                }
            }
        }
    }

    /* Check if it is video mode */
    if (!is_video) {
        /* End image processing */
        QueryPerformanceCounter(&end);
        cout << endl << ">>> 图像处理结束（执行时间: " << setiosflags(ios::fixed) << setprecision(6) << double(end.QuadPart - begin.QuadPart) / tick.QuadPart << "秒" << "）" << endl;

        /* Wait for enter to draw image */
        cout << endl << ">>> 按回车键显示图像";
        while (_getch() != '\r')
            continue;

        /* Draw image */
        FastPrinter printer(x * 2, y, 6);
        printer.cleanSrceen();
        printer.setData(dataBuffer, frontColorBuffer, backColorBuffer);
        printer.draw(true);

        /* Wait for enter to continue */
        if (!is_video) {
            cct_setconsoletitle("Press Enter to Return Menu");
            while (_getch() != '\r')
                continue;
        }
    }
    else {
        /* Save array to dat file */
        snprintf(path, sizeof(path), "videos/frame_%d_dataBuffer.dat", frame);
        saveArrayToFile(path, dataBuffer, total * 2);
        snprintf(path, sizeof(path), "videos/frame_%d_frontColorBuffer.dat", frame);
        saveArrayToFile(path, frontColorBuffer, total * 6);
        snprintf(path, sizeof(path), "videos/frame_%d_backColorBuffer.dat", frame);
        saveArrayToFile(path, backColorBuffer, total * 6);

        /* End image processing */
        QueryPerformanceCounter(&end);
        cout << ">>> 第" << setw(5) << frame + 1 << " 帧图像处理完成（执行时间: " << setiosflags(ios::fixed) << setprecision(6) << double(end.QuadPart - begin.QuadPart) / tick.QuadPart << "秒" << "）" << endl;
    }

    /* Clean up memory */
    delete[] dataBuffer;
    delete[] frontColorBuffer;
    delete[] backColorBuffer;
}