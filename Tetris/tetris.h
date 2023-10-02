/****************************************************************
 * Project Name:  Tetris
 * File Name:     tetris.h
 * File Function: Block类、Control类、游戏函数、图形化界面函数、主体函数的头文件
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/10/2
 ****************************************************************/

#pragma once
#include <graphics.h>
#include <vector>

/* Define KEYBOARD_ESC */
#define KEYBOARD_ESC 27

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
const int rightGridMargin = 260;
const int displayGridSideLength = 4;
const int infoOffset = 6;
const int colorNum = 7;
const int gameRulesX = 460;
const int gameRulesY = 15;
const int oneLineScore = 10;
const int twoLinesScore = 25;
const int threeLinesScore = 45;
const int fourLinesScore = 70;
const int delayTime = 500;

/* Define constant LOGFONT variables */
const LOGFONT Font_CN{ (topGridMargin - topInfoMargin - bottomInfoMargin), (topGridMargin - topInfoMargin - bottomInfoMargin) / 2, 0, 0, FW_DONTCARE, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH, L"黑体" };
const LOGFONT Font_EN{ (topGridMargin - topInfoMargin - bottomInfoMargin), 0, 0, 0, FW_BOLD, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH, L"等线" };

/* Define block category and block limits */
const std::vector<std::vector<std::vector<std::vector<int>>>> blockCategory = {
    { { {1,1},{1,2},{2,1},{2,2} }                                                                                     }, // "O" shape
    { { {0,1},{1,1},{2,1},{3,1} },{ {1,0},{1,1},{1,2},{1,3} }                                                         }, // "I" shape
    { { {1,1},{1,2},{2,0},{2,1} },{ {0,1},{1,1},{1,2},{2,2} }                                                         }, // "S" shape
    { { {1,0},{1,1},{2,1},{2,2} },{ {0,2},{1,1},{1,2},{2,1} }                                                         }, // "Z" shape
    { { {0,1},{1,1},{2,1},{2,2} },{ {1,1},{1,2},{1,3},{2,1} },{ {1,1},{1,2},{2,2},{3,2} },{ {1,2},{2,0},{2,1},{2,2} } }, // "L" shape
    { { {0,2},{1,2},{2,2},{2,1} },{ {1,1},{2,1},{2,2},{2,3} },{ {1,1},{1,2},{2,1},{3,1} },{ {1,0},{1,1},{1,2},{2,2} } }, // "J" shape
    { { {2,1},{2,0},{1,1},{2,2} },{ {1,1},{0,1},{2,1},{1,2} },{ {1,2},{1,1},{2,2},{1,3} },{ {2,2},{2,1},{1,2},{3,2} } }  // "T" shape
};
const std::vector<std::vector<std::vector<std::vector<int>>>> blockLimits = {
    { { {1,1},{2,2} }                                                 }, // "O" shape
    { { {0,1},{3,1} },{ {1,0},{1,3} }                                 }, // "I" shape
    { { {1,0},{2,2} },{ {0,1},{2,2} }                                 }, // "S" shape
    { { {1,0},{2,2} },{ {0,1},{2,2} }                                 }, // "Z" shape
    { { {0,1},{2,2} },{ {1,1},{2,3} },{ {1,1},{3,2} },{ {1,0},{2,2} } }, // "L" shape
    { { {0,1},{2,2} },{ {1,1},{2,3} },{ {1,1},{3,2} },{ {1,0},{2,2} } }, // "J" shape
    { { {1,0},{2,2} },{ {0,1},{2,2} },{ {1,1},{2,3} },{ {1,1},{3,2} } }  // "T" shape
};

/* Define Block class */
class Block {
private:
    std::vector<std::vector<int>> block;
    COLORREF color;
    int category;
    int direction;
public:
    Block();
    const std::vector<std::vector<int>>& getBlock(void) const;
    const COLORREF getColor(void) const;
    const int getCategory(void) const;
    const int getDirection(void) const;
    void rotateClockwise(void);
    void rotateAnticlockwise(void);
};

/* Define Control class */
class Control {
private:
    bool** map;
    int eliminatedLines = 0;
    int score = 0;
    int currentRow;
    int currentCol;
    COLORREF** color;
    Block current;
    Block hold;
    Block next[3];
public:
    Control();
    ~Control();
    const int& getScore(void) const;
    const int& getCurrentRow(void) const;
    const int& getCurrentCol(void) const;
    const Block& getCurrentBlock(void) const;
    void printHoldBlock(void);
    void printNextBlocks(void);
    void rotateCurrentClockwise(void);
    void rotateCurrentAnticlockwise(void);
    bool printBlock(int row, int col, bool is_blank = false);
    void refreshBlocks(void);
    void refreshBlock(int row, int col);
    void changeCurrentAndHold(void);
    bool eliminateLines(void);
    void refreshMap(void);
    void resetCurrentRowAndCol(void);
    void rotateRight(void);
    bool softDrop(void);
    void moveLeft(void);
    void moveRight(void);
    void changeHold(void);
    void rotateLeft(void);
    void hardDrop(void);
};

/* Function declaration in tetris_game.cpp */
bool tetris(void);

/* Function declarations in tetris_graphics.cpp */
void initializeGraphics(void);
void printGridStatus(int row, int col, COLORREF color);
void printEliminatedLines(int eliminatedLines, bool is_first = false);
void printScore(int score, bool is_first = false);