//LUIGI DISTEFANO 1000063372

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_STRING_LENGTH 20
#define ARRAY_MAX_DIM 200
#define DEFAULT_EMPTY_RECORD -1

typedef struct p {
	char *fileName;
	int k;
} Parameters;

typedef struct record {
	char key[MAX_STRING_LENGTH];
	int length;
} R;

Parameters readInput(int argc, char *argv[]);
void error(char *e); 
void success(char *s);
R *allocArray(int max);
void buildArray();
void filter();
void ceateSet();
void printArray();

int main(int argc, char *argv[])
{	
	printf("==============A==============\n");
	Parameters p = readInput(argc, argv);
	
	printf("==============B==============\n");
	R *r = allocArray(MAX_STRING_LENGTH);
	printf("==============C==============\n");
	
}

void error(char *e)
{
	fprintf(stderr, "[Error]: %s\n", e);
	exit(EXIT_FAILURE);
}

void success(char *s)
{
	printf("[Success]: %s", s);
	
	return;
}

Parameters readInput(int argc, char *argv[])
{
	if (argc != 3)
		error("Number of parameters wrong");
	
	
	//L'indice 1 sarà dedicato al nome del file
	char* fileName = argv[1];
	//L'indice 2 sarà dedicato al parametro K
	int k = atoi(argv[2]);
	if (k < 5 || k > 10)
		error("Insert a number between 5 and 10");
	
	Parameters p = {fileName, k};
	success("Parameters inserted in the suggested structure");
	return p;
}

R *allocArray(int max){
	if (!max)
		error("Please give a correct int to allocArray function");
	
	R *r = (R *)malloc(max * sizeof(R));
	
	for (int i = 0; i < max; i++)
	{
		r[i].length = -1;
	}
	
	success("Array allocato dinamicamente in modo corretto");
	return r;
}

void printArray(R *r, int max)
{
	for (int i = 0; i < max; i++)
	{
		printf("RECORD N°1 [KEY]=%s\t[LENGTH]=%d\n", r[i].key, r[i].length);
	}
	
	success("ARRAY PRINTED");
}
