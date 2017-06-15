/** O programa “calculo.c” realiza uma série de cálculos, armazenando
os resultados em um arranjo de tamanho SIZE. Para compilá-lo adicione a
flag de compilação -lm. Paralelize esse programa com OpenMP. Verifique o
tempo de execução da versão sequencial e paralela com diferentes números
de threads com o uso da ferramenta time do Linux. Dica: remova todos
os printf() para medir o tempo de execução corretamente.
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 50000

int main(int argc, char *argv[]) {
  int i;

  double *c = (double *) malloc (sizeof(double) * SIZE);


  for (i = 0; i < SIZE; i++) {
    c[i] = sqrt(i*  32) + sqrt(i * 16 + i * 8) + sqrt(i * 4 + i * 2 + i);
    c[i] -= sqrt(i * 32 * i * 16 + i * 4 + i * 2 + i);
    c[i] += pow(i * 32, 8) + pow(i * 16, 12);
  }

  free(c);

  return 0;
}