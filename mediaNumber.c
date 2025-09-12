#include <stdio.h>
#include <stdlib.h>



void read(char *filename, int tamanho){
    FILE * file = fopen(filename, "rb");
    if(file == NULL){
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    fread(file, sizeof(int), tamanho, file);

    printf("Conteudo do arquivo:\n");
    for(int i = 0; i < tamanho; i++){
        printf("%d ", file[i]);
    }
    printf("\n");

    fclose(file);
}


int main(){
    int tamanho;
    printf("Digite o tamanho do arquivo em bytes: ");
    scanf("%d", &tamanho);
    read("randomNumbers.bin", tamanho);
    

    return 0;
}