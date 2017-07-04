#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>

int contador_global = 0;
#define MAX_THREADS 2

/** 
*	Tendo como base a solução para o exercício anterior (thread2.c), crie uma
*	variável global do tipo inteiro inicialmente contendo o valor 0 (int contador_global
*	= 0;). Modifique a função executada pelas threads para que
*	cada thread realize 100 operações de incremento nesta variável global
*	(contador_global++) sem a utilização de mutex. Após o término
*	da execução das threads, a main thread deverá imprimir o valor armazenado
*	na variável contador_global. Em uma execução correta, o valor
*	impresso deverá ser igual a 100 vezes o número de threads criadas,
*	ou seja contador_global = 100 * MAX_THREADS. Execute várias
*	vezes este programa com 2, 4, 8, 32 e 128 threads e observe o valor impresso
*	a cada vez. O que acontece?
*/

void *inc() {
	for(int j = 0; j < 100; j++)
		contador_global++;

	pthread_exit(NULL);
}

int main (int argc, char **argv) {
	pthread_t thread[MAX_THREADS];	
	for(int i = 0; i < MAX_THREADS; i++) {
		pthread_create(&thread[i], NULL, inc, NULL);
	}
	for(int i2 = 0; i2 < MAX_THREADS; i2++) {
		pthread_join(thread[i2], NULL);
	}
	printf("%d\n",contador_global);
}