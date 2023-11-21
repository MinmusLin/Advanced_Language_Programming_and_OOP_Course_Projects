# Tic Tac Toe

## 项目名称

Tic_Tac_Toe

## 项目实现功能

井字棋游戏

## 项目文件组成

* `cmd_console_tools.h`
伪图形界面函数工具集的头文件

* `tic_tac_toe.h`
算法函数、主体函数、工具函数的头文件

### 源文件

* `cmd_console_tools.cpp`
伪图形界面函数工具集的实现

* `tic_tac_toe_algorithm.cpp`
算法函数的实现

* `tic_tac_toe_main.cpp`
主体函数的实现

* `tic_tac_toe_tools.cpp`
工具函数的实现

## 项目技术细节

### 游戏主体架构

```cpp
while (true) {
    int optn = menu();
    switch (optn) {
        case 1:
        case 2:
        case 3:
        case 4: {
            GridStatus gridStatus[BOARD_SIZE][BOARD_SIZE] = { Empty };
            for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
                cout << ">>> 第 " << i + 1 << " 轮" << endl << endl;
                while (true) {
                    int r, c;
                    switch (optn) {
                        case 1:
                            cout << (i % 2 ? "后手(○)" : "先手(×)") << "请输入本轮落子行数: ";
                            r = input_digit(1, BOARD_SIZE);
                            cout << (i % 2 ? "后手(○)" : "先手(×)") << "请输入本轮落子列数: ";
                            c = input_digit(1, BOARD_SIZE);
                            break;
                        case 2:
                            if (i % 2) {
                                cout << "后手(○)请输入本轮落子行数: ";
                                r = input_digit(1, BOARD_SIZE);
                                cout << "后手(○)请输入本轮落子列数: ";
                                c = input_digit(1, BOARD_SIZE);
                            }
                            else {
                                find_next_move_to_win(gridStatus, r, c);
                                cout << "先手(×)请输入本轮落子行数: " << ++r << endl;
                                cout << "先手(×)请输入本轮落子列数: " << ++c << endl;
                            }
                            break;
                        case 3:
                            if (i % 2) {
                                find_next_move_to_win(gridStatus, r, c);
                                cout << "后手(○)请输入本轮落子行数: " << ++r << endl;
                                cout << "后手(○)请输入本轮落子列数: " << ++c << endl;
                            }
                            else {
                                cout << "先手(×)请输入本轮落子行数: ";
                                r = input_digit(1, BOARD_SIZE);
                                cout << "先手(×)请输入本轮落子列数: ";
                                c = input_digit(1, BOARD_SIZE);
                            }
                            break;
                        case 4:
                            find_next_move_to_win(gridStatus, r, c);
                            cout << (i % 2 ? "后手(○)" : "先手(×)") << "请输入本轮落子行数: " << ++r << endl;
                            cout << (i % 2 ? "后手(○)" : "先手(×)") << "请输入本轮落子列数: " << ++c << endl;
                            break;
                        default:
                            exit(-1);
                    }
                    if (gridStatus[r - 1][c - 1] == Empty) {
                        gridStatus[r - 1][c - 1] = (i % 2 ? SecondPlayer : FirstPlayer);
                        cout << endl;
                        print_grid_status(gridStatus);
                        cout << endl;
                        break;
                    }
                    else
                        cout << endl << ">>> 该位置已被占用，请重新输入!" << endl << endl;
                }
                GridStatus winner = check_win(gridStatus);
                if (winner == FirstPlayer || winner == SecondPlayer) {
                    print_winner(winner);
                    break;
                }
                else if (winner == Empty && i == BOARD_SIZE * BOARD_SIZE - 1)
                    cout << ">>> 游戏结束! 平局!" << endl << endl;
            }
            system("pause");
            break;
        }
        default:
            return 0;
    }
}
```

### 算法函数的实现

井字棋游戏算法：

* 如果自己能赢，就下一步走法以获胜。

* 如果对手能赢，就下一步走法以阻止对手获胜。

* 否则，下一步走法选择一个空白位置。一个常见的优先级顺序是：中心位置 > 边缘位置 > 角落位置。

```cpp
GridStatus find_next_move_to_win(const GridStatus gridStatus[][BOARD_SIZE], int& row, int& col)
{
    /* Initialize temporary grid to simulate moves */
    GridStatus tmpGridStatus[BOARD_SIZE][BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            tmpGridStatus[i][j] = gridStatus[i][j];

    /* Iterate over empty positions to simulate possible moves */
    for (int k = 1; k <= 2; k++)
        for (int i = 0; i < BOARD_SIZE; i++)
            for (int j = 0; j < BOARD_SIZE; j++)
                if (tmpGridStatus[i][j] == Empty) {
                    tmpGridStatus[i][j] = static_cast<GridStatus>(k);
                    GridStatus winner = check_win(tmpGridStatus);
                    if (winner == Empty) {
                        tmpGridStatus[i][j] = Empty;
                        continue;
                    }
                    else {
                        row = i;
                        col = j;
                        return winner;
                    }
                }

    /* If no winning or blocking move is found, choose a empty position */
    const int preferredPositions[BOARD_SIZE * BOARD_SIZE][2] = {
        {1, 1}, // Center
        {0, 1}, // Middle row
        {1, 0}, // Middle column
        {2, 1}, // Bottom row
        {1, 2}, // Rightmost column
        {0, 0}, // Top left corner
        {0, 2}, // Top right corner
        {2, 0}, // Bottom left corner
        {2, 2}  // Bottom right corner
    };
    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
        int r = preferredPositions[i][0], c = preferredPositions[i][1];
        if (tmpGridStatus[r][c] == Empty) {
            row = r;
            col = c;
            break;
        }
    }
    return Empty;
}
```

## 集成开发环境

* Microsoft Visual Studio 2022

## 编译运行环境

* 本项目适用于x86和x64架构

## 文档更新日期

2023年11月21日