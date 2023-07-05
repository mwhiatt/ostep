#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "common.h"
#include <semaphore.h>
#include <sched.h>

volatile int counter = 0;
int loops;

void *worker(void * args) {
    int i;
    for (i=0; i<loops; i++) {
        counter++;
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Improper usage. Try: ./threads [loop #]\n");
        exit(-1);
    }

    loops = atoi(argv[1]);
    pthread_t t1, t2;
    printf("Initial value: %d\n", counter);
    pthread_create(&t1, NULL, worker, NULL);
    pthread_create(&t2, NULL, worker, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("Final Value: %d\n", counter);
    return 0;
}