#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


void *thread_one(void *arg){
    printf("Thread 1 executou: %s\n", (char *)arg);
    pthread_exit(NULL);
}

void *thread_two(void *arg){
    printf("Thread 2 executou: %s\n", (char *)arg);
    pthread_exit(NULL);
}

void msg_handler(char *buffer1, char *buffer2){
    for (int i = 0; i < 2; i++) {
        printf("Digite a mensagem de ate 100 caracteres para a thread %d: ", i + 1);
        if (fgets(i == 0 ? buffer1 : buffer2, 100, stdin) == NULL) {
            perror("Erro ao ler a mensagem para a thread");
            exit(EXIT_FAILURE);
        }
        (i == 0 ? buffer1 : buffer2)[strcspn(i == 0 ? buffer1 : buffer2, "\n")] = '\0';// remove
    }
    printf("=======================================================================\n");

}

void create_threads(pthread_t *t1, pthread_t *t2, char *msg1, char *msg2){
    if (pthread_create(t1, NULL, thread_one, (void *)msg1) != 0){
        perror("Erro ao criar a thread 1");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(t2, NULL, thread_two, (void *)msg2) != 0){
        perror("Erro ao criar a thread 2");
        exit(EXIT_FAILURE);
    }
    pthread_join(*t1, NULL);
    pthread_join(*t2, NULL);
}


int main(){
    pthread_t t1, t2;
    char buffer1[100];
    char buffer2[100];

    msg_handler(buffer1, buffer2);
    create_threads(&t1, &t2, buffer1, buffer2);

    return 0;
}