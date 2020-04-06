#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <fcntl.h>
#include <string.h>
#include "biblio.h"


///  -----------------------------------------------------------------------------------
int isExistTag(Tags tags,char *tagName){


    /* get the first token */
    Token *token=tags.sommet;

    /* walk through other tokens */
    while( token != NULL ) {
        if(strcmp(token->tag,tagName)==0)
          return 1;
        token = token->suivant;
    }
    return 0;
}



void set_tags(char *Path,char data[MAXLEN],char *tagName,int replace){
    int fd = open(Path, O_RDWR);
    char buf[30];
    sprintf(buf,"user.%s",tagName);
    if(replace==0) {
        if (setxattr(Path, buf, data, sizeof(data), XATTR_CREATE) > -1) {
            printf("tag set\n");

        } else {
            perror(" err set");
        }
    }
    else{/// replace data
    printf("replace data =%s in the fnct set\n",data);
        if (setxattr(Path, buf,data, sizeof(data), XATTR_REPLACE) > -1) {
            printf("tag modifier\n");

        } else {
            perror(" err set");
        }
    }
}
void add(Tags *tags,char *tagName){
    Token *token=malloc(sizeof(Token));
    strcpy(token->tag,tagName);
    token->suivant=tags->sommet;
    tags->sommet=token;
    tags->NbTags+=1;
    return;
}
void init_tags(Tags *tags,char buf[MAXLEN]){
    const char s[2] = "#";
    char *token;
    printf("data buf %s\n",buf);
    if(buf!="") {
        /* get the first token */
        token = strtok(buf, s);

        /* walk through other tokens */
        while (token != NULL) {
            printf(" %s\n", token);
            add(tags, token);
            token = strtok(NULL, s);
        }
    }

}
void get_tags(Tags *tags,char *Path,char *tagName){

    const char *fichier = Path;
    char buf_Tags[MAXLEN];
    char buf[30];
    sprintf(buf,"user.%s",tagName);
    if (getxattr(fichier, buf, buf_Tags, sizeof(buf_Tags)))
    {
        printf("value of tag %s : %s\n", buf, buf_Tags);
        init_tags(tags,buf_Tags);

    }else{
        printf(" Error ");
    }
}
void ListOfTags(Tags *tableau,char buff[MAXLEN],int size){
    char *mot;
    int index=0;
    while(index<size){
        mot=&buff[index];
        char *m=&mot[5];
        add(tableau,m);
        index+= sizeof(mot)+2;
    }

}
int findCateg(Tags *tags,char *tagName){
    Token *token=tags->sommet;
    while(token!=NULL){
        if(strcmp(token->tag,tagName)==0) return 1;
        token=token->suivant;
    }
    return 0;
}
void addCategorie(char *Path,char *tagName){
    const char *fichier =Path;
    char buff[MAXLEN];
    int size=listxattr(fichier, buff, sizeof(buff));
    Tags *list=malloc(sizeof(Tags));
    list->NbTags=0;
    list->sommet=NULL;
    if(size>0){
        ListOfTags(list,buff,size);
    }
    if(findCateg(list,tagName)){
        printf("Error , category exist");
    }
    else{// new categorie
      set_tags(Path,"",tagName,0);
    }
}
char *TagsToBuf(Tags *tags){
    Token *token=tags->sommet;
    char *data=malloc(sizeof(MAXLEN));
    while(token!=NULL){
        strcat(token->tag, "#");
        strcat(data,token->tag);
        printf("in fn tagtoBuf %s\n",token->tag);
        token=token->suivant;
    }
    return data;

}

void addTagInCategorie(char *Path,char *category,char *tagName){

    const char *fichier =Path;
    char buff[MAXLEN];
    int size=listxattr(fichier, buff, sizeof(buff));
    Tags *list=malloc(sizeof(Tags));
    list->NbTags=0;
    list->sommet=NULL;
    if(size>0){
        ListOfTags(list,buff,size);
    }
    if(findCateg(list,category)){
        Tags *listOfTags=malloc(sizeof(Tags));
        listOfTags->NbTags=0;
        listOfTags->sommet=NULL;
        get_tags(listOfTags,Path,category);
        add(listOfTags,tagName);   /// add the tag to the list of tags
        char *buffer;
        buffer=TagsToBuf(listOfTags);
        printf("%s\n",buffer);
       /* char Buf[MAXLEN];
        int i;
        for (i = 0; i <strlen(buffer) ; i++) {
            Buf[i]=buffer[i];
        }
        Buf[i]='\0';
        printf("buf at last %s\n",Buf);
        */
        set_tags(Path,buffer,category,1);
    }
    else{// new categorie
        printf("Error , category doesn't exist");
    }
}

