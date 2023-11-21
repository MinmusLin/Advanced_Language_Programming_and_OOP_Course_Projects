/****************************************************************
 * Project Name:  common
 * File Name:     FastPrinter.h
 * File Function: 底层控制台绘制函数工具集的头文件
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/11/21
 ****************************************************************/

#pragma once
#ifndef FASTPRINTER_H
#define FASTPRINTER_H

#include <Windows.h>

/* Define FastPrinter class */
class FastPrinter {
private:
    HANDLE hOutput = INVALID_HANDLE_VALUE;
    char* dataGrid = nullptr;
    BYTE* frontColorGrid = nullptr;
    BYTE* backColorGrid = nullptr;
    char* outputSequence = nullptr;
    size_t sequenceLength = 0;
    size_t sequenceCapacity = 0;
    size_t needUpdate = 0;
    size_t sizeX = 0;
    size_t sizeY = 0;
    void initDrawer(void);
    void _setFontSize(const WORD x);
    void _destroy(void);
    void _draw(void);
    void _drawC(void);
public:
    FastPrinter(size_t x, size_t y);
    FastPrinter(size_t x, size_t y, WORD fontSize);
    ~FastPrinter();
    void setData(const char* _in_data, const BYTE* _in_front_color, const BYTE* _in_back_color);
    void setData(const char* _in_data, const BYTE* _in_front_color, const BYTE* _in_back_color, SMALL_RECT _area);
    void setRect(SMALL_RECT _area, const char _val, const BYTE textR, const BYTE textG, const BYTE textB, const BYTE backR, const BYTE backG, const BYTE backB);
    void fillRect(SMALL_RECT _area, const char _val, const BYTE textR, const BYTE textG, const BYTE textB, const BYTE backR, const BYTE backG, const BYTE backB);
    void setText(COORD _pos, const char* _val, const size_t len, const BYTE textR, const BYTE textG, const BYTE textB, const BYTE backR, const BYTE backG, const BYTE backB);
    void setText(COORD _pos, const char* _val, const BYTE textR, const BYTE textG, const BYTE textB, const BYTE backR, const BYTE backG, const BYTE backB);
    void setText(COORD _pos, const char* _val);
    void cleanSrceen(void);
    void draw(bool withColor);
};

#endif // !FASTPRINTER_H