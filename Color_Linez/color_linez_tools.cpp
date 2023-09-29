/****************************************************************
 * Project Name:  Color_Linez
 * File Name:     color_linez_tools.cpp
 * File Function: 工具函数的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/9/30
 ****************************************************************/

#include <iostream>
#include "../common/cmd_console_tools.h"
#include "../common/lib_gmw_tools.h"
#include "color_linez.h"

using namespace std;

/*
 * Function Name:    initialize_CGI
 * Function:         Initialize CONSOLE_GRAPHICS_INFO structure
 * Input Parameters: CONSOLE_GRAPHICS_INFO* pCGI
 * Return Value:     void
 */
void initialize_CGI(CONSOLE_GRAPHICS_INFO* pCGI)
{
    cct_setconsoletitle("Color Linez");
    cct_setcursor(CURSOR_INVISIBLE);
    gmw_init(pCGI);
    gmw_set_rowcol(pCGI, row, col);
    gmw_set_font(pCGI, "新宋体", 24);
    gmw_set_ext_rowcol(pCGI, 3, 0, 2, 35);
    gmw_set_frame_style(pCGI, 2, 1);
    gmw_set_frame_color(pCGI, COLOR_HWHITE, COLOR_BLACK);
    gmw_set_status_line_switch(pCGI, TOP_STATUS_LINE, false);
    gmw_set_status_line_switch(pCGI, LOWER_STATUS_LINE, false);
    gmw_draw_frame(pCGI);
    print_statistic_chart();
}

/*
 * Function Name:    print_statistic_chart
 * Function:         Print statistic chart
 * Input Parameters: void
 * Return Value:     void
 */
void print_statistic_chart(void)
{
    cct_showstr(10 + col * 2, 1, "彩球游戏 Color Linez", COLOR_BLACK, COLOR_HYELLOW);
    cct_showstr(6 + col * 4, 3, "╔═════╦════════╗", COLOR_HWHITE, COLOR_BLACK);
    cct_showstr(6 + col * 4, 4, "║得分:   0 ║下轮生成:       ║", COLOR_HWHITE, COLOR_BLACK);
    cct_showstr(6 + col * 4, 5, "╚═════╩════════╝", COLOR_HWHITE, COLOR_BLACK);
    cct_showstr(6 + col * 4, 7, "╔══════════════╗", COLOR_HWHITE, COLOR_BLACK);
    for (int i = 0; i < 7; i++) {
        cct_showstr(6 + col * 4, 8 + i * 2, "║", COLOR_HWHITE, COLOR_BLACK);
        cct_setcolor(COLOR_HWHITE, bdi[i + 1].fgcolor);
        cout << "●球数";
        cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
        cout << ":   (  . %) 已消除:   ║";
        cct_showstr(6 + col * 4, 9 + i * 2, i == 6 ? "╚══════════════╝" : "╠══════════════╣", COLOR_HWHITE, COLOR_BLACK);
    }
    cct_showstr(2, 5 + row * 2, "[游戏方法:] 单击鼠标左键移动彩球连线消除 按R/r键重新开始游戏 按Q/q键退出", COLOR_BLACK, COLOR_HWHITE);
}

/*
 * Function Name:    BFS
 * Function:         Breadth-First Search
 * Input Parameters: int grid[][col]
 *                   int startRow
 *                   int startCol
 *                   int targetRow
 *                   int targetCol
 *                   struct point path[]
 * Return Value:     -1 / shortest path length
 */
int BFS(int grid[][col], int startRow, int startCol, int targetRow, int targetCol, struct point path[])
{
    /* Define offsets for four directions to traverse adjacent nodes */
    int dx[] = { 0, 0, 1, -1 };
    int dy[] = { 1, -1, 0, 0 };

    /* Define a queue to store nodes to be explored */
    queue q;

    /* Define a 2D array to record visited nodes */
    bool visited[row][col] = { false };

    /* Define a 2D array to record the predecessor node for backtracking the path */
    point pre[row][col] = { {0, 0} };

    /* Enqueue the starting node and mark it as visited */
    q.push({ startRow, startCol });
    visited[startRow][startCol] = true;

    /* Start Breadth-First Search */
    while (!q.empty()) {
        /* If the current node is the target node, backtrack to record the path */
        point curr = q.pop();
        if (curr.x == targetRow && curr.y == targetCol) {
            int steps = 0;
            while (curr.x != startRow || curr.y != startCol) {
                path[row * col - 1 - steps].x = curr.x;
                path[row * col - 1 - steps].y = curr.y;
                steps++;
                curr = pre[curr.x][curr.y];
            }
            path[row * col - 1 - steps].x = startRow;
            path[row * col - 1 - steps].y = startCol;
            return steps;
        }

        /* Traverse adjacent nodes in four directions */
        for (int i = 0; i < 4; i++) {
            /* Check if the adjacent node is valid, unvisited, and not an obstacle (assuming obstacles are represented by 1) */
            int nextX = curr.x + dx[i];
            int nextY = curr.y + dy[i];
            bool is_valid = (nextX >= 0 && nextX < row && nextY >= 0 && nextY < col);
            if (is_valid && !visited[nextX][nextY] && grid[nextX][nextY] != 1) {
                /* Enqueue the adjacent node and mark it as visited */
                q.push({ nextX, nextY });
                visited[nextX][nextY] = true;

                /* Record the predecessor node for backtracking the path */
                pre[nextX][nextY] = curr;
            }
        }
    }

    /* If the path is not found, return -1 to indicate that the target point is unreachable */
    return -1;
}

/*
 * Function Name:    print_moving_path
 * Function:         Print moving path
 * Input Parameters: CONSOLE_GRAPHICS_INFO* pCGI
 *                   struct point path[]
 *                   int startRow
 *                   int startCol
 *                   int value
 * Return Value:     void
 */
void print_moving_path(CONSOLE_GRAPHICS_INFO* pCGI, struct point path[], int startRow, int startCol, int value)
{
    for (int i = 0; i < row * col - 1; i++) {
        if (path[i].x == -1 && path[i].y == -1)
            continue;
        if (path[i].x > path[i + 1].x)
            gmw_move_block(pCGI, path[i].x, path[i].y, value, BDI_VALUE_BLANK, bdi, DOWN_TO_UP, 1);
        else if (path[i].x < path[i + 1].x)
            gmw_move_block(pCGI, path[i].x, path[i].y, value, BDI_VALUE_BLANK, bdi, UP_TO_DOWN, 1);
        else if (path[i].y > path[i + 1].y)
            gmw_move_block(pCGI, path[i].x, path[i].y, value, BDI_VALUE_BLANK, bdi, RIGHT_TO_LEFT, 1);
        else if (path[i].y < path[i + 1].y)
            gmw_move_block(pCGI, path[i].x, path[i].y, value, BDI_VALUE_BLANK, bdi, LEFT_TO_RIGHT, 1);
    }
}