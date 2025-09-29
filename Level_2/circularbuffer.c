#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#define TAM 5


typedef struct {
    int buffer[TAM];
    int head;
    int tail;
    int count;
    pthread_mutex_t mutex;
} CircularBuffer;

void cb_init(CircularBuffer *cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;  
    pthread_mutex_init(&cb->mutex, NULL);
}

bool cb_is_full(CircularBuffer *cb) {
    return cb->count == TAM;
}

bool cb_is_empty(CircularBuffer *cb) {
    return cb->count == 0;
}

bool cb_enqueue(CircularBuffer *cb, int valor) {
    pthread_mutex_lock(&cb->mutex);

    if (cb_is_full(cb)) {
        pthread_mutex_unlock(&cb->mutex);
        return false;
    }
    
    cb->buffer[cb->head] = valor;
    cb->head = (cb->head + 1) % TAM;
    cb->count++;
    pthread_mutex_unlock(&cb->mutex);

    return true;
}

void *thread_func(void *arg) {
    CircularBuffer *cb = (CircularBuffer *)arg;
    static int counter = 1;
    static pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;
    
    int valor;
    
    pthread_mutex_lock(&counter_mutex);
    valor = counter++;
    pthread_mutex_unlock(&counter_mutex);

    if (cb_enqueue(cb, valor)) {
        printf("Thread %ld adicionou valor %d\n", pthread_self(), valor);
    } else {
        printf("Thread %ld: Buffer cheio!\n", pthread_self());
    }
    
    return NULL;
}

int main (){
    CircularBuffer cb;
    cb_init(&cb);

    pthread_t threads[5];

    for (int i = 0; i < 5; i++) {
        if (pthread_create(&threads[i], NULL, thread_func, &cb) != 0){
            perror("Erro ao criar a thread");
            return 1;
        }
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&cb.mutex);

    return 0;
}