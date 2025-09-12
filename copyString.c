#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* copyString(char* origem) {
    int i = 0;
    char* destino = malloc(strlen(origem) + 1);
    if (!destino) return NULL;
    while (origem[i] != '\0') {
        destino[i] = origem[i];
        i++;
    }
    destino[i] = '\0';
    return destino;
    }


int main() {
    char *origem = "Teste de copia";
    char *destino = copyString(origem);

    if (destino){
        printf("%s\n", destino);
        free(destino);
    }
    return 0;
}