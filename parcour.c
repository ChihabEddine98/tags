#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include "biblio.h"
int main(int argc, char *argv[])
{
    // if (argc > 1)
    // {
    //     struct stat sb;
    //     stat(argv[1], &sb);
    //     printf("File inode: \t\t%d\n", sb.st_ino);
    // }
    DIR *rep = opendir("./");
    if (rep == NULL)
        perror("Erreur : ");

    struct dirent *fichierLu = NULL;

    struct stat sb1;
    struct stat sb2;

    // fichierLu = readdir(rep);

    // if (stat(fichierLu->d_name, &sb1) == -1)
    // {
    //     perror("stat");
    // }

    // printf("%d %s\n", sb1.st_ino, fichierLu->d_name);
    // if (stat("./", &sb1) == -1)
    // {
    //     perror("stat");
    // }
    addCategorie("./cmd.c", "Color");
    addTagInCategorie("./cmd.c", "Color", "Blue");
    while ((fichierLu = readdir(rep)) != NULL)
    {
        if (stat(fichierLu->d_name, &sb1) == -1)
        {
            perror("stat");
        }
        // if (sb1.st_ino == currentPid)
        // {
        //     printf("%s is the current working directory ", fichierLu->d_name);
        // }
        printf("%s\n", fichierLu->d_name);
        listTag(fichierLu->d_name);
    }

    return 1;
}
