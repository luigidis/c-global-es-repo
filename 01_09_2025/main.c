#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_SIZE 31
#define MAX_ARRAY_SIZE 20

typedef struct p {
	char *inputFilename;
	char *outputFilename;	
} Parameters;

typedef struct r {
	char id[MAX_STRING_SIZE];
	char name[MAX_STRING_SIZE];
	char surname[MAX_STRING_SIZE];
	int age;
} Record;

Parameters readInput(int, char *[]);
int buildArray(char *,Record [MAX_ARRAY_SIZE]);
int printRecord(Record [MAX_ARRAY_SIZE], int);
int sortArray(Record [MAX_ARRAY_SIZE], int);
int elab(Record [MAX_ARRAY_SIZE], int, char* );

void error (char* e);

int main(int argc, char *argv[])
{
	printf("Numero di parametri: %d", argc);
	for (int i = 0; i < argc; i++)
	{
		printf("\nPararmetro numero %d: %s", i, argv[i]);
	}
	
	printf("\n================A================");
	Parameters p = readInput(argc, argv);
	printf("\n %s, %s", p.inputFilename, p.outputFilename);
	
	printf("\n================B================");
	Record arrayToBuild[MAX_ARRAY_SIZE] = {0};
	int totalElements = buildArray(p.inputFilename, arrayToBuild);
	printf("\nNumero di elementi inseriti nell'Array: %d", totalElements);
	
	printf("\n================C================");
	int j = printRecord(arrayToBuild, totalElements);
	if ( j == 1 ) printf("\nArray stampato correttamente!");
	
	printf("\n================D================");
	int r = sortArray(arrayToBuild, totalElements);
	if (r == 1) printf("\nArray sortato correttamente!");
	
	printf("\n================E================");
	int z = printRecord(arrayToBuild, totalElements);
	if ( z == 1 ) printf("\nArray stampato correttamente!");
	
	printf("\n================F================");
	int f = elab(arrayToBuild, totalElements, p.outputFilename);
	if (f == 1) printf("\nFile %s creato correttamente", p.outputFilename);
	
	
}

void error(char *e)
{
	if (!e) return;
	
	fprintf(stderr, "\n[ERROR]: %s\n", e);
	exit(EXIT_FAILURE);		
}

Parameters readInput(int argc, char *argv[])
{
	if(argc != 3)
	{
		error("Number of Parameters wrong");
	}
	
	char *inputFilename = argv[1];
	char *outputFilename = argv[2];
	
	if (!inputFilename || strcmp(inputFilename + strlen(inputFilename) - 4, ".bin"))
	{
		error("inputFilename is not a correct file extension");
	}

	if (!outputFilename || strcmp(outputFilename + strlen(outputFilename) - 4, ".txt"))
	{
		error("outputFilename is not a correct file text");
	}
	
	Parameters p ={inputFilename, outputFilename};
	
	return p;
		
}

int buildArray(char *inputFilename, Record array[MAX_ARRAY_SIZE]) 
{
	FILE *file = fopen(inputFilename, "rb");
	if (!file) 
	{
		fclose(file);
		error("Errore di apertura file");
	}
	
	Record r;
	int index = 0;
	
	while (fread(&r, sizeof(Record), 1, file) == 1)
	{
		//Elaboriamo il record
		printf("\nID: %s, Nome: %s, Cognome; %s, age: %d", r.id, r.name, r.surname, r.age);
		array[index] = r;
		index += 1;
	}
	
	fclose(file);
	printf("\nArray buildato correttamente, file %s chiuso", inputFilename);
	
	return index;
	
}

int printRecord(Record array[MAX_ARRAY_SIZE], int totalElements)
{
	int  i = 0;
	while (i < totalElements)
	{
		printf("\nID: %s, Nome: %s, Cognome; %s, age: %d", array[i].id, array[i].name, array[i].surname, array[i].age);
		i++;
	}
	
	return 1;
}
//Ordina l'array di record in ordine lessiografico crescente rispetto al cognome mediante l'insertion sort
int sortArray(Record array[MAX_ARRAY_SIZE], int totalElements)
{
	for (int i = 1; i < totalElements; i++)
	{
		Record key = array[i];
		int j = i - 1;
		
		while (j >= 0 && strcmp(array[j].surname, key.surname) > 0)
		{
			array[j + 1] = array[j];
			j--;
		}
		array[j + 1] = key;
	}
	
	return 1;
}

//Scrivere in formato testo tutti i record dell'array che hanno un campo codice che inizia per X o Z, un record per riga in questo modo:
// codice nome cognome eta
int elab(Record array[MAX_ARRAY_SIZE], int totalElements, char *outputFilename)
{
	FILE *f = fopen(outputFilename, "w");
	
	if (!f)
	{
		error("Error opening file!");
	}
	
	for (int i = 0; i < totalElements; i++)
	{
		if (array[i].id[0] == 'X' || array[i].id[0] == 'Z')
		{
			fprintf(f, "%s %s %s %d\n", array[i].id, array[i].name, array[i].surname, array[i].age);
		}
	}
	

	fclose(f);
	
	return 1;
}



