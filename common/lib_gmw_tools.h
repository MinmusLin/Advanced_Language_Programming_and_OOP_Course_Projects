/****************************************************************
 * Project Name:  common
 * File Name:     lib_gmw_tools.h
 * File Function: 消除类游戏通用函数工具集的头文件
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/9/27
 ****************************************************************/

#pragma once
#include <iostream>

/* Define status line information */
#define TOP_STATUS_LINE 0
#define LOWER_STATUS_LINE 1

/* Define a structure describing status line information */
typedef struct _status_line_info_ {
    /* Whether there is top or lower status line */
    bool is_top_status_line;
    bool is_lower_status_line;

    /* Fill bytes */
    char pad1[2];

    /* The position, normal information color scheme, and catchy information color scheme of the top status line */
    int top_start_x;
    int top_start_y;
    int top_normal_bgcolor;
    int top_normal_fgcolor;
    int top_catchy_bgcolor;
    int top_catchy_fgcolor;

    /* The position, normal information color scheme, and catchy information color scheme of the lower status line */
    int lower_start_x;
    int lower_start_y;
    int lower_normal_bgcolor;
    int lower_normal_fgcolor;
    int lower_catchy_bgcolor;
    int lower_catchy_fgcolor;

    /* The width occupied by the status line (this value is calculated, if the information exceeds the width, it will be truncated) */
    int width;

    /* Fill bytes */
    char pad[64];
} STATUS_LINE_INFO;

/* Define length (including '\0') of the character array storing the game main frame border information */
#define CFI_LEN 3

/* Define a structure describing the game main frame area */
typedef struct _console_frame_info_ {
    /* The shapes of the game main frames */
    char top_left[CFI_LEN]; // "╔"
    char lower_left[CFI_LEN]; // "╚"
    char top_right[CFI_LEN]; // "╗"
    char lower_right[CFI_LEN]; // "╝"
    char h_normal[CFI_LEN]; // "═"
    char v_normal[CFI_LEN]; // "║"
    char h_top_separator[CFI_LEN]; // "╤"
    char h_lower_separator[CFI_LEN]; // "╧"
    char v_left_separator[CFI_LEN]; // "╟"
    char v_right_separator[CFI_LEN]; // "╢"
    char mid_separator[CFI_LEN]; // "┼"

    /* Fill bytes */
    char pad1[3];

    /* Background color and foreground color of the game main frame area */
    int bgcolor;
    int fgcolor;

    /* Width and height of each color block (width must be a multiple of 2) */
    int block_width;
    int block_high;

    /* Whether separator line is needed */
    bool separator;

    /* Fill bytes */
    char pad2[3];

    /* Additional width and height for each color block (if there is a separator line it is 2 or 1) */
    int block_width_ext;
    int block_high_ext;

    /* Total width per row / per column (including the separator line) */
    int bwidth;
    int bhigh;

    /* Fill bytes */
    char pad[64];
} CONSOLE_FRAME_INFO;

/* Define length (including '\0') of the character array storing the color block border information */
#define CBI_LEN 3

/* Define a structure describing color block information */
typedef struct _console_block_info_ {
    /* The shapes of the color block frames */
    char top_left[CBI_LEN]; // "╔"
    char lower_left[CBI_LEN]; // "╚"
    char top_right[CBI_LEN]; // "╗"
    char lower_right[CBI_LEN]; // "╝"
    char h_normal[CBI_LEN]; // "═"
    char v_normal[CBI_LEN]; // "║"

    /* Whether border is needed */
    bool block_border;

    /* Fill bytes */
    bool pad1;
    char pad[64];
} CONSOLE_BLOCK_INFO;

/* Define the special value for black and end in the BLOCK_DISPLAY_INFO array */
#define BDI_VALUE_BLANK 0
#define BDI_VALUE_END -999

/* Define a structure of correspondence between the internal array's int value for color block display and the corresponding graphical representation on the interface */
typedef struct _block_display_info_ {
    const int value;
    const int bgcolor;
    const int fgcolor;
    const char* content;
} BLOCK_DISPLAY_INFO;
//Usage example:
/*
    const BLOCK_DISPLAY_INFO bdi[] = {
        {BDI_VALUE_BLANK,-1,-1,NULL}, // 如果为BDI_VALUE_BLANK，则不显示内容
        {1,COLOR_HYELLOW,COLOR_HRED,"★"}, // 如果二维数组中的值为1，则显示★
        {2,COLOR_HYELLOW,COLOR_HRED,-1,NULL}, // NULL表示直接显示二维数组中的值2
        {BDI_VALUE_END,-1,-1,NULL} // 如果为BDI_VALUE_END，则结束
    };
*/

/* Define the maximum length of the font name (including '\0') */
#define FONTNAME_LEN 12

/* Define a structure describing font and font size information */
typedef struct _console_font_type_ {
    char font_type[FONTNAME_LEN];
    int font_size_width;
    int font_size_high;
} CONSOLE_FONT_TYPE;

/* Define types of delays */
#define DELAY_OF_DRAW_FRAME 0
#define DELAY_OF_DRAW_BLOCK 1
#define DELAY_OF_BLOCK_MOVED 2
#define BLOCK_MOVED_DELAY_MS 15

/* Define initialization flag */
#define CGI_INITED 99999

/* Define a structure describing all the information of the entire window */
typedef struct _console_graphics_info_ {
    /* Main frame information */
    CONSOLE_FRAME_INFO CFI; // 136 Bytes

    /* Color block information */
    CONSOLE_BLOCK_INFO CBI; // 84 Bytes

    /* Status line information */
    STATUS_LINE_INFO SLI; // 120 Bytes

    /* Font information */
    CONSOLE_FONT_TYPE CFT; // 20 Bytes

    /* A flag indicating whether initialization has been performed. If initialized, set it to 99999 */
    int inited;

    /* The additional rows and columns required for the entire graphical interface on the top, bottom, left, and right */
    int extern_up_lines;
    int extern_down_lines;
    int extern_left_cols;
    int extern_right_cols;

    /* The number of rows and columns of color blocks contained in the game main frame area */
    int row_num;
    int col_num;

    /* Background color and foreground color of the entire graphical interface */
    int area_bgcolor;
    int area_fgcolor;

    /* Whether there is top or lower status line */
    bool top_status_line;
    bool lower_status_line;

    /* Whether row numbers and column labels are needed when printing the main frame */
    bool draw_frame_with_row_no;
    bool draw_frame_with_col_no;

    /* Delay time */
    int delay_of_draw_frame;
    int delay_of_draw_block;
    int delay_of_block_moved;

    /* Starting coordinates of the main frame area */
    int start_x;
    int start_y;

    /* Size of the cmd window */
    int lines;
    int cols;

    /* Fill bytes */
    char pad[64];
} CONSOLE_GRAPHICS_INFO;

/* Define four movement directions */
#define DOWN_TO_UP 0
#define UP_TO_DOWN 1
#define RIGHT_TO_LEFT 2
#define LEFT_TO_RIGHT 3

/* Conditional compilation */
#if 1
#define gmw_set_rowcol tgmw_set_rowcol
#define gmw_set_color tgmw_set_color
#define gmw_set_font tgmw_set_font
#define gmw_set_delay tgmw_set_delay
#define gmw_set_ext_rowcol tgmw_set_ext_rowcol
#define gmw_set_frame_default_linetype tgmw_set_frame_default_linetype
#define gmw_set_frame_linetype tgmw_set_frame_linetype
#define gmw_set_frame_style tgmw_set_frame_style
#define gmw_set_frame_color tgmw_set_frame_color
#define gmw_set_block_default_linetype tgmw_set_block_default_linetype
#define gmw_set_block_linetype tgmw_set_block_linetype
#define gmw_set_block_border_switch tgmw_set_block_border_switch
#define gmw_set_status_line_switch tgmw_set_status_line_switch
#define gmw_set_status_line_color tgmw_set_status_line_color
#define gmw_set_rowno_switch tgmw_set_rowno_switch
#define gmw_set_colno_switch tgmw_set_colno_switch
#define gmw_init tgmw_init
#define gmw_print tgmw_print
#define gmw_draw_frame tgmw_draw_frame
#define gmw_status_line tgmw_status_line
#define gmw_move_block tgmw_move_block
#define gmw_read_keyboard_and_mouse tgmw_read_keyboard_and_mouse
#endif

/* Function declaration in lib_gmw_tools.cpp */

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
int gmw_draw_block(const CONSOLE_GRAPHICS_INFO* const pCGI, const int row_no, const int col_no, const int bdi_value, const BLOCK_DISPLAY_INFO* const bdi);

/* Function declarations in lib_gmw_tools.lib */

/*
 * Function Name:    tgmw_set_rowcol
 * Function:         设置游戏主框架的行列数
 * Input Parameters: CONSOLE_GRAPHICS_INFO* const pCGI
 *                   const int row
 *                   const int col
 * Return Value:     0 / -1 (未调用 gmw_init 前调用其它函数)
 * Notes:            行列数指消除类游戏的矩形区域的行列值
 */
int tgmw_set_rowcol(CONSOLE_GRAPHICS_INFO* const pCGI, const int row, const int col);

/*
 * Function Name:    tgmw_set_color
 * Function:         设置整个cmd窗口的颜色
 * Input Parameters: CONSOLE_GRAPHICS_INFO* const pCGI
 *                   const int bgcolor
 *                   const int fgcolor
 *                   const bool cascade
 * Return Value:     0 / -1 (未调用 gmw_init 前调用其它函数)
 * Notes:            cascade == true 时同步修改游戏主区域颜色和上下状态栏文本颜色
 */
int tgmw_set_color(CONSOLE_GRAPHICS_INFO* const pCGI, const int bgcolor = COLOR_BLACK, const int fgcolor = COLOR_WHITE, const bool cascade = true);

/*
 * Function Name:    tgmw_set_font
 * Function:         设置窗口的字体
 * Input Parameters: CONSOLE_GRAPHICS_INFO* const pCGI
 *                   const char* fontname
 *                   const int fs_high
 *                   const int fs_width
 * Return Value:     0 / -1 (未调用 gmw_init 前调用其它函数)
 * Notes:            仅支持"点阵字体"("Terminal")和"新宋体"
 */
int tgmw_set_font(CONSOLE_GRAPHICS_INFO* const pCGI, const char* fontname = "Terminal", const int fs_high = 16, const int fs_width = 8);

/*
 * Function Name:    tgmw_set_delay
 * Function:         设置延时时间
 * Input Parameters: CONSOLE_GRAPHICS_INFO* const pCGI
 *                   const int type
 *                   const int delay_ms
 * Return Value:     0 / -1 (未调用 gmw_init 前调用其它函数)
 */
int tgmw_set_delay(CONSOLE_GRAPHICS_INFO* const pCGI, const int type, const int delay_ms);

/*
 * Function Name:    tgmw_set_ext_rowcol
 * Function:         设置游戏主框架结构之外需要保留的额外区域
 * Input Parameters: CONSOLE_GRAPHICS_INFO* const pCGI
 *                   const int up_lines
 *                   const int down_lines
 *                   const int left_cols
 *                   const int right_cols
 * Return Value:     0 / -1 (未调用 gmw_init 前调用其它函数)
 */
int tgmw_set_ext_rowcol(CONSOLE_GRAPHICS_INFO* const pCGI, const int up_lines = 0, const int down_lines = 0, const int left_cols = 0, const int right_cols = 0);

/*
 * Function Name:    tgmw_set_frame_default_linetype
 * Function:         填充 CONSOLE_FRAME_TYPE 结构体中的11种线型(缺省4种)
 * Input Parameters: CONSOLE_GRAPHICS_INFO* const pCGI
 *                   const int type : 1 - 全双线
 *                                    2 - 全单线
 *                                    3 - 横双竖单线
 *                                    4 - 横单竖双线
 * Return Value:     0 / -1 (未调用 gmw_init 前调用其它函数)
 */
int tgmw_set_frame_default_linetype(CONSOLE_GRAPHICS_INFO* const pCGI, const int type);

/*
 * Function Name:    tgmw_set_frame_linetype
 * Function:         填充 CONSOLE_FRAME_TYPE 结构体中的11种线型
 * Input Parameters: CONSOLE_GRAPHICS_INFO* const pCGI
 *                   const char* top_left
 *                   const char* lower_left
 *                   const char* top_right
 *                   const char* lower_right
 *                   const char* h_normal
 *                   const char* v_normal
 *                   const char* h_top_separator
 *                   const char* h_lower_separator
 *                   const char* v_left_separator
 *                   const char* v_right_separator
 *                   const char* mid_separator
 * Return Value:     0 / -1 (未调用 gmw_init 前调用其它函数)
 * Notes:            填充2字节字符，超过2字节只取前2字节，填充1字节字符补1个空格，填充NULL补2个空格
 */
int tgmw_set_frame_linetype(CONSOLE_GRAPHICS_INFO* const pCGI, const char* top_left = "╔", const char* lower_left = "╚", const char* top_right = "╗", const char* lower_right = "╝", const char* h_normal = "═", const char* v_normal = "║", const char* h_top_separator = "╦", const char* h_lower_separator = "╩", const char* v_left_separator = "╠", const char* v_right_separator = "╣", const char* mid_separator = "╬");

/*
 * Function Name:    tgmw_set_frame_style
 * Function:         填充 CONSOLE_FRAME_TYPE 结构体中的色块大小与是否需要分隔线
 * Input Parameters: CONSOLE_GRAPHICS_INFO* const pCGI
 *                   const int block_width
 *                   const int block_high
 *                   const bool separator
 * Return Value:     0 / -1 (未调用 gmw_init 前调用其它函数)
 */
int tgmw_set_frame_style(CONSOLE_GRAPHICS_INFO* const pCGI, const int block_width = 2, const int block_high = 1, const bool separator = true);

/*
 * Function Name:    tgmw_set_frame_color
 * Function:         填充 CONSOLE_BORDER_TYPE 结构体中的颜色
 * Input Parameters: CONSOLE_GRAPHICS_INFO* const pCGI
 *                   const int bgcolor
 *                   const int fgcolor
 * Return Value:     0 / -1 (未调用 gmw_init 前调用其它函数)
 */
int tgmw_set_frame_color(CONSOLE_GRAPHICS_INFO* const pCGI, const int bgcolor = -1, const int fgcolor = -1);

/*
 * Function Name:    tgmw_set_block_default_linetype
 * Function:         填充 CONSOLE_BLOCK_INFO 结构体中的6种线型(缺省4种)
 * Input Parameters: CONSOLE_GRAPHICS_INFO* const pCGI
 *                   const int def_type : 1 - 全双线
 *                                        2 - 全单线
 *                                        3 - 横双竖单线
 *                                        4 - 横单竖双线
 * Return Value:     0 / -1 (未调用 gmw_init 前调用其它函数)
 */
int tgmw_set_block_default_linetype(CONSOLE_GRAPHICS_INFO* const pCGI, const int def_type);

/*
 * Function Name:    tgmw_set_block_linetype
 * Function:         填充 CONSOLE_BLOCK_INFO 结构体中的6种线型
 * Input Parameters: CONSOLE_GRAPHICS_INFO* const pCGI
 *                   const char* top_left
 *                   const char* lower_left
 *                   const char* top_right
 *                   const char* lower_right
 *                   const char* h_normal
 *                   const char* v_normal
 * Return Value:     0 / -1 (未调用 gmw_init 前调用其它函数)
 * Notes:            填充2字节字符，超过2字节只取前2字节，填充1字节字符补1个空格，填充NULL补2个空格
 */
int tgmw_set_block_linetype(CONSOLE_GRAPHICS_INFO* const pCGI, const char* top_left = "╔", const char* lower_left = "╚", const char* top_right = "╗", const char* lower_right = "╝", const char* h_normal = "═", const char* v_normal = "║");

/*
 * Function Name:    tgmw_set_block_border_switch
 * Function:         设置每个游戏色块(彩球)是否需要边框
 * Input Parameters: CONSOLE_GRAPHICS_INFO* const pCGI
 *                   const bool on_off
 * Return Value:     0 / -1 (未调用 gmw_init 前调用其它函数)
 */
int tgmw_set_block_border_switch(CONSOLE_GRAPHICS_INFO* const pCGI, const bool on_off = false);

/*
 * Function Name:    tgmw_set_status_line_switch
 * Function:         设置是否显示上下状态栏
 * Input Parameters: CONSOLE_GRAPHICS_INFO* const pCGI
 *                   const int type
 *                   const bool on_off
 * Return Value:     0 / -1 (未调用 gmw_init 前调用其它函数)
 * Notes:            上状态栏仅一行，在主区域最上方框线/列标的上一行，为主区域的第一行
 *                   下状态栏仅一行，在主区域最下方框线的下一行
 *                   状态栏宽度为主区域宽度，若状态栏显示信息过长则截断
 */
int tgmw_set_status_line_switch(CONSOLE_GRAPHICS_INFO* const pCGI, const int type, const bool on_off = true);

/*
 * Function Name:    tgmw_set_status_line_color
 * Function:         设置上下状态栏的颜色
 * Input Parameters: CONSOLE_GRAPHICS_INFO* const pCGI
 *                   const int type
 *                   const int normal_bgcolor
 *                   const int normal_fgcolor
 *                   const int catchy_bgcolor
 *                   const int catchy_fgcolor
 * Return Value:     0 / -1 (未调用 gmw_init 前调用其它函数)
 */
int tgmw_set_status_line_color(CONSOLE_GRAPHICS_INFO* const pCGI, const int type, const int normal_bgcolor = -1, const int normal_fgcolor = -1, const int catchy_bgcolor = -1, const int catchy_fgcolor = -1);

/*
 * Function Name:    tgmw_set_rowno_switch
 * Function:         设置是否显示行标
 * Input Parameters: CONSOLE_GRAPHICS_INFO* const pCGI
 *                   const bool on_off
 * Return Value:     0 / -1 (未调用 gmw_init 前调用其它函数)
 */
int tgmw_set_rowno_switch(CONSOLE_GRAPHICS_INFO* const pCGI, const bool on_off = false);

/*
 * Function Name:    tgmw_set_colno_switch
 * Function:         设置是否显示列标
 * Input Parameters: CONSOLE_GRAPHICS_INFO* const pCGI
 *                   const bool on_off
 * Return Value:     0 / -1 (未调用 gmw_init 前调用其它函数)
 */
int tgmw_set_colno_switch(CONSOLE_GRAPHICS_INFO* const pCGI, const bool on_off = false);

/*
 * Function Name:    tgmw_init
 * Function:         将 CONSOLE_GRAPHICS_INFO 结构体用缺省值进行初始化
 * Input Parameters: CONSOLE_GRAPHICS_INFO* const pCGI
 *                   const int row
 *                   const int col
 *                   const int bgcolor
 *                   const int fgcolor
 * Return Value:     0
 */
int tgmw_init(CONSOLE_GRAPHICS_INFO* const pCGI, const int row = 10, const int col = 10, const int bgcolor = COLOR_BLACK, const int fgcolor = COLOR_WHITE);

/*
 * Function Name:    tgmw_print
 * Function:         打印 CONSOLE_GRAPHICS_INFO 结构体中的各成员值
 * Input Parameters: const CONSOLE_GRAPHICS_INFO* const pCGI
 * Return Value:     0 / -1 (未调用 gmw_init 前调用其它函数)
 */
int tgmw_print(const CONSOLE_GRAPHICS_INFO* const pCGI);

/*
 * Function Name:    tgmw_draw_frame
 * Function:         画游戏主框架
 * Input Parameters: const CONSOLE_GRAPHICS_INFO* const pCGI
 * Return Value:     0 / -1 (未调用 gmw_init 前调用其它函数)
 */
int tgmw_draw_frame(const CONSOLE_GRAPHICS_INFO* const pCGI);

/*
 * Function Name:    tgmw_status_line
 * Function:         显示状态栏信息
 * Input Parameters: const CONSOLE_GRAPHICS_INFO* const pCGI: 整体结构指针
 *                   const int type: 上/下状态栏
 *                   const char* msg: 正常信息
 *                   const char* catchy_msg: 醒目信息
 * Return Value:     0 / -1 (未调用 gmw_init 前调用其它函数)
 * Notes:            若输出宽度超出主框架宽度(含行号列标位置)则截去
 */
int tgmw_status_line(const CONSOLE_GRAPHICS_INFO* const pCGI, const int type, const char* msg, const char* catchy_msg = NULL);

/*
 * Function Name:    tgmw_draw_block
 * Function:         画一个色块
 * Input Parameters: const CONSOLE_GRAPHICS_INFO* const pCGI: 整体结构指针
 *                   const int row_no: 行号
 *                   const int col_no: 列号
 *                   const int bdi_value: 需要显示的值
 *                   const BLOCK_DISPLAY_INFO* const bdi: 存放该值对应的显示信息的结构体数组
 * Return Value:     0 / -1 (未调用 gmw_init 前调用其它函数)
 * Notes:            pCGI->CBI.block_border == true 时的实现
 */
int tgmw_draw_block(const CONSOLE_GRAPHICS_INFO* const pCGI, const int row_no, const int col_no, const int bdi_value, const BLOCK_DISPLAY_INFO* const bdi);

/*
 * Function Name:    tgmw_move_block
 * Function:         移动一个色块
 * Input Parameters: const CONSOLE_GRAPHICS_INFO* const pCGI: 整体结构指针
 *                   const int row_no: 行号
 *                   const int col_no: 列号
 *                   const int bdi_value: 需要显示的值
 *                   const int blank_bdi_value: 移动过程中用于动画效果显示时用于表示空白的值
 *                   const BLOCK_DISPLAY_INFO* const bdi: 存放显示值/空白值对应的显示信息的结构体数组名
 *                   const int direction: 移动方向
 *                   const int distance: 移动距离
 * Return Value:     0 / -1 (未调用 gmw_init 前调用其它函数)
 */
int tgmw_move_block(const CONSOLE_GRAPHICS_INFO* const pCGI, const int row_no, const int col_no, const int bdi_value, const int blank_bdi_value, const BLOCK_DISPLAY_INFO* const bdi, const int direction, const int distance);

/*
 * Function Name:    tgmw_read_keyboard_and_mouse
 * Function:         读键盘和鼠标事件
 * Input Parameters: const CONSOLE_GRAPHICS_INFO* const pCGI: 整体结构指针
 *                   int& MAction: 鼠标事件
 *                   int& MRow: 鼠标所在行数
 *                   int& MCol: 鼠标所在列数
 *                   int& KeyCode1: 键盘事件返回的第一个键码
 *                   int& KeyCode2: 键盘事件返回的第二个键码
 *                   const bool update_lower_status_line: 是否显示鼠标位置信息
 * Return Value:     CCT_MOUSE_EVENT / CCT_KEYBOARD_EVENT / -1 (未调用 gmw_init 前调用其它函数)
 */
int tgmw_read_keyboard_and_mouse(const CONSOLE_GRAPHICS_INFO* const pCGI, int& MAction, int& MRow, int& MCol, int& KeyCode1, int& KeyCode2, const bool update_lower_status_line = true);