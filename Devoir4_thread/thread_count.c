#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t semIncrement, semDecrement; // Sémaphores pour synchronisation
int compteur = 0;                // Compteur partagé entre les threads
int n;                           // Limite supérieure et inférieure

void *increment_thread(void *arg) {
    for (int i = 0; i < n; i++) {
        sem_wait(&semIncrement); // Attendre le signal pour incrémenter
        compteur++;              // Incrémenter
        printf("%d\n", compteur);
        sem_post(&semDecrement); // Signaler au thread décrémentation
    }
    return NULL;
}

void *decrement_thread(void *arg) {
    for (int i = 0; i < n; i++) {
        sem_wait(&semDecrement); // Attendre le signal pour décrémenter
        compteur--;              // Décrémenter
        printf("%d\n", compteur);
        sem_post(&semIncrement); // Signaler au thread incrémentation
    }
    return NULL;
}

int main() {
    printf("Entrez la valeur de n (limite positive et négative) : ");
    scanf("%d", &n);

    if (n <= 0) {
        fprintf(stderr, "n doit être un entier positif.\n");
        exit(EXIT_FAILURE);
    }

    // Initialisation des sémaphores
    sem_init(&semIncrement, 0, 1); // Le thread incrément peut commencer
    sem_init(&semDecrement, 0, 0); // Le thread décrément est bloqué initialement

    pthread_t thread1, thread2;

    // Création des threads
    pthread_create(&thread1, NULL, increment_thread, NULL);
    pthread_create(&thread2, NULL, decrement_thread, NULL);

    // Attente de la fin des threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destruction des sémaphores
    sem_destroy(&semIncrement);
    sem_destroy(&semDecrement);

    return 0;
}
