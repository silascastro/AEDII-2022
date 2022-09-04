#include <stdio.h>
#include <stdlib.h>

#define LEN 5


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
        printf("vertice %d: ",linha);
        for(int coluna = 0; coluna< LEN; coluna++){
            printf("%d ", mat[linha][coluna]);
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
    int copiamatriz[LEN][LEN] = {{0,1,0,0,1},{1,0,1,1,1},{0,1,0,1,0},{0,1,1,0,1},{1,1,0,1,0}};
    int **matriz = criaMatriz();

    for(int index = 0; index< LEN;index++){
        insereNaMatriz(matriz,copiamatriz[index], index);
    }

    mostraMatriz(matriz);
    liberaMatriz(matriz);

    return 0;
}




