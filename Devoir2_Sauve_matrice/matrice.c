#include <unistd.h>
#include  <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
extern char * optarg;
extern int optopt;
extern int optind;
int main(int argc , char * argv[]){
    srand(time(NULL));
 int **matrix;
 int dim ,opt ,estbinaire = 0;
  char nomfic[255];
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
                if(estbinaire){
                printf("affichage de la matrice :\n");
                 int i = 0 , nbread = 0 , buf;
                     int fdr = open(nomfic ,O_RDONLY);
                     if(fdr == -1){
                         perror("Ouverture pour lire");
                         return EXIT_FAILURE;
                    }
                 do{ nbread = read(fdr, &buf, sizeof(int));
                     i++;
                     if(nbread > 0)
                     {  printf("%5d ",buf);
                      if(i%dim == 0)
                             printf("\n");
                     }

                   }while(nbread > 0);
                 close(fdr);
                }
                else{
                    // text
                }
                        break;
            case 'f':
                strcpy(nomfic,optarg);
                printf("creation du fichier %s ",optarg);
                int fd = open(optarg, O_CREAT , S_IWUSR | S_IRUSR);
                if(fd == -1){
                   printf("a echouer !!?\n");
                    return EXIT_FAILURE;
                }
                printf("reussi avec succes !\n");
                close(fd);
                break;

            case 'b':
                estbinaire = 1;
                 int fdw = open(nomfic,O_WRONLY);
                 if(fdw == -1)
                 { perror("Ouverture !");
                     return EXIT_FAILURE;
                 }

                for(int i = 0;i < dim ;i++)
                    for(int j = 0;j < dim ;j++)
                         if(write(fdw , &matrix[i][j] , sizeof(int)) <= 0){
                             perror("Erreur d'ecritue dans le fichier ");
                             return EXIT_FAILURE;
                        }

                close(fdw);
                break;
            case 't':
                estbinaire = 0;
                for(int i = 0;i < dim ;i++)
                    for(int j = 0;j < dim ;j++)
                     //
        }
    }
}
