/****************************************************************
 * Project Name:  Gluttonous_Snake
 * File Name:     gluttonous_snake_menu.cpp
 * File Function: 菜单函数的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/9/30
 ****************************************************************/

#include <conio.h>
#include "gluttonous_snake.h"

using namespace std;

/* Define static variable */
static bool menuFlag = false;

/*
 * Function Name:    isPointInRect
 * Function:         Check if a point is in a rectangular range
 * Input Parameters: int x
 *                   int y
 *                   int top
 *                   int bottom
 *                   int left
 *                   int right
 * Return Value:     true / false
 */
static bool isPointInRect(int x, int y, int top, int bottom, int left = 554, int right = 981)
{
    return (x >= left && x <= right && y >= top && y <= bottom);
}

/*
 * Function Name:    startPage
 * Function:         Display start page
 * Input Parameters: void
 * Return Value:     void
 */
void startPage(void)
{
    initgraph(menuWidth, menuHeight);
    HWND hwnd = GetHWnd();
    SetWindowText(hwnd, _T("Gluttonous Snake"));
    IMAGE img;
    loadimage(&img, _T("data/start_page.png"));
    putimage(0, 0, &img);
    Sleep(startTime);
}

/*
 * Function Name:    menu
 * Function:         Display menu items and read the correct option
 * Input Parameters: void
 * Return Value:     mode
 */
Mode menu(void)
{
    /* Display menu page */
    if (menuFlag) {
        initgraph(menuWidth, menuHeight);
        HWND hwnd = GetHWnd();
        SetWindowText(hwnd, _T("Gluttonous Snake"));
    }
    menuFlag = true;
    IMAGE img;
    loadimage(&img, _T("data/menu_page.png"));
    putimage(0, 0, &img);

    /* Read mouse events */
    MOUSEMSG m{ 0 };
    while (true) {
        if (MouseHit())
            m = GetMouseMsg();
        switch (m.uMsg) {
            case WM_LBUTTONDOWN:
                if (isPointInRect(m.x, m.y, 105, 150)) {
                    loadimage(&img, _T("data/basic_mode_page.png"));
                    putimage(0, 0, &img);
                    while (_getch() != ' ')
                        continue;
                    return BasicMode;
                }
                else if (isPointInRect(m.x, m.y, 161, 206)) {
                    loadimage(&img, _T("data/advanced_mode_page.png"));
                    putimage(0, 0, &img);
                    while (_getch() != ' ')
                        continue;
                    return AdvancedMode;
                }
                else if (isPointInRect(m.x, m.y, 216, 261)) {
                    loadimage(&img, _T("data/expert_mode_page.png"));
                    putimage(0, 0, &img);
                    while (_getch() != ' ')
                        continue;
                    return ExpertMode;
                }
                else if (isPointInRect(m.x, m.y, 272, 317)) {
                    loadimage(&img, _T("data/human_vs_human_mode_page.png"));
                    putimage(0, 0, &img);
                    while (_getch() != ' ')
                        continue;
                    return HumanVsHumanMode;
                }
                else if (isPointInRect(m.x, m.y, 327, 373)) {
                    loadimage(&img, _T("data/human_vs_AI_mode_page.png"));
                    putimage(0, 0, &img);
                    while (_getch() != ' ')
                        continue;
                    return HumanVsAIMode;
                }
                else if (isPointInRect(m.x, m.y, 383, 428)) {
                    loadimage(&img, _T("data/AI_vs_AI_mode_page.png"));
                    putimage(0, 0, &img);
                    while (_getch() != ' ')
                        continue;
                    return AIVsAIMode;
                }
                else if (isPointInRect(m.x, m.y, 438, 484)) {
                    resetHighestScore();
                    loadimage(&img, _T("data/reset_highest_score_page.png"));
                    putimage(0, 0, &img);
                    menuFlag = false;
                    while (_getch() != ' ')
                        continue;
                    return ResetHighestScore;
                }
                else if (isPointInRect(m.x, m.y, 438, 484, 42, 118))
                    return Quit;
                break;
            default:
                break;
        }
    }
}

/*
 * Function Name:    endPage
 * Function:         Display end page
 * Input Parameters: EndPageCategory endPageCategory
 * Return Value:     void
 */
void endPage(EndPageCategory endPageCategory)
{
    IMAGE img;
    switch (endPageCategory) {
        case PageDefault:
            loadimage(&img, _T("data/default_end_page.png"));
            break;
        case PageHumanSnakeA:
            loadimage(&img, _T("data/human_snake_A_end_page.png"));
            break;
        case PageHumanSnakeB:
            loadimage(&img, _T("data/human_snake_B_end_page.png"));
            break;
        case PageAISnakeA:
            loadimage(&img, _T("data/AI_snake_A_end_page.png"));
            break;
        case PageAISnakeB:
            loadimage(&img, _T("data/AI_snake_B_end_page.png"));
            break;
        default:
            exit(-1);
    }
    int x = (getwidth() - img.getwidth()) / 2, y = (getheight() - img.getheight()) / 2;
    putimage(x, y, &img);
    while (_getch() != ' ')
        continue;
}