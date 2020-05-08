#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <fcntl.h>
#include <string.h>
#include "biblio.h"
#include <dirent.h>
#include <ctype.h>
#include <sys/stat.h>
#include <unistd.h>

///  -----------------------------------------------------------------------------------
void low(char str[40])
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            str[i] = str[i] + 32;
        }
    }
    //printf("\n%s", str);
}
int isExistTag(Tags tags, char *tagName)
{

    /* get the first token */
    Token *token = tags.sommet;

    /* walk through other tokens */
    while (token != NULL)
    {
        if (strcmp(token->tag, tagName) == 0)
            return 1;
        token = token->suivant;
    }
    return 0;
}

void set_tags(char *Path, char data[MAXLEN], char *tagName, int replace)
{
    char buf[30];
    sprintf(buf, "user.%s", tagName);
    if (replace == 0)
    {
        char tab[MAXLEN] = "";
        if (setxattr(Path, buf, tab, sizeof(tab), 0) > -1)
        {
            printf("tag set\n");
        }
        else
        {
            perror(" err set");
        }
    }
    else
    { /// replace data

        //removexattr(Path,tagName);
        char tab[MAXLEN];

        int i;
        for (i = 0; i < strlen(data); i++)
        {
            //printf("c=%c\n", data[i]);
            tab[i] = data[i];
        }
        tab[i] = '\0';
        if (setxattr(Path, buf, tab, sizeof(tab), XATTR_REPLACE) > -1)
        {
            printf("tag modifier\n");
        }
        else
        {
            perror(" err set");
        }
    }
}
void add(Tags *tags, char *tagName)
{
    Token *token = malloc(sizeof(Token));
    strcpy(token->tag, tagName);
    token->suivant = tags->sommet;
    tags->sommet = token;
    tags->NbTags += 1;
    return;
}
void deletTag(Tags *tags, char *tagName)
{
    Token *token = tags->sommet;
    Token *pres = token;
    int find = 0;
    while (find == 0 && token != NULL)
    {
        if (strcmp(token->tag, tagName) == 0)
        {
            find = 1;
        }
        else
        {
            pres = token;
            token = token->suivant;
        }
    }
    if (find)
    {
        tags->NbTags -= 1;
        if (pres == token)
            tags->sommet = token->suivant;
        else
            pres->suivant = token->suivant;
    }
}
void init_tags(Tags *tags, char buf[MAXLEN])
{
    const char s[2] = "#";
    char *token;
    if (buf != "")
    {
        /* get the first token */
        token = strtok(buf, s);

        /* walk through other tokens */
        while (token != NULL)
        {
            add(tags, token);
            token = strtok(NULL, s);
        }
    }
}
void get_tags(Tags *tags, char *Path, char *tagName)
{

    const char *fichier = Path;
    char buf_Tags[MAXLEN];
    char buf[30];
    sprintf(buf, "user.%s", tagName);
    if (getxattr(fichier, buf, buf_Tags, sizeof(buf_Tags)))
    {
        init_tags(tags, buf_Tags);
    }
    else
    {
        red();
        printf("Error");
    }
}
void ListOfTags(Tags *tableau, char buff[MAXLEN], int size)
{

    int index = 0;
    while (index < (size - 1))
    {
        char *mot = &buff[index];
        char *m = &mot[5];
        // printf("mot =%s and %d\n",m,strlen(m));
        add(tableau, m);
        index += strlen(m) + 6;
    }
}
int findInList(Tags *tags, char *tagName)
{
    Token *token = tags->sommet;
    while (token != NULL)
    {
        if (strcmp(token->tag, tagName) == 0)
            return 1;
        token = token->suivant;
    }
    return 0;
}
void addCategorie(char *Path, char *tagName)
{
    const char *fichier = Path;
    char buff[MAXLEN];
    int size = listxattr(fichier, buff, sizeof(buff));
    Tags *list = malloc(sizeof(Tags));
    list->NbTags = 0;
    list->sommet = NULL;
    if (size > 0)
    {
        ListOfTags(list, buff, size);
    }
    if (findInList(list, tagName))
    {
        red();
        printf("Error , category exist");
    }
    else
    { // new categorie
        set_tags(Path, "", tagName, 0);
    }
}
char *TagsToBuf(Tags *tags)
{
    Token *token = tags->sommet;
    char *data = malloc(sizeof(char) * MAXLEN);
    while (token != NULL)
    {
        strcat(token->tag, "#");
        strcat(data, token->tag);
        //printf("tag :%s\n", token->tag);
        token = token->suivant;
    }
    //printf("\ndata :%s\n", data);
    return data;
}

void addTagInCategorie(char *Path, char *category, char *tagName)
{

    const char *fichier = Path;
    char buff[MAXLEN];
    int size = listxattr(fichier, buff, sizeof(buff));
    Tags *list = malloc(sizeof(Tags));
    list->NbTags = 0;
    list->sommet = NULL;
    if (size > 0)
    {
        ListOfTags(list, buff, size);
    }
    if (findInList(list, category))
    {
        Tags *listOfTags = malloc(sizeof(Tags));
        listOfTags->NbTags = 0;
        listOfTags->sommet = NULL;
        get_tags(listOfTags, Path, category);
        if (findInList(listOfTags, tagName) == 0)
        {
            add(listOfTags, tagName); /// add the tag to the list of tags
            char *buffer;
            buffer = TagsToBuf(listOfTags);
            //printf("%s\n", buffer);
            set_tags(Path, buffer, category, 1);
        }
        else
            printf("\ntag exist\n");
    }
    else
    {
        red();
        printf("Error , category doesn't exist");
    }
}

void removeTagCategory(char *Path, char *category, char *tagName)
{
    const char *fichier = Path;
    char buff[MAXLEN];
    int size = listxattr(fichier, buff, sizeof(buff));
    Tags *list = malloc(sizeof(Tags));
    list->NbTags = 0;
    list->sommet = NULL;
    if (size > 0)
    {
        ListOfTags(list, buff, size);
    }
    if (findInList(list, category))
    {
        Tags *listOfTags = malloc(sizeof(Tags));
        listOfTags->NbTags = 0;
        listOfTags->sommet = NULL;
        get_tags(listOfTags, Path, category);
        deletTag(listOfTags, tagName);
        char *buffer;
        buffer = TagsToBuf(listOfTags);
        //printf("%s\n", buffer);
        set_tags(Path, buffer, category, 1);
    }
    else
    {
        green();
        printf("Error , category doesn't exist");
    }
}
void removeTag(char *Path, char *tagName)
{
    const char *fichier = Path;
    char buff[MAXLEN];
    int size = listxattr(fichier, buff, sizeof(buff));
    Tags *list = malloc(sizeof(Tags));
    list->NbTags = 0;
    list->sommet = NULL;
    if (size > 0)
    {
        ListOfTags(list, buff, size);
    }
    Token *tmp = list->sommet;
    int cnt = 0;
    while (tmp != NULL && cnt == 0)
    {
        Tags *listOfTags = malloc(sizeof(Tags));
        listOfTags->NbTags = 0;
        listOfTags->sommet = NULL;
        get_tags(listOfTags, Path, tmp->tag);
        if (findInList(listOfTags, tagName))
        {
           // printf("\nremove\n");
            deletTag(listOfTags, tagName);
            char *buffer;
            buffer = TagsToBuf(listOfTags);
            //printf("%s\n", buffer);
            set_tags(Path, buffer, tmp->tag, 1);
            cnt = 1;
        }
        else
            tmp = tmp->suivant;
    }
}

void supprimerCategorie(char *Path, char *category)
{
    const char *fichier = Path;
    char buf[30];
    sprintf(buf, "user.%s", category);
    int supr = removexattr(fichier, buf);
    if (supr == 0)
    {   green();
        printf("success ,supprimer Categorie ");
    }
    else{
        red();
        printf("Error ,supprimer Categorie ");
}
}

void afficher(Tags *tags)
{

    Token *token = tags->sommet;
    while (token != NULL)
    {
        printf("  - tag :%s\n", token->tag);
        token = token->suivant;
    }
}
void afficherhierarchique(Tags *tags){
    Token *token = tags->sommet;
    printf("\n");

    while (token != NULL)
    {
        printf("%s", token->tag);
        token = token->suivant;
        if(token!=NULL)
            printf("/");
    }
    printf("\n");

}

void listTag(char *Path)
{
    const char *fichier = Path;
    char buff[MAXLEN];
    int size = listxattr(fichier, buff, sizeof(buff));
    Tags *list = malloc(sizeof(Tags));
    list->NbTags = 0;
    list->sommet = NULL;
    if (size > 0)
    {
        ListOfTags(list, buff, size);
    }
    Token *token = list->sommet;
    if (token == NULL)
    {
        printf("\nList vide \n ");
        return;
    }
    while (token != NULL)
    {
        red();
        printf(" Categorie :");
        yellow();
        printf("%s\n", token->tag);
        Tags *listOfTags = malloc(sizeof(Tags));
        listOfTags->NbTags = 0;
        listOfTags->sommet = NULL;
        get_tags(listOfTags, Path, token->tag);
        afficher(listOfTags);
        token = token->suivant;
    }
}
void addListInLIst(Tags *res, Tags *list)
{
    Token *token = list->sommet;
    while (token != NULL)
    {
        add(res, token->tag);
        token = token->suivant;
    }
}
Tags *Allsoustags2(char *Path, Tags *listcat)
{
    Tags *res = malloc(sizeof(Tags));
    res->NbTags = 0;
    res->sommet = NULL;
    Token *tok = listcat->sommet;
    while (tok != NULL)
    {
        Tags *listOfTags = malloc(sizeof(Tags));
        listOfTags->NbTags = 0;
        listOfTags->sommet = NULL;
        get_tags(listOfTags, Path, tok->tag);
        addListInLIst(res, listOfTags);
        tok = tok->suivant;
    }
    return res;
}
Tags *Allsoustags(char *Path, Tags *listcat)
{
    Tags *res = malloc(sizeof(Tags));
    res->NbTags = 0;
    res->sommet = NULL;
    Token *tok = listcat->sommet;
    while (tok != NULL)
    {
        Tags *listOfTags = malloc(sizeof(Tags));
        listOfTags->NbTags = 0;
        listOfTags->sommet = NULL;
        get_tags(listOfTags, Path, tok->tag);
        add(res, tok->tag);
        addListInLIst(res, listOfTags);
        tok = tok->suivant;
    }
    return res;
}

int testCriteria(char *Path, search_criteria_t criteria)
{
    const char *fichier = Path;
    char buff[MAXLEN];
    int size = listxattr(fichier, buff, sizeof(buff));
    Tags *listcat = malloc(sizeof(Tags));
    listcat->NbTags = 0;
    listcat->sommet = NULL;
    if (size > 0)
    {
        ListOfTags(listcat, buff, size);
    }
    if (listcat->sommet == NULL)
        return 0;
    Tags *listall = Allsoustags(Path, listcat);
    //printf(" \n int : %d  and name %s\n",listall->NbTags,Path);
    for (size_t i = 0; i < criteria.in_size; i++)
    {
        if (findInList(listall, criteria.in[i]) == 0)
            return 0;
    }

    for (size_t j = 0; j < criteria.not_in_size; j++)
    {
        if (findInList(listall, criteria.not_in[j]) == 1)
            return 0;
    }

    return 1;
}
char *paireTag(char *Path,char *tag1){
    const char *fichier = Path;
    char buff[MAXLEN];
    int size = listxattr(fichier, buff, sizeof(buff));
    Tags *list = malloc(sizeof(Tags));
    list->NbTags = 0;
    list->sommet = NULL;
    if (size > 0)
    {
        ListOfTags(list, buff, size);
    }
    Token *token = list->sommet;
    if (token == NULL)
    {
        return "";
    }
    while (token != NULL)
    {
        Tags *listOfTags = malloc(sizeof(Tags));
        listOfTags->NbTags = 0;
        listOfTags->sommet = NULL;
        get_tags(listOfTags, Path, token->tag);
        if(findInList(listOfTags,tag1)) return token->tag;
        token = token->suivant;
    }
    return "";
}
Tags *lienEntreTags(char *Path,char *tag1,char *tag2){
    const char *fichier = Path;
    char buff[MAXLEN];
    int size = listxattr(fichier, buff, sizeof(buff));
    Tags *listcat = malloc(sizeof(Tags));
    listcat->NbTags = 0;
    listcat->sommet = NULL;
    if (size > 0)
    {
        ListOfTags(listcat, buff, size);
    }
    if (listcat->sommet == NULL)
        return NULL;
    Tags *listall = Allsoustags2(Path, listcat);
    int count=1;
    char *tagtmp=malloc(45);
    memcpy(tagtmp,tag2,strlen(tag2));
    Tags *res = malloc(sizeof(Tags));
    res->NbTags = 0;
    res->sommet = NULL;
    for (int j = 0; j <10 ; j++) {
        if(strcmp(tagtmp,tag1)==0){
            add(res,tag1);
            break;
        }
        else if(findInList(listall,tagtmp)){
            add(res,tagtmp);
            if(strcmp(paireTag(Path,tagtmp),"")==0)
                return NULL;
            strcpy(tagtmp,paireTag(Path,tagtmp));
        } else {
            return NULL;
        }
    }
    return res;

}
void lienhierarchique(char *Path,char *tag1,char *tag2){
    Tags *list1=lienEntreTags(Path,tag1,tag2);
    Tags *list2=lienEntreTags(Path,tag2,tag1);
    if(list1!=NULL){
     afficherhierarchique(list1);
    }else if (list2!=NULL){
        afficherhierarchique(list2);
    }else printf("\nil n'y a pas de lien");
}

void listFilesRecursively(char *basePath, search_criteria_t criteria)
{
    char path[1000];
    struct dirent *dp;
    int inodes[10000];
    int cpt = 0;
    struct stat res1;

    DIR *dir = opendir(basePath);

    // Unable to open directory stream
    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {

        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {

            if (testCriteria(dp->d_name, criteria) == 1)
            {
                stat(dp->d_name, &res1);
                if (existe(res1.st_ino, cpt, inodes) == 0)
                {
                    printf("{ %s } satisfy the criteria ! \n", dp->d_name);
                    inodes[cpt] = res1.st_ino;
                    cpt++;
                }
            }
            // listTag("./fichiertest/test2/test.txt");

            // Construct new path from our base path
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            listFilesRecursively(path, criteria);
        }
    }

    closedir(dir);
}
int existe(int inode, int cpt, int tab[])
{
    for (int i = 0; i < cpt; i++)
    {
        if (tab[i] == inode)
        {
            return 1;
        }
    }
    return 0;
}
void red () {
    printf("\033[1;31m");
}
void blue () {
    printf("\033[0;34m");
}
void color1 () {
    printf("\033[1;36m");
}
void color3 () {
    printf("\033[0;35m");
}

void color2() {
    printf("\033[1;32m");
}
void yellow() {
    printf("\033[1;33m");
}
void green(){
    printf("\033[0;32m");
}
void reset () {
    printf("\033[0m");
}