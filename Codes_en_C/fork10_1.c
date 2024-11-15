#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(){
    pid_t pidfils1 , pidfils2 , pidfils3;
   // pidfils2 = fork();
for(int i = 0; i<10 ;i++){
    pidfils1 = fork();
    switch(pidfils1){
        case -1: perror("Erreur de creation "); break;
        case 0:
            printf("%d  ->  %d ;\n",getpid(),getppid());
            break;
        default:
            wait(NULL);
           return 0;
    }
}
return 0;
}

// pour que le pere cree tout les fils on change le return et le mettre dans le fils
