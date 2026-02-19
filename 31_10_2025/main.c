#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct p
{
    char *inputFilename;
    int n;
    int m;
} Parameters;

Parameters readInput(int, char *[]);
void error(char *);
double ***allocateMatrix(int, int);
void fillMatrix(char *, double ***, int, int);
void printMatrix(double ***, int, int);
void normalize(double ***, double ***, int, int);
void sortMatrixCols(double ***, int, int);
void swap(double first, double second);

int main(int argc, char *argv[])
{
    printf("\n==========A===========");
    Parameters p = readInput(argc, argv);

    printf("\n===========B===========");
    double ***matrixA = allocateMatrix(p.n, p.m);
    fillMatrix(p.inputFilename, matrixA, p.n, p.m);

    printf("\n===========C===========");
    double ***matrixB = allocateMatrix(p.n, p.m);
    fillMatrix(p.inputFilename, matrixB, p.n, p.m);

    printf("\n===========D===========");
    printMatrix(matrixA, p.n, p.m);
    printMatrix(matrixB, p.n, p.m);

    printf("\n===========E===========");
    sortMatrixCols(matrixB, p.n, p.m);
    printMatrix(matrixB, p.n, p.m);
}

void swap(double first, double second)
{
    double tmp = first;
    first = second;
    second = tmp;
}

void sortMatrixCols(double ***matrix, int row, int col)
{
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row - 1; j++)
        {
            for (int k = 0; k < row - 1 - j; k++)
            {
                if (*matrix[k + 1][i] < *matrix[k][i])
                {
                    double *tmp = matrix[k][i];
                    matrix[k][i] = matrix[k + 1][i];
                    matrix[k + 1][i] = tmp;
                }
            }
        }
    }
}

void normalize(double ***matrixA, double ***matrixB, int row, int col)
{
    // Itero su tutte e due le matrici contemporaneamente
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            matrixB[i][j] = matrixA[i][j];
        }
    }
}

void printMatrix(double ***matrix, int row, int col)
{

    for (int i = 0; i < row; i++)
    {
        printf("\n");
        for (int j = 0; j < col; j++)
        {
            printf("| %lf |", *matrix[i][j]);
        }
    }

    printf("\nMatrix printed!");
}

void fillMatrix(char *inputFilename, double ***matrix, int row, int col)
{
    FILE *f = fopen(inputFilename, "r");
    if (!f)
        error("error opening the file");

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            double *ptr = (double *)malloc(sizeof(double));

            fscanf(f, "%lf", ptr);

            matrix[i][j] = ptr;
        }
    }
    fclose(f);
}

double ***allocateMatrix(int n, int m)
{
    printf("\nStart Matrix allocation %dx%d", n, m);

    double ***matrix = (double ***)malloc(sizeof(double **) * n);
    if (!matrix)
        error("Allocation failed");

    for (int i = 0; i < n; i++)
    {
        matrix[i] = (double **)malloc(sizeof(double *) * m);

        if (!matrix[i])
            error("Allocation failed");
    }

    printf("\nMatrix allocated %dx%d", n, m);

    return matrix;
}

void error(char *e)
{
    fprintf(stderr, "\n[ERROR]: %s", e);
    exit(EXIT_FAILURE);
}

Parameters readInput(int argc, char *argv[])
{
    if (argc != 4)
        error("Number of parameters wrong");

    char *inputFilename = argv[1];
    int n = atoi(argv[2]);
    int m = atoi(argv[3]);

    if (!inputFilename || strcmp(inputFilename + strlen(inputFilename) - 4, ".txt") != 0)
        error("Input File name not correct extension");

    if (n < 5 || n > 10)
        error("n integer is not in the correct range");

    if (m < 5 || m > 10)
        error("n integer is not in the correct range");

    Parameters p = {inputFilename, n, m};

    return p;
}
