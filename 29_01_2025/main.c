#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 200

typedef struct p
{
    char *inputFilename;
    char *outputFilename;
    unsigned int n;
    unsigned int m;
} Parameters;

Parameters readInput(int, char *[]);
double ***allocMatrix(int, int);
double ***readMatrix(char *, int, int);
void printMatrix(double ***, int, int);
double ***transposeMatrix(double ***, int, int);
void sortColMatrix(double ***, int, int);
void writeMatrix(char* , double*** , int , int );

int main(int argc, char *argv[])
{
    printf("\n==========A==========");

    Parameters p = readInput(argc, argv);
    printf("\nParameters found: {inputFilename = %s, outputFilename = %s, n = %d, m = %d}", p.inputFilename, p.outputFilename, p.n, p.m);

    printf("\n==========B==========");
    double ***matrix = readMatrix(p.inputFilename, p.n, p.m);
    printf("\n==========C==========");
    double ***matrixT = transposeMatrix(matrix, p.n, p.m);

    printf("\n==========D==========");
    sortColMatrix(matrixT, p.m, p.n);
    printMatrix(matrixT, p.m, p.n);

    printf("\n==========E==========");

    writeMatrix(p.outputFilename,matrixT, p.m, p.n);
    printf("\nMatrice stampata");

}

void error(char *e)
{
    fprintf(stderr, "[ERROR]: %s", e);
    exit(EXIT_FAILURE);
}

Parameters readInput(int argc, char *argv[])
{
    if (argc != 5)
        error("Number of parameters wrong!");

    char *inputFilename = argv[1];
    char *outputFilename = argv[2];
    int n = atoi(argv[3]);
    int m = atoi(argv[4]);

    if (!inputFilename || strcmp(inputFilename + strlen(inputFilename) - 4, ".txt") != 0)
        error("Input file name not valid!");

    if (!outputFilename || strcmp(outputFilename + strlen(outputFilename) - 4, ".txt") != 0)
        error("Output file name not valid!");

    if (n < 0 || m < 0)
        error("n or m integer must be positive!");

    Parameters p = {inputFilename, outputFilename, n, m};

    return p;
}

double ***allocMatrix(int n, int m)
{
    double ***matrix = (double ***)malloc(sizeof(double **) * n);
    if (!matrix)
        error("Error during allocation!");

    for (int i = 0; i < n; i++)
    {
        matrix[i] = (double **)malloc(sizeof(double *) * m);
        if (!matrix[i])
            error("Error during allocation!");
    }

    printf("\nMatrice allocata %dx%d", n, m);

    return matrix;
}

double ***readMatrix(char *inputFilename, int n, int m)
{
    // Alloco la matrice
    double ***matrix = allocMatrix(n, m);

    // Sezione di lettura file
    FILE *f = fopen(inputFilename, "r");
    if (!f)
        error("error opening input file");

    for (int i = 0; i < n; i++)
    {

        for (int j = 0; j < m; j++)
        {
            double *ptr = (double *)malloc(sizeof(double));

            fscanf(f, "%lf", ptr);

            matrix[i][j] = ptr;
        }
    }

    fclose(f);

    // Alla fine dobbiamo stampare la matrice letta dal file
    printMatrix(matrix, n, m);
    printf("\nMatrice letta");
    return matrix;
}

void printMatrix(double ***matrix, int n, int m)
{
    printf("\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("| %f |", *matrix[i][j]);
        }
        printf("\n");
    }

    printf("\nMatrice stampata");
}

double ***transposeMatrix(double ***matrix, int n, int m)
{
    // Alloco matrice trasposta
    double ***matrixT = allocMatrix(m, n);

    // Riempio la matrice trasposta allocata
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            double *ptr = (double *)malloc(sizeof(double));

            *ptr = *matrix[j][i];

            matrixT[i][j] = ptr;
        }
    }

    // Stampo sul stdout
    printMatrix(matrixT, m, n);
    return matrixT;
}

void sortColMatrix(double ***matrix, int row, int col)
{
    
    for (int j = 0; j < col; j++)
    {
        for (int i = 0; i < row; i++)
        {   
            int position_to_insert = i;
            double *item_ptr = matrix[i][j];
            double item_to_insert = *matrix[i][j];

            //Dobbiamo fare l'insertion sort
            while(position_to_insert > 0 && *matrix[position_to_insert - 1][j] > item_to_insert)
            {
                matrix[position_to_insert][j] = matrix[position_to_insert - 1][j];
                position_to_insert--;
            }

            matrix[position_to_insert][j] = item_ptr;
            printf("Elemento inserito");
        }
    }

    printf("\nMatrice riordinata");
}

void writeMatrix(char* outputFilename, double*** matrix, int row, int col)
{
    FILE *f = fopen(outputFilename, "w");
    if (!f)
        error("Error opening file");

    // Riempio la matrice trasposta allocata
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            fprintf(f, "%lf ", *matrix[i][j]);
        }

        fputs("\n", f);
    }


    fclose(f);
}