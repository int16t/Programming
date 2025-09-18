#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void ps() {
    pid_t child = fork();

    if (child < 0){
        perror("Fork falhou");
        exit(EXIT_FAILURE);
    }
    else if (child == 0) {
        // Processo filho
        execlp("/bin/ps", "ps", "aux", NULL);
        perror("execlp falhou");
        exit(EXIT_FAILURE);
    } else {
        // Processo pai
        wait(NULL); // Espera o filho terminar
        printf("<==================================>\n");
        printf("Comando 'ps aux' executado com sucesso.\n");
    }
}

void minitop() {
    pid_t pid = getpid();
    pid_t ppid = getppid();

    printf("Minitop - Monitoramento de Processos\n");
    printf("<==================================>\n");
    printf("PID do processo atual: %d\n", pid);
    printf("PID do processo pai: %d\n", ppid);
    printf("<==================================>\n");
}


int main() {

    minitop();
    sleep(2);
    ps();

    return 0;
}