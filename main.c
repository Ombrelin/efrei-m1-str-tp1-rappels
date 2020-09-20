#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define P sem_wait
#define V sem_post

// Exo 1

sem_t sem1;
sem_t sem2;

void *jemes() {
    printf("Je");
    V(&sem1);
    P(&sem2);
    printf("mes ");
    V(&sem1);
}

void *syncthreads() {
    P(&sem1);
    printf(" synchronise ");
    V(&sem2);
    P(&sem1);
    printf("Threads");
}

void exo1() {
    pthread_t thread_id_1;
    pthread_t thread_id_2;

    pthread_create(&thread_id_1, NULL, jemes, NULL);
    pthread_create(&thread_id_2, NULL, syncthreads, NULL);
    pthread_join(thread_id_1, NULL);
    pthread_join(thread_id_2, NULL);
}

// Exo 2

#define THREAD_COUNT 15

sem_t barriere;

void *threadN(void *arg) {
    unsigned int *number = (int *) arg;
    srand(time(NULL));
    unsigned int randomTime = rand() % 10;
    sleep(randomTime);
    printf("%d : Travail termine\n", *number);
    V(&barriere);
    sleep(3);
    printf("%d : Fin du thread\n", *number);
}

void exo2() {
    sem_init(&barriere, 0, 0);
    pthread_t threads[THREAD_COUNT];
    unsigned int threadNumber[THREAD_COUNT];

    for (unsigned int i = 0; i < THREAD_COUNT; ++i) {
        threadNumber[i] = i;
    }

    for (unsigned int i = 0; i < THREAD_COUNT; ++i) {
        pthread_create(&threads[i], NULL, threadN, &threadNumber[i]);
    }
    sleep(3);
    printf("Barriere : Travail terminé\n");

    for (int i = 0; i < THREAD_COUNT; ++i) {
        P(&barriere);
    }

    printf("Barrière : Peut continuer\n");
}

// Exo 3

#define BUFFER_SIZE 10

sem_t lib;
sem_t occ;

typedef struct Buffer {
    int data[BUFFER_SIZE];
    unsigned int writeIndex;
    unsigned int readIndex;
} Buffer;

struct Buffer buffer;

void writeBuffer(int data) {
    buffer.data[buffer.writeIndex] = data;
    buffer.writeIndex = (buffer.writeIndex + 1) % BUFFER_SIZE;
}

int readBuffer() {
    int data = buffer.data[buffer.readIndex];
    buffer.readIndex = (buffer.readIndex + 1) % BUFFER_SIZE;
    return data;
}

void *producer() {
    while (1) {
        P(&lib);
        srand(time(NULL));
        int randomData = rand();
        sleep(3);
        writeBuffer(randomData);
        printf("Producer wrote %d in the buffer\n", randomData);
        V(&occ);
    }
}

void *consumer() {
    while (1) {
        P(&occ);
        int data = readBuffer();
        sleep(3);
        printf("Consumer read %d from the buffer\n", data);
        V(&lib);
    }
}


void exo3() {
    buffer.writeIndex = 0;
    buffer.readIndex = 0;

    sem_init(&lib, 0, BUFFER_SIZE);
    sem_init(&occ, 0, 0);

    pthread_t consumer_thread;
    pthread_t producer_thread;

    pthread_create(&consumer_thread,NULL,consumer,NULL);
    pthread_create(&producer_thread,NULL,producer,NULL);

    while (1){}
}

int main() {
    // Exo 1
    //exo1();

    // Exo 2
    //exo2();

    // Exo 3
    exo3();

    return 0;
}