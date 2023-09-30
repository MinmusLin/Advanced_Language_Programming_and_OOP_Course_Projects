/****************************************************************
 * Project Name:  Tetris
 * File Name:     tetris.h
 * File Function: Block类、Control类、历史最高分记录函数、图形化界面函数、主体函数的头文件
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/10/1
 ****************************************************************/

#pragma once
#include <graphics.h>
#include <vector>

/* Define RGB color */
#define GRID_LINE_COLOR RGB(210, 210, 210)
#define GRID_BLANK_COLOR RGB(255, 255, 255)
#define COLOR_1 RGB(0, 121, 255)
#define COLOR_2 RGB(0, 223, 162)
#define COLOR_3 RGB(246, 250, 112)
#define COLOR_4 RGB(255, 0, 96)
#define COLOR_5 RGB(48, 227, 223)
#define COLOR_6 RGB(171, 70, 210)
#define COLOR_7 RGB(255, 127, 63)

/* Define constant COLORREF variable */
const COLORREF Color[] = { COLOR_1, COLOR_2, COLOR_3, COLOR_4, COLOR_5, COLOR_6, COLOR_7 };

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
const int colorNum = 7;

/* Define constant LOGFONT variables */
const LOGFONT Font_CN{ (topGridMargin - topInfoMargin - bottomInfoMargin), (topGridMargin - topInfoMargin - bottomInfoMargin) / 2, 0, 0, FW_DONTCARE, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH, L"黑体" };
const LOGFONT Font_EN{ (topGridMargin - topInfoMargin - bottomInfoMargin), 0, 0, 0, FW_BOLD, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH, L"等线" };

/* Define block category */
const std::vector<std::vector<std::vector<std::vector<int>>>> blockCategory = {
    { { {1,1},{1,2},{2,1},{2,2} }                                                                                     }, // "O" shape
    { { {0,1},{1,1},{2,1},{3,1} },{ {1,0},{1,1},{1,2},{1,3} }                                                         }, // "I" shape
    { { {1,1},{1,2},{2,0},{2,1} },{ {0,1},{1,1},{1,2},{2,2} }                                                         }, // "S" shape
    { { {1,0},{1,1},{2,1},{2,2} },{ {0,2},{1,1},{1,2},{2,1} }                                                         }, // "Z" shape
    { { {0,1},{1,1},{2,1},{2,2} },{ {1,1},{1,2},{1,3},{2,1} },{ {1,1},{1,2},{2,2},{3,2} },{ {1,2},{2,0},{2,1},{2,2} } }, // "L" shape
    { { {0,2},{1,2},{2,2},{2,1} },{ {1,1},{2,1},{2,2},{2,3} },{ {1,1},{1,2},{2,1},{3,1} },{ {1,0},{1,1},{1,2},{2,2} } }, // "J" shape
    { { {2,1},{2,0},{1,1},{2,2} },{ {1,1},{0,1},{2,1},{1,2} },{ {1,2},{1,1},{2,2},{1,3} },{ {2,2},{2,1},{1,2},{3,2} } }  // "T" shape
};

/* Define Block class */
class Block {
private:
    std::vector<std::vector<int>> block;
    int category;
    int direction;
    COLORREF color;
public:
    Block();
    const std::vector<std::vector<int>>& getBlock(void) const;
    const COLORREF getColor(void) const;
    void rotate(void);
};

/* Define Control class */
class Control {
private:
    Block current;
    Block hold;
    Block next[3];
public:
    Control();
    void print_hold_block(void);
    void print_next_blocks(void);
    void rotate_current(void);
};

/* Function declarations in tetris_file.cpp */
void updateHighestScore(int score);
int readHighestScore(void);

/* Function declarations in tetris_graphics.cpp */
void initialize_graphics(void);
void print_grid_status(int row, int col, COLORREF color);