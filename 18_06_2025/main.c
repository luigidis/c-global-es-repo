#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_SIZE 20
#define MAX_ARRAY_SIZE 200

typedef struct p
{
	char* inputFilename;
	char* outputFilename;
} Parameters;

typedef struct r {
	char key[MAX_STRING_SIZE];
	int length;
} Record;

void error(char* e);
Parameters readInput(int , char* []);
void buildArray(char*, Record []);
void printTotalArray(Record []);
void filter(Record []);
int is_my_punct(char c);
void createSet(Record []);
void printArray(Record []);
void save(char*, Record []);
void read(char*);
void printArrayFormBin(Record [], size_t);

int main(int argc, char* argv[])
{
	printf("======================A======================");
	Parameters p = readInput(argc, argv);
	
	printf("\n======================B======================");
	Record records[MAX_ARRAY_SIZE];
	buildArray(p.inputFilename, records);
	printf("\nArray builded!");
	printTotalArray(records);
	
	printf("\n======================C======================");
	filter(records);
	printTotalArray(records);
	
	printf("\n======================D======================");
	createSet(records);
	printTotalArray(records);
	
	printf("\n======================E======================");
	printArray(records);
	
	printf("\n======================F======================");
	save(p.outputFilename, records);
	
	printf("\n======================D======================");
	read(p.outputFilename);
	
	
}

void error(char* e)
{
	fprintf(stderr, "\n[ERROR]\n: %s", e);
	exit(EXIT_FAILURE);
}

Parameters readInput(int argc, char* argv[])
{
	if (argc != 3)
		error("Number of Parameters wrong!");
	
	if (!argv[1] || strlen(argv[1]) < 5 || strcmp(argv[1] + strlen(argv[1]) - 4, ".txt"))
		error("Extension for first file not correct");
	if (!argv[2] || strlen(argv[2]) < 5 || strcmp(argv[2] + strlen(argv[2]) - 4, ".bin"))
		error("Extension for second file not correct");
	
	char* inputFilename = (char*)malloc(sizeof(char)*(strlen(argv[1]) + 1));
	if (!inputFilename)
		error("Allocation for inputFilename wrong");
	
	strcpy(inputFilename, argv[1]);
	
	char* outputFilename = (char*)malloc(sizeof(char)*(strlen(argv[2]) + 1));
	if (!outputFilename)
		error("Allocation for outputFilename wrong");
	
	strcpy(outputFilename, argv[2]);
	
	Parameters p = {inputFilename, outputFilename};
	return p;
}

void buildArray(char* inputFilename,Record arrayToBuild[MAX_ARRAY_SIZE])
{
	FILE *f = fopen(inputFilename, "r");
	if (!f)
		error("Error opening file!");
	
	char string[MAX_STRING_SIZE];
	
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		if (fscanf(f, "%s", string) != EOF)
		{
			strcpy(arrayToBuild[i].key, string);
			arrayToBuild[i].length = strlen(string);
		} else
		{
			arrayToBuild[i].key[0] = '\0';
			arrayToBuild[i].length = -1;
		}
	}
	
	fclose(f);
}

void printTotalArray(Record array[MAX_ARRAY_SIZE])
{
	printf("\n================");
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		printf("\n%s %d\t", array[i].key, array[i].length);
	}
	printf("\n================");
	
	return;
}

void printArray(Record array[MAX_ARRAY_SIZE])
{
	printf("\n================");
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		if(array[i].length == -1) continue;
		
		printf("\n%s %d\t", array[i].key, array[i].length);
	}
	printf("\n================");
	
	return;
}
//Funzione che elimina tutti i caratteri di punteggiatura da ogni key dell'array
void filter(Record array[MAX_ARRAY_SIZE])
{
	int k = 0;
	int j = 0;
	
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		k = 0;
		j = 0;
		
		//Scorri tutta la stringa
		while(array[i].key[k] != '\0')
		{	//Se trovi punteggiatura
			if (!is_my_punct(array[i].key[k]))
			{
				array[i].key[j] = array[i].key[k];
				j++;
			} 
			else if (is_my_punct(array[i].key[k]))
			{
				printf("\nPunteggiatura rimossa nell chiave %d", i);
				array[i].length -= 1;
			}
			
			k++;
		}
		array[i].key[j] = '\0';
		
	}
}

int is_my_punct(char c)
{
	return (c == ';' || c == ',' || c == ':' || c == '.');
}

void createSet(Record array[MAX_ARRAY_SIZE])
{	
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		
		if (array[i].length == -1) continue;
		
		for (int j = i + 1; j < MAX_ARRAY_SIZE; j++)
		{	
			if (array[j].length == -1) continue;
			
			if (array[i].length == array[j].length)
			{
				//strcmp restituisce 0 se le stringhe sono identiche
				if (strcmp(array[i].key,array[j].key) == 0)
				{
					array[j].length = -1;
					printf("\nDuplicato trovato e rimosso alla posizione %d", j);
				}
			}
		}
	}
}

void save(char* outputFilename, Record array[MAX_ARRAY_SIZE])
{
	FILE* f = fopen(outputFilename, "wb");
	if (f == NULL)
	{
		printf("Errore nell'apertura del file!\n");
		return;
	}
	
	size_t w = 0;
	
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		if (array[i].length == -1) continue;
		
		size_t result = fwrite(&array[i], sizeof(Record), 1, f);
		w += result;
	}
	
	printf("\nSalvataggio completato: scritti %zu record validi.\n", w);
	fclose(f);
}

void read(char* outputFilename)
{
	Record records[MAX_ARRAY_SIZE];
	
	FILE* f= fopen(outputFilename, "rb");
		if (f == NULL)
	{
		printf("Errore nell'apertura del file!\n");
		return;
	}
	
	const size_t result = fread(records, sizeof records[0], MAX_ARRAY_SIZE, f);
	
	if (result > 0)
	{
		printArrayFormBin(records, result);
	}
	
	fclose(f);
	
}

void printArrayFormBin(Record array[], size_t length)
{
	printf("\n================");
	for (size_t i = 0; i < length; i++)
	{
		printf("\n%s %d\t", array[i].key, array[i].length);
	}
	printf("\n================");
	
	return;
	
}