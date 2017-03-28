#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main (int argc, char **argv) {

    pid_t pid = getpid();
    
    for (int i = 0; i < 4; i++) {  
        if (pid > 0) {
            pid = fork(); 
            if (pid > 0) {
               printf("Processo %d criou %d\n" ,getpid(), pid);
            } else if (pid ==0) {
                printf("Processo filho. PID = %d\n", getpid());
                break;
            } else {
                printf("Processo não pode ser criado.");
                break;
            } 
        }    
    }
    
    //while(1) {}
    while (wait(NULL) != -1);
}
