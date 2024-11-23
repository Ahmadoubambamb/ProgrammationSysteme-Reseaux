#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

#define MAX_THREADS 100

sem_t semaphores[MAX_THREADS]; // Un sémaphore par thread
int num_threads;               // Nombre de threads

void *ithread(void *args){
    int thread_id = *(int *)args;
    while (1){
        // Attendre que ce soit au tour de ce thread
        sem_wait(&semaphores[thread_id]);
        printf("Je suis le thread %d\n", thread_id + 1);
       for(int i = 0;i< 100000000;i++);
        // Passer au thread suivant
        sem_post(&semaphores[(thread_id + 1) % num_threads]);
    }
    return NULL;
}

int main(){
    int res;
    printf("Donnez le nombre de threads : ");
    scanf("%d", &num_threads);
    if (num_threads <= 0 || num_threads > MAX_THREADS){
        fprintf(stderr, "Le nombre de threads doit être compris entre 1 et %d.\n", MAX_THREADS);
        exit(EXIT_FAILURE);
    }
    pthread_t threads[MAX_THREADS];
    int thread_ids[MAX_THREADS];
    // ici on initialiser les sémaphores
    for (int i = 0; i < num_threads; i++){
        sem_init(&semaphores[i], 0, 0); // Initialise tous les sémaphores à 0
    }
    sem_post(&semaphores[0]); //on demarre le premier thread
    for (int i = 0; i < num_threads; i++){
        thread_ids[i] = i;
        res = pthread_create(&threads[i], NULL, ithread, &thread_ids[i]);
        if (res != 0) {
            perror("Erreur lors de la création du thread");
            exit(EXIT_FAILURE);
        }
    }
    // Attendre la fin des threads (inutile ici car ils tournent en boucle)
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    for (int i = 0; i < num_threads; i++){
        sem_destroy(&semaphores[i]);
    }
    return EXIT_SUCCESS;
}
