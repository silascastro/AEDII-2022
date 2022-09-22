
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

typedef struct queue{
    int value;
    struct queue* next;
}Queue;

typedef struct visited{
    int value;
    struct visited* next;
}Visited;
