#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node* next;
} Node;

typedef struct queue
{
    Node* front;
    Node* rear;
} Queue;


void error(char*);
Queue* initQueue();
int isEmpty(Queue*);
int enqueue(Queue* , int);
int dequeue(Queue*);
int peek(Queue* );

void main (int argc, char* argv[])
{

}

void error(char* e)
{
    if (e == NULL) return;

    fprintf(stderr, "[ERROR]: %s", e);
    exit(EXIT_FAILURE);
}

Queue* initQueue()
{
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (!q)
        error("Queue allocation failed!");

    q->front = NULL;
    q->rear = NULL;

    return q;

}

int isEmpty(Queue* q)
{
    return (q->front == NULL);
}

int enqueue(Queue* q, int val)
{
    Node *temp = (Node*)malloc(sizeof(Node));
    if (!temp)
        error("Queue allocation failed!");
    
    temp->data = val;
    temp->next = NULL;

    if (isEmpty(q))
    {
        //La coda è vuota quindi devo metterlo in testa
        q->front = temp;
        q->rear = temp;
    }
    else 
    {
        q->rear->next = temp;
        q->rear = temp;
    }

    return 1;
}

int dequeue(Queue* q)
{
    //Controllo se la coda è vuota
    if (q == NULL || isEmpty(q))
    {
        fprintf(stderr, "Attempted dequeue from an empty queue!");
        return -1;
    }

    Node *temp = q->front;
    int val = temp->data;

    //Modifico la front della queue
    q->front = q->front->next;

    //Se la coda è diventata vuota, si resetta anche rear
    if(q->front == NULL)
    {
        q->rear = NULL;
    }

    free(temp);
    return val;
}

//Restituisce il valore dell'elemento in testa senza rimuoverlo
int peek(Queue* q)
{
    if(q == NULL || isEmpty(q))
    {
        fprintf(stderr, "Queue is empty or does not exsit");
        return -1;
    }

    return q->front->data;
}