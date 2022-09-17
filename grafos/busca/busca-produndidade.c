#include <stdio.h>
#include <stdlib.h>


#define LEN 5

typedef struct node
{
    int v;
    int weight;
    struct no* next;
}Node;

typedef struct adjList{
    Node* head;
}AdjList;

typedef struct graph{
    int n;
    AdjList* list;
}Graph;

typedef struct stack{
    int value;
    struct stack* next;
}Stack;


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

Graph* createEdge(Graph* g, int node, int dest){
    Node* p = NULL;
    Node* new_node = createNewNode(dest);

    if(g->list[node].head == NULL){
        new_node->next = g->list[node].head;
        g->list[node].head = new_node;
    }else{
        p = g->list[node].head;
        while(p->next != NULL){
            p = p->next;
        }
        p->next = new_node;
    }

    return g;

}

AdjList* searchOnGraph(Graph* g, int index){
    Node* p = g->list;

    Node* adjList = g->list[index].head;
    return adjList;

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

Stack* createStack(){
    return NULL;
}

Stack* addNodeToStack(Stack* s, int value){
    Stack* new = (Stack*) malloc(sizeof(Stack));
    new->value = value;
    new->next = s;
}

void displayStack(Stack* s){
    Stack* p = s;
    while(p!= NULL)
    {
        printf("%d\n",p->value);
        p = p->next;
    }

}

Stack* pop(Stack* s){
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

void DFS(Graph* g){
    Stack *p;
    int visited[LEN], visitedIndex = 0;
    p = createStack();

    // p = addNodeToStack(p, 2);
    // p = pop(p);
    // displayStack(p);
    // freeStack(p);


    for(int i = 0.; i<LEN; i++){
        Node* adj = searchOnGraph(g, i);
        printf("%d ",adj->v+1);
        printf("\n");
    }

}



int main(int argc, char const *argv[])
{
    Graph* g;
    g = createGraph(LEN);
    g = createEdge(g,0,1);
    g = createEdge(g,0,4);
    g = createEdge(g,1,0);
    g = createEdge(g,1,4);
    g = createEdge(g,1,3);
    g = createEdge(g,1,2);
    g = createEdge(g,2,1);
    g = createEdge(g,2,3);
    g = createEdge(g,3,1);
    g = createEdge(g,3,4);
    g = createEdge(g,4,0);
    g = createEdge(g,4,1);
    g = createEdge(g,4,3);
    DFS(g);
    freeGraph(g);
    /* code */
    return 0;
}


/*
    v1 -> 2, 5
    v2 -> 1, 5, 4, 3
    v3 -> 2, 4
    v4 -> 2, 5
    v5 -> 1, 2, 4
*/