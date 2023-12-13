# Gomoku

## 项目名称

Gomoku

## 项目实现功能

五子棋AI对战程序

### 比赛规则

本规则是五子棋的原始规则。

* 对局在一个12*12的方形网格上进行；

* 对局由两名玩家（被称为黑方和白方）进行。黑方先行，然后玩家轮流在空棋位上放置自己的棋子；

* 对局在一名玩家成功地以自己的颜色形成连续五颗或以上棋子的一条直线时结束，这条直线可以是水平、垂直或对角线上的；

* 如果棋盘上的所有空棋位都被占据，并且没有玩家达到获胜条件，对局被视为和棋；

* 轮到己方走子时，大脑程序需要在2秒时间内给出落子方案；

* 每一局中，己方不能使用超过90秒的总时间（对方走子时不算己方用时）；

* 大脑程序任何时刻都不能使用超过350MB的内存；

* 在对方走子时，己方的程序会继续保持运行。

### 输入输出格式

五子棋大脑程序需要从标准输入（ `stdin` ）接收指令，并相应地做出响应，将响应输出到标准输出（ `stdout` ）。每一个指令都独占一行。大脑程序的响应也需要独占一行（即跟随一个换行符 `'\n'` ）。以下是大脑程序需要支持的指令。

#### START [FIELD]

在开始对局前，大脑程序一定会收到该指令，指令表明了己方有关的信息。 `FIELD` 代表该己方大脑执子颜色， `FIELD` 为 `1` 时代表己方执黑棋， `FIELD` 为 `2` 时代表己方执白棋。收到该指令后，大脑程序需要在1秒响应OK，否则判负。

#### PLACE [X] [Y]

该指令代表一次对手的行棋， `X` 、 `Y` 是对手要放置棋子的行列坐标（坐标从 `0` 开始）。大脑程序不需要回复该指令。

#### TURN

该指令代表轮到己方操作。大脑程序收到该指令后，经过计算得出己方走子，并将要放置棋子的行坐标、列坐标作为响应内容。大脑程序需要在指定时限内做出走子响应，否则判负。该指令可能直接出现在 `START` 指令之后，即己方执黑棋开局，也可能出现在一次 `PLACE` 指令之后，即对手落子完毕轮到己方落子。注意，若对手落子完毕后对局直接结束，则 `PLACE ` 指令之后不会跟随有 `TURN` 指令。

#### END [FIELD]

代表该局比赛结束，其中 `FIELD` 代表获胜方， `FIELD` 为 `0` 时是平局， `FIELD` 为 `1` 时是己方获胜， `FIELD` 为 `2` 时是对方获胜。在收到该指令后，大脑程序不需要做任何响应，可以自行决定是否要退出程序。该指令可能在任何时刻出现，例如出现在 `BEGIN` 前的话，可能是对手程序崩溃导致的这场比赛直接结束。

## 项目文件组成

### 源文件

* `gomoku.cpp`
五子棋AI对战程序的实现

## 项目技术细节

### `Status` 类型的实现

```cpp
typedef enum {
    Empty, // 空位标志
    Black, // 黑棋标志
    White  // 白棋标志
} Status;
```

### `Move` 类型的实现

```cpp
typedef struct {
    int x;     // 行数
    int y;     // 列数
    int score; // 评分
} Move;
```

### `HashEntry` 类型的实现

```cpp
typedef struct {
    int depth; // 深度
    int score; // 评分
} HashEntry;
```

### 对战程序主体架构的实现

```cpp
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
```

### 调试模式的实现

```cpp
#define DEBUG_MODE 0 // 调试模式开关

#if DEBUG_MODE
    void printBoard(void) { ... }
#endif // DEBUG_MODE

#if DEBUG_MODE
    void printScore(void) { ... }
#endif // DEBUG_MODE

#if DEBUG_MODE
    printScore();
    printBoard();
    printf("DEBUG [Depth = %d, NextX = %d, NextY = %d, Score = %d]\n", SEARCH_DEPTH, nextX, nextY, score);
    fflush(stdout);
#endif // DEBUG_MODE

#if DEBUG_MODE
    clock_t startTime = clock();
#endif // DEBUG_MODE

#if DEBUG_MODE
    printf("DEBUG [Time = %ldms]\n", clock() - startTime);
    fflush(stdout);
#endif // DEBUG_MODE
```

### Zobrist置换表

```cpp
ULL g_zobristTable[BOARD_SIZE][BOARD_SIZE][3];   // Zobrist 数
ULL g_currentZobristHash;                        // 当前 Zobrist 哈希值
std::unordered_map<ULL, HashEntry> g_transTable; // Zobrist 置换表

void start(void)
{
    ...
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
    ...
}

inline void updateZobristHash(const int x, const int y, const Status flag)
{
    g_currentZobristHash ^= g_zobristTable[x][y][flag];
}
```

### 状态评估函数的实现

```cpp
const int MAX_SCORE = 1000000000;  // 最高分数
const int MIN_SCORE = -1000000000; // 最低分数
const int FIVE_LINE = 10000000;    // 五连分数
const int LIVE_FOUR = 100000;      // 活四分数
const int BLOCK_FOUR = 1000;       // 冲四分数
const int LIVE_THREE = 1000;       // 活三分数
const int BLOCK_THREE = 100;       // 冲三分数
const int LIVE_TWO = 100;          // 活二分数
const int BLOCK_TWO = 10;          // 冲二分数
const int LIVE_ONE = 10;           // 活一分数
const int BLOCK_ONE = 1;           // 冲一分数

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
```

### 位置评估函数的实现

```cpp
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
```

### 局面评估函数的实现

```cpp
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
```

### 评估函数的局部更新

```cpp
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
```

### 启发式搜索

```cpp
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
```

### Negamax算法和Alpha-Beta剪枝算法

```cpp
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
```

## 集成开发环境

* Microsoft Visual Studio 2022

## 编译运行环境

* 本项目适用于x86和x64架构

## 文档更新日期

2023年12月14日