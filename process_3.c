#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main (int argc, char **argv) {

    pid_t pid, pid2;
    pid = getpid();
    int i, j;

    for (i = 0; i < 2; i++) {
        if (pid > 0) {
            pid = fork();  // first level
            if (pid == 0) {
                for (j = 0; j < 2; j++) {
                    pid2 = fork(); //second level
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
