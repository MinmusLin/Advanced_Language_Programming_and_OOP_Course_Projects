/****************************************************************
 * Project Name:  common
 * File Name:     lib_gmw_tools.h
 * File Function: ��������Ϸͨ�ú������߼���ͷ�ļ�
 * Author:        Jishen Lin (�ּ���)
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
    char top_left[CFI_LEN]; // "�X"
    char lower_left[CFI_LEN]; // "�^"
    char top_right[CFI_LEN]; // "�["
    char lower_right[CFI_LEN]; // "�a"
    char h_normal[CFI_LEN]; // "�T"
    char v_normal[CFI_LEN]; // "�U"
    char h_top_separator[CFI_LEN]; // "�h"
    char h_lower_separator[CFI_LEN]; // "�k"
    char v_left_separator[CFI_LEN]; // "�c"
    char v_right_separator[CFI_LEN]; // "�f"
    char mid_separator[CFI_LEN]; // "��"

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
    char top_left[CBI_LEN]; // "�X"
    char lower_left[CBI_LEN]; // "�^"
    char top_right[CBI_LEN]; // "�["
    char lower_right[CBI_LEN]; // "�a"
    char h_normal[CBI_LEN]; // "�T"
    char v_normal[CBI_LEN]; // "�U"

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
        {BDI_VALUE_BLANK,-1,-1,NULL}, // ���ΪBDI_VALUE_BLANK������ʾ����
        {1,COLOR_HYELLOW,COLOR_HRED,"��"}, // �����ά�����е�ֵΪ1������ʾ��
        {2,COLOR_HYELLOW,COLOR_HRED,-1,NULL}, // NULL��ʾֱ����ʾ��ά�����е�ֵ2
        {BDI_VALUE_END,-1,-1,NULL} // ���ΪBDI_VALUE_END�������
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
 * Function:         ��һ��ɫ��
 * Input Parameters: const CONSOLE_GRAPHICS_INFO* const pCGI: ����ṹָ��
 *                   const int row_no: �к�
 *                   const int col_no: �к�
 *                   const int bdi_value: ��Ҫ��ʾ��ֵ
 *                   const BLOCK_DISPLAY_INFO* const bdi: ��Ÿ�ֵ��Ӧ����ʾ��Ϣ�Ľṹ������
 * Return Value:     0 / -1 (δ���� gmw_init ǰ������������)
 * Notes:            pCGI->CBI.block_border == false ʱ��ʵ��
 */
int gmw_draw_block(const CONSOLE_GRAPHICS_INFO* const pCGI, const int row_no, const int col_no, const int bdi_value, const BLOCK_DISPLAY_INFO* const bdi);

/* Function declarations in lib_gmw_tools.lib */

/*
 * Function Name:    tgmw_set_rowcol
 * Function:         ������Ϸ����ܵ�������
 * Input Parameters: CONSOLE_GRAPHICS_INFO* const pCGI
 *                   const int row
 *                   const int col
 * Return Value:     0 / -1 (δ���� gmw_init ǰ������������)
 * Notes:            ������ָ��������Ϸ�ľ������������ֵ
 */
int tgmw_set_rowcol(CONSOLE_GRAPHICS_INFO* const pCGI, const int row, const int col);

/*
 * Function Name:    tgmw_set_color
 * Function:         ��������cmd���ڵ���ɫ
 * Input Parameters: CONSOLE_GRAPHICS_INFO* const pCGI
 *                   const int bgcolor
 *                   const int fgcolor
 *                   const bool cascade
 * Return Value:     0 / -1 (δ���� gmw_init ǰ������������)
 * Notes:            cascade == true ʱͬ���޸���Ϸ��������ɫ������״̬���ı���ɫ
 */
int tgmw_set_color(CONSOLE_GRAPHICS_INFO* const pCGI, const int bgcolor = COLOR_BLACK, const int fgcolor = COLOR_WHITE, const bool cascade = true);

/*
 * Function Name:    tgmw_set_font
 * Function:         ���ô��ڵ�����
 * Input Parameters: CONSOLE_GRAPHICS_INFO* const pCGI
 *                   const char* fontname
 *                   const int fs_high
 *                   const int fs_width
 * Return Value:     0 / -1 (δ���� gmw_init ǰ������������)
 * Notes:            ��֧��"��������"("Terminal")��"������"
 */
int tgmw_set_font(CONSOLE_GRAPHICS_INFO* const pCGI, const char* fontname = "Terminal", const int fs_high = 16, const int fs_width = 8);

/*
 * Function Name:    tgmw_set_delay
 * Function:         ������ʱʱ��
 * Input Parameters: CONSOLE_GRAPHICS_INFO* const pCGI
 *                   const int type
 *                   const int delay_ms
 * Return Value:     0 / -1 (δ���� gmw_init ǰ������������)
 */
int tgmw_set_delay(CONSOLE_GRAPHICS_INFO* const pCGI, const int type, const int delay_ms);

/*
 * Function Name:    tgmw_set_ext_rowcol
 * Function:         ������Ϸ����ܽṹ֮����Ҫ�����Ķ�������
 * Input Parameters: CONSOLE_GRAPHICS_INFO* const pCGI
 *                   const int up_lines
 *                   const int down_lines
 *                   const int left_cols
 *                   const int right_cols
 * Return Value:     0 / -1 (δ���� gmw_init ǰ������������)
 */
int tgmw_set_ext_rowcol(CONSOLE_GRAPHICS_INFO* const pCGI, const int up_lines = 0, const int down_lines = 0, const int left_cols = 0, const int right_cols = 0);

/*
 * Function Name:    tgmw_set_frame_default_linetype
 * Function:         ��� CONSOLE_FRAME_TYPE �ṹ���е�11������(ȱʡ4��)
 * Input Parameters: CONSOLE_GRAPHICS_INFO* const pCGI
 *                   const int type : 1 - ȫ˫��
 *                                    2 - ȫ����
 *                                    3 - ��˫������
 *                                    4 - �ᵥ��˫��
 * Return Value:     0 / -1 (δ���� gmw_init ǰ������������)
 */
int tgmw_set_frame_default_linetype(CONSOLE_GRAPHICS_INFO* const pCGI, const int type);

/*
 * Function Name:    tgmw_set_frame_linetype
 * Function:         ��� CONSOLE_FRAME_TYPE �ṹ���е�11������
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
 * Return Value:     0 / -1 (δ���� gmw_init ǰ������������)
 * Notes:            ���2�ֽ��ַ�������2�ֽ�ֻȡǰ2�ֽڣ����1�ֽ��ַ���1���ո����NULL��2���ո�
 */
int tgmw_set_frame_linetype(CONSOLE_GRAPHICS_INFO* const pCGI, const char* top_left = "�X", const char* lower_left = "�^", const char* top_right = "�[", const char* lower_right = "�a", const char* h_normal = "�T", const char* v_normal = "�U", const char* h_top_separator = "�j", const char* h_lower_separator = "�m", const char* v_left_separator = "�d", const char* v_right_separator = "�g", const char* mid_separator = "�p");

/*
 * Function Name:    tgmw_set_frame_style
 * Function:         ��� CONSOLE_FRAME_TYPE �ṹ���е�ɫ���С���Ƿ���Ҫ�ָ���
 * Input Parameters: CONSOLE_GRAPHICS_INFO* const pCGI
 *                   const int block_width
 *                   const int block_high
 *                   const bool separator
 * Return Value:     0 / -1 (δ���� gmw_init ǰ������������)
 */
int tgmw_set_frame_style(CONSOLE_GRAPHICS_INFO* const pCGI, const int block_width = 2, const int block_high = 1, const bool separator = true);

/*
 * Function Name:    tgmw_set_frame_color
 * Function:         ��� CONSOLE_BORDER_TYPE �ṹ���е���ɫ
 * Input Parameters: CONSOLE_GRAPHICS_INFO* const pCGI
 *                   const int bgcolor
 *                   const int fgcolor
 * Return Value:     0 / -1 (δ���� gmw_init ǰ������������)
 */
int tgmw_set_frame_color(CONSOLE_GRAPHICS_INFO* const pCGI, const int bgcolor = -1, const int fgcolor = -1);

/*
 * Function Name:    tgmw_set_block_default_linetype
 * Function:         ��� CONSOLE_BLOCK_INFO �ṹ���е�6������(ȱʡ4��)
 * Input Parameters: CONSOLE_GRAPHICS_INFO* const pCGI
 *                   const int def_type : 1 - ȫ˫��
 *                                        2 - ȫ����
 *                                        3 - ��˫������
 *                                        4 - �ᵥ��˫��
 * Return Value:     0 / -1 (δ���� gmw_init ǰ������������)
 */
int tgmw_set_block_default_linetype(CONSOLE_GRAPHICS_INFO* const pCGI, const int def_type);

/*
 * Function Name:    tgmw_set_block_linetype
 * Function:         ��� CONSOLE_BLOCK_INFO �ṹ���е�6������
 * Input Parameters: CONSOLE_GRAPHICS_INFO* const pCGI
 *                   const char* top_left
 *                   const char* lower_left
 *                   const char* top_right
 *                   const char* lower_right
 *                   const char* h_normal
 *                   const char* v_normal
 * Return Value:     0 / -1 (δ���� gmw_init ǰ������������)
 * Notes:            ���2�ֽ��ַ�������2�ֽ�ֻȡǰ2�ֽڣ����1�ֽ��ַ���1���ո����NULL��2���ո�
 */
int tgmw_set_block_linetype(CONSOLE_GRAPHICS_INFO* const pCGI, const char* top_left = "�X", const char* lower_left = "�^", const char* top_right = "�[", const char* lower_right = "�a", const char* h_normal = "�T", const char* v_normal = "�U");

/*
 * Function Name:    tgmw_set_block_border_switch
 * Function:         ����ÿ����Ϸɫ��(����)�Ƿ���Ҫ�߿�
 * Input Parameters: CONSOLE_GRAPHICS_INFO* const pCGI
 *                   const bool on_off
 * Return Value:     0 / -1 (δ���� gmw_init ǰ������������)
 */
int tgmw_set_block_border_switch(CONSOLE_GRAPHICS_INFO* const pCGI, const bool on_off = false);

/*
 * Function Name:    tgmw_set_status_line_switch
 * Function:         �����Ƿ���ʾ����״̬��
 * Input Parameters: CONSOLE_GRAPHICS_INFO* const pCGI
 *                   const int type
 *                   const bool on_off
 * Return Value:     0 / -1 (δ���� gmw_init ǰ������������)
 * Notes:            ��״̬����һ�У������������Ϸ�����/�б����һ�У�Ϊ������ĵ�һ��
 *                   ��״̬����һ�У������������·����ߵ���һ��
 *                   ״̬�����Ϊ�������ȣ���״̬����ʾ��Ϣ������ض�
 */
int tgmw_set_status_line_switch(CONSOLE_GRAPHICS_INFO* const pCGI, const int type, const bool on_off = true);

/*
 * Function Name:    tgmw_set_status_line_color
 * Function:         ��������״̬������ɫ
 * Input Parameters: CONSOLE_GRAPHICS_INFO* const pCGI
 *                   const int type
 *                   const int normal_bgcolor
 *                   const int normal_fgcolor
 *                   const int catchy_bgcolor
 *                   const int catchy_fgcolor
 * Return Value:     0 / -1 (δ���� gmw_init ǰ������������)
 */
int tgmw_set_status_line_color(CONSOLE_GRAPHICS_INFO* const pCGI, const int type, const int normal_bgcolor = -1, const int normal_fgcolor = -1, const int catchy_bgcolor = -1, const int catchy_fgcolor = -1);

/*
 * Function Name:    tgmw_set_rowno_switch
 * Function:         �����Ƿ���ʾ�б�
 * Input Parameters: CONSOLE_GRAPHICS_INFO* const pCGI
 *                   const bool on_off
 * Return Value:     0 / -1 (δ���� gmw_init ǰ������������)
 */
int tgmw_set_rowno_switch(CONSOLE_GRAPHICS_INFO* const pCGI, const bool on_off = false);

/*
 * Function Name:    tgmw_set_colno_switch
 * Function:         �����Ƿ���ʾ�б�
 * Input Parameters: CONSOLE_GRAPHICS_INFO* const pCGI
 *                   const bool on_off
 * Return Value:     0 / -1 (δ���� gmw_init ǰ������������)
 */
int tgmw_set_colno_switch(CONSOLE_GRAPHICS_INFO* const pCGI, const bool on_off = false);

/*
 * Function Name:    tgmw_init
 * Function:         �� CONSOLE_GRAPHICS_INFO �ṹ����ȱʡֵ���г�ʼ��
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
 * Function:         ��ӡ CONSOLE_GRAPHICS_INFO �ṹ���еĸ���Աֵ
 * Input Parameters: const CONSOLE_GRAPHICS_INFO* const pCGI
 * Return Value:     0 / -1 (δ���� gmw_init ǰ������������)
 */
int tgmw_print(const CONSOLE_GRAPHICS_INFO* const pCGI);

/*
 * Function Name:    tgmw_draw_frame
 * Function:         ����Ϸ�����
 * Input Parameters: const CONSOLE_GRAPHICS_INFO* const pCGI
 * Return Value:     0 / -1 (δ���� gmw_init ǰ������������)
 */
int tgmw_draw_frame(const CONSOLE_GRAPHICS_INFO* const pCGI);

/*
 * Function Name:    tgmw_status_line
 * Function:         ��ʾ״̬����Ϣ
 * Input Parameters: const CONSOLE_GRAPHICS_INFO* const pCGI: ����ṹָ��
 *                   const int type: ��/��״̬��
 *                   const char* msg: ������Ϣ
 *                   const char* catchy_msg: ��Ŀ��Ϣ
 * Return Value:     0 / -1 (δ���� gmw_init ǰ������������)
 * Notes:            �������ȳ�������ܿ��(���к��б�λ��)���ȥ
 */
int tgmw_status_line(const CONSOLE_GRAPHICS_INFO* const pCGI, const int type, const char* msg, const char* catchy_msg = NULL);

/*
 * Function Name:    tgmw_draw_block
 * Function:         ��һ��ɫ��
 * Input Parameters: const CONSOLE_GRAPHICS_INFO* const pCGI: ����ṹָ��
 *                   const int row_no: �к�
 *                   const int col_no: �к�
 *                   const int bdi_value: ��Ҫ��ʾ��ֵ
 *                   const BLOCK_DISPLAY_INFO* const bdi: ��Ÿ�ֵ��Ӧ����ʾ��Ϣ�Ľṹ������
 * Return Value:     0 / -1 (δ���� gmw_init ǰ������������)
 * Notes:            pCGI->CBI.block_border == true ʱ��ʵ��
 */
int tgmw_draw_block(const CONSOLE_GRAPHICS_INFO* const pCGI, const int row_no, const int col_no, const int bdi_value, const BLOCK_DISPLAY_INFO* const bdi);

/*
 * Function Name:    tgmw_move_block
 * Function:         �ƶ�һ��ɫ��
 * Input Parameters: const CONSOLE_GRAPHICS_INFO* const pCGI: ����ṹָ��
 *                   const int row_no: �к�
 *                   const int col_no: �к�
 *                   const int bdi_value: ��Ҫ��ʾ��ֵ
 *                   const int blank_bdi_value: �ƶ����������ڶ���Ч����ʾʱ���ڱ�ʾ�հ׵�ֵ
 *                   const BLOCK_DISPLAY_INFO* const bdi: �����ʾֵ/�հ�ֵ��Ӧ����ʾ��Ϣ�Ľṹ��������
 *                   const int direction: �ƶ�����
 *                   const int distance: �ƶ�����
 * Return Value:     0 / -1 (δ���� gmw_init ǰ������������)
 */
int tgmw_move_block(const CONSOLE_GRAPHICS_INFO* const pCGI, const int row_no, const int col_no, const int bdi_value, const int blank_bdi_value, const BLOCK_DISPLAY_INFO* const bdi, const int direction, const int distance);

/*
 * Function Name:    tgmw_read_keyboard_and_mouse
 * Function:         �����̺�����¼�
 * Input Parameters: const CONSOLE_GRAPHICS_INFO* const pCGI: ����ṹָ��
 *                   int& MAction: ����¼�
 *                   int& MRow: �����������
 *                   int& MCol: �����������
 *                   int& KeyCode1: �����¼����صĵ�һ������
 *                   int& KeyCode2: �����¼����صĵڶ�������
 *                   const bool update_lower_status_line: �Ƿ���ʾ���λ����Ϣ
 * Return Value:     CCT_MOUSE_EVENT / CCT_KEYBOARD_EVENT / -1 (δ���� gmw_init ǰ������������)
 */
int tgmw_read_keyboard_and_mouse(const CONSOLE_GRAPHICS_INFO* const pCGI, int& MAction, int& MRow, int& MCol, int& KeyCode1, int& KeyCode2, const bool update_lower_status_line = true);