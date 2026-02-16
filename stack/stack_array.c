#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

typedef struct {
    int data[MAX];
    int top;
} Stack;

void initStack(Stack* s);
bool isEmpty(Stack* s);
bool isFull(Stack* s);
void push(Stack* s, int value);
int pop(Stack* s);
int peek(Stack* s);
void printStack(Stack* s);
void error(char* e);

int main() {
    Stack s;
    initStack(&s);

    printf("--- Test Pila con Array Statico ---");
    
    push(&s, 10);
    push(&s, 20);
    push(&s, 30);
    
    printStack(&s);
    
    printf("Elemento in cima (peek): %d", peek(&s));
    
    printf("Estrazione (pop): %d", pop(&s));
    printf("Estrazione (pop): %d", pop(&s));
    
    printStack(&s);
    
    return 0;
}

void initStack(Stack* s) {
    s->top = -1;
}

bool isEmpty(Stack* s) {
    return s->top == -1;
}

bool isFull(Stack* s) {
    return s->top == MAX - 1;
}

void error(char* e) {
    fprintf(stderr, "[ERROR]: %s", e);
    exit(EXIT_FAILURE);
}

void push(Stack* s, int value) {
    if (isFull(s)) {
        error("Stack Overflow");
    }
    s->data[++(s->top)] = value;
}

int pop(Stack* s) {
    if (isEmpty(s)) {
        error("Stack Underflow");
    }
    return s->data[(s->top)--];
}

int peek(Stack* s) {
    if (isEmpty(s)) {
        error("Peek on empty stack");
    }
    return s->data[s->top];
}

void printStack(Stack* s) {
    if (isEmpty(s)) {
        printf("Pila vuota.");
        return;
    }
    printf("Contenuto della Pila (cima -> fondo):");
    for (int i = s->top; i >= 0; i--) {
        printf("| %d |", s->data[i]);
    }
    printf(" --- ");
}
