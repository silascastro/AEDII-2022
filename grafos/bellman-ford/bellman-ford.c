#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Edge {
    // This structure is equal to an edge. Edge contains two end points. These edges are directed edges so they
    //contain source and destination and some weight. These 3 are elements in this structure
    int source, destination, weight;
};

// a structure to represent a connected, directed and weighted graph
struct Graph {
    int V, E;            // V is number of vertices and E is number of edges
    struct Edge* edge;   // This structure contain another structure which we already created edge.
};

struct Graph* createGraph(int V, int E) {
    //Allocating space to structure graph
    struct Graph* graph = (struct Graph*) malloc( sizeof(struct Graph) );

    //assigning values to structure elements that taken form user.
    graph->V = V;
    graph->E = E;

    //Creating "Edge" type structures inside "Graph" structure, the number of edge type structures are equal to number of edges
    graph->edge = (struct Edge*) malloc( graph->E * sizeof( struct Edge ) );

    return graph;
}

void PrintSolution(int dist[], int n) { // This function prints the final solution
    printf("\nVertice\t\tDistancia do Vertice 0\n");
    int i;
    for (i = 0; i < n; ++i) {
        printf("%d \t\t\t\t %d\n", i, dist[i]);
    }
}

void BellmanFord(struct Graph* graph, int source) {
    int V = graph->V;
    int E = graph->E;
    int StoreDistance[V];
    int i,j;

    // Step 1: Initialize distances from src to all other
    // vertices as INFINITE
    // We assign source distance as 0(zero)
    for (i = 0; i < V; i++)
        StoreDistance[i] = INT_MAX;
    StoreDistance[source] = 0;

    // Step 2: Relax all edges |V| - 1 times. A simple
    // shortest path from src to any other vertex can have
    // at-most |V| - 1 edges
    for (i = 1; i <= V-1; i++) {

        for (j = 0; j < E; j++) {
            int u = graph->edge[j].source;
            int v = graph->edge[j].destination;
            int weight = graph->edge[j].weight;

            if (StoreDistance[u] != INT_MAX && StoreDistance[u] + weight < StoreDistance[v])
                StoreDistance[v] = StoreDistance[u] + weight;
        }
    }

    // Step 3: check for negative-weight cycles.  The above
    // step guarantees shortest distances if graph doesn't
    // contain negative weight cycle.  If we get a shorter
    // path, then there is a cycle.
    for (i = 0; i < E; i++) {
        int u = graph->edge[i].source;
        int v = graph->edge[i].destination;
        int weight = graph->edge[i].weight;

        if (StoreDistance[u] != INT_MAX && StoreDistance[u] + weight < StoreDistance[v]) {
            printf("\nThis graph contains negative edge cycle\n");
            return;
        }
    }
    PrintSolution(StoreDistance, V);
    return;
}

int main() {
    int V,E,S;  //V = no.of Vertices, E = no.of Edges, S is source vertex

{   printf("GRAFO 1");
    V = 5;
    E = 10;
    S = 0;
    struct Graph* graph = createGraph(V, E);

    //aresta 1
    graph->edge[0].source = 0;
    graph->edge[0].destination = 1;
    graph->edge[0].weight = 6;
    //aresta 2
    graph->edge[1].source = 0;
    graph->edge[1].destination = 2;
    graph->edge[1].weight = 7;
    //aresta 3
    graph->edge[2].source = 1;
    graph->edge[2].destination = 2;
    graph->edge[2].weight = 8;
    //aresta 4
    graph->edge[3].source = 1;
    graph->edge[3].destination = 3;
    graph->edge[3].weight = 5;
    //aresta 5
    graph->edge[4].source = 1;
    graph->edge[4].destination = 4;
    graph->edge[4].weight = -4;
    //aresta 6
    graph->edge[5].source = 2;
    graph->edge[5].destination = 3;
    graph->edge[5].weight = -3;
    //aresta 7
    graph->edge[6].source = 2;
    graph->edge[6].destination = 4;
    graph->edge[6].weight = 9;
    //aresta 8
    graph->edge[7].source = 3;
    graph->edge[7].destination = 1;
    graph->edge[7].weight = -2;
    //aresta 9
    graph->edge[8].source = 4;
    graph->edge[8].destination = 0;
    graph->edge[8].weight = 2;
    //aresta 10
    graph->edge[9].source = 4;
    graph->edge[9].destination = 3;
    graph->edge[9].weight = 7;

    BellmanFord(graph, S);
    //passing created graph and source vertex to BellmanFord Algorithm function
}

{   printf("\nGRAFO 2");
    V = 5;
    E = 6;
    S = 0;
    struct Graph* graph1 = createGraph(V, E);
    //aresta 1
    graph1->edge[0].source = 0;
    graph1->edge[0].destination = 1;
    graph1->edge[0].weight = 2;
    //aresta 2
    graph1->edge[1].source = 0;
    graph1->edge[1].destination = 2;
    graph1->edge[1].weight = 1;
    //aresta 3
    graph1->edge[2].source = 1;
    graph1->edge[2].destination = 3;
    graph1->edge[2].weight = 3;
    //aresta 4
    graph1->edge[3].source = 2;
    graph1->edge[3].destination = 4;
    graph1->edge[3].weight = 1;
    //aresta 5
    graph1->edge[4].source = 3;
    graph1->edge[4].destination = 4;
    graph1->edge[4].weight = -6;
    //aresta 6
    graph1->edge[5].source = 4;
    graph1->edge[5].destination = 2;
    graph1->edge[5].weight = -1;

    BellmanFord(graph1, S);
}

 {  printf("\nGRAFO 3");
    V = 6;
    E = 10;
    S = 0;
    struct Graph* graph3 = createGraph(V, E);

    //aresta 1
    graph3->edge[0].source = 0;
    graph3->edge[0].destination = 1;
    graph3->edge[0].weight = 1;
    //aresta 2
    graph3->edge[1].source = 0;
    graph3->edge[1].destination = 2;
    graph3->edge[1].weight = 3;
    //aresta 3
    graph3->edge[2].source = 1;
    graph3->edge[2].destination = 2;
    graph3->edge[2].weight = 1;
    //aresta 4
    graph3->edge[3].source = 1;
    graph3->edge[3].destination = 3;
    graph3->edge[3].weight = 2;
    //aresta 5
    graph3->edge[4].source = 1;
    graph3->edge[4].destination = 4;
    graph3->edge[4].weight = 3;
    //aresta 6
    graph3->edge[5].source = 2;
    graph3->edge[5].destination = 4;
    graph3->edge[5].weight = 2;
    //aresta 7
    graph3->edge[6].source = 3;
    graph3->edge[6].destination = 4;
    graph3->edge[6].weight = -3;
    //aresta 8
    graph3->edge[7].source = 4;
    graph3->edge[7].destination = 3;
    graph3->edge[7].weight = -1;
    //aresta 9
    graph3->edge[8].source = 5;
    graph3->edge[8].destination = 4;
    graph3->edge[8].weight = 3;
    //aresta 10
    graph3->edge[9].source = 4;
    graph3->edge[9].destination = 5;
    graph3->edge[9].weight = 2;

    BellmanFord(graph3, S);
}

 { printf("\nGRAFO 4");
    V = 6;
    E = 9;
    S = 0;
    struct Graph* graph4 = createGraph(V, E);

    //aresta 1
    graph4->edge[0].source = 0;
    graph4->edge[0].destination = 1;
    graph4->edge[0].weight = 5;
    //aresta 2
    graph4->edge[1].source = 0;
    graph4->edge[1].destination = 2;
    graph4->edge[1].weight = -2;
    //aresta 3
    graph4->edge[2].source = 1;
    graph4->edge[2].destination = 3;
    graph4->edge[2].weight = 1;
    //aresta 4
    graph4->edge[3].source = 2;
    graph4->edge[3].destination = 1;
    graph4->edge[3].weight = 2;
    //aresta 5
    graph4->edge[4].source = 2;
    graph4->edge[4].destination = 4;
    graph4->edge[4].weight = 4;
    //aresta 6
    graph4->edge[5].source = 2;
    graph4->edge[5].destination = 3;
    graph4->edge[5].weight = 4;
    //aresta 7
    graph4->edge[6].source = 3;
    graph4->edge[6].destination = 4;
    graph4->edge[6].weight = -1;
    //aresta 8
    graph4->edge[7].source = 3;
    graph4->edge[7].destination = 5;
    graph4->edge[7].weight = 3;
    //aresta 9
    graph4->edge[8].source = 4;
    graph4->edge[8].destination = 5;
    graph4->edge[8].weight = 1;

    BellmanFord(graph4, S);
}

    return 0;
}