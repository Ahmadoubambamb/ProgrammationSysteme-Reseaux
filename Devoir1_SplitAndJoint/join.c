#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc , char *argv[]){
   if(argc < 3){
      printf("Usage : %s nomfichier ",argv[0]);
        return EXIT_FAILURE;
     }
      int *fdsrc = (int *)malloc(argc * sizeof(int));
      // on cree le fichier de destination
      char nomfd[255] , buf ;
      int nbread = 0;
      sprintf(nomfd,"Fichier_join");
      int fddest = open(nomfd , O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH);
   for(int i = 0;i < argc ;i++){
         fdsrc[i] = open(argv[i],O_RDONLY);
         do{
             nbread = read(fdsrc,&buf,sizeof(char));
             if(nbread > 0){
                 if(write(fddest,&buf,sizeof(char)) <= 0){
                     perror("Ecriture");
                    return EXIT_FAILURE;
                }

            }
        }while(nbread > 0);
  }
}
