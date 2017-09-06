#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 2
// #define TAM_VET 10

pthread_mutex_t mutex;

unsigned long int *a;
unsigned long int *b;
unsigned long int prod;
int TAM_VET;

void *f(void *ide) {
  int i = 0;
  int id = atoi(ide);
  int tam = TAM_VET/NUM_THREADS;

  if (id > 0) {
    i = id * tam;  
  }

  if (id == NUM_THREADS -1) {
    tam += TAM_VET%NUM_THREADS;
  }

  tam += i;

  /* produto escalar dos vetores */
  pthread_mutex_lock(&mutex);

  for (i; i<tam; i++)
    prod += a[i] * b[i];

  pthread_mutex_unlock(&mutex);

  return 0;
}

int main (int argc, char *argv[]) { 
  int i;
  prod = 0.0;
  pthread_t threads[NUM_THREADS];
  pthread_mutex_init(&mutex, NULL);

  if(argc<2){
    printf("uso %s <tamanho vetores>\n", argv[0]);
    exit(1);
  }

  /* tamanho dos vetores */
  TAM_VET = atoi(argv[1]);

  /* alocacao do vetor A */
  a = (unsigned long int *) malloc(sizeof(unsigned long int) * TAM_VET);

  /* alocacao do vetor B */
  b = (unsigned long int *) malloc(sizeof(unsigned long int) * TAM_VET);

  printf("Inicializando vetores A e B...\n");

  /* inicializacao dos vetores */
  for (i=0; i<TAM_VET; i++)
    a[i] = 2;

  for (i=0; i<TAM_VET; i++)
    b[i] = 2;  

  for (i=0; i<NUM_THREADS; i++)
    pthread_create(&threads[i], NULL, f, (void *)threads[i]);

 for (i=0; i<NUM_THREADS; i++)
    pthread_join(threads[i], NULL);

  printf("Calculando...\n");

  printf("Terminou!\n");

  /*** imprime o resultado ***/
  printf("******************************************************\n");
  printf("Produto escalar: %lu\n", prod);
  printf("******************************************************\n");

  free(a);
  free(b);
  pthread_mutex_destroy(&mutex);
}
