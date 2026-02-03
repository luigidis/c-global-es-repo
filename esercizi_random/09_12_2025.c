#include <stdio.h>
#include <stdlib.h>

#define N 3
#define M 4
#define FILENAME output

void printMatrix(double matrix[][M]);
int printFile(double matrix[][M]);
int readAndAllocFromFile(double matrix[][M]);
int trasposedMatrix(double matrix[][M], double matrix_t[][N]);
void printTMatrix(double matrix_t[][N]);

int main (int argc, char *argv[]) 
{
	
	double matrix[N][M];
	
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
				matrix[i][j] = (i + 3.6) * (j + 4.8) * M / 2.5;
		}
	}
	printMatrix(matrix);
	
	int r = printFile(matrix);
	
	if (r == 0)
		printf("Succes\n");
	
	double matrix_n[N][M];
	
	printf("Nuova Matrice Allocata\n");
	int z = readAndAllocFromFile(matrix_n);
	
	if (z = 0)
	{
		printf("Nuova Matrice Creata\n");
		printMatrix(matrix_n);		
	}
	
	double matrix_t[M][N];
	
	int y = trasposedMatrix(matrix, matrix_t);
	printTMatrix(matrix_t);
	
	return 0;
}

void printMatrix(double matrix[][M])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
				printf("matrix[%d][%d] = %.2lf\t",i,j,matrix[i][j]);
		}
		printf("\n");
	}
	
	printf("Matrix printed\n");
	
}

void printTMatrix(double matrix_t[][N])
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
				printf("matrix[%d][%d] = %.2lf\t",i,j,matrix_t[i][j]);
		}
		printf("\n");
	}
	
	printf("Matrix Trasposed printed\n");
	
}

int printFile(double matrix[][M])
{
	FILE *file;
	
	//Apre il file e se non esiste lo crea
	file  = fopen("output.txt", "w");
	
	if (file == NULL)
	{
		printf("File non aperto correttamente\n");
		return -1;
	}
	
	
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
				fprintf(file, "%.2lf ", matrix[i][j]);
		}
		fprintf(file, "\n");
	}
	
	fclose(file);
	
	printf("Matrice scritta su  correttamente\n");
	return 0;
}

int readAndAllocFromFile(double matrix[][M])
{
	FILE *f;
	
	f = fopen("output.txt", "r");
	
	if(f == NULL)
	{
		printf("File non aperto correttamente\n");
		return -1;
	}
	
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (fscanf(f, "%lf", &matrix[i][j]) != 1)
			{
				printf("Errore nella lettura alla  posizione [%d][%d]\n", i, j);
				fclose(f);
				return -1;
			};
		}
	}
	
	
	fclose(f);
	
	return 0;
}

int trasposedMatrix(double matrix[][M], double matrix_t[][N])
{
	if (matrix && matrix_t == NULL)
		perror("[ERROR]: Error matrix not allocated");
	
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			matrix_t[j][i] = matrix[i][j];
		}
	}
		
}
