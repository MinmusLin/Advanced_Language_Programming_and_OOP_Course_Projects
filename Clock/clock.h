/****************************************************************
 * Project Name:  Clock
 * File Name:     clock.h
 * File Function: 抗锯齿图形处理函数、主体函数的头文件
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/11/21
 ****************************************************************/

#pragma once
#ifndef CLOCK_H
#define CLOCK_H

/* Define constant variables */
double const PI = 3.1415926535;
const int consoleHeight = 801;
const int consoleWidth = 801;
const int dialRadius = 380;
const int edgeWidth = 5;
const int majorTickInnerRadius = 360;
const int majorTickOuterRadius = 345;
const int majorTickWidth = 2;
const int minorTickInnerRadius = 358;
const int minorTickOuterRadius = 347;
const int minorTickWidth = 1;
const int numberCenterRadius = 315;
const int numberHeight = 70;
const int numberWeight = 500;
const int hourHandLength = 215;
const int hourHandNegativeLength = 40;
const int hourHandWidth = 4;
const int hourHandCenterRadius = 15;
const int hourHandEndRadius = 7;
const int minuteHandLength = 250;
const int minuteHandNegativeLength = 60;
const int minuteHandWidth = 3;
const int minuteHandCenterRadius = 10;
const int minuteHandEndRadius = 5;
const int secondHandLength = 285;
const int secondHandNegativeLength = 80;
const int secondHandWidth = 2;
const int secondHandCenterRadius = 5;
const int secondHandEndRadius = 3;
const int refreshTime = 30;

/* Function declarations in clock_graphics.cpp */
double calculate_line_SDF(int x, int y, int x1, int y1, int x2, int y2, int d);
void line_SDF(int x1, int y1, int x2, int y2, int d, COLORREF color);
void circle_SDF(int x, int y, int r, int d, COLORREF color);

#endif // !CLOCK_H