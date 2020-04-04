//
// Created by netbook on 04/04/2020.
//

#ifndef SYSTPROJET_BIBLIO_H
#define SYSTPROJET_BIBLIO_H
#define MAXLEN 1024


int isExist(char data[MAXLEN],char *tagName);
void set_tags(char *Path,char data[MAXLEN],char *tagName);
void get_tags(char *Path,char *tagName);




#endif //SYSTPROJET_BIBLIO_H
