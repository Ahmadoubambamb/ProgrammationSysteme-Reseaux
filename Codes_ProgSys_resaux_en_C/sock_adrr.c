//#include <sys/stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
int main(int argc , char *argv[]){
    if(argc < 3){
        printf("Erreur d'argument insuffisant \n");
        printf("Usage: %s adress_IP PORT \n",argv[0]);
        return 0;
    }
    struct sockaddr_in addrServer;
    // initialisation de la structure a 0
    memset(&addrServer, 0 ,sizeof(struct sockaddr_in));

    addrServer .sin_family = AF_INET;
    addrServer.sin_port = atoi(argv[2]);
    addrServer.sin_addr.s_addr = inet_addr(argv[1]);

    printf("Adresse IP %s : %X\n",inet_ntoa(addrServer.sin_addr),ntohl(addrServer.sin_addr.s_addr));
    printf("num port %d : %d",ntohs(addrServer.sin_port),addrServer.sin_port);
    return 0;
}
