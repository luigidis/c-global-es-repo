#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_MAX_LENGTH 30

typedef struct p
{
	int n;
	int m;
} Parameters;

typedef struct s
{
	char string[STRING_MAX_LENGTH];
	int l;
} S;

Parameters readArgs(int argc, char *argv[]);
void error(char *error);
S** allocMatrix(int a, int b); //Funzione che alloca dinamicamente un array bidimensuionale NxM di stringhe
void freeMatrix(S** matrix, int n, int m);
void readMatrix(S **matrix,int n, int m);
int computeAvg(S** matrix, int n, int m);
void printMatrix(S** matrix, int n, int m);
void buildAvgArray();
void sortColMatrix();

int main(int argc, char *argv[])
{
	printf("Numeri di argomenti passati: %d\n", argc);
	
	for (int i = 0; i < argc; i++) {
		printf("Parametro passato number %d = %s\n", i, argv[i]);
	}
	
	printf("==============1==============\n");
	Parameters p = readArgs(argc,argv);
	
	printf("==============2==============\n");
	S** matrix = allocMatrix(p.n, p.m);
	readMatrix(matrix,  p.n, p.m);
	printMatrix(matrix, p.n, p.m);
	
	printf("==============3==============\n");
	int s = 0;
	int s = computeAvg(matrix, p.n, p.m);
	

}

void error(char *e)
{
	fprintf(stderr, "[ERROR]: %s\n", e);
	exit(EXIT_FAILURE);
}

Parameters readArgs(int argc, char *argv[])
{
	if (argc !=3)
		error("Number of Argument not valid!\n");
	
	//Ricorda argv[0] è il nome del programma!!
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);
	
	Parameters p = {a,b};
	printf("Parameters inserted in the suggested struct");
	return p;
}

S** allocMatrix(int n, int m)
{
	//Alloca tutte le righe
	S** matrix = (S **)malloc(n * sizeof(S *));
	
	if (matrix == NULL) return NULL;
	
	//Alloca tutti i dati in un unico blocco
	S *datas = (S *)malloc(n * m * sizeof(S));
	
	if (datas == NULL) {
		free(matrix);
		return NULL;
	}
	
	//Collega i puntatore delle righe al puno giusto nel blocco dati
	for (int i = 0; i < n; i++)
	{
		matrix[i] = &datas[i * m]; //Punta all'inizio della riga i-esima
	}
	
	return matrix;
}

void freeMatrix(S** matrix, int n, int m)
{
	if (matrix == NULL)
		return;
	
	//Libero il blocco dei dati cioè il contenuto della matrice
	if (matrix[0] != NULL)
	{
		free(matrix[0]);
	}
	
	//Libero l'array dei puntatori
	free(matrix);
}

void readMatrix (S** matrix,int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			scanf("%s", matrix[i][j].string);
			matrix[i][j].l = strlen(matrix[i][j].string);
		}
	}
}

//Prende in input la matrice S e calcoli la media di una singola colonna (parametro della funzione) della matrice; 
int computeAvg(S** matrix, int n, int m) {
	if (matrix != NULL) 
	{
		error("Please insert a matrix!\n");
	};
	
	int s = 0; //Somma parziale
	
	for (int i = 0; i < n; i++)
	{
		s += matrix[i][m].l;
	}
	
	return s /= n;
}

void printMatrix(S** matrix, int n, int m)
{
	printf("==============MATRIX==============\n");
	for (int i = 0; i < n; i++)
	{
		for (int j= 0; j < m; j++)
		{
			printf("%s[%d]\t", matrix[i][j].string, matrix[i][j].l);
		}
		printf("\n");
	}
	printf("==============END==============\n");
}

//Funzione che prenda in input la matrice di strutture S e calcoli la media per ogni colonna di S come specificato al punto 5 (mediante la funzione computeAvg()), restituisca un array di dimensioni M contenenti tali valori medi;
void buildAvgArray()
{
	
}

//Funzione che proceda all'ordinamento della matrice S come specificato al punto 6.
void sortColMatrix()
{
	
}





