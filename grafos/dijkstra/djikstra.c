#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "../data.h"

#define LEN 4

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
    new->next = NULL;
    new->weight = NULL;
    new->visited = 0;
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

Graph* addEdgeToDirectGraph(Graph* g, int src, int dest, int weight){
    Node* p = NULL;
    Node* new_node = createNewNode(dest);

    if(g->list[src].head == NULL){
        new_node->next = g->list[src].head;
        if(weight != NULL && weight > 0){
            new_node->weight = weight;
        }
        g->list[src].head = new_node;

    }else{
        p = g->list[src].head;
        while(p->next != NULL){
            p = p->next;
        }
        if(weight != NULL && weight > 0){
            new_node->weight = weight;
        }
        p->next = new_node;


    }




    return g;

}

void displayGraph(Graph* g){
    if(g!= NULL){
       for(int index = 0; index < LEN; index++){
            printf("v%d: ",index);
            Node* adjList = g->list[index].head;

            while (adjList!= NULL)
            {
                printf("%d(%d)",adjList->v, adjList->weight);
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

Djikstra* createDjikstraList(){
    return NULL;
}

Djikstra* appendToDjikstraList(Djikstra* d, int v, double dist, int prev, int visisted){
    Djikstra* new = (Djikstra*) malloc(sizeof(Djikstra));
    new->dist = dist;
    new->prev = prev;
    new->v = v;
    new->visited = visisted;
    new->next = d;
    return new;
}

Djikstra* displayDjikstraList(Djikstra* d){
    Djikstra* p = d;
    while(p!= NULL){
        printf("previous: %d, distance: %d, vertice: %d, visited: %d\n",p->prev, (p->dist == INFINITY), p->v, p->visited);
        p = p->next;
    }
}

void freeDjikstraList(Djikstra* d){
    Djikstra* p = d;
    while(p!= NULL){
       Djikstra* aux = p->next;
       free(p);
        p = aux;
    }
}

void djikstra(Graph* g){

    Djikstra* d = createDjikstraList();


    d = appendToDjikstraList(d, 0, 0,0, 1);
    for(int index = 1; index<LEN; index++){
        d = appendToDjikstraList(d, index,INFINITY,NULL,0);

    }

    displayDjikstraList(d);
    freeDjikstraList(d);

    /*
    if(g!= NULL){
       for(int index = 0; index < LEN; index++){
            printf("v%d: ",index);
            Node* adjList = g->list[index].head;

            while (adjList!= NULL)
            {
                printf("%d(%d) tem dist %d",adjList->v, adjList->weight, adjList->dist != NULL);
                Node* p = adjList;
                adjList = p->next;

            }
            printf("\n");
       }
    }*/


}


int main(int argc, char const *argv[])
{
    Graph* g = createGraph();
    g = addEdgeToDirectGraph(g,0,1, 5);
    g = addEdgeToDirectGraph(g,1,0, 50);
    g = addEdgeToDirectGraph(g,1,2, 15);
    g = addEdgeToDirectGraph(g,1,3, 5);
    g = addEdgeToDirectGraph(g,2,0, 30);
    g = addEdgeToDirectGraph(g,2,3, 15);
    g = addEdgeToDirectGraph(g,3,2, 5);
    g = addEdgeToDirectGraph(g,3,0, 15);
    //displayGraph(g);

    djikstra(g);
    freeGraph(g);
    return 0;
}

/*

    v0 -> v1
    v1 -> v0
    v1 -> v2
    v1 -> v3
    v2 -> v0
    v2 -> v3
    v3 -> v2
    v3 -> v0
*/