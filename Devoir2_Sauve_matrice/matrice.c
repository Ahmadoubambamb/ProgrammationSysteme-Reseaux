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
 int dim ,opt;
 int estbinaire = 0;// pour savoir si le contenu a afficher dans l'option -a est
                              //dans un fichier binaire ou text

  char nomfic[255] ;// doit contenir le nom du fichier passer en argument
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
                 // on on alloue la matrice de dimension dim passer en argument dans l'option -d
                matrix = (int **)malloc(dim * sizeof(int*));
                for(int i = 0;i < dim;i++)
                    matrix[i] = (int*)malloc(dim * sizeof(int));
                break;

            case 'c':
                printf("creation d'une matrice aleatoire !\n");
                for(int i =0 ;i < dim ;i++)
                    for(int j = 0;j < dim ; j++)
                        matrix[i][j] = rand()%100 + 1; //nombre aleatoire entre 0 et 100
                break;

            case 'a':
                if(estbinaire) //affichage extrait dans le ficher binaire
                {
                printf("affichage de la matrice extrait dans le fichier binaire %s:\n",nomfic);
                 int  nbread = 0 , buf;
                     int fdrB = open(nomfic ,O_RDONLY);
                     if(fdrB == -1){
                         perror("Ouverture pour lire");
                         return EXIT_FAILURE;
                    }
                    int i = 0;
                 do{ nbread = read(fdrB, &buf, sizeof(int));
                     i++;
                     if(nbread > 0)
                     {  printf("%5d ",buf);
                         // si le rest de i div dim est null on va a la ligne pour afficher en format matrice
                      if(i%dim == 0)
                             printf("\n");
                     }

                   }while(nbread > 0);
                 close(fdrB);
                }
             else{ // extrait dans le ficher text pour afficher
                printf("affichage de la matrice extrait dans le fichier text %s:\n",nomfic);
                 int fdrT = open(nomfic , O_RDONLY);//Ouverture du fichier en mode lecture seul
                 char Buf;
                 while(read(fdrT ,&Buf ,sizeof(char)) > 0){
                     printf("%c",Buf);
                    }
                    close(fdrT);
                }

                        break;

            case 'f':
                // on garde le nom du fichier passer en argument dans l'option -f
                strcpy(nomfic,optarg);
                printf("creation du fichier %s ",optarg);
                // on cree le fichier uniquement sans l'Ouvrir
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
                 int fdwB = open(nomfic,O_WRONLY); //Ouverture en en ecriture seul
                 if(fdwB == -1)
                 { perror("Ouverture !");
                     return EXIT_FAILURE;
                 }

                for(int i = 0;i < dim ;i++)
                    for(int j = 0;j < dim ;j++)
                         if(write(fdwB , &matrix[i][j] , sizeof(int)) <= 0){
                             perror("Erreur d'ecriture dans le fichier ");
                             return EXIT_FAILURE;
                        }

                close(fdwB);
                break;

            case 't':
                estbinaire = 0;
                int fdwT = open(nomfic ,O_WRONLY);
                if(fdwT == -1){
                    fprintf(stderr,"erreur d'Ouverture");
                    return EXIT_FAILURE;
                }
               char enText[10] ;// pour contenir l'entier en format text
                for(int i = 0;i < dim ;i++){
                    for(int j = 0;j < dim ;j++){
                   int L = sprintf(enText,"%5d",matrix[i][j]);
                     if(write(fdwT ,enText,L) <= 0)
                     { perror("Erreur d'ecriture ");
                       return EXIT_FAILURE;
                     }
                    }
                  int L = sprintf(enText,"\n");
                    if(write(fdwT ,enText,L) <= 0)
                        { perror("Erreur d'ecriture2 ");
                       return EXIT_FAILURE;
                     }
                    }
                    break;
        }
    }
}
