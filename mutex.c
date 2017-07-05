#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>

int contador_global = 0;
#define MAX_THREADS 2
pthread_mutex_t mutex;

/** 
*	Com base na solução do Exercício 3 (thread3.c)
*	sobre threads, utilize um mutex para resolver o problema da condição
*	de corrida.
*/

void *inc() {
	pthread_mutex_lock(&mutex);
	for(int j = 0; j < 100; j++)
		contador_global++;

	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
}

int main (int argc, char **argv) {
	pthread_t thread[MAX_THREADS];
	pthread_mutex_init(&mutex, NULL);	
	for(int i = 0; i < MAX_THREADS; i++) {
		pthread_create(&thread[i], NULL, inc, NULL);
	}
	for(int i2 = 0; i2 < MAX_THREADS; i2++) {
		pthread_join(thread[i2], NULL);
	}
	pthread_mutex_destroy(&mutex);
	printf("%d\n",contador_global);
}