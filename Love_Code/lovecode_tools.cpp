/****************************************************************
 * Project Name:  Love_Code
 * File Name:     lovecode_tools.cpp
 * File Function: 工具函数的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/11/21
 ****************************************************************/

#include <iostream>
#include <cmath>
#include <Windows.h>
#include <conio.h>
#include "../common/cmd_console_tools.h"
#include "lovecode.h"
#include "pixel_matrixs.h"

/* Namespace */
using namespace std;

/*
 * Function Name:    print_starting_captions
 * Function:         Print starting captions
 * Input Parameters: int bg_color
 *                   int fg_color
 * Return Value:     void
 */
void print_starting_captions(int bg_color, int fg_color)
{
    class pixel_ASCIIs* p_ASCIIs = new(nothrow) class pixel_ASCIIs(pixel_ASCII);
    if (p_ASCIIs == NULL)
        exit(-1);
    for (int i = 0; starting_captions[i][0] >= 0; i++) {
        int j;
        for (j = 0; starting_captions[i][j] >= 0; j++) {
            p_ASCIIs->print_ASCII(ABSCISSA_OF_STARTING_CAPTION + 8 * j, ORDINATE_OF_STARTING_CAPTION + (16 + LINE_SPACE) * i, starting_captions[i][j], bg_color, fg_color);
            p_ASCIIs->print_ASCII(ABSCISSA_OF_STARTING_CAPTION + 8 * (j + 1), ORDINATE_OF_STARTING_CAPTION + (16 + LINE_SPACE) * i, UNDERLINE, bg_color, fg_color);
            if (starting_captions[i][j] != SPACE)
                Sleep(SLEEP_TIME);
        }
        if (starting_captions[i + 1][0] != END) {
            int flicker = 0;
            for (int k = 0; k < FLICKER_TIMES; k++) {
                p_ASCIIs->print_ASCII(ABSCISSA_OF_STARTING_CAPTION + 8 * j, ORDINATE_OF_STARTING_CAPTION + (16 + LINE_SPACE) * i, UNDERLINE, ++flicker % 2 ? bg_color : COLOR_BLACK, flicker % 2 ? fg_color : COLOR_BLACK);
                Sleep(SLEEP_TIME * 5);
            }
        }
        else {
            for (int k = 0; !_kbhit(); k++) {
                p_ASCIIs->print_ASCII(ABSCISSA_OF_STARTING_CAPTION + 8 * j, ORDINATE_OF_STARTING_CAPTION + (16 + LINE_SPACE) * i, UNDERLINE, k % 2 ? bg_color : COLOR_BLACK, k % 2 ? fg_color : COLOR_BLACK);
                Sleep(SLEEP_TIME * 5);
            }
            delete p_ASCIIs;
            cct_setcolor();
            return;
        }
    }
}

/*
 * Function Name:    print_elapsed_time
 * Function:         Print elapsed time
 * Input Parameters: struct system_time& current_tim
 *                   int bg_color
 *                   int fg_color
 * Return Value:     void
 */
void print_elapsed_time(struct system_time& current_time, int bg_color, int fg_color)
{
    /* Save previous time */
    int last_days = current_time.days, last_hours = current_time.hours, last_minutes = current_time.minutes, last_seconds = current_time.seconds;

    /* Update current time */
    time_t t = time(0) - OUR_STORY_BEGINNING;
    current_time.days = int(t / 86400);
    current_time.hours = int((t % 86400) / 3600);
    current_time.minutes = int((t % 3600) / 60);
    current_time.seconds = int(t % 60);

    /* Initialize p_ASCIIs object */
    class pixel_ASCIIs* p_ASCIIs = new(nothrow) class pixel_ASCIIs(pixel_ASCII);
    if (p_ASCIIs == NULL)
        exit(-1);

    /* If seconds change print seconds */
    if (last_seconds != current_time.seconds) {
        p_ASCIIs->print_ASCII(LEFT_INDENT - LEFT_SHIFT_DISTANCE + 8 * 15, ORIGIN_OF_ORDINATE * 2 + 16, current_time.seconds / 10, bg_color, fg_color);
        p_ASCIIs->print_ASCII(LEFT_INDENT - LEFT_SHIFT_DISTANCE + 8 * 16, ORIGIN_OF_ORDINATE * 2 + 16, current_time.seconds % 10, bg_color, fg_color);
    }
    else {
        delete p_ASCIIs;
        return;
    }

    /* If minutes change print minutes */
    if (last_minutes != current_time.minutes) {
        p_ASCIIs->print_ASCII(LEFT_INDENT - LEFT_SHIFT_DISTANCE + 8 * 11, ORIGIN_OF_ORDINATE * 2 + 16, current_time.minutes / 10, bg_color, fg_color);
        p_ASCIIs->print_ASCII(LEFT_INDENT - LEFT_SHIFT_DISTANCE + 8 * 12, ORIGIN_OF_ORDINATE * 2 + 16, current_time.minutes % 10, bg_color, fg_color);
    }
    else {
        delete p_ASCIIs;
        return;
    }

    /* If hours change print hours */
    if (last_hours != current_time.hours) {
        p_ASCIIs->print_ASCII(LEFT_INDENT - LEFT_SHIFT_DISTANCE + 8 * 7, ORIGIN_OF_ORDINATE * 2 + 16, current_time.hours / 10, bg_color, fg_color);
        p_ASCIIs->print_ASCII(LEFT_INDENT - LEFT_SHIFT_DISTANCE + 8 * 8, ORIGIN_OF_ORDINATE * 2 + 16, current_time.hours % 10, bg_color, fg_color);
    }
    else {
        delete p_ASCIIs;
        return;
    }

    /* If days change print days */
    if (last_days != current_time.days) {
        p_ASCIIs->print_ASCII(LEFT_INDENT - LEFT_SHIFT_DISTANCE + 8 * 0, ORIGIN_OF_ORDINATE * 2 + 16, (current_time.days / 10000), bg_color, fg_color);
        p_ASCIIs->print_ASCII(LEFT_INDENT - LEFT_SHIFT_DISTANCE + 8 * 1, ORIGIN_OF_ORDINATE * 2 + 16, (current_time.days / 1000) % 10, bg_color, fg_color);
        p_ASCIIs->print_ASCII(LEFT_INDENT - LEFT_SHIFT_DISTANCE + 8 * 2, ORIGIN_OF_ORDINATE * 2 + 16, (current_time.days / 100) % 10, bg_color, fg_color);
        p_ASCIIs->print_ASCII(LEFT_INDENT - LEFT_SHIFT_DISTANCE + 8 * 3, ORIGIN_OF_ORDINATE * 2 + 16, (current_time.days / 10) % 10, bg_color, fg_color);
        p_ASCIIs->print_ASCII(LEFT_INDENT - LEFT_SHIFT_DISTANCE + 8 * 4, ORIGIN_OF_ORDINATE * 2 + 16, current_time.days % 10, bg_color, fg_color);
    }
    else {
        delete p_ASCIIs;
        return;
    }
}

/*
 * Function Name:    print_heart_shape
 * Function:         Print heart shape
 * Input Parameters: void
 * Return Value:     void
 */
void print_heart_shape(void)
{
    /* Initialize characters object and print pixel characters */
    class pixel_characters characters[13] = { pixel_characters(pixel_ling), pixel_characters(pixel_yang),pixel_characters(pixel_yi_first), pixel_characters(pixel_zhi), pixel_characters(pixel_pa), pixel_characters(pixel_qia), pixel_characters(pixel_gou), pixel_characters(pixel_yi_third), pixel_characters(pixel_jing), pixel_characters(pixel_tian), pixel_characters(pixel_shi), pixel_characters(pixel_fen), pixel_characters(pixel_miao) };
    for (int i = 0; i < 9; i++)
        characters[i].print_character(LEFT_INDENT + 16 * i, ORIGIN_OF_ORDINATE * 2 - LINE_SPACE, COLOR_HWHITE, COLOR_HWHITE);
    for (int i = 0; i < 4; i++)
        characters[i + 9].print_character(LEFT_INDENT - LEFT_SHIFT_DISTANCE + 8 * (5 + 4 * i), ORIGIN_OF_ORDINATE * 2 + 16, COLOR_HWHITE, COLOR_HWHITE);

    /* Initialize current_time object and print current time */
    struct system_time current_time;
    print_elapsed_time(current_time);

    /* Print heart shape cyclically */
    int k = -1;
    for (EVER) {
        /* Record cycle index */
        k++;

        /* Print heart shape once */
        for (int j = 0; j < CYCLE_INDEX; j++) {
            /* Initialize point_set objects */
            class point_set* p_expend = new(nothrow) class point_set[MAGNIFICATION * POINT_SET_DENSITY];
            if (p_expend == NULL)
                exit(-1);
            class point_set* p_shrink = new(nothrow) class point_set[MAGNIFICATION * POINT_SET_DENSITY];
            if (p_shrink == NULL)
                exit(-1);
            for (int i = 0; i < MAGNIFICATION * POINT_SET_DENSITY; i++) {
                p_expend[i].point_initialize(i * MAGNIFICATION, i / double(POINT_SET_DENSITY));
                p_shrink[i].point_initialize(i * MAGNIFICATION, i / double(POINT_SET_DENSITY));
            }

            /* Print internal graphics amplification process */
            if (!j) {
                for (int i = 0; i < SHRINK_BOUNDARIES; i++) {
                    p_expend[i].print_heart(color(k), color(k));
                    print_elapsed_time(current_time);
                }
            }

            /* Print external graphics amplification process */
            for (int i = SHRINK_BOUNDARIES; i < MAGNIFICATION * POINT_SET_DENSITY; i++) {
                p_expend[i].print_heart(color(k), color(k));
                if (rand() % FLICKER_PROBABILITY)
                    p_expend[rand() % SHRINK_BOUNDARIES].print_heart(COLOR_BLACK, COLOR_BLACK);
                else
                    p_expend[rand() % SHRINK_BOUNDARIES].print_heart(color(k), color(k));
                print_elapsed_time(current_time);
            }

            /* Print external graphics contraction process */
            for (int i = MAGNIFICATION * POINT_SET_DENSITY - 1; i >= SHRINK_BOUNDARIES; i--) {
                p_expend[i].print_heart(COLOR_BLACK, COLOR_BLACK);
                if (rand() % FLICKER_PROBABILITY)
                    p_shrink[rand() % SHRINK_BOUNDARIES].print_heart(COLOR_BLACK, COLOR_BLACK);
                else
                    p_shrink[rand() % SHRINK_BOUNDARIES].print_heart(color(k), color(k));
                print_elapsed_time(current_time);
            }

            /* Print internal graphics contraction process */
            if (j == CYCLE_INDEX - 1) {
                class point_set* p_shrink_fullfit = new(nothrow) class point_set[MAGNIFICATION * POINT_SET_DENSITY];
                if (p_shrink_fullfit == NULL)
                    exit(-1);
                for (int i = 0; i < SHRINK_BOUNDARIES; i++)
                    p_shrink_fullfit[i].point_initialize(i * MAGNIFICATION, i / double(POINT_SET_DENSITY), FULL_FIT);
                for (int i = SHRINK_BOUNDARIES - 1; i >= 0; i--) {
                    p_shrink_fullfit[i].print_heart(COLOR_BLACK, COLOR_BLACK);
                    print_elapsed_time(current_time);
                }
                delete[] p_expend, p_shrink, p_shrink_fullfit;
            }
        }
    }
}

/*
 * Function Name:    color
 * Function:         Return color
 * Input Parameters: int cycle_index
 * Return Value:     color
 */
int color(int cycle_index)
{
    return (cycle_index + 3) % 7 + (rand() % 2) * 8 + 1;
}