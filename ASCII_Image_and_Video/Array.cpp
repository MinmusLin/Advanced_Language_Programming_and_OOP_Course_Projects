/****************************************************************
 * Project Name:  ASCII_Image_and_Video
 * File Name:     Array.cpp
 * File Function: Array类的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/10/26
 ****************************************************************/

#include <iostream>
#include "Array.h"

using namespace std;

/*
 * Function Name:    checkTypes
 * Function:         Terminate the recursive unpacking of the parameter tuple
 * Input Parameters: bool is_index
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void Array::checkTypes(bool is_index)
{
    return;
}

/*
 * Function Name:    calculateOffset
 * Function:         Calculate offset
 * Input Parameters: int indexs[]
 * Return Value:     offset
 * Notes:            Class external implementation of member functions
 */
int Array::calculateOffset(int indexs[])
{
    int offset = 0, stride = 1;
    for (int i = axisNum - 1; i >= 0; i--) {
        offset += indexs[i] * stride;
        stride *= shape[i];
    }
    return offset;
}

/*
 * Function Name:    is_homogeneous_matrix
 * Function:         Determine if two matrices are of the same type
 * Input Parameters: Array& a
 *                   Array& b
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
bool Array::is_homogeneous_matrix(Array& a, Array& b)
{
    if (a.axisNum != b.axisNum || a.len != b.len)
        return false;
    else {
        for (int i = 0; i < a.axisNum; i++)
            if (a.shape[i] != b.shape[i])
                return false;
        return true;
    }
}

/*
 * Function Name:    elementwiseOperation
 * Function:         Overload element-wise operation
 * Input Parameters: Array& arr
 *                   Operation optn
 * Return Value:     result
 * Notes:            Class external implementation of member functions
 */
Array Array::elementwiseOperation(Array& arr, Operation optn)
{
    if (!is_homogeneous_matrix(*this, arr))
        exit(-1);
    Array result;
    for (int i = 0; i < HIGHEST_DIMENSION; i++)
        result.shape[i] = shape[i];
    result.axisNum = axisNum;
    result.nowAxis = nowAxis;
    result.len = len;
    result.check = false;
    delete[] result.data;
    result.data = new(nothrow) int[result.len];
    if (result.data == NULL)
        exit(-1);
    for (int i = 0; i < result.len; i++)
        switch (optn) {
            case Add:
                result.data[i] = data[i] + arr.data[i];
                break;
            case Sub:
                result.data[i] = data[i] - arr.data[i];
                break;
            case Mul:
                result.data[i] = data[i] * arr.data[i];
                break;
            case Div:
                result.data[i] = data[i] / arr.data[i];
                break;
            case Opp:
                result.data[i] = -data[i];
                break;
            default:
                exit(-1);
        }
    return result;
}

/*
 * Function Name:    Array
 * Function:         Constructed function
 * Notes:            Class external implementation of member functions
 *                   If the parameter packet size is 0, force the program to terminate and return an error code
 */
Array::Array()
{
    check = true;
}

/*
 * Function Name:    Array
 * Function:         Constructed function
 * Input Parameters: const Array& other
 * Notes:            Class external implementation of member functions
 */
Array::Array(const Array& other)
{
    data = other.data;
    for (int i = 0; i < HIGHEST_DIMENSION; i++)
        shape[i] = other.shape[i];
    axisNum = other.axisNum;
    nowAxis = other.nowAxis;
    index = other.index;
    len = other.len;
    check = other.check;
}

/*
 * Function Name:    ~Array
 * Function:         Destructor
 * Notes:            Class external implementation of member functions
 */
Array::~Array()
{
    if (check)
        delete[] data;
}

/*
 * Function Name:    set
 * Function:         Set the value of a specific element in an array
 * Input Parameters: int value
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 *                   Used in conjunction with the at function
 */
void Array::set(int value)
{
    if (nowAxis == 0)
        this->data[index] = value;
    else
        exit(-1);
}

/*
 * Function Name:    get_content
 * Function:         Retrieve the starting address of the internal array
 * Input Parameters: void
 * Return Value:     data
 * Notes:            Class external implementation of member functions
 */
int* Array::get_content(void)
{
    return data;
}

/*
 * Function Name:    operator[]
 * Function:         Overload operator []
 * Input Parameters: int n
 * Return Value:     copy
 * Notes:            Class external implementation of member functions
 */
Array Array::operator[](int n)
{
    if (!isTypeSame(n, int()) || n < 0 || n >= *shape)
        exit(-1);
    Array copy;
    copy.check = false;
    copy.data = data;
    copy.axisNum = axisNum;
    copy.nowAxis = nowAxis - 1;
    for (int i = 0; i < nowAxis; i++)
        copy.shape[i] = shape[i + 1];
    int product = n;
    for (int i = 0; i < copy.nowAxis; i++)
        product *= copy.shape[i];
    int _index = index;
    _index += product;
    copy.index = _index;
    for (int i = 0; i < copy.nowAxis; i++)
        copy.len *= copy.shape[i];
    return copy;
}

/*
 * Function Name:    operator=
 * Function:         Overload operator =
 * Input Parameters: int value
 * Return Value:     *this
 * Notes:            Class external implementation of member functions
 */
Array& Array::operator=(int value)
{
    data[index] = value;
    return *this;
}

/*
 * Function Name:    operator+
 * Function:         Overload operator +
 * Input Parameters: Array& arr
 * Return Value:     result
 * Notes:            Class external implementation of member functions
 *                   Element-wise operation
 */
Array Array::operator+(Array& arr)
{
    return elementwiseOperation(arr, Add);
}

/*
 * Function Name:    operator-
 * Function:         Overload operator -
 * Input Parameters: void
 * Return Value:     result
 * Notes:            Class external implementation of member functions
 *                   Element-wise operation
 */
Array Array::operator-(void)
{
    return elementwiseOperation(*this, Opp);
}

/*
 * Function Name:    operator-
 * Function:         Overload operator -
 * Input Parameters: Array& arr
 * Return Value:     result
 * Notes:            Class external implementation of member functions
 *                   Element-wise operation
 */
Array Array::operator-(Array& arr)
{
    return elementwiseOperation(arr, Sub);
}

/*
 * Function Name:    operator*
 * Function:         Overload operator *
 * Input Parameters: Array& arr
 * Return Value:     result
 * Notes:            Class external implementation of member functions
 *                   Element-wise operation
 */
Array Array::operator*(Array& arr)
{
    return elementwiseOperation(arr, Mul);
}

/*
 * Function Name:    operator/
 * Function:         Overload operator /
 * Input Parameters: Array& arr
 * Return Value:     result
 * Notes:            Class external implementation of member functions
 *                   Element-wise operation
 */
Array Array::operator/(Array& arr)
{
    return elementwiseOperation(arr, Div);
}

/*
 * Function Name:    operator int
 * Function:         Overload operator int
 * Input Parameters: void
 * Return Value:     data[index]
 * Notes:            Class external implementation of member functions
 */
Array::operator int(void)
{
    return data[index];
}

/*
 * Function Name:    operator<<
 * Function:         Overload operator <<
 * Input Parameters: std::ostream& out
 *                   const Array& arr
 * Return Value:     out
 */
std::ostream& operator<<(std::ostream& out, const Array& arr)
{
    out << "[" << *arr.data;
    for (int i = 1; i < arr.len; i++)
        out << "," << arr.data[i];
    out << "]";
    return out;
}

/*
 * Function Name:    operator>>
 * Function:         Overload operator >>
 * Input Parameters: std::ostream& in
 *                   Array& arr
 * Return Value:     in
 */
std::istream& operator>>(std::istream& in, Array& arr)
{
    for (int i = 0; i < arr.len; i++) {
        int n;
        in >> n;
        if (in.fail())
            exit(-1);
        arr.data[i] = n;
    }
    return in;
}

/*
 * Function Name:    elementwiseOperation
 * Function:         Overload element-wise operation
 * Input Parameters: Array& arr
 *                   int n
 *                   Operation optn
 * Return Value:     result
 */
Array elementwiseOperation(Array& arr, int n, Operation optn)
{
    Array result;
    result.check = false;
    result.axisNum = arr.axisNum;
    for (int i = 0; i < HIGHEST_DIMENSION; i++)
        result.shape[i] = arr.shape[i];
    result.len = arr.len;
    delete[] result.data;
    result.data = new(nothrow) int[result.len];
    if (result.data == NULL)
        exit(-1);
    for (int i = 0; i < result.len; i++)
        switch (optn) {
            case MatMulNum:
                result.data[i] = arr.data[i] * n;
                break;
            case NumMulMat:
                result.data[i] = n * arr.data[i];
                break;
            case MatDivNum:
                result.data[i] = arr.data[i] / n;
                break;
            case NumDivMat:
                result.data[i] = n / arr.data[i];
                break;
            default:
                exit(-1);
        }
    return result;
}

/*
 * Function Name:    operator*
 * Function:         Overload operator *
 * Input Parameters: Array& arr
 *                   int n
 * Return Value:     result
 * Notes:            Element-wise operation
 */
Array operator*(Array& arr, int n)
{
    return elementwiseOperation(arr, n, MatMulNum);
}

/*
 * Function Name:    operator*
 * Function:         Overload operator *
 * Input Parameters: int n
 *                   Array& arr
 * Return Value:     result
 * Notes:            Element-wise operation
 */
Array operator*(int n, Array& arr)
{
    return elementwiseOperation(arr, n, NumMulMat);
}

/*
 * Function Name:    operator/
 * Function:         Overload operator /
 * Input Parameters: Array& arr
 *                   int n
 * Return Value:     result
 * Notes:            Element-wise operation
 */
Array operator/(Array& arr, int n)
{
    return elementwiseOperation(arr, n, MatDivNum);
}

/*
 * Function Name:    operator/
 * Function:         Overload operator /
 * Input Parameters: int n
 *                   Array& arr
 * Return Value:     result
 * Notes:            Element-wise operation
 */
Array operator/(int n, Array& arr)
{
    return elementwiseOperation(arr, n, NumDivMat);
}