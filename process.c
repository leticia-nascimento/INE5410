#include <stdio.h>
#include <unistd.h>

/* Escreva um programa em C que cria um processo utilizando
* a chamada de sistema fork(). Ambos os processos pai e filho
* deverão imprimir na tela a frase "Novo processo criado!". Você
* deverá utilizar apenas um printf().
*/

int main (int argc, char **argv) {
    pird_t pid = fork();

    if (pid >= 0) {
      printf("Novo processo criado!\n");
    }

    return 0;
}
