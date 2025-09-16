#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(){

    char msg[100];
    char buffer[100];
    int fd[2];

    printf("Digite uma mensagem para seu filho:");
    if (fgets(msg, sizeof(msg), stdin) == NULL) {
        perror("Erro ao ler a mensagem");
        exit(EXIT_FAILURE);
    }

    msg[strcspn(msg, "\n")] = 0; // remove a quebra de linha no final da string 

    if (pipe(fd) == -1){
        perror("Falha ao criar pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid < 0){
        perror("Falha ao criar processo filho");
        exit(EXIT_FAILURE);
    }

    if (pid > 0){
        close(fd[0]); // pai fecha o pipe de leitura
        if (write(fd[1], msg, strlen(msg) + 1) == -1){
            perror("Erro ao escrever no pipe");
            exit(EXIT_FAILURE);
        } // pai escreve no pipe 
        close(fd[1]); // apos escrever, fecha a extremidade de escrita
        wait(NULL); // espera o filho "ler"
        
    } else {
        close(fd[1]); // estremidade de escrita fechada
        if (read(fd[0], buffer, sizeof(buffer)) == -1){
            perror("Erro ao ler do pipe");
            exit(EXIT_FAILURE);
        } // filho le o pipe no espaco de memoria alocado
        printf("Filho recebeu: %s\n", buffer); // mensagem lida
        close(fd[0]);// apos ler, fecha a extremidade de leitura
    }
    return 0;
}