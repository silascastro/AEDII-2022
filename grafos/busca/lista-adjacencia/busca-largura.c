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
            printf("v%d: ",index);
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

void BFS(Graph* g){
    int isAllNodesVisited = 0, index = 0;
    Queue* q = createQueue();
    Visited* v = createList();

    v = appendToList(v, 0);
    while(!isAllNodesVisited){
        Node* adj = g->list[index].head;

        while(adj != NULL){
            if(!isInQueueOrVisitedList(q, v, adj->v)){
                q = appendToQueue(q, adj->v);
            }

            adj = adj->next;
        }

        if(!isNodeVisited(v, index)){
            v = appendToList(v, index);

        }


        if(q != NULL){
            index = getFirstNodeFromQueue(q);
            q = removeFromQueue(q);
        }

        if(getQtyOfNodeVisited(v) == LEN){
            isAllNodesVisited = 1;
        }

    }

    displayList(v);
    freeVisitedList(v);
    freeQueue(q);
}




int main(int argc, char const *argv[])
{
    Graph* g = createGraph();
    g = addEdgeToUndirectGraph(g,0,1);
    g = addEdgeToUndirectGraph(g,0,4);
    g = addEdgeToUndirectGraph(g,1,4);
    g = addEdgeToUndirectGraph(g,1,3);
    g = addEdgeToUndirectGraph(g,1,2);
    g = addEdgeToUndirectGraph(g,2,3);
    g = addEdgeToUndirectGraph(g,3,4);

     BFS(g);


    freeGraph(g);

    return 0;
}
