#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_BUFFER_SIZE 100

typedef struct p {
	int n;
	int m;
} Parameters;

void error(char*);
char* readInput(int, char* []);
Parameters readFileToSetParameters(char*);
double** allocateMatrix(int , int);
void fillMatrix(char* ,double** ,int ,int);
void printMatrix(double**,int ,int );
int normalize(double**, double**, int, int);
double getMax(double**, int,int);
void sortMatrixCols(double**, int , int );

int main(int argc, char* argv[])
{
	printf("\nA.");
	
	char* inputFilename = readInput(argc, argv);
	printf("%s", inputFilename);
	
	Parameters p;
	p = readFileToSetParameters(inputFilename);
	printf("\nn=%d m=%d", p.n, p.m);
	
	printf("\nB.");
	// double matrix[p.n][p.m];
	double** v = allocateMatrix(p.n, p.m);
	printf("\nMatrice V allocata");
	fillMatrix(inputFilename, v, p.n, p.m);
	printf("\nMatrix V filled");
	
	printf("\nC.");
	//Alloco la matrice W
	double** w = allocateMatrix(p.n, p.m);
	//Riempio la matrice W come descritto
	int i = normalize(v,w, p.n, p.m);
	if (i == 1)
		printf("\nMatrice normalizzata corretamente");
	
	
	printf("\nD.");
	printMatrix(v, p.n, p.m);
	printf("\nMatrix printed");
	
	printMatrix(w, p.n, p.m);
	
	printf("\nMatrix printed");
	
	printf("\nE.");
	
	sortMatrixCols(w, p.n, p.m);	
	printf("\nMatrix sorted");
	
	printMatrix(w, p.n, p.m);
	
	printf("\nMatrix printed");
}

void error(char* e)
{
	fprintf(stderr, "\n[ERROR]: %s", e);
	exit(EXIT_FAILURE);
}

char* readInput(int argc, char* argv[])
{
	if (argc != 2)
		error("Number of prameters wrong!");
	
	// char *inputFilename = argv[1];
	
	if (!argv[1] || strlen(argv[1]) < 5 || strcmp(argv[1] + strlen(argv[1]) - 4, ".txt"))
		error("Error in inputFilename ext o name");
	
	// char *inputFilename = malloc(sizeof(char)*strlen(argv[1] + 1));
	// if (!inputFilename)
		// error("Memory allocation failed");
	
	// strcpy(inputFilename, argv[1]);
	
	return argv[1];
}

Parameters readFileToSetParameters(char* inputFilename)
{
	FILE* f = fopen(inputFilename, "r");
	
	if(!f)
	{
		error("Errore opening file");		
	}
	
	int n = 0;
	int m = 0;
	
	char buffer[MAX_BUFFER_SIZE];
	
	if (fgets(buffer, MAX_BUFFER_SIZE, f) != NULL)
	{
		sscanf(buffer, "%d %d", &n, &m);
	}
	
	fclose(f);

	Parameters p = {n, m};
	return  p;
}


double** allocateMatrix(int n, int m)
{
	double **matrix = (double**)malloc(sizeof(double*)*n);
	
	if (!matrix)
		error("Matrix not allocated correctly");
	
	for (int i=0; i < n; i++)
	{
		matrix[i] = (double*)malloc(sizeof(double)*m);
		if (!matrix[i])
			//Devo liberare la memoria se avviene un errore
			error("Matrix not alocated correctly");
	}
	
	
	return matrix;
}

void fillMatrix(char *inputFilename, double** matrix, int n, int m)
{
	FILE* f = fopen(inputFilename, "r");
	
	if(!f)
		error("Errore opening file");
	
	char buffer[MAX_BUFFER_SIZE];
	
	fgets(buffer, MAX_BUFFER_SIZE, f); //predo la prima riga e la scarto	
	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			fscanf(f, "%lf", &matrix[i][j]);
		}
	}
	
	fclose(f);
	
	return;
}

void printMatrix(double** matrix, int n, int m)
{
	if (!matrix)
		error("Matrix not exist");
	
	for (int i= 0; i < n; i++)
	{
		printf("\n"); 
		for (int j= 0; j < m; j++)
		{
			printf("[%lf]", matrix[i][j]);
		}
	}
	
	return;
}

int normalize(double** matrixSource, double** matrixToFill, int n, int m)
{
	for (int i = 0; i < m; i++)
	{
		double z = getMax(matrixSource, i, n);
		
		for (int j = 0; j < n; j++)
		{
			matrixToFill[j][i] = matrixSource[j][i] / z;
		}
	}
	
	return 1;
}

//Prendere il massimo da una colonna dato l'index della riga in una matrice doppia
double getMax(double** matrix, int col, int n)
{
	double max = matrix[0][col];
	for (int k = 1; k < n; k++)
	{
		if (matrix[k][col] > max)
		{
			max = matrix[k][col];
		}
	}
	
	return max;
}

void sortMatrixCols(double** matrixToSort, int n, int m)
{
	
	for (int col = 0; col < m; col++)
	{
		//insertion sort sulla colonna col
		for (int i = 1; i < n; i++)
		{
			double key = matrixToSort[i][col];
			int j = i - 1;
			
			while (j >= 0 &&  matrixToSort[j][col] < key)
			{
				matrixToSort[j + 1][col] = matrixToSort[j][col];
				j--;
			}
			matrixToSort[j + 1][col] = key;
		}
		
	}
}