#include<stdio.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<string.h>
#include<stdlib.h>
#include <unistd.h>
#include"serveurWeb.h"
 int compteur = 0;
 char *RACIN
int main(int argc,char* argv[])
 {
    if(argc<2)
     {
        printf("nombre d argument insuffissant \n");
        printf("Usage : %s Port \n",argv[0]);
        return 0;
     }
  //creation de socket 
  int sockServeur=socket(AF_INET, SOCK_STREAM, 0);
  if(sockServeur==-1){
     printf("Erreur de  la creation du socket \n");
     return 0;
  }
  printf("[#Sock SERVEUR ] creation de la socket    OK\n");

  // Initialiser la structure de l adresse 
     struct sockaddr_in addrServer;
  // initialisation de la strcture 
   memset(&addrServer,0,sizeof(struct sockaddr_in ));
    addrServer.sin_family=AF_INET;
    addrServer.sin_port=htons(atoi(argv[1]));
    addrServer.sin_addr.s_addr=inet_addr("0.0.0.0");

    int result=bind(sockServeur, (struct sockaddr*)& addrServer, sizeof(struct sockaddr_in));
      if(result==-1){
        printf("Erreur de la creation du bind()\n");
        return 0;
      }
    printf("[#Sock SERVEUR ] Nommage de la socket avec Bind() \n");
    int resut=listen(sockServeur,5);
    if(resut==-1){
        printf("Erreur de la creation du Listen()\n");
        return 0;
      }
    printf("[#Sock SERVEUR ] Nommage de la socket avec Listen() \n");
    struct sockaddr_in addrClient;
    int taille_addr =sizeof(struct sockaddr_in);
    int socketClient;
    char buffRecieve[8192];
    int nbRecieve;
    while (1)
    {
       socketClient=accept(sockServeur,(struct sockaddr *)&addrClient,&taille_addr);
       affiche_sockaddr(addrClient);
       //initialiser le buffRecieve 
       memset(buffRecieve,0,8192*sizeof(char));
       nbRecieve=recv(socketClient,buffRecieve,8192*sizeof(char),0);

       if(nbRecieve==-1){
        printf("Erreur de  Reception recv()\n");
        return 0;
      }
      affiche_Requete(buffRecieve);
       close(socketClient);
    }
    

  return 0;
}

void affiche_sockaddr(struct sockaddr_in  sockaddr){
    printf("Client Accepter :  \n");
    printf("=======================================================\n");
    printf("Adresse IP :%s \n",inet_ntoa(sockaddr.sin_addr));
    printf("Numero PORT : %d\n",ntohs(sockaddr.sin_port));
    printf("========================================================\n");

}

void affiche_Requete(char*buffRecieve){
    printf("Requete du client \n");
    printf(" %s :\n",buffRecieve);
    printf("========================================================\n");
}

int Reponse_Requete(int sock , char requete[]){



    char templateEntete[8194] = "du n'import quoi et quelque truc ok";
    int nbsend = send(sock ,reponse ,strlen(reponse),0);
    if(nbsend < 0){
       perror("Erreur d'envoi de la reponse");
       return -1;
   }
   return 0;
}




