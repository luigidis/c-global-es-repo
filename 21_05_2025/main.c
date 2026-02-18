#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct p
{
    int a;
    int b;
    double alpha;
    double beta;
} Parameters;

void error(char *);
Parameters readInput(int, char *[]);
double ***allocMatrix(int, int);
unsigned int get_random();
double genDouble();
void fillMatrix(double*** , int , int , double , double);
void printMatrix(double***, int , int );
double normalizedDouble(double , double );
double*** transposeMatrix(double*** , int , int );

int main(int argc, char *argv[])
{
    printf("\n=========A=========");
    Parameters p = readInput(argc, argv);

    printf("\n=========B=========");
    double*** matrixM = allocMatrix(p.a, p.b);

    printf("\n=========C=========");
    fillMatrix(matrixM, p.a, p.b, p.alpha, p.beta);

    printf("\n=========D=========");
    double*** matrixT = transposeMatrix(matrixM, p.a, p.b);
    printf("\n=========E=========");
    printMatrix(matrixM, p.a, p.b);
    printMatrix(matrixT, p.b, p.a);

}

void error(char *e)
{
    fprintf(stderr, "[ERROR]: %s", e);
    exit(EXIT_FAILURE);
}

Parameters readInput(int argc, char *argv[])
{
    if (argc != 5)
        error("Number of parameters wrong");

    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    double alpha = atof(argv[3]);
    double beta = atof(argv[4]);

    // a e b devono essere compresi tra 5 e 20
    if (a < 5 || a > 20)
        error("Parameter a is not in the correct range [5,20]");

    if (b < 5 || b > 20)
        error("Parameter b is not in the correct range [5,20]");

    // alpha deve essere compreso in 10 20
    if (alpha < 10 || alpha > 20)
        error("Parameter alfa is not in the correct range[10,20]");

    // beta deve essere compreso in 1 5
    if (beta < 1 || beta > 5)
        error("Parameter alfa is not in the correct range[1,5]");

    Parameters p = {a, b, alpha, beta};

    return p;
}

double ***allocMatrix(int a, int b)
{
    // Righe
    double ***matrixToAlloc = (double ***)malloc(sizeof(double **) * a);
    if (!matrixToAlloc)
        error("Error during matrix row allocation allocation");

    // Colonne
    for (int i = 0; i < a; i++)
    {
        matrixToAlloc[i] = (double **)malloc(sizeof(double*) * b);
        if (!matrixToAlloc[i])
            error("Error during matrix colomn allocation allocation");
    }

    return matrixToAlloc;
}

void fillMatrix(double ***matrix, int a, int b, double alpha, double beta)
{
    //Estraggo un numero pseudo casuale p in virgola mobile con genDouble()
    double p = genDouble();

    //Se p > 0,2 si popoli l'elemento della matrice con un numero dobule pseudo casuale
    //appartenente all'intervallo di normalizedDouble()

    //tra le righe
    for (int i = 0; i < a; i++)
    {
        //tra le colonne
        for (int j = 0; j < b; j++)
        {
            if(p > 0,2)
            {
                double* ptr = (double*)malloc(sizeof(double));

                *ptr = normalizedDouble(alpha, beta);

                matrix[i][j] = ptr;
            }
            else
            {
                matrix[i][j] = NULL;
            }
        }
    }
}

unsigned int get_random()
{
    static unsigned int m_w = 123456;
    static unsigned int m_z = 789123;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}

double genDouble()
{
    //Mi vado a prendere un valore intero casuale
    unsigned int random_val = get_random();

    //Lo normalizzo in 0,1 rendendolo double
    double normalized_val = (double)random_val / (double)UINT_MAX;

    return normalized_val;
}

double normalizedDouble(double alpha, double beta)
{
    //Il range da rispettare deve essere [alpha - beta, alpha + beta]
    double d_1 = alpha - beta;
    double d_2 = alpha + beta;
    
    //Mi vado a prendere un valore double casuale in [0,1]
    double normalized_double = genDouble();

    //Porto il numero normalizzato nell'intervallo [d_1,beta] porco dio
    return normalized_double + d_1 * (d_1 - d_2);
}


double*** transposeMatrix(double*** m, int a, int b)
{
    double*** m_t = allocMatrix(b, a);

    for (int i = 0; i < b; i++)
    {
        for (int j = 0; j < a; j++)
        {
            if (m[j][i] != NULL)
            {
                double* ptr = (double*)malloc(sizeof(double));

                *ptr = *m[j][i];
                
                m_t[i][j] = ptr;
                
            }
            else
            {
                m_t[i][j] = NULL;
            }
        }
    }

    return m_t;
}

void printMatrix(double*** matrix, int a, int b)
{
    printf("\n*** Matrice (%d x %d)\n", a, b);

    for (int i = 0; i < a; i++)
    {

        for (int j = 0; j < b; j++)
        {
            if (matrix[i][j] != NULL)
            {
                printf("%f\t", *matrix[i][j]);
            }
            else
            {
                printf("N");
            }
        }
        printf("\n");
    }
}