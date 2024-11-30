#include <unistd.h>
#include  <stdio.h>
#include <stdlib.h>
extern char * optarg;
extern int optopt;
extern int optind;//indexe du premier du element de argv qui qui n'est ni parametre d'option
int main(int argc,  char * argv[])
{
    int opt;
    int pas = 0;
    int n = 1;
    //traiter le resultat de getopt
    while((opt = getopt(argc,argv,":n:p:")) != -1)
    {
         switch(opt){
             case 'n':
                 n = atoi(optarg);
                 break;
             case ':':
                  printf("Erreur: L'option -%c attend un argument \n",optopt);
                  break;
             case '?':
                 printf("Erreur : option -%c inconnu ",optopt);
                 break;
        }
    }
    int i;
    for(i=optind;i<argc;i++)
        printf("%s  ",argv[i]);
    return 0;
}
