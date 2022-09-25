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