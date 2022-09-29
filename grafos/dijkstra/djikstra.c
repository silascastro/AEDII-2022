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

Node* getNodeWithLowestWeightFromAdj(Graph* g, int index){
    Node* adj = g->list[index].head;
    Node* lowestAdj;

    int lowestWeight = adj->weight;
    while(adj!= NULL){
        if(adj->weight<=lowestWeight){
            lowestAdj = adj;
        }
        adj= adj->next;
    }

    return lowestAdj;
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
        printf("previous: %d, distance: %lf, vertice: %d, visited: %d\n", p->prev, p->dist, p->v, p->visited);
        p = p->next;
    }
}

int isNodeVisitedInDjikstraList(Djikstra* d, int value){
    Djikstra* p = d;
    int visited = 0;
    while(p!= NULL){

        if(p->v == value){
            visited = p->visited;
        }

        p = p->next;
    }

    return visited;
}

Djikstra* getNodeFromDjikstraList(Djikstra* d, int v){
    Djikstra *p = d;

    while(p != NULL){
        if(p->v == v){
            return p;
        }
        p = p->next;
    }

    return NULL;
}

void setVisitedStatusInDjiskstraList(Djikstra* d, int v){
    Djikstra *p = d;

    while(p != NULL){
        if(p->v == v){
            p->visited = 1;
            break;
        }
        p = p->next;
    }


}

int isAllNodesVisited(Djikstra* d){
    Djikstra* p = d;
    int isAllNodesVisited = 1;
    while(p!= NULL){
        if(!p->visited){
            isAllNodesVisited = 0;
            break;
        }
        p = p->next;
    }

    return isAllNodesVisited;
}

int getFirstNodeNotVisitedWithLowerWeight(Djikstra* d){
    Djikstra* p = d;

    int node = p->v;
    double lowestDist = p->dist;

    while(p!= NULL){

        if((!p->visited)){
            lowestDist = p->dist;
            node = p->v;
        }
        p = p->next;
    }
    return node;
}

Djikstra* initDjikstraList(Djikstra* d){
    d = appendToDjikstraList(d, 0, 0,0, 1);

    for(int index = 1; index<LEN; index++){
        d = appendToDjikstraList(d, index,INFINITY,0,0);
    }

    return d;
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
    d = initDjikstraList(d);

    int allNodeshavebeenVisited = 0;
    Djikstra* p = d;
    int index = 0;

    while(!isAllNodesVisited(d)){
        Node* adj = g->list[index].head;
        Djikstra* djikstraNode = getNodeFromDjikstraList(d, index), *djikstraEdge;

        setVisitedStatusInDjiskstraList(d, index);

        while(adj != NULL){

            djikstraEdge = getNodeFromDjikstraList(d, adj->v);

            if(!djikstraEdge->visited &&
            ((djikstraNode->dist + adj->weight) < djikstraEdge->dist))
            {
                djikstraEdge->dist =  djikstraNode->dist+adj->weight;
                djikstraEdge->prev = index;

            }
            adj = adj->next;
        }



        index = getFirstNodeNotVisitedWithLowerWeight(d);
    }
    displayDjikstraList(d);

    freeDjikstraList(d);
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