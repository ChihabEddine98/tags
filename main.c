#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <fcntl.h>
#include <string.h>
#include "biblio.h"

int main()
{
    const char *fichier = "../test.txt";
    char buff[MAXLEN];
    //int fd = open("../teest", O_RDWR);
    char tab[MAXLEN]="aymen";
    //set_tags("../test.txt",tab,"data");
    /*  if (setxattr("../teest", "user.tag4", tab, sizeof(tab), 0) > -1)
    {
        printf("tag set\n");
    }
    else
    {
        perror(" err set");
    }
*/
    // if (listxattr(fichier, buff, sizeof(buff)) > -1)
    // {
    //     printf("tag names :%s\n", buff);
    // }
    // else
    // {
    //     perror(" err list");
    // }

    listTag("./test.txt");



    //get_tags("../test.txt","data");
    return 0;
}