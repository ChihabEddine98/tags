#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <fcntl.h>
#include <string.h>
int main() {
    const char * fichier = "../test.txt";
    
    int fd = open("../test.txt", O_RDWR);

   if(setxattr("test.txt","user.couleur1","bleu",sizeof("bleu"),0) > -1){
        printf("tag set\n");

    } else {
        perror(" err set");
    }

    return 0;
}