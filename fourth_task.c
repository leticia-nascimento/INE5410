#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>

#define N 10

sem_t full;
sem_t empty;
sem_t printI;
int buffer[N];
int inicio;
int final;
int contador;

void imprime () {
  sem_wait(&printI);

  for(int i = 0; i < N; i++) {
    printf("%d, ", buffer[i]);
  }

  printf("\n");
  sem_post(&printI);
}

void *produtor (void *arg) {
  while(10) {
  sem_wait(&empty);
  sleep(3);
  final = (final + 1) % N;
  buffer[final] = 42;
  imprime();
  sem_post(&full);
  contador++;
  }
}

void *consumidor (void *arg) {
  while(42) {
  sem_wait(&full);
  sleep(5);
  inicio = (inicio + 1) % N;
  buffer[inicio] = 1;
  imprime();
  sem_post(&empty);
  }
}

int main(int argc, char **argv) {
  sem_init (&full, 0, 0);
  sem_init (&empty, 0, N);
  sem_init (&printI, 0, 1);
  inicio = -1;
  final = -1;
  int i;
  pthread_t thread1;
  pthread_t thread2;

  pthread_create(&thread1, NULL, produtor, NULL);
  pthread_create(&thread2, NULL, consumidor, NULL);

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  sem_destroy(&full);
  sem_destroy(&empty);
  sem_destroy(&printI);

  return 0;
}