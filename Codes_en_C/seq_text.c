#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
int main(int argc , char const * argv[])
{ if(argc < 3)
  {
    printf("erreur nombre argument insuffisant :");
    printf("Usage: %s nomfichier \n",argv[0]);
    return 0;
  }
  int max = atoi(argv[1]);
  int fd = open(argv[2],O_WRONLY | O_CREAT , S_IRUSR | S_IRGRP | S_IROTH );
  if(fd == -1)
  {perror("Erreur d'ouverture :");
   return 0;
  }
  // ajouter les donnees dans le fichier
   int nbWrite = 0;
   char textBuff[255]; //buffer text

 for(int i = 1; i <= max; ++i)
 {  // construction d'un chaine a partir des variable
     sprintf(textBuff,"%d",i);
    //ecriture de la chaine de caractere
     nbWrite = write(fd,textBuff,strlen(textBuff));
    if(nbWrite <= 0){
    perror("erreur d'ecriture ");
     return 0;
    }
 }
 close(fd);
 return 0;
}
