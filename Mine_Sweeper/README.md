# Mine Sweeper

## 项目名称

Mine_Sweeper

## 项目实现功能

扫雷游戏

1. 经典难度模式（8×8）8颗雷

1. 简单难度模式（9×9）10颗雷

1. 中等难度模式（16×16）40颗雷

1. 专家难度模式（16×30）99颗雷

1. 自定义难度模式

## 项目文件组成

### 头文件

* `cmd_console_tools.h`
伪图形界面函数工具集的头文件

* `lib_gmw_tools.h`
消除类游戏通用函数工具集的头文件

* `mine_sweeper.h`
主体函数、菜单函数、工具函数的头文件

### 源文件

* `cmd_console_tools.cpp`
伪图形界面函数工具集的实现

* `lib_gmw_tools.cpp`
消除类游戏通用函数工具集的实现

* `mine_sweeper_main.cpp`
主体函数的实现

* `mine_sweeper_menu.cpp`
菜单函数的实现

* `mine_sweeper_tools.cpp`
工具函数的实现

### 资源文件
* `lib_gmw_tools.lib`
消除类游戏通用函数工具集的静态链接库

## 项目技术细节

### 游戏主体架构

```cpp
while (1) {
    /* Call the menu function */
    int row, col, mine;
    int optn = menu(row, col, mine);
    if (optn == 'Q' || optn == 'q')
        return 0;

    /* Initialize unit and CONSOLE_GRAPHICS_INFO structure */
    CONSOLE_GRAPHICS_INFO CGI;
    initialize_CGI(&CGI, row, col);
    struct unit matrix[18][34];
    initialize_matrix(matrix, row, col, mine);

    /* Print all color blocks */
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            draw_block(&CGI, i, j, matrix, bdi);

    /* Save the start time */
    time_t start_time = clock();

    /* Read keyboard and mouse events */
    while (1) {
        /* Print the number of mines */
        cct_showint(10, 0, mine, COLOR_BLACK, COLOR_HYELLOW);

        /* Determine if the game is over */
        if (game_judgment(matrix, row, col)) {
            print_prompt(start_time, true);
            break;
        }

        /* Read keyboard and mouse events */
        int MAction, MRow, MCol, KeyCode1 = 0, KeyCode2 = 0;
        gmw_read_keyboard_and_mouse(&CGI, MAction, MRow, MCol, KeyCode1, KeyCode2);

        /* Determine whether to quit the game */
        if (KeyCode1 == 27)
            break;

        /* Print a color block */
        if (MAction == MOUSE_LEFT_BUTTON_CLICK || MAction == MOUSE_LEFT_BUTTON_DOUBLE_CLICK) {
            if (matrix[MRow + 1][MCol + 1].status == UNKNOWN && matrix[MRow + 1][MCol + 1].status != MARKED_MINE && matrix[MRow + 1][MCol + 1].status != MARKED_QUESTION) {
                if (matrix[MRow + 1][MCol + 1].value == '*') {
                    matrix[MRow + 1][MCol + 1].status = KNOWN;
                    draw_block(&CGI, MRow, MCol, matrix, bdi);
                    Sleep(300);
                    for (int i = 1; i <= row; i++) {
                        for (int j = 1; j <= col; j++) {
                            if (matrix[i][j].value == '*') {
                                matrix[i][j].status = KNOWN;
                                Sleep(50);
                                draw_block(&CGI, i - 1, j - 1, matrix, bdi);
                            }
                        }
                    }
                    print_prompt(start_time, false);
                    break;
                }
                else if (matrix[MRow + 1][MCol + 1].value) {
                    matrix[MRow + 1][MCol + 1].status = KNOWN;
                    draw_block(&CGI, MRow, MCol, matrix, bdi);
                }
                else {
                    print_continuity(&CGI, MRow, MCol, matrix, bdi, row, col);
                }
            }
        }
        else if (MAction == MOUSE_RIGHT_BUTTON_CLICK || MAction == MOUSE_RIGHT_BUTTON_DOUBLE_CLICK) {
            if (matrix[MRow + 1][MCol + 1].status == UNKNOWN) {
                matrix[MRow + 1][MCol + 1].status = MARKED_MINE;
                cct_showch(10, 0, ' ', COLOR_BLACK, COLOR_BLACK, 4);
                cct_showint(10, 0, --mine, COLOR_BLACK, COLOR_HYELLOW);
                draw_block(&CGI, MRow, MCol, matrix, bdi);
            }
            else if (matrix[MRow + 1][MCol + 1].status == MARKED_MINE) {
                matrix[MRow + 1][MCol + 1].status = MARKED_QUESTION;
                cct_showch(10, 0, ' ', COLOR_BLACK, COLOR_BLACK, 4);
                cct_showint(10, 0, ++mine, COLOR_BLACK, COLOR_HYELLOW);
                draw_block(&CGI, MRow, MCol, matrix, bdi);
            }
            else if (matrix[MRow + 1][MCol + 1].status == MARKED_QUESTION) {
                matrix[MRow + 1][MCol + 1].status = UNKNOWN;
                draw_block(&CGI, MRow, MCol, matrix, bdi);
            }
        }
    }
}
```

## 集成开发环境

* Microsoft Visual Studio

## 编译运行环境

* 本项目仅适用于x86架构

* Windows控制台主机的旧版控制台运行（取消选项“快速编辑模式”和“插入模式”）

## 文档更新日期

2023年9月25日