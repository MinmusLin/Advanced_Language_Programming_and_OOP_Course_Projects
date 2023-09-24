/****************************************************************
 * Project Name:  Gluttonous_Snake
 * File Name:     gluttonous_snake_file.cpp
 * File Function: 历史最高分记录函数的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/9/24
 ****************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include "gluttonous_snake.h"
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
 * Input Parameters: Mode mode
 *                   int score
 * Return Value:     void
 */
void updateHighestScore(Mode mode, int score)
{
    int highestScore[MODE_NUMBER];
    readArrayFromFile("data/highest_score.dat", highestScore, MODE_NUMBER);
    highestScore[mode] = score;
    saveArrayToFile("data/highest_score.dat", highestScore, MODE_NUMBER);
}

/*
 * Function Name:    readHighestScore
 * Function:         Read highest score
 * Input Parameters: Mode mode
 * Return Value:     highest score
 */
int readHighestScore(Mode mode)
{
    int highestScore[MODE_NUMBER];
    readArrayFromFile("data/highest_score.dat", highestScore, MODE_NUMBER);
    return highestScore[mode];
}

/*
 * Function Name:    resetHighestScore
 * Function:         Reset highest score
 * Input Parameters: void
 * Return Value:     void
 */
void resetHighestScore(void)
{
    int highestScore[MODE_NUMBER] = { 0 };
    saveArrayToFile("data/highest_score.dat", highestScore, MODE_NUMBER);
}