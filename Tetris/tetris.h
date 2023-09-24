/****************************************************************
 * Project Name:  Tetris
 * File Name:     tetris.h
 * File Function: Control类、历史最高分记录函数、图形化界面函数、主体函数的头文件
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/9/24
 ****************************************************************/

#pragma once
#include <graphics.h>

/* Define RGB color */
#define GRID_LINE_COLOR RGB(210, 210, 210)
#define GRID_BLANK_COLOR RGB(255, 255, 255)

/* Define constant int variables */
const int gridRow = 24;
const int gridCol = 12;
const int gridSideLength = 24;
const int gridSpace = 1;
const int topInfoMargin = 10;
const int bottomInfoMargin = 10;
const int topGridMargin = 40;
const int bottomGridMargin = 15;
const int leftGridMargin = 15;
const int rightGridMargin = 15;
const int displayGridSideLength = 4;
const int infoOffset = 6;

/* Define constant LOGFONT variable */
const LOGFONT Font_CN{ (topGridMargin - topInfoMargin - bottomInfoMargin), (topGridMargin - topInfoMargin - bottomInfoMargin) / 2, 0, 0, FW_DONTCARE, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH, L"黑体" };
const LOGFONT Font_EN{ (topGridMargin - topInfoMargin - bottomInfoMargin), 0, 0, 0, FW_BOLD, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH, L"等线" };

/* Function declarations in tetris_file.cpp */
void updateHighestScore(int score);
int readHighestScore(void);

/* Function declarations in tetris_graphics.cpp */
void initialize_graphics(void);