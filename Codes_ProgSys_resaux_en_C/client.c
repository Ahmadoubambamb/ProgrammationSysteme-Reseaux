#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
int main(int argc , char *argv[]){
  if(argc < 3){
      perror("Erreur arg insuffisant\n");
      printf("Usage : %s ADRESS_IP PORT",argv[0]);
      return 0;
}
   //1. CREATION D'UNE SOCKET
   int socketClient = socket(AF_INET,SOCK_STREAM,0);
   if(socketClient == -1){
     perror("Erreur de creation de la socket");
     return 0;
  }
  //preparation de la structure vers le serveur
  struct sockaddr_in addrServer;
  memset(&addrServer,0,sizeof(struct sockaddr_in));
  addrServer.sin_family = AF_INET;
  addrServer.sin_port   = htons(atoi(argv[2]));
  addrServer.sin_addr.s_addr =inet_addr(argv[1]);
  //3. connect
  int resultat = connect(socketClient,(struct sockaddr*)&addrServer,sizeof(struct sockaddr_in));
  if(resultat == -1){
  perror("Erreur d'ouverture de la connection");
  return 0;
  }
  //4. logique de l'application
  char bufferReceive[10];
  char bufferSend[] ="pong";
  int nbreceive = 0;
  int i = 1;
  while(1){
     memset(bufferReceive,0,10*sizeof(char));
    nbreceive = recv(socketClient,bufferReceive,10*sizeof(char),0);
    if(nbreceive > 0)
    {
      printf("[%d] client > Serveur: %s \n",bufferReceive);
    }
    sleep(1);
    send(socketClient,bufferSend,strlen(bufferSend),0);
    printf("[%d]  Serveur > client: %s \n",bufferSend);
    i++;
  }
 return 0;
}
