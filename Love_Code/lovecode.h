/****************************************************************
 * Project Name:  Love_Code
 * File Name:     lovecode.h
 * File Function: 主体函数、工具函数的头文件
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/11/21
 ****************************************************************/

#pragma once
#ifndef LOVECODE_H
#define LOVECODE_H

/* Macro definitions */
#define OUR_STORY_BEGINNING 1675297680
#define EVER ;;
#define FULL_FIT true
#define UPPERCASE 55
#define LOWERCASE 61
#define GREATER_THAN_SIGN 62
#define EQUAL_SIGN 63
#define UNDERLINE 64
#define SPACE 94
#define END -1

/* Define constant variables */
const double PI = 3.14;
const int ORIGIN_OF_ABSCISSA = 150;
const int ORIGIN_OF_ORDINATE = 150;
const int ABSCISSA_OF_STARTING_CAPTION = 34;
const int ORDINATE_OF_STARTING_CAPTION = 46;
const int CORRECTION_FACTOR = 20;
const int MAXIMUN_OF_POINTS = 1024;
const int LINE_SPACE = 8;
const int LEFT_INDENT = 78;
const int LEFT_SHIFT_DISTANCE = 4;
const int CYCLE_INDEX = 9;
const int MAGNIFICATION = 8;
const int SHRINK_BOUNDARIES = 100;
const int POINT_SET_DENSITY = 16;
const int PROBABILITY_FACTOR = 2;
const int FLICKER_PROBABILITY = 6;
const int FLICKER_TIMES = 6;
const int SLEEP_TIME = 50;
const int starting_captions[][32] = {
    {GREATER_THAN_SIGN,GREATER_THAN_SIGN,GREATER_THAN_SIGN,SPACE,'l' - LOWERCASE,'o' - LOWERCASE,'v' - LOWERCASE,'e' - LOWERCASE,SPACE,EQUAL_SIGN,SPACE,'t' - LOWERCASE,'h' - LOWERCASE,'i' - LOWERCASE,'s' - LOWERCASE,END},
    {GREATER_THAN_SIGN,GREATER_THAN_SIGN,GREATER_THAN_SIGN,SPACE,'t' - LOWERCASE,'h' - LOWERCASE,'i' - LOWERCASE,'s' - LOWERCASE,SPACE,'i' - LOWERCASE,'s' - LOWERCASE,SPACE,'l' - LOWERCASE,'o' - LOWERCASE,'v' - LOWERCASE,'e' - LOWERCASE,END},
    {'T' - UPPERCASE,'r' - LOWERCASE,'u' - LOWERCASE,'e' - LOWERCASE,END},
    {GREATER_THAN_SIGN,GREATER_THAN_SIGN,GREATER_THAN_SIGN,SPACE,'l' - LOWERCASE,'o' - LOWERCASE,'v' - LOWERCASE,'e' - LOWERCASE,SPACE,'i' - LOWERCASE,'s' - LOWERCASE,SPACE,'T' - UPPERCASE,'r' - LOWERCASE,'u' - LOWERCASE,'e' - LOWERCASE,END},
    {'F' - UPPERCASE,'a' - LOWERCASE,'l' - LOWERCASE,'s' - LOWERCASE,'e' - LOWERCASE,END},
    {GREATER_THAN_SIGN,GREATER_THAN_SIGN,GREATER_THAN_SIGN,SPACE,'l' - LOWERCASE,'o' - LOWERCASE,'v' - LOWERCASE,'e' - LOWERCASE,SPACE,'i' - LOWERCASE,'s' - LOWERCASE,SPACE,'F' - UPPERCASE,'a' - LOWERCASE,'l' - LOWERCASE,'s' - LOWERCASE,'e' - LOWERCASE,END},
    {'F' - UPPERCASE,'a' - LOWERCASE,'l' - LOWERCASE,'s' - LOWERCASE,'e' - LOWERCASE,END},
    {GREATER_THAN_SIGN,GREATER_THAN_SIGN,GREATER_THAN_SIGN,SPACE,'l' - LOWERCASE,'o' - LOWERCASE,'v' - LOWERCASE,'e' - LOWERCASE,SPACE,'i' - LOWERCASE,'s' - LOWERCASE,SPACE,'n' - LOWERCASE,'o' - LOWERCASE,'t' - LOWERCASE,SPACE,'T' - UPPERCASE,'r' - LOWERCASE,'u' - LOWERCASE,'e' - LOWERCASE,SPACE,'o' - LOWERCASE,'r' - LOWERCASE,SPACE,'F' - UPPERCASE,'a' - LOWERCASE,'l' - LOWERCASE,'s' - LOWERCASE,'e' - LOWERCASE,END},
    {'T' - UPPERCASE,'r' - LOWERCASE,'u' - LOWERCASE,'e' - LOWERCASE,END},
    {GREATER_THAN_SIGN,GREATER_THAN_SIGN,GREATER_THAN_SIGN,SPACE,'l' - LOWERCASE,'o' - LOWERCASE,'v' - LOWERCASE,'e' - LOWERCASE,SPACE,'i' - LOWERCASE,'s' - LOWERCASE,SPACE,'l' - LOWERCASE,'o' - LOWERCASE,'v' - LOWERCASE,'e' - LOWERCASE,END},
    {'T' - UPPERCASE,'r' - LOWERCASE,'u' - LOWERCASE,'e' - LOWERCASE,END},
    {END}
};

/* Define structure types */
struct point {
    double x = 0;
    double y = 0;
};

struct system_time {
    int days = 0;
    int hours = 0;
    int minutes = 0;
    int seconds = 0;
};

/* Define point_set class */
class point_set {
private:
    struct point points[MAXIMUN_OF_POINTS];
    int number_of_points;
public:
    void point_initialize(int precision, double factor, int fullfit_or_not = 0);
    void print_heart(int bg_color, int fg_color);
};

/* Define pixel_characters class */
class pixel_characters {
private:
    int pixel_matrix[16][16];
public:
    pixel_characters(const int character[][16]);
    void print_character(int x, int y, int bg_color, int fg_color);
};

/* Define pixel_ASCIIs class */
class pixel_ASCIIs {
private:
    int pixel_matrix[95][16][8];
public:
    pixel_ASCIIs(const int ASCII[][16][8]);
    void print_ASCII(int x, int y, int ASCII, int bg_color, int fg_color);
};

/* Function declarations in lovecode_tools.cpp */
void print_starting_captions(int bg_color = COLOR_HWHITE, int fg_color = COLOR_HWHITE);
void print_elapsed_time(struct system_time& current_time, int bg_color = COLOR_HWHITE, int fg_color = COLOR_HWHITE);
void print_heart_shape(void);
int color(int cycle_index);

#endif // !LOVECODE_H