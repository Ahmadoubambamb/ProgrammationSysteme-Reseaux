#include "common.h"

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
  printf("En attente de connexion...\n");
  int sockClient = accept(socketServerTCP,(struct sockaddr*)&addrClient,&taille);
  printf("connection accepter pour le client %s : %d\n",inet_ntoa(addrClient.sin_addr),ntohs(addrClient.sin_port));

  // initialisation du compteur
   int compteur = 0;
  printf("compteur initiliser a zero \n");
 while(1){
     send(sockClient , &compteur , sizeof(int) , 0);
     printf("compteur enoyer : compteur = %d\n",compteur);
     memset(&compteur , 0 , sizeof(int));
     recv(sockClient , &compteur , sizeof(int) , 0);
     printf("compteur recu : compteur = %d\n",compteur);
     compteur++;
     sleep(1);
}

  return 0;
}
