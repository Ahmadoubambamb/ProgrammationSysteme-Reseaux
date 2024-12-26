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
int main(int argc , char *argv[]){
  if(argc < 2){
      printf("Usage: %s PORT",argv[0]);
      return 0;
   }

   int socketServerTCP = socket(AF_INET,SOCK_STREAM,0);
   if(socketServerTCP == -1)
   {perror("Erreur de creation de socket");
       return 0;
   }
   printf("Socket creer avec sucess\n");

   // initialisation de la structure

   struct sockaddr_in addrServer;
   memset(&addrServer,0,sizeof(struct sockaddr_in));

   addrServer.sin_family = AF_INET;
   addrServer.sin_port = htons(atoi(argv[1]));
   addrServer.sin_addr.s_addr = inet_addr("0.0.0.0");
   // appel de bind

   int resultat = bind(socketServerTCP,(struct sockaddr*)&addrServer,sizeof(struct sockaddr_in));
   if(resultat == -1)
   {perror("Erreur d'appel de bind");
       return 0;
  }
  printf("appel de bind reussi avec sucess\n");
  //appel de listen

  resultat = listen(socketServerTCP,5);
  if(resultat == -1)
  {perror("Erreur de listen");
      return 0;
  }
  printf("appel de listen avec sucess\n");

  // accept de connection

  struct sockaddr_in addrClient;
  int taille = sizeof(struct sockaddr_in);
  int sockClient = accept(socketServerTCP,(struct sockaddr*)&addrClient,&taille);
  printf("connection accepter pour le client %s : %d\n",inet_ntoa(addrClient.sin_addr),ntohs(addrClient.sin_port));

 //recuperation des info du fichier
  // buffer
  char bufrecv[255] ;
  char bufsend[255] = "OK";
  struct infofile info_f;
  //memset(&info_f,0,sizeof(struct infofile));
  int nbrec = recv(sockClient,&info_f,sizeof(struct infofile),0);
  if(nbrec <=0)
   strcpy(bufsend,"NOK");
   printf("creation du fichier %s:\ntaille: %d\nmode: %o\n",info_f.nomfichier,info_f.taille,info_f.mode);
  int fd = open(info_f.nomfichier,O_WRONLY | O_CREAT | O_EXCL,info_f.mode);
  if(fd == -1)
      strcpy(bufsend,"NOK");
    send(sockClient,bufsend,strlen(bufsend),0);
    if(strcmp(bufsend,"NOK")==0)
    {perror("Erreur de reception");
        return 0;
    }
    struct bloc_data bdata;
    int nbr;

    do{ memset(&bdata,0,sizeof(struct bloc_data));
        nbr = recv(sockClient,&bdata,sizeof(struct bloc_data),0);
        if(bdata.taille > 0 && nbr > 0)
           write(fd,bdata.data,bdata.taille * sizeof(char));

    }while(bdata.taille > 0);
        printf("fichier bien recu!!\n");
        close(fd);
        close(sockClient);
  return 0;
}
