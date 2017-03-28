#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main (int argc, char **argv) {

    for (int i = 0; i < 4; i++) {  
        pid_t pid = fork(); 
        if (pid > 0) {
           printf("Processo %d criou %d\n" ,getpid(), pid);
        } else {
            printf("Processo filho. PID = %d\n", getpid());
            break;
        }
    }
    
    wait(NULL);
}
