#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct p
{
    double x;
    double y;
    int n;

} Parameters;

typedef struct n
{
    double d;
    struct n *next;
} Node;

typedef struct s
{
    Node *top;
} Stack;

void error(char *);
Parameters readInput(int, char *[]);
unsigned int get_random();
void initStack(Stack *s);
int isEmpty(Stack *s);
void push(Stack* , double );
double pop(Stack* );
void buildStack(double, double, int, Stack*);
void buildArray(Stack*, double [], int );
void elabValues(double*, int);

void main(int argc, char *argv[])
{
    printf("\n===============A===============");
    Parameters p = readInput(argc, argv);

    printf("\n===============B===============");
    Stack stack;
    initStack(&stack);
    buildStack(p.x, p.y, p.n, &stack);

    printf("\n===============C e D===============");
    double *array = (double*)malloc(sizeof(double)*p.n);

    buildArray(&stack, array, p.n);

    printf("\n===============E===============");
    elabValues(array, p.n);

}

void error(char *e)
{
    fprintf(stderr, "[ERROR]: %s", e);
    exit(EXIT_FAILURE);
}

Parameters readInput(int argc, char *argv[])
{
    if (argc != 4)
        error("\nNumber of Parameters wrong!");

    double x = atof(argv[1]);
    double y = atof(argv[2]);
    int n = atoi(argv[3]);

    if (x < 100 || x > 10000)
        error("\nx parameters does not satisfy the correct range [100.0, 1000,0]");

    if (y < 100 || y > 10000)
        error("\ny parameters does not satisfy the correct range [100.0, 1000,0]");

    if (x > y)
        error("\nx must be minor to y");

    if (y - x < 300)
        error("\ny - x must be major to 300.0");

    if (n < 15 || n > 30)
        error("\nInteger n does not satisfy the correct range [15, 30]");

    Parameters p = {x, y, n};

    return p;
}

double genDouble(double x, double y)
{
    unsigned int random_val = get_random();
    // Normalizziamo [0,1]
    double normalized_val = (double)random_val / (double)UINT_MAX;

    // Portiamo a range [x, y]
    return normalized_val + x * (y - x);
}

unsigned int get_random()
{
    static unsigned int m_w = 123456;
    static unsigned int m_z = 789123;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}

void initStack(Stack *s)
{
    s->top = NULL;

    return;
}

int isEmpty(Stack *s)
{
    return s->top == NULL;
}

void push(Stack *s, double d)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode)
        error("Error allocating memor for new node");

    // Prima diamo contenuto al nostro nodo
    newNode->d = d;
    newNode->next = s->top; //Sarà NULL se la pila è vuota

    s->top = newNode;


}

double pop(Stack *s)
{
    if(isEmpty(s))
    {
        error("Pila vuota!");
    }

    Node *tmp = s->top;
    double d = tmp->d; 

    s->top = tmp->next;
    free(tmp);
    return d;
}

void buildStack(double x, double y, int n, Stack* stack)
{
    printf("\n** buildStack() **");

    double random_number = 0;

    for (int i = 0; i < n; i++)
    {
        random_number = genDouble(x, y);
        push(stack, random_number);

        printf("\nDato inserito (%d): %lf", i, random_number);
    }

    printf("\n** buildStack() end**");
    
}

void buildArray(Stack* stack, double arrayToBuild[], int n)
{
    printf("\n** buildArray() **");
    
    int i = 0;
    while(isEmpty(stack) != 1 && i < n)
    {
        double elementPopped = pop(stack);
        printf("\nDato estratto (%d): %lf", i, elementPopped);
        arrayToBuild[i] = elementPopped;
        i++;
    }
    
    printf("\n** buildArray() end**");
    
}

void elabValues(double* array, int n)
{
    printf("\n** elabValues() ** ");

    double m = 0;
    int k = 0;

    for (int i = 0; i < n; i++)
    {
        m += array[i];
    }

    m = m/n;
    printf("avg= %lf ", m);
    
    
    for (int j = 0; j < n; j++)
    {
        if (array[j] > m)
        {
            k++;
        }
    }

    printf("no. of values > %lf = %d", m, k);
}