#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define S_SIZE 30
#define A_SIZE 300
//Ignoriamo la lista e usiamo un array di record che li marcate con ampiezza massima 300
typedef struct p {
	char *inputFileName;
	char *outputFileName;
	int k;
} Parameters;

typedef struct r {
	char codiceEvent[S_SIZE];
	char nomeLuogo[S_SIZE];
	int capienzaMax;
} Record;

void error(char *e);
Parameters readInput(int argc, char *argv[]);
// void insertRecord();
// void printList();
// void buildList();
void printArray(Record recordArray[]);
void buildArray(char *inputFileName, Record recordArray[]);
void elab();


int main(int argc, char*argv[])
{
	 printf("=============A=============\n");

	 Parameters p = readInput(argc, argv);


	 printf("=============B=============\n");
	 Record recordArray[A_SIZE] = {0};
	 buildArray(p.inputFileName, recordArray);

	 printArray(recordArray);
	 printf("=============C============\n");

	 printf("=============D============\n");


}

void error(char *e)
{
	if (e == NULL)
		return;

	fprintf(stderr, "[ERROR]: %s\n", e);
	exit(EXIT_FAILURE);
}

Parameters readInput(int argc, char *argv[])
{
	if (argc != 4)
		error("Number o parameters wrong!\n");

	char *inputFileName = argv[1];
	char *outputFileName = argv[2];
	int k = atoi(argv[3]);

	//deve essere un file .bin
	if (!inputFileName || strcmp(inputFileName + strlen(inputFileName) - 4, ".bin") != 0)
		error("inputFileName not valid\n");

	//file .txt
	if (!outputFileName || strcmp(outputFileName + strlen(outputFileName) - 4, ".txt") != 0)
		error("outputFileName not valid\n");

	//intero
	Parameters p = {inputFileName, outputFileName, k};
	//posso creare la mia strutture Parameters e ritornarla
	return p;
}

void buildArray(char *inputFileName, Record recordArray[A_SIZE])
{

	const char *mode = "r";

	FILE *fp =  fopen(inputFileName, mode);
	if (!fp)
	{
		error("Error opening file with mode");
	}

	// Salta la prima riga "** PrintList() **"
	char buffer[256];
	fgets(buffer, sizeof(buffer), fp);

	int i = 0;

	// Il file è di TESTO, non binario! Usa fscanf invece di fread
	while (fscanf(fp, "%s %s %d",
	              recordArray[i].codiceEvent,
	              recordArray[i].nomeLuogo,
	              &recordArray[i].capienzaMax) == 3)
	{
		printf("Record %d: %s %s %d\n", i,
		       recordArray[i].codiceEvent,
		       recordArray[i].nomeLuogo,
		       recordArray[i].capienzaMax);
		i++;

		if (i >= A_SIZE)
			break;
	}

	printf("Read %d records from file %s\n", i, inputFileName);

	if (fclose(fp) == EOF)
		error("Error closing file\n");

	return;
}

 void printArray(Record recordArray[A_SIZE])
 {
	 for (int i = 0; i < A_SIZE; i++)
	 {
		 if (recordArray[i].codiceEvent[0] == '\0')
		 {
			 printf("End of Array\n");
			 break;
		 }

		 printf("Element number %d: %s %s %d\n", i + 1, recordArray[i].codiceEvent, recordArray[i].nomeLuogo, recordArray[i].capienzaMax);
	 }

 }
