# Spiegazione del programma e dell'Insertion Sort

## Panoramica del programma

Il programma legge una matrice di `double` da un file di testo, la normalizza dividendo ogni elemento per il massimo della sua colonna, e infine ordina i valori di ogni colonna tramite insertion sort.

---

## Struttura del file di input

Il file `.txt` ha questo formato:

```
3 4
1.0 2.0 3.0 4.0
5.0 6.0 7.0 8.0
9.0 10.0 11.0 12.0
```

- La prima riga contiene `n` (righe) e `m` (colonne).
- Le righe successive contengono i valori `double` della matrice.

---

## Spiegazione riga per riga

### Includes e definizioni (righe 1-11)

```c
#include <stdio.h>    // Funzioni di I/O: printf, fprintf, fopen, fgets, fscanf, sscanf
#include <stdlib.h>   // malloc, exit, EXIT_FAILURE
#include <string.h>   // strlen, strcmp

#define MAX_BUFFER_SIZE 100   // Dimensione massima del buffer per leggere righe dal file
```

```c
typedef struct p {
    int n;    // Numero di righe della matrice
    int m;    // Numero di colonne della matrice
} Parameters;
```

Definisce una struct per raggruppare i due parametri `n` e `m` letti dal file, in modo da poterli restituire insieme da una funzione.

---

### Prototipi (righe 13-20)

```c
void error(char*);                              // Stampa un errore e termina il programma
char* readInput(int, char* []);                 // Valida gli argomenti da riga di comando
Parameters readFileToSetParameters(char*);      // Legge n e m dalla prima riga del file
double** allocateMatrix(int, int);              // Alloca dinamicamente una matrice n x m
void fillMatrix(char*, double**, int, int);     // Riempie la matrice con i valori dal file
void printMatrix(double**, int, int);           // Stampa la matrice a schermo
int normalize(double**, double**, int, int);    // Normalizza la matrice dividendo per il max di colonna
double getMax(double**, int, int);              // Trova il massimo di una colonna
```

I prototipi dichiarano le funzioni prima del `main`, permettendo al compilatore di conoscerne la firma prima di incontrarle nel codice.

---

### main (righe 22-58)

```c
char* inputFilename = readInput(argc, argv);
```
Valida gli argomenti passati da riga di comando e restituisce il nome del file di input.

```c
Parameters p;
p = readFileToSetParameters(inputFilename);
```
Apre il file, legge la prima riga e estrae `n` e `m`.

```c
double** v = allocateMatrix(p.n, p.m);
fillMatrix(inputFilename, v, p.n, p.m);
```
Alloca dinamicamente la matrice `v` con `n` righe e `m` colonne, poi la riempie con i valori dal file.

```c
double** w = allocateMatrix(p.n, p.m);
int i = normalize(v, w, p.n, p.m);
```
Alloca una seconda matrice `w` e la riempie con i valori normalizzati di `v`.

```c
printMatrix(v, p.n, p.m);
printMatrix(w, p.n, p.m);
```
Stampa entrambe le matrici.

---

### error (righe 60-64)

```c
void error(char* e)
{
    fprintf(stderr, "\n[ERROR]: %s", e);   // Stampa il messaggio su stderr (stream di errore)
    exit(EXIT_FAILURE);                     // Termina il programma con codice di errore
}
```

Funzione di utilita: stampa un messaggio di errore e termina immediatamente il programma.

---

### readInput (righe 66-83)

```c
if (argc != 2)
    error("Number of prameters wrong!");
```
Controlla che l'utente abbia passato esattamente un argomento (il nome del file). `argc` conta il nome del programma + gli argomenti, quindi deve essere 2.

```c
if (!argv[1] || strlen(argv[1]) < 5 || strcmp(argv[1] + strlen(argv[1]) - 4, ".txt"))
    error("Error in inputFilename ext o name");
```
- `!argv[1]`: controlla che l'argomento non sia NULL.
- `strlen(argv[1]) < 5`: il nome minimo valido e' `x.txt` (4 caratteri + almeno 1), quindi deve avere almeno 5 caratteri.
- `strcmp(argv[1] + strlen(argv[1]) - 4, ".txt")`: controlla che il file termini con `.txt`. `strcmp` restituisce 0 se le stringhe sono uguali, e 0 in C e' falso, quindi entra nell'if quando NON termina con `.txt`.

```c
return argv[1];
```
Restituisce il puntatore alla stringa dell'argomento (non crea una copia).

---

### readFileToSetParameters (righe 85-108)

```c
FILE* f = fopen(inputFilename, "r");
```
Apre il file in modalita lettura ("r" = read).

```c
if(!f)
    error("Errore opening file");
```
Se `fopen` fallisce restituisce NULL. Controlla e termina in caso di errore.

```c
char buffer[MAX_BUFFER_SIZE];
if (fgets(buffer, MAX_BUFFER_SIZE, f) != NULL)
{
    sscanf(buffer, "%d %d", &n, &m);
}
```
- `fgets` legge la prima riga del file nel buffer.
- `sscanf` estrae i due interi `n` e `m` dalla stringa letta.

```c
fclose(f);
Parameters p = {n, m};
return p;
```
Chiude il file e restituisce la struct con i parametri.

---

### allocateMatrix (righe 111-128)

```c
double **matrix = (double**)malloc(sizeof(double*) * n);
```
Alloca un array di `n` puntatori a `double`. Ogni puntatore rappresentera una riga della matrice.

```c
if (!matrix)
    error("Matrix not allocated correctly");
```
Controlla che `malloc` non abbia restituito NULL (memoria insufficiente).

```c
for (int i = 0; i < n; i++)
{
    matrix[i] = (double*)malloc(sizeof(double) * m);
    if (!matrix[i])
        error("Matrix not alocated correctly");
}
```
Per ogni riga, alloca un array di `m` double (le colonne). La struttura in memoria e':

```
matrix    → [ptr0][ptr1][ptr2]     (n puntatori)
              |     |     |
              v     v     v
            [m double] [m double] [m double]   (le righe)
```

---

### fillMatrix (righe 130-152)

```c
FILE* f = fopen(inputFilename, "r");
```
Riapre il file dall'inizio.

```c
fgets(buffer, MAX_BUFFER_SIZE, f);
```
Legge la prima riga e la scarta (contiene `n` e `m`, gia letti in precedenza).

```c
for (int i = 0; i < n; i++)
{
    for (int j = 0; j < m; j++)
    {
        fscanf(f, "%lf", &matrix[i][j]);
    }
}
```
- Ciclo esterno: itera sulle righe.
- Ciclo interno: itera sulle colonne.
- `fscanf(f, "%lf", ...)`: legge un `double` dal file. `%lf` e' il formato per `double` in `scanf`/`fscanf`. `fscanf` salta automaticamente spazi e newline.

```c
fclose(f);
```
Chiude il file.

---

### printMatrix (righe 154-169)

```c
for (int i = 0; i < n; i++)
{
    printf("\n");
    for (int j = 0; j < m; j++)
    {
        printf("[%lf]", matrix[i][j]);
    }
}
```
Per ogni riga stampa un newline, poi stampa ogni elemento tra parentesi quadre. `%lf` in `printf` stampa un `double` con 6 decimali di default.

---

### normalize (righe 171-184)

```c
for (int i = 0; i < m; i++)
```
Ciclo sulle **colonne** (da 0 a m-1).

```c
double z = getMax(matrixSource, i, n);
```
Trova il valore massimo della colonna `i`, scorrendo tutte le `n` righe.

```c
for (int j = 0; j < n; j++)
{
    matrixToFill[j][i] = matrixSource[j][i] / z;
}
```
Per ogni riga `j`, divide l'elemento della colonna `i` per il massimo `z`. Il risultato sara un valore tra 0.0 e 1.0 (se i valori sono positivi).

---

### getMax (righe 187-199)

```c
double max = matrix[0][col];
```
Inizializza `max` con il primo elemento della colonna.

```c
for (int k = 1; k < n; k++)
{
    if (matrix[k][col] > max)
    {
        max = matrix[k][col];
    }
}
```
Scorre tutte le righe della colonna `col`. Se trova un valore maggiore di `max`, aggiorna `max`. Alla fine, `max` contiene il valore piu grande della colonna.

---

## Insertion Sort sulle colonne (righe 201-221)

### Come funziona l'insertion sort

L'insertion sort funziona come ordinare le carte in mano: prendi una carta alla volta e la inserisci nella posizione corretta tra quelle gia ordinate.

### Spiegazione riga per riga

```c
void sortMatrixCols(double** matrixToSort, int n, int m)
```
Riceve la matrice, il numero di righe `n` e il numero di colonne `m`.

```c
for (int col = 0; col < m; col++)
```
**Ciclo esterno**: itera su ogni colonna. Ogni colonna viene ordinata indipendentemente dalle altre.

```c
for (int i = 1; i < n; i++)
```
**Ciclo dell'insertion sort**: parte dalla seconda riga (`i = 1`) perche un singolo elemento (la riga 0) e' gia "ordinato" per definizione. Ad ogni iterazione, l'elemento alla riga `i` verra inserito nella posizione corretta tra le righe 0..i-1.

```c
double key = matrixToSort[i][col];
```
Salva l'elemento corrente in `key`. Questo e' l'elemento che vogliamo inserire nella posizione corretta. Lo salviamo perche durante lo spostamento potrebbe essere sovrascritto.

```c
int j = i - 1;
```
`j` parte dalla posizione immediatamente sopra `i`. Scorrera verso l'alto (verso la riga 0) cercando la posizione giusta per `key`.

```c
while (j >= 0 && matrixToSort[j][col] < key)
```
Questo ciclo scorre verso l'alto finche:
- `j >= 0`: non siamo usciti dalla matrice (riga 0 e' il limite).
- `matrixToSort[j][col] < key`: l'elemento sopra e' piu piccolo di `key`.

Dato che la condizione e' `< key`, gli elementi piu piccoli vengono spostati verso il basso, quindi l'ordinamento e' **decrescente** (dal piu grande al piu piccolo).

> Se fosse `> key` l'ordinamento sarebbe **crescente**.

```c
matrixToSort[j + 1][col] = matrixToSort[j][col];
```
Sposta l'elemento alla riga `j` una posizione in basso (riga `j+1`), facendo spazio per `key`.

```c
j--;
```
Si sposta una riga piu in alto per continuare il confronto.

```c
matrixToSort[j + 1][col] = key;
```
Quando il `while` termina, `j+1` e' la posizione corretta per `key`. Lo inseriamo li.

### Esempio visivo

Ordinamento decrescente della colonna 0:

```
Stato iniziale:  [3]    Passo 1 (key=7):  [7]    Passo 2 (key=1):  [7]
                 [7]                       [3]                       [3]
                 [1]                       [1]                       [1]

i=1: key=7               i=2: key=1
j=0: 3 < 7 → sposta      j=1: 3 < 1? No → stop
     [3]  →  [_]               key va in posizione j+1 = 2
     [7]     [3]               (resta dov'e')
j=-1: stop
key va in posizione 0
```
