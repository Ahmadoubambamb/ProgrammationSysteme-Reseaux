int main(int argc , char *argv[]){
    if(argc < 2)
    {printf("Erreur : Nombre d'argument insufissant \n");
        printf("Usage: %s PORT \n");
        return 0;
    }
    //1 creation de la socket
    int socketServer = socket(AF_INET,SOCK_STREAM,0);
    if(socketServer == -1){

    }
}
