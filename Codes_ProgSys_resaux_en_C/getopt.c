#include <unistd.h>
#include  <stdio.h>
#include <stdlib.h>
extern char * optarg;
//extern int opt;
extern int optopt;
int main(int argc,  char * argv[])
{
    int opt;
    int pas = 0;
    int nmax = 0;
    //traiter le resultat de getopt
    while((opt = getopt(argc,argv,":n:p:")) != -1)
    {
         switch(opt){
             case 'n':
                 nmax = atoi(optarg);
                 break;
             case 'p':
                pas = atoi(optarg);
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
    for(i=1;i<nmax;i++)
        printf("%d  ",i);
    return 0;
}
