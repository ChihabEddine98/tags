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
    char res[100];
    printf("Enter path to list files: ");

    int result = scanf("%99[^\n]%*c", path);
    if (result != 1)
        memcpy(path, "./", strlen("./"));

    listFilesRecursively(path);
    // addCategorie("./fichiertest/test2", "Color");
    // addTagInCategorie("./fichiertest/test2", "Color", "Blue");

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
            printf("%s\n", dp->d_name);

            if (contientTag(dp->d_name, "Blue") == 1)
                printf("%s\n", dp->d_name);
            // listTag("./fichiertest/test2/test.txt");

            // Construct new path from our base path
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            listFilesRecursively(path);
        }
    }

    closedir(dir);
}
