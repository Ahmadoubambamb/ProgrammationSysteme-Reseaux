#include "common.h"

int main(int argc , char *argv[]){
    if(argc < 3)
    {printf("Usage: %s adress PORT \n",argv[0]);
        return 0;
    }
    // socket client

    int socketClientTCP = socket(AF_INET , SOCK_STREAM ,0);
    if(socketClientTCP == -1)
    {perror("Erreur de creation de socket");
        return 0;
    }
    printf("socketClientTCP cree avec sucess\n");

    // adress
   struct sockaddr_in addrServer;
    memset(&addrServer,0,sizeof(struct sockaddr_in));
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(atoi(argv[2]));
    addrServer.sin_addr.s_addr = inet_addr(argv[1]);
    //connexion
    int res = connect(socketClientTCP,(struct sockaddr*)&addrServer,sizeof(struct sockaddr_in));
    if(res == -1)
    {perror("Erreur de connexion");
        return 0;
    }
    printf("connection reussi\n");
   // compteur
    int compteur;
    while(1){
        memset(&compteur , 0 , sizeof(int));
        recv(socketClientTCP , &compteur ,sizeof(int),0);
        printf("compteur recu : compteur = %d\n",compteur);
        sleep(1);
        compteur++;
        send(socketClientTCP , &compteur , sizeof(int) ,0);
        printf("compteur enoyer : compteur = %d\n",compteur);
    }
    return 0;
}
