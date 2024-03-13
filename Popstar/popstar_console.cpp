/****************************************************************
 * Project Name:  Popstar
 * File Name:     popstar_console.cpp
 * File Function: 伪图形界面方式函数的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/11/21
 ****************************************************************/

#include <iostream>
#include <iomanip>
#include <Windows.h>
#include "../common/cmd_console_tools.h"
#include "popstar.h"

/* Namespace */
using namespace std;

/*
 * Function Name:    console_select
 * Function:         Executing menu item D / E
 * Input Parameters: int divider_or_not
 * Return Value:     void
 */
void console_select(int divider_or_not)
{
    /* Initialize */
    int row, column, select_r = 0, select_c = 0, matrix[10][10] = { 0 }, X = 4, Y = 3;

    /* Enter the number of rows and columns */
    parameters_input(row, column);
    
    /* Initialize the pseudo-graphical interface */
    graphical_initialize(matrix, row, column, divider_or_not);

    /* Keyboard and mouse operations */
    mouse_and_keyboard_operations(matrix, row, column, X, Y, select_r, select_c, divider_or_not, NON_ELIMINATION);
}

/*
 * Function Name:    console_eliminate
 * Function:         Executing menu item F
 * Input Parameters: int divider_or_not
 * Return Value:     void
 */
void console_eliminate(int divider_or_not)
{
    /* Initialize */
    int row, column, select_r = 0, select_c = 0, matrix[10][10] = { 0 }, judgment_array[12][12] = { 0 }, X = 4, Y = 3, loop1 = 1;

    /* Enter the number of rows and columns */
    parameters_input(row, column);

    /* Initialize the pseudo-graphical interface */
    graphical_initialize(matrix, row, column, divider_or_not);

    /* Complete one elimination */
    while (loop1) {
        /* Determine if the game is over */
        if (mouse_and_keyboard_operations(matrix, row, column, X, Y, select_r, select_c, divider_or_not, ELIMINATION) == 0) {
            clear_information(row, column, divider_or_not);
            cct_disable_mouse();
            cct_setcursor(CURSOR_VISIBLE_NORMAL);
            return;
        }

        /* Count the number of consecutive identical values and merge them together */
        judgment_synthesis(matrix, judgment_array, row, column, select_r, select_c, divider_or_not);

        /* Keyboard and mouse operations */
        int _select_r, _select_c, ret, maction, keycode1, keycode2, loop2 = 1;
        cct_enable_mouse();
        cct_setcursor(CURSOR_INVISIBLE);
        while (loop2) {
            /* Read mouse and keyboard inputs */
            _select_r = select_r;
            _select_c = select_c;
            ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);

            /* Move coordinates using keyboard arrow keys */
            move_coordinate_keyboard(matrix, row, column, select_r, select_c, ret, keycode1, keycode2, X, Y, divider_or_not);

            /* Cancel the highlighting and print the current operation */
            print_nonReverse_current(matrix, judgment_array, row, column, ret, keycode1, keycode2, X, Y, select_r, select_c, _select_r, _select_c, loop2, divider_or_not, TRANSFORMATION);
            if (ret == CCT_MOUSE_EVENT) {
                switch (maction) {
                    case MOUSE_LEFT_BUTTON_CLICK:
                    case MOUSE_LEFT_BUTTON_DOUBLE_CLICK:
                        if (judgment_continuity(matrix, judgment_array, row, column, select_r, select_c) != 1) {
                            synthesize_drop(matrix, judgment_array, row, column, divider_or_not, NON_FULLVERSION);
                            loop1 = 0;
                            loop2 = 0;
                        }
                        break;
                    case MOUSE_RIGHT_BUTTON_CLICK:
                    case MOUSE_RIGHT_BUTTON_DOUBLE_CLICK:
                        clear_information(row, column, divider_or_not);
                        loop1 = 0;
                        loop2 = 0;
                        break;
                    default:
                        break;
                } // end of switch (maction)
            } // end of if (ret == CCT_MOUSE_EVENT)
            else if (ret == CCT_KEYBOARD_EVENT) {
                switch (keycode1) {
                    case '\r':
                        if (judgment_continuity(matrix, judgment_array, row, column, select_r, select_c) != 1) {
                            synthesize_drop(matrix, judgment_array, row, column, divider_or_not, NON_FULLVERSION);
                            loop1 = 0;
                            loop2 = 0;
                        }
                        break;
                    case 'Q':
                    case 'q':
                        clear_information(row, column, divider_or_not);
                        loop1 = 0;
                        loop2 = 0;
                        break;
                    default:
                        break;
                } // end of switch (keycode1)
            } // end of else if (ret == CCT_KEYBOARD_EVENT)
        } // end of while (loop2)
        cct_disable_mouse();
        cct_setcursor(CURSOR_VISIBLE_NORMAL);
    } // end of while (loop1)
}

/*
 * Function Name:    console_fullVersion
 * Function:         Executing menu item G
 * Input Parameters: int divider_or_not
 * Return Value:     void
 */
void console_fullVersion(int divider_or_not)
{
    /* Initialize */
    int row, column, select_r = 0, select_c = 0, matrix[10][10] = { 0 }, judgment_array[12][12] = { 0 }, X = 4, Y = 3, score_bound = 0, score_total = 0, score_reward = 0, loop3 = 1;

    /* Enter the number of rows and columns */
    parameters_input(row, column);

    /* Full version of the pseudo-graphical interface */
    while (loop3) {
        /* Initialize the pseudo-graphical interface */
        graphical_initialize(matrix, row, column, divider_or_not);

        /* Complete one level */
        int loop4 = 1;
        while (loop4) {
            /* Calculate and print the bonus score and total score */
            if (!print_score_level(matrix, row, column, score_reward, score_total, divider_or_not))
                break;

            /* Complete one elimination */
            int num, loop1 = 1;
            while (loop1) {
                /* Determine if the game is over */
                if (mouse_and_keyboard_operations(matrix, row, column, X, Y, select_r, select_c, divider_or_not, ELIMINATION) == 0) {
                    clear_information(row, column, divider_or_not);
                    cct_disable_mouse();
                    cct_setcursor(CURSOR_VISIBLE_NORMAL);
                    return;
                }

                /* Count the number of consecutive identical values and merge them together */
                judgment_synthesis(matrix, judgment_array, row, column, select_r, select_c, divider_or_not);

                /* Keyboard and mouse operations */
                int _select_r, _select_c, ret, maction, keycode1, keycode2;
                cct_enable_mouse();
                cct_setcursor(CURSOR_INVISIBLE);
                int loop2 = 1;
                while (loop2) {
                    /* Read mouse and keyboard inputs */
                    _select_r = select_r;
                    _select_c = select_c;
                    ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);

                    /* Move coordinates using keyboard arrow keys */
                    move_coordinate_keyboard(matrix, row, column, select_r, select_c, ret, keycode1, keycode2, X, Y, divider_or_not);

                    /* Cancel the highlighting and print the current operation */
                    print_nonReverse_current(matrix, judgment_array, row, column, ret, keycode1, keycode2, X, Y, select_r, select_c, _select_r, _select_c, loop2, divider_or_not, TRANSFORMATION);
                    if (ret == CCT_MOUSE_EVENT) {
                        switch (maction) {
                            case MOUSE_LEFT_BUTTON_CLICK:
                            case MOUSE_LEFT_BUTTON_DOUBLE_CLICK:
                                calculate_print_score(matrix, judgment_array, row, column, select_r, select_c, score_bound, score_total, num, loop1, loop2, divider_or_not);
                                if (!judgment_legality(matrix, row, column, X, Y, select_r, select_c, divider_or_not, NON_TRANSFORMATION)) {
                                    int i;
                                    for (i = 0; i < row; i++) {
                                        if (matrix[i][0])
                                            break;
                                    }
                                    X = 4;
                                    Y = 3 + 4 * i;
                                }
                                break;
                            case MOUSE_RIGHT_BUTTON_CLICK:
                            case MOUSE_RIGHT_BUTTON_DOUBLE_CLICK:
                                clear_information(row, column, divider_or_not);
                                loop1 = 0;
                                loop2 = 0;
                                loop3 = 0;
                                loop4 = 0;
                                break;
                            default:
                                break;
                        } // end of switch (maction)
                    } // end of if (ret == CCT_MOUSE_EVENT)
                    else if (ret == CCT_KEYBOARD_EVENT) {
                        switch (keycode1) {
                            case '\r':
                                calculate_print_score(matrix, judgment_array, row, column, select_r, select_c, score_bound, score_total, num, loop1, loop2, divider_or_not);
                                int i;
                                for (i = 0; i < row; i++) {
                                    if (matrix[i][0])
                                        break;
                                }
                                X = 4;
                                Y = 3 + 4 * i;
                                break;
                            case 'Q':
                            case 'q':
                                clear_information(row, column, divider_or_not);
                                loop1 = 0;
                                loop2 = 0;
                                loop3 = 0;
                                loop4 = 0;
                            default:
                                break;
                        } // end of switch (keycode1)
                    } // end of else if (ret == CCT_KEYBOARD_EVENT)
                } // end of while (loop2)
                cct_disable_mouse();
                cct_setcursor(CURSOR_VISIBLE_NORMAL);
            } // end of while (loop1)
        } // end of while (true)
    } // end of while (loop)
}

/*
 * Function Name:    print_frame
 * Function:         Print frame
 * Input Parameters: int row
 *                   int column
 *                   int divider_or_not
 * Return Value:     void
 */
void print_frame(int row, int column, int divider_or_not)
{
    /* Print the number of rows */
    for (int i = 0; i < column; i++)
        cct_showint((divider_or_not ? 8 * i + 6 : 6 * i + 6), 1, i, COLOR_BLACK, COLOR_WHITE, 1);

    /* Print the first row */
    cct_showstr(2, 2, "╔", COLOR_HWHITE, COLOR_BLACK, 1, -1);
    for (int i = 0; i < column; i++) {
        cct_showstr((divider_or_not ? 8 * i + 4 : 6 * i + 4), 2, (divider_or_not ? "═══╦" : "═══"), COLOR_HWHITE, COLOR_BLACK, 1, -1);
        if (i % 2)
            Sleep(SLEEP_TIME_FRAME);
    }
    cct_showstr((divider_or_not ? 8 * column + 2 : 6 * column + 4), 2, "╗", COLOR_HWHITE, COLOR_BLACK, 1, -1);

    /* Print the middle rows */
    for (int i = 0; i < row; i++) {
        /* Print the non-delimiter row */
        for (int j = 0; j < 3; j++) {
            if (j == 1)
                cct_showch(0, 4 + (divider_or_not + 3) * i, char(i + 'A'), COLOR_BLACK, COLOR_WHITE, 1);
            cct_showstr(2, 3 + j + (divider_or_not + 3) * i, "║", COLOR_HWHITE, COLOR_BLACK, 1, -1);
            for (int k = 0; k < column; k++) {
                cct_showstr((divider_or_not ? 8 * k + 4 : 6 * k + 4), 3 + j + (divider_or_not + 3) * i, (divider_or_not ? "      ║" : "      "), COLOR_HWHITE, COLOR_BLACK, 1, -1);
                if (k % 2)
                    Sleep(SLEEP_TIME_FRAME);
            }
            cct_showstr((divider_or_not ? 8 * column + 2 : 6 * column + 4), 3 + j + (divider_or_not + 3) * i, "║", COLOR_HWHITE, COLOR_BLACK, 1, -1);
        } // end of for

        /* Print the delimiter row */
        if (divider_or_not && i != row - 1) {
            cct_showstr(2, 4 * i + 6, "╠", COLOR_HWHITE, COLOR_BLACK, 1, -1);
            for (int j = 0; j < column; j++) {
                cct_showstr((divider_or_not ? 8 * j + 4 : 6 * j + 4), 4 * i + 6, (divider_or_not ? "═══╬" : "═══"), COLOR_HWHITE, COLOR_BLACK, 1, -1);
                if (j % 2)
                    Sleep(SLEEP_TIME_FRAME);
            }
            cct_showstr((divider_or_not ? 8 * column + 2 : 6 * column + 4), 4 * i + 6, "╣", COLOR_HWHITE, COLOR_BLACK, 1, -1);
        } // end of if (divider_or_not)
    } // end of for

    /* Print the last row */
    cct_showstr(2, (divider_or_not + 3) * (row - 1) + 6, "╚", COLOR_HWHITE, COLOR_BLACK, 1, -1);
    for (int j = 0; j < column; j++) {
        cct_showstr((divider_or_not ? 8 * j + 4 : 6 * j + 4), (divider_or_not + 3) * (row - 1) + 6, (divider_or_not ? "═══╩" : "═══"), COLOR_HWHITE, COLOR_BLACK, 1, -1);
        if (j % 2)
            Sleep(SLEEP_TIME_FRAME);
    }
    cct_showstr((divider_or_not ? 8 * column + 2 : 6 * column + 4), (divider_or_not + 3) * (row - 1) + 6, "╝", COLOR_HWHITE, COLOR_BLACK, 1, -1);

    /* Print the prompt message */
    cct_setcolor();
    cout << endl << "箭头键/鼠标移动，回车键/单击左键选择并结束";
    cct_gotoxy(0, 0);
    cout << "屏幕当前设置为：" << 3 * row + 8 + divider_or_not * (row - 1) << "行" << 6 * column + 7 + divider_or_not * (column - 1) * 2 << "列";
}

/*
 * Function Name:    print_block_initial
 * Function:         Print all initial color blocks
 * Input Parameters: int matrix[][10]
 *                   int row
 *                   int column
 *                   int divider_or_not
 *                   int width
 *                   int height
 * Return Value:     void
 */
void print_block_initial(int matrix[][10], int row, int column, int divider_or_not, int width, int height)
{
    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
            print_block(matrix, i, j, divider_or_not, COLOR_BLACK, width, height, COORDINATE_LOCK, COORDINATE_LOCK, COORDINATE_LOCK);
}

/*
 * Function Name:    print_block
 * Function:         Print a block
 * Input Parameters: int matrix[][10]
 *                   int i
 *                   int j
 *                   int divider_or_not
 *                   int color
 *                   int width
 *                   int height
 *                   int x
 *                   int y
 *                   int lock_or_not
 * Return Value:     void
 */
void print_block(int matrix[][10], int i, int j, int divider_or_not, int color, int width, int height, int x, int y, int lock_or_not)
{
    /* Set the print color */
    cct_setcolor(matrix[i][j] ? matrix[i][j] + 8 : COLOR_HWHITE, matrix[i][j] ? color : COLOR_HWHITE);

    /* Print the first row of color blocks */
    if (lock_or_not)
        cct_gotoxy(4 + width * j + 2 * divider_or_not * j, 3 + height * i + divider_or_not * i);
    else
        cct_gotoxy(x, y);
    cout << "┏";
    for (int k = 0; k < width / 2 - 2; k++)
        cout << "━";
    cout << "┓";

    /* Print the middle row of color blocks */
    for (int k = 0; k < width / 2 - 2; k++) {
        if (lock_or_not)
            cct_gotoxy(4 + width * j + 2 * divider_or_not * j, 3 + height * i + divider_or_not * i + k + 1);
        else
            cct_gotoxy(x, y + 1);
        cout << "┃";
        for (int m = 0; m < width / 2 - 2; m++)
            cout << "★";
        cout << "┃";
    }

    /* Print the last row of color blocks */
    if (lock_or_not)
        cct_gotoxy(4 + width * j + 2 * divider_or_not * j, 3 + height * i + divider_or_not * i + height - 1);
    else
        cct_gotoxy(x, y + 2);
    cout << "┗";
    for (int k = 0; k < width / 2 - 2; k++)
        cout << "━";
    cout << "┛";

    /* Set the default print color */
    cct_setcolor();
}

/*
 * Function Name:    mouse_and_keyboard_operations
 * Function:         Use keyboard and mouse operations to obtain the number of rows and columns
 * Input Parameters: int matrix[][10]
 *                   int row
 *                   int column
 *                   int& X
 *                   int& Y
 *                   int& select_r
 *                   int& select_c
 *                   int divider_or_not
 *                   int eliminate_or_not
 * Return Value:     0 - End the game
 *                   1 - Continue the game
 */
int mouse_and_keyboard_operations(int matrix[][10], int row, int column, int& X, int& Y, int& select_r, int& select_c, int divider_or_not, int eliminate_or_not)
{
    /* Initialize */
    int _select_r, _select_c, ret, maction, keycode1, keycode2;

    /* Enable mouse and cursor settings */
    cct_enable_mouse();
    cct_setcursor(CURSOR_INVISIBLE);

    /* Mouse and keyboard operations */
    while (true) {
        /* Reverse display */
        if (judgment_legality(matrix, row, column, X, Y, select_r, select_c, divider_or_not, TRANSFORMATION))
            print_block(matrix, select_r, select_c, divider_or_not, COLOR_WHITE, BLOCK_WIDTH, BLOCK_HEIGHT, COORDINATE_LOCK, COORDINATE_LOCK, COORDINATE_LOCK);

        /* Save current state */
        _select_r = select_r;
        _select_c = select_c;

        /* Read mouse and keyboard inputs */
        ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);

        /* End the game */
        if ((ret == CCT_KEYBOARD_EVENT && keycode1 == 'Q' || ret == CCT_KEYBOARD_EVENT && keycode1 == 'q') && eliminate_or_not)
            return print_selected_or_exit(row, column, select_r, select_c, divider_or_not, END_GAME);

        /* Move the coordinates using the arrow keys on the keyboard */
        move_coordinate_keyboard(matrix, row, column, select_r, select_c, ret, keycode1, keycode2, X, Y, divider_or_not);

        /* Cancel reverse display */
        if (!judgment_legality(matrix, row, column, X, Y, select_r, select_c, divider_or_not, TRANSFORMATION) || _select_r != select_r || _select_c != select_c)
            print_block(matrix, _select_r, _select_c, divider_or_not, COLOR_BLACK, BLOCK_WIDTH, BLOCK_HEIGHT, COORDINATE_LOCK, COORDINATE_LOCK, COORDINATE_LOCK);

        /* Mouse and keyboard operations */
        if (ret == CCT_MOUSE_EVENT) {
            print_current(matrix, row, column, X, Y, select_r, select_c, "鼠标", divider_or_not);
            switch (maction) {
                case MOUSE_LEFT_BUTTON_CLICK:
                case MOUSE_LEFT_BUTTON_DOUBLE_CLICK:
                    if (judgment_legality(matrix, row, column, X, Y, select_r, select_c, divider_or_not, NON_TRANSFORMATION))
                        return print_selected_or_exit(row, column, select_r, select_c, divider_or_not, CONTINUE_GAME);
                    break;
                case MOUSE_RIGHT_BUTTON_CLICK:
                case MOUSE_RIGHT_BUTTON_DOUBLE_CLICK:
                    if (judgment_legality(matrix, row, column, X, Y, select_r, select_c, divider_or_not, NON_TRANSFORMATION))
                        return eliminate_or_not ? 0 : print_selected_or_exit(row, column, select_r, select_c, divider_or_not, CONTINUE_GAME);
                    break;
                default:
                    break;
            } // end of switch (maction)
        } // end of if (ret == CCT_MOUSE_EVENT)
        else if (ret == CCT_KEYBOARD_EVENT) {
            if (keycode1 == 224 && (keycode2 == KB_ARROW_DOWN || keycode2 == KB_ARROW_LEFT || keycode2 == KB_ARROW_RIGHT || keycode2 == KB_ARROW_UP))
                print_current(matrix, row, column, X, Y, select_r, select_c, "键盘", divider_or_not);
            switch (keycode1) {
                case 'Q':
                case 'q':
                case '\r':
                    return print_selected_or_exit(row, column, select_r, select_c, divider_or_not, CONTINUE_GAME);
                default:
                    break;
            } // end of switch (keycode1)
        } // end of else if (ret == CCT_KEYBOARD_EVENT)
    }
}

/*
 * Function Name:    clear_information
 * Function:         Clear the prompt message
 * Input Parameters: int row
 *                   int column
 *                   int divider_or_not
 * Return Value:     void
 */
void clear_information(int row, int column, int divider_or_not)
{
    cct_showch(0, 3 * row + 4 + divider_or_not * (row - 1), ' ', COLOR_BLACK, COLOR_WHITE, 6 * column + 7 + divider_or_not * (column - 1) * 2);
    cct_gotoxy(0, 3 * row + 4 + divider_or_not * (row - 1));
}

/*
 * Function Name:    judgment_legality
 * Function:         Check the legality of the coordinate position
 * Input Parameters: int matrix[][10]
 *                   int row
 *                   int column
 *                   int X
 *                   int Y
 *                   int& select_r
 *                   int& select_c
 *                   int divider_or_not
 *                   int trans_or_not
 * Return Value:     0 - Coordinate position is illegal
 *                   1 - Coordinate position is legal
 */
int judgment_legality(int matrix[][10], int row, int column, int X, int Y, int& select_r, int& select_c, int divider_or_not, int trans_or_not)
{
    /* Initialize the old rows and columns */
    int _select_r = 0, _select_c = 0;

    /* Check the legality of the coordinate position */
    if (divider_or_not) { // With dividing lines
        get_row_column(row, column, X, Y, _select_r, _select_c, divider_or_not); // Get the old rows and columns
        if (X >= 4 && Y >= 3 && X <= 3 + 6 * column + 2 * (column - 1) && Y <= 2 + 3 * row + (row - 1) && (X - 2) % 8 != 0 && (X - 2) % 8 != 1 && (Y - 2) % 4 != 0 && matrix[_select_r][_select_c] != 0) { // Coordinate position is legal
            if (trans_or_not)
                get_row_column(row, column, X, Y, select_r, select_c, divider_or_not); // Get the new rows and columns
            return 1;
        }
        else { // Coordinate position is illegal
            return 0;
        }
    } // end of if (divider_or_not)
    else { // Without dividing lines
        get_row_column(row, column, X, Y, _select_r, _select_c, divider_or_not); // Get the old rows and columns
        if (X >= 4 && Y >= 3 && X <= 3 + 6 * column && Y <= 2 + 3 * row && matrix[_select_r][_select_c] != 0) { // Coordinate position is legal
            if (trans_or_not)
                get_row_column(row, column, X, Y, select_r, select_c, divider_or_not); //Get the new rows and columns
            return 1;
        }
        else { // Coordinate position is illegal
            return 0;
        }
    } // end of else
}

/*
 * Function Name:    print_current
 * Function:         Print the current mouse or keyboard operation
 * Input Parameters: int matrix[][10]
 *                   int row
 *                   int column
 *                   int X
 *                   int Y
 *                   int select_r
 *                   int select_c
 *                   const char prompt[]
 *                   int divider_or_not
 * Return Value:     void
 */
void print_current(int matrix[][10], int row, int column, int X, int Y, int select_r, int select_c, const char prompt[], int divider_or_not)
{
    cct_showstr(0, 3 * row + 4 + divider_or_not * (row - 1), "[当前", COLOR_BLACK, COLOR_WHITE, 1 - 1);
    cout << prompt << "] ";
    if (judgment_legality(matrix, row, column, X, Y, select_r, select_c, divider_or_not, TRANSFORMATION)) { // Coordinate position is legal
        cct_setcolor(COLOR_BLACK, COLOR_HGREEN);
        cout << char(select_r + 'A') << "行" << select_c << "列" << setw(6 * column + 7 + divider_or_not * (column - 1) * 2 - 17) << "";
    }
    else { // Coordinate position is illegal
        cct_setcolor(COLOR_BLACK, COLOR_HRED);
        cout << "位置非法" << setw(6 * column + 7 + divider_or_not * (column - 1) * 2 - 19) << "";
    }
    cct_setcolor();
}


/*
 * Function Name:    synthesize_drop
 * Function:         Composite and fall continuous same values
 * Input Parameters: int matrix[][10]
 *                   int judgment_array[][12]
 *                   int row
 *                   int column
 *                   int divider_or_not
 *                   int fullVersion_or_not
 * Return Value:     void
 */
void synthesize_drop(int matrix[][10], int judgment_array[][12], int row, int column, int divider_or_not, int fullVersion_or_not)
{
    /* Merge arrays with the same values */
    array_incorporate(matrix, judgment_array, row, column);
    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
            if (matrix[i][j] == 0) {
                print_block(matrix, i, j, divider_or_not, COLOR_HWHITE, BLOCK_WIDTH, BLOCK_HEIGHT, COORDINATE_LOCK, COORDINATE_LOCK, COORDINATE_LOCK);
                Sleep(SLEEP_TIME_BLOCK);
            }

    /* Print prompt message */
    clear_information(row, column, divider_or_not);
    cout << "合成完成，回车键/单击左键下落0";

    /* Keyboard and mouse operations */
    int X, Y, ret, maction, keycode1, keycode2, loop = 1;
    cct_enable_mouse();
    cct_setcursor(CURSOR_INVISIBLE);
    while (loop) {
        ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
        if (ret == CCT_MOUSE_EVENT) {
            switch (maction) {
                case MOUSE_LEFT_BUTTON_CLICK:
                case MOUSE_LEFT_BUTTON_DOUBLE_CLICK:
                    array_translation(matrix, row, column, GRAPHICAL_INTERFACE, divider_or_not);
                    loop = 0;
                    break;
                default:
                    break;
            }
        } // end of if (ret == CCT_MOUSE_EVENT)
        else if (ret == CCT_KEYBOARD_EVENT) {
            switch (keycode1) {
                case '\r':
                    array_translation(matrix, row, column, GRAPHICAL_INTERFACE, divider_or_not);
                    loop = 0;
                    break;
                default:
                    break;
            }
        } // end of else if (ret == CCT_KEYBOARD_EVENT)
    } // end of while (loop)

    /* Print prompt message */
    clear_information(row, column, divider_or_not);
    cout << "本次合成结束，按C/单击左键继续新一次的合成";

    /* Keyboard and mouse operations */
    loop = 1;
    while (loop) {
        ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
        if (ret == CCT_MOUSE_EVENT) {
            switch (maction) {
                case MOUSE_LEFT_BUTTON_CLICK:
                case MOUSE_LEFT_BUTTON_DOUBLE_CLICK:
                    loop = 0;
                    break;
                default:
                    break;
            }
        } // end of if (ret == CCT_MOUSE_EVENT)
        else if (ret == CCT_KEYBOARD_EVENT) {
            switch (keycode1) {
                case 'C':
                case 'c':
                    loop = 0;
                    break;
                default:
                    break;
            }
        } // end of else if (ret == CCT_KEYBOARD_EVENT)
    } // end of while (loop)
    cct_disable_mouse();
    cct_setcursor(CURSOR_VISIBLE_NORMAL);

    /* Clear prompt message */
    clear_information(row, column, divider_or_not);
}

/*
 * Function Name:    print_move_vertical
 * Function:         Print the vertical movement process of color blocks
 * Input Parameters: int matrix[][10]
 *                   int src_r
 *                   int src_c
 *                   int len
 *                   int divider_or_not
 * Return Value:     void
 */
void print_move_vertical(int matrix[][10], int src_r, int src_c, int len, int divider_or_not)
{
    for (int y = 3 + src_r * (3 + divider_or_not); y < 3 + (src_r + len) * (3 + divider_or_not); y++) {
        if (divider_or_not && (y - 2) % 4 == 0) // Print frame
            cct_showstr(4 + src_c * (6 + 2 * divider_or_not), y, "═", COLOR_HWHITE, COLOR_BLACK, 3);
        else // Not print frame
            cct_showch(4 + src_c * (6 + 2 * divider_or_not), y, ' ', COLOR_HWHITE, COLOR_BLACK, 6);
        print_block(matrix, src_r + len, src_c, divider_or_not, COLOR_BLACK, BLOCK_WIDTH, BLOCK_HEIGHT, 4 + src_c * (6 + 2 * divider_or_not), y + 1, COORDINATE_UNLOCK);
        if (y % 2)
            Sleep(SLEEP_TIME_BLOCK); // Delaying animation effects
    }
}

/*
 * Function Name:    print_move_horizontal
 * Function:         Print the horizontal movement process of color blocks
 * Input Parameters: int matrix[][10]
 *                   int src_r
 *                   int src_c
 *                   int len
 *                   int divider_or_not
 * Return Value:     void
 */
void print_move_horizontal(int matrix[][10], int src_r, int src_c, int len, int divider_or_not)
{
    for (int x = 4 + src_c * (6 + 2 * divider_or_not); x > 4 + (src_c - len) * (6 + 2 * divider_or_not); x -= 2) {
        if (divider_or_not && (x + 2) % 8 == 0) { // Print frame
            for (int i = 0; i < 3; i++)
                cct_showstr(x + 4, 3 + src_r * (3 + 1 * divider_or_not) + i, "║", COLOR_HWHITE, COLOR_BLACK, 1);
        }
        else { // Not print frame
            for (int i = 0; i < 3; i++)
                cct_showch(x + 4, 3 + src_r * (3 + 1 * divider_or_not) + i, ' ', COLOR_HWHITE, COLOR_BLACK, 2);
        }
        print_block(matrix, src_r, src_c - len, divider_or_not, COLOR_BLACK, BLOCK_WIDTH, BLOCK_HEIGHT, x - 2, 3 + src_r * (3 + 1 * divider_or_not), COORDINATE_UNLOCK);
        if (x % 4)
            Sleep(SLEEP_TIME_BLOCK); // Delaying animation effects
    }
}

/*
 * Function Name:    move_coordinate_keyboard
 * Function:         Move coordinates using keyboard arrow keys
 * Input Parameters: int matrix[][10]
 *                   int row
 *                   int column
 *                   int select_r
 *                   int select_c
 *                   int ret
 *                   int keycode1
 *                   int keycode2
 *                   int& X
 *                   int& Y
 *                   int divider_or_not
 * Return Value:     void
 */
void move_coordinate_keyboard(int matrix[][10], int row, int column, int select_r, int select_c, int ret, int keycode1, int keycode2, int& X, int& Y, int divider_or_not)
{
    /* Move coordinates using keyboard arrow keys */
    if (ret == CCT_KEYBOARD_EVENT && keycode1 == 224 && (keycode2 == KB_ARROW_DOWN || keycode2 == KB_ARROW_LEFT || keycode2 == KB_ARROW_RIGHT || keycode2 == KB_ARROW_UP)) {
        /* Save the old state */
        int temp_r = select_r, temp_c = select_c;

        /* Change the state */
        switch (keycode2) {
            case KB_ARROW_UP:
                while (true) {
                    temp_r--;
                    if (temp_r == -1)
                        temp_r = row - 1;
                    if (matrix[temp_r][temp_c] != 0)
                        break;
                }
                break;
            case KB_ARROW_DOWN:
                while (true) {
                    temp_r++;
                    if (temp_r == row)
                        temp_r = 0;
                    if (matrix[temp_r][temp_c] != 0)
                        break;
                }
                break;
            case KB_ARROW_LEFT:
                while (true) {
                    temp_c--;
                    if (temp_c == -1)
                        temp_c = column - 1;
                    if (matrix[temp_r][temp_c] != 0)
                        break;
                }
                break;
            case KB_ARROW_RIGHT:
                while (true) {
                    temp_c++;
                    if (temp_c == column)
                        temp_c = 0;
                    if (matrix[temp_r][temp_c] != 0)
                        break;
                }
                break;
            default:
                break;
        } // end of switch (keycode2)

        /* Save the new state */
        X = 4 + (6 + 2 * divider_or_not) * temp_c;
        Y = 3 + (3 + divider_or_not) * temp_r;
    } // end of if (ret == CCT_KEYBOARD_EVENT && keycode1 == 224 && (keycode2 == KB_ARROW_DOWN || keycode2 == KB_ARROW_LEFT || keycode2 == KB_ARROW_RIGHT || keycode2 == KB_ARROW_UP))
}

/*
 * Function Name:    get_row_column
 * Function:         Get row and column
 * Input Parameters: int row
 *                   int column
 *                   int X
 *                   int Y
 *                   int& select_r
 *                   int& select_c
 *                   int divider_or_not
 * Return Value:     void
 */
void get_row_column(int row, int column, int X, int Y, int& select_r, int& select_c, int divider_or_not)
{
    if (divider_or_not) { // With dividing lines
        for (int i = 0; i < column; i++) // Get column
            if (X >= 8 * i + 4 && X <= 8 * i + 9)
                select_c = i;
        for (int i = 0; i < row; i++) // Get row
            if (Y >= 4 * i + 3 && Y <= 4 * i + 5)
                select_r = i;
    }
    else { // Without dividing lines
        for (int i = 0; i < column; i++) // Get column
            if (X >= 6 * i + 4 && X <= 6 * i + 9)
                select_c = i;
        for (int i = 0; i < row; i++) // Get row
            if (Y >= 3 * i + 3 && Y <= 3 * i + 5)
                select_r = i;
    }
}

/*
 * Function Name:    print_selected_or_exit
 * Function:         Print the currently selected row and column or end the game
 * Input Parameters: int row
 *                   int column
 *                   int select_r
 *                   int select_c
 *                   int divider_or_not
 *                   int continue_or_not
 * Return Value:     0 - End the game
 *                   1 - Continue the game
 */
int print_selected_or_exit(int row, int column, int select_r, int select_c, int divider_or_not, int continue_or_not)
{
    /* Clear prompt message */
    clear_information(row, column, divider_or_not);

    /* Print the currently selected row and column */
    cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
    if (continue_or_not)
        cout << "[当前选中] " << char(select_r + 'A') << "行" << select_c << "列";
    cct_setcolor();

    /* Disable mouse and cursor settings */
    cct_disable_mouse();
    cct_setcursor(CURSOR_VISIBLE_NORMAL);

    /* Return the game state */
    return continue_or_not;
}

/*
 * Function Name:    graphical_initialize
 * Function:         Initialize a pseudo-graphical interface
 * Input Parameters: int matrix[][10]
 *                   int row
 *                   int column
 *                   int divider_or_not
 * Return Value:     void
 */
void graphical_initialize(int matrix[][10], int row, int column, int divider_or_not)
{
    /* Set console size */
    cct_setconsoleborder(6 * column + 7 + divider_or_not * (column - 1) * 2, 3 * row + 8 + divider_or_not * (row - 1), 6 * column + 7 + divider_or_not * (column - 1) * 2, 3 * row + 8 + divider_or_not * (row - 1));

    /* Initialize the matrix */
    matrix_initialize(matrix, row, column);

    /* Print frame */
    print_frame(row, column, divider_or_not);

    /* Print all initial color blocks */
    print_block_initial(matrix, row, column, divider_or_not, BLOCK_WIDTH, BLOCK_HEIGHT);
}

/*
 * Function Name:    judgment_synthesis
 * Function:         Count the number of consecutive identical values and merge them
 * Input Parameters: int matrix[][10]
 *                   int judgment_array[][12]
 *                   int row
 *                   int column
 *                   int select_r
 *                   int select_c
 *                   int divider_or_not
 * Return Value:     void
 */
void judgment_synthesis(int matrix[][10], int judgment_array[][12], int row, int column, int select_r, int select_c, int divider_or_not)
{
    /* Clear prompt message */
    clear_information(row, column, divider_or_not);

    /* Count the number of consecutive identical values */
    if (judgment_continuity(matrix, judgment_array, row, column, select_r, select_c) == 1) { // No consecutive identical values
        /* Print prompt message */
        cct_setcolor(COLOR_BLACK, COLOR_HRED);
        cout << "[无连续值] ";
        cct_setcolor();
        cout << "箭头键/鼠标移动，回车键/左键选择，Q/右键结束";
        print_block(matrix, select_r, select_c, divider_or_not, COLOR_WHITE, BLOCK_WIDTH, BLOCK_HEIGHT, COORDINATE_LOCK, COORDINATE_LOCK, COORDINATE_LOCK);
    }
    else { // Consecutive identical values
        /* Print prompt message */
        cct_setcolor(COLOR_BLACK, COLOR_HGREEN);
        cout << "[有连续值] ";
        cct_setcolor();
        cout << "箭头键/鼠标移动取消当前选择，回车键/左键合成";
        print_block(matrix, select_r, select_c, divider_or_not, COLOR_HWHITE, BLOCK_WIDTH, BLOCK_HEIGHT, COORDINATE_LOCK, COORDINATE_LOCK, COORDINATE_LOCK);

        /* Print reverse display */
        for (int i = 1; i < row + 1; i++)
            for (int j = 1; j < column + 1; j++)
                if (judgment_array[i][j] == '*' && !(i - 1 == select_r && j - 1 == select_c)) {
                    print_block(matrix, i - 1, j - 1, divider_or_not, COLOR_WHITE, BLOCK_WIDTH, BLOCK_HEIGHT, COORDINATE_LOCK, COORDINATE_LOCK, COORDINATE_LOCK);
                    Sleep(SLEEP_TIME_BLOCK);
                }
    }
}

/*
 * Function Name:    calculate_print_score
 * Function:         Calculate and print the current score and total score
 * Input Parameters: int matrix[][10]
 *                   int judgment_array[][12]
 *                   int row
 *                   int column
 *                   int select_r
 *                   int select_c
 *                   int& score_bound
 *                   int& score_total
 *                   int& num
 *                   int& loop1
 *                   int& loop2
 *                   int divider_or_not
 * Return Value:     void
 */
void calculate_print_score(int matrix[][10], int judgment_array[][12], int row, int column, int select_r, int select_c, int& score_bound, int& score_total, int& num, int& loop1, int& loop2, int divider_or_not)
{
    /* Count the number of consecutive identical values at a matrix coordinate position */
    num = judgment_continuity(matrix, judgment_array, row, column, select_r, select_c);
    if (num != 1) { // Consecutive identical values
        /* Calculate and print the current score and total score */
        score_bound = num * num * 5;
        score_total += score_bound;
        cct_gotoxy(0, 0);
        cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
        cout << "本次得分：" << setiosflags(ios::left) << setw(5) << score_bound << " 总得分：" << setw(11) << score_total << resetiosflags(ios::left);
        cct_gotoxy(6 * column + 7 + divider_or_not * (column - 1) * 2 - 34, 0);
        cout << "★ 通关目标：剩余星星不多于" << (row * column / 10) * 2 + 2 << "个 ★";
        cct_setcolor();

        /* Merge identical values in an array */
        array_incorporate(matrix, judgment_array, row, column);
        for (int i = 0; i < row; i++)
            for (int j = 0; j < column; j++)
                if (matrix[i][j] == 0) {
                    print_block(matrix, i, j, divider_or_not, COLOR_HWHITE, BLOCK_WIDTH, BLOCK_HEIGHT, COORDINATE_LOCK, COORDINATE_LOCK, COORDINATE_LOCK);
                    Sleep(SLEEP_TIME_BLOCK);
                }

        /* Shift zero values in an array */
        array_translation(matrix, row, column, GRAPHICAL_INTERFACE, divider_or_not);

        /* Set the loop condition */
        loop1 = 0;
        loop2 = 0;
    }
}

/*
 * Function Name:    print_nonReverse_current
 * Function:         Cancel reverse display and print the current operation
 * Input Parameters: int matrix[][10]
 *                   int judgment_array[][12]
 *                   int row
 *                   int column
 *                   int ret
 *                   int keycode1
 *                   int keycode2
 *                   int X
 *                   int Y
 *                   int& select_r
 *                   int& select_c
 *                   int _select_r
 *                   int _select_c
 *                   int& loop2
 *                   int divider_or_not
 *                   int trans_or_not
 * Return Value:     void
 */
void print_nonReverse_current(int matrix[][10], int judgment_array[][12], int row, int column, int ret, int keycode1, int keycode2, int X, int Y, int& select_r, int& select_c, int _select_r, int _select_c, int& loop2, int divider_or_not, int trans_or_not)
{
    /* Check the validity of a coordinate position */
    if (!judgment_legality(matrix, row, column, X, Y, select_r, select_c, divider_or_not, trans_or_not) || _select_r != select_r || _select_c != select_c) {
        /* Cancel reverse display */
        for (int i = 1; i < row + 1; i++)
            for (int j = 1; j < column + 1; j++)
                if (judgment_array[i][j] == '*') {
                    print_block(matrix, i - 1, j - 1, divider_or_not, COLOR_BLACK, BLOCK_WIDTH, BLOCK_HEIGHT, COORDINATE_LOCK, COORDINATE_LOCK, COORDINATE_LOCK);
                    Sleep(SLEEP_TIME_BLOCK);
                }

        /* Print the current operation */
        if (ret == CCT_MOUSE_EVENT)
            print_current(matrix, row, column, X, Y, select_r, select_c, "鼠标", divider_or_not);
        if (keycode1 == 224 && (keycode2 == KB_ARROW_DOWN || keycode2 == KB_ARROW_LEFT || keycode2 == KB_ARROW_RIGHT || keycode2 == KB_ARROW_UP))
            print_current(matrix, row, column, X, Y, select_r, select_c, "键盘", divider_or_not);

        /* Set the loop condition */
        loop2 = 0;
    }
}

/*
 * Function Name:    print_score_level
 * Function:         Calculate and print the reward score and total score
 * Input Parameters: int matrix[][10]
 *                   int row
 *                   int column
 *                   int& score_reward
 *                   int& score_total
 *                   int divider_or_not
 * Return Value:     0 - End the game
 *                   1 - Continue the game
 */
int print_score_level(int matrix[][10], int row, int column, int& score_reward, int& score_total, int divider_or_not)
{
    /* Determine if an array has consecutive identical values */
    int remain = array_judgment(matrix, row, column);
    if (remain >= 0) { // No consecutive identical values
        /* Calculate the score */
        score_reward = (remain >= 10 ? 0 : (10 - remain) * 180);
        score_total += score_reward;
        score_total += (remain > (row * column / 10) * 2 + 2 ? 0 : ((row * column / 10) * 2 + 2 - remain) * 90);

        /* Print the reward score and total score */
        cct_gotoxy(0, 0);
        cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
        cout << "星星奖励得分：" << setiosflags(ios::left) << setw(4) << score_reward << " 总得分：" << setw(6) << score_total << resetiosflags(ios::left);
        cct_setcolor();

        /* Print prompt message and achievement score */
        clear_information(row, column, divider_or_not);
        cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
        cout << "[本关结束] 剩余" << remain << "个星星，无可消除项，";
        if (remain <= (row * column / 10) * 2 + 2)
            cout << "达到通关目标，通关奖励得分：" << ((row * column / 10) * 2 + 2 - remain) * 90;
        else
            cout << "未达到通关目标，无通关奖励得分";
        cct_setcolor();

        /* Press Enter to continue to the next level */
        wait_for_enter("回车继续下一关");
        clear_information(row, column, divider_or_not);
        cout << endl << setw(14) << "";
        return 0;
    }
    else { // Consecutive identical values
        return 1;
    }
}