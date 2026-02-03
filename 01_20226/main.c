#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGHT_STRING_SIZE 200
//Inizio ore 10:50

typedef struct p {
	char *inputFilename;
	char *outputFilename;
	int n;
	int m;
} Parameters;

typedef struct n {
	char p[MAX_LENGHT_STRING_SIZE]; //il valore salvato
	int l;
	struct n* next; //Puntatore al nodo sottostante
} Node;



void error(char*);
Parameters readInput(int argc, char *argv[]);
int countWords(char* s);
int isEmpty(Node*);
void push(Node **, char *);
char* pop(Node **);
int buildStack(Node** ,FILE* ,int ,int);
void printStack(Node*);
int clearStack(Node **top,char *outputFilename);
void printRecord(Node *record);
void elabStrVowels(char *s);
void printFile(char *s, char* outputFilename);

int main(int argc, char *argv[])
{
	printf("\n===============A===============");
	Parameters p = readInput(argc, argv);
	
	
	printf("\n===============B===============");
	FILE *f = fopen(p.inputFilename, "r");
	if (f == NULL) {
		error("Error opening the input file!");
	}
	
	printf("\nDEBUG: File aperto");
	printf("\n===============C===============");
	Node *stack = NULL;
	
	buildStack(&stack, f, p.n, p.m);
	// printStack(stack);
	
	fclose(f);
	 printf("\nDEBUG: Stack costruito");
	
	printf("\n===============D ed E===============");
	
	if (clearStack(&stack, p.outputFilename))
		printf("\n[SUCCESS]\n");
	
}


void error(char *e)
{
	if (!e)
		return;
	
	fprintf(stderr, "\n[ERROR]: %s", e);
	exit(EXIT_FAILURE);
}


Parameters readInput(int argc, char *argv[]) 
{
	if (argc != 5)
	{
		error("Numer of Parameters wrong!");
	}
	
	char *inputFilename = argv [1];
	char *outputFilename = argv[2];
	int n = atoi(argv[3]);
	int m = atoi(argv[4]);
	
	if (!inputFilename || strcmp(inputFilename + strlen(inputFilename) - 4, ".txt") != 0)
		error("Input file name not valid!");
	
	if (!outputFilename || strcmp(outputFilename + strlen(outputFilename) - 4, ".txt") != 0)
		error("Output file name not valid!");
	
	if (n >= m)
		error("Integer not valid secont integer must be bigger than first");
	
	
	Parameters p = {inputFilename, outputFilename, n, m};
	
	return p;
}

int countWords(char *s)
{
	int count = 0;
	int in_word = 0;
	
	for (int i = 0; s[i] != '\n' && s[i] != '\0' ; i++)
	{
		//Se trovo uno spazio
		if (s[i] == ' ') 
		{
			in_word = 0;
		}
		//Se trovo un carattere diverso dallo spazio
		else if (in_word == 0) {
			in_word = 1;
			count++;
		}
	}
	
	return count;
}

int isEmpty(Node *top)
{
	return top == NULL;
}
void push(Node **top, char *value)
{
	Node *newNode = (Node*)malloc(sizeof(Node));
	
	if(!newNode) return;
	
	strcpy(newNode->p, value);
	newNode->l = strlen(value);
	newNode->next = *top;
	*top = newNode;
	
	return;
}


char* pop(Node **top)
{
	if (isEmpty(*top)) return NULL;
	
	Node *temp = *top;
	char *val = (char*)malloc(strlen(temp->p) + 1);
	if (val == NULL) return NULL;
	strcpy(val, temp->p);
	*top = temp->next;
	free(temp);
	
	return val;
	
}

void printStack(Node *top)
{
	if (isEmpty(top) == 1) return;
	
	Node *temp = top;
	int i = 1;
	
	while (isEmpty(temp) == 0)
	{
		
		printf("\nElemento dello stack numero %d: [Lunghezza] = %d, [Frase] = %s", i, temp->l, temp->p);
		temp = temp->next;
		i++;
	}
}

void printRecord(Node *record)
{
	if (isEmpty(record) == 1) return;
	
	printf("\n %d ## %d ## %s", countWords(record->p), record->l, record->p);
}


int buildStack(Node** top, FILE *f, int n, int m)
{
	
	char buffer[MAX_LENGHT_STRING_SIZE];
	//Leggo riga per riga
	while(fgets(buffer, MAX_LENGHT_STRING_SIZE, f) != NULL)
	{
		
		if (countWords(buffer) >= n && countWords(buffer) <= m)
		{
			 //rimuovo la new line
			buffer[strcspn(buffer, "\n")] = '\0';
			push(top, buffer);	
		}
	}
	
	return 1;
}

void elabStrVowels(char *s)
{
	char *c = s;
	
	while (*c != '\0')
	{
		if (*c >= 'A' && *c <= 'Z')
		{
			*c = tolower(*c);
		}
		
		if (*c == 'a' || *c == 'e' || *c == 'i' || *c == 'o'|| *c == 'u')
		{
			*c = 'X';
		}
		
		c++;
	}
}

int clearStack(Node **top,char* outputFilename)
{
	while(isEmpty(*top) == 0)
	{
		//stampa il record dello stack
		printRecord(*top);
	
		//poppa il record dallo stack
		char *s = pop(top);
	
		//salva la frase del record nel file di output
		elabStrVowels(s);
		printFile(s, outputFilename);
		
		free(s);
		
	}	
	
	return 1;
}

void printFile(char *s, char* outputFilename)
{
	FILE *f = fopen(outputFilename, "a");
	
	if (f == NULL)
	{
		error("Error opening the file");
	}
	
	fprintf(f, "%s\n", s);
	
	fclose(f);
}