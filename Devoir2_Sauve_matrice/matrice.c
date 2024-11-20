#include <unistd.h>
#include  <stdio.h>
#include <stdlib.h>
#include <time.h>
extern char * optarg;
extern int optopt;
extern int optind;
int main(int argc , char * argv[]){
 int **matrix;
 int dim;
    int opt ;
    while((opt = getopt(argc , argv , ":d:cabtf:")) != -1)
    {
        switch(opt)
        {
            case ':':
                printf("-%c attent un argument \n",optopt);
                break;
            case '?':
                printf("option -%c inconnu \n",optopt);
                break;
            case 'd':
                 dim = atoi(optarg);
                 printf("alloction d'une matrice de taille %d\n",dim);
                matrix = (int **)malloc(dim * sizeof(int*));
                for(int i = 0;i < dim;i++)
                    matrix[i] = (int*)malloc(dim * sizeof(int));
                break;
            case 'c':
                printf("creation d'une matrice aleatoire !\n");
                for(int i =0 ;i < dim ;i++)
                    for(int j = 0;j < dim ; j++)
                        matrix[i][j] = rand()%100 + 1;
                break;
            case 'a':
                for(int i =0 ;i < dim ;i++)
                 { for(int j = 0;j < dim ; j++)
                        printf("%d\t",matrix[i][j]);
                        printf("\n\n");}
                        break;
        }
    }

}
