#ifndef SERVEURWEB_H
#define SERVEURWEB_H
#include<stdio.h>


void affiche_sockaddr(struct sockaddr_in );
void affiche_Requete(char*buffRecieve);
int Reponse_Requete(int sock);
#endif //SERVEURWEB_H
