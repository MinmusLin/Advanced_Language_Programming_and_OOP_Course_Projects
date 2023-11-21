/****************************************************************
 * Project Name:  Matrix_Operations_and_Image_Processing
 * File Name:     MOIP_image.cpp
 * File Function: 图像处理函数的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/11/21
 ****************************************************************/

#include <iostream>
#include "..\common\cmd_console_tools.h"
#include "MOIP.h"

using namespace std;

/*
 * Function Name:    Image_Convolution
 * Function:         Applications of matrix convolution
 * Input Parameters: void
 * Return Value:     void
 */
void Image_Convolution(void)
{
    /* Get kernel matrix and kernel sum */
    int kernel[kernelSize][kernelSize], kernel_sum;
    if (!get_kernel(kernel, kernel_sum))
        return;
    
    /* Output kernel matrix */
    cct_showstr(4, 6, "卷积核矩阵 =", COLOR_HWHITE, COLOR_BLACK);
    print_matrix(4, 7, kernelSize, kernelSize);
    for (int i = 0; i < kernelSize; i++)
        for (int j = 0; j < kernelSize; j++) {
            cct_gotoxy(7 + 10 * j, 8 + i);
            cout << kernel[i][j];
        }

    /* Input the image file and initialize */
    char path[64] = "images/";
    cct_showstr(4, 10 + kernelSize, "请输入要打开的图像文件: ", COLOR_HWHITE, COLOR_BLACK);
    cin >> &path[7];
    cv::Mat colorImage = cv::imread(path);

    /* Determine whether the file is opened successfully */
    if (colorImage.empty()) {
        /* Print the prompt message */
        print_prompt("文件打开失败! ", COLOR_HWHITE, COLOR_RED);
    }
    else {
        /* Print the prompt message */
        print_prompt("文件打开成功! ", COLOR_HWHITE, COLOR_HGREEN);

        /* Initialize grayImage and processedImage, show colorImage and grayImage */
        cv::Mat grayImage;
        cvtColor(colorImage, grayImage, cv::COLOR_BGR2GRAY);
        cv::namedWindow("Color Image");
        imshow("Color Image", colorImage);
        cv::namedWindow("Gray Image");
        imshow("Gray Image", grayImage);
        cv::Mat processedImage = grayImage;

        /* Get the image size */
        int width = processedImage.cols, height = processedImage.rows;

        /* Define dynamic arrays and initialize them */
        int** grayArray = new(nothrow) int* [height + 2];
        if (grayArray == NULL)
            exit(-1);
        for (int i = 0; i < height + 2; i++) {
            grayArray[i] = new(nothrow) int[width + 2];
            if (grayArray[i] == NULL)
                exit(-1);
        }
        int** convolutionArray = new(nothrow) int* [height];
        if (convolutionArray == NULL)
            exit(-1);
        for (int i = 0; i < height; i++) {
            convolutionArray[i] = new(nothrow) int[width];
            if (convolutionArray[i] == NULL)
                exit(-1);
        }
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                convolutionArray[i][j] = 0;
        for (int i = 0; i < height + 2; i++)
            for (int j = 0; j < width + 2; j++)
                grayArray[i][j] = ((i == 0 || j == 0 || i == height + 1 || j == width + 1) ? 0 : static_cast<int>(processedImage.at<uchar>(i - 1, j - 1)));

        /* Matrix convolution operation */
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++) {
                for (int m = 0; m < kernelSize; m++)
                    for (int n = 0; n < kernelSize; n++)
                        convolutionArray[i][j] += grayArray[i + m][j + n] * kernel[m][n];
                if (kernel_sum != 0)
                    convolutionArray[i][j] /= kernel_sum;
                if (convolutionArray[i][j] < 0)
                    convolutionArray[i][j] = 0;
                if (convolutionArray[i][j] > 255)
                    convolutionArray[i][j] = 255;
                processedImage.at<uchar>(i, j) = static_cast<uchar>(convolutionArray[i][j]);
            }

        /* Free dynamic arrays */
        for (int i = 0; i < height + 2; i++)
            delete[] grayArray[i];
        delete[] grayArray;
        for (int i = 0; i < height; i++)
            delete[] convolutionArray[i];
        delete[] convolutionArray;

        /* Print the prompt message */
        print_prompt("利用矩阵卷积运算进行图像处理应用完成! ", COLOR_HWHITE, COLOR_GREEN);

        /* Show processedImage */
        cv::namedWindow("Processed Image");
        imshow("Processed Image", processedImage);

        /* Wait for keyboard input to close all image windows */
        if (cv::waitKey(0))
            cv::destroyAllWindows();
    }

    /* Pause and return */
    std::system("pause");
    return;
}

/*
 * Function Name:    Image_Otsu
 * Function:         Otsu's algorithm
 * Input Parameters: void
 * Return Value:     void
 */
void Image_Otsu(void)
{
    /* Input the image file and initialize */
    char path[64] = "images/";
    cct_showstr(4, 6, "请输入要打开的图像文件: ", COLOR_HWHITE, COLOR_BLACK);
    cin >> &path[7];
    cv::Mat colorImage = cv::imread(path);

    /* Determine whether the file is opened successfully */
    if (colorImage.empty()) {
        /* Print the prompt message */
        print_prompt("文件打开失败! ", COLOR_HWHITE, COLOR_RED);
    }
    else {
        /* Print the prompt message */
        print_prompt("文件打开成功! ", COLOR_HWHITE, COLOR_HGREEN);

        /* Initialize grayImage and processedImage, show colorImage and grayImage */
        cv::Mat grayImage;
        cvtColor(colorImage, grayImage, cv::COLOR_BGR2GRAY);
        cv::namedWindow("Color Image");
        imshow("Color Image", colorImage);
        cv::namedWindow("Gray Image");
        imshow("Gray Image", grayImage);
        cv::Mat processedImage = grayImage;

        /* Get the image size */
        int width = processedImage.cols, height = processedImage.rows;

        /* Define dynamic arrays and initialize them */
        int** grayArray = new(nothrow) int* [height];
        if (grayArray == NULL)
            exit(-1);
        for (int i = 0; i < height; i++) {
            grayArray[i] = new(nothrow) int[width];
            if (grayArray[i] == NULL)
                exit(-1);
        }
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                grayArray[i][j] = static_cast<int>(processedImage.at<uchar>(i, j));

        /* Calculate Otsu threshold */
        int Otsu_threshold = calculate_Otsu_threshold(processedImage, height, width);

        /* Print Otsu threshold */
        cct_showstr(4, 8, "Otsu阈值cv::threshold函数计算结果: ", COLOR_HWHITE, COLOR_BLACK);
        cout << threshold(grayImage, grayImage, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
        cct_showstr(4, 10, "Otsu阈值自定义函数计算结果: ", COLOR_HWHITE, COLOR_BLACK);
        cout << Otsu_threshold;

        /* Process the image */
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                processedImage.at<uchar>(i, j) = (grayArray[i][j] > Otsu_threshold ? 255 : 0);

        /* Free dynamic arrays */
        for (int i = 0; i < height; i++)
            delete[] grayArray[i];
        delete[] grayArray;

        /* Print the prompt message */
        print_prompt("利用Otsu算法(大津算法)进行图像处理应用完成! ", COLOR_HWHITE, COLOR_GREEN);

        /* Show processedImage */
        cv::namedWindow("Processed Image");
        imshow("Processed Image", processedImage);

        /* Wait for keyboard input to close all image windows */
        if (cv::waitKey(0))
            cv::destroyAllWindows();
    }

    /* Pause and return */
    std::system("pause");
    return;
}

/*
 * Function Name:    Image_Segmentation
 * Function:         Segmentation algorithm
 * Input Parameters: void
 * Return Value:     void
 */
void Image_Segmentation(void)
{
    /* Input the image file and initialize */
    char path[64] = "images/";
    cct_showstr(4, 6, "请输入要打开的图像文件: ", COLOR_HWHITE, COLOR_BLACK);
    cin >> &path[7];
    cv::Mat colorImage = cv::imread(path);

    /* Determine whether the file is opened successfully */
    if (colorImage.empty()) {
        /* Print the prompt message */
        print_prompt("文件打开失败! ", COLOR_HWHITE, COLOR_RED);
    }
    else {
        /* Print the prompt message */
        print_prompt("文件打开成功! ", COLOR_HWHITE, COLOR_HGREEN);

        /* Initialize grayImage and processedImage, show colorImage and grayImage */
        cv::Mat grayImage;
        cvtColor(colorImage, grayImage, cv::COLOR_BGR2GRAY);
        cv::namedWindow("Color Image");
        imshow("Color Image", colorImage);
        cv::namedWindow("Gray Image");
        imshow("Gray Image", grayImage);
        cv::Mat processedGrayImage = grayImage;

        /* Get the image size */
        int width = processedGrayImage.cols, height = processedGrayImage.rows;

        /* Define dynamic arrays and initialize them */
        int** grayArray = new(nothrow) int* [height];
        if (grayArray == NULL)
            exit(-1);
        for (int i = 0; i < height; i++) {
            grayArray[i] = new(nothrow) int[width];
            if (grayArray[i] == NULL)
                exit(-1);
        }
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                grayArray[i][j] = static_cast<int>(processedGrayImage.at<uchar>(i, j));

        /* Calculate Otsu threshold */
        int Otsu_threshold = calculate_Otsu_threshold(processedGrayImage, height, width);

        /* Process the gray image */
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                if (grayArray[i][j] < Otsu_threshold)
                    processedGrayImage.at<uchar>(i, j) = 0;

        /* Process the color image */
        cv::Mat processedColorImage = colorImage;
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                if (grayArray[i][j] < Otsu_threshold) {
                    cv::Vec3b& pixel = colorImage.at<cv::Vec3b>(i, j);
                    pixel[0] = cv::saturate_cast<uchar>(0);
                    pixel[1] = cv::saturate_cast<uchar>(0);
                    pixel[2] = cv::saturate_cast<uchar>(0);
                }

        /* Free dynamic arrays */
        for (int i = 0; i < height; i++)
            delete[] grayArray[i];
        delete[] grayArray;

        /* Print the prompt message */
        print_prompt("利用Segmentation算法(传统分割算法)进行图像处理应用完成! ", COLOR_HWHITE, COLOR_GREEN);

        /* Show processedImage */
        cv::namedWindow("Processed Gray Image");
        imshow("Processed Gray Image", processedGrayImage);
        cv::namedWindow("Processed Color Image");
        imshow("Processed Color Image", processedColorImage);

        /* Wait for keyboard input to close all image windows */
        if (cv::waitKey(0))
            cv::destroyAllWindows();
    }

    /* Pause and return */
    std::system("pause");
    return;
}