/****************************************************************
 * Project Name:  Gluttonous_Snake
 * File Name:     gluttonous_snake.h
 * File Function: Control类、Snake类、历史最高分记录函数、游戏函数、图形化界面函数、主体函数、菜单函数的头文件
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/9/28
 ****************************************************************/

#pragma once
#include <graphics.h>
#include <Windows.h>

/* Define mode number */
#define MODE_NUMBER 6

/* Define invalid row and column */
#define INVALID_ROW -1
#define INVALID_COLUMN -1

/* Define RGB color */
#define GRID_LINE_COLOR RGB(210, 210, 210)
#define GRID_BLANK_COLOR RGB(255, 255, 255)
#define GRID_WALL_COLOR RGB(130, 130, 130)
#define GRID_OBSTACLE_COLOR RGB(170, 170, 170)
#define SNAKE_A_COLOR RGB(102, 202, 251)
#define SNAKE_B_COLOR RGB(255, 161, 245)
#define GOOD_FOOD_COLOR RGB(246, 250, 112)
#define GREAT_FOOD_COLOR RGB(0, 223, 162)
#define BAD_FOOD_COLOR RGB(121, 63, 223)
#define BOOM_FOOD_COLOR RGB(255, 0, 96)

/* Define constant int variables */
const int menuWidth = 1024;
const int menuHeight = 512;
const int gridRow = 32;
const int gridCol = 64;
const int gridSideLength = 24;
const int gridSpace = 1;
const int topInfoMargin = 10;
const int bottomInfoMargin = 10;
const int topGridMargin = 40;
const int bottomGridMargin = 10;
const int leftGridMargin = 10;
const int rightGridMargin = 10;
const int dataLength = 6;
const int startTime = 1000;
const int snakeInitialLength = 5;
const int maxGoodFood = 12;
const int maxGreatFood = 4;
const int maxBadFood = 6;
const int maxBoomFood = 2;
const int maxObstacle = 4;
const int goodScore = 10;
const int greatScore = 50;
const int badScore = -20;
const int boomScore = -40;
const int obstacleScore = -30;
const int deathScore = -100;
const int deathCountMaximum = 5;
const int timeThreshold = 180;
const int timeAIThreshold = 10;

/* Define constant enum variables */
const enum Mode { BasicMode, AdvancedMode, ExpertMode, HumanVsHumanMode, HumanVsAIMode, AIVsAIMode, ResetHighestScore, Quit };
const enum GridCondition { GridBlank, GridWall, SnakeHead, SnakeBody, GoodFood, GreatFood, BadFood, BoomFood, GridObstacle };
const enum Direction { Up, Down, Left, Right, InvalidDirection };
const enum SnakeCategory { SnakeA, SnakeB, InvalidSnakeCategory };
const enum EndPageCategory { PageDefault, PageHumanSnakeA, PageHumanSnakeB, PageAISnakeA, PageAISnakeB };

/* Define constant LOGFONT variable */
const LOGFONT Font{ (topGridMargin - topInfoMargin - bottomInfoMargin), (topGridMargin - topInfoMargin - bottomInfoMargin) / 2, 0, 0, FW_DONTCARE, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH, L"黑体" };

/* Define Point structure */
typedef struct {
    int row;
    int col;
} Point;

/* Define Snake class */
class Snake {
private:
    SnakeCategory snakeCategory;
    GridCondition** map;
    struct SnakeSegment {
        COORD coordinate;
        Direction direction;
        SnakeSegment* nextSegment;
    };
    SnakeSegment* head;
    SnakeSegment* tail;
    int* pGoodFood;
    int* pGreatFood;
    int* pBadFood;
    int* pBoomFood;
    int* pObstacle;
    int score = 0;
    int length = 1;
    int death = 0;
    void deleteSnake(void);
    void addSegment(Direction direction);
    void deleteSegment(void);
    bool findEmptySpace(COORD& coord, Direction& direction, bool is_multiplayer);
    Point findClosestCoordinate(void);
    Point findNextStep(int map[][gridCol], int startRow, int startCol, int targetRow, int targetCol);
public:
    friend class Control;
    ~Snake();
    bool generateSnake(bool is_multiplayer = false);
    void refreshSnake(void);
    void changeGridCondition(GridCondition gridCondition);
    void correct(int len);
    bool changeDirection(Direction direction);
    int getLength(void);
    int getDeath(void);
    Direction getSnakeDirection(void);
    Direction BFS(void);
};

/* Define Control class */
class Control {
private:
    Mode mode;
    DWORD startTickCount;
    GridCondition** map;
    int* pGoodFood;
    int* pGreatFood;
    int* pBadFood;
    int* pBoomFood;
    int* pObstacle;
    void allocateAndInitialize(int*& p);
    void setObstacles(void);
    int count(GridCondition gridCondition);
public:
    Snake Snake_A;
    Snake Snake_B;
    Control(Mode _mode);
    ~Control();
    void generateGrid(GridCondition gridCondition);
    void print_information(void);
    void refreshMap(void);
    int getHighestScore(void);
};

/* Function declarations in gluttonous_snake_file.cpp */
void updateHighestScore(Mode mode, int score);
int readHighestScore(Mode mode);
void resetHighestScore(void);

/* Function declarations in gluttonous_snake_game.cpp */
void gluttonous_snake(Mode mode);

/* Function declarations in gluttonous_snake_graphics.cpp */
void initialize_graphics(Mode mode);
void print_grid_status(int row, int col, GridCondition gridCondition, SnakeCategory snakeCategory = InvalidSnakeCategory, Direction direction = InvalidDirection);

/* Function declarations in gluttonous_snake_menu.cpp */
void startPage(void);
Mode menu(void);
void endPage(EndPageCategory endPageCategory = PageDefault);