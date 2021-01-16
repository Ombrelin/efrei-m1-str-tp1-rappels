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

void writeBuffer(int data, struct Buffer* buffer) {
    buffer->data[buffer->writeIndex] = data;
    buffer->writeIndex = (buffer->writeIndex + 1) % BUFFER_SIZE;
}

int readBuffer(struct Buffer* buffer) {
    int data = buffer->data[buffer->readIndex];
    buffer->readIndex = (buffer->readIndex + 1) % BUFFER_SIZE;
    return data;
}

void *producer() {
    while (1) {

        srand(time(NULL));
        int randomData = rand();
        sleep(3);
        P(&lib);
        writeBuffer(randomData, &buffer);
        printf("Producer wrote %d in the buffer\n", randomData);
        V(&occ);
    }
}

void *consumer() {
    while (1) {
        P(&occ);
        int data = readBuffer(&buffer);
        printf("Consumer read %d from the buffer\n", data);
        V(&lib);
        sleep(3);
    }
}


void exo3() {
    buffer.writeIndex = 0;
    buffer.readIndex = 0;

    sem_init(&lib, 0, BUFFER_SIZE);
    sem_init(&occ, 0, 0);

    pthread_t consumer_thread;
    pthread_t producer_thread;

    pthread_create(&consumer_thread, NULL, consumer, NULL);
    pthread_create(&producer_thread, NULL, producer, NULL);

    pthread_join(consumer_thread,NULL);
    pthread_join(producer_thread,NULL);
}

// Exo 4


sem_t freeAir;
sem_t occAir;

sem_t freeGround;
sem_t occGround;

// Air buffer
struct Buffer air;
// Ground Buffer
struct Buffer ground;

// Air producer
void *incomingPlane() {
    while (1) {
        srand(time(NULL));
        int randomData = rand();
        sleep(3);
        P(&freeAir);
        writeBuffer(randomData, &air);
        printf("Plane %d incoming\n", randomData);
        V(&occAir);
    }
}

// Air consumer
void *landPlane() {
    while (1) {
        P(&occAir);
        int data = readBuffer(&air);
        sleep(3);
        printf("Plane %d has landed\n", data);
        V(&freeGround);
    }
}

// Ground producer
void *releasePlane() {
    while (1) {
        srand(time(NULL));
        int randomData = rand();
        sleep(3);
        P(&freeGround);
        writeBuffer(randomData, &ground);
        printf("Plane %d out of hangar\n", randomData);
        V(&occAir);
    }
}

// Ground consumer
void *takeOffPLane() {
    while (1) {
        P(&occGround);
        int data = readBuffer(&ground);
        sleep(3);
        printf("Plane %d has taken off\n", data);
        V(&freeGround);
    }
}

void exo4() {
    sem_init(&freeAir, 0, BUFFER_SIZE);
    sem_init(&occAir, 0, 0);

    sem_init(&freeGround, 0, BUFFER_SIZE);
    sem_init(&occGround, 0, 0);

    pthread_t releasePlane_thread;
    pthread_t takeOffPLane_thread;
    pthread_t incomingPlane_thread;
    pthread_t landPlane_thread;

    pthread_create(&releasePlane_thread, NULL, releasePlane, NULL);
    pthread_create(&takeOffPLane_thread, NULL, takeOffPLane, NULL);
    pthread_create(&incomingPlane_thread, NULL, incomingPlane, NULL);
    pthread_create(&landPlane_thread, NULL, landPlane, NULL);

    pthread_join(releasePlane_thread,NULL);
    pthread_join(takeOffPLane_thread,NULL);
    pthread_join(incomingPlane_thread,NULL);
    pthread_join(incomingPlane_thread,NULL);
}

int main() {
    // Exo 1
    //exo1();

    // Exo 2
    //exo2();

    // Exo 3
    //exo3();

    // Exo 4
    exo4();

    return 0;
}