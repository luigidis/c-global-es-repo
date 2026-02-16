#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node* next;
} Node;

typedef struct stack
{
    Node* top;
} Stack;

void error(char*);
void initStack(Stack*);
int isEmpty(Stack*);
void push(Stack*, int);
int pop(Stack*);
int peek(Stack*);
void printStack(Stack*);

int main(int argc, char* argv[])
{
    Stack stack;
    initStack(&stack);

    push(&stack, 1);
    push(&stack, 10);
    push(&stack, 20);

    printStack(&stack);

    int first = pop(&stack);
    printf("\nfirst element: %d", first);
    printStack(&stack);

    int second = pop(&stack);
    printf("\nsecond element: %d", second);
    printStack(&stack);

    int third = pop(&stack);
    printf("\nthird element: %d", third);
    printStack(&stack);
    
    return 1;
}

void error(char* e)
{
    fprintf(stderr, "[ERROR]: %s", e);
    exit(EXIT_FAILURE);
}

void initStack(Stack* s)
{
    s->top = NULL;

    return;
}

int isEmpty(Stack* s)
{
    return (s->top == NULL);
}

void push(Stack* s, int value)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode)
        error("Node not allocated correctly");

    newNode->data = value;
    newNode->next = s->top;
    s->top = newNode;
    
}

int pop(Stack* s)
{
    if (isEmpty(s))
        error("Stack empty");
    
    Node* temp = s->top;

    int value = temp->data;

    s->top = temp->next;
    free(temp);

    return value;
}

int peek(Stack* s)
{
    if(isEmpty(s)) return -1;

    return s->top->data;
}

void printStack(Stack* s)
{
    if(isEmpty(s))
    {
        printf("\nPila vuota. \n");
        return;
    }

    Node* current = s->top;
    printf("\nContenuto nella Pila (dalla cima):\n");
    while (current != NULL)
    {
        printf("| %d |\n", current->data);
        current = current->next;
    }

    printf(" --- \n");
}