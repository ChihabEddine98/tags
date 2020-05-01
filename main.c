#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <fcntl.h>
#include <string.h>
#include <asm/errno.h>
#include "biblio.h"


int main()
{
    const char *fichier = "../teest";
   // addCategorie("../teest","all");
 //  addTagInCategorie("../teest","all","color1");
//removeTag(fichier,"adem");
 //  removeTagCategory("../teest","adem","lina");
   // supprimerCategorie(fichier,"adem");
  // if (contientTag(fichier,"aymen")==1) printf("\n rana hna hbb");
   //listTag(fichier);
   //lienEntreTags(fichier,"all","blue");
   lienhierarchique(fichier,"color1","blue");
   //char mot[]="Aymen";
    //low(mot);

/*
    char buff[MAXLEN];
    //int fd = open("../teest", O_RDWR);
    char tab[MAXLEN]="je suis une chaine decharactermotherfucker";

  //  set_tags("../test.txt",tab,"data");
  /*   if (setxattr("../teest", "user.tag9", tab, sizeof(tab), 0) > -1)
    {
        printf("tag set\n");
    }
    else
    {
        perror(" err set");
    }

  int size=listxattr(fichier, buff, sizeof(buff));
    Tags *list=malloc(sizeof(Tags));
    list->NbTags=0;
    list->sommet=NULL;
  printf("size =%d\n",size);
    if ( size> 0)
    {
       // char *mot=buff;
        //printf("tag names :%s  %d\n", mot, sizeof(mot));
        //printf("tag names :%s\n", buff[11]);


    }
    else
    {
        perror(" err list");
    }
    char buf_Tags[MAXLEN];
    int t=getxattr(fichier, "user.adem",buf_Tags, sizeof(buf_Tags));
    if (t){
      //  init_tags(tags,buf_Tags);
        //afficher(tags);
       // char *m=TagsToBuf(tags);
         //printf("value1 = %s \n",m);

        printf("value = %s size =%d\n",buf_Tags, t);
    }else{
        printf("sdf");
    }
  //  get_tags("../test.txt","data");

  */  return 0;

}