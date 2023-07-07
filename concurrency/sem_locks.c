//Example of semaphore used as locks
#include <semaphore.h>

sem_t s;

int main(int argc, char *argv[]) {
    sem_init(&s, 0, 1); // 1 is the initial value of the semaphore, 0 represents all threads are in the same process
    sem_wait(&s);
    // critical section here
    sem_post(&s);
    sem_destroy(&s);
    return 0;
}