#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <errno.h> 

#define FIFO_PATH "/tmp/my_fifo"
#define MAX_BUFFER 100

struct Node{
    int data; // valor do nó
    struct Node* next; // ponteiro para o próximo nó
};

struct Queue{
    struct Node *front; // ponteiro para o nó da frente
    struct Node *rear; // ponteiro para o nó de trás
};

void initQueue(struct Queue* q){
    q->front = NULL;
    q->rear = NULL;
}

void inQueue(struct Queue* q, int value){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode){
        perror("Erro ao alocar memória");
        exit(EXIT_FAILURE);
    }
    
    newNode->data = value;
    newNode->next = NULL;

    if (q->rear == NULL){
        q->front = newNode;
        q->rear = newNode;
        return;
    }

    q->rear->next = newNode;
    q->rear = newNode;
}

int dequeue(struct Queue* q){
    if (q->front == NULL){
        perror("A fila está vazia, nao é possível remover elementos");
        exit(EXIT_FAILURE);
    }

    struct Node* temp = q->front;
    int removedValue = temp->data;
    q->front = q->front->next;

    if (q->front == NULL){
        q->rear = NULL;
    }
    free(temp);
    return removedValue;
}

int queueIsEmpty(struct Queue* q){
    return q->front == NULL;
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void processes(struct Queue* q){
    pid_t pid = fork();

    
    if (pid < 0){
        perror("Erro ao criar o processo filho");
        exit(EXIT_FAILURE);
    }
    else if(pid > 0){
        int fd = open(FIFO_PATH, O_WRONLY);
        int value;
        int continuar = 1;
        if (fd == -1){
            perror("Erro ao abrir o FIFO para escrita");
            exit(EXIT_FAILURE);
        }

        while(continuar != 0){
            printf("Digite um valor inteiro para ser adicionado na fila (FIFO): ");
            if (scanf("%d", &value) != 1) {
                printf("Entrada inválida. Por favor, digite um número inteiro.\n");
                clearInputBuffer(); // Limpa o buffer de entrada
                continue;
            }
            inQueue(q, value);
            clearInputBuffer(); // Limpa o buffer de entrada após leitura bem-sucedida
            continuar = -1; // Inicializa com um valor inválido
            while (continuar != 0 && continuar != 1){
                printf("Deseja adicionar outro valor? (1-Sim / 0-Não): ");
                scanf("%d", &continuar);
                clearInputBuffer(); // Limpa o buffer de entrada
                continue;
                }
        }// Loop para inserir múltiplos valores, se necessário

        inQueue(q, -1); // Sinaliza o fim da inserção com -1

        while(!queueIsEmpty(q)){
            value = dequeue(q);
            write(fd, &value, sizeof(int));
            if (value == -1) break; // Não escreve o sinal de término no FIFO
            printf("Processo pai escreveu %d no FIFO...\n", value);
        }
        close(fd);
        wait(NULL);  // Espera pelo filho
        unlink(FIFO_PATH);
        
    }else{
        int value;
        int fd = open(FIFO_PATH, O_RDONLY);
        if (fd == -1){
            perror("Erro ao abrir o FIFO para leitura");
            exit(EXIT_FAILURE);
        }
        while(read(fd, &value, sizeof(int)) > 0){
            if (value == -1) break; // Sinal de término
            printf("Processo filho leu %d do FIFO...\n", value);
        }
        close(fd);
    }
}

void freeQueue(struct Queue* q) {
    while (!queueIsEmpty(q)) {
        dequeue(q);
    }
}


int main (){

    if (mkfifo(FIFO_PATH, 0666) == -1 && errno != EEXIST) {
        perror("Erro ao criar FIFO");
        exit(EXIT_FAILURE);
    }
    struct Queue q;
    initQueue(&q);
    processes(&q);
    freeQueue(&q);

    return 0;
}