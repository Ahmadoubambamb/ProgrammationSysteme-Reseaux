#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(){
    pid_t pidfils1 , pidfils2 , pidfils3;
   // pidfils2 = fork();
    int profondeur = 0, nbfils;
for( nbfils = 0; nbfils <2 ;){
    pidfils1 = fork();
    switch(pidfils1){
        case -1: perror("Erreur de creation "); break;
        case 0:
            printf("%d  ->  %d ;\n",getpid(),getppid());
            profondeur ++;
            if(profondeur > 2)
            {
                return 0;
            }
            nbfils = 0;
            break;
        default:
         wait(NULL);
         ++ nbfils;
          if(nbfils >= 2)
           return 0;

    }
}
return 0;
}
