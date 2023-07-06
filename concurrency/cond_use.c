#include <pthread.h>
#include <stdio.h>

void my_exit();
void my_join();

int sentry = 0;
pthread_cond_t cond;
pthread_mutex_t mutex;

void *child(void *arg) {
  printf("child\n");
  my_exit();
  return NULL;
}

void my_exit() {
  pthread_mutex_lock(&mutex);
  sentry = 1;
  pthread_cond_signal(&cond);
  pthread_mutex_unlock(&mutex);
}

void my_join() {
  pthread_mutex_lock(&mutex);
  while (sentry == 0) {
    pthread_cond_wait(&cond, &mutex);
  }
  pthread_mutex_unlock(&mutex);
}

int main (int argc, char *argv[]) {
  printf("parent: begin\n");

  pthread_cond_init(&cond, NULL);
  pthread_t p;
  pthread_create(&p, NULL, &child, NULL);
  my_join();
  pthread_cond_destroy(&cond);

  printf("parent: end\n");
  return 0;
}