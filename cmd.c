#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "biblio.h"
#include "cmd.h"

char* str_splitBetweenParentheses(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }
      
    return result[1];
}
char *iterate(char *p, const char *d, const size_t len)
{   
   while(p!=NULL && *p && memcmp(p, d, len)==0)
   {
      memset(p, 0x0, len);
      p+=len;    
   }
   return p;
}
uint8_t strContains(char* string, char* toFind)
{
    uint8_t slen = strlen(string);
    uint8_t tFlen = strlen(toFind);
    uint8_t found = 0;

    if( slen >= tFlen )
    {
        for(uint8_t s=0, t=0; s<slen; s++)
        {
            do{

                if( string[s] == toFind[t] )
                {
                    if( ++found == tFlen ) return 1;
                    s++;
                    t++;
                }
                else { s -= found; found=0; t=0; }

              }while(found);
        }
        return 0;
    }
    else return -1;
}
char* replace_char(char* str, char find, char replace){
    char *current_pos = strchr(str,find);
    while (current_pos){
        *current_pos = replace;
        current_pos = strchr(current_pos,find);
    }
    return str;
}

char *ltrim(char *s)
{
    while(isspace(*s)) s++;
    return s;
}

char *rtrim(char *s)
{
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

char *trim(char *s)
{
    return rtrim(ltrim(s));
}

search_criteria_t tokenize( char **result, char *working, const char *src, const char *delim)
{
     int i=0;
     char *p=NULL;
     size_t len=strlen(delim);     
     strcpy(working, src);

     p=working;
     for(result[i]=NULL, p=iterate(p, delim, len); p!=NULL && *p; p=iterate(p, delim, len) )
     {
         result[i++]=p;
         result[i]=NULL;
         p=strstr(p, delim);
     }

     int cpt=i;
     search_criteria_t search_criteria_result;
     search_criteria_result.in=malloc(cpt+1);
     search_criteria_result.not_in=malloc(cpt+1);
     search_criteria_result.in_size=0;
     search_criteria_result.not_in_size=0;
  
     i=0;
     size_t j=0;
     size_t k=0;
     char *tmpp;
    for (int l = 0; l <cpt ; l++) {
        tmpp=trim(result[l]);
        result[l]=tmpp;
    }
     for (k = 0;k < cpt;k++)
     {
         printf("\n K=[%s]",result[k]);


       if(strstr(result[k],"Non") || strstr(result[k],"NON")|| strstr(result[k],"non")
       || strstr(result[k],"Not") || strstr(result[k],"NOT")|| strstr(result[k],"not")
       || strstr(result[k],"Pas") || strstr(result[k],"PAS")|| strstr(result[k],"pas") )
       {
          char* s=str_splitBetweenParentheses(result[k],'(');
          char *motifNot=malloc(strlen(s));
          motifNot=s;

          motifNot[strlen(s)-1]='\0';
          if (motifNot[strlen(s)-1]==')')
          {
            motifNot[strlen(s)-1]='\0';
          }
          search_criteria_result.not_in[i]=motifNot;
         search_criteria_result.not_in_size+=1;
         i++;

        }
        else
        {
          
          search_criteria_result.in[j]=replace_char(result[k],' ','\0');
         search_criteria_result.in_size+=1;
         j++;
        }
        

       
     }
     
     //free(&search_criteria_result);

     return search_criteria_result;
}

void printCriteriaT(search_criteria_t criteria)
{
  printf("\n Searched for :\n");
  for (size_t i = 0; i < criteria.in_size; i++)
  {
    printf("-- %s --\n",criteria.in[i]);
  }
  
  printf("\n And Not  :\n");
  for (size_t i = 0; i < criteria.not_in_size; i++)
  {
    printf("-- %s --\n",criteria.not_in[i]);
  }
}

  
void menu()
{
  char fichier[85];
    char catName[45];
    char tagNAme[45];
    char tagNAme2[45];
    color3();
    printf("\n\n\t\tSysteme project - Best place to learn\n\n\n");
    int choice, num, i;
    char ch;
    while(1)
    {
        color1();
        printf("\n1. ajouter catégorie  \n");
        printf("2. ajouter tag dans catégorie\n");
        printf("3. supprimer categorie\n");
        printf("4. supprimer tag dans catégorie \n");
        printf("5. supprimer tag\n");
        printf("6. lien hiérarchique entre deux tag\n");
        printf("7. Afficher les Tags\n");
        printf("8. Exit \n\n\n");
        yellow();
        printf("Enter your choice :  ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                color2();
                printf("le chemin du fichier:\n");
                scanf("%s", fichier);
                printf("nom de categorie:\n");
                scanf("%s", catName);
                printf("%s",fichier);
                addCategorie(fichier,catName);
                printf("\n");
                getchar();

                break;

            case 2:
                color2();
                printf("le chemin du fichier:\n");
                scanf("%s", fichier);
                printf("nom de categorie:\n");
                scanf("%s", catName);
                printf("nom de tag :\n");
                scanf("%s", tagNAme);
                addTagInCategorie(fichier,catName,tagNAme);

                break;
            case 3:
                color2();
                printf("le chemin du fichier:\n");
                scanf("%s", fichier);
                printf("nom de categorie :\n");
                scanf("%s", catName);
                supprimerCategorie(fichier,catName);

                break;
            case 4:
                color2();
                printf("le chemin du fichier:\n");
                scanf("%s", fichier);
                printf("nom de categorie :\n");
                scanf("%s", catName);
                printf("nom de tag :\n");
                scanf("%s", tagNAme);
                removeTagCategory(fichier,catName,tagNAme);

                break;
            case 5:
                color2();
                printf("le chemin du fichier:\n");
                scanf("%s", fichier);
                printf("nom de tag :\n");
                scanf("%s", tagNAme);
                removeTag(fichier,tagNAme);

                break;
            case 6:
                color2();
                printf("le chemin du fichier:\n");
                scanf("%s", fichier);
                printf("nom de tag 1:\n");
                scanf("%s", tagNAme);
                printf("nom de tag 2:\n");
                scanf("%s", tagNAme2);
                lienhierarchique(fichier,tagNAme,tagNAme2);

                break;
            case 7:
                color2();
                printf("le chemin du fichier:\n");
                scanf("%s", fichier);
                printf("\n\n");
                listTag(fichier);
                printf("\n\n");

                break;

            case 8:
                blue();
                printf("\n\n\t\t\tCoding is Fun !\n\n\n");
                exit(0);    // terminates the complete program execution
            default:
                red();
                printf("default\n\n");
        }
    }
    printf("\n\n\t\t\tCoding is Fun !\n\n\n");
    reset();
 
}

/* Parse a single option. */
static error_t parse_opt (int key, char *arg, struct argp_state *state)
{
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
  struct arguments *arguments = state->input;

  switch (key)
    {
      //  Add a tag
    case 'a': 
      arguments->add_tag = arg;
      break;
      //  Delete a tag
    case 'd':
      arguments->rm_tag = arg;
      break;
      //  Add a category
    case 'c': 
      arguments->add_category = arg;
      break;
      //  Delete a category
    case 'x': 
      arguments->rm_category = arg;
      break;
      //  Search with criteria
    case 's': 
      arguments->search_files_criteria = arg;
      arguments->args[0]="";
      break;
    
    case 'l': 
      arguments->search_tags_criteria = arg;
      break;
    case 'o':
      arguments->output_file = arg;
      break;

    case ARGP_KEY_ARG:
      if (state->arg_num > 1)
        /* Too many arguments. */
        argp_usage (state);

      arguments->args[state->arg_num] = arg;

      break;

    case ARGP_KEY_END:
      if (state->arg_num < 0)
        /* Not enough arguments. */
        argp_usage (state);
      break;

    default:
      return ARGP_ERR_UNKNOWN;
    }



  return 0;
}




/* Our argp parser. */
static struct argp argp = { options, parse_opt, args_doc, doc };

int main (int argc, char **argv)
{
  
  struct arguments arguments;
  char *catego_tmp=malloc((size_t)(MAX_STRING+1));

  /* Default values. */
  arguments.add_tag = 0;
  arguments.rm_tag = 0;
  arguments.add_category = 0;
  arguments.rm_category = 0;
  arguments.search_files_criteria=0;
  arguments.search_tags_criteria=0;
  arguments.output_file = "-";

  /* Parse our arguments; every option seen by parse_opt will
     be reflected in arguments. */
  argp_parse (&argp, argc, argv, 0, 0, &arguments);

  // MENU HERE !
  if (!arguments.rm_tag && !arguments.rm_category 
      && !arguments.add_tag && !arguments.search_files_criteria 
      && !arguments.search_tags_criteria && !arguments.add_category)
  {
    menu();
  }

  
  // Case of tag -d TAG -c CATEGORY file.txt
  if(arguments.rm_tag)
  {
     // Case -c CATEGORY
    if(arguments.add_category)
    {
      removeTagCategory(arguments.args[0],arguments.add_category,arguments.rm_tag);
    }
    else
    {
      removeTag(arguments.args[0],arguments.rm_tag);
    }
    
    
    listTag(arguments.args[0]);
  }

  
  // Case of tag -x CATEGORY file.txt
  if(arguments.rm_category)
  {
    printf("\n Are you sure ? (y/n)");
    printf("\n>>");
    scanf("%[^'\n']s",catego_tmp);
    low(catego_tmp);
    if(strcmp(catego_tmp,"y")== 0 || strcmp(catego_tmp,"yes")== 0)
    {
      supprimerCategorie(arguments.args[0],arguments.rm_category);
    } 
    printf("\n");
    listTag(arguments.args[0]);
  }

  // Case of tag -a TAG -c CATEGORY file.txt
  if(arguments.add_tag)
  {
      // Case ok !
      if(arguments.add_category)
      { 
        addTagInCategorie(arguments.args[0],arguments.add_category,arguments.add_tag);
      }
      else
      {
        printf(" Enter category [default: %s]\n",arguments.add_tag);
        scanf("%[^'\n']s",catego_tmp);

        if(strcmp(catego_tmp,"")== 0)
        {
            arguments.add_category=arguments.add_tag;
        } 
        else
        {
          arguments.add_category=catego_tmp;
        }

        addCategorie(arguments.args[0],arguments.add_category);
        addTagInCategorie(arguments.args[0],arguments.add_category,arguments.add_tag);

      }

      listTag(arguments.args[0]);
      
  }


  char delimit[]=" \t\r\n\v\fet ET and"; // 2) POSIX whitespace characters
  int i = 0, j = 0;

  // Case of tag -s "Criteria !" file.txt

  if (arguments.search_files_criteria)
  {
    printf("\n searching !\n---------------\n  %s  \n",arguments.search_files_criteria);
    char** res=malloc(1000);
    char* w=malloc(1000);
    search_criteria_t search_criteria_result =tokenize(res,w,arguments.search_files_criteria,"et");
  
    printCriteriaT(search_criteria_result);

    listFilesRecursively(".",search_criteria_result);


    free(res);
    free(w);
    
    
  }


  // Case of tag -l file.txt

  if (arguments.search_tags_criteria)
  {
    listTag(arguments.search_tags_criteria);
  }
  

  // printf ("FILE = %s\nADDED_TAG = %s\n"
  //         "REMOVED_TAG = %s\nADDED_CATEGORY = %s\n",
  //         arguments.args[0],
  //         arguments.add_tag,
  //         arguments.rm_tag ? arguments.rm_tag:"no_rm",
  //         arguments.add_category? arguments.add_category:"no_add_category");

  exit (0);
}