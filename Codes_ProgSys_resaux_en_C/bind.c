#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
int main(int argc , char *argv[]){
  if(argc < 2){
      perror("Erreur arg insuffisant\n");
      printf("Usage : %s PORT",argv[0]);
      return 0;
}
   // int socketTCP = socket(AF_INET,SOCK_STREAM,0);
      int socketServeurTCP = socket(AF_INET,SOCK_STREAM,0);
    if(socketServeurTCP == -1){
        perror("Erreur de creation de la socket TCP");
        return 0;
    }
    printf("creation de socketServeurTCP avec success\n");
  //2 initialisation de la structure d'adresse
    struct sockaddr_in addrServer;
    memset(&addrServer , 0 ,sizeof(struct sockaddr_in));
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(atoi(argv[1]));
    addrServer.sin_addr.s_addr = inet_addr("0.0.0.0");

     //3 appel de bind
    int resultat = bind(socketServeurTCP,(struct sockaddr*) &addrServer,sizeof(struct sockaddr_in));
   if(resultat == -1){
       perror("Erreur de lencement de bind");
       return 0;
    }
    printf("creation de bind avec success\n");
    resultat = listen(socketServeurTCP,5);
    if(resultat == -1){
          perror("Erreur de lencement de listen");
       return 0;
    }
    printf("creation de listen avec success\n");

    // accept
    // declarer la structure qui va contenir l'adresse distante
    struct sockaddr_in addrClient;
    int taille = sizeof(struct sockaddr_in);
    while(1)
        { int sockClientTCP = accept(socketServeurTCP ,(struct sockaddr*) &addrClient , &taille);
         printf("connection accepter pour le client %s : %d",inet_ntoa(addrClient.sin_addr), ntohs(addrClient.sin_port));
        }
    return 0;
}
