#include <stdio.h>
#include <stdlib.h>

#include "data.h"

#define LEN 5

Graph* createGraph(){
    Graph *g = (Graph*) malloc(sizeof(Graph));
    if(g!= NULL){
        g->list = (AdjList*) malloc(sizeof(AdjList*)*LEN);
        for(int i =0; i < LEN; i++){
            g->list[0].head = NULL;
        }
    }
    return g;
}

Node* createNewNode(int dest){
    Node* new = (Node*) malloc(sizeof(Node));
    new->v = dest;
    Node* next = NULL;


    return new;
}

Graph* addEdgeToUndirectGraph(Graph* g, int src, int dest){
    Node* p = NULL;
    Node* new_node = createNewNode(dest);

    if(g->list[src].head == NULL){
        new_node->next = g->list[src].head;
        g->list[src].head = new_node;
    }else{
        p = g->list[src].head;
        while(p->next != NULL){
            p = p->next;
        }
        p->next = new_node;
    }

    new_node = createNewNode(src);
    if(g->list[dest].head == NULL){
        new_node->next = g->list[dest].head;
        g->list[dest].head = new_node;
    }else{
        p = g->list[dest].head;
        while(p->next != NULL){
            p = p->next;
        }
        p->next = new_node;
    }


    return g;

}

void displayGraph(Graph* g){
    if(g!= NULL){
       for(int index = 0; index < LEN; index++){
            Node* adjList = g->list[index].head;

            while (adjList!= NULL)
            {
                printf("%d ",adjList->v);
                Node* p = adjList;
                adjList = p->next;

            }
            printf("\n");
       }
    }
}

void freeGraph(Graph* g){
    if(g!= NULL){
       for(int index = 0; index < LEN; index++){
            Node* adjList = g->list[index].head;

            while (adjList!= NULL)
            {
                Node* p = adjList;
                adjList = p->next;
                free(p);
            }
       }
       free(g->list);
       free(g);
    }
}

// pilha | busca em profundidade

Stack* createQueue(){
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
    free(p);
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

Stack* addNodesToStack(Graph* g, Stack* p, Visited* v){


    return;
}

void DFS(Graph* g){

    int hasVisitedAllNodes = 0;

    Visited* visited = createList();
    Stack* stack = createQueue();

    visited = appendToList(visited, 0);
    int index = 0;

    while(!hasVisitedAllNodes){

        Node* adj = g->list[index].head;
        int hasChildren = 0;
        while(adj!= NULL){
            // printf("%d ",adj->v);

            if(!isNodeInStack(stack,adj->v) && !isNodeVisited(visited,adj->v)){
                stack = appendToStack(stack,adj->v);
                hasChildren = 1;
            }
            adj = adj->next;
        }

        if(!isNodeVisited(visited, index)){
            visited = appendToList(visited, index);
        }

        if(!hasChildren){
            stack = popAll(stack);
            index = 0;
        }else{
            index = getLastNodeFromStack(stack);
        }


        if(isAllNodeVisited(visited)){
            hasVisitedAllNodes = 1;
        }


    }

    displayList(visited);
    freeStack(stack);
    freeList(visited);
}



int main(int argc, char const *argv[])
{
    Graph* g;
    g = createGraph();
    g = addEdgeToUndirectGraph(g,0,1);
    g = addEdgeToUndirectGraph(g,0,4);
    g = addEdgeToUndirectGraph(g,1,4);
    g = addEdgeToUndirectGraph(g,1,3);
    g = addEdgeToUndirectGraph(g,1,2);
    g = addEdgeToUndirectGraph(g,2,3);
    g = addEdgeToUndirectGraph(g,3,4);
    DFS(g);
    freeGraph(g);
    /* code */
    return 0;
}