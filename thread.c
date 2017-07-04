#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>

/** 
*	Escreva um programa em C que cria uma worker thread usando
*	PThreads. A thread criada deverá imprimir na tela a frase “Nova thread
*	criada. TID = XX!”, onde XX é o identificador da thread. A main thread
*	deverá aguardar que a thread criada imprima a frase na tela antes de
*	terminar. Dica: use a função pthread_self() para retornar o ID da thread.
*/

void *printHi() {
	pthread_t tid = pthread_self();
	printf("Nova thread criada. TID = %u\n", (unsigned int)tid);
	pthread_exit(NULL);
}

int main (int argc, char **argv) {
	pthread_t thread;	
	pthread_create(&thread, NULL, printHi, NULL);	
	pthread_join(thread, NULL);	
}