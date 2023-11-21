/****************************************************************
 * Project Name:  Matrix_Operations_and_Image_Processing
 * File Name:     MOIP.h
 * File Function: 图像处理函数、菜单函数、矩阵运算函数、工具函数的头文件
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/11/21
 ****************************************************************/

#pragma once
#ifndef MOIP_H
#define MOIP_H

#include <opencv2/opencv.hpp>

/* Define constant variables */
const int consoleRow = 40;
const int consoleCol = 120;
const int maxRow = 5;
const int maxCol = 5;
const int kernelSize = 3;

/* Function declarations in MOIP_matrix.cpp */
void Matrix_Determinant(void);
void Matrix_Addition(void);
void Matrix_Scalar_Multiplication(void);
void Matrix_Transposition(void);
void Matrix_Multiplication(void);
void Matrix_Hadamard(void);
void Matrix_Convolution(void);

/* Function declarations in MOIP_image.cpp */
void Image_Convolution(void);
void Image_Otsu(void);
void Image_Segmentation(void);

/* Function declarations in MOIP_tools.cpp */
int menu(void);
void print_prompt(const char prompt[], int bg_color, int fg_color);
void clear_content(void);
void print_framework(void);
int enter_digit(int x, int y, const char* prompt);
void print_matrix(int x, int y, int r, int c);
bool enter_element(double matrix[][maxCol], int r, int c, int x, int y);
bool input_matrix(double matrix[][maxCol], int row, int col, int x, int y, const char sign[] = "", bool is_prompt = true);
void output_matrix(double matrix[][maxCol], int row, int col, int x, int y, const char sign[] = "", bool is_prompt = true);
double calculate_determinant(double matrix[][maxCol], int n);
bool get_kernel(int kernel[][kernelSize], int& kernel_sum);
int calculate_Otsu_threshold(cv::Mat grayImage, int height, int width);

#endif // !MOIP_H