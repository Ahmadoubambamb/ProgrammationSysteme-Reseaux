#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
int main(int argc , char *argv[]){
    if(argc < 2){
        printf("usage : %s PORT",argv[0]);
        return 0;
    }
    int socketServerTCP = socket(AF_INET,SOCK_STREAM,0);
    if(socketServerTCP == -1){
        perror("Erreur de creation de socket\n");
        return 0;
    }
    printf("socketServerTCP cree avec succes\n");

    // initialisation de la structure d'adress
    struct sockaddr_in addr_server;
    memset(&addr_server,0,sizeof(addr_server));
    addr_server.sin_family = AF_INET;
    addr_server.sin_port = htons(atoi(argv[1]));
    addr_server.sin_addr.s_addr = inet_addr("0.0.0.0"); //ou INADDR_ANY

    // appel de bind
    int resultat = bind(socketServerTCP,(struct sockaddr*)&addr_server,sizeof(struct sockaddr_in));
    if(resultat == -1){
        perror("Erreur de lancement de bind");
       return 0;
    }
    printf("lancement de bind avec succes\n");
    resultat = listen(socketServerTCP,5); //taille de la fil d'attente = 5
    if(resultat == -1){
        perror("Erreur de listen");
        return 0;
    }
    printf("creation de listen avec succes\n");

    // accept declaration de la structure qui va contenir l'adress distant
    struct sockaddr_in addrClient;
    // buffer
    char buffsend[] = "pong";
    char buffrecv[10] ;
    int taille = sizeof(struct sockaddr_in);
    while(1){
        int socketClientTCP = accept(socketServerTCP,(struct sockaddr*)&addrClient,&taille);
        printf("connexion accepter pour le client %s : %d\n ",inet_ntoa(addrClient.sin_addr),ntohs(addrClient.sin_port));

        // envoi  de ping

        send(socketClientTCP,buffsend,strlen(buffsend),0);
        printf("envoi de ping :\n");
        sleep(1);
        // recevoir
        memset(buffrecv,0,10);
        recv(socketClientTCP,buffrecv,5*sizeof(char),0);
        printf("donnees recu : %s \n",buffrecv);
        close(socketClientTCP);
    }
    return 0;

}
