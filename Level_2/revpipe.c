#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 100
#define MAX_INPUT (BUFFER_SIZE - 1)  // 99

void reverse_communication(char *msg, char *buffer, int *fd){

    pid_t pid = fork();
    ssize_t bytes_read;

    if (pid < 0){
        perror("Falha ao criar processo filho");
        exit(EXIT_FAILURE);
    }

    if (pid == 0){
        close(fd[0]); // filho fecha o pipe de leitura
        printf("Digite uma mensagem para seu pai:");
        if (fgets(msg, MAX_INPUT, stdin) == NULL){
            perror("Erro ao ler a mensagem");
            exit(EXIT_FAILURE);
        }
        msg[strcspn(msg, "\n")] = '\0'; // remove a quebra de linha no final da string
        if (write(fd[1], msg, strlen(msg) + 1) == -1){
            perror("Erro ao escrever no pipe");
            exit(EXIT_FAILURE);
        } // filho escreve no pipe
        close(fd[1]); // apos escrever, fecha a extremidade de escrita
        exit(0);
    }   else {
            close(fd[1]); // pai fecha o pipe de escrita
            bytes_read = read(fd[0], buffer, BUFFER_SIZE);// pai le o pipe no espaco de memoria alocado
            if (bytes_read == -1){
                perror("Erro ao ler do pipe");
                exit(EXIT_FAILURE);
            } // verifica erro na leitura
            buffer[bytes_read] = '\0'; // garante que a string esteja terminada
            printf("Pai recebeu: %s\n", buffer); // mensagem lida
            close(fd[0]);// apos ler, fecha a extremidade de leitura
            wait(NULL);
    }
}

int main(){

    char msg[100];
    char buffer[100];
    int fd[2];

    if (pipe(fd) == -1){
        perror("Falha ao criar pipe");
        exit(EXIT_FAILURE);
    }
    
    reverse_communication(msg, buffer, fd);

    return 0;
}