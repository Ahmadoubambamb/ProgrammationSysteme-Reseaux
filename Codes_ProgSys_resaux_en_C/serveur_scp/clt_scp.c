#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "utils.h"
#include <sys/stat.h>
int main(int argc , char *argv[]){
    if(argc < 4)
    {printf("Usage : %s ADRESS PORT FICHIER\n",argv[0]);
        return 0;
    }
    int socketClient = socket(AF_INET,SOCK_STREAM,0);
    if(socketClient == -1)
    {perror("Erreur de creation de socket");
        return 0;
    }
    printf("socketClient cree avec sucess \n");

    // ADRESS
    struct sockaddr_in addrserv;
    memset(&addrserv,0,sizeof(struct sockaddr_in));
    addrserv.sin_family = AF_INET;
    addrserv.sin_port = htons(atoi(argv[2]));
    addrserv.sin_addr.s_addr = inet_addr(argv[1]);
    // connexion
    int resultat = connect(socketClient,(struct sockaddr*)&addrserv,sizeof(struct sockaddr_in));

   // printf("connexion du client %s : %d reussi\n",inet_ntoa(addrserv.sin_addr),ntohs(addrserv.sin_port));

    if(resultat == -1)
    {perror("erreur de connexion");
        return 0;
    }

    //recuperation des info du fichier
    struct stat sfile;
    stat(argv[3],&sfile);
    // initialisation
    struct infofile file;
    // memset(file,0,(struct infofile));
    file.taille = sfile.st_size;
    file.mode = sfile.st_mode;
    strcpy(file.nomfichier,argv[3]);
    // transfer des info
     int nbSend = send(socketClient,&file,sizeof(struct infofile),0);
     if(nbSend <=0){
         perror("Erreur d'envoi de donnees du fichier");
         return 0;
    }
    char bufr[255];
    memset(bufr,0,255*sizeof(char));
    recv(socketClient,bufr,255*sizeof(char),0);
    printf("reponse du serveur est: %s\n",bufr);
    //examen de la reponse du serveur
    if(strcmp(bufr,"OK")!=0)
    {
        perror("erreur de creation de reception ou de creation du fichier dans le serveur");
        return 0;
    }
    struct bloc_data bdata;
    int fd = open(argv[3],O_RDONLY);
    if(fd == -1){
        perror("error d'ouverture du fichier");
        return 0;
    }
    int nbred = 0;
    do{ nbred = read(fd,bdata.data,4096 * sizeof(char));
        if(nbred <= 0)
         bdata.taille = nbred;
        else
            bdata.taille = nbred;
        send(socketClient,&bdata,sizeof(bdata),0);

    }while(nbred > 0);
    close(fd);
    close(socketClient);
}
