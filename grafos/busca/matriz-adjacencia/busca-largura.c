#include <stdio.h>
#include <stdlib.h>
#include "data.h"

#define LEN 5

int** createMatriz(){
    int row;
    int **mat = (int**) malloc(LEN*sizeof(int*));
    for(row =0; row< LEN; row++){
        mat[row] = (int*) malloc(LEN*sizeof(int));
    }

    return mat;
}

void appendToMatriz(int **mat, int* values, int index){
    int column;

    for(column= 0; column< LEN; column++){
        mat[index][column] = values[column];
    }
}

void displayMatriz(int **mat){
    int column, row;
    for(row =0; row<LEN; row++){
        printf("vertice %d =>",row+1);
        for(int column = 0; column< LEN; column++){
            if(mat[row][column] == 1){
                printf("v%d ",column+1);
            }

        }
        printf("\n");
    }
}

//desaloca
void freeMatriz(int **mat){
    for(int row=0; row<LEN; row++){
        free(mat[row]);
    }
    free(mat);
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

int getQtyOfNodeVisited(Visited* v){
    Visited* p = v;
    int num=0;
    while(p!= NULL){
        num++;
        p=p->next;
    }

    return num;
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

void freeVisitedList(Visited* v){
    Visited* p = v;
    while(p!= NULL)
    {
        Visited* aux = p->next;
        free(p);
        p = aux;
    }
    free(p);
}


Queue* createQueue(){
    return NULL;
}

Queue* appendToQueue(Queue* q,int value){
    Queue* new = (Queue*) malloc(sizeof(Queue));
    new->value = value;
    new->next = q;

    return new;
}

int isInQueueOrVisitedList(Queue* q,Visited* v, int value){
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

int getFirstNodeFromQueue(Queue* q){
    if(q != NULL){
        while(q!= NULL){
            if(q->next == NULL){
                return q->value;
            }
            q = q->next;
        }
    }else{
         return NULL;
    }
}

Queue* removeFromQueue(Queue* q){
    Queue* p = q;
    Queue* temp;
    if(p->next == NULL){
        free(p);
        p = NULL;
        return p;
    }else{
        while(p!= NULL){
            if(p->next->next == NULL){
                temp = p->next;
                free(temp);
                p->next = NULL;
                break;
            }
            p = p->next;
        }
    }

    return q;
}

void freeQueue(Queue* q){
    Queue* p = q;

     while(p!= NULL){
         Queue* aux = p->next;
         free(p);
         p = aux;
     }

     free(p);
}

void displayQueue(Queue* q){
    Queue* p = q;
    while(p!= NULL){
        printf("%d ",p->value);
        p = p->next;
    }
}




//BFS

void BFS(int **mat){
    int hasVisitedAllNodes = 0, index = 0;
    Queue* queue = createQueue();
    Visited* visisted = createList();

    visisted = appendToList(visisted, 0);
    int row = 0, column;
    while(!hasVisitedAllNodes){

         for(column = 0; column < LEN; column++){
             int node = mat[row][column];
             if(node == 1){
                 if(!isInQueueOrVisitedList(queue,visisted,column)){
                     queue = appendToQueue(queue, column);
                 }
             }
         }

        if(!isNodeVisited(visisted, row)){
            visisted = appendToList(visisted, row);

        }

        if(queue != NULL){
            row = getFirstNodeFromQueue(queue);
            queue = removeFromQueue(queue);
        }

        if(getQtyOfNodeVisited(visisted) == LEN){
            hasVisitedAllNodes = 1;
        }
    }

    displayQueue(queue);
    displayList(visisted);
    freeVisitedList(visisted);
    freeQueue(queue);
}




int main(int argc, char const *argv[])
{


    int copy[LEN][LEN] = {
        {0,1,0,0,1},
        {1,0,1,1,1},
        {0,1,0,1,0},
        {0,1,1,0,1},
        {1,1,0,1,0}};
    int **mat = createMatriz();
    for(int index = 0; index < LEN; index++){
        appendToMatriz(mat, copy[index],index);
    }
    BFS(mat);
    // displayMatriz(mat);
    freeMatriz(mat);

    return 0;
}
