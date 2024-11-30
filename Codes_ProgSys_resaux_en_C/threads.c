#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *fthreasecondaire(void *arg){
    int i = 0 ;
    while(1){
        printf("le thread secondaire :%d ...%d\n",i++,getpid());
    }
}

int main(int argc , char *argv[]){
    pthread_t th1;
    int resultat;
    resultat = pthread_create(&th1, NULL ,fthreasecondaire,(void*)NULL);
    if(resultat == -1){
        perror("Erreur de lancemenent du pthread secondaire ");
        exit(1);
    }
  int i = 0 ;

    while(1){
        printf("le thread principal :%d ...%d\n",i++,getpid());
    }
    return 0;
}
