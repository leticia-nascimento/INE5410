#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

#define MAX_THREADS 100

int contador_global = 0;
sem_t sem_;

void *thread (void *arg) {
	sem_wait(&sem_);
 	int i;

  	for(i = 0; i < 100; i++)
    contador_global++;

	sem_post(&sem_);
}

int main(int argc, char **argv) {
 	int i;
 	pthread_t threads[MAX_THREADS];
 	sem_init (&sem_, 0, 1);

  	for(i = 0; i < MAX_THREADS; i++)
    	pthread_create(&threads[i], NULL, thread, NULL);

  	for(i = 0; i < MAX_THREADS; i++)
    	pthread_join(threads[i], NULL);

  	printf("Valor do contador global = %d\n", contador_global);
  	sem_destroy(&sem_);

  	return 0;
}