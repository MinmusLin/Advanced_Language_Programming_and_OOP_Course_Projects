/****************************************************************
 * Project Name:  common
 * File Name:     lib_hdc_tools.h
 * File Function: 图形界面绘制函数工具集的头文件
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/9/24
 ****************************************************************/

#pragma once

/* Define invalid RGB */
#define INVALID_RGB 0x7FFFFFFF

/* Conditional compilation */
#define HDC_SERIES_BY_TONGJI 1
#if HDC_SERIES_BY_TONGJI
#define hdc_init thdc_init
#define hdc_release thdc_release
#define hdc_set_delay thdc_set_delay
#define hdc_set_pencolor thdc_set_pencolor
#define hdc_cls thdc_cls
#define hdc_point thdc_point
#define hdc_line thdc_line
#define hdc_triangle thdc_triangle
#define hdc_rectangle thdc_rectangle
#define hdc_square thdc_square
#define hdc_arc thdc_arc
#define hdc_sector thdc_sector
#define hdc_circle thdc_circle
#define hdc_ellipse thdc_ellipse

/* Function declarations in lib_hdc_tools.lib */
void thdc_init(const int bgcolor = 0, const int fgcolor = 7, const int width = 8 * 120, const int high = 16 * 30);
void thdc_release(void);
void thdc_set_delay(int ms);
void thdc_set_pencolor(const int rgb_value);
void thdc_set_pencolor(const unsigned char red, const unsigned char green, const unsigned char blue);
void thdc_cls(void);
void thdc_point(const int x, const int y, const int thickness = 3, const int RGB_value = INVALID_RGB);
void thdc_line(const int x1, const int y1, const int x2, const int y2, const int thickness = 2, const int RGB_value = INVALID_RGB);
void thdc_triangle(const int x1, const int y1, const int x2, const int y2, const int x3, const int y3, bool filled = false, const int thickness = 2, const int RGB_value = INVALID_RGB);
void thdc_rectangle(const int left_up_x, const int left_up_y, const int width, const int high, const int rotation_angles = 0, const bool filled = false, const int thickness = 2, const int RGB_value = INVALID_RGB);
void thdc_square(const int left_up_x, const int left_up_y, const int length, const int rotation_angles = 0, const bool filled = false, const int thickness = 2, const int RGB_value = INVALID_RGB);
void thdc_arc(const int point_x, const int point_y, const int radius, const int angle_begin = 0, const int angle_end = 360, const int thickness = 2, const int RGB_value = INVALID_RGB);
void thdc_sector(const int point_x, const int point_y, const int radius, const int angle_begin = 0, const int angle_end = 360, const bool filled = false, const int thickness = 2, const int RGB_value = INVALID_RGB);
void thdc_circle(const int point_x, const int point_y, const int radius, const bool filled = false, const int thickness = 2, const int RGB_value = INVALID_RGB);
void thdc_ellipse(const int point_x, const int point_y, const int radius_a, const int radius_b, const int rotation_angles = 0, const bool filled = false, const int thickness = 2, const int RGB_value = INVALID_RGB);
#else

/* Function declarations in lib_hdc_tools.cpp */
void hdc_init(const int bgcolor = 0, const int fgcolor = 7, const int width = 8 * 120, const int high = 16 * 30);
void hdc_release(void);
void hdc_set_delay(int ms);
void hdc_set_pencolor(const int rgb_value);
void hdc_set_pencolor(const unsigned char red, const unsigned char green, const unsigned char blue);
void hdc_cls(void);
void hdc_point(const int x, const int y, const int thickness = 3, const int RGB_value = INVALID_RGB);
void hdc_line(const int x1, const int y1, const int x2, const int y2, const int thickness = 2, const int RGB_value = INVALID_RGB);
void hdc_triangle(const int x1, const int y1, const int x2, const int y2, const int x3, const int y3, bool filled = false, const int thickness = 2, const int RGB_value = INVALID_RGB);
void hdc_rectangle(const int left_up_x, const int left_up_y, const int width, const int high, const int rotation_angles = 0, const bool filled = false, const int thickness = 2, const int RGB_value = INVALID_RGB);
void hdc_square(const int left_up_x, const int left_up_y, const int length, const int rotation_angles = 0, const bool filled = false, const int thickness = 2, const int RGB_value = INVALID_RGB);
void hdc_arc(const int point_x, const int point_y, const int radius, const int angle_begin = 0, const int angle_end = 360, const int thickness = 2, const int RGB_value = INVALID_RGB);
void hdc_sector(const int point_x, const int point_y, const int radius, const int angle_begin = 0, const int angle_end = 360, const bool filled = false, const int thickness = 2, const int RGB_value = INVALID_RGB);
void hdc_circle(const int point_x, const int point_y, const int radius, const bool filled = false, const int thickness = 2, const int RGB_value = INVALID_RGB);
void hdc_ellipse(const int point_x, const int point_y, const int radius_a, const int radius_b, const int rotation_angles = 0, const bool filled = false, const int thickness = 2, const int RGB_value = INVALID_RGB);
#endif