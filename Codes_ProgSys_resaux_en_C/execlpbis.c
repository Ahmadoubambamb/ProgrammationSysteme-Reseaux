#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
void execute(char *argv[]){
    pid_t pidfils = fork();
    switch(pidfils){
        case 0:
            execvp(argv[0],argv);
            printf("erreur de execvp");
        default:
            wait(NULL);
    }
}

char ** build(char *cmd){
    char ** buff = (char **)malloc(255*sizeof(char *));
    for(int i =0 i < 255 ;i++)
        buff[i] = NULL ;
    char cmdbuff[255];
    strcpy(cmdbuff,cmd);
    int i = 0;
    argvbis[i] = strtok(cmdbuff , " ");
    while(argvbis[i] != NULL && (i < 255)){
      i++;
    }
}
int main(int argc , char *argv[])
{
//    printf("Nouvelle commande ls\n");
//     execlp("ls","ls","-l","-a",NULL);
// //     printf("erreur de exexc");
//     char * args[] = {"ls", "-l", "-a"};
//     execvp("ls",args);
//     printf("erreur de execv");


 }
