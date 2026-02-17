#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_SIZE 31

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

void error(char* );
Parameters readInput(int ,char* []);
void initializeList(List* );
void insertRecord(List* , float f, char* s);
void buildList(List* , char*);
void printList(List*);
void elab(float, List*);

int main(int argc,char* argv[])
{
	printf("\n====================A====================");
	Parameters p = readInput(argc, argv);
	printf("\nstring: %s, float: %f", p.inputFilename, p.f);

	printf("\n====================B====================");
	printf("Loading PrintList");
	
	List list;
	initializeList(&list);

	buildList(&list, p.inputFilename);

	printf("\n====================C====================");
	printList(&list);
	
	printf("\n====================D====================");
	elab(p.f, &list);
	
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
	
	if (!inputFilename || strlen(inputFilename) < 5 || strcmp(inputFilename + strlen(inputFilename) - 4, ".txt"))
	{
		error("Input file name has a wrong extension");
	}
	
	if (f < 1.0 || f >20.0)
	{
		error("float not correct");
	}
		
	Parameters p = {inputFilename, f};
	
	return p;
}

void initializeList(List *list)
{
	list->head = NULL;
	list->tail = NULL;

	printf("List initialized");

	return;
}

void insertRecord(List *list, float f, char* s)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (!newNode)
		error("Error during node allocation");

	//Diamo identità e contenuto al nuovo nodo
	newNode->f = f;
	strcpy(newNode->string, s);

	newNode->next = NULL;
	newNode->prev = NULL;
	//Dobbiamo implementare il comportamento secondo il quale l'elemento si va a posizionare in ordine lessiografico crescente
	
	//Caso 1: Lista vuota
	if (list->head == NULL)
	{
		list->head = newNode;
		list->tail = newNode;
		printf("Inserito primo elemento in una lista vuota");
		return;
	}

	//Cerca la poszione per dove essere messo il nuovo nodo rispettando l'ordine lessiografico crescente
	Node* current = list->head;

	while(current != NULL && strcmp(newNode->string, current->string) >= 0)
	{
		current = current->next;
	}

	//Se current è == NULL, significa che newNode è il più grande quindi va in Coda
	if (current == NULL)
	{
		newNode->prev = list->tail;
		list->tail->next = newNode;
		list->tail = newNode; //Aggiorniamo la tail
	}
	//Se current->prev == NULL significa che il nostro nuovo nodo viene prima della testa
	else if (current->prev == NULL)
	{
		newNode->next = current; //Questa sarebbe la testa list->head prima di sostituirla
		current->prev = newNode;
		list->head = newNode; //Head aggiornata
	}
	//Ultimo caso siamo nel Mezzo, quindi non dobbiamo aggiornare nè head nè tail
	//Quindi devo inserere tra current->perv e current
	else
	{
		newNode->next = current;
		newNode->prev = current->prev;
		current->prev->next = newNode;
		current->prev = newNode;
	}
	
	printf("Inserito primo elemento in lista");


}

void buildList(List *list, char* inputFilename)
{
	//legge le stringhe dal file
	FILE* f = fopen(inputFilename, "r");
	
	char buffer[MAX_STRING_SIZE];
	char bufferString[MAX_STRING_SIZE];
	float bufferFloat;

	int i = 1;
	while (fgets(buffer, MAX_STRING_SIZE,f) != NULL)
	{
		//Se ci troviamo in posizione dispari torveremo il float
		if (i % 2 != 0)
		{
			bufferFloat = atof(buffer);
			printf("\nFloat trovato: %f", bufferFloat);

			i++;
		}
		//Sennò troveremo la stringa e ogni volta che trovo la string inserisco il record e resetto i buffer
		else
		{
			strcpy(bufferString, buffer);
			printf("\nString trovata: %s", bufferString);
			//strcspn restituisce la prima occorrenza di ciò che mettiamo come secondo argomento
			bufferString[strcspn(bufferString, "\n")] = '\0';
			insertRecord(list, bufferFloat, bufferString);
			i++;
		}

	}
	
	
	//le inserisce una alla volta mendiante insertRecord()
	
}

void printList(List *list)
{
	if (list->head == NULL)
	{
		printf("Lista vuota");
		return;
	}

	printf("\nStampo la Lista...");
	int i = 0;
	Node* current = list->head;

	while (current != NULL)
	{
		printf("\nRecord %d: | %s | %f |\n", i, current->string, current->f);
		current = current->next;
		i++;
	}

	printf("\nFine stampa...");

}

//Funzione che stampa il numero di record tali che V >= F;
void elab(float f, List* list)
{
	if (list->head == NULL)
	{
		printf("Lista vuota");
		return;
	}

	printf("\nElab in corso...");
	int i = 0;
	Node* current = list->head;

	while (current != NULL)
	{
		if (current->f >= f)
		{
			i++;
		}
		current = current->next;
	}

	printf("\nFine elab, numero di record tali che V >= %f è %d", f, i);
}
