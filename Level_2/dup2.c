#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

#define STDOUT 1
#define MAX_INPUT 99 // 99 caracteres + \n ou \0 = 100 bytes


void dup2_scall(char *nome_arquivo){

    pid_t pid = fork();

    if (pid < 0){
        perror("Falha ao criar processo filho");
        exit(EXIT_FAILURE);
    }

    if (pid == 0){        
        int fd = open(nome_arquivo, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1){
            perror("Erro ao abrir/criar o arquivo");
            exit(EXIT_FAILURE);
        }
        if (dup2(fd, STDOUT) == -1){
            perror("Erro ao redirecionar a saída padrão");
            close(fd);
            exit(EXIT_FAILURE);
        }

        execlp("/bin/ls", "ls", NULL);

        perror("Erro ao executar o comando ls");
        close(fd);
        exit(EXIT_FAILURE);
    }
    else {
        // Processo pai: espera o filho terminar
        wait(NULL);
        sleep(1);
        printf("Comando ls executado, saída salva em %s\n", nome_arquivo);
    }
}

char *nome(){
    static char nome[100];
    printf("Digite o nome do arquivo: ");
    if (fgets(nome, MAX_INPUT, stdin) == NULL){
        perror("Erro ao ler o nome do arquivo");
        exit(EXIT_FAILURE);
    }
    nome[strcspn(nome, "\n")] = '\0'; // remove a quebra de linha no final da string
    return nome;
}

int main(){
    char *nome_arquivo = nome();
    dup2_scall(nome_arquivo);
    
    return 0;
}
