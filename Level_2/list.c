#include <stdio.h>      
#include <stdlib.h> //utilizar exit para maior portabilidade    
#include <unistd.h>     
#include <sys/types.h>
#include <sys/wait.h>

int main(){

    pid_t ls = fork();

    if (ls == -1){
        printf("Falha no fork\n");
        exit(EXIT_FAILURE);
    }
    else if (ls == 0){
        execlp("/bin/ls", "ls", "-l" , NULL);//substitui o processo filho pelo comando ls -l
        perror("Falha ao executar ls");//caso execlp falhe
        exit(EXIT_FAILURE);
    } 
    else {
        int status;
        waitpid(ls, &status, 0);//espera o processo filho terminar
        printf("-----------------------------------------------------------\n");
        printf("Filho terminou com status %d\n", WEXITSTATUS(status));
        printf("Diretorio listado com sucesso!\n");
    }

    return 0;
}