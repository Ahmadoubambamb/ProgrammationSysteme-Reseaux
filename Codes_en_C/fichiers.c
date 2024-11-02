#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
int main(int argc , char *argv[])
{ int fd = open(argv[1],O_RDONLY);
    if(argc < 2)
    {
        printf("le nombre d'argument est insuffisant !\n");
        printf("Usage : %s nomfichier\n",argv[0]);
        return 0;
    }
    if(fd == -1)
    {
        perror("Erreur d'ouverture en lecture seule ");
    }
    else
        printf("ouverture en lecture seule OK\n");
   close(fd);
   fd = open(argv[1],O_RDWR);
   if(fd == -1)
    {
        perror("Erreur d'ouverture en ecriture  seule ");
    }
    else
        printf("ouverture en ecriture seule OK\n");
    close(fd);
    return 0;
}
