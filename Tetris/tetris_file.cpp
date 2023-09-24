/****************************************************************
 * Project Name:  Tetris
 * File Name:     tetris_file.cpp
 * File Function: 历史最高分记录函数的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/9/25
 ****************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include "tetris.h"
using namespace std;

/*
 * Function Name:    saveArrayToFile
 * Function:         Save array to file
 * Input Parameters: const char* filename
 *                   T* array
 *                   size_t size
 * Return Value:     void
 */
template <typename T>
static void saveArrayToFile(const char* filename, T* array, size_t size)
{
    FILE* file = fopen(filename, "wb");
    if (file == NULL)
        exit(-1);
    fwrite(array, sizeof(T), size, file);
    fclose(file);
}

/*
 * Function Name:    readArrayFromFile
 * Function:         Read array from file
 * Input Parameters: const char* filename
 *                   T* array
 *                   size_t size
 * Return Value:     void
 */
template <typename T>
static void readArrayFromFile(const char* filename, T* array, size_t size)
{
    FILE* file = fopen(filename, "rb");
    if (file == NULL)
        exit(-1);
    fread(array, sizeof(T), size, file);
    fclose(file);
}

/*
 * Function Name:    updateHighestScore
 * Function:         Update highest score
 * Input Parameters: int score
 * Return Value:     void
 */
void updateHighestScore(int score)
{
    int highestScore[1] = { score };
    saveArrayToFile("data/highest_score.dat", highestScore, 1);
}

/*
 * Function Name:    readHighestScore
 * Function:         Read highest score
 * Input Parameters: void
 * Return Value:     highest score
 */
int readHighestScore(void)
{
    int highestScore[1];
    readArrayFromFile("data/highest_score.dat", highestScore, 1);
    return highestScore[0];
}