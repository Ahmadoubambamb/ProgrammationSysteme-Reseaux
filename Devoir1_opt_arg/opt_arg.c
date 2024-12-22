#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
extern int optopt ;
extern char *optarg;
extern int optind ;
int f(int n){
    int fn = 1;
    for(int i = 1; i <= n ; i++)
        fn *= 2;
    return fn;
}

int g(int n){
    return 2 * n;
}

int main(int argc , char *argv[]){
    if(argc < 2 || argc >4){
        printf("Usage: %s -option arg\n ou \n",argv[0]);
         printf("Usage: %s -option arg -option\n",argv[0]);
         return 0;
    }
    int  nf , ng;
    int opt;
    int boolf = 0, boolg = 0; // pour verifier si l'option g ou f est donnee
    char opt_sans_arg = '\0'; // connaitre l'option qui a ete choisi et qui n'a d'argument
    while((opt=getopt(argc , argv ,":f:g:"))!= -1){
        switch(opt){
            case 'f':
                boolf = 1;
                nf = atoi(optarg);
            break;
            case 'g':
                boolg = 1;
                ng = atoi(optarg);
            break;
            case ':':
               opt_sans_arg = (char)optopt;
            break;

            case '?':
                printf("l'option -%c inconnu",optopt);
            break;
        }
    }

   if(opt_sans_arg == 'f')
       printf("gof(%d) = %d\n",ng,g(f(ng)));
    else if(opt_sans_arg == 'g')
        printf("fog(%d) = %d\n",nf,f(g(nf)));
    else
    { if(boolf == 1)
        printf("f(%d) = %d\n",nf,f(nf));
        else if(boolg == 1)
        printf("g(%d) = %d\n",ng,g(ng));
    }
}
