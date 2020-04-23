#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include "biblio.h"

void listFilesRecursively(char *path);

int main()
{
    // Directory path to list files
    char path[100];

    // Input path from user
    printf("Enter path to list files: ");
    fgets(path, sizeof(path), stdin);
    if (path[0] == '\n')
        memcpy(path, "./", strlen("./"));
    // addCategorie("./cmd.c", "Color");
    // addTagInCategorie("./cmd.c", "Color", "Blue");
    listFilesRecursively(path);

    return 0;
}

/**
 * Lists all files and sub-directories recursively 
 * considering path as base path.
 */
void listFilesRecursively(char *basePath)
{
    char path[1000];
    struct dirent *dp;

    DIR *dir = opendir(basePath);

    // Unable to open directory stream
    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            // printf("%d \n", contientTag(dp->d_name, "Blue"));
            if (contientTag(dp->d_name, "Blue") == 1)
                printf("%s\n", dp->d_name);
            // listTag(dp->d_name);

            // Construct new path from our base path
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            listFilesRecursively(path);
        }
    }

    closedir(dir);
}
