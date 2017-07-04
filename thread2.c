#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>

#define MAX_THREADS 5

/** 
*	Transforme o código do exercício anterior (thread.c) em um código gené-
*	rico que cria n threads. Da mesma forma que o exercício anterior, a
*	main thread deverá aguardar a finalização de todas as worker threads
*	antes de terminar. O número de threads deverá ser definido no código
*	em uma constante chamada MAX_THREADS. Por exemplo, deverão ser
*	criadas 5 threads se a constante for definida da seguinte forma: #define
*	MAX_THREADS 5.
*/

void *printHi() {
	pthread_t tid = pthread_self();
	printf("Nova thread criada. TID = %u\n", (unsigned int)tid);
	pthread_exit(NULL);
}

int main (int argc, char **argv) {
	pthread_t thread[MAX_THREADS];	
	for(int i = 0; i < MAX_THREADS; i++) {
		pthread_create(&thread[i], NULL, printHi, NULL);
	}
	for(int i2 = 0; i2 < MAX_THREADS; i2++) {
		pthread_join(thread[i2], NULL);
	}
}