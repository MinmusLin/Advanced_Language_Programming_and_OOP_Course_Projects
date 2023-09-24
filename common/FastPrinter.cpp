/****************************************************************
 * Project Name:  common
 * File Name:     FastPrinter.cpp
 * File Function: 底层控制台绘制函数工具集的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/9/24
 ****************************************************************/

#include <iostream>
#include "../common/FastPrinter.h"
using namespace std;

/*
 * Function Name:    initDrawer
 * Function:         Initialize drawer
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void FastPrinter::initDrawer(void)
{
    /* Init the data buffer */
    dataGrid = new(nothrow) char[sizeX * sizeY];
    if (dataGrid == NULL)
        exit(-1);
    frontColorGrid = new(nothrow) BYTE[sizeX * sizeY * 3];
    if (frontColorGrid == NULL)
        exit(-1);
    backColorGrid = new(nothrow) BYTE[sizeX * sizeY * 3];
    if (backColorGrid == NULL)
        exit(-1);
    cleanSrceen();
    outputSequence = new(nothrow) char[sizeX * sizeY * 128];
    if (outputSequence == NULL)
        exit(-1);
    sequenceCapacity = sizeX * sizeY * 128;

    /* Get font size */
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

    /* Load the external WinAPI module */
    typedef HWND(WINAPI* PROCGETCONSOLEWINDOW)();
    PROCGETCONSOLEWINDOW GetConsoleWindow;
    HMODULE hKernel32 = GetModuleHandleA("kernel32");
    GetConsoleWindow = (PROCGETCONSOLEWINDOW)GetProcAddress(hKernel32, "GetConsoleWindow");

    /* Get console window handle and move the window to the upper left */
    HWND hwnd = GetConsoleWindow();
    SetWindowPos(hwnd, HWND_TOP, 0, 0, cfi.dwFontSize.X * sizeX, cfi.dwFontSize.Y * sizeY, 0);

    /* Renew the code page */
    system("chcp 936");

    /* Resize the window */
    char cmd_buffer[32] = "mode con: cols=0000 lines=0000";
    cmd_buffer[15] = '0' + (sizeX / 1000 % 10);
    cmd_buffer[16] = '0' + (sizeX / 100 % 10);
    cmd_buffer[17] = '0' + (sizeX / 10 % 10);
    cmd_buffer[18] = '0' + sizeX % 10;
    cmd_buffer[26] = '0' + (sizeY / 1000 % 10);
    cmd_buffer[27] = '0' + (sizeY / 100 % 10);
    cmd_buffer[28] = '0' + (sizeY / 10 % 10);
    cmd_buffer[29] = '0' + sizeY % 10;
    system(cmd_buffer);

    /* Invisible the cursor */
    hOutput = CreateConsoleScreenBuffer(GENERIC_WRITE | GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    CONSOLE_CURSOR_INFO cci;
    cci.bVisible = 0;
    cci.dwSize = 1;
    SetConsoleCursorInfo(hOutput, &cci);

    /* Enable the console virtual terminal sequences */
    DWORD dwMode = 0;
    GetConsoleMode(hOutput, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOutput, dwMode);
    SetConsoleActiveScreenBuffer(hOutput);
}

/*
 * Function Name:    _setFontSize
 * Function:         Set font size
 * Input Parameters: const WORD x
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void FastPrinter::_setFontSize(const WORD x)
{
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    cfi.dwFontSize.X = 0;
    cfi.dwFontSize.Y = x;
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

/*
 * Function Name:    _destroy
 * Function:         Clean up memory
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void FastPrinter::_destroy(void)
{
    delete[] dataGrid;
    delete[] frontColorGrid;
    delete[] backColorGrid;
    delete[] outputSequence;
    CloseHandle(hOutput);
}

/*
 * Function Name:    _draw
 * Function:         Flush the whole screen without color
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void FastPrinter::_draw(void)
{
    COORD coordBufCoord = { 0 };
    DWORD dWrite = 0;
    for (DWORD i = 0; i < sizeY; i++) {
        coordBufCoord.Y = (SHORT)i;
        WriteConsoleOutputCharacterA(hOutput, dataGrid + (i * sizeX), sizeX, coordBufCoord, &dWrite);
    }
    SetConsoleActiveScreenBuffer(hOutput);
}

/*
 * Function Name:    _drawC
 * Function:         Flush the whole screen with color
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void FastPrinter::_drawC(void)
{
    sequenceLength = 0;
    BYTE oldColor[8];
    memset(oldColor, rand(), 8);
    for (size_t i = 0; i < sizeY; i++) {
        char posSequence[16] = "\x1b[001;001H";
        posSequence[2 + 2] = '0' + (i + 1) % 10;
        posSequence[2 + 1] = '0' + (i + 1) / 10 % 10;
        posSequence[2] = '0' + (char)(i + 1) / 100;
        memcpy(outputSequence + sequenceLength, posSequence, 10);
        sequenceLength += 10;
        for (size_t j = 0; j < sizeX; j++) {
            const size_t dataIndex = i * sizeX + j;
            const size_t colorIndex = dataIndex * 3;
            int cmp1 = memcmp(oldColor, frontColorGrid + colorIndex, 3);
            int cmp2 = memcmp(oldColor + 3, backColorGrid + colorIndex, 3);
            if (cmp1 != 0) {
                char sequence[] = "\x1b[38;2;000;000;000m";
                sequence[9] = '0' + frontColorGrid[colorIndex] % 10;
                sequence[8] = '0' + frontColorGrid[colorIndex] / 10 % 10;
                sequence[7] = '0' + frontColorGrid[colorIndex] / 100;
                sequence[13] = '0' + frontColorGrid[colorIndex + 1] % 10;
                sequence[12] = '0' + frontColorGrid[colorIndex + 1] / 10 % 10;
                sequence[11] = '0' + frontColorGrid[colorIndex + 1] / 100;
                sequence[17] = '0' + frontColorGrid[colorIndex + 2] % 10;
                sequence[16] = '0' + frontColorGrid[colorIndex + 2] / 10 % 10;
                sequence[15] = '0' + frontColorGrid[colorIndex + 2] / 100;
                memcpy(outputSequence + sequenceLength, sequence, 19);
                sequenceLength += 19;
                memcpy(oldColor, frontColorGrid + colorIndex, 3);
            }
            if (cmp2 != 0) {
                char sequence[] = "\x1b[48;2;000;000;000m";
                sequence[9] = '0' + backColorGrid[colorIndex] % 10;
                sequence[8] = '0' + backColorGrid[colorIndex] / 10 % 10;
                sequence[7] = '0' + backColorGrid[colorIndex] / 100;
                sequence[13] = '0' + backColorGrid[colorIndex + 1] % 10;
                sequence[12] = '0' + backColorGrid[colorIndex + 1] / 10 % 10;
                sequence[11] = '0' + backColorGrid[colorIndex + 1] / 100;
                sequence[17] = '0' + backColorGrid[colorIndex + 2] % 10;
                sequence[16] = '0' + backColorGrid[colorIndex + 2] / 10 % 10;
                sequence[15] = '0' + backColorGrid[colorIndex + 2] / 100;
                memcpy(outputSequence + sequenceLength, sequence, 19);
                sequenceLength += 19;
                memcpy(oldColor + 3, backColorGrid + colorIndex, 3);
            }
            outputSequence[sequenceLength] = dataGrid[dataIndex];
            if (outputSequence[sequenceLength] == '\0')
                outputSequence[sequenceLength] = ' ';
            sequenceLength++;
        }
    }
    outputSequence[sequenceLength] = '\0';
    DWORD dWrite = 0;
    WriteConsoleA(hOutput, outputSequence, sequenceLength, &dWrite, NULL);
}

/*
 * Function Name:    FastPrinter
 * Function:         Constructed function
 * Input Parameters: size_t x
 *                   size_t y
 * Notes:            Class external implementation of member functions
 */
FastPrinter::FastPrinter(size_t x, size_t y) :sizeX(x), sizeY(y)
{
    initDrawer();
}

/*
 * Function Name:    FastPrinter
 * Function:         Constructed function
 * Input Parameters: size_t x
 *                   size_t y
 *                   WORD fontSize
 * Notes:            Class external implementation of member functions
 */
FastPrinter::FastPrinter(size_t x, size_t y, WORD fontSize) : sizeX(x), sizeY(y)
{
    _setFontSize(fontSize);
    initDrawer();
}

/*
 * Function Name:    ~FastPrinter
 * Function:         Destructor
 * Notes:            Class external implementation of member functions
 */
FastPrinter::~FastPrinter()
{
    _destroy();
}

/*
 * Function Name:    setData
 * Function:         Copy the data to inner buffer
 * Input Parameters: const char* _in_data
 *                   const BYTE* _in_front_color
 *                   const BYTE* _in_back_color
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void FastPrinter::setData(const char* _in_data, const BYTE* _in_front_color, const BYTE* _in_back_color)
{
    memcpy(dataGrid, _in_data, sizeX * sizeY);
    memcpy(frontColorGrid, _in_front_color, sizeX * sizeY * 3);
    memcpy(backColorGrid, _in_back_color, sizeX * sizeY * 3);
}

/*
 * Function Name:    setData
 * Function:         Copy the data to the specified area
 * Input Parameters: const char* _in_data
 *                   const BYTE* _in_front_color
 *                   const BYTE* _in_back_color
 *                   SMALL_RECT _area
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void FastPrinter::setData(const char* _in_data, const BYTE* _in_front_color, const BYTE* _in_back_color, SMALL_RECT _area)
{
    SHORT row = (_area.Right - _area.Left);
    for (WORD _i = _area.Top, i = 0; _i < _area.Bottom; _i++, i++) {
        const size_t dataIndex = _i * sizeX + _area.Left;
        const size_t inDataIndex = i * row;
        const size_t colorIndex = dataIndex * 3;
        const size_t inColorIndex = inDataIndex * 3;
        memcpy(dataGrid + dataIndex, _in_data + inDataIndex, row);
        memcpy(frontColorGrid + colorIndex, _in_front_color + inColorIndex, row * 3);
        memcpy(backColorGrid + colorIndex, _in_back_color + inColorIndex, row * 3);
    }
}

/*
 * Function Name:    setRect
 * Function:         Draw a hollow rectangle
 * Input Parameters: SMALL_RECT _area
 *                   const char _val
 *                   const BYTE textR
 *                   const BYTE textG
 *                   const BYTE textB
 *                   const BYTE backR
 *                   const BYTE backG
 *                   const BYTE backB
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void FastPrinter::setRect(SMALL_RECT _area, const char _val, const BYTE textR, const BYTE textG, const BYTE textB, const BYTE backR, const BYTE backG, const BYTE backB)
{
    for (WORD i = _area.Left; i < _area.Right; i++) {
        size_t dataIndex = _area.Top * sizeX + i;
        size_t colorIndex = dataIndex * 3;
        dataGrid[dataIndex] = _val;
        frontColorGrid[colorIndex] = textR;
        frontColorGrid[colorIndex + 1] = textG;
        frontColorGrid[colorIndex + 2] = textB;
        backColorGrid[colorIndex] = backR;
        backColorGrid[colorIndex + 1] = backG;
        backColorGrid[colorIndex + 2] = backB;
        dataIndex = (_area.Bottom - 1) * sizeX + i;
        colorIndex = dataIndex * 3;
        dataGrid[dataIndex] = _val;
        frontColorGrid[colorIndex] = textR;
        frontColorGrid[colorIndex + 1] = textG;
        frontColorGrid[colorIndex + 2] = textB;
        backColorGrid[colorIndex] = backR;
        backColorGrid[colorIndex + 1] = backG;
        backColorGrid[colorIndex + 2] = backB;
    }
    for (WORD i = _area.Top; i < _area.Bottom; i++) {
        size_t dataIndex = i * sizeX + _area.Left;
        size_t colorIndex = dataIndex * 3;
        dataGrid[dataIndex] = _val;
        frontColorGrid[colorIndex] = textR;
        frontColorGrid[colorIndex + 1] = textG;
        frontColorGrid[colorIndex + 2] = textB;
        backColorGrid[colorIndex] = backR;
        backColorGrid[colorIndex + 1] = backG;
        backColorGrid[colorIndex + 2] = backB;
        dataIndex = i * sizeX + _area.Right - 1;
        colorIndex = dataIndex * 3;
        dataGrid[dataIndex] = _val;
        frontColorGrid[colorIndex] = textR;
        frontColorGrid[colorIndex + 1] = textG;
        frontColorGrid[colorIndex + 2] = textB;
        backColorGrid[colorIndex] = backR;
        backColorGrid[colorIndex + 1] = backG;
        backColorGrid[colorIndex + 2] = backB;
    }
}

/*
 * Function Name:    fillRect
 * Function:         Draw a solid rectangle
 * Input Parameters: SMALL_RECT _area
 *                   const char _val
 *                   const BYTE textR
 *                   const BYTE textG
 *                   const BYTE textB
 *                   const BYTE backR
 *                   const BYTE backG
 *                   const BYTE backB
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void FastPrinter::fillRect(SMALL_RECT _area, const char _val, const BYTE textR, const BYTE textG, const BYTE textB, const BYTE backR, const BYTE backG, const BYTE backB)
{
    SHORT row = (_area.Right - _area.Left);
    for (size_t _i = _area.Top, i = 0; _i < (size_t)_area.Bottom; _i++, i++) {
        memset(dataGrid + (_i * sizeX + _area.Left), _val, row);
        for (size_t _j = _area.Left; _j < (size_t)_area.Right; _j++) {
            const size_t colorIndex = (_i * sizeX + _j) * 3;
            frontColorGrid[colorIndex] = textR;
            frontColorGrid[colorIndex + 1] = textG;
            frontColorGrid[colorIndex + 2] = textB;
            backColorGrid[colorIndex] = backR;
            backColorGrid[colorIndex + 1] = backG;
            backColorGrid[colorIndex + 2] = backB;
        }
    }
}

/*
 * Function Name:    setText
 * Function:         Print text with position and color
 * Input Parameters: COORD _pos
 *                   const char* _val
 *                   const size_t len
 *                   const BYTE textG
 *                   const BYTE textB
 *                   const BYTE backR
 *                   const BYTE backG
 *                   const BYTE backB
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 *                   Try not to set text with '\n'
 */
void FastPrinter::setText(COORD _pos, const char* _val, const size_t len, const BYTE textR, const BYTE textG, const BYTE textB, const BYTE backR, const BYTE backG, const BYTE backB)
{
    memcpy(dataGrid + (_pos.Y * sizeX + _pos.X), _val, len);
    for (size_t i = _pos.X; i < len + _pos.X; i++) {
        const size_t colorIndex = (_pos.Y * sizeX + i) * 3;
        frontColorGrid[colorIndex] = textR;
        frontColorGrid[colorIndex + 1] = textG;
        frontColorGrid[colorIndex + 2] = textB;
        backColorGrid[colorIndex] = backR;
        backColorGrid[colorIndex + 1] = backG;
        backColorGrid[colorIndex + 2] = backB;
    }
}

/*
 * Function Name:    setText
 * Function:         Print text with position and color but no len
 * Input Parameters: COORD _pos
 *                   const char* _val
 *                   const BYTE textG
 *                   const BYTE textB
 *                   const BYTE backR
 *                   const BYTE backG
 *                   const BYTE backB
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void FastPrinter::setText(COORD _pos, const char* _val, const BYTE textR, const BYTE textG, const BYTE textB, const BYTE backR, const BYTE backG, const BYTE backB)
{
    size_t len = strlen(_val);
    memcpy(dataGrid + (_pos.Y * sizeX + _pos.X), _val, len);
    for (size_t i = _pos.X; i < len + _pos.X; i++) {
        const size_t colorIndex = (_pos.Y * sizeX + i) * 3;
        frontColorGrid[colorIndex] = textR;
        frontColorGrid[colorIndex + 1] = textG;
        frontColorGrid[colorIndex + 2] = textB;
        backColorGrid[colorIndex] = backR;
        backColorGrid[colorIndex + 1] = backG;
        backColorGrid[colorIndex + 2] = backB;
    }
}

/*
 * Function Name:    setText
 * Function:         Print text with position but no len
 * Input Parameters: COORD _pos
 *                   const char* _val
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void FastPrinter::setText(COORD _pos, const char* _val)
{
    size_t len = strlen(_val);
    memcpy(dataGrid + (_pos.Y * sizeX + _pos.X), _val, len);
    memset(frontColorGrid + (_pos.Y * sizeX + _pos.X) * 3, 255, len * 3);
    memset(backColorGrid + (_pos.Y * sizeX + _pos.X) * 3, 0, len * 3);
}

/*
 * Function Name:    cleanSrceen
 * Function:         Clean srceen
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void FastPrinter::cleanSrceen(void)
{
    memset(dataGrid, 0, sizeX * sizeY);
    memset(frontColorGrid, 0, sizeX * sizeY * 3);
    memset(backColorGrid, 0, sizeX * sizeY * 3);
}

/*
 * Function Name:    draw
 * Function:         Flush the whole screen
 * Input Parameters: bool withColor
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 *                   Here is a higher performance on drawc without using double buffer
 */
void FastPrinter::draw(bool withColor)
{
    withColor ? _drawC() : _draw();
}