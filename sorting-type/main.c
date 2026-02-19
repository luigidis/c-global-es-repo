#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE 10

void bubbleSort(int[], int);
void insertionSort(int[], int);
void selectionSort(int[], int);
void printArray(int[], int);
void swap(int[], int, int);

int main(int argc, char *argv[])
{
    int original[10] = {10, 28, 40, 32, 76, 20, 30, 1, 5, 8};
    int matrix[ARRAY_SIZE];

    printf("\nArray originale:");
    printArray(original, ARRAY_SIZE);

    // Selection Sort
    printf("\nSelection Sort originale:");

    memcpy(matrix, original, sizeof(original));
    selectionSort(matrix, ARRAY_SIZE);
    printArray(matrix, ARRAY_SIZE);

    // Insertion Sort
    printf("\nInsertion Sort originale:");

    memcpy(matrix, original, sizeof(original));
    insertionSort(matrix, ARRAY_SIZE);
    printArray(matrix, ARRAY_SIZE);

    // Bubble Sort
    printf("\nBubble Sort originale:");
    memcpy(matrix, original, sizeof(original));
    bubbleSort(matrix, ARRAY_SIZE);
    printArray(matrix, ARRAY_SIZE);

    printf("\n");
}

// L'idea del bubbleSort è quella di confrontare due valori adiacenti, se questi valori sono uno più grande dell'altro all'ora li scambio (se voglio oridnare l'array in ordine crescente)
// Viene definito bubble perchè i valori più grandi o piccoli in base a come si ordina, "galleggiano" verso la fine dell'array come le bolle che salgono
void bubbleSort(int matrix[], int n)
{
    // Iteriamo lungo tutto l'array partendo sempre dal secondo elemento
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (matrix[j] > matrix[j + 1])
            {
                swap(matrix, j, j + 1);
            }
        }
    }
}

void insertionSort(int matrix[], int n)
{

    // Questo volta parto dall'indice 1 cioè il secondo elemento dell'array perchè il primo lo considero già ordinato,
    // anche qui non devo andare a vedere tutti i 10 elementi ma solo i 9 elementi dietro al primo
    for (int i = 1; i < n; i++)
    {
        int element_to_insert = matrix[i];
        int position_to_insert = i;
        // Mentre il punto dove inserire e maggiore di 0 e finche il valore nella posizione dell'array è maggiore all'elemento da inserire
        // Sposto il valore a destra rispetto all'ellemento e diminuisco l'indice
        while (position_to_insert > 0 && matrix[position_to_insert - 1] > element_to_insert)
        {
            matrix[position_to_insert] = matrix[position_to_insert - 1];
            position_to_insert--;
        }
        // Appena ho trovato la posizione dove inserire l'elemento
        matrix[position_to_insert] = element_to_insert;
    }
}

// Il seclection sort
// 1. selezione l'elemento più piccolo dell'array e lo scambia con il primo
// 2. selezione il secondo elemento più piccolo dell'array e lo scambia con il secondo
// 3. e così via fino alla fine dell'array

void selectionSort(int matrix[], int n)
{
    // scorriamo l'interno array meno un elemento perchè l'ultimo sarà già ordinato quindi n - 1
    // Questo vuol dire che se ho un array da 10 elementi io dovrò iterare solo 9 volte perchè nell'ultimo scambio
    // l'array sarà già ordinato
    for (int i = 0; i < n - 1; i++)
    {
        int smallest = i; // indice dell'item che andiamo a prendere
        for (int j = i + 1; j < n; j++)
        {
            if (matrix[j] < matrix[smallest])
            {
                smallest = j;
            }
        }
        swap(matrix, i, smallest);
    }
}

void printArray(int matrix[], int n)
{
    printf("\n*** Stampo array ***");

    for (int i = 0; i < n; i++)
    {
        printf("| %d |", matrix[i]);
    }

    printf("\n*** Fine stampa array ***");
}

void swap(int matrix[], int first, int second)
{
    int temp = matrix[first];
    matrix[first] = matrix[second];
    matrix[second] = temp;
}
