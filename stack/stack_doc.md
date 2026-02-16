# Documentazione Pila (Stack) in C

Una **Pila** (o Stack) è una struttura dati lineare che segue il principio **LIFO** (*Last In, First Out*): l'ultimo elemento inserito è il primo ad essere rimosso.

## Concetti Principali

- **Top**: L'indice o il puntatore all'elemento in cima alla pila.
- **Capacità**: Il numero massimo di elementi che la pila può contenere (nel caso di implementazione con array statico).
- **Underflow**: Si verifica quando si tenta di estrarre un elemento da una pila vuota.
- **Overflow**: Si verifica quando si tenta di inserire un elemento in una pila piena.

## Funzioni Principali da Implementare

Ecco le firme delle funzioni fondamentali per gestire una pila di interi:

### 1. Inizializzazione
Inizializza la struttura della pila o il puntatore al top.
```c
void init(Stack *s);
```

### 2. IsEmpty
Verifica se la pila è vuota.
```c
bool isEmpty(Stack *s);
```

### 3. IsFull
Verifica se la pila è piena (necessaria per implementazioni con array).
```c
bool isFull(Stack *s);
```

### 4. Push
Inserisce un nuovo elemento in cima alla pila.
```c
void push(Stack *s, int value);
```

### 5. Pop
Rimuove e restituisce l'elemento in cima alla pila.
```c
int pop(Stack *s);
```

### 6. Peek (o Top)
Restituisce l'elemento in cima alla pila senza rimuoverlo.
```c
int peek(Stack *s);
```

## Struttura Dati Esempio (Array Statica)

```c
#define MAX 100

typedef struct {
    int data[MAX];
    int top;
} Stack;
```

## Struttura Dati Esempio (Lista Collegata Dinamica)

L'implementazione con lista dinamica permette alla pila di crescere indefinitamente (fino a esaurimento della memoria RAM).

```c
typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* top;
} DynamicStack;
```

### Differenze principali
- **Memoria**: L'array statico alloca memoria contigua in anticipo. La lista dinamica alloca memoria per ogni nodo a runtime (`malloc`).
- **Overflow**: Virtualmente assente nella lista dinamica (limitata solo dalla RAM).
- **Gestione**: Richiede la deallocazione manuale della memoria (`free`) per evitare memory leak.
