#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
int main(int argc , char *argv[])
{ if(argc < 2){
    printf("Erreur nombre d'argument insuffisant \n");
    printf("Usage : %s nomfichier \n",argv[0]);
    return 0;
   }
    int fd = open(argv[1], O_WRONLY |O_CREAT | O_EXCL,S_IWUSR | S_IRGRP | S_IROTH);
    if(fd == -1)
    {
        perror("Erreur de creation du fichier :");
        return 0;
    }
    printf("fichier %s creer avec succes \n",argv[1]);
    close(fd);
    return 0;
}
