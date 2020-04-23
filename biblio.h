//
// Created by netbook on 04/04/2020.
//

#ifndef SYSTPROJET_BIBLIO_H
#define SYSTPROJET_BIBLIO_H
#define MAXLEN 256

///  ------------------- project structure ----------------------
typedef struct
{
    char tag[30];
    struct elem *suivant;
} Token;

typedef struct
{
    Token *sommet;
    int NbTags;
} Tags;

typedef struct {
    char** in;
    char** not_in;
    int in_size;
    int not_in_size;

} search_criteria_t;


/// -------------------------------------------------------------

int isExistTag(Tags tags, char *tagName);
char *TagsToBuf(Tags *tag);
void init_tags(Tags *tags, char buf[MAXLEN]);
void add(Tags *tags, char *tagName);
void deletTag(Tags *tags, char *tagName);
void set_tags(char *Path, char data[MAXLEN], char *tagName, int replace);
void get_tags(Tags *tags, char *Path, char *tagName);
void ListOfTags(Tags *tableau, char buff[MAXLEN], int size);
int findInList(Tags *tags, char *tagName);
void addCategorie(char *Path, char *tagName);
void addTagInCategorie(char *Path, char *category, char *tagName);
void supprimerCategorie(char *Path, char *category);
void removeTagCategory(char *Path, char *category, char *tagName);
void afficher(Tags *tags);
void listTag(char *Path);
void removeTag(char *Path, char *tagName);
int contientTag(char *Path, char *tag);
Tags *Allsoustags(char *Path, Tags *listcat);
int testCriteria(char *Path,search_criteria_t criteria);
void listFilesRecursively(char *basePath,search_criteria_t criteria);
void low(char str[40]);
#endif //SYSTPROJET_BIBLIO_H
