#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(){
    pid_t pidfils1 , pidfils2 , pidfils3;

    pidfils1 = fork();
    switch(pidfils1){
        case -1: perror("Erreur de creation "); break;
        case 0:
            printf("pid = %d ppid = %d \n",getpid(),getppid());
            break;
        default:
            wait(NULL);
            break;
    }
    pidfils2 = fork();
    switch(pidfils2){
        case -1: perror("Erreur de creation "); break;
        case 0:
            printf("pid = %d ppid = %d \n",getpid(),getppid());
            break;
        default:
            wait(NULL);
            break;
    }
    pidfils3 = fork();
    switch(pidfils3){
        case -1: perror("Erreur de creation \n"); break;
        case 0:
            printf("pid = %d ppid = %d \n",getpid(),getppid());
            break;
        default:
            wait(NULL);
            break;
    }
return 0;
}
