#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
sem_t semSecond , semTer;
int i = 0 , compteur = 0;

void *fthreasecondaire(void *arg){
    while(1){
        sem_wait(&semSecond);
        printf("%d  %10d\n",++i,compteur++);
        sem_post(&semTer);
    }
   // pthread_exit(NULL);
}

void *fthreadternaire(void *arg){

    while(1){
        sem_wait(&semTer);
        printf("%d  %10d\n",++i,compteur--);
        sem_post(&semSecond);
    }
  //  pthread_exit(NULL);
}

int main(int argc , char *argv[]){
   // initialisation de semaphore
     int resultat0 , resultat1 ,r1,r2;
    resultat0 = sem_init(&semSecond , 0 ,1);
     if(resultat0 == -1){
        perror("Erreur de lancemenent du pthread secondaire ");
        exit(1);
    }

   resultat1 = sem_init(&semTer, 0 ,0);
     if(resultat1 == -1){
        perror("Erreur de lancemenent du pthread secondaire ");
        exit(1);
    }
    pthread_t th1;

    r1 = pthread_create(&th1, NULL ,fthreasecondaire,(void*)NULL);
    if(r1 == -1){
        perror("Erreur de lancemenent du pthread secondaire ");
        exit(1);
    }
pthread_t th2;
r2 = pthread_create(&th2, NULL ,fthreadternaire,(void*)NULL);
    if(r2 == -1){
        perror("Erreur de lancemenent du pthread secondaire ");
        exit(1);
    }
  pthread_join(th1,NULL);
  pthread_join(th2,NULL);

    return 0;
}
