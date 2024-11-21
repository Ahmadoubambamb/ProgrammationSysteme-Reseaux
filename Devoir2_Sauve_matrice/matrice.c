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

/*des booleen  pour connaitre les option saisi d'avance pour rendre aleatoire
  la saisi des option*/
 int estbinaire = 0;
  int uneDimension = 0;
  int unFicher = 0;
  int matAleatoire = 0;
  int afficherMat = 0;
  char nomfic[255] ;// doit contenir le nom du fichier passer en argument
    while((opt = getopt(argc , argv , ":d:cabtf:")) != -1)
    {
        switch(opt)
        {
            case ':':
                printf("-%c attent un argument \n",optopt);
                exit(1);
                break;
            case '?':
                printf("option -%c inconnu \n",optopt);
                exit(2);
                break;

            case 'd':
                uneDimension = 1;
                  dim = atoi(optarg);
                break;

            case 'c':
                matAleatoire = 1;
                break;

            case 'a':
                afficherMat = 1;
                        break;

            case 'f':
                unFicher = 1;
                // on garde le nom du fichier passer en argument dans l'option -f
                strcpy(nomfic,optarg);
                break;

            case 'b':
                estbinaire = 1;
                break;

            case 't':
                estbinaire = 0;
                    break;
        }
    }
    if(uneDimension){
                 printf("alloction d'une matrice de taille %d\n",dim);
                 // on on alloue la matrice de dimension dim passer en argument dans l'option -d
                matrix = (int **)malloc(dim * sizeof(int*));
                for(int i = 0;i < dim;i++)
                    matrix[i] = (int*)calloc(dim , sizeof(int));

         }
         else{
             fprintf(stderr,"Vous devez donner une dimension");
             return EXIT_FAILURE;
        }
        if(matAleatoire){
          printf("creation d'une matrice aleatoire !\n");
                for(int i =0 ;i < dim ;i++)
                    for(int j = 0;j < dim ; j++)
                        matrix[i][j] = rand()%100 + 1; //nombre aleatoire entre 0 et 100
        }
        else{
            printf("Vous n'avez pas saisi l'option -c pour creation une matrice aleatoire saisissez la alors:\n");
            for(int i = 0;i < dim ;i++)
                for(int j = 0; j < dim; j++){
                    printf("M[%d][%d] = ",i,j);
                    scanf("%d",&matrix[i][j]);
                }
        }
        if(unFicher){
            printf("creation du fichier %s ",nomfic);
                // on cree le fichier uniquement sans l'Ouvrir
                int fd = open(nomfic, O_CREAT , S_IWUSR | S_IRUSR);
                if(fd == -1){
                   printf("a echouer !!?\n");
                    return EXIT_FAILURE;
                }
                printf("reussi avec succes !\n");
                close(fd);
        }
        else{
            printf("vous n'avez pas indiquer l'option -f\n");
        }
        if(estbinaire){
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
        }
        else{
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
        }
        if(afficherMat){
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
        }
    // liberation de la matrice
  if(matrix)
   { for(int i = 0;i < dim; i++)
        free(matrix[i]);
     free(matrix);
   }
    return 0;
}
