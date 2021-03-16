#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>


#include "CException.h"

//основная структура
typedef struct Matrix
{
    void *arr;

    size_t row;
    size_t column;
    size_t elementSize;

    void *(*sum) (const void *x1, const void *x2);

    void *(*multi) (const void *x1, const void *x2);

} Matrix;


//основные функции

//суммирование матриц
Matrix sumMatrix (const Matrix *x1, const Matrix *x2);

//умножение матриц
Matrix multiMatrix (const Matrix *x1, const Matrix *x2);

//транспонирование11
Matrix transpose (const Matrix *matrix);

//линейная комбинация строк
void linearCombinationRow (Matrix *matrix, size_t number_rows, size_t change_row, const void *numbers_row, const void *coefficients);


//для обработки исключений
enum ERRORCODE_T
{
    NULL_POINTER,
    WRONG_ELEMENT_SIZE,
    DIFFERENT_ELEMENT_SIZE,
    WRONG_DIMENSION,
    NO_SUMMAT,
    NO_MULTI,
    WRONG_SHAPE,
    DIFF_SUM,
    DIFF_MULTI,
    OVERFLOW_EL
};

Matrix enterIntMatrix();
Matrix enterRealMatrix();

//функции вывода
void printIntMatrix (const Matrix *matrix);
void printRealMatrix (const Matrix *matrix);

int *sumInt (const int *x1, const int *x2);
int *multiInt (const int *x1, const int *x2);

float *sumReal (const float *x1, const float *x2);
float *multiReal (const float *x1, const float *x2);
#endif //MATRIX_H
