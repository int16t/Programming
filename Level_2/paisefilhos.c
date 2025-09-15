#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    pid_t filho, neto;

    filho = fork();

    if (filho < 0) {
        perror("Erro, falha no fork");
        return 1;
    }
    else if (filho > 0) {
        // Processo pai
        printf("Eu sou o processo pai com o PID: %d e meu filho e: %d\n", getpid(), filho);
        wait(NULL); // espera pelo filho
    }
    else {
        // Processo filho
        printf("Eu sou o processo filho com o PID: %d\n", getpid());
        
        neto = fork();
        if (neto < 0) {
            perror("Erro, falha no fork");
            return 1;
        }
        else if (neto == 0) {
            // Processo neto
            printf("Eu sou o processo neto com o PID: %d e meu pai e: %d\n", getpid(), getppid());
            return 0;
        }
        else {
            // Filho espera pelo neto
            wait(NULL);
            return 0;
        }
    }

    return 0;
}