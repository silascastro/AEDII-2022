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

// pilha
typedef struct stack{
    int value;
    struct stack* next;
}Stack;

typedef struct visited{
    int value;
    struct stack* next;
}Visited;

//no arvore
typedef struct noTree{
    int value;
    struct noTree* left;
    struct noTree* right;
}NoTree;


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

void displayStack(Stack* s){
    Stack* p = s;
    printf("STack: ");
    while(p!= NULL)
    {
        printf("%d ",p->value);
        p = p->next;
    }
    printf("\n");
}

Stack* StashAllVisited(Stack* s, Visited* v){
    Stack* p = s;
    if(p!= NULL){

        Stack* aux = p->next;
        free(p);
        p = aux;
    }
    return p;
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

void searchForChildrenNodes(Graph* g, Stack* p, Visited* v){



}

void DFS(Graph* g){
    Visited* visited = createList();
    Stack* stack = createStack();

    Node* adj = g->list[0].head;
    visited = appendToList(visited, 0);
    while(adj != NULL){
        if(!isNodeInStack(stack, adj->v)){
             stack = appendToStack(stack, adj->v);
        }
        adj = adj->next;
    }

    // searchForChildrenNodes(g, stack, visited);

    int hasVisitedNodes = 1;

    while(hasVisitedNodes){
        int s = getLastNodeFromStack(stack);

        Node* n = g->list[s].head;
        while(n != NULL){

            if(!isNodeVisited(visited, n->v) && !isNodeInStack(stack,n->v)){
                // visita o nó não visitado
                hasVisitedNodes = 1;
                stack = appendToStack(stack,n->v);
            }else{
                    hasVisitedNodes = 0;


            }
            n = n->next;
        }
        visited = appendToList(visited,s);
    }


    displayList(visited);
    displayStack(stack);
    freeStack(stack);
    freeList(visited);
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
    g = createEdge(g,3,2);
    g = createEdge(g,4,0);
    g = createEdge(g,4,1);
    g = createEdge(g,4,3);
    DFS(g);

    freeGraph(g);
    /* code */
    return 0;
}

