#define SORTSNAMES 3
#define SORTSTYPES 3
#define ARRAYSIZE 10
#define ROWS 8
#define COLS (ROWS/2)+1
#define N 3
static const char * const sortsNames[SORTSNAMES] = {
	"bubble",
	"insertion",
    "selection"
};

static const int sortsTypes[SORTSTYPES] = 
{
        1,      /* Ordinamento di un array monodimensionale */
        2,      /* Ordinamento di una matrice               */
        3       /* Ordinamento di una matrice di puntatori  */
};

enum exitval{
        SUCCESS = 0,
        INPUT_ERROR,
        READ_ERROR,
		MALLOC_ERROR,
        BUBBLE_ARRAY,
        BUBBLE_MATRIX,
        BUBBLE_POINTERS_MATRIX,
        INSERTION_ARRAY,
        INSERTION_MATRIX,
        INSERTION_POINTERS_MATRIX,
        SELECTION_ARRAY,
        SELECTION_MATRIX,
        SELECTION_POINTERS_MATRIX
};
const char * tags[] = {
	"BUBBLE_ARRAY",
	"BUBBLE_MATRIX",
	"BUBBLE_POINTERS",
	"INSERTION_ARRAY",
	"INSERTION_MATRIX",
	"INSERTION_POINTERS",
	"SELECTION_ARRAY",
	"SELECTION_MATRIX",
	"SELECTION_POINTERS",
};
const char * warnmsg[] = {
	"Operazione completata con successo",
    "Utilizzo >>> ./a.out <sort> <tipologia>\nConsultare >>> Istruzioni.txt",
    "Errore di lettura degli argomenti del main",
    "Errore durante un tentativo di allocazione dinamica",
    "Hai scelto il bubble sort in riferimento ad un array monodimensionale",
    "Hai scelto il bubble sort in riferimento ad una matrice",
    "Hai scelto il bubble sort in riferimento ad una matrice di puntatori",
    "Hai scelto l'insertion sort in riferimento ad un array monodimensionale",
    "Hai scelto l'insertion sort in riferimento ad una matrice",
    "Hai scelto l'insertion sort in riferimento ad una matrice di puntatori",
    "Hai scelto il selection sort in riferimento ad un array monodimensionale",
    "Hai scelto il selection sort in riferimento ad una matrice",
    "Hai scelto il selection sort in riferimento ad una matrice di puntatori"
};
typedef struct{
	int chosenType; 		 /* identifica il tipo di oggetto da allocare a prescindere dal sort */
	union{
		double * arr;
		double ** mat;
		double *** pmat;
	}allocation_t; 			 /* allocation_type */
	enum exitval exitStatus; /* valore di ritorno embeddato dentro la struct */
}data;
enum exitval chooseSort(int argc, char**argv,int * typeChoice);

/* Funzioni per allocazione e pseudo-randomizzazione */

double * randomizeArray(void);
double** randomizeMatrix(void);
double*** randomizePointersMatrix(void);

/* Funzione per liberare gli oggetti allocati*/

void freeData(data dt);

/* Funzioni di stampa */

void printArray(double*arr); 
void printMatrix(double**mat);
void printPointers(double***pmat);

data allocateData(int chosenType);

/* Funzione che stampa il codice sullo standard output */

enum exitval displayCode(int status);

/* Wrapper Functions:
 * Queste funzioni servono per poter passare il puntatore inizializzato dentro
 * l'union allocation_t */

void bubbleWrapper(data dt);
void insertionWrapper(data dt);
void selectionWrapper(data dt);

/* Sort Functions */

void bubbleArray(double *arr);
void bubbleMatrix(double **mat);
void bubblePointerMatrix(double ***pmat);
void insertionArray(double *arr);
void insertionMatrix(double **mat);
void insertionPointersMatrix(double ***pmat);
void selectionArray(double *arr);
void selectionMatrix(double **mat);
void selectionPointersMatrix(double ***pmat);

/* array di puntatori a funzioni che gestiscono effettivamente la chiamata alla funzione
 * associata all'algoritmo scelto, implementato secondo la modalità scelta  */

extern void (*doSort[3])(data dt);
