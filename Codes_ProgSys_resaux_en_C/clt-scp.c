#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include "utils.h"
int main(int argc , char *argv[]){
  if(argc < 4){
      perror("Erreur arg insuffisant\n");
      printf("Usage : %s ADRESS_IP PORT FICHIER",argv[0]);
      return 0;
   }
 // connection au serveur

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
  //4 copie
  //4.1 recuperation des donnees
  struct stat stfile;
  // envoyer information
  struct infofile info;
  info.taille = stfile.st_size;
  info.mode = stfile.st_mode;
  strcpy(info.nomfichier, argv[3]);
  int nbsend = 0;
  nbsend = send(socketClient,&info,sizeof(struct infofile),0);
  if(nbsend <= 0){
      perror("Erreur d'envoi des donnees du fichier ");
      return 0;
}
//buff

 char buffreceive[255];
 memset(buffreceive,0,255*sizeof(char));
recv(socketClient,buffreceive,255 * sizeof(char),0);
if(strcmp(buffreceive,"OK")!= 0){
    perror("Erreur de creation du fichier");
    return 0;
}
// l'envoi des donnees
int fd = open(argv[3],O_RDONLY);
if(fd == -1){
  perror("Erreur d'ouverture du fichier a distance");
  return 0;
}
int nbred = 0;
struct block_data bdata;
do{
  nbred = read(fd,bdata.data,4096*sizeof(char));
  if(nbred > 0){
    bdata.taille = nbred;
    send(socketClient,&bdata,4096*sizeof(char));
  }
  else if(nbred == 0)
  bdata.taille = 0;
  else
    bdata.taille = -1;

}while(nbred > 0);

nbsend = send (socketClient,)

close(socketClient);
return 0;
}
