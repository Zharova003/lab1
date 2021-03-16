#include "matrix.h"

Matrix sumMatrix(const Matrix *x1, const Matrix *x2) {

    if (x1->arr == NULL || x2->arr == NULL)
        Throw(NULL_POINTER);
    if (x1->sum == NULL)
        Throw(NO_SUMMAT);
    if (x1->sum != x2->sum)
        Throw(DIFF_SUM);
    if (x1->column <= 0)
        Throw(WRONG_DIMENSION);
    if (x1->row <= 0)
        Throw(WRONG_DIMENSION);
    if (x1->column != x2->column || x1->row != x2->row)
        Throw(WRONG_SHAPE);
    if (x1->elementSize <= 0 || x2->elementSize <= 0)
        Throw(WRONG_ELEMENT_SIZE);
    if (x1->elementSize != x2->elementSize)
        Throw(DIFFERENT_ELEMENT_SIZE);

    void *result_arr = malloc(x1->row * x1->column * x1->elementSize);

    Matrix result = {result_arr, x1->row, x1->column, x1->elementSize, x1->sum};

    if (x1->multi != NULL)
        result.multi = x1->multi;

    for (size_t i = 0; i < x1->row; i++) {
        for (size_t j = 0; j < x1->column; j++) {

            //ещё нужны проверки на переполнение
            //то есть, например, если сложим MAX_INT_SIZE + 1
            //посмотри у меня в работе или погугли
            memcpy(result.arr + i * x1->elementSize * x1->column + j * x1->elementSize,
                   x1->sum(x1->arr + i * x1->elementSize * x1->column + j * x1->elementSize,
                           x2->arr + i * x1->elementSize * x1->column + j * x1->elementSize),
                   x1->elementSize);
        }
    }
    return result;
}



Matrix multiMatrix(const Matrix *x1, const Matrix *x2) {
    if (x1->arr == NULL || x2->arr == NULL)
        Throw(NULL_POINTER);
    if (x1->multi == NULL)
        Throw(NO_MULTI);
    if (x1->multi != x2->multi)
        Throw(DIFF_MULTI);
    if (x1->column <= 0)
        Throw(WRONG_DIMENSION);
    if (x1->row <= 0)
        Throw(WRONG_DIMENSION);
    if (x1->column != x2->row)
        Throw(WRONG_SHAPE);
    if (x1->sum == NULL)
        Throw(NO_SUMMAT);
    if (x1->sum != x2->sum)
        Throw(DIFF_SUM);
    if (x1->elementSize <= 0 || x2->elementSize <= 0)
        Throw(WRONG_ELEMENT_SIZE);
    if (x1->elementSize != x2->elementSize)
        Throw(DIFFERENT_ELEMENT_SIZE);


    void *result_arr = malloc(x1->column * x2->row * x1->elementSize);

    Matrix result = {result_arr, x1->row, x2->column, x1->elementSize};

    result.multi = x1->multi;

    if (x1->sum != NULL)
        result.sum = x1->sum;

    for (size_t i = 0; i < x1->row; i++) {
        for (size_t j = 0; j < x2->column; j++) {
            void *result_sum = calloc(1, x1->elementSize);
            for (size_t k = 0; k < x1->column; k++) {

                result_sum = x1->sum(result_sum,
                                     x1->multi(x1->arr + i * x1->elementSize * x1->column + k * x1->elementSize,
                                               x2->arr + k * x2->elementSize * x2->column + j * x2->elementSize));


            }
            memcpy(result.arr + i * x1->elementSize * x2->column + j * x1->elementSize,
                   result_sum,
                   x1->elementSize);


        }
    }
    return result;
}

Matrix transpose(const Matrix *matrix) {
    if (matrix->arr == NULL)
        Throw(NULL_POINTER);
    if (matrix->column <= 0)
        Throw(WRONG_DIMENSION);
    if (matrix->row <= 0)
        Throw(WRONG_DIMENSION);
    if (matrix->elementSize <= 0)
        Throw(WRONG_ELEMENT_SIZE);

    void *result_arr = malloc(matrix->column * matrix->row * matrix->elementSize);

    Matrix result = {result_arr, matrix->column, matrix->row, matrix->elementSize, matrix->sum, matrix->multi};

    for (size_t i = 0; i < matrix->row; i++) {
        for (size_t j = 0; j < matrix->column; j++) {
            memcpy(result.arr + j * result.elementSize * result.column + i * result.elementSize,
                   matrix->arr + i * matrix->elementSize * matrix->column + j * matrix->elementSize,
                   result.elementSize);
        }
    }
    return result;
}

void linearCombinationRow (Matrix *matrix, size_t number_rows, size_t change_row, const void *numbers_row, const void *coefficients) {
    if (matrix->arr == NULL)
        Throw(NULL_POINTER);
    if (matrix->column <= 0)
        Throw(WRONG_DIMENSION);
    if (matrix->row <= 1)
        Throw(WRONG_DIMENSION);
    if (matrix->elementSize <= 0)
        Throw(WRONG_ELEMENT_SIZE);
    if (matrix->sum == NULL)
        Throw(NO_SUMMAT);
    if (matrix->multi == NULL)
        Throw(NO_MULTI);
    if (number_rows <= 0 || change_row <= 0)
        Throw(WRONG_SHAPE);
    if (numbers_row == NULL || coefficients == NULL)
        Throw(NULL_POINTER);

    for (size_t i = 0, j; i < matrix->column; i++) {
        void *result_sum = calloc(1, matrix->elementSize);

        result_sum = matrix->arr + (change_row - 1) * matrix->column * matrix->elementSize + i * matrix->elementSize;

        for (j = 0; j < number_rows; j++) {

            result_sum = matrix->sum(result_sum, matrix->multi(coefficients + j * matrix->elementSize,
                                                               matrix->arr + i * matrix->elementSize + (number_rows + j*matrix->elementSize) * matrix->column * matrix->elementSize));
        }
        memcpy(matrix->arr + (change_row - 1) * matrix->column * matrix->elementSize + i * matrix->elementSize, result_sum, matrix->elementSize);

    }
}

int *sumInt (const int *x1, const int *x2)
{
    if (*((int *)x1) > (INT_MAX - *((int *)(x2))))
        Throw(OVERFLOW_EL);
    int *result = calloc(1, sizeof(int));
    *result = *x1 + *x2;
    return result;
}

int *multiInt (const int *x1, const int *x2)
{
    if (*((int *)x1) > (INT_MAX / *((int *)(x2))))
        Throw(OVERFLOW_EL);

    int *result = calloc(1, sizeof(int));
    *result = *x1 * *x2;
    return result;
}

float *sumReal (const float *x1, const float *x2) {
    float *result = calloc(1, sizeof(float));
    *result = *x1 + *x2;
    return result;
}
float *multiReal (const float *x1, const float *x2) {
    float *result = calloc(1, sizeof(float));
    *result = *x1 * *x2;
    return result;
}

Matrix enterIntMatrix() {
    int m, n;
    printf("enter shape of matrix: \n m ");
    scanf("%d", &m);
    getchar();
    printf("\n n ");
    scanf("%d", &n);
    getchar();

    if (n <= 0 || m <=0)
        Throw(WRONG_DIMENSION);
    
    int result_arr[m][n];
    for (int i = 0; i < m; i++) {
        for (int j = 0; i < n; j++) {
            scanf("%d", &result_arr[i][j]);
        }
    }
    Matrix result = {result_arr, m, n, sizeof(int), sumInt, multiInt};
    return result;
}

Matrix enterRealMatrix(){
    int m, n;
    printf("enter shape of matrix: \n m ");
    scanf("%d", &m);
    getchar();
    printf("\n n ");
    scanf("%d", &n);
    getchar();

    if (n <= 0 || m <=0)
        Throw(WRONG_DIMENSION);

    float result_arr[m][n];
    for (int i = 0; i < m; i++) {
        for (int j = 0; i < n; j++) {
            scanf("%f", &result_arr[i][j]);
        }
    }
    Matrix result = {result_arr, m, n, sizeof(float), sumReal, multiReal};
    return result;
}

void printIntMatrix(const Matrix *matrix) {
    for (size_t i = 0; i < matrix->row; i++) {
        for (size_t j = 0; j < matrix->column; j++)
            printf("%d ",
                   *((int *) (matrix->arr + i * matrix->elementSize * matrix->column + j * matrix->elementSize)));
        printf("\n");
    }
}

void printRealMatrix (const Matrix *matrix) {
    for (size_t i = 0; i < matrix->row; i++) {
        for (size_t j = 0; j < matrix->column; j++)
            printf("%f ",
                   *((float *) (matrix->arr + i * matrix->elementSize * matrix->column + j * matrix->elementSize)));
        printf("\n");
    }
}