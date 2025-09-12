#include <stdio.h>

int sumVetor(int *vetor, int tamanho){
    int i, sum = 0;
    for(i = 0; i < tamanho; i++){
        sum += vetor[i];
    }
    return sum;
}


int main(){

    int vetor1[] = {1, 2, 3, 4, 5};
    int vetor2[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    int soma1 = sumVetor(vetor1, 5);
    int soma2 = sumVetor(vetor2, 10);

    printf("Soma do vetor1: %d\n", soma1);
    printf("Soma do vetor2: %d\n", soma2);

    return 0;
}