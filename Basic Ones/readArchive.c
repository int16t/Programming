#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

void linha(int tamanho_linha){
    for(int i = 0; i < tamanho_linha; i++){
        printf("-");
    }
    printf("\n");
}
void cabecalho(const char *nome, int tamanho_linha){
    linha(tamanho_linha);
    int tamanho_nome = strlen(nome);
    int espacos = (tamanho_linha - tamanho_nome) / 2;
    for(int i = 0; i < espacos; i++){
        printf(" ");
    }
    printf("%s\n", nome);
    linha(tamanho_linha);
    sleep(1);

}


char *nome(){
    char temp[30];
    printf("Name of file to read: ");
    scanf("%29s", temp);

    char *arquivo = malloc(strlen(temp) + 1);
    strcpy(arquivo, temp);

    return arquivo;
}

int readArchive(const char *arquivo, char *buffer, int bufferSize){
    sleep(1);
    int fd = open(arquivo, O_RDONLY);
    if(fd == -1){
        perror("Error to open the file");
        return -1;
    }
    int bytesRead = read(fd, buffer, bufferSize - 1);
    if(bytesRead == -1){
        perror("Error to open archive");
        close(fd);
        return -1; // Erro na leitura
    }
    buffer[bytesRead] = '\0';
    close(fd);

    return bytesRead; // Retorna o número de bytes lidos
}

int rows(int lidos, const char *buffer){
    int count = 0;
    for(int i = 0; i < lidos; i++){
        if(buffer[i] == '\n'){
            count++;
        }
    }
    return count;
}

int words(int lidos, char *buffer){
    int count = 0;
    for (int i = 0; i < lidos; i++){
        if(buffer[i] == ' ' || buffer[i] == '\n' || buffer[i] == '\t'){
            count++;
        }
    }
    
    return count;
}


int main(){
    
    
    cabecalho("READ ARCHIVE PROGRAM", 30);
    char *arquivo = nome();
    cabecalho("READ INFORMATIONS", 30);
    char buffer[1024];
    
    int bytes = readArchive(arquivo, buffer, sizeof(buffer));
    
    printf("%s\n", buffer);
    
    cabecalho("STATISTICS", 30);
    int rows_ammount = rows(bytes, buffer);
    printf("Number of rows: %d\n", rows_ammount);
    printf("Number of characters (including newlines): %d\n", bytes);
    int words_ammount = words(bytes, buffer);
    printf("Number of words: %d\n", words_ammount);

    free(arquivo);
    return 0;
}