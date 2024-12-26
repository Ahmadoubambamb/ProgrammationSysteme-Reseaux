#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc ,char *argv[]) {
    if(argc < 2){
        printf("Usage: %s adress\n",argv[0]);
        return 0;
    }
    struct sockaddr_in addrServer;
    int port;
    // Configuration de la structure sockaddr_in pour l'adresse cible
    memset(&addrServer, 0, sizeof(addrServer));
    addrServer.sin_family = AF_INET;
    addrServer.sin_addr.s_addr = inet_addr(argv[1]);

    printf("Scan des ports TCP ouverts sur %s (plage 0-3000):\n", argv[1]);
    int sockClient;
    for (port = 0; port <= 3000; port++) {
        // Création du socket
        sockClient = socket(AF_INET, SOCK_STREAM, 0);
        if(sockClient == -1){
            perror("Erreur de création du socket");
            return 1;
        }

        // Configuration du port cible
        addrServer.sin_port = htons(port);

        // Tentative de connexion
   int res = connect(sockClient, (struct sockaddr *)&addrServer, sizeof(addrServer));
        if(res != 0)
            printf("Port ouvert : %d\n", port);
        // Fermeture du socket
        close(sockClient);
    }
    printf("Scan terminé.\n");
    return 0;
}
