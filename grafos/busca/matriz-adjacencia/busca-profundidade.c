#include <stdio.h>
#include <stdlib.h>

#include "data.h"

#define LEN 5


int** criaMatriz(){
    int linha;
    int **mat = (int**) malloc(LEN*sizeof(int*));
    for(linha =0; linha< LEN; linha++){
        mat[linha] = (int*) malloc(LEN*sizeof(int));
    }

    return mat;
}

void insereNaMatriz(int **mat, int* valores, int indexLinha){
    int coluna;

    for(coluna = 0; coluna< LEN; coluna++){
        mat[indexLinha][coluna] = valores[coluna];
    }
}

void mostraMatriz(int **mat){
    int coluna, linha;
    for(linha =0; linha<LEN; linha++){
        printf("vertice %d =>",linha+1);
        for(int coluna = 0; coluna< LEN; coluna++){
            if(mat[linha][coluna] == 1){
                printf("v%d ",coluna+1);
            }

        }
        printf("\n");
    }
}

//desaloca
void liberaMatriz(int **mat){
    for(int linha=0; linha<LEN; linha++){
        free(mat[linha]);
    }
    free(mat);
}

//visitados e pilha

int isInStackOrVisitedList(Stack* q,Visited* v, int value){
    int elementhasBeenVisited = 0;

    while(q != NULL){
        if(q->value == value){
            elementhasBeenVisited = 1;
            break;
        }
        q = q->next;
    }

    if(!elementhasBeenVisited){
        while(v != NULL){
            if(v->value == value){
                elementhasBeenVisited = 1;
                break;
            }
            v = v->next;
        }
    }
    return elementhasBeenVisited;
}

Stack* createStack(){
    return NULL;
}

Stack* appendToStack(Stack* s, int value){
    Stack* new = (Stack*) malloc(sizeof(Stack));
    new->value = value;
    new->next = s;

    return new;
}

int isNodeInStack(Stack* s, int v){
    Stack* p = s;
    int isInStack = 0;
    while(p != NULL){
        if(p->value == v){
            isInStack = 1;
        }
        p = p->next;
    }

    return isInStack;
}

int getLastNodeFromStack(Stack* s){
    if(s != NULL){
        return s->value;
    }else{
         return NULL;
    }
}

Stack* popAll(Stack* s){
    Stack* p = s;
    if(p!= NULL){

        Stack* aux = p->next;
        free(p);
        p = aux;
    }
    return p;
}

void freeStack(Stack* s){
    Stack* p = s;
     while(p!= NULL)
     {
         Stack* aux = p->next;
         free(p);
         p = aux;
     }
 }



Visited* createList(){
    return NULL;
}

Visited* appendToList(Visited* v, int value){
    Visited* new = (Visited*) malloc(sizeof(Visited));
    new->value = value;
    new->next = v;

    return new;
}

void unstacksNoVisitedNodes(Stack* s, Visited* v){
    Stack* p = v;
    while(p!= NULL){
        printf("%d ",p->value);
        p = p->next;
    }
}

void displayList(Visited* s){
    Visited* p = s;
    printf("Visited: ");
    while(p!= NULL)
    {
        printf("%d ",p->value);
        p = p->next;
    }
    printf("\n");
}

int isAllNodeVisited(Visited* v){
    Visited* p = v;
    int num=0;
    while(p!= NULL){
        num++;
        p=p->next;
    }

    return num == LEN;
}

int isNodeVisited(Visited* v, int value){
    Visited* p = v;

    while(p!= NULL){
        if(p->value == value){
            return 1;
        }
        p=p->next;
    }

    return 0;
}

void freeList(Visited* v){
    Visited* p = v;
    while(p!= NULL)
    {
        Visited* aux = p->next;
        free(p);
        p = aux;
    }
    free(p);
}


//DFS

void DFS(int **mat){

    int hasVisitedAllNodes = 0;

    Visited* visited = createList();
    Stack* stack = createStack();

    visited = appendToList(visited, 0);
    int index = 0;


    int column, row;
    int hasChildren;
    while(!hasVisitedAllNodes){
        hasChildren = 0;
        for(column = 0; column < LEN; column++)
        {
            int node = mat[row][column];
            if(node == 1){
                if(!isInStackOrVisitedList(stack, visited,column)){
                    stack = appendToStack(stack, column);
                    hasChildren = 1;
                }
            }
        }

        if(!isNodeVisited(visited, row)){
            visited = appendToList(visited, row);
        }
        if(!hasChildren){
            stack = popAll(stack);
            row = 0;
        }else{
            row = getLastNodeFromStack(stack);
        }

        if(isAllNodeVisited(visited)){
            break;
        }
    }


    hasVisitedAllNodes = 1;

    displayList(visited);
    freeStack(stack);
    freeList(visited);
}


int main()
{
    int copiamatriz[LEN][LEN] = {
        {0,1,0,0,1},
        {1,0,1,1,1},
        {0,1,0,1,0},
        {0,1,1,0,1},
        {1,1,0,1,0}};
    int **matriz = criaMatriz();

    for(int index = 0; index< LEN;index++){
        insereNaMatriz(matriz,copiamatriz[index], index);
    }
    DFS(matriz);
    //mostraMatriz(matriz);
    liberaMatriz(matriz);

    return 0;
}



/*
    v0 -> v1, v4
    v1 -> v0, v2, v3, v4
    v2 -> v1, v3
    v3 -> v1, v2,v4
    v4 -> v0, v1, v3

    s = 1, 4, 3, 2
    v = 0, 4, 3, 2

*/
