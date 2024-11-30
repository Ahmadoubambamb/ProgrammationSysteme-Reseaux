#include <unistd.h>
#include  <stdio.h>
#include <stdlib.h>

extern int  optopt; //option saisi par user
extern char * optarg; // pointeur de l'arguemnt courant
extern int optind ; //ind coomme indexe du tab d'argument

int main(int argc , char *argv[])
{ int opt;
    while((opt = getopt(argc , argv , ":a:bcn:")) != -1)
    {
        switch(opt){
            case 'a':
            case 'n':
            printf("vous avez tapez option: -%c arg: %s.\n",opt,optarg); break;
            case 'b':
            case 'c':
            printf("vous tapez opt: - %c \n",opt); break;
            case ':':
                printf("L'option -%c attend un arguemnt \n",optopt);
                break;
            default:
                printf("l'option -%c est mauvais \n",optopt);
        }
    }
    return 0;
}
