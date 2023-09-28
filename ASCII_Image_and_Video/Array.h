/****************************************************************
 * Project Name:  ASCII_Image_and_Video
 * File Name:     Array.h
 * File Function: Array类的头文件
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/9/27
 ****************************************************************/

#pragma once
#include <iostream>

/* Macro definition */
#define HIGHEST_DIMENSION 16

/* Define constant variables */
const int consoleWindowsSize = 150;
const char asciiStrength[] = { '@','M','N','H','Q','$','O','C','?','7','1','>','!',':','-','.' };
const enum Operation { Add, Sub, Mul, Div, Opp, MatMulNum, NumMulMat, MatDivNum, NumDivMat };

/* Define Array class */
class Array {
private:
    /* Define private data members */
    int* data = NULL;
    int shape[HIGHEST_DIMENSION] = { 0 };
    int axisNum = 0;
    int nowAxis = 0;
    int index = 0;
    int len = 1;
    bool check = true;

    /* Function declarations in Array.cpp */
    void checkTypes(bool is_index);
    int calculateOffset(int indexs[]);
    bool is_homogeneous_matrix(Array& a, Array& b);
    Array elementwiseOperation(Array& arr, Operation optn);

    /*
     * Function Name:    isTypeSame
     * Function:         Return false when the function types are different
     * Input Parameters: T1
     *                   T2
     * Return Value:     false
     */
    template <typename T1, typename T2>
    bool isTypeSame(T1, T2)
    {
        return false;
    }

    /*
     * Function Name:    isTypeSame
     * Function:         Return true when the function types are same
     * Input Parameters: T
     *                   T
     * Return Value:     true
     */
    template <typename T>
    bool isTypeSame(T, T)
    {
        return true;
    }

    /*
     * Function Name:    checkType
     * Function:         Check if the data type is int and if the data is correct
     * Input Parameters: bool is_index
     *                   const T& arg
     * Return Value:     void
     */
    template <typename T>
    void checkType(bool is_index, const T& arg)
    {
        if (!isTypeSame(arg, int()) || (is_index ? false : arg < 1))
            exit(-1);
    }

    /*
     * Function Name:    checkTypes
     * Function:         Recursively unpack a parameter tuple
     * Input Parameters: bool is_index
     *                   const T& arg
     *                   const Args&... args
     * Return Value:     void
     */
    template <typename T, typename... Args>
    void checkTypes(bool is_index, const T& arg, const Args&... args)
    {
        checkType(is_index, arg);
        checkTypes(is_index, args...);
    }

public:
    /* Function declarations in Array.cpp */
    Array();
    Array(const Array& other);
    ~Array();
    void set(int value);
    int* get_content(void);
    Array operator[](int n);
    Array& operator=(int value);
    Array operator+(Array& arr);
    Array operator-(void);
    Array operator-(Array& arr);
    Array operator*(Array& arr);
    Array operator/(Array& arr);
    operator int(void);

    /* Friend function declarations in Array.cpp */
    friend std::ostream& operator<<(std::ostream& out, const Array& arr);
    friend std::istream& operator>>(std::istream& in, Array& arr);
    friend Array elementwiseOperation(Array& arr, int n, Operation optn);
    friend Array operator*(Array& arr, int n);
    friend Array operator*(int n, Array& arr);
    friend Array operator/(Array& arr, int n);
    friend Array operator/(int n, Array& arr);

    /* Friend function declarations in Matrix.cpp */
    friend void input(Array& arr, char name);

    /*
     * Function Name:    Array
     * Function:         Constructed function
     * Input Parameters: Args... args
     * Notes:            If the parameter packet size is greater than 0, then validate the correctness of the parameters
     */
    template <typename... Args>
    Array(Args... args)
    {
        checkTypes(false, args...);
        axisNum = sizeof...(args);
        nowAxis = axisNum;
        int list[] = { args... };
        for (int i = 0; i < axisNum; i++)
            shape[i] = list[i];
        for (int i = 0; i < axisNum; i++)
            len *= shape[i];
        data = new(std::nothrow) int[len] {0};
        if (data == NULL)
            exit(-1);
    }

    /*
     * Function Name:    at
     * Function:         Modify the value of the index and return the Array class itself
     * Input Parameters: Args... args
     * Return Value:     *this
     * Notes:            Used in conjunction with the set function
     */
    template <typename... Args>
    Array& at(Args... args)
    {
        if (axisNum != sizeof...(args))
            exit(-1);
        checkTypes(true, args...);
        int* indexs = new(std::nothrow) int[axisNum] {args...};
        if (indexs == NULL)
            exit(-1);
        for (int i = 0; i < axisNum; i++)
            if (indexs[i] >= shape[i] || indexs[i] < 0)
                exit(-1);
        index = calculateOffset(indexs);
        delete[] indexs;
        return *this;
    }

    /*
     * Function Name:    reshape
     * Function:         Reshape a matrix into a matrix of different dimensions
     * Input Parameters: Args... args
     * Return Value:     void
     */
    template <typename... Args>
    void reshape(Args... args)
    {
        checkTypes(false, args...);
        axisNum = sizeof...(args);
        nowAxis = axisNum;
        int list[] = { args... };
        for (int i = 0; i < HIGHEST_DIMENSION; i++)
            shape[i] = ((i < axisNum) ? list[i] : 0);
        int newLen = 1;
        for (int i = 0; i < axisNum; i++)
            newLen *= shape[i];
        if (newLen != len)
            exit(-1);
    }
};