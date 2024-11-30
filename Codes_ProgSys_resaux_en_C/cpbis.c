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
    printf("Usage: %s source dest \n",argv[0]);
    return 0;
  }
 // ouverture du fichier source
 int fdsrc = open(argv[1],O_RDONLY );
  if(fdsrc == -1)
  {perror("Erreur d'ouverture :");
   return 0;
  }
  printf("ouverture du fichier %s avec succes ",argv[1]);
  //creation de fichier destination
  struct stat stFichierSrc;
  int resultat = fstat(fdsrc,&stFichierSrc);
  if(resultat == -1)
  {perror("Erreur de recuperation des informations sur le fichier source ");
    return 0;
  }
  printf("la taille du fichier %ld\n",stFichierSrc.st_size);
  printf("permision: %o \n",stFichierSrc.st_mode);

  //creation du fddest

  int fdDst = open(argv[2], O_CREAT | O_WRONLY,stFichierSrc.st_mode);
  if(fdDst == -1)
      {perror("Erreur d'ouverture du fichier de destination:");
   return 0;
  }
  printf("creation du fichier de destination avec succes !!\n");
  // copie des donnees
  char buff ;
  int nbRead , nbWrite ;
  int nbTotal = 0;
  do{
      // lecture dans le fichier source
      nbRead = read(fdsrc,&buff,sizeof(char));
      if(nbRead > 0)
      {
          nbWrite = write(fdDst,&buff,sizeof(char));
          if(nbWrite <= 0)
          {
              perror("Erreur d'ecriture dans le fichier de destination");
              return 0;
        }
        nbTotal +=nbWrite;
        printf("\r%.4f%%",100.0 * nbTotal/stFichierSrc.st_size);
    }

 }while(nbRead > 0);
 close(fdsrc);
 close(fdDst);
  return 0;
}

/*
 char *buff = malloc(stFichierSrc.st_size * sizeof(char));

 on lit  nbWrite = write(fdDst,buff,nbRead * sizeof(char));
 */