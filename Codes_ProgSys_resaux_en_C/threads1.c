#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
int i = 0 , comptpr = 0, comptscd = 0 , compttern = 0;
void *fthreasecondaire(void *arg){

    while(1){
        printf("%d  %10d  %10d  %10d\n",++i,comptpr , comptscd++,compttern);
    }
    pthread_exit(NULL);
}

void *fthreadternaire(void *arg){

    while(1){
        printf("%d  %10d  %10d  %10d\n",++i,comptpr , comptscd , compttern++);
    }
    pthread_exit(NULL);
}

int main(int argc , char *argv[]){
    pthread_t th1;
    int resultat;
    resultat = pthread_create(&th1, NULL ,fthreasecondaire,(void*)NULL);
    if(resultat == -1){
        perror("Erreur de lancemenent du pthread secondaire ");
        exit(1);
    }
pthread_t th2;
resultat = pthread_create(&th2, NULL ,fthreadternaire,(void*)NULL);
    if(resultat == -1){
        perror("Erreur de lancemenent du pthread secondaire ");
        exit(1);
    }

    while(1){
        printf("%d  %10d  %10d  %10d\n",++i,comptpr++ , comptscd ,compttern);
    }
    return 0;
}
