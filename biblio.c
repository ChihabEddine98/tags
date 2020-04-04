#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <fcntl.h>
#include <string.h>
#include "biblio.h"


///  -----------------------------------------------------------------------------------
int isExist(char data[MAXLEN],char *tagName){
    const char s[2] = "#";
    char *token;

    /* get the first token */
    token = strtok(data,s);

    /* walk through other tokens */
    while( token != NULL ) {
        printf( " %s\n", token );
        if(strcmp(token,tagName)==0)
          return 1;
        token = strtok(NULL, s);
    }
    return 0;
}
void ajouter_tag_data(char data[MAXLEN],char *tag){

}


void set_tags(char *Path,char data[MAXLEN],char *tagName){
    int fd = open(Path, O_RDWR);
    char buf[30];
    sprintf(buf,"user.%s",tagName);
    if(setxattr(Path,"user.tags",data,sizeof(data),0) > -1){
        printf("tag set\n");

    } else {
        perror(" err set");
    }
}
void get_tags(char *Path,char *tagName){

    const char *fichier = Path;
    char buf_Tags[MAXLEN];
    char buf[30];
    sprintf(buf,"user.%s",tagName);
    if (getxattr(fichier, buf, buf_Tags, sizeof(buf_Tags)))
    {
        printf("value of tag %s : %s\n", buf, buf_Tags);

    }
}

