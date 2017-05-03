#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Escreva um programa em C no qual o processo pai cria 4 processos
* filhos. Para cada filho criado, o processo pai deverá imprimir 
* "Processo pai XX criou YY", onde XX é o PID do pai e YY o PID do filho.
* Além disso, os processos filhos deverão imprimir na tela "Processo filho XX",
* onde XX é o PID do filho. Dica: Utilize a função getpid() para retornar o PID 
* do processo concorrente. 
*/

int main (int argc, char **argv) {
    pid_t pid = getpid();

    for (int i = 0; i < 4; i++) {  
        if (pid > 0) {
            pid = fork();
            if (pid > 0) {
               printf("Processo %d criou %d\n", getpid(), pid);
            } else if (pid == 0) {
                printf("Processo filho. PID = %d\n", getpid());
                break;
            } else {
                printf("Processo não pode ser criado.\n");
                break;
            } 
        }    
    }
    //while(1) {}
    while (wait(NULL) != -1);
}
