#include <iostream>

using namespace std;


typedef struct adjacencia{
    int vertice;
    int peso;
    struct adjacencia *prox;
}ADJACENCIA;

typedef struct vertice{
    ADJACENCIA *cad;

}VERTICE;

typedef struct grafo{
    int vertices;
    int arestas;
    VERTICE *vert;
}GRAFO;

GRAFO* criaGrafo(int v){
    GRAFO* g = new (GRAFO);
    g->vertices = v;
    g->arestas = 0;
    g->vert = new VERTICE[v];

    for(int i=0; i<v;i++)
        g->vert[i].cad = NULL;

    return g;
}

ADJACENCIA* criaAdj(int v, int peso){
    ADJACENCIA* temp = new (ADJACENCIA);
    temp->vertice = v;
    temp->peso = peso;
    temp->prox = NULL;
    return (temp);
}

bool criaAresta(GRAFO* g, int verticeInicial, int verticeFinal, int p){
    if(!g) return false;

    if((verticeFinal < 0) || verticeFinal >= g->vertices)
    return false;

    if((verticeInicial < 0) || verticeInicial >= g->vertices)
    return false;

    ADJACENCIA* novo = criaAdj(verticeFinal, p);
    novo->prox = g->vert[verticeInicial].cad;
    g->vert[verticeInicial].cad = novo;
    g->arestas++;
    return true;
}


void imprime(GRAFO* g){
    cout << "Vertices: " << g->vertices << ". Arestas: " << g->arestas << endl;

    for(int i=0; i<g->vertices; i++){
        cout << "v" << i+1 << ": ";
        ADJACENCIA* ad = g->vert[i].cad;
        while(ad){
            cout << "v" << ad->vertice+1 << "(" << ad->peso << ")";
            ad = ad->prox;
        }

        cout << endl;
    }

}

int main()
{
    GRAFO* g = criaGrafo(6);
    criaAresta(g,0,1,10);
    criaAresta(g,0,3,3);
    criaAresta(g,1,4,4);
    criaAresta(g,3,1,15);
    criaAresta(g,4,3,6);
    criaAresta(g,2,4,7);
    criaAresta(g,2,5,18);
    criaAresta(g,5,5,9);
    imprime(g);


    return 0;
}


