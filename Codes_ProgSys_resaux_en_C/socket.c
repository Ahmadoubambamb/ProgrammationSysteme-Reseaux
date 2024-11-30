#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
int main(int argc , char *argv[]){

    int socketTCP = socket(AF_INET,SOCK_STREAM,0);
    if(socketTCP == -1){
        perror("Erreur de creation de la socket TCP");
        return 0;
    }
    printf("creation de socketTCP avec success\n");
     int socketUDP = socket(AF_INET,SOCK_DGRAM,0);
    if(socketUDP == -1){
        perror("Erreur de creation de la socket TCP");
        return 0;
    }

    printf("creation de socketUDP avec success\n");
    return 0;
}
