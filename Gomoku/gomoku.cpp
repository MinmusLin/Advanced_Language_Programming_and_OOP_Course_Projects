/****************************************************************
 * Project Name:  Gomoku
 * File Name:     gomoku.cpp
 * File Function: 五子棋AI对战程序
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/11/21
 ****************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <random>                                // C++ 随机数生成器和分布
#include <algorithm>                             // C++ 标准模板库（泛型算法组件）
#include <unordered_map>                         // C++ 标准模板库（哈希表关联容器）
#include <stdio.h>                               // C 语言标准输入输出库
#include <stdlib.h>                              // C 标准通用工具库
#include <string.h>                              // C 风格字符串处理函数库
#include <time.h>                                // C 日期和时间处理函数库

/* Namespace */
using ULL = unsigned long long;                  // 64 位无符号整数类型

/* Conditional compilation */
#define DEBUG_MODE 0                             // 调试模式开关

/* Define Status type */
typedef enum {
    Empty,                                       // 空位标志
    Black,                                       // 黑棋标志
    White                                        // 白棋标志
} Status;

/* Define Move type */
typedef struct {
    int x;                                       // 行数
    int y;                                       // 列数
    int score;                                   // 评分
} Move;

/* Define HashEntry type */
typedef struct {
    int depth;                                   // 深度
    int score;                                   // 评分
} HashEntry;

/* Define constant variables */
const int OFFSET_X[] = { -1,-1,-1,0,0,1,1,1 };   // X 方向偏移量
const int OFFSET_Y[] = { -1,0,1,-1,1,-1,0,1 };   // Y 方向偏移量
const int BOARD_SIZE = 12;                       // 棋盘大小
const int INVALID_COORD = -1;                    // 无效坐标
const int MAX_SCORE = 1000000000;                // 最高分数
const int MIN_SCORE = -1000000000;               // 最低分数
const int FIVE_LINE = 10000000;                  // 五连分数
const int LIVE_FOUR = 100000;                    // 活四分数
const int BLOCK_FOUR = 1000;                     // 冲四分数
const int LIVE_THREE = 1000;                     // 活三分数
const int BLOCK_THREE = 100;                     // 冲三分数
const int LIVE_TWO = 100;                        // 活二分数
const int BLOCK_TWO = 10;                        // 冲二分数
const int LIVE_ONE = 10;                         // 活一分数
const int BLOCK_ONE = 1;                         // 冲一分数
const int SEARCH_DEPTH = 3;                      // 搜索深度

/* Define global variables */
Status g_myFlag;                                 // 我方棋子标志
Status g_enemyFlag;                              // 对方棋子标志
Status g_board[BOARD_SIZE][BOARD_SIZE];          // 棋盘信息
int g_myScore[BOARD_SIZE][BOARD_SIZE];           // 我方分数
int g_enemyScore[BOARD_SIZE][BOARD_SIZE];        // 对方分数
int g_stepCount;                                 // 步数统计
ULL g_zobristTable[BOARD_SIZE][BOARD_SIZE][3];   // Zobrist 数
ULL g_currentZobristHash;                        // 当前 Zobrist 哈希值
std::unordered_map<ULL, HashEntry> g_transTable; // Zobrist 置换表

#if DEBUG_MODE
/*
 * Function Name:    printBoard
 * Function:         Print board used for debugging
 * Input Parameters: void
 * Return Value:     void
 */
void printBoard(void)
{
    printf("    ");
    fflush(stdout);
    for (int col = 0; col < BOARD_SIZE; col++) {
        printf("%2d ", col);
        fflush(stdout);
    }
    printf("\n");
    fflush(stdout);
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("   +");
        fflush(stdout);
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("--+");
            fflush(stdout);
        }
        printf("\n%2d ", i);
        fflush(stdout);
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (g_board[i][j] == White) {
                printf("|●");
                fflush(stdout);
            }
            else if (g_board[i][j] == Black) {
                printf("|○");
                fflush(stdout);
            }
            else {
                printf("|  ");
                fflush(stdout);
            }
        }
        printf("|\n");
        fflush(stdout);
    }
    printf("   +");
    fflush(stdout);
    for (int j = 0; j < BOARD_SIZE; j++) {
        printf("--+");
        fflush(stdout);
    }
    printf("\n");
    fflush(stdout);
}
#endif // DEBUG_MODE

#if DEBUG_MODE
/*
 * Function Name:    printScore
 * Function:         Print score used for debugging
 * Input Parameters: void
 * Return Value:     void
 */
void printScore(void)
{
    printf("    ");
    fflush(stdout);
    for (int col = 0; col < BOARD_SIZE; col++) {
        printf("%8d ", col);
        fflush(stdout);
    }
    printf("\n");
    fflush(stdout);
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("   +");
        fflush(stdout);
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("--------+");
            fflush(stdout);
        }
        printf("\n%2d ", i);
        fflush(stdout);
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("|");
            fflush(stdout);
            if (g_board[i][j] == g_myFlag) {
                printf(g_myFlag == Black ? "○" : "●");
                printf("%6d", g_myScore[i][j]);
                fflush(stdout);
            }
            else if (g_board[i][j] == g_enemyFlag) {
                printf(g_enemyFlag == Black ? "○" : "●");
                printf("%6d", -g_enemyScore[i][j]);
                fflush(stdout);
            }
            else {
                printf("        ");
                fflush(stdout);
            }
        }
        printf("|\n");
        fflush(stdout);
    }
    printf("   +");
    fflush(stdout);
    for (int j = 0; j < BOARD_SIZE; j++) {
        printf("--------+");
        fflush(stdout);
    }
    printf("\n");
    fflush(stdout);
}
#endif // DEBUG_MODE

/*
 * Function Name:    isInBound
 * Function:         Determine if the point is within the chessboard
 * Input Parameters: const int x
 *                   const int y
 * Return Value:     true / false
 */
inline bool isInBound(const int x, const int y)
{
    return (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE);
}

/*
 * Function Name:    updateZobristHash
 * Function:         Update zobrist hash
 * Input Parameters: const int x
 *                   const int y
 *                   const Status flag
 * Return Value:     void
 */
inline void updateZobristHash(const int x, const int y, const Status flag)
{
    g_currentZobristHash ^= g_zobristTable[x][y][flag];
}

/*
 * Function Name:    hasNeighbor
 * Function:         Determine whether there are other chess pieces around a certain point
 * Input Parameters: const int x
 *                   const int y
 *                   const int radius
 *                   int count
 * Return Value:     true / false
 */
bool hasNeighbor(const int x, const int y, const int radius = 1, int count = 1)
{
    /* Determine the scope of the check */
    int startRow = std::max(0, x - radius);
    int endRow = std::min(BOARD_SIZE - 1, x + radius);
    int startCol = std::max(0, y - radius);
    int endCol = std::min(BOARD_SIZE - 1, y + radius);

    /* Determine whether there are other chess pieces around a certain point */
    for (int i = startRow; i <= endRow; i++) {
        for (int j = startCol; j <= endCol; j++) {
            if (i == x && j == y) {
                continue; // Skip the current point
            }
            if (g_board[i][j] != Empty) {
                if (--count <= 0) { // Decrease the count for each neighbor found
                    return true;
                }
            }
        }
    }
    return false;
}

/*
 * Function Name:    evaluateState
 * Function:         Evaluate the state of a specific point
 * Input Parameters: const int count
 *                   const int block
 *                   const int empty
 * Return Value:     score
 */
int evaluateState(const int count, const int block, const int empty)
{
    if (empty <= 0) {
        if (count >= 5) {
            return FIVE_LINE;               // 五连
        }
        if (block == 0) {
            switch (count) {
                case 1: return LIVE_ONE;    // 活一
                case 2: return LIVE_TWO;    // 活二
                case 3: return LIVE_THREE;  // 活三
                case 4: return LIVE_FOUR;   // 活四
                default: break;
            }
        }
        if (block == 1) {
            switch (count) {
                case 1: return BLOCK_ONE;   // 冲一
                case 2: return BLOCK_TWO;   // 冲二
                case 3: return BLOCK_THREE; // 冲三
                case 4: return BLOCK_FOUR;  // 冲四
                default: break;
            }
        }
    } // end of if (empty <= 0)
    else if (empty == 1 || empty == count - 1) {
        if (count >= 6) {
            return FIVE_LINE;               // 五连
        }
        if (block == 0) {
            switch (count) {
                case 2: return LIVE_TWO;    // 活二
                case 3: return LIVE_THREE;  // 活三
                case 4: return BLOCK_FOUR;  // 冲四
                case 5: return LIVE_FOUR;   // 活四
                default: break;
            }
        }
        if (block == 1) {
            switch (count) {
                case 2: return BLOCK_TWO;   // 冲二
                case 3: return BLOCK_THREE; // 冲三
                case 4: return BLOCK_FOUR;  // 冲四
                case 5: return BLOCK_FOUR;  // 冲四
                default: break;
            }
        }
    } // end of else if (empty == 1 || empty == count - 1)
    else if (empty == 2 || empty == count - 2) {
        if (count >= 7) {
            return FIVE_LINE;               // 五连
        }
        if (block == 0) {
            switch (count) {
                case 3: return LIVE_THREE;  // 活三
                case 4: return BLOCK_FOUR;  // 冲四
                case 5: return BLOCK_FOUR;  // 冲四
                case 6: return LIVE_FOUR;   // 活四
                default: break;
            }
        }
        if (block == 1) {
            switch (count) {
                case 3: return BLOCK_THREE; // 冲三
                case 4: return BLOCK_FOUR;  // 冲四
                case 5: return BLOCK_FOUR;  // 冲四
                case 6: return LIVE_FOUR;   // 活四
                default: break;
            }
        }
        if (block == 2) {
            switch (count) {
                case 4: return BLOCK_FOUR;  // 冲四
                case 5: return BLOCK_FOUR;  // 冲四
                case 6: return BLOCK_FOUR;  // 冲四
                default: break;
            }
        }
    } // end of else if (empty == 2 || empty == count - 2)
    else if (empty == 3 || empty == count - 3) {
        if (count >= 8) {
            return FIVE_LINE;               // 五连
        }
        if (block == 0) {
            switch (count) {
                case 4: return LIVE_THREE;  // 活三
                case 5: return LIVE_THREE;  // 活三
                case 6: return BLOCK_FOUR;  // 冲四
                case 7: return LIVE_FOUR;   // 活四
                default: break;
            }
        }
        if (block == 1) {
            switch (count) {
                case 4: return BLOCK_FOUR;  // 冲四
                case 5: return BLOCK_FOUR;  // 冲四
                case 6: return BLOCK_FOUR;  // 冲四
                case 7: return LIVE_FOUR;   // 活四
                default: break;
            }
        }
        if (block == 2) {
            switch (count) {
                case 4: return BLOCK_FOUR;  // 冲四
                case 5: return BLOCK_FOUR;  // 冲四
                case 6: return BLOCK_FOUR;  // 冲四
                case 7: return BLOCK_FOUR;  // 冲四
                default: break;
            }
        }
    } // end of else if (empty == 3 || empty == count - 3)
    else if (empty == 4 || empty == count - 4) {
        if (count >= 9) {
            return FIVE_LINE;               // 五连
        }
        if (block == 0) {
            switch (count) {
                case 5: return LIVE_FOUR;   // 活四
                case 6: return LIVE_FOUR;   // 活四
                case 7: return LIVE_FOUR;   // 活四
                case 8: return LIVE_FOUR;   // 活四
                default: break;
            }
        }
        if (block == 1) {
            switch (count) {
                case 4: return BLOCK_FOUR;  // 冲四
                case 5: return BLOCK_FOUR;  // 冲四
                case 6: return BLOCK_FOUR;  // 冲四
                case 7: return BLOCK_FOUR;  // 冲四
                case 8: return LIVE_FOUR;   // 活四
                default: break;
            }
        }
        if (block == 2) {
            switch (count) {
                case 5: return BLOCK_FOUR;  // 冲四
                case 6: return BLOCK_FOUR;  // 冲四
                case 7: return BLOCK_FOUR;  // 冲四
                case 8: return BLOCK_FOUR;  // 冲四
                default: break;
            }
        }
    } // end of else if (empty == 4 || empty == count - 4)
    else if (empty == 5 || empty == count - 5) {
        return FIVE_LINE;                   // 五连
    } // end of else if (empty == 5 || empty == count - 5)
    return 0;                               // 缺省
}

/*
 * Function Name:    evaluatePoint
 * Function:         Evaluate the situation at a specific point
 * Input Parameters: const int x
 *                   const int y
 *                   const Status flag
 * Return Value:     score
 */
int evaluatePoint(const int x, const int y, const Status flag)
{
    /* Horizontal direction ( - ) */
    int score = 0, count = 1, block = 0, empty = -1;
    for (int i = y + 1; true; i++) {
        if (i >= BOARD_SIZE) {
            block++;
            break;
        }
        if (g_board[x][i] == Empty) {
            if (empty == -1 && i < BOARD_SIZE - 1 && g_board[x][i + 1] == flag) {
                empty = count;
                continue;
            }
            else {
                break;
            }
        }
        else if (g_board[x][i] == flag) {
            count++;
            continue;
        }
        else {
            block++;
            break;
        }
    } // end of for
    for (int i = y - 1; true; i--) {
        if (i < 0) {
            block++;
            break;
        }
        if (g_board[x][i] == Empty) {
            if (empty == -1 && i > 0 && g_board[x][i - 1] == flag) {
                empty = 0;
                continue;
            }
            else {
                break;
            }
        }
        else if (g_board[x][i] == flag) {
            count++;
            if (empty != -1) {
                empty++;
            }
            continue;
        }
        else {
            block++;
            break;
        }
    } // end of for
    score += evaluateState(count, block, empty);

    /* Vertical direction ( | ) */
    count = 1;
    block = 0;
    empty = -1;
    for (int i = x + 1; true; i++) {
        if (i >= BOARD_SIZE) {
            block++;
            break;
        }
        if (g_board[i][y] == Empty) {
            if (empty == -1 && i < BOARD_SIZE - 1 && g_board[i + 1][y] == flag) {
                empty = count;
                continue;
            }
            else {
                break;
            }
        }
        else if (g_board[i][y] == flag) {
            count++;
            continue;
        }
        else {
            block++;
            break;
        }
    } // end of for
    for (int i = x - 1; true; i--) {
        if (i < 0) {
            block++;
            break;
        }
        if (g_board[i][y] == Empty) {
            if (empty == -1 && i > 0 && g_board[i - 1][y] == flag) {
                empty = 0;
                continue;
            }
            else {
                break;
            }
        }
        else if (g_board[i][y] == flag) {
            count++;
            if (empty != -1) {
                empty++;
            }
            continue;
        }
        else {
            block++;
            break;
        }
    } // end of for
    score += evaluateState(count, block, empty);

    /* Main diagonal direction ( \ ) */
    count = 1;
    block = 0;
    empty = -1;
    for (int i = 1; true; i++) {
        int X = x + i;
        int Y = y + i;
        if (X >= BOARD_SIZE || Y >= BOARD_SIZE) {
            block++;
            break;
        }
        if (g_board[X][Y] == Empty) {
            if (empty == -1 && (X < BOARD_SIZE - 1 && Y < BOARD_SIZE - 1) && g_board[X + 1][Y + 1] == flag) {
                empty = count;
                continue;
            }
            else {
                break;
            }
        }
        else if (g_board[X][Y] == flag) {
            count++;
            continue;
        }
        else {
            block++;
            break;
        }
    } // end of for
    for (int i = 1; true; i++) {
        int X = x - i;
        int Y = y - i;
        if (X < 0 || Y < 0) {
            block++;
            break;
        }
        if (g_board[X][Y] == Empty) {
            if (empty == -1 && (X > 0 && Y > 0) && g_board[X - 1][Y - 1] == flag) {
                empty = 0;
                continue;
            }
            else {
                break;
            }
        }
        else if (g_board[X][Y] == flag) {
            count++;
            if (empty != -1) {
                empty++;
            }
            continue;
        }
        else {
            block++;
            break;
        }
    } // end of for
    score += evaluateState(count, block, empty);

    /* Minor diagonal direction ( / ) */
    count = 1;
    block = 0;
    empty = -1;
    for (int i = 1; true; i++) {
        int X = x + i;
        int Y = y - i;
        if (X < 0 || Y < 0 || X >= BOARD_SIZE || Y >= BOARD_SIZE) {
            block++;
            break;
        }
        if (g_board[X][Y] == Empty) {
            if (empty == -1 && (X < BOARD_SIZE - 1 && Y > 0) && g_board[X + 1][Y - 1] == flag) {
                empty = count;
                continue;
            }
            else {
                break;
            }
        }
        else if (g_board[X][Y] == flag) {
            count++;
            continue;
        }
        else {
            block++;
            break;
        }
    } // end of for
    for (int i = 1; true; i++) {
        int X = x - i;
        int Y = y + i;
        if (X < 0 || Y < 0 || X >= BOARD_SIZE || Y >= BOARD_SIZE) {
            block++;
            break;
        }
        if (g_board[X][Y] == Empty) {
            if (empty == -1 && (X > 0 && Y < BOARD_SIZE - 1) && g_board[X - 1][Y + 1] == flag) {
                empty = 0;
                continue;
            }
            else {
                break;
            }
        }
        else if (g_board[X][Y] == flag) {
            count++;
            if (empty == -1) {
                empty++;
            }
            continue;
        }
        else {
            block++;
            break;
        }
    } // end of for
    score += evaluateState(count, block, empty);
    return score;
}

/*
 * Function Name:    evaluateBoard
 * Function:         Evaluate the situation of our side
 * Input Parameters: void
 * Return Value:     score
 */
int evaluateBoard(void)
{
    int result = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (g_board[i][j] == g_myFlag) {
                result += g_myScore[i][j]; // Add our side's score
            }
            else if (g_board[i][j] == g_enemyFlag) {
                result -= g_enemyScore[i][j]; // Subtract opponent's score
            }
        }
    }
    return result;
}

/*
 * Function Name:    updateScore
 * Function:         Update the chessboard score
 * Input Parameters: const int x
 *                   const int y
 * Return Value:     void
 */
void updateScore(const int x, const int y)
{
    /* Update the current point score */
    if (g_board[x][y] == g_myFlag) {
        g_myScore[x][y] = evaluatePoint(x, y, g_myFlag);
    }
    else if (g_board[x][y] == g_enemyFlag) {
        g_enemyScore[x][y] = evaluatePoint(x, y, g_enemyFlag);
    }
    else {
        g_myScore[x][y] = 0;
        g_enemyScore[x][y] = 0;
    }

    /* Update the scores of points in eight directions */
    for (int i = 0; i < 8; i++) {
        int newX = x, newY = y;
        while (true) {
            newX += OFFSET_X[i];
            newY += OFFSET_Y[i];
            if (!isInBound(newX, newY)) {
                break;
            }
            if (g_board[newX][newY] == g_myFlag) {
                g_myScore[newX][newY] = evaluatePoint(newX, newY, g_myFlag);
            }
            else if (g_board[newX][newY] == g_enemyFlag) {
                g_enemyScore[newX][newY] = evaluatePoint(newX, newY, g_enemyFlag);
            }
        }
    }
}

/*
 * Function Name:    makeMove
 * Function:         Make a move
 * Input Parameters: const int x
 *                   const int y
 *                   const Status flag
 * Return Value:     void
 */
void makeMove(const int x, const int y, const Status flag = Empty)
{
    updateZobristHash(x, y, g_board[x][y]);
    g_board[x][y] = flag;
    updateZobristHash(x, y, flag);
    updateScore(x, y);
}

/*
 * Function Name:    findEmptyToPlace
 * Function:         Find a empty position to place
 * Input Parameters: const Status flag
 *                   int& bestX
 *                   int& bestY
 * Return Value:     void
 */
void findEmptyToPlace(const Status flag, int& bestX, int& bestY)
{
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (g_board[i][j] == Empty) {
                bestX = i;
                bestY = j;
                return;
            }
        }
    }
}

/*
 * Function Name:    checkLine
 * Function:         Check five in a line
 * Input Parameters: const int x
 *                   const int y
 *                   const Status flag
 * Return Value:     true / false
 */
bool checkLine(const int x, const int y, const Status flag)
{
    int i, j, count;
    for (int dir = 4; dir < 8; dir++) {
        count = 1;
        i = x + OFFSET_X[dir];
        j = y + OFFSET_Y[dir];
        while (isInBound(i, j) && g_board[i][j] == flag) {
            count++;
            i += OFFSET_X[dir];
            j += OFFSET_Y[dir];
        }
        i = x - OFFSET_X[dir];
        j = y - OFFSET_Y[dir];
        while (isInBound(i, j) && g_board[i][j] == flag) {
            count++;
            i -= OFFSET_X[dir];
            j -= OFFSET_Y[dir];
        }
        if (count >= 5) {
            return true;
        }
    }
    return false;
}

/*
 * Function Name:    checkLine
 * Function:         check line
 * Input Parameters: const int x
 *                   const int y
 *                   const Status flag
 *                   const int checkCount
 *                   const int checkEmpty
 * Return Value:     true / false
 */
bool checkLine(const int x, const int y, const Status flag, const int checkCount, const int checkEmpty)
{
    int i, j, count, empty;
    for (int dir = 4; dir < 8; dir++) {
        count = 1;
        empty = 0;
        i = x + OFFSET_X[dir];
        j = y + OFFSET_Y[dir];
        while (isInBound(i, j)) {
            if (g_board[i][j] == flag) {
                count++;
            }
            else if (g_board[i][j] == Empty) {
                empty++;
                break;
            }
            else {
                break;
            }
            i += OFFSET_X[dir];
            j += OFFSET_Y[dir];
        }
        i = x - OFFSET_X[dir];
        j = y - OFFSET_Y[dir];
        while (isInBound(i, j)) {
            if (g_board[i][j] == flag) {
                count++;
            }
            else if (g_board[i][j] == Empty) {
                empty++;
                break;
            }
            else {
                break;
            }
            i -= OFFSET_X[dir];
            j -= OFFSET_Y[dir];
        }
        if (count == checkCount && empty == checkEmpty) {
            return true;
        }
    }
    return false;
}

/*
 * Function Name:    generateMoves
 * Function:         Generate moves with heuristic search
 * Input Parameters: Move moves[]
 *                   int& movesLength
 *                   const Status flag
 * Return Value:     void
 */
void generateMoves(Move moves[], int& movesLength, const Status flag)
{
    /* Find candidate points */
    movesLength = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (g_board[i][j] == Empty && hasNeighbor(i, j)) {
                moves[movesLength].x = i;
                moves[movesLength].y = j;
                moves[movesLength].score = evaluatePoint(i, j, flag);
                movesLength++;
            }
        }
    }

    /* Heuristic search */
    std::sort(moves, moves + movesLength, [](const Move& a, const Move& b) {
        return a.score > b.score;
        });
}

/*
 * Function Name:    negamaxAlphaBeta
 * Function:         Negamax and alpha-beta pruning algorithm with heuristic search
 * Input Parameters: const int depth
 *                   int alpha
 *                   const int beta
 *                   const Status flag
 *                   int& bestX
 *                   int& bestY
 *                   bool top
 * Return Value:     score
 */
int negamaxAlphaBeta(const int depth, int alpha, const int beta, const Status flag, int& bestX, int& bestY, bool top = false)
{
    /* Check transposition table */
    std::unordered_map<ULL, HashEntry>::iterator it = g_transTable.find(g_currentZobristHash);
    if (it != g_transTable.end() && it->second.depth >= depth) {
        return it->second.score;
    }

    /* Evaluate g_board */
    if (depth == 0) {
        int score = -evaluateBoard();
        g_transTable[g_currentZobristHash] = { depth, score };
        return score;
    }

    /* Heuristic Search */
    int score = 0, bestLocalX = INVALID_COORD, bestLocalY = INVALID_COORD, movesLength = 0;
    Move nextMoves[BOARD_SIZE * BOARD_SIZE];
    generateMoves(nextMoves, movesLength, flag);

    /* Traverse candidate points */
    for (int k = 0; k < movesLength; k++) {
        int i = nextMoves[k].x, j = nextMoves[k].y;
        makeMove(i, j, flag); // Make a move
        score = -negamaxAlphaBeta(depth - 1, -beta, -alpha, static_cast<Status>(3 - flag), bestX, bestY);
        makeMove(i, j); // Undo a move
        if (score >= beta) {
            return beta; // Beta cutoff
        }
        if (score > alpha) {
            alpha = score; // Update alpha
            bestLocalX = i;
            bestLocalY = j;
        }
    }

    /* Update best move */
    if (top && bestLocalX != INVALID_COORD && bestLocalY != INVALID_COORD) {
        bestX = bestLocalX;
        bestY = bestLocalY;
    }

    /* Return the best score */
    return alpha;
}

/*
 * Function Name:    tryMove
 * Function:         Try a move
 * Input Parameters: int& nextX
 *                   int& nextY
 *                   int& score
 * Return Value:     true / false
 */
bool tryMove(int& nextX, int& nextY, int& score)
{
    /* First move */
    if (g_stepCount == 4) {
        nextX = 4;
        nextY = 4;
        return false;
    }
    if (g_stepCount == 5) {
        if (g_board[4][7] == Black) {
            nextX = 7;
            nextY = 4;
            return false;
        }
        if (g_board[7][4] == Black) {
            nextX = 4;
            nextY = 7;
            return false;
        }
        if (g_board[4][4] == Black) {
            nextX = 5;
            nextY = 7;
            return false;
        }
        if (g_board[7][7] == Black) {
            nextX = 6;
            nextY = 4;
            return false;
        }
    }

    /* Check for our winning move (FIVE_LINE) */
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (g_board[i][j] == Empty && checkLine(i, j, g_myFlag)) {
                nextX = i;
                nextY = j;
                return false;
            }
        }
    }

    /* Check for opponent's move (FIVE_LINE) */
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (g_board[i][j] == Empty && checkLine(i, j, g_enemyFlag)) {
                nextX = i;
                nextY = j;
                return false;
            }
        }
    }

    /* Check for our winning move (LIVE_FOUR || (BLOCK_FOUR && LIVE_THREE)) */
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (g_board[i][j] == Empty && (checkLine(i, j, g_myFlag, 4, 2) || (checkLine(i, j, g_myFlag, 4, 1) && checkLine(i, j, g_myFlag, 3, 2)))) {
                nextX = i;
                nextY = j;
                return false;
            }
        }
    }

    /* Check for opponent's move (LIVE_FOUR || (BLOCK_FOUR && LIVE_THREE)) */
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (g_board[i][j] == Empty && (checkLine(i, j, g_enemyFlag, 4, 2) || (checkLine(i, j, g_enemyFlag, 4, 1) && checkLine(i, j, g_enemyFlag, 3, 2)))) {
                nextX = i;
                nextY = j;
                return false;
            }
        }
    }
    return true;
}

/*
 * Function Name:    start
 * Function:         Start the game
 * Input Parameters: void
 * Return Value:     void
 */
void start(void)
{
    /* Get our side's symbol */
    scanf("%d", &g_myFlag);

    /* Initialization */
    g_enemyFlag = static_cast<Status>(3 - g_myFlag);
    memset(g_board, 0, sizeof(g_board));
    memset(g_myScore, 0, sizeof(g_myScore));
    memset(g_enemyScore, 0, sizeof(g_enemyScore));

    /* Initialize zobrist hashing table */
    std::random_device g_randomDevice; // Non-deterministic random number generator
    std::mt19937_64 g_rng(g_randomDevice()); // Random number generator based on the Mersenne Twister algorithm
    std::uniform_int_distribution<ULL> g_uniDist; // Uniform distribution for generating 64-bit unsigned integers
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            for (int k = 0; k < 3; k++) {
                g_zobristTable[i][j][k] = g_uniDist(g_rng);
            }
        }
    }
    g_currentZobristHash = 0;

    /* Default moves */
    makeMove(5, 5, White);
    makeMove(6, 6, White);
    makeMove(5, 6, Black);
    makeMove(6, 5, Black);
    g_stepCount = 4;

    /* Respond to terminal program */
    printf("OK\n");
    fflush(stdout);
}

/*
 * Function Name:    place
 * Function:         Opponent makes a move
 * Input Parameters: void
 * Return Value:     void
 */
void place(void)
{
    Move command = { 0, 0, 0 };
    scanf("%d %d", &command.x, &command.y);
    makeMove(command.x, command.y, g_enemyFlag);
    g_stepCount++;
}

/*
 * Function Name:    turn
 * Function:         Our side makes a move
 * Input Parameters: void
 * Return Value:     void
 */
void turn(void)
{
    int nextX = INVALID_COORD, nextY = INVALID_COORD, score = 0;
    if (tryMove(nextX, nextY, score)) {
        score = negamaxAlphaBeta(SEARCH_DEPTH, MIN_SCORE, MAX_SCORE, g_myFlag, nextX, nextY, true);
    }
    if (nextX == INVALID_COORD || nextY == INVALID_COORD) {
        findEmptyToPlace(g_myFlag, nextX, nextY);
    }
    makeMove(nextX, nextY, g_myFlag);
    printf("%d %d\n", nextX, nextY);
    fflush(stdout);
    g_stepCount++;
#if DEBUG_MODE
    printScore();
    printBoard();
    printf("DEBUG [Depth = %d, NextX = %d, NextY = %d, Score = %d]\n", SEARCH_DEPTH, nextX, nextY, score);
    fflush(stdout);
#endif // DEBUG_MODE
}

/*
 * Function Name:    main
 * Function:         Main function
 * Return Value:     0
 */
int main()
{
    char tag[10] = { 0 };
    while (true) {
        memset(tag, 0, sizeof(tag));
        scanf("%s", tag);
        if (!strcmp(tag, "START")) { // Start
            start();
        }
        else if (!strcmp(tag, "PLACE")) { // Place
            place();
        }
        else if (!strcmp(tag, "TURN")) { // Turn
#if DEBUG_MODE
            clock_t startTime = clock();
#endif // DEBUG_MODE
            turn();
#if DEBUG_MODE
            printf("DEBUG [Time = %ldms]\n", clock() - startTime);
            fflush(stdout);
#endif // DEBUG_MODE
        }
        else if (!strcmp(tag, "END")) { // End
            int status;
            scanf("%d", &status);
            return 0;
        }
    }
}