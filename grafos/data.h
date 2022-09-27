
typedef struct node
{
    int v;
    int weight;
    int visited;
    int dist;
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

typedef struct djikstra{
    int v;
    double dist;
    int prev;
    int visited;
    struct djikstra* next;
}Djikstra;

typedef struct queue{
    int value;
    struct queue* next;
}Queue;

typedef struct visited{
    int value;
    struct visited* next;
}Visited;
