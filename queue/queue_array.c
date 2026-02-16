#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 5 // Dimensione fissa della coda

typedef struct {
    int items[MAX_SIZE];
    int front;
    int rear;
} Queue;

// Prototipi
void initQueue(Queue* q);
bool isFull(Queue* q);
bool isEmpty(Queue* q);
void enqueue(Queue* q, int value);
int dequeue(Queue* q);
int peek(Queue* q);
void display(Queue* q);

int main() {
    Queue q;
    initQueue(&q);

    // Test Enqueue
    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);
    enqueue(&q, 50);

    // Prova a inserire in coda piena
    enqueue(&q, 60);

    display(&q);

    // Test Dequeue
    printf("Rimosso: %d\n", dequeue(&q));
    printf("Rimosso: %d\n", dequeue(&q));

    display(&q);

    // Test inserimento circolare (dovrebbe funzionare ora che abbiamo liberato 2 posti)
    enqueue(&q, 60);
    enqueue(&q, 70);
    
    display(&q);

    // Test Peek
    printf("Elemento in testa (peek): %d\n", peek(&q));

    return 0;
}

// Inizializza la coda
void initQueue(Queue* q) {
    q->front = -1;
    q->rear = -1;
}

// Verifica se la coda è piena
bool isFull(Queue* q) {
    // La coda è piena se il prossimo indice di rear coincide con front
    if ((q->rear + 1) % MAX_SIZE == q->front) {
        return true;
    }
    return false;
}

// Verifica se la coda è vuota
bool isEmpty(Queue* q) {
    if (q->front == -1) {
        return true;
    }
    return false;
}

// Inserisce un elemento (Enqueue)
void enqueue(Queue* q, int value) {
    if (isFull(q)) {
        printf("Errore: Coda piena (Overflow) -> Impossibile inserire %d\n", value);
        return;
    }

    if (isEmpty(q)) {
        // Se è il primo elemento, imposto front a 0
        q->front = 0;
    }

    // Avanzamento circolare: (rear + 1) % N
    q->rear = (q->rear + 1) % MAX_SIZE;
    q->items[q->rear] = value;
    
    printf("Inserito: %d\n", value);
}

// Rimuove un elemento (Dequeue)
int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Errore: Coda vuota (Underflow)\n");
        return -1;
    }

    int item = q->items[q->front];

    if (q->front == q->rear) {
        // Se era l'ultimo elemento rimasto, resetto la coda
        q->front = -1;
        q->rear = -1;
    } else {
        // Avanzamento circolare di front
        q->front = (q->front + 1) % MAX_SIZE;
    }

    return item;
}

// Restituisce l'elemento in testa senza rimuoverlo
int peek(Queue* q) {
    if (isEmpty(q)) {
        printf("Errore: Coda vuota\n");
        return -1;
    }
    return q->items[q->front];
}

// Stampa la coda (per debug)
void display(Queue* q) {
    if (isEmpty(q)) {
        printf("Coda vuota\n");
        return;
    }

    printf("Stato Coda: ");
    int i = q->front;
    while (true) {
        printf("%d ", q->items[i]);
        if (i == q->rear) break;
        i = (i + 1) % MAX_SIZE;
    }
    printf("\n");
}
