/****************************************************************
 * Project Name:  common
 * File Name:     str_proc_funcs.cpp
 * File Function: �ַ������������߼���ʵ��
 * Author:        Jishen Lin (�ּ���)
 * Update Date:   2023/9/28
 ****************************************************************/

#include "../common/str_proc_funcs.h"

using namespace std;

/*
 * Function Name:    strlen_array
 * Function:         ���ַ���str�ĳ���(���鷨ʵ��)
 * Input Parameters: const char str[]: �ַ�����str
 * Return Value:     �ַ�������
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
 * Function:         ���ַ���s2׷�ӵ�s1���棬��\0(���鷨ʵ��)
 * Input Parameters: char s1[]: �ַ�����s1
 *                   const char s2[]: �ַ�����s2
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
 * Function:         ���ַ���s2��ǰlen���ַ�׷�ӵ�s1���棬�����\0(���鷨ʵ��)
 * Input Parameters: char s1[]: �ַ�����s1
 *                   const char s2[]: �ַ�����s2
 *                   const int len: ����
 * Return Value:     0
 * Notes:            ��len��s2�ĳ��ȴ���׷������s2����(��\0)
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
 * Function:         ���ַ���s2���Ƶ�s1�У�����s1��ԭ���ݣ�����ʱ����\0(���鷨ʵ��)
 * Input Parameters: char s1[]: �ַ�����s1
 *                   const char s2[]: �ַ�����s2
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
 * Function:         ���ַ���s2��ǰlen���ַ����Ƶ�s1�У�����ʱ����\0(���鷨ʵ��)
 * Input Parameters: char s1[]: �ַ�����s1
 *                   const char s2[]: �ַ�����s2
 *                   const int len : ����
 * Return Value:     0
 * Notes:            ��len��s2�ĳ��ȴ󣬸���s2���ȸ��ַ�����(����\0)
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
 * Function:         �Ƚ��ַ���s1��s2�Ĵ�С��Ӣ����ĸ���ִ�Сд(���鷨ʵ��)
 * Input Parameters: const char s1[]: �ַ�����s1
 *                   const char s2[]: �ַ�����s2
 * Return Value:     0 / ��1��������ַ���ASCII��ֵ
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
 * Function:         �Ƚ��ַ���s1��s2�Ĵ�С��Ӣ����ĸ�����ִ�Сд(���鷨ʵ��)
 * Input Parameters: const char s1[]: �ַ�����s1
 *                   const char s2[]: �ַ�����s2
 * Return Value:     0 / ��1��������ַ���ASCII��ֵ
 * Notes:            ������ȴ��ַ��ǲ�ͬ�Ĵ�Сд��ĸ����ͳһת��ΪСд��Ƚ�
 *                   ������ȴ��ַ��Ǵ�д��ĸ�������ַ����򷵻ض�ӦСд��ĸ�������ַ��Ĳ�ֵ
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
 * Function:         �Ƚ��ַ���s1��s2��ǰlen���ַ��Ĵ�С��Ӣ����ĸ���ִ�Сд(���鷨ʵ��)
 * Input Parameters: const char s1[]: �ַ�����s1
 *                   const char s2[]: �ַ�����s2
 *                   const int len : ����
 * Return Value:     0 / ��1��������ַ���ASCII��ֵ
 * Notes:            ��len����s1/s2�г��ȶ̵Ĵ�����Ƚϵ��̴���\0������
 *                   ������ȴ��ַ��ǲ�ͬ�Ĵ�Сд��ĸ����ͳһת��ΪСд��Ƚ�
 *                   ������ȴ��ַ��Ǵ�д��ĸ�������ַ����򷵻ض�ӦСд��ĸ�������ַ��Ĳ�ֵ
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
 * Function:         �Ƚ��ַ���s1��s2��ǰlen���ַ��Ĵ�С��Ӣ����ĸ�����ִ�Сд(���鷨ʵ��)
 * Input Parameters: const char s1[]: �ַ�����s1
 *                   const char s2[]: �ַ�����s2
 *                   const int len: ����
 * Return Value:     0 / ��1��������ַ���ASCII��ֵ
 * Notes:            ��len����s1/s2�г��ȶ̵Ĵ�����Ƚϵ��̴���\0������
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
 * Function:         ���ַ���str������Сд��ĸתΪ��д�������ַ����䣬ת�������ԭ����(���鷨ʵ��)
 * Input Parameters: char str[]: �ַ�����str
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
 * Function:         ���ַ���str������Сд��ĸתΪ��д�������ַ����䣬ת�������ԭ����(���鷨ʵ��)
 * Input Parameters: char str[]: �ַ�����str
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
 * Function:         ���ַ���str��Ѱ���ַ�ch��1�γ��ֵ�λ�ã�˳���Ǵ�����(���鷨ʵ��)
 * Input Parameters: const char str[]: �ַ�����str
 *                   char ch: �ַ�
 * Return Value:     0 / λ��
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
 * Function:         ���ַ���str��Ѱ���ַ���substr��1�γ��ֵ�λ�ã�˳���Ǵ�����(���鷨ʵ��)
 * Input Parameters: const char str[]: �ַ�����str
 *                   const char substr[]: �ַ�����substr
 * Return Value:     0 / λ��
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
 * Function:         ���ַ���str��Ѱ���ַ�ch��1�γ��ֵ�λ�ã�˳���Ǵ��ҵ���(���鷨ʵ��)
 * Input Parameters: const char str[]: �ַ�����str
 *                   char ch: �ַ�
 * Return Value:     0 / λ��
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
 * Function:         ���ַ���str��Ѱ���ַ���substr��1�γ��ֵ�λ�ã�˳���Ǵ��ҵ���(���鷨ʵ��)
 * Input Parameters: const char str[]: �ַ�����str
 *                   const char substr[]: �ַ�����substr
 * Return Value:     0 / λ��
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
 * Function:         �ַ�����ת������ԭ����(���鷨ʵ��)
 * Input Parameters: char str[]: �ַ�����str
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
 * Function:         ���ַ���str�ĳ���(ָ�뷨ʵ��)
 * Input Parameters: const char* str: �ַ�����str��ָ��
 * Return Value:     �ַ�������
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
 * Function:         ���ַ���s2׷�ӵ�s1���棬��\0(ָ�뷨ʵ��)
 * Input Parameters: char* s1: �ַ�����s1��ָ��
 *          const char* s2: �ַ�����s2��ָ��
 * Return Value:     �ַ�����s1��ָ��
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
 * Function:         ���ַ���s2��ǰlen���ַ�׷�ӵ�s1���棬�����\0(ָ�뷨ʵ��)
 * Input Parameters: char* s1: �ַ�����s1��ָ��
 *                   const char* s2: �ַ�����s2��ָ��
 *                   const int len: ����
 * Return Value:     �ַ�����s1��ָ��
 * Notes:            ��len��s2�ĳ��ȴ���׷������s2����(��\0)
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
 * Function:         ���ַ���s2���Ƶ�s1�У�����s1��ԭ���ݣ�����ʱ����\0(ָ�뷨ʵ��)
 * Input Parameters: char* s1: �ַ�����s1��ָ��
 *                   const char* s2: �ַ�����s2��ָ��
 * Return Value:     �ַ�����s1��ָ��
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
 * Function:         ���ַ���s2��ǰlen���ַ����Ƶ�s1�У�����ʱ����\0(ָ�뷨ʵ��)
 * Input Parameters: char* s1: �ַ�����s1��ָ��
 *                   const char* s2: �ַ�����s2��ָ��
 *                   const int len: ����
 * Return Value:     �ַ�����s1��ָ��
 * Notes:            ��len��s2�ĳ��ȴ󣬸���s2���ȸ��ַ�����(����\0)
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
 * Function:         �Ƚ��ַ���s1��s2�Ĵ�С��Ӣ����ĸ���ִ�Сд(ָ�뷨ʵ��)
 * Input Parameters: const char* s1: �ַ�����s1��ָ��
 *                   const char* s2: �ַ�����s2��ָ��
 * Return Value:     0 / ��1��������ַ���ASCII��ֵ
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
 * Function:         �Ƚ��ַ���s1��s2�Ĵ�С��Ӣ����ĸ�����ִ�Сд(ָ�뷨ʵ��)
 * Input Parameters: const char* s1: �ַ�����s1��ָ��
 *                   const char* s2: �ַ�����s2��ָ��
 * Return Value:     0 / ��1��������ַ���ASCII��ֵ
 * Notes:            ������ȴ��ַ��ǲ�ͬ�Ĵ�Сд��ĸ����ͳһת��ΪСд��Ƚ�
 *                   ������ȴ��ַ��Ǵ�д��ĸ�������ַ����򷵻ض�ӦСд��ĸ�������ַ��Ĳ�ֵ
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
 * Function:         �Ƚ��ַ���s1��s2��ǰlen���ַ��Ĵ�С��Ӣ����ĸ���ִ�Сд(ָ�뷨ʵ��)
 * Input Parameters: const char* s1: �ַ�����s1��ָ��
 *                   const char* s2: �ַ�����s2��ָ��
 *                   const int len: ����
 * Return Value:     0 / ��1��������ַ���ASCII��ֵ
 * Notes:            ��len����s1/s2�г��ȶ̵Ĵ�����Ƚϵ��̴���\0������
 *                   ������ȴ��ַ��ǲ�ͬ�Ĵ�Сд��ĸ����ͳһת��ΪСд��Ƚ�
 *                   ������ȴ��ַ��Ǵ�д��ĸ�������ַ����򷵻ض�ӦСд��ĸ�������ַ��Ĳ�ֵ
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
 * Function:         �Ƚ��ַ���s1��s2��ǰlen���ַ��Ĵ�С��Ӣ����ĸ�����ִ�Сд(ָ�뷨ʵ��)
 * Input Parameters: const char* s1: �ַ�����s1��ָ��
 *                   const char* s2: �ַ�����s2��ָ��
 *                   const int len: ����
 * Return Value:     0 / ��1��������ַ���ASCII��ֵ
 * Notes:            ��len����s1/s2�г��ȶ̵Ĵ�����Ƚϵ��̴���\0������
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
 * Function:         ���ַ���str������Сд��ĸתΪ��д�������ַ����䣬ת�������ԭ����(ָ�뷨ʵ��)
 * Input Parameters: char* str: �ַ�����str��ָ��
 * Return Value:     �ַ�����str��ָ��
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
 * Function:         ���ַ���str������Сд��ĸתΪ��д�������ַ����䣬ת�������ԭ����(ָ�뷨ʵ��)
 * Input Parameters: char* str: �ַ�����str��ָ��
 * Return Value:     �ַ�����str��ָ��
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
 * Function:         ���ַ���str��Ѱ���ַ�ch��1�γ��ֵ�λ�ã�˳���Ǵ�����(ָ�뷨ʵ��)
 * Input Parameters: const char* str: �ַ�����str��ָ��
 *                   const char ch: �ַ�
 * Return Value:     0 / λ��
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
 * Function:         ���ַ���str��Ѱ���ַ���substr��1�γ��ֵ�λ�ã�˳���Ǵ�����(ָ�뷨ʵ��)
 * Input Parameters: const char* str: �ַ�����str��ָ��
 *                   const char* substr: �ַ�����substr��ָ��
 * Return Value:     0 / λ��
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
 * Function:         ���ַ���str��Ѱ���ַ�ch��1�γ��ֵ�λ�ã�˳���Ǵ��ҵ���(ָ�뷨ʵ��)
 * Input Parameters: const char* str: �ַ�����str��ָ��
 *                   const char ch: �ַ�
 * Return Value:     0 / λ��
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
 * Function:         ���ַ���str��Ѱ���ַ���substr��1�γ��ֵ�λ�ã�˳���Ǵ��ҵ���(ָ�뷨ʵ��)
 * Input Parameters: const char* str: �ַ�����str��ָ��
 *                   const char* substr: �ַ�����substr��ָ��
 * Return Value:     0 / λ��
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
 * Function:         �ַ�����ת������ԭ����(ָ�뷨ʵ��)
 * Input Parameters: char* str: �ַ�����str��ָ��
 * Return Value:     �ַ�����str��ָ��
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