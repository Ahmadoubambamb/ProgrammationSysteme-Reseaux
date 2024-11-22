#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/stat.h>
int main(int argc , char *argv[]){
    if(argc < 3){
        printf("Usage : %s nomfichier taille",argv[0]);
        return EXIT_FAILURE;
    }
    int taille , fd , result , nbr_parti;
    taille = atoi(argv[2]);
    fd = open(argv[1] , O_RDONLY);
    if(fd == -1){
        perror("Ouverture ");
        EXIT_FAILURE;
    }
    struct stat infoFic;
    result = fstat(fd ,&infoFic);
    if(result == -1){
        perror("Erreur de recuperatoin d'information du fichier!!");
        return 0;
    }
    printf("la taille de %s est: %d \n",argv[1],infoFic.st_size);
    printf("Permission de %s est: %o \n",argv[1],infoFic.st_mode);

    nbr_parti = infoFic.st_size/taille ;
   // taillerest = infoFic.st_size%taille;

    int *fddest = (int *)malloc(nbr_parti * sizeof(int));
    char nomDesFic[255];
    int nbread = 0 , total ;
    char buf;
    printf("Le fichier est partitionner en des sous-parti suivant:\n");
    for(int i = 0; i< nbr_parti ;i++){
        total = 0;
        sprintf(nomDesFic,"partie_%d",i);
        fddest[i] = open(nomDesFic , O_WRONLY | O_CREAT,infoFic.st_mode);
     while((nbread = read(fd,&buf,sizeof(char))) > 0)
     {
       if(write(fddest[i],&buf,sizeof(char)) <= 0){
           printf("Erreur d'ecriture dans la partie_%d",i);
           exit(1);
       }
       total += nbread;
       if(i < nbr_parti - 1){
       if(total == taille)
           break;
       }
      /*else if(total == taille + taillerest) break; */ //ceci n'est pas utile
    // la dernier fichier va contenir taille + le rest de la fichier
     }
     printf("partie_%d\n",i);
     close(fddest[i]); // on ferm le fichier cree
      }
 close(fd);
 free(fddest);// on libere l'espace alloue
    return 0;
}
