/****************************************************************
 * Project Name:  common
 * File Name:     str_proc_funcs.cpp
 * File Function: 字符串处理函数工具集的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/9/28
 ****************************************************************/

#include "../common/str_proc_funcs.h"

using namespace std;

/*
 * Function Name:    strlen_array
 * Function:         求字符串str的长度(数组法实现)
 * Input Parameters: const char str[]: 字符数组str
 * Return Value:     字符串长度
 */
int strlen_array(const char str[])
{
    int i = -1;
    while (1) {
        if (str[++i])
            continue;
        else
            break;
    }
    return i;
}

/*
 * Function Name:    strcat_array
 * Function:         将字符串s2追加到s1后面，含\0(数组法实现)
 * Input Parameters: char s1[]: 字符数组s1
 *                   const char s2[]: 字符数组s2
 * Return Value:     0
 */
int strcat_array(char s1[], const char s2[])
{
    int i = strlen_array(s1), j = 0;
    while (1) {
        if (s2[j]) {
            s1[i++] = s2[j++];
            continue;
        }
        else
            break;
    }
    s1[i] = s2[j];
    return 0;
}

/*
 * Function Name:    strncat_array
 * Function:         将字符串s2的前len个字符追加到s1后面，并添加\0(数组法实现)
 * Input Parameters: char s1[]: 字符数组s1
 *                   const char s2[]: 字符数组s2
 *                   const int len: 长度
 * Return Value:     0
 * Notes:            若len比s2的长度大，则追加整个s2即可(含\0)
 */
int strncat_array(char s1[], const char s2[], const int len)
{
    int i = strlen_array(s1), j, length;
    len > strlen_array(s2) ? length = strlen_array(s2) : length = len;
    for (j = 0; j < length; j++)
        s1[i++] = s2[j];
    len > strlen_array(s2) ? s1[i] = s2[j] : s1[i] = 0;
    return 0;
}

/*
 * Function Name:    strcpy_array
 * Function:         将字符串s2复制到s1中，覆盖s1中原内容，复制时包含\0(数组法实现)
 * Input Parameters: char s1[]: 字符数组s1
 *                   const char s2[]: 字符数组s2
 * Return Value:     0
 */
int strcpy_array(char s1[], const char s2[])
{
    int i = 0, j = 0;
    while (1) {
        if (s2[j]) {
            s1[i++] = s2[j++];
            continue;
        }
        else
            break;
    }
    s1[i] = s2[j];
    return 0;
}

/*
 * Function Name:    strncpy_array
 * Function:         将字符串s2的前len个字符复制到s1中，复制时不含\0(数组法实现)
 * Input Parameters: char s1[]: 字符数组s1
 *                   const char s2[]: 字符数组s2
 *                   const int len : 长度
 * Return Value:     0
 * Notes:            若len比s2的长度大，复制s2长度个字符即可(不含\0)
 */
int strncpy_array(char s1[], const char s2[], const int len)
{
    int i = 0, j, length;
    len > strlen_array(s2) ? length = strlen_array(s2) : length = len;
    for (j = 0; j < length; j++)
        s1[i++] = s2[j];
    return 0;
}

/*
 * Function Name:    strcmp_array
 * Function:         比较字符串s1和s2的大小，英文字母区分大小写(数组法实现)
 * Input Parameters: const char s1[]: 字符数组s1
 *                   const char s2[]: 字符数组s2
 * Return Value:     0 / 第1个不相等字符的ASCII差值
 */
int strcmp_array(const char s1[], const char s2[])
{
    int i = 0;
    while (1) {
        if (s1[i] == s2[i]) {
            if (s1[i])
                i++;
            else
                return 0;
        }
        else
            return s1[i] - s2[i];
    }
}

/*
 * Function Name:    strcasecmp_array
 * Function:         比较字符串s1和s2的大小，英文字母不区分大小写(数组法实现)
 * Input Parameters: const char s1[]: 字符数组s1
 *                   const char s2[]: 字符数组s2
 * Return Value:     0 / 第1个不相等字符的ASCII差值
 * Notes:            若不相等处字符是不同的大小写字母，则统一转换为小写后比较
 *                   若不相等处字符是大写字母和其他字符，则返回对应小写字母和其他字符的差值
 */
int strcasecmp_array(const char s1[], const char s2[])
{
    int i = 0;
    char a, b;
    while (1) {
        a = s1[i];
        b = s2[i];
        if (a >= 'A' && a <= 'Z')
            a += 32;
        if (b >= 'A' && b <= 'Z')
            b += 32;
        if (a == b) {
            if (a)
                i++;
            else
                return 0;
        }
        else
            return a - b;
    }
}

/*
 * Function Name:    strncmp_array
 * Function:         比较字符串s1和s2的前len个字符的大小，英文字母区分大小写(数组法实现)
 * Input Parameters: const char s1[]: 字符数组s1
 *                   const char s2[]: 字符数组s2
 *                   const int len : 长度
 * Return Value:     0 / 第1个不相等字符的ASCII差值
 * Notes:            若len大于s1/s2中长度短的串，则比较到短串的\0即结束
 *                   若不相等处字符是不同的大小写字母，则统一转换为小写后比较
 *                   若不相等处字符是大写字母和其他字符，则返回对应小写字母和其他字符的差值
 */
int strncmp_array(const char s1[], const char s2[], const int len)
{
    int i = 0;
    while (1) {
        if (s1[i] == s2[i]) {
            if (s1[i]) {
                if (++i == len)
                    return 0;
            }
            else
                return 0;
        }
        else
            return s1[i] - s2[i];
    }
}

/*
 * Function Name:    strcasencmp_array
 * Function:         比较字符串s1和s2的前len个字符的大小，英文字母不区分大小写(数组法实现)
 * Input Parameters: const char s1[]: 字符数组s1
 *                   const char s2[]: 字符数组s2
 *                   const int len: 长度
 * Return Value:     0 / 第1个不相等字符的ASCII差值
 * Notes:            若len大于s1/s2中长度短的串，则比较到短串的\0即结束
 */
int strcasencmp_array(const char s1[], const char s2[], const int len)
{
    int i = 0;
    char a, b;
    while (1) {
        a = s1[i];
        b = s2[i];
        if (a >= 'A' && a <= 'Z')
            a += 32;
        if (b >= 'A' && b <= 'Z')
            b += 32;
        if (a == b) {
            if (a) {
                if (++i == len)
                    return 0;
            }
            else
                return 0;
        }
        else
            return a - b;
    }
}

/*
 * Function Name:    strupr_array
 * Function:         将字符串str中所有小写字母转为大写，其他字符不变，转换后放在原串中(数组法实现)
 * Input Parameters: char str[]: 字符数组str
 * Return Value:     0
 */
int strupr_array(char str[])
{
    for (int i = 0; i < strlen_array(str); i++)
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] -= 32;
    return 0;
}

/*
 * Function Name:    strlwr_array
 * Function:         将字符串str中所有小写字母转为大写，其他字符不变，转换后放在原串中(数组法实现)
 * Input Parameters: char str[]: 字符数组str
 * Return Value:     0
 */
int strlwr_array(char str[])
{
    for (int i = 0; i < strlen_array(str); i++)
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 32;
    return 0;
}

/*
 * Function Name:    strchr_array
 * Function:         在字符串str中寻找字符ch第1次出现的位置，顺序是从左到右(数组法实现)
 * Input Parameters: const char str[]: 字符数组str
 *                   char ch: 字符
 * Return Value:     0 / 位置
 */
int strchr_array(const char str[], char ch)
{
    for (int i = 0; i < strlen_array(str); i++)
        if (str[i] == ch)
            return i + 1;
    return 0;
}

/*
 * Function Name:    strstr_array
 * Function:         在字符串str中寻找字符串substr第1次出现的位置，顺序是从左到右(数组法实现)
 * Input Parameters: const char str[]: 字符数组str
 *                   const char substr[]: 字符数组substr
 * Return Value:     0 / 位置
 */
int strstr_array(const char str[], const char substr[])
{
    for (int i = 0; i < strlen_array(str); i++)
        for (int j = i, k = 0; j < i + strlen_array(substr); j++) {
            if (str[j] == substr[k++]) {
                if (substr[k])
                    continue;
                else
                    return i + 1;
            }
            else
                break;
        }
    return 0;
}

/*
 * Function Name:    strrchr_array
 * Function:         在字符串str中寻找字符ch第1次出现的位置，顺序是从右到左(数组法实现)
 * Input Parameters: const char str[]: 字符数组str
 *                   char ch: 字符
 * Return Value:     0 / 位置
 */
int strrchr_array(const char str[], const char ch)
{
    for (int i = strlen_array(str) - 1; i >= 0; i--)
        if (str[i] == ch)
            return i + 1;
    return 0;
}

/*
 * Function Name:    strrstr_array
 * Function:         在字符串str中寻找字符串substr第1次出现的位置，顺序是从右到左(数组法实现)
 * Input Parameters: const char str[]: 字符数组str
 *                   const char substr[]: 字符数组substr
 * Return Value:     0 / 位置
 */
int strrstr_array(const char str[], const char substr[])
{
    for (int i = strlen_array(str) - 1; i >= 0; i--)
        for (int j = i + strlen_array(substr) - 1, k = strlen_array(substr) - 1; j >= i; j--) {
            if (str[j] == substr[k--]) {
                if (j == 0)
                    return 1;
                if (k + 1 == 0)
                    return j + 1;
            }
            else
                break;
        }
    return 0;
}

/*
 * Function Name:    strrev_array
 * Function:         字符串反转，放入原串中(数组法实现)
 * Input Parameters: char str[]: 字符数组str
 * Return Value:     0
 */
int strrev_array(char str[])
{
    int i = 0, j = strlen_array(str) - 1;
    while (j > i) {
        char temp = str[i];
        str[i++] = str[j];
        str[j--] = temp;
    }
    return 0;
}

/*
 * Function Name:    strlen_pointer
 * Function:         求字符串str的长度(指针法实现)
 * Input Parameters: const char* str: 字符数组str的指针
 * Return Value:     字符串长度
 */
int strlen_pointer(const char* str)
{
    const char* p;
    if (str == NULL)
        return 0;
    for (p = str; *p; p++)
        continue;
    return p - str;
}

/*
 * Function Name:    strcat_pointer
 * Function:         将字符串s2追加到s1后面，含\0(指针法实现)
 * Input Parameters: char* s1: 字符数组s1的指针
 *          const char* s2: 字符数组s2的指针
 * Return Value:     字符数组s1的指针
 */
char* strcat_pointer(char* s1, const char* s2)
{
    char* p1 = s1 + strlen_pointer(s1);
    const char* p2 = s2;
    if (s1 == NULL)
        return NULL;
    if (s2 == NULL)
        return s1;
    while (1) {
        if (*p2) {
            *p1 = *p2;
            p1++;
            p2++;
            continue;
        }
        else
            break;
    }
    *p1 = *p2;
    return s1;
}

/*
 * Function Name:    strncat_pointer
 * Function:         将字符串s2的前len个字符追加到s1后面，并添加\0(指针法实现)
 * Input Parameters: char* s1: 字符数组s1的指针
 *                   const char* s2: 字符数组s2的指针
 *                   const int len: 长度
 * Return Value:     字符数组s1的指针
 * Notes:            若len比s2的长度大，则追加整个s2即可(含\0)
 */
char* strncat_pointer(char* s1, const char* s2, const int len)
{
    char* p1 = s1 + strlen_pointer(s1);
    const char* p2 = s2;
    int length;
    int* p3 = &length;
    if (s1 == NULL)
        return NULL;
    if (s2 == NULL)
        return s1;
    len > strlen_pointer(s2) ? *p3 = strlen_pointer(s2) : *p3 = len;
    for (; p2 - s2 < *p3; p2++) {
        *p1 = *p2;
        p1++;
    }
    len > strlen_pointer(s2) ? *p1 = *p2 : *p1 = 0;
    return s1;
}

/*
 * Function Name:    strcpy_pointer
 * Function:         将字符串s2复制到s1中，覆盖s1中原内容，复制时包含\0(指针法实现)
 * Input Parameters: char* s1: 字符数组s1的指针
 *                   const char* s2: 字符数组s2的指针
 * Return Value:     字符数组s1的指针
 */
char* strcpy_pointer(char* s1, const char* s2)
{
    char* p1 = s1;
    const char* p2 = s2;
    if (s1 == NULL)
        return NULL;
    if (s2 != NULL)
        while (1) {
            if (*p2) {
                *p1 = *p2;
                p1++;
                p2++;
                continue;
            }
            else
                break;
        }
    *p1 = 0;
    return s1;
}

/*
 * Function Name:    strncpy_pointer
 * Function:         将字符串s2的前len个字符复制到s1中，复制时不含\0(指针法实现)
 * Input Parameters: char* s1: 字符数组s1的指针
 *                   const char* s2: 字符数组s2的指针
 *                   const int len: 长度
 * Return Value:     字符数组s1的指针
 * Notes:            若len比s2的长度大，复制s2长度个字符即可(不含\0)
 */
char* strncpy_pointer(char* s1, const char* s2, const int len)
{
    if (s1 == NULL)
        return NULL;
    if (s2 != NULL) {
        char* p1 = s1;
        const char* p2 = s2;
        int length;
        int* p3 = &length;
        len > strlen_pointer(s2) ? *p3 = strlen_pointer(s2) : *p3 = len;
        for (; p2 - s2 < *p3; p2++) {
            *p1 = *p2;
            p1++;
        }
    }
    return s1;
}

/*
 * Function Name:    strcmp_pointer
 * Function:         比较字符串s1和s2的大小，英文字母区分大小写(指针法实现)
 * Input Parameters: const char* s1: 字符数组s1的指针
 *                   const char* s2: 字符数组s2的指针
 * Return Value:     0 / 第1个不相等字符的ASCII差值
 */
int strcmp_pointer(const char* s1, const char* s2)
{
    const char* p1 = s1, * p2 = s2;
    if (s1 == NULL && s2 == NULL)
        return 0;
    else if (s1 == NULL && s2 != NULL)
        return -1;
    else if (s1 != NULL && s2 == NULL)
        return 1;
    else
        while (1) {
            if (*p1 == *p2) {
                if (*p1) {
                    p1++;
                    p2++;
                }
                else
                    return 0;
            }
            else
                return *p1 - *p2;
        }
}

/*
 * Function Name:    strcasecmp_pointer
 * Function:         比较字符串s1和s2的大小，英文字母不区分大小写(指针法实现)
 * Input Parameters: const char* s1: 字符数组s1的指针
 *                   const char* s2: 字符数组s2的指针
 * Return Value:     0 / 第1个不相等字符的ASCII差值
 * Notes:            若不相等处字符是不同的大小写字母，则统一转换为小写后比较
 *                   若不相等处字符是大写字母和其他字符，则返回对应小写字母和其他字符的差值
 */
int strcasecmp_pointer(const char* s1, const char* s2)
{
    const char* p1 = s1, * p2 = s2;
    if (s1 == NULL && s2 == NULL)
        return 0;
    else if (s1 == NULL && s2 != NULL)
        return -1;
    else if (s1 != NULL && s2 == NULL)
        return 1;
    else
        while (1) {
            char temp1 = *p1, temp2 = *p2;
            if (temp1 >= 'A' && temp1 <= 'Z')
                temp1 += 32;
            if (temp2 >= 'A' && temp2 <= 'Z')
                temp2 += 32;
            if (temp1 == temp2) {
                if (temp1) {
                    p1++;
                    p2++;
                }
                else
                    return 0;
            }
            else
                return temp1 - temp2;
        }
}

/*
 * Function Name:    strncmp_pointer
 * Function:         比较字符串s1和s2的前len个字符的大小，英文字母区分大小写(指针法实现)
 * Input Parameters: const char* s1: 字符数组s1的指针
 *                   const char* s2: 字符数组s2的指针
 *                   const int len: 长度
 * Return Value:     0 / 第1个不相等字符的ASCII差值
 * Notes:            若len大于s1/s2中长度短的串，则比较到短串的\0即结束
 *                   若不相等处字符是不同的大小写字母，则统一转换为小写后比较
 *                   若不相等处字符是大写字母和其他字符，则返回对应小写字母和其他字符的差值
 */
int strncmp_pointer(const char* s1, const char* s2, const int len)
{
    const char* p1 = s1, * p2 = s2;
    if (s1 == NULL && s2 == NULL)
        return 0;
    else if (s1 == NULL && s2 != NULL)
        return -1;
    else if (s1 != NULL && s2 == NULL)
        return 1;
    else
        while (1) {
            if (*p1 == *p2) {
                if (*p1) {
                    p1++;
                    p2++;
                    if (p1 - s1 == len)
                        return 0;
                }
                else
                    return 0;
            }
            else
                return *p1 - *p2;
        }
}

/*
 * Function Name:    strcasencmp_pointer
 * Function:         比较字符串s1和s2的前len个字符的大小，英文字母不区分大小写(指针法实现)
 * Input Parameters: const char* s1: 字符数组s1的指针
 *                   const char* s2: 字符数组s2的指针
 *                   const int len: 长度
 * Return Value:     0 / 第1个不相等字符的ASCII差值
 * Notes:            若len大于s1/s2中长度短的串，则比较到短串的\0即结束
 */
int strcasencmp_pointer(const char* s1, const char* s2, const int len)
{
    const char* p1 = s1, * p2 = s2;
    if (s1 == NULL && s2 == NULL)
        return 0;
    else if (s1 == NULL && s2 != NULL)
        return -1;
    else if (s1 != NULL && s2 == NULL)
        return 1;
    else
        while (1) {
            char temp1 = *p1, temp2 = *p2;
            if (temp1 >= 'A' && temp1 <= 'Z')
                temp1 += 32;
            if (temp2 >= 'A' && temp2 <= 'Z')
                temp2 += 32;
            if (temp1 == temp2) {
                if (temp1) {
                    p1++;
                    p2++;
                    if (p1 - s1 == len)
                        return 0;
                }
                else
                    return 0;
            }
            else
                return temp1 - temp2;
        }
}

/*
 * Function Name:    strupr_pointer
 * Function:         将字符串str中所有小写字母转为大写，其他字符不变，转换后放在原串中(指针法实现)
 * Input Parameters: char* str: 字符数组str的指针
 * Return Value:     字符数组str的指针
 */
char* strupr_pointer(char* str)
{
    if (str == NULL)
        return NULL;
    for (char* p = str; p - str < strlen_pointer(str); p++)
        if (*p >= 'a' && *p <= 'z')
            *p -= 32;
    return str;
}

/*
 * Function Name:    strlwr_pointer
 * Function:         将字符串str中所有小写字母转为大写，其他字符不变，转换后放在原串中(指针法实现)
 * Input Parameters: char* str: 字符数组str的指针
 * Return Value:     字符数组str的指针
 */
char* strlwr_pointer(char* str)
{
    if (str == NULL)
        return NULL;
    for (char* p = str; p - str < strlen_pointer(str); p++)
        if (*p >= 'A' && *p <= 'Z')
            *p += 32;
    return str;
}

/*
 * Function Name:    strchr_pointer
 * Function:         在字符串str中寻找字符ch第1次出现的位置，顺序是从左到右(指针法实现)
 * Input Parameters: const char* str: 字符数组str的指针
 *                   const char ch: 字符
 * Return Value:     0 / 位置
 */
int strchr_pointer(const char* str, const char ch)
{
    if (str != NULL)
        for (const char* p = str; p - str < strlen_pointer(str); p++)
            if (*p == ch)
                return p - str + 1;
    return 0;
}

/*
 * Function Name:    strstr_pointer
 * Function:         在字符串str中寻找字符串substr第1次出现的位置，顺序是从左到右(指针法实现)
 * Input Parameters: const char* str: 字符数组str的指针
 *                   const char* substr: 字符数组substr的指针
 * Return Value:     0 / 位置
 */
int strstr_pointer(const char* str, const char* substr)
{
    if (str != NULL)
        for (const char* p = str; p - str < strlen_pointer(str); p++)
            for (const char* _p = substr, *__p = p; __p - p < strlen_pointer(substr); __p++) {
                if (*__p == *_p++) {
                    if (*_p)
                        continue;
                    else
                        return p - str + 1;
                }
                else
                    break;
            }
    return 0;
}

/*
 * Function Name:    strrchr_pointer
 * Function:         在字符串str中寻找字符ch第1次出现的位置，顺序是从右到左(指针法实现)
 * Input Parameters: const char* str: 字符数组str的指针
 *                   const char ch: 字符
 * Return Value:     0 / 位置
 */
int strrchr_pointer(const char* str, const char ch)
{
    if (str != NULL)
        for (const char* p = str + strlen_pointer(str) - 1; p - str >= 0; p--)
            if (*p == ch)
                return p - str + 1;
    return 0;
}

/*
 * Function Name:    strrstr_pointer
 * Function:         在字符串str中寻找字符串substr第1次出现的位置，顺序是从右到左(指针法实现)
 * Input Parameters: const char* str: 字符数组str的指针
 *                   const char* substr: 字符数组substr的指针
 * Return Value:     0 / 位置
 */
int strrstr_pointer(const char* str, const char* substr)
{
    if (str != NULL)
        for (const char* p = str + strlen_pointer(str) - 1; p - str >= 0; p--)
            for (const char* _p = substr + strlen_pointer(substr) - 1, *__p = p + strlen_pointer(substr) - 1; __p >= p; __p--) {
                if (*__p == *_p--) {
                    if (__p == str)
                        return 1;
                    if (_p - substr + 1 == 0)
                        return __p - str + 1;
                }
                else
                    break;
            }
    return 0;
}

/*
 * Function Name:    strrev_pointer
 * Function:         字符串反转，放入原串中(指针法实现)
 * Input Parameters: char* str: 字符数组str的指针
 * Return Value:     字符数组str的指针
 */
char* strrev_pointer(char* str)
{
    char* p1 = str, * p2 = str + strlen_pointer(str) - 1;
    if (str != NULL)
        while (p2 > p1) {
            char temp = *p1;
            *p1 = *p2;
            *p2 = temp;
            p1++;
            p2--;
        }
    return str;
}