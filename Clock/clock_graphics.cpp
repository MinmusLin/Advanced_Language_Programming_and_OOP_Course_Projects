/****************************************************************
 * Project Name:  Clock
 * File Name:     clock_graphics.cpp
 * File Function: 抗锯齿图形处理函数的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/11/21
 ****************************************************************/

#include <graphics.h>
#include <cmath>
#include "clock.h"

using namespace std;

/*
 * Function Name:    calculate_line_SDF
 * Function:         Calculate the signed distance field of a straight line
 * Input Parameters: int x
 *                   int y
 *                   int x1
 *                   int y1
 *                   int x2
 *                   int y2
 *                   int d
 * Return Value:     the signed distance field of a straight line
 */
double calculate_line_SDF(int x, int y, int x1, int y1, int x2, int y2, int d)
{
    /* Preprocessing operations */
    int dx = x2 - x1, dy = y2 - y1, px = x - x1, py = y - y1, qx = x - x2, qy = y - y2;

    /* Calculate the length of the segment */
    double length = sqrt(dx * dx + dy * dy);

    /* Calculate the projection length from a point to the extension of the segment */
    double projection = (px * dx + py * dy) / length;

    /* Calculate the signed distance field of a straight line */
    if (projection < 0) { // Return the distance from the point to the starting point if the projection is before the endpoints
        return sqrt(px * px + py * py) - d;
    }
    else if (projection > length) { // Return the distance from the point to the ending point if the projection is after the endpoints
        return sqrt(qx * qx + qy * qy) - d;
    }
    else { // Return the perpendicular distance from a point to a line segment
        return fabs(px * dy - py * dx) / length - d;
    }
}

/*
 * Function Name:    line_SDF
 * Function:         Draw a line using SDF algorithm
 * Input Parameters: int x1
 *                   int y1
 *                   int x2
 *                   int y2
 *                   int d
 *                   COLORREF color
 * Return Value:     void
 */
void line_SDF(int x1, int y1, int x2, int y2, int d, COLORREF color)
{
    /* Determine traversal boundaries */
    int minX = min(x1, x2) - d;
    int maxX = max(x1, x2) + d;
    int minY = min(y1, y2) - d;
    int maxY = max(y1, y2) + d;

    /* Draw a line using SDF algorithm */
    for (int i = minX; i <= maxX; i++) {
        for (int j = minY; j <= maxY; j++) {
            /* Calculate the signed distance field of a straight line */
            double distance = calculate_line_SDF(i, j, x1, y1, x2, y2, d) + 1;
            if (distance < 2) {
                /* Alpha Blending */
                double alpha = 0.5 * distance;
                if (alpha < 0)
                    alpha = 0;
                if (alpha > 1)
                    alpha = 1;

                /* Put pixel */
                COLORREF target_color = getpixel(i, j);
                putpixel(i, j, RGB(GetRValue(color) * (1 - alpha) + GetRValue(target_color) * alpha, GetGValue(color) * (1 - alpha) + GetGValue(target_color) * alpha, GetBValue(color) * (1 - alpha) + GetBValue(target_color) * alpha));
            }
        }
    }
}

/*
 * Function Name:    circle_SDF
 * Function:         Draw a circle using SDF algorithm
 * Input Parameters: int x
 *                   int y
 *                   int r
 *                   int d
 *                   COLORREF color
 * Return Value:     void
 */
void circle_SDF(int x, int y, int r, int d, COLORREF color)
{
    /* Determine traversal boundaries */
    int minX = x - r - d;
    int maxX = x + r + d;
    int minY = y - r - d;
    int maxY = y + r + d;

    /* Draw a circle using SDF algorithm */
    for (int i = minX; i <= maxX; i++) {
        for (int j = minY; j <= maxY; j++) {
            /* Calculate the signed distance field of a circle */
            double distance = fabs(sqrt((i - x) * (i - x) + (j - y) * (j - y)) - r) - d + 1;
            if (distance < 2) {
                /* Alpha Blending */
                double alpha = 0.5 * distance;
                if (alpha < 0)
                    alpha = 0;
                if (alpha > 1)
                    alpha = 1;

                /* Put pixel */
                COLORREF target_color = getpixel(i, j);
                putpixel(i, j, RGB(GetRValue(color) * (1 - alpha) + GetRValue(target_color) * alpha, GetGValue(color) * (1 - alpha) + GetGValue(target_color) * alpha, GetBValue(color) * (1 - alpha) + GetBValue(target_color) * alpha));
            }
        }
    }
}