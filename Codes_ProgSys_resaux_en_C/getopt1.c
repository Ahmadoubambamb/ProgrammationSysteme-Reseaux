#include <stdio.h>
#include <stdlib.h>
/*
int main(int argc,char *argv[])
{ printf("argc = %d \n",argc);
    for(int i=0;i<argc;i++) //on commence par 0 pour afficher le chemin du fichier .exe
    {
        printf("argv[%d] = %s \n",i,argv[i]);
    }
   return 0;
}*/
/*
int main(int argc, char *argv[], char *arge[])
{
    int i=0;
    while(arge[i] != NULL){
        printf("arge[%d] = %s \n",i,arge[i]);
        i++;
    }

}*/
#include <unistd.h>
extern char * optarg;
extern int opt;
int main(int argc,  char * argv[])
{
    int opt;
    //traiter le resultat de getopt
    while((opt = getopt(argc,argv,":ln:mk:")) != -1)
    {
         switch(opt){
             case 'l':
             case 'm':
                 printf("l'otpion -%c est fourni \n",opt);
                 break;
             case 'n':
             case 'k':
                 printf("L'option -%c est fournie avec comme argument %s \n",opt,optarg);
                 break;
             case ':':
                 //une option qui attend un argument qui est absent
                 printf("Erreur: L'option -%c attend un argument \n",optopt);
             case '?':
                 printf("Erreur : option -%c inconnu ",optopt);
                 break;
        }

    }
    return 0;
}
