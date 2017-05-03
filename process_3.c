#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Escreva um programa em C no qual o processo pai cria 2 processos
* filhos e cada um dos processos filhos cria mais 2 processos filhos.
* Os processos filhos deverão imrpimir "Processo XX filho de YY", onde
* XX é o PID do processo e YY é o PID do pai do processo. Dica: Utilize
* a função getpid() para retornar o PID do processo corrente e
* getppid() para retornar o PID do pai do processo corrente.
*/

int main (int argc, char **argv) {
    pid_t pid, pid2;
    pid = getpid();
    int i, j;

    for (i = 0; i < 2; i++) {
        if (pid > 0) {
            pid = fork();  // first level
            if (pid == 0) {
                for (j = 0; j < 2; j++) {
                    pid2 = fork(); // second level
                    if (pid2 == 0) {
                        break;
                    } else if (pid2 < 0) {
                        printf("Processo não pode ser criado.\n");
                        break;
                     }    
                } printf("Processo %d filho de %d\n", getpid(), getppid());
                  break;     
            } else if (pid < 0) {
                printf("Processo não pode ser criado.\n");
                break;
            }
        }
    }
    //while (1){}
    while (wait(NULL) != -1);
}
