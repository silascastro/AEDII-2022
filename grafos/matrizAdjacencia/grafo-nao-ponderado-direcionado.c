#include <stdio.h>
#include <stdlib.h>

#define LEN 6


int** criaMatriz(){
    int linha;
    int **mat = (int**) malloc(LEN*sizeof(int*));
    for(linha =0; linha< LEN; linha++){
        mat[linha] = (int*) malloc(LEN*sizeof(int));
    }

    return mat;
}

void insereNaMatriz(int **mat, int* valores, int indexLinha){
    int coluna;

    for(coluna = 0; coluna< LEN; coluna++){
        mat[indexLinha][coluna] = valores[coluna];
    }
}

void mostraMatriz(int **mat){
    int coluna, linha;
    for(linha =0; linha<LEN; linha++){
        printf("vertice %d =>",linha+1);
        for(int coluna = 0; coluna< LEN; coluna++){
            if(mat[linha][coluna] == 1){
                printf("v%d ",coluna+1);
            }

        }
        printf("\n");
    }
}

//desaloca
void liberaMatriz(int **mat){
    for(int linha=0; linha<LEN; linha++){
        free(mat[linha]);
    }
    free(mat);
}


int main()
{
    int copiamatriz[LEN][LEN] = {
        {0,1,0,1,0,0},
        {0,0,0,0,1,0},
        {0,0,0,0,1,1},
        {0,1,0,0,0,0},
        {0,0,0,1,0,0},
        {0,0,0,0,0,1}
        };
    int **matriz = criaMatriz();

    for(int index = 0; index< LEN;index++){
        insereNaMatriz(matriz,copiamatriz[index], index);
    }

    mostraMatriz(matriz);
    liberaMatriz(matriz);

    return 0;
}




