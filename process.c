#include <stdio.h>
#include <unistd.h>


int main (int argc, char **argv) {
    pird_t pid = fork();

    if (pid >= 0) {
      printf("Novo processo criado!\n");
     }
    
    return 0;
}
