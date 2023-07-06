#include <assert.h>
#include <stdio.h>
#include <pthread.h>
#define MAX 10

int buffer[MAX];
int count = 0;
int loops = 10;
int fill_ptr = 0;
int use_ptr = 0;
pthread_cond_t empty, fill;
pthread_mutex_t mutex;

void put(int value) {
  buffer[fill_ptr] = value;
  fill_ptr = (fill_ptr + 1) % MAX;
  count++;
}

int get() {
  int tmp = buffer[use_ptr];
  use_ptr = (use_ptr + 1) % MAX;
  count--;
  return tmp;
}

void *producer(void *arg) {
  int i;
  for (i = 0; i < loops; i++) {
    pthread_mutex_lock(&mutex);
    while (count == MAX) {
      pthread_cond_wait(&empty, &mutex);
    }
    put(i);
    pthread_cond_signal(&fill);
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

void *consumer(void *arg) {
  int i;
  for (i = 0; i < loops; i++) {
    pthread_mutex_lock(&mutex);
    while (count == 0) {
      pthread_cond_wait(&fill, &mutex);
    }
    int tmp = get();
    pthread_cond_signal(&empty);
    printf("%d\n", tmp);
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

int main (int argc, char *argv[]) {
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&empty, NULL);
  pthread_cond_init(&fill, NULL);

  pthread_t p1, p2, p3, c1, c2, c3;
  pthread_create(&p1, NULL, producer, NULL);
  pthread_create(&p2, NULL, producer, NULL);
  pthread_create(&p3, NULL, producer, NULL);
  pthread_create(&c1, NULL, consumer, NULL);
  pthread_create(&c2, NULL, consumer, NULL);
  pthread_create(&c3, NULL, consumer, NULL);
  pthread_join(c3, NULL);
  pthread_join(c2, NULL);
  pthread_join(c1, NULL);
  pthread_join(p3, NULL);
  pthread_join(p2, NULL);
  pthread_join(p1, NULL);

  pthread_cond_destroy(&fill);
  pthread_cond_destroy(&empty);
  pthread_mutex_destroy(&mutex);

  return 0;
}