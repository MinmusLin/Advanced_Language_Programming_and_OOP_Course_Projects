/****************************************************************
 * Project Name:  common
 * File Name:     cmd_console_tools.cpp
 * File Function: 伪图形界面函数工具集的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/9/24
 ****************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <tchar.h>
#include <string.h>
#include <Windows.h>
#include "..\common\cmd_console_tools.h"
using namespace std;

static const HANDLE __hout = GetStdHandle(STD_OUTPUT_HANDLE); //Get the handle of the standard output device
static const HANDLE __hin = GetStdHandle(STD_INPUT_HANDLE); //Get the handle of the standard input device

/*
 * Function Name:    cct_cls
 * Function:         Call the system's "cls" command to clear the screen
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Clear the entire screen buffer (not just the visible window area) using the current color
 */
void cct_cls(void)
{
    COORD coord = { 0, 0 };
    CONSOLE_SCREEN_BUFFER_INFO binfo;
    DWORD num;
    GetConsoleScreenBufferInfo(__hout, &binfo);
    FillConsoleOutputCharacter(__hout, (TCHAR)' ', binfo.dwSize.X * binfo.dwSize.Y, coord, &num);
    FillConsoleOutputAttribute(__hout, binfo.wAttributes, binfo.dwSize.X * binfo.dwSize.Y, coord, &num);
    SetConsoleCursorPosition(__hout, coord);
}

/*
 * Function Name:    cct_setcolor
 * Function:         Set the specified color
 * Input Parameters: const int bg_color
 *                   const int fg_color
 * Return Value:     void
 */
void cct_setcolor(const int bg_color, const int fg_color)
{
    SetConsoleTextAttribute(__hout, bg_color * 16 + fg_color);
}

/*
 * Function Name:    cct_getcolor
 * Function:         Retrieve the foreground color and background color
 * Input Parameters: int& bg_color
 *                   int& fg_color
 * Return Value:     void
 */
void cct_getcolor(int& bg_color, int& fg_color)
{
    CONSOLE_SCREEN_BUFFER_INFO binfo;
    GetConsoleScreenBufferInfo(__hout, &binfo);
    bg_color = binfo.wAttributes / 16;
    fg_color = binfo.wAttributes % 16;
}

/*
 * Function Name:    cct_gotoxy
 * Function:         Move the cursor to the specified position
 * Input Parameters: const int X
 *                   const int Y
 * Return Value:     void
 */
void cct_gotoxy(const int X, const int Y)
{
    COORD coord;
    coord.X = X;
    coord.Y = Y;
    SetConsoleCursorPosition(__hout, coord);
}

/*
 * Function Name:    cct_getxy
 * Function:         Retrieve the coordinates of the current cursor position
 * Input Parameters: int& x
 *                   int& y
 * Return Value:     void
 */
void cct_getxy(int& x, int& y)
{
    CONSOLE_SCREEN_BUFFER_INFO binfo;
    GetConsoleScreenBufferInfo(__hout, &binfo);
    x = binfo.dwCursorPosition.X;
    y = binfo.dwCursorPosition.Y;
}

/*
 * Function Name:    cct_setcursor
 * Function:         Set the cursor state
 * Input Parameters: const int options
 * Return Value:     void
 */
void cct_setcursor(const int options)
{
    CONSOLE_CURSOR_INFO cursor_info;
    switch (options) {
        case CURSOR_VISIBLE_FULL:
            cursor_info.bVisible = 1;
            cursor_info.dwSize = 100;
            break;
        case CURSOR_VISIBLE_HALF:
            cursor_info.bVisible = 1;
            cursor_info.dwSize = 50;
            break;
        case CURSOR_INVISIBLE:
            cursor_info.bVisible = 0;
            cursor_info.dwSize = 1;
            break;
        case CURSOR_VISIBLE_NORMAL:
        default:
            cursor_info.bVisible = 1;
            cursor_info.dwSize = 25;
            break;
    }
    SetConsoleCursorInfo(__hout, &cursor_info);
}

/*
 * Function Name:    cct_showch
 * Function:         Display a character multiple times at the specified position with the specified color
 * Input Parameters: const int X
 *                   const int Y
 *                   const char ch
 *                   const int bg_color
 *                   const int fg_color
 *                   const int rpt
 * Return Value:     void
 */
void cct_showch(const int X, const int Y, const char ch, const int bg_color, const int fg_color, const int rpt)
{
    cct_gotoxy(X, Y);
    cct_setcolor(bg_color, fg_color);
    for (int i = 0; i < rpt; i++)
        putchar(ch);
}

/*
 * Function Name:    cct_showstr
 * Function:         Display a string multiple times at the specified position with the specified color
 * Input Parameters: const int X
 *                   const int Y
 *                   const char* str
 *                   const int bg_color
 *                   const int fg_color
 *                   const int rpt
 *                   int maxlen
 * Return Value:     void
 */
void cct_showstr(const int X, const int Y, const char* str, const int bg_color, const int fg_color, int rpt, int maxlen)
{
    const char* p;
    int i, rpt_count = 0;
    cct_gotoxy(X, Y);
    cct_setcolor(bg_color, fg_color);
    if (str == NULL || str[0] == 0) {
        for (i = 0; i < maxlen; i++)
            putchar(' ');
        return;
    }
    if (rpt <= 0)
        rpt = 1;
    if (maxlen < 0)
        maxlen = strlen(str) * rpt;
    for (i = 0, p = str; i < maxlen; i++, p++) {
        if (*p == 0) {
            p = str;
            rpt_count++;
        }
        putchar(rpt_count < rpt ? *p : ' ');
    }
}

/*
 * Function Name:    cct_showint
 * Function:         Display an int value multiple times at the specified position with the specified color
 * Input Parameters: const int X
 *                   const int Y
 *                   const int num
 *                   const int bg_color
 *                   const int fg_color
 *                   const int rpt
 * Return Value:     void
 */
void cct_showint(const int X, const int Y, const int num, const int bg_color, const int fg_color, const int rpt)
{
    cct_gotoxy(X, Y);
    cct_setcolor(bg_color, fg_color);
    for (int i = 0; i < rpt; i++)
        cout << num;
}

/*
 * Function Name:    cct_setconsoleborder
 * Function:         Set the size of the CMD window and the size of the buffer
 * Input Parameters: int set_cols
 *                   int set_lines
 *                   int set_buffer_cols
 *                   int set_buffer_lines
 * Return Value:     void
 */
void cct_setconsoleborder(int set_cols, int set_lines, int set_buffer_cols, int set_buffer_lines)
{
    COORD max_coord = GetLargestConsoleWindowSize(__hout);
    if (set_cols <= 0 || set_lines <= 0)
        return;
    if (set_cols > max_coord.X)
        set_cols = max_coord.X;
    if (set_lines > max_coord.Y)
        set_lines = max_coord.Y;
    SMALL_RECT rect;
    rect.Top = 0;
    rect.Bottom = set_lines - 1;
    rect.Left = 0;
    rect.Right = set_cols - 1;
    COORD cr;
    cr.X = (set_buffer_cols == -1 || set_buffer_cols < set_cols) ? set_cols : set_buffer_cols;
    cr.Y = (set_buffer_lines == -1 || set_buffer_lines < set_lines) ? set_lines : set_buffer_lines;
    int cur_cols, cur_lines, cur_buffer_cols, cur_buffer_lines;
    CONSOLE_SCREEN_BUFFER_INFO binfo;
    GetConsoleScreenBufferInfo(__hout, &binfo);
    cur_cols = binfo.srWindow.Right - binfo.srWindow.Left + 1;
    cur_lines = binfo.srWindow.Bottom - binfo.srWindow.Top + 1;
    cur_buffer_cols = binfo.dwSize.X;
    cur_buffer_lines = binfo.dwSize.Y;
    cct_cls();
    if (cr.X <= cur_buffer_cols) {
        if (cr.Y <= cur_buffer_lines) {
            SetConsoleWindowInfo(__hout, true, &rect);
            SetConsoleScreenBufferSize(__hout, cr);
        }
        else {
            COORD tmpcr;
            tmpcr.X = cur_buffer_cols;
            tmpcr.Y = cr.Y;
            SetConsoleScreenBufferSize(__hout, tmpcr);
            SetConsoleWindowInfo(__hout, true, &rect);
            SetConsoleScreenBufferSize(__hout, cr);
        }
    }
    else {
        if (cr.Y >= cur_buffer_lines) {
            SetConsoleScreenBufferSize(__hout, cr);
            SetConsoleWindowInfo(__hout, true, &rect);
        }
        else {
            COORD tmpcr;
            tmpcr.X = cr.X;
            tmpcr.Y = cur_buffer_lines;
            SetConsoleScreenBufferSize(__hout, tmpcr);
            SetConsoleWindowInfo(__hout, true, &rect);
            SetConsoleScreenBufferSize(__hout, cr);
        }
    }
}

/*
 * Function Name:    cct_getconsoleborder
 * Function:         Retrieve the current size of the CMD window and the size of the buffer
 * Input Parameters: int& cols
 *                   int& lines
 *                   int& buffer_cols
 *                   int& buffer_lines
 * Return Value:     void
 */
void cct_getconsoleborder(int& cols, int& lines, int& buffer_cols, int& buffer_lines)
{
    CONSOLE_SCREEN_BUFFER_INFO binfo;
    GetConsoleScreenBufferInfo(__hout, &binfo);
    cols = binfo.srWindow.Right - binfo.srWindow.Left + 1;
    lines = binfo.srWindow.Bottom - binfo.srWindow.Top + 1;
    buffer_cols = binfo.dwSize.X;
    buffer_lines = binfo.dwSize.Y;
}

/*
 * Function Name:    cct_getconsoletitle
 * Function:         Retrieve the title of the current CMD window
 * Input Parameters: char* title: The starting address of the title string
 *                   int maxbuflen: The size of the memory space occupied by the title string
 * Return Value:     void
 */
void cct_getconsoletitle(char* title, int maxbuflen)
{
    GetConsoleTitleA(title, maxbuflen);
}

/*
 * Function Name:    cct_setconsoletitle
 * Function:         Set the title of the current CMD window
 * Input Parameters: const char* title
 * Return Value:     void
 */
void cct_setconsoletitle(const char* title)
{
    SetConsoleTitleA(title);
}

/*
 * Function Name:    cct_enable_mouse
 * Function:         Enable the mouse
 * Input Parameters: void
 * Return Value:     void
 * Notes:            After executing certain CMD window control statements, mouse support may be disabled
 *                   You need to call this function again to re-enable it
 */
void cct_enable_mouse(void)
{
    DWORD Mode;
    GetConsoleMode(__hin, &Mode);
    SetConsoleMode(__hin, Mode | ENABLE_MOUSE_INPUT);
}

/*
 * Function Name:    cct_disable_mouse
 * Function:         Disable the mouse
 * Input Parameters: void
 * Return Value:     void
 */
void cct_disable_mouse(void)
{
    DWORD Mode;
    GetConsoleMode(__hin, &Mode);
    SetConsoleMode(__hin, Mode & (~ENABLE_MOUSE_INPUT));
}

/*
 * Function Name:    cct_read_keyboard_and_mouse
 * Function:         Read mouse and keyboard events
 * Input Parameters: int& MX: The X-coordinate of the mouse position
 *                   int& MY: The Y-coordinate of the mouse position
 *                   int& MAction: Mouse events
 *                   int& keycode1: The first key code returned by the keyboard event
 *                   int& keycode2: The second key code returned by the keyboard event
 * Return Value:     CCT_MOUSE_EVENT
 */
int cct_read_keyboard_and_mouse(int& MX, int& MY, int& MAction, int& keycode1, int& keycode2)
{
    static int MX_old = -1, MY_old = -1, MAction_old = MOUSE_ONLY_MOVED;
    INPUT_RECORD InputRec;
    DWORD res;
    COORD crPos;
    while (1) {
        ReadConsoleInput(__hin, &InputRec, 1, &res);
        if (InputRec.EventType == KEY_EVENT) {
            keycode1 = 0x00;
            keycode2 = 0x00;
            if (InputRec.Event.KeyEvent.bKeyDown) {
                switch (InputRec.Event.KeyEvent.wVirtualKeyCode) {
                    case VK_UP:
                        keycode1 = 0xe0;
                        keycode2 = KB_ARROW_UP;
                        break;
                    case VK_DOWN:
                        keycode1 = 0xe0;
                        keycode2 = KB_ARROW_DOWN;
                        break;
                    case VK_LEFT:
                        keycode1 = 0xe0;
                        keycode2 = KB_ARROW_LEFT;
                        break;
                    case VK_RIGHT:
                        keycode1 = 0xe0;
                        keycode2 = KB_ARROW_RIGHT;
                        break;
                    default:
                        break;
                }
                if (keycode1 == 0)
                    keycode1 = InputRec.Event.KeyEvent.uChar.AsciiChar;
                return CCT_KEYBOARD_EVENT;
            }
        }
        if (InputRec.EventType == MOUSE_EVENT) {
            crPos = InputRec.Event.MouseEvent.dwMousePosition;
            MX = crPos.X;
            MY = crPos.Y;
            if (InputRec.Event.MouseEvent.dwEventFlags == MOUSE_MOVED) {
                if (MX_old == MX && MY_old == MY && MAction_old == MOUSE_ONLY_MOVED)
                    continue;
                MX_old = MX;
                MY_old = MY;
                MAction = MOUSE_ONLY_MOVED;
                MAction_old = MAction;
                return CCT_MOUSE_EVENT;
            }
            MAction_old = MOUSE_NO_ACTION;
            if (InputRec.Event.MouseEvent.dwEventFlags == MOUSE_WHEELED) {
                if (InputRec.Event.MouseEvent.dwButtonState & 0x80000000)
                    MAction = MOUSE_WHEEL_MOVED_DOWN;
                else
                    MAction = MOUSE_WHEEL_MOVED_UP;
                return CCT_MOUSE_EVENT;
            }
            if (InputRec.Event.MouseEvent.dwButtonState == (FROM_LEFT_1ST_BUTTON_PRESSED | RIGHTMOST_BUTTON_PRESSED)) {
                MAction = MOUSE_LEFTRIGHT_BUTTON_CLICK;
                return CCT_MOUSE_EVENT;
            }
            else if (InputRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
                if (InputRec.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK)
                    MAction = MOUSE_LEFT_BUTTON_DOUBLE_CLICK;
                else
                    MAction = MOUSE_LEFT_BUTTON_CLICK;
                return CCT_MOUSE_EVENT;
            }
            else if (InputRec.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED) {
                if (InputRec.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK)
                    MAction = MOUSE_RIGHT_BUTTON_DOUBLE_CLICK;
                else
                    MAction = MOUSE_RIGHT_BUTTON_CLICK;
                return CCT_MOUSE_EVENT;
            }
            else if (InputRec.Event.MouseEvent.dwButtonState == FROM_LEFT_2ND_BUTTON_PRESSED) {
                MAction = MOUSE_WHEEL_CLICK;
                return CCT_MOUSE_EVENT;
            }
            else
                continue;
        }
    }
    return CCT_MOUSE_EVENT;
}

typedef BOOL(WINAPI* PROCSETCONSOLEFONT)(HANDLE, DWORD);
typedef BOOL(WINAPI* PROCGETCONSOLEFONTINFO)(HANDLE, BOOL, DWORD, PCONSOLE_FONT_INFO);
typedef COORD(WINAPI* PROCGETCONSOLEFONTSIZE)(HANDLE, DWORD);
typedef DWORD(WINAPI* PROCGETNUMBEROFCONSOLEFONTS)();
typedef BOOL(WINAPI* PROCGETCURRENTCONSOLEFONT)(HANDLE, BOOL, PCONSOLE_FONT_INFO);
typedef BOOL(WINAPI* PROCSetBufferSize)(HANDLE hConsoleOutput, COORD dwSize);
typedef HWND(WINAPI* PROCGETCONSOLEWINDOW)();

#if 0
PROCSETCONSOLEFONT SetConsoleFont;
PROCGETCONSOLEFONTINFO GetConsoleFontInfo;
PROCGETCONSOLEFONTSIZE GetConsoleFontSize;
PROCGETNUMBEROFCONSOLEFONTS GetNumberOfConsoleFonts;
PROCGETCURRENTCONSOLEFONT GetCurrentConsoleFont;
#endif

/*
 * Function Name:    cct_getfontinfo
 * Function:         Retrieve the font information of the output window
 * Input Parameters: void
 * Return Value:     -1 / 0
 */
int cct_getfontinfo(void)
{
    HMODULE hKernel32 = GetModuleHandleA("kernel32");
    if (hKernel32 == 0)
        return -1;
    PROCSETCONSOLEFONT SetConsoleFont = (PROCSETCONSOLEFONT)GetProcAddress(hKernel32, "SetConsoleFont");
    PROCGETCONSOLEFONTINFO GetConsoleFontInfo = (PROCGETCONSOLEFONTINFO)GetProcAddress(hKernel32, "GetConsoleFontInfo");
    PROCGETCONSOLEFONTSIZE GetConsoleFontSize = (PROCGETCONSOLEFONTSIZE)GetProcAddress(hKernel32, "GetConsoleFontSize");
    PROCGETNUMBEROFCONSOLEFONTS GetNumberOfConsoleFonts = (PROCGETNUMBEROFCONSOLEFONTS)GetProcAddress(hKernel32, "GetNumberOfConsoleFonts");
    PROCGETCURRENTCONSOLEFONT GetCurrentConsoleFont = (PROCGETCURRENTCONSOLEFONT)GetProcAddress(hKernel32, "GetCurrentConsoleFont");
    CONSOLE_FONT_INFOEX infoex;
    char fontname[64];
    CONSOLE_FONT_INFO cur_f;
    int nFontNum;
    infoex.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(__hout, 1, &infoex);
    WideCharToMultiByte(CP_ACP, 0, infoex.FaceName, -1, fontname, sizeof(fontname), NULL, NULL);
    cout << "Font Name: " << fontname << endl;
    nFontNum = GetNumberOfConsoleFonts();
    cout << "Font Size: " << nFontNum << endl;
    GetCurrentConsoleFont(__hout, 0, &cur_f);
    cout << "Font Index: " << cur_f.nFont << endl;
    cout << "Width: " << cur_f.dwFontSize.X << "pixels" << endl;
    cout << "Height: " << cur_f.dwFontSize.Y << "pixels" << endl;
    return 0;
}

/*
 * Function Name:    cct_setconsolefont
 * Function:         Set the font size of the output window
 * Input Parameters: const int font_no
 * Return Value:     void
 * Notes:            font_no  width  high
 *                      0       3     5
 *                      1       4     6
 *                      2       5     8
 *                      3       6     8
 *                      4       8     8
 *                      5       16    8
 *                      6       5     12
 *                      7       6     12
 *                      8       7     12
 *                      9       8     12
 *                      10      16    12
 *                      11      8     16
 *                      12      12    16
 *                      13      8     18
 *                      14      10    18
 *                      15      10    20
 */
void cct_setconsolefont(const int font_no)
{
    HMODULE hKernel32 = GetModuleHandleA("kernel32");
    if (hKernel32 == 0)
        return;
    PROCSETCONSOLEFONT SetConsoleFont = (PROCSETCONSOLEFONT)GetProcAddress(hKernel32, "SetConsoleFont");
    SetConsoleFont(__hout, font_no);
}

/*
 * Function Name:    cct_setfontsize
 * Function:         Set the font and size of the output window
 * Input Parameters: const char* fontname
 *                   const int high
 *                   const int width
 * Return Value:     void
 * Notes:            The GBK-encoded CMD window supports only "Terminal" and "NSimSun" font
 *                   If a fontname other than "NSimSun" is given, consider it as the default font "Terminal"
 *                   For TrueType fonts, you only need to set the height parameter
 *                   Usage example:
 *                       cct_setfontsize("新宋体", 16);
 *                       cct_setfontsize("Terminal", 16, 8);
 */
void cct_setfontsize(const char* fontname, const int high, const int width)
{
    CONSOLE_FONT_INFOEX infoex = { 0 };
    infoex.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    infoex.dwFontSize.X = width;
    infoex.dwFontSize.Y = high;
    infoex.FontWeight = FW_NORMAL;
    MultiByteToWideChar(CP_ACP, 0, fontname, -1, infoex.FaceName, LF_FACESIZE);
    SetCurrentConsoleFontEx(__hout, NULL, &infoex);
}