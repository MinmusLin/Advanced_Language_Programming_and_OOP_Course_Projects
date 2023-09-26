/****************************************************************
 * Project Name:  ASCII_Image_and_Video
 * File Name:     Video.cpp
 * File Function: 视频播放函数的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/9/27
 ****************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "winmm.lib")
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include <opencv2/opencv.hpp>
#include "../common/cmd_console_tools.h"
#include "../common/FastPrinter.h"
#include "Array.h"

using namespace std;
using namespace cv;

/* Function declaration in Image.cpp */
void imageViewer(bool is_color, bool is_inverse = false, bool is_video = false, int frame = 0, int _reductionFactor = 0, int _total = 0);

/*
 * Function Name:    readArrayFromFile
 * Function:         Read array from file
 * Input Parameters: const char* filename
 *                   T* array
 *                   size_t size
 * Return Value:     void
 */
template <typename T>
static void readArrayFromFile(const char* filename, T* array, size_t size)
{
    FILE* file = fopen(filename, "rb");
    if (file == NULL)
        exit(-1);
    fread(array, sizeof(T), size, file);
    fclose(file);
}

/*
 * Function Name:    videoPlayer
 * Function:         ASCII video player
 * Input Parameters: bool is_color
 *                   bool is_inverse
 * Return Value:     void
 */
void videoPlayer(bool is_color, bool is_inverse)
{
    /* Input video file */
    cout << ">>> 请不要中途关闭程序" << endl << endl;
    char path[64] = "videos/";
    cout << "请输入要打开的视频文件: ";
    cin >> &path[7];

    /* Start video processing */
    cout << endl << ">>> 视频处理开始" << endl << endl;
    LARGE_INTEGER tick, begin, end;
    QueryPerformanceFrequency(&tick);
    QueryPerformanceCounter(&begin);

    /* Read video file */
    VideoCapture cap(path);
    if (!cap.isOpened())
        exit(-1);
    Mat frame;
    int frameNumber = 0;
    while (true) {
        cap >> frame;
        if (frame.empty())
            break;
        snprintf(path, sizeof(path), "videos/frame_%d.jpg", frameNumber);
        imwrite(path, frame);
        cout << ">>> 保存第" << setw(5) << ++frameNumber << " 帧为 " << &path[7] << endl;
    }
    int x = int(cap.get(CAP_PROP_FRAME_WIDTH));
    int y = int(cap.get(CAP_PROP_FRAME_HEIGHT));
    double frameRate = cap.get(cv::CAP_PROP_FPS);
    cap.release();

    /* End video processing */
    QueryPerformanceCounter(&end);
    cout << endl << ">>> 视频处理结束（执行时间: " << setiosflags(ios::fixed) << setprecision(6) << double(end.QuadPart - begin.QuadPart) / tick.QuadPart << "秒" << "）（共" << frameNumber << "帧）" << endl;

    /* Calculate reduction factor */
    int reductionFactor = (max(x, y) - 1) / consoleWindowsSize + 1;
    cout << endl << ">>> 降采样因子: " << reductionFactor << endl;
    x /= reductionFactor;
    y /= reductionFactor;
    int total = x * y;

    /* Start image processing */
    cout << endl << ">>> 图像处理开始" << endl << endl;
    QueryPerformanceFrequency(&tick);
    QueryPerformanceCounter(&begin);
    for (int i = 0; i < frameNumber; i++)
        imageViewer(is_color, is_inverse, true, i, reductionFactor, total);

    /* End image processing */
    QueryPerformanceCounter(&end);
    cout << endl << ">>> 图像处理结束（执行时间: " << setiosflags(ios::fixed) << setprecision(6) << double(end.QuadPart - begin.QuadPart) / tick.QuadPart << "秒" << "）（共" << frameNumber << "帧）" << endl;

    /* Wait for enter to play video */
    cout << endl << ">>> 按回车键播放视频";
    while (_getch() != '\r')
        continue;

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

    /* Play video */
    int nowFrame = 0;
    QueryPerformanceFrequency(&tick);
    FastPrinter printer(x * 2, y, 6);
    printer.cleanSrceen();
    PlaySoundA("videos/bgm.wav", NULL, SND_FILENAME | SND_ASYNC);
    QueryPerformanceCounter(&begin);
    while (true) {
        /* Calculate frame */
        QueryPerformanceCounter(&end);
        nowFrame = int((end.QuadPart - begin.QuadPart) * frameRate / tick.QuadPart);

        /* Read array from file */
        snprintf(path, sizeof(path), "videos/frame_%d_dataBuffer.dat", nowFrame);
        readArrayFromFile(path, dataBuffer, total * 2);
        snprintf(path, sizeof(path), "videos/frame_%d_frontColorBuffer.dat", nowFrame);
        readArrayFromFile(path, frontColorBuffer, total * 6);
        snprintf(path, sizeof(path), "videos/frame_%d_backColorBuffer.dat", nowFrame);
        readArrayFromFile(path, backColorBuffer, total * 6);

        /* Draw image */
        printer.setData(dataBuffer, frontColorBuffer, backColorBuffer);
        printer.draw(true);
        
        /* Check if video ends */
        if (nowFrame == frameNumber - 1)
            break;
    }

    /* Clean up memory */
    delete[] dataBuffer;
    delete[] frontColorBuffer;
    delete[] backColorBuffer;

    /* Remove temp files */
    for (int i = 0; i < frameNumber; i++) {
        snprintf(path, sizeof(path), "videos/frame_%d.jpg", i);
        remove(path);
        snprintf(path, sizeof(path), "videos/frame_%d_dataBuffer.dat", i);
        remove(path);
        snprintf(path, sizeof(path), "videos/frame_%d_frontColorBuffer.dat", i);
        remove(path);
        snprintf(path, sizeof(path), "videos/frame_%d_backColorBuffer.dat", i);
        remove(path);
    }

    /* Wait for enter to continue */
    cct_setconsoletitle("Press Enter to Return Menu");
    while (_getch() != '\r')
        continue;
}