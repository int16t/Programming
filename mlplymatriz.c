#include <stdio.h>

void multiplyMatriz(int *matriz1, int *matriz2){
    int i, j, k;
    int result[3][3] = {0}; // Inicializa a matriz resultado com zeros

    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            for(k = 0; k < 3; k++){
                result[i][j] += (*(matriz1 + i*3 + k)) * (*(matriz2 + k*3 + j));
            }
        }
    }

    printf("Resultado da multiplicação de matrizes:\n");
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
}

int main(){

    const int matriz1[3][3]= {1,2,3,4,5,6,7,8,9};
    const int matriz2[3][3]= {1,2,3,4,5,6,7,8,9};
    
    multiplyMatriz((int *)matriz1, (int *)matriz2);

    return 0;
}