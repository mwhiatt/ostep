// Example of semaphores as condition variables
// prints begin, end, child on my machine and I can't figure out why
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

sem_t *s;
static const char *sname = "lock";

void *child(void *arg) {
  printf("child\n");
  sem_post(s); // signal here: child is done
  return NULL;
}

int main(int argc, char *argv[]) {
  s = sem_open(sname, O_CREAT, 0777, 0);
  printf("parent: begin\n");
  pthread_t c;
  pthread_create(&c, NULL, child, NULL);
  sem_wait(s);
  sem_unlink(sname);
  printf("parent: end\n");
  return 0;
}