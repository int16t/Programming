#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>

struct timeval start, end;

int main(int argc, char *argv[]){

    pid_t pid;

    gettimeofday(&start, NULL);

    pid = fork();

    if (pid == 0) {
        execvp(argv[1], &argv[1]);
        perror("execvp falhou");
        exit(1);
    } else if (pid > 0) {
        // processo pai: espera o filho terminar
        int status;
        waitpid(pid, &status, 0);

        // pega o tempo final
        gettimeofday(&end, NULL);

        // calcula diferença em segundos e microssegundos
        double time = (end.tv_sec - start.tv_sec) +
                      (end.tv_usec - start.tv_usec) / 1000000.0;

        printf("Tempo de execução: %.6f segundos\n", time);
    } else {
        perror("fork falhou");
        return 1;
    }

    return 0;
}