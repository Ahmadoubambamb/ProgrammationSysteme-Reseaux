#ifndef UTILS_H_
#define UTILS_H_

struct infofile{
    char nomfichier[255];
    int taille ;
    int mode;
};

struct bloc_data{
    int taille ;
    char data[4096];
};


#endif
