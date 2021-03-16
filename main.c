#include <stdio.h>
#include "matrix.h"

void handlerError (CEXCEPTION_T EXPT);

int dialog (const char *msgs[], int n)
{
    int choice;
    do {
        for (int i = 0; i < n; ++i)
            puts(msgs[i]);
        printf("> ");

        choice = getchar() - '0';
        while (getchar() != '\n');
        if (choice < 0 || choice >= n)
            printf("You're wrong. Try again!\n");

    } while (choice < 0 || choice >= n);

    return choice;
}

const char *MENU[] = {"0. Exit",
                      "1. integer numbers",
                      "2. real numbers"};
const int MENU_SIZE = sizeof(MENU) / sizeof(MENU[0]);

const char *MENU_INT[] = {"0. back",
                          "1. create matrix",
                          "2. sum matrices",
                          "3. multi matrices",
                          "4. transpose matrix",
                          "5. add linear combination"};
const int MENU_INT_SIZE = sizeof(MENU_INT) / sizeof(MENU_INT[0]);


int main ()
{
    int a[3][3] = {1, 2, 3,
                   4, 5, 6,
                   7, 8, 9};
    int a1[3][4] = {1, 2, 3, 4,
                    5, 6, 7, 8,
                    9, 10, 11, 12};
    float c[3][3] = {1.0, 2.0, 3.0,
                     4.0, 5.0, 6.0,
                     7.0, 8.0, 9.0};
    float c1[3][4] = {1.0, 2.0, 3.0, 4.0,
                      2.0, 3.0, 4.0, 5.0,
                      3.0, 4.0, 5.0, 6.0};

    /*int b[3][1] = {1,
                   2,
                   3};

    int c[1][3] = {1, 2, 3};
    int coef[1] = {3};
    int n[1] = {2};*/

    Matrix A = {a, 3, 3, sizeof(int), sumInt, multiInt};
    Matrix A1 = {a1, 3, 4, sizeof(int), sumInt, multiInt};
    Matrix C = {c, 3, 3, sizeof(float), sumReal, multiReal};
    Matrix C1 = {c1, 3, 4, sizeof(float), sumReal, multiReal};
    /*Matrix B = {b, 3, 1, sizeof(int), sumInt, multiInt};
    Matrix C = {c, 1, 3, sizeof(int), sumInt, multiInt};*/
    CEXCEPTION_T EXCEPTION;
    int menu;
    do {
        menu = dialog(MENU, MENU_SIZE);
        switch (menu) {
            case 0:
                break;
            case 1: {
                int menu_int;
                do {
                    menu_int = dialog(MENU_INT, MENU_INT_SIZE);
                    switch (menu_int) {
                        Matrix x1, x2;
                        case 0:
                            break;
                        case 1: {
                            int c;
                            printf("use examples?\n0.no\n1.yes\n");
                            scanf("%d", &c);
                            getchar();
                            if (c) {
                                x1 = A;
                                printIntMatrix(&x1);
                                x2 = A1;
                                printIntMatrix(&x2);
                            } else {
                                Try{
                                    x1 = enterIntMatrix();
                                    x2 = enterIntMatrix();
                                } Catch(EXCEPTION) {
                                    handlerError(EXCEPTION);
                                }
                            }
                        }
                            break;
                        case 2: {
                            int c;
                            printf("use examples?\n0.no\n1.yes\n");
                            scanf("%d", &c);
                            getchar();
                            if (c) {
                                x1 = A;
                                printIntMatrix(&x1);
                                x2 = transpose(&A);
                                printIntMatrix(&x2);
                            }
                            Try {
                                Matrix ANS = sumMatrix(&x1, &x2);
                                printIntMatrix(&ANS);
                            } Catch(EXCEPTION) {
                                handlerError(EXCEPTION);
                            }
                        }
                            break;
                        case 3: {
                            Try {
                                Matrix ANS = multiMatrix(&x1, &x2);
                                printIntMatrix(&ANS);
                            } Catch(EXCEPTION) {
                                handlerError(EXCEPTION);
                            }
                        }
                            break;
                        case 4: {
                            Try {
                                Matrix ANS = transpose(&x1);
                                printIntMatrix(&ANS);
                                ANS = transpose(&x2);
                                printIntMatrix(&ANS);
                            } Catch(EXCEPTION) {
                                handlerError(EXCEPTION);
                            }
                        }
                            break;
                        case 5: {
                            int c;
                            printf("what matrix use?\n0. 1\n1. 2\n");
                            scanf("%d", &c);
                            getchar();
                            Matrix ANS;
                            if (c) {
                                ANS = x2;
                            } else {
                                ANS = x1;
                            }
                            int change_row, number_rows;
                            printf("change row number: ");
                            scanf("%d", &change_row);
                            getchar();
                            printf("how mary rows do you add? ");
                            scanf("%d", &number_rows);
                            getchar();
                            //printf("1\n");
                            //int rows[number_rows];
                            int *rows = (int*) malloc(number_rows * (sizeof(int)));
                            //printf("1\n");
                            //int coefficients[number_rows];
                            int *coefficients = (int*) malloc(number_rows * (sizeof(int)));
                            //printf("1\n");

                            printf("add rows: ");
                            //getchar(); getchar();
                            for (int i = 0; i < number_rows; i++) {
                                scanf("%d", &rows[i]);
                            }
                            printf("enter coefficients ");
                            for (int i = 0; i < number_rows; i++) {
                                scanf("%d", &coefficients[i]);
                            }
                            Try {
                                linearCombinationRow(&ANS, number_rows, change_row, rows, coefficients);
                                printIntMatrix(&ANS);
                            } Catch(EXCEPTION) {
                                handlerError(EXCEPTION);
                            }
                        }
                            break;
                    }
                } while (menu_int);
            }
                break;
            case 2: {
                int menu_int;
                do {
                    menu_int = dialog(MENU_INT, MENU_INT_SIZE);
                    switch (menu_int) {
                        Matrix x1, x2;
                        case 0:
                            break;
                        case 1: {
                            int c;
                            printf("use examples?\n0.no\n1.yes\n");
                            scanf("%d", &c);
                            getchar();
                            if (c) {
                                x1 = C;
                                printRealMatrix(&x1);
                                x2 = C1;
                                printRealMatrix(&x2);
                            } else {
                                Try{
                                    x1 = enterRealMatrix();
                                    x2 = enterRealMatrix();
                                } Catch(EXCEPTION) {
                                    handlerError(EXCEPTION);
                                }
                            }
                        }
                            break;
                        case 2: {
                            int c;
                            printf("use examples?\n0.no\n1.yes\n");
                            scanf("%d", &c);
                            getchar();
                            if (c) {
                                x1 = C;
                                printRealMatrix(&x1);
                                x2 = transpose(&C);
                                printRealMatrix(&x2);
                            }
                            Try {
                                Matrix ANS = sumMatrix(&x1, &x2);
                                printRealMatrix(&ANS);
                            } Catch(EXCEPTION) {
                                handlerError(EXCEPTION);
                            }
                        }
                            break;
                        case 3: {
                            Try {
                                Matrix ANS = multiMatrix(&x1, &x2);
                                printRealMatrix(&ANS);
                            } Catch(EXCEPTION) {
                                handlerError(EXCEPTION);
                            }
                        }
                            break;
                        case 4: {
                            Try {
                                Matrix ANS = transpose(&x1);
                                printRealMatrix(&ANS);
                                ANS = transpose(&x2);
                                printRealMatrix(&ANS);
                            } Catch(EXCEPTION) {
                                handlerError(EXCEPTION);
                            }
                        }
                            break;
                        case 5: {
                            int c;
                            printf("what matrix use?\n0. 1\n1. 2\n");
                            scanf("%d", &c);
                            getchar();
                            Matrix ANS;
                            if (c) {
                                ANS = x2;
                            } else {
                                ANS = x1;
                            }
                            int change_row, number_rows;
                            printf("change row number: ");
                            scanf("%d", &change_row);
                            getchar();
                            printf("how mary rows do you add? ");
                            scanf("%d", &number_rows);
                            getchar();
                            //printf("1\n");
                            //int rows[number_rows];
                            int *rows = (int*) malloc(number_rows * (sizeof(int)));
                            //printf("1\n");
                            //int coefficients[number_rows];
                            float *coefficients = (float*) malloc(number_rows * (sizeof(float)));
                            //printf("1\n");

                            printf("add rows: ");
                            //getchar(); getchar();
                            for (int i = 0; i < number_rows; i++) {
                                scanf("%d", &rows[i]);
                            }
                            printf("enter coefficients ");
                            for (int i = 0; i < number_rows; i++) {
                                scanf("%f", &coefficients[i]);
                            }
                            Try {
                                        linearCombinationRow(&ANS, number_rows, change_row, rows, coefficients);
                                        printRealMatrix(&ANS);
                                    } Catch(EXCEPTION) {
                                handlerError(EXCEPTION);
                            }
                        }
                            break;
                    }
                } while (menu_int);

            }
        }
    } while (menu);
    return 0;
}

void handlerError (CEXCEPTION_T EXPT)
{
    switch (EXPT) {
        case NULL_POINTER:
            printf("points to a null pointer!");
            break;

        case WRONG_ELEMENT_SIZE:
            printf("Element length less than or equal to 0!");
            break;

        case WRONG_DIMENSION:
            printf("Array length is less than or equal to 0!");
            break;

        case NO_SUMMAT:
            printf("No sum function!");
            break;

        case NO_MULTI:
            printf("No multi function!");
            break;

        case DIFFERENT_ELEMENT_SIZE:
            printf("Different element length!");
            break;

        case DIFF_SUM:
            printf("Different sum functions!");
            break;

        case DIFF_MULTI:
            printf("Different multi functions!");
            break;

        case OVERFLOW_EL:
            printf("Variable overflow has occurred!");
            break;

        case WRONG_SHAPE:
            printf("Impossible to use matrices of different shape");
            break;

        default:
            printf("Unknown error %d", EXPT);
            break;
    }
    printf("\n");
}