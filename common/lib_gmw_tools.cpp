/****************************************************************
 * Project Name:  common
 * File Name:     lib_gmw_tools.cpp
 * File Function: 消除类游戏通用函数工具集的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/11/21
 ****************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <iomanip>
#include "../common/cmd_console_tools.h"
#include "../common/lib_gmw_tools.h"

/* Namespace */
using namespace std;

/*
 * Function Name:    gmw_draw_block
 * Function:         画一个色块
 * Input Parameters: const CONSOLE_GRAPHICS_INFO* const pCGI: 整体结构指针
 *                   const int row_no: 行号
 *                   const int col_no: 列号
 *                   const int bdi_value: 需要显示的值
 *                   const BLOCK_DISPLAY_INFO* const bdi: 存放该值对应的显示信息的结构体数组
 * Return Value:     0 / -1 (未调用 gmw_init 前调用其它函数)
 * Notes:            pCGI->CBI.block_border == false 时的实现
 */
int gmw_draw_block(const CONSOLE_GRAPHICS_INFO* const pCGI, const int row_no, const int col_no, const int bdi_value, const BLOCK_DISPLAY_INFO* const bdi)
{
    if (pCGI->CBI.block_border)
        tgmw_draw_block(pCGI, row_no, col_no, bdi_value, bdi);
    else {
        if (pCGI->inited != CGI_INITED)
            return -1;
        const BLOCK_DISPLAY_INFO* pbdi = bdi;
        int block_start_x = pCGI->start_x + 2 * pCGI->draw_frame_with_col_no + 2 + col_no * (pCGI->CFI.block_width + 2 * pCGI->CFI.separator);
        int block_start_y = pCGI->start_y + 1 * pCGI->SLI.is_top_status_line + 1 * pCGI->draw_frame_with_row_no + 1 + row_no * (pCGI->CFI.block_high + 1 * pCGI->CFI.separator);
        while (pbdi->value != bdi_value && pbdi->value != BDI_VALUE_END)
            pbdi++;
        cct_setcolor((pbdi->bgcolor == -1 ? pCGI->CFI.bgcolor : pbdi->bgcolor), (pbdi->fgcolor == -1 ? pCGI->CFI.fgcolor : pbdi->fgcolor));
        for (int i = 0; i < pCGI->CFI.block_high; i++) {
            cct_gotoxy(block_start_x, block_start_y + i);
            for (int j = 0; j < pCGI->CFI.block_width / 2; j++) {
                cout << "  ";
                Sleep(pCGI->delay_of_draw_block);
            }
        }
        if (bdi_value != BDI_VALUE_BLANK) {
            cct_gotoxy(block_start_x + (pCGI->CFI.block_width - 1) / 2, block_start_y + (pCGI->CFI.block_high - 1) / 2);
            if (pbdi->content == NULL)
                cout << pbdi->value;
            else
                cout << pbdi->content;
        }
    }
    return 0;
}