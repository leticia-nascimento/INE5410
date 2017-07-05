#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int contador_global = 0;
#define MAX_THREADS 2
sem_t semaphore;

/** 
*	Substitua o mutex da solução anterior (mutex.c) por um semáforo. Verifique 
*	se o comportamento com semáforo é equivalente ao do mutex.ão
*/

void *inc() {
	sem_wait(&semaphore);
	for(int j = 0; j < 100; j++)
		contador_global++;

	sem_post(&semaphore);
	pthread_exit(NULL);
}

int main (int argc, char **argv) {
	pthread_t thread[MAX_THREADS];
	sem_init(&semaphore, 0,	1);	
	for(int i = 0; i < MAX_THREADS; i++) {
		pthread_create(&thread[i], NULL, inc, NULL);
	}
	for(int i2 = 0; i2 < MAX_THREADS; i2++) {
		pthread_join(thread[i2], NULL);
	}
	sem_destroy(&semaphore);
	printf("%d\n",contador_global);
}