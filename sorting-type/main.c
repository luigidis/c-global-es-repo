#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 10

void bubbleStort(int [], int);
void isertionSort(int [], int);
void selectionSort(int [], int);
void printArray(int [], int);

int main(int argc, char* argv[])
{
    int original[10] = {10, 28, 40, 32, 76, 20, 30, 1, 5, 8};
    int matrix[ARRAY_SIZE];

    printf("\nArray originale:");
    printArray(original, ARRAY_SIZE);

}

void bubbleSort(int matrix[], int n)
{

}

void isertionSort(int matrix[], int n)
{

}

void selectionSort(int matrix[], int n)
{

}

void printArray(int matrix[], int n)
{
    printf("\n*** Stampo array ***");
    
    for (int i = 0; i < n; i++)
    {
        printf("%d ,", matrix[i]);
    }

    printf("\n*** Fine stampa array ***");
}