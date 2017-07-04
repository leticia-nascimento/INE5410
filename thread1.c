#include <pthread.h>	
#include <stdio.h>

void *PrintHello (void *arg) {	
	long int val = (long int) arg;	
	pthread_t Dd = pthread_self();	
	printf("Thread %u: Hello! arg = %ld\n", (unsigned int)Dd, val);	
	pthread_exit(NULL);	
}	

int main (int argc, char**argv)	{
	int N = 2;
  	if (argc == 2) {
    	N = atoi(argv[1]);
    	if (N < 1) {
     		printf("Erro: numero de threads deve ser positivo.\n");
     		return 0;
    	}
  	}

	pthread_t threads[N];	
	long int arg = 123;
	for (int i = 0; i < N; i++) {
		pthread_create(&threads[i],	NULL, PrintHello, (void*)arg);
	}
	for (int i2 = 0; i2 < N; i2++) {	
		pthread_join(threads[i], NULL);	
	}
}