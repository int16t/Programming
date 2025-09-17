#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

void handler(int sig) {
    printf("Recebi sinal %d\n", sig);
    fflush(stdout);
}

int main() {
    struct sigaction sa_usr1, sa_int;

    // Trata SIGUSR1
    memset(&sa_usr1, 0, sizeof(sa_usr1));
    sa_usr1.sa_handler = handler;
    sigemptyset(&sa_usr1.sa_mask);
    sigaction(SIGUSR1, &sa_usr1, NULL);

    // Ignora SIGINT
    memset(&sa_int, 0, sizeof(sa_int));
    sa_int.sa_handler = SIG_IGN;
    sigemptyset(&sa_int.sa_mask);
    sigaction(SIGINT, &sa_int, NULL);

    printf("Executando... PID = %d\n", getpid());
    printf("Use: kill -SIGUSR1 %d\n", getpid());
    printf("CTRL+C deve ser ignorado.\n");

    while (1) {
        sleep(5);
    }

    return 0;
}
