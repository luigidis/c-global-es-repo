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

int main(int argc, char* argv[])
{
	printf("======================A======================");
	Parameters p = readInput(argc, argv);
	
	printf("\n======================B======================");
	Record records[MAX_ARRAY_SIZE];
	buildArray(p.inputFilename, records);
	printf("Array builded!");
	printTotalArray(records);
	
	printf("\n======================C======================");
	printf("\n======================D======================");
	
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
	printf("================");
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		printf("%s %d\t", array[i].key, array[i].length);
	}
	printf("================");
	
	return;
}