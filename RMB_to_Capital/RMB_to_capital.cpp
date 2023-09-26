/****************************************************************
 * Project Name:  RMB_to_Capital
 * File Name:     RMB_to_capital.cpp
 * File Function: 人民币转大写函数的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/9/27
 ****************************************************************/

#include <iostream>

using namespace std;

/*
 * Function Name:    capital
 * Function:         RMB to capital
 * Input Parameters: int num
 *                   int flag_of_zero
 * Return Value:     void
 */
void capital(int num, int flag_of_zero)
{
    switch (num) {
        case 0:
            if (flag_of_zero)
                cout << "零";
            break;
        case 1:
            cout << "壹";
            break;
        case 2:
            cout << "贰";
            break;
        case 3:
            cout << "叁";
            break;
        case 4:
            cout << "肆";
            break;
        case 5:
            cout << "伍";
            break;
        case 6:
            cout << "陆";
            break;
        case 7:
            cout << "柒";
            break;
        case 8:
            cout << "捌";
            break;
        case 9:
            cout << "玖";
            break;
        default:
            cout << "error";
            break;
    }
}

/*
 * Function Name:    main
 * Function:         Main function
 * Return Value:     0
 */
int main()
{
    /* Input */
    double num, temp;
    int a01, a02, a03, a04, a05, a06, a07, a08, a09, a10, a11, a12, mark = 0;
    cout << "请输入[0-100亿)之间的数字:" << endl;
    while (1) {
        cin >> num;
        if (cin.good() && num >= 0 && num < 10000000000) {
            break;
        }
        else {
            cin.clear();
            cin.ignore(65536, '\n');
            cout << "请输入[0-100亿)之间的数字:" << endl;
        }
    }

    /* Decompose floating-point number */
    a12 = int(num / 1000000000);
    a11 = int(num / 100000000) % 10;
    a10 = int(num / 10000000) % 10;
    a09 = int(num / 1000000) % 10;
    a08 = int(num / 100000) % 10;
    a07 = int(num / 10000) % 10;
    a06 = int(num / 1000) % 10;
    a05 = int(num / 100) % 10;
    a04 = int(num / 10) % 10;
    a03 = int(num - double(a12) * 1000000000) % 10;
    temp = (num * 10000 + 0.01) / double(10000);
    a02 = int((temp - double(a12) * 1000000000 - a11 * 100000000 - a10 * 10000000 - a09 * 1000000 - a08 * 100000 - a07 * 10000 - a06 * 1000 - a05 * 100 - a04 * 10 - a03) * 10);
    a01 = int((temp - double(a12) * 1000000000 - a11 * 100000000 - a10 * 10000000 - a09 * 1000000 - a08 * 100000 - a07 * 10000 - a06 * 1000 - a05 * 100 - a04 * 10 - a03) * 100) % 10;

    /* Output */
    cout << "人民币转大写结果是:" << endl;
    if (num == 0) {
        capital(0, 1);
        cout << "圆整";
    }
    else {
        capital(a12, 0);
        if (a12 != 0)
            cout << "拾";
        capital(a11, 0);
        if (a12 != 0 || a11 != 0)
            cout << "亿";
        capital(a10, (a12 != 0 || a11 != 0) && ((a09 != 0 || a08 != 0 || a07 != 0) || (a09 == 0 && a08 == 0 && a07 == 0 && a06 == 0 && (a05 != 0 || a04 != 0 || a03 != 0))));
        if (a10 != 0)
            cout << "仟";
        capital(a09, (a10 != 0 && a08 != 0 && a07 == 0) || (a10 != 0 && a08 == 0 && a07 != 0) || (a10 != 0 && a08 != 0 && a07 != 0));
        if (a09 != 0)
            cout << "佰";
        capital(a08, a09 != 0 && a07 != 0);
        if (a08 != 0)
            cout << "拾";
        capital(a07, 0);
        if (a10 != 0 || a09 != 0 || a08 != 0 || a07 != 0)
            cout << "万";
        capital(a06, (a10 != 0 || a09 != 0 || a08 != 0 || a07 != 0) && (a05 != 0 || a04 != 0 || a03 != 0));
        if (a06 != 0)
            cout << "仟";
        capital(a05, (a06 != 0 && a04 != 0 && a03 == 0) || (a06 != 0 && a04 == 0 && a03 != 0) || (a06 != 0 && a04 != 0 && a03 != 0));
        if (a05 != 0)
            cout << "佰";
        capital(a04, a05 != 0 && a03 != 0);
        if (a04 != 0)
            cout << "拾";
        capital(a03, 0);
        if (a12 != 0 || a11 != 0 || a10 != 0 || a09 != 0 || a08 != 0 || a07 != 0 || a06 != 0 || a05 != 0 || a04 != 0 || a03 != 0)
            cout << "圆";
        if (a02 == 0) {
            if (a01 != 0 && (a12 != 0 || a11 != 0 || a10 != 0 || a09 != 0 || a08 != 0 || a07 != 0 || a06 != 0 || a05 != 0 || a04 != 0)) {
                capital(a02, 1);
                mark = 1;
            }
            if (a02 == 0 && a01 == 0)
                cout << "整";
            else if (a03 == 0 && a02 == 0 && a01 != 0)
                ;
            else if (mark != 1)
                capital(a02, 1);
            else
                ;
        }
        else
            capital(a02, 0);
        if (a02 != 0)
            cout << "角";
        if (a01 == 0) {
            if (a02 != 0)
                cout << "整";
        }
        else
            capital(a01, 0);
        if (a01 != 0)
            cout << "分";
    }
    cout << endl;

    /* Program ends */
    return 0;
}