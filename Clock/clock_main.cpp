/****************************************************************
 * Project Name:  Clock
 * File Name:     clock_main.cpp
 * File Function: 主体函数的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/9/24
 ****************************************************************/

#include <graphics.h>
#include <cmath>
#include <ctime>
#include "clock.h"
using namespace std;

/*
 * Function Name:    main
 * Function:         Main function
 * Return Value:     0
 */
int main()
{
    /* Initialize graphical interface */
    initgraph(consoleWidth, consoleHeight);

    /* Draw gradient color background */
    COLORREF start = RGB(130, 148, 196), end = RGB(255, 234, 210);
    for (int step = 0; step < consoleHeight; step++) {
        double t = double(step) / consoleHeight;
        int r = GetRValue(start) + int((GetRValue(end) - GetRValue(start)) * t);
        int g = GetGValue(start) + int((GetGValue(end) - GetGValue(start)) * t);
        int b = GetBValue(start) + int((GetBValue(end) - GetBValue(start)) * t);
        setlinecolor(RGB(r, g, b));
        line(0, step, consoleWidth - 1, step);
    }

    /* Draw dial */
    setorigin(consoleWidth / 2, consoleHeight / 2);
    setfillcolor(RGB(187, 225, 250));
    fillcircle(0, 0, dialRadius);
    circle_SDF(0, 0, dialRadius, edgeWidth, RGB(50, 130, 184));

    /* Draw tick lines */
    for (int i = 0; i < 60; i++) {
        double a = PI / 30 * i;
        int outerRadius = (i % 5 == 0 ? majorTickOuterRadius : minorTickOuterRadius);
        int innerRadius = (i % 5 == 0 ? majorTickInnerRadius : minorTickInnerRadius);
        int tickWidth = (i % 5 == 0 ? majorTickWidth : minorTickWidth);
        line_SDF(int(outerRadius * cos(a)), int(outerRadius * sin(a)), int(innerRadius * cos(a)), int(innerRadius * sin(a)), tickWidth, RGB(15, 76, 117));
    }

    /* Draw numbers */
    LOGFONT f;
    gettextstyle(&f);
    f.lfHeight = numberHeight;
    f.lfWeight = numberWeight;
    _tcscpy_s(f.lfFaceName, _T("Segoe UI Light"));
    f.lfQuality = ANTIALIASED_QUALITY;
    settextstyle(&f);
    setbkmode(TRANSPARENT);
    settextcolor(RGB(15, 76, 117));
    TCHAR number[12][3] = { _T("1") ,_T("2") ,_T("3") ,_T("4") ,_T("5") ,_T("6") ,_T("7") ,_T("8") ,_T("9"),_T("10"),_T("11"),_T("12") };
    for (int i = 0; i < 12; i++) {
        double a = PI / 6 * (i - 2);
        RECT r = { long(numberCenterRadius * cos(a) - numberHeight), long(numberCenterRadius * sin(a) - numberHeight), long(numberCenterRadius * cos(a) + numberHeight), long(numberCenterRadius * sin(a) + numberHeight) };
        drawtext(number[i], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }

    /* Initialize old time */
    clock_t oldClock = 0;
    time_t oldTime = 0;

    /* Initialize elapsed time */
    int elapsed_time = (time(0) % 60 - 15) * CLOCKS_PER_SEC;

    /* Print clock hands */
    while (true) {
        /* Obtain new time */
        time_t newTime = time(0) % 43200;
        clock_t newClock = clock_t((clock() + elapsed_time) / (CLOCKS_PER_SEC / (double)refreshTime));

        /* Update clock hands' state */
        if (newClock != oldClock) {
            /* Calculate angles */
            double a1 = (oldClock)*PI / 30 / refreshTime;
            double a2 = (newClock)*PI / 30 / refreshTime;
            double b1 = (oldTime - 900) * PI / 1800;
            double b2 = (newTime - 900) * PI / 1800;
            double c1 = (oldTime - 25200) * PI / 21600;
            double c2 = (newTime - 25200) * PI / 21600;

            /* Initialize background buffer */
            IMAGE* backBuffer = new(nothrow) IMAGE(consoleWidth, consoleHeight);
            if (backBuffer == NULL)
                return -1;
            getimage(backBuffer, -consoleWidth / 2, -consoleHeight / 2, consoleWidth, consoleHeight);
            SetWorkingImage(backBuffer);
            setorigin(consoleWidth / 2, consoleHeight / 2);

            /* Erase old clock hands */
            line_SDF(int(-hourHandNegativeLength * cos(c1)), int(-hourHandNegativeLength * sin(c1)), int(hourHandLength * cos(c1)), int(hourHandLength * sin(c1)), hourHandWidth + 2, RGB(187, 225, 250));
            circle_SDF(int(-hourHandNegativeLength * cos(c1)), int(-hourHandNegativeLength * sin(c1)), 0, hourHandEndRadius + 2, RGB(187, 225, 250));
            line_SDF(int(-minuteHandNegativeLength * cos(b1)), int(-minuteHandNegativeLength * sin(b1)), int(minuteHandLength * cos(b1)), int(minuteHandLength * sin(b1)), minuteHandWidth + 2, RGB(187, 225, 250));
            circle_SDF(int(-minuteHandNegativeLength * cos(b1)), int(-minuteHandNegativeLength * sin(b1)), 0, minuteHandEndRadius + 2, RGB(187, 225, 250));
            line_SDF(int(-secondHandNegativeLength * cos(a1)), int(-secondHandNegativeLength * sin(a1)), int(secondHandLength * cos(a1)), int(secondHandLength * sin(a1)), secondHandWidth + 2, RGB(187, 225, 250));
            circle_SDF(int(-secondHandNegativeLength * cos(a1)), int(-secondHandNegativeLength * sin(a1)), 0, secondHandEndRadius + 2, RGB(187, 225, 250));
            
            /* Draw new clock hands */
            line_SDF(int(-hourHandNegativeLength * cos(c2)), int(-hourHandNegativeLength * sin(c2)), int(hourHandLength * cos(c2)), int(hourHandLength * sin(c2)), hourHandWidth, RGB(26, 50, 99));
            circle_SDF(0, 0, 0, hourHandCenterRadius, RGB(26, 50, 99));
            circle_SDF(int(-hourHandNegativeLength * cos(c2)), int(-hourHandNegativeLength * sin(c2)), 0, hourHandEndRadius, RGB(26, 50, 99));
            line_SDF(int(-minuteHandNegativeLength * cos(b2)), int(-minuteHandNegativeLength * sin(b2)), int(minuteHandLength * cos(b2)), int(minuteHandLength * sin(b2)), minuteHandWidth, RGB(241, 104, 33));
            circle_SDF(0, 0, 0, minuteHandCenterRadius, RGB(241, 104, 33));
            circle_SDF(int(-minuteHandNegativeLength * cos(b2)), int(-minuteHandNegativeLength * sin(b2)), 0, minuteHandEndRadius, RGB(241, 104, 33));
            line_SDF(int(-secondHandNegativeLength * cos(a2)), int(-secondHandNegativeLength * sin(a2)), int(secondHandLength * cos(a2)), int(secondHandLength * sin(a2)), secondHandWidth, RGB(250, 185, 91));
            circle_SDF(0, 0, 0, secondHandCenterRadius, RGB(250, 185, 91));
            circle_SDF(int(-secondHandNegativeLength * cos(a2)), int(-secondHandNegativeLength * sin(a2)), 0, secondHandEndRadius, RGB(250, 185, 91));

            /* Draw the background buffer on the screen */
            setorigin(0, 0);
            SetWorkingImage(NULL);
            putimage(-consoleWidth / 2, -consoleHeight / 2, backBuffer);

            /* Free dynamic memory */
            delete backBuffer;
        }

        /* Save old time */
        oldClock = newClock;
        oldTime = newTime;
    }

    /* Program ends (theoretically unreachable) */
    closegraph();
    return 0;
}