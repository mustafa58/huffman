#include <stdio.h>
#include <stdlib.h>

void yaz(int [][2], int);
int Partition(int [][2], int, int);
void swap(int [][2], int, int);

typedef struct STACK {
    int size;
    int st[50];
    int top;
}STACK;

STACK* initialize(int size) {
    STACK *stack = malloc(sizeof(STACK));
    stack->size = size;
    stack->top = 0;
}

int isEmpty(STACK *stack) {
    if(stack->top==0)
        return 1;
    else return 0;
}

int isFull(STACK *stack) {
    if(stack->top==stack->size)
        return 1;
    else return 0;
}

int pop(STACK *stack) {
    if(isEmpty(stack)) {
        printf("Stack is Empty.");
        return -1;
    }else {
        stack->top--;
        int val = stack->st[stack->top];
        return val;
    }
}

void push(STACK *stack, int value) {
    if(isFull(stack)) {
        printf("Stack is Full.");
        return;
    }else {
        stack->st[stack->top] = value;
        stack->top++;
    }
}

void topla(int A[][2], int N) {
    int T,j,k,i=0;
    while(i<(N-1))
    {
        //printf("i: %d\n", i);
        T = A[i][1] + A[i+1][1];
        //printf("A[%d][1]: %d, A[%d][1]: %d\n", i, A[i][1], i+1, A[i+1][1]);
        j = i+2;
        while(A[j][1]<=T && j<N) {
            j++;
        }
        k = N-1;
        while(k>=j) {
            A[k+1][1] = A[k][1];
            A[k+1][0] = A[k][0];
            k--;
        }
        A[j][1] = T;
        A[j][0] = -(i+1);
        i+=2;

        N++;
        //yaz(A, N);
    }
}

void yaz(int A[][2], int N)
{
    int i;
    /*for(i=0;i<N;i++) {
        //if(A[i-1][1]>=10)
        //    printf(" ");
        printf("%d ", i);
    }
    printf("\n");*/
    for(i=0;i<N;i++) {
        if(A[i-1][1]>=10 && i>0)
            printf(" ");
        if(A[i][0] == 0)
            printf("LF ");
        else if(A[i][0] == ' ')
            printf("SP ");
        else
            printf("%c ", A[i][0]);
    }
    printf("\n");
    for(i=0;i<N;i++) {
        if(A[i][0]==0 || A[i][0]==' ')
            printf("%d  ", A[i][1]);
        else
            printf("%d ", A[i][1]);
    }
    printf("\n");
}

void Quicksort(int A[][2], int left, int right) {
    int s;
    if(left < right) {
        s = Partition(A, left, right);
        //printf("s = %d\n", s);
        Quicksort(A, left, s-1);
        Quicksort(A, s+1, right);
    }
}

int Partition(int A[][2], int left, int right)
{
    int i,j,pivot;
    pivot = A[left][1];
    i = left+1;
    j = right;
    //printf("pivot = %d\n", pivot);
    while(i<=j)
    {
        while((i<=j) && A[i][1]<pivot) {
            i++;
        }
        //printf("\ti=%d, ", i);
        while((i<=j) && A[j][1]>=pivot) {
            j--;
        }
        //printf("j=%d\n", j);
        //printf("\t%d<->%d\n", A[i], A[j]);
        swap(A, i, j);
    }
    //printf("%d<->%d\n", A[i], A[j]);
    swap(A, i, j);
    //printf("pivot swap, %d<->%d\n", A[left], A[j]);
    swap(A, left, j);
    //yazdir(A, 16);
    return j;
}

void swap(int A[][2], int x, int y) {
    int temp,tmp;
    temp = A[x][0];
    tmp = A[x][1];
    A[x][0] = A[y][0];
    A[x][1] = A[y][1];
    A[y][0] = temp;
    A[y][1] = tmp;
}

void frekans_analiz(int ASCII[], char metin[], int metin_boyut)
{
    int i;
    for(i=0;i<256;i++) {
        ASCII[i] = 0;
    }
    for(i=0;i<metin_boyut;i++)
    {
        ASCII[(int)metin[i]]++;
    }
}

void make_charset(int char_set[][2], int size, int ASCII[])
{
    int i,j;
    for(i=0;i<size;i++) {
        char_set[i][0] = 0;
        char_set[i][1] = 0;
    }

    j = 0;
    for(i=0;i<256;i++) {
        if(ASCII[i]) {
            char_set[j][0] = i;
            char_set[j][1] = ASCII[i];
            j++;
        }
    }
}

int gezinTree(int kar[][2], int indis, int sembl, STACK* stk)
{
    if(kar[indis][0]<0) {
        int right, left;
        right = (-1*kar[indis][0]);
        left = (right-1);

        if(gezinTree(kar, left, sembl, stk)) {
            push(stk, 0);
            return 1;
        }else if(gezinTree(kar, right, sembl, stk))
        {
            push(stk, 1);
            return 1;
        }
        else return 0;
    }
    else {
        if(kar[indis][0]==sembl)
            return 1;
        else return 0;
    }
}

int karakter(int kar[][2], int size, int sembl) {
    STACK *st = initialize(50);
    gezinTree(kar, size-1, sembl, st);
    while(!isEmpty(st))
    {
        printf("%d", pop(st));
    }
    printf("\n");
    free(st);
}

int boyut(char metin[]) {
    int i=0;
    while(metin[i]!='\0') {
        i++;
    }
    i++;
    return i;
}

int main(int argc, char** argv)
{
    printf("Huffman Project[v0.7]\nCreator: MustafaBodur\n");
    int i,size,N=0;

    //char metin[] = "it was the best of times it was the worst of times";
    
    char metin[10000];
    printf("metin :");
    gets(metin);
    
    
    int ASCII[256];
    printf("%d karakter\n", boyut(metin));
    frekans_analiz(ASCII, metin, boyut(metin));


    for(i=0;i<256;i++) {
        if(ASCII[i]) {
            if(i==0)
                printf("%d LF=>%d\n", i, ASCII[i]);
            else if(i==' ')
                printf("%d SP=>%d\n", i,ASCII[i]);
            else
                printf("%d %c=>%d\n", i,i,ASCII[i]);
            N++;
        }
    }

    printf("N :%d\n", N);

    size = 2*N-1;

    int char_set[size][2];
    make_charset(char_set, size, ASCII);

    Quicksort(char_set, 0, N-1);
    int harfler[N];
    for(i=0;i<N;i++)
        harfler[i] = char_set[i][0];
    topla(char_set, N);
    yaz(char_set, size);

    //Eğer pointerları int derğer olarak depolarsak???

    for(i=0;i<N;i++) {
        if(harfler[i]==0)
            printf("LF: ");
        else if(harfler[i]==' ')
            printf("SP: ");
        else
            printf("%c: ", harfler[i]);
        karakter(char_set, size, harfler[i]);
    }
    getch();
    return 0;
}
