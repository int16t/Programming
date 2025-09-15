#include <stdlib.h> 
#include <stdio.h>  
#include <time.h>  
 


void rdmNumber(int lista[], int tamanho){
    static int initialized = 0;
    if (!initialized) {
    srand(time(NULL));
    initialized = 1;
    }

    for (int i = 0; i < tamanho; i++){
        int max;
        printf("Digite o valor maximo para o numero %d: \n", i + 1);
        scanf("%d", &max);
        lista[i] = rand() % max + 1;
        printf("Numero aleatorio: %d\n", lista[i]);
    }
}

void writeRandom(int lista[], int tamanho, const char *filename){
    FILE *arquivo = fopen(filename, "wb");
    if (arquivo == NULL){
        printf("Error opening file!\n");
        return;
    }
    fwrite(lista, sizeof(int), tamanho, arquivo);
    fclose(arquivo);
}

void readRandom(int lista[], int tamanho, const char *filename){
    FILE *arquivo = fopen(filename, "rb");
    if (arquivo == NULL){
        printf("Error opening file!\n");
        return;
    }

    fread(lista, sizeof(int), tamanho, arquivo);
    fclose(arquivo);
    printf("Numeros lidos do arquivo:\n");
    for (int i = 0; i < tamanho; i++){
        if (i == tamanho - 1){
            printf("%d.\n", lista[i]);
        }
        else{
            printf("%d, ", lista[i]);
        }
    }
    printf("Numeros lidos com sucesso!\n");
}

int main(){
    int lista[5];
    int tamanho = 5;
    
    //Gerar numeros aleatorios
    rdmNumber(lista, tamanho);
    
    //Escrever numeros em arquivo binario
    writeRandom(lista,tamanho, "randomNumbers.bin");

    //Mostrar numeros sorteados
    printf("Os numeros sorteados foram: \n");
    for(int j = 0; j < tamanho; j++){
        if (j == tamanho - 1){
            printf("%d.\n", lista[j]);
        }
        else {
            printf("%d, ", lista[j]);
        }
    }

    //Ler numeros do arquivo binario
    readRandom(lista, tamanho, "randomNumbers.bin");

    return 0;
}