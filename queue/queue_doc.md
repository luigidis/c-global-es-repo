# Coda (Queue) in C

## Introduzione
Una **Coda** (o *Queue*) è una struttura dati astratta lineare che segue il principio **FIFO** (First In, First Out). Questo significa che il primo elemento inserito nella coda è il primo ad essere rimosso. È analoga a una fila di persone in attesa: chi arriva prima viene servito per primo.

A differenza della Pila (Stack) che è LIFO (Last In, First Out), nella Coda gli inserimenti avvengono a un'estremità (chiamata *Rear* o *Tail*) e le rimozioni avvengono all'estremità opposta (chiamata *Front* o *Head*).

## Strutture Dati Comuni
Le code in C possono essere implementate principalmente in due modi:
1.  **Array (Statica o Circolare):** Dimensione fissa. È efficiente ma limitata dalla dimensione allocata. Spesso si usa un approccio "circolare" per riutilizzare lo spazio liberato.
2.  **Lista Concatenata (Dinamica):** Dimensione variabile. Utilizza puntatori e allocazione dinamica della memoria (`malloc`). Non ha limiti di dimensione se non la memoria disponibile.

## Funzioni Principali
Per gestire una Coda, si implementano tipicamente le seguenti operazioni fondamentali:

### 1. `initQueue` (Inizializzazione)
Prepara la struttura dati per l'uso (es. imposta i puntatori `front` e `rear` a `NULL` o gli indici a `-1`).

### 2. `isEmpty` (Verifica se vuota)
Restituisce `true` (1) se la coda non contiene elementi, `false` (0) altrimenti. È fondamentale controllarlo prima di rimuovere elementi.

### 3. `isFull` (Verifica se piena - solo per implementazione con Array)
Restituisce `true` se non c'è più spazio per nuovi elementi. Non necessario per le liste collegate (a meno che non finisca la memoria heap).

### 4. `enqueue` (Inserimento)
Aggiunge un nuovo elemento alla fine (*rear*) della coda.
- Se la coda è piena (overflow), l'operazione fallisce.
- Se la coda era vuota, il nuovo elemento diventa sia *front* che *rear*.

### 5. `dequeue` (Rimozione)
Rimuove e restituisce l'elemento in testa (*front*) alla coda.
- Se la coda è vuota (underflow), l'operazione fallisce o restituisce un errore.
- Dopo la rimozione, il `front` avanza al prossimo elemento.

### 6. `peek` o `front` (Consultazione)
Restituisce il valore dell'elemento in testa senza rimuoverlo. Utile per vedere chi è il prossimo "servito".

## Esempio di Struttura (Lista Concatenata)

```c
typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;
```

## Esempio di Struttura (Array Circolare)

```c
#define MAX_SIZE 100

typedef struct Queue {
    int items[MAX_SIZE];
    int front;
    int rear;
} Queue;
```
