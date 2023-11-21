/****************************************************************
 * Project Name:  common
 * File Name:     lib_hdc_tools.cpp
 * File Function: 图形界面绘制函数工具集的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/11/21
 ****************************************************************/

#include <cmath>
#include <Windows.h>
#include "../common/cmd_console_tools.h"
#include "../common/lib_hdc_tools.h"

using namespace std;

/* Conditional compilation */
#if !HDC_SERIES_BY_TONGJI

/* Retrieve the handle of the current process's console window */
extern "C" WINBASEAPI HWND WINAPI GetConsoleWindow();

/* Define PI */
const double PI = 3.1415926535;

/* Define static variables */
static HWND hWnd = GetConsoleWindow();
static HDC hdc = NULL;
static int _BgColor_;
static int _FgColor_;
static int _Width_;
static int _High;
static int _Delay_ms;

/*
 * Function Name:    calculate_shortest_distance
 * Function:         Calculate the shortest distance from a point to a line segment
 * Input Parameters: int x
 *                   int y
 *                   int x1
 *                   int y1
 *                   int x2
 *                   int y2
 *                   double d
 * Return Value:     the shortest distance from a point to a line segment
 */
static double calculate_shortest_distance(int x, int y, int x1, int y1, int x2, int y2, double d)
{
    int dx = x2 - x1, dy = y2 - y1, px = x - x1, py = y - y1, qx = x - x2, qy = y - y2;
    double length = sqrt(dx * dx + dy * dy);
    double projection = (px * dx + py * dy) / length;
    if (projection < 0)
        return sqrt(px * px + py * py) - d;
    else if (projection > length)
        return sqrt(qx * qx + qy * qy) - d;
    else
        return fabs(px * dy - py * dx) / length - d;
}

/*
 * Function Name:    calculate_cross_product
 * Function:         Calculate cross product
 * Input Parameters: int x0
 *                   int y0
 *                   int x1
 *                   int y1
 *                   int x2
 *                   int y2
 * Return Value:     cross product
 */
static int calculate_cross_product(int x0, int y0, int x1, int y1, int x2, int y2)
{
    return (x1 - x0) * (y2 - y0) - (y1 - y0) * (x2 - x0);
}

/*
 * Function Name:    is_inside_triangle
 * Function:         Check if a point is inside a triangle
 * Input Parameters: int x
 *                   int y
 *                   int x1
 *                   int y1
 *                   int x2
 *                   int y2
 *                   int x3
 *                   int y3
 * Return Value:     true / false
 */
static bool is_inside_triangle(int x, int y, int x1, int y1, int x2, int y2, int x3, int y3)
{
    int cp1 = calculate_cross_product(x1, y1, x2, y2, x, y);
    int cp2 = calculate_cross_product(x2, y2, x3, y3, x, y);
    int cp3 = calculate_cross_product(x3, y3, x1, y1, x, y);
    return (cp1 >= 0 && cp2 >= 0 && cp3 >= 0) || (cp1 <= 0 && cp2 <= 0 && cp3 <= 0);
}

/*
 * Function Name:    degrees_to_radians
 * Function:         Convert degrees to radians
 * Input Parameters: double degrees
 * Return Value:     radians
 */
static double degrees_to_radians(double degrees)
{
    return degrees * PI / 180;
}

/*
 * Function Name:    is_inside_ellipse
 * Function:         Check if a point is inside a ellipse
 * Input Parameters: int x
 *                   int y
 *                   int x0
 *                   int y0
 *                   int a
 *                   int b
 *                   double alpha
 *                   double tolerance
 * Return Value:     true / false
 */
static bool is_inside_ellipse(int x, int y, int x0, int y0, int a, int b, double alpha, double tolerance = 1e-6)
{
    double xRot = cos(-alpha) * (x - x0) - sin(-alpha) * (y - y0);
    double yRot = sin(-alpha) * (x - x0) + cos(-alpha) * (y - y0);
    double distance = (xRot * xRot) / (a * a) + (yRot * yRot) / (b * b);
    return (distance <= 1.0 + tolerance);
}

/*
 * Function Name:    hdc_init
 * Function:         Initialization function
 * Input Parameters: const int bgcolor
 *                   const int fgcolor
 *                   const int width
 *                   const int high
 * Return Value:     void
 */
void hdc_init(const int bgcolor, const int fgcolor, const int width, const int high)
{
    hdc_release();
    _BgColor_ = bgcolor;
    _FgColor_ = fgcolor;
    _Width_ = width;
    _High = high;
    hdc = GetDC(hWnd);
    cct_setcursor(CURSOR_INVISIBLE);
    cct_setcolor(bgcolor, fgcolor);
    cct_setfontsize("Terminal", 16);
    cct_setconsoleborder(width / 8 + !!(width % 8), high / 16 + !!(high % 16));
    cct_cls();
}

/*
 * Function Name:    hdc_release
 * Function:         Release drawing resources
 * Input Parameters: void
 * Return Value:     void
 */
void hdc_release(void)
{
    if (hdc) {
        ReleaseDC(hWnd, hdc);
        hdc = NULL;
        cct_setcursor(CURSOR_VISIBLE_NORMAL);
    }
}

/*
 * Function Name:    hdc_set_delay
 * Function:         Set delay time
 * Input Parameters: int ms
 * Return Value:     void
 */
void hdc_set_delay(int ms)
{
    _Delay_ms = (ms > 0 ? ms : 0);
}

/*
 * Function Name:    hdc_set_pencolor
 * Function:         Set pen color
 * Input Parameters: const int RGB_value
 * Return Value:     void
 */
void hdc_set_pencolor(const int RGB_value)
{
    SelectObject(hdc, GetStockObject(DC_PEN));
    SetDCPenColor(hdc, RGB_value);
}

/*
 * Function Name:    hdc_set_pencolor
 * Function:         Set pen color (RGB)
 * Input Parameters: const unsigned char red
 *                   const unsigned char green
 *                   const unsigned char blue
 * Return Value:     void
 */
void hdc_set_pencolor(const unsigned char red, const unsigned char green, const unsigned char blue)
{
    hdc_set_pencolor(RGB(red, green, blue));
}

/*
 * Function Name:    hdc_cls
 * Function:         Clear the screen content
 * Input Parameters: void
 * Return Value:     void
 */
void hdc_cls(void)
{
    hdc_init(_BgColor_, (_FgColor_ + 1) % 16, _Width_, _High);
    hdc_init(_BgColor_, _FgColor_, _Width_, _High);
    Sleep(30);
}

/*
 * Function Name:    hdc_base_point
 * Function:         Draw a point
 * Input Parameters: const int x
 *                   const int y
 * Return Value:     void
 */
static inline void hdc_base_point(const int x, const int y)
{
    MoveToEx(hdc, x - 1, y - 1, NULL);
    LineTo(hdc, x, y);
    if (_Delay_ms > 0)
        Sleep(_Delay_ms);
}

/*
 * Function Name:    hdc_base_line
 * Function:         Draw a line
 * Input Parameters: const int x1
 *                   const int y1
 *                   const int x2
 *                   const int y2
 * Return Value:     void
 */
static inline void hdc_base_line(const int x1, const int y1, const int x2, const int y2)
{
    MoveToEx(hdc, x1, y1, NULL);
    LineTo(hdc, x2, y2);
    if (_Delay_ms > 0)
        Sleep(_Delay_ms);
}

/*
 * Function Name:    hdc_point
 * Function:         Draw a point with a specified thickness
 * Input Parameters: const int x
 *                   const int y
 *                   const int thickness
 *                   const int RGB_value
 * Return Value:     void
 */
void hdc_point(const int x, const int y, const int thickness, const int RGB_value)
{
    int tn = thickness, angle, level, old_x1 = INT_MAX, old_y1 = INT_MAX, x1, y1, count = 0;
    if (tn < 1)
        tn = 1;
    const int tn_end = (tn <= 1) ? 1 : tn / 2;
    if (RGB_value != INVALID_RGB)
        hdc_set_pencolor(RGB_value);
    for (level = 1; level <= tn_end; level++)
        for (angle = 0; angle <= 360; angle++) {
            x1 = x + (int)(level * sin(angle * PI / 180));
            y1 = y - (int)(level * cos(angle * PI / 180));
            if (x1 != old_x1 || y1 != old_y1) {
                old_x1 = x1;
                old_y1 = y1;
                hdc_base_point(x1, y1);
                count++;
            }
        }
}

/*
 * Function Name:    hdc_line
 * Function:         Draw a line with a specified thickness
 * Input Parameters: const int x1
 *                   const int y1
 *                   const int x2
 *                   const int y2
 *                   const int thickness
 *                   const int RGB_value
 * Return Value:     void
 */
void hdc_line(const int x1, const int y1, const int x2, const int y2, const int thickness, const int RGB_value)
{
    int minX = min(x1, x2) - thickness / 2;
    int maxX = max(x1, x2) + thickness / 2;
    int minY = min(y1, y2) - thickness / 2;
    int maxY = max(y1, y2) + thickness / 2;
    hdc_set_pencolor(RGB_value);
    for (int i = minX; i <= maxX; i++)
        for (int j = minY; j <= maxY; j++)
            if (calculate_shortest_distance(i, j, x1, y1, x2, y2, double(thickness / 2)) <= 0)
                hdc_base_point(i, j);
}

/*
 * Function Name:    hdc_triangle
 * Function:         Draw a triangle
 * Input Parameters: const int x1
 *                   const int y1
 *                   const int x2
 *                   const int y2
 *                   const int x3
 *                   const int y3
 *                   bool filled
 *                   const int thickness
 *                   const int RGB_value
 * Return Value:     void
 */
void hdc_triangle(const int x1, const int y1, const int x2, const int y2, const int x3, const int y3, bool filled, const int thickness, const int RGB_value)
{
    if (filled) {
        int minX = min(min(x1, x2), x3) - thickness / 2;
        int maxX = max(max(x1, x2), x3) + thickness / 2;
        int minY = min(min(y1, y2), y3) - thickness / 2;
        int maxY = max(max(y1, y2), y3) + thickness / 2;
        hdc_set_pencolor(RGB_value);
        for (int i = minX; i <= maxX; i++)
            for (int j = minY; j <= maxY; j++)
                if (is_inside_triangle(i, j, x1, y1, x2, y2, x3, y3))
                    hdc_base_point(i, j);
    }
    hdc_line(x1, y1, x2, y2, thickness, RGB_value);
    hdc_line(x2, y2, x3, y3, thickness, RGB_value);
    hdc_line(x3, y3, x1, y1, thickness, RGB_value);
}

/*
 * Function Name:    hdc_rectangle
 * Function:         Draw a rectangle
 * Input Parameters: const int left_up_x
 *                   const int left_up_y
 *                   const int width
 *                   const int high
 *                   const int rotation_angles
 *                   const bool filled
 *                   const int thickness
 *                   const int RGB_value
 * Return Value:     void
 */
void hdc_rectangle(const int left_up_x, const int left_up_y, const int width, const int high, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
    double a = degrees_to_radians(rotation_angles);
    int x1 = left_up_x, y1 = left_up_y;
    int x2 = int(x1 + width * cos(a)), y2 = int(y1 + width * sin(a));
    int x3 = int(x1 - high * sin(a)), y3 = int(y1 + high * cos(a));
    int x4 = x2 + x3 - x1, y4 = y2 + y3 - y1;
    if (filled) {
        hdc_triangle(x1, y1, x2, y2, x3, y3, filled, thickness, RGB_value);
        hdc_triangle(x4, y4, x2, y2, x3, y3, filled, thickness, RGB_value);
    }
    else {
        hdc_line(x1, y1, x2, y2, thickness, RGB_value);
        hdc_line(x1, y1, x3, y3, thickness, RGB_value);
        hdc_line(x4, y4, x2, y2, thickness, RGB_value);
        hdc_line(x4, y4, x3, y3, thickness, RGB_value);
    }
}

/*
 * Function Name:    hdc_square
 * Function:         Draw a square
 * Input Parameters: const int left_up_x
 *                   const int left_up_y
 *                   const int length
 *                   const int rotation_angles
 *                   const bool filled
 *                   const int thickness
 *                   const int RGB_value
 * Return Value:     void
 */
void hdc_square(const int left_up_x, const int left_up_y, const int length, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
    hdc_rectangle(left_up_x, left_up_y, length, length, rotation_angles, filled, thickness, RGB_value);
}

/*
 * Function Name:    hdc_arc
 * Function:         Draw an arc
 * Input Parameters: const int point_x
 *                   const int point_y
 *                   const int radius
 *                   const int angle_begin
 *                   const int angle_end
 *                   const int thickness
 *                   const int RGB_value
 * Return Value:     void
 */
void hdc_arc(const int point_x, const int point_y, const int radius, const int angle_begin, const int angle_end, const int thickness, const int RGB_value)
{
    int degree_end = angle_end;
    while (degree_end <= angle_begin)
        degree_end += 360;
    for (int i = angle_begin * 10; i < degree_end * 10; angle_begin < degree_end ? i++ : i--)
        hdc_point(int(point_x + radius * cos(degrees_to_radians(i / 10.0 - 90))), int(point_y + radius * sin(degrees_to_radians(i / 10.0 - 90))), thickness, RGB_value);
}

/*
 * Function Name:    hdc_sector
 * Function:         Draw a sector
 * Input Parameters: const int point_x
 *                   const int point_y
 *                   const int radius
 *                   const int angle_begin
 *                   const int angle_end
 *                   const bool filled
 *                   const int thickness
 *                   const int RGB_value
 * Return Value:     void
 */
void hdc_sector(const int point_x, const int point_y, const int radius, const int angle_begin, const int angle_end, const bool filled, const int thickness, const int RGB_value)
{
    int degree_end = angle_end;
    while (degree_end <= angle_begin)
        degree_end += 360;
    hdc_line(point_x, point_y, int(point_x + radius * cos(degrees_to_radians(angle_begin - 90))), int(point_y + radius * sin(degrees_to_radians(angle_begin - 90))), thickness, RGB_value);
    hdc_line(point_x, point_y, int(point_x + radius * cos(degrees_to_radians(angle_end - 90))), int(point_y + radius * sin(degrees_to_radians(angle_end - 90))), thickness, RGB_value);
    hdc_arc(point_x, point_y, radius, angle_begin, angle_end, thickness, RGB_value);
    if (filled)
        for (int i = angle_begin * 10; i < degree_end * 10; angle_begin < degree_end ? i += thickness - 1 : i -= thickness - 1)
            hdc_line(point_x, point_y, int(point_x + radius * cos(degrees_to_radians(i / 10.0 - 90))), int(point_y + radius * sin(degrees_to_radians(i / 10.0 - 90))), thickness, RGB_value);
}

/*
 * Function Name:    hdc_circle
 * Function:         Draw a circle
 * Input Parameters: const int point_x
 *                   const int point_y
 *                   const int radius
 *                   const bool filled
 *                   const int thickness
 *                   const int RGB_value
 * Return Value:     void
 */
void hdc_circle(const int point_x, const int point_y, const int radius, const bool filled, const int thickness, const int RGB_value)
{
    hdc_arc(point_x, point_y, radius, 0, 0, thickness, RGB_value);
    if (filled)
        for (int i = point_x - radius; i <= point_x + radius; i++)
            for (int j = point_y - radius; j <= point_y + radius; j++)
                if ((i - point_x) * (i - point_x) + (j - point_y) * (j - point_y) <= radius * radius) {
                    hdc_set_pencolor(RGB_value);
                    hdc_base_point(i, j);
                }
}

/*
 * Function Name:    hdc_ellipse
 * Function:         Draw a ellipse
 * Input Parameters: const int point_x
 *                   const int point_y
 *                   const int radius_a
 *                   const int radius_b
 *                   const int rotation_angles
 *                   const bool filled
 *                   const int thickness
 *                   const int RGB_value
 * Return Value:     void
 */
void hdc_ellipse(const int point_x, const int point_y, const int radius_a, const int radius_b, const int rotation_angles, const bool filled, const int thickness, const int RGB_value)
{
    double a = degrees_to_radians(rotation_angles);
    for (int i = 0; i < 3600; i++) {
        double b = degrees_to_radians(i);
        int x = int(point_x + radius_a * cos(b / 10.0) * cos(a) - radius_b * sin(b / 10.0) * sin(a));
        int y = int(point_y + radius_a * cos(b / 10.0) * sin(a) + radius_b * sin(b / 10.0) * cos(a));
        hdc_point(x, y, thickness, RGB_value);
    }
    if (filled) {
        int r = max(radius_a, radius_b);
        for (int i = point_x - r; i <= point_x + r; i++)
            for (int j = point_y - r; j <= point_y + r; j++)
                if (is_inside_ellipse(i, j, point_x, point_y, radius_a, radius_b, a)) {
                    hdc_set_pencolor(RGB_value);
                    hdc_base_point(i, j);
                }
    }
}
#endif