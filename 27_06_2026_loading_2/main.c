#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_SIZE 30

typedef struct p {
	char* inputFilename;
	float f;
} Parameters;


typedef struct n {
	char string[MAX_STRING_SIZE];
	float f;
	struct n* next;
	struct n* prev;
} Node;

typedef struct l {
	Node* head;
	Node* tail;
} List;

int main(int argc,char* argv[])
{
	printf("====================A====================");
	
	printf("====================A====================");
	printf("====================A====================");
	printf("====================A====================");
	printf("====================A====================");
	
	
}

void error(char *e)
{
	if (e == NULL)
		return;
	
	fprintf(stderr, "[ERROR]: %s", e);
	exit(EXIT_FAILURE);
}

Parameters readInput(int argc, char* argv[])
{
	if (argc != 3)
		error("Number of parameters wrong!");
	
	char *inputFilename = argv[1];
	float f = atof(argv[2]);
	
	if (!inputFilename || strlen(inputFilename) < 5 || strcmp(inputFilename + strlen(inputFilename) - 4, ".txt")
	{
		error("Input file name has a wrong extension");
	}
	
	if (f < 1.0 || f >20.0)
	{
		error("float not correct");
	}
	
	// p.inputFilename = malloc(strlen(inputFilename) + 1);
	// strcpy(p.inputFilename, inputFilename)
	//p.f = f;
	
	Parameters p = {inputFilename, f};
	
	return p;

}

void insertRecord(List *list)
{
	
}

void buildList(List *list, Record *record)
{
	//legge le stringhe dal file
	
	//le inserisce una alla volta mendiante insertRecord()
	
}

void printList(List *list)
{
	//Funzione che stampa l'intera lista sullo standard output dal primo all'ultimo elemento
}


void elab()
{
	//Funzione che stampa il numero di record tali che V >= F;
}

void push(List *list, char *s,float f)
{
	//Creiamo il nuovo nodo
	Node *newNode = (Node*)malloc(sizeof(Node));
	
	strcpy(newNode->string, s);
	newNode->f = f;
	
	//Inserisco nella test (Comportamento LIFO)
	newNode->next = list->head;
	newNode->prev = NULL;
	
	if (list->head != NULL)
	{
		list->head->prev = newNode;
	} else {
		//Lista vuola: head e tail sono lo stesso nodo
		list->tail = newNode;
	}
	
	list->head = newNode; // Aggiorno la testa 
}