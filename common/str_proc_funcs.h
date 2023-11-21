/****************************************************************
 * Project Name:  common
 * File Name:     str_proc_funcs.h
 * File Function: 字符串处理函数工具集的头文件
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/11/21
 ****************************************************************/

#pragma once
#ifndef STR_PROC_FUNCS_H
#define STR_PROC_FUNCS_H

/* Function declarations in str_proc_funcs.cpp */
int strlen_array(const char str[]);
int strcat_array(char s1[], const char s2[]);
int strncat_array(char s1[], const char s2[], const int len);
int strcpy_array(char s1[], const char s2[]);
int strncpy_array(char s1[], const char s2[], const int len);
int strcmp_array(const char s1[], const char s2[]);
int strcasecmp_array(const char s1[], const char s2[]);
int strncmp_array(const char s1[], const char s2[], const int len);
int strcasencmp_array(const char s1[], const char s2[], const int len);
int strupr_array(char str[]);
int strlwr_array(char str[]);
int strchr_array(const char str[], char ch);
int strstr_array(const char str[], const char substr[]);
int strrchr_array(const char str[], const char ch);
int strrstr_array(const char str[], const char substr[]);
int strrev_array(char str[]);
int strlen_pointer(const char* str);
char* strcat_pointer(char* s1, const char* s2);
char* strncat_pointer(char* s1, const char* s2, const int len);
char* strcpy_pointer(char* s1, const char* s2);
char* strncpy_pointer(char* s1, const char* s2, const int len);
int strcmp_pointer(const char* s1, const char* s2);
int strcasecmp_pointer(const char* s1, const char* s2);
int strncmp_pointer(const char* s1, const char* s2, const int len);
int strcasencmp_pointer(const char* s1, const char* s2, const int len);
char* strupr_pointer(char* str);
char* strlwr_pointer(char* str);
int strchr_pointer(const char* str, const char ch);
int strstr_pointer(const char* str, const char* substr);
int strrchr_pointer(const char* str, const char ch);
int strrstr_pointer(const char* str, const char* substr);
char* strrev_pointer(char* str);

#endif // !STR_PROC_FUNCS_H