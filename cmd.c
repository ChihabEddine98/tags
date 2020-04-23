#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "cmd.h"
#include "biblio.h"

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
      if (state->arg_num < 1)
        /* Not enough arguments. */
        argp_usage (state);
      break;

    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
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
           
     for (k = 0;k < cpt;k++)
     {


      //  if(strstr(result[i],"Non") || strstr(result[i],"NON")|| strContains(result[i],"non") 
      //  || strstr(result[i],"Not") || strstr(result[i],"NOT")|| strstr(result[i],"not")
      //  || strstr(result[i],"Pas") || strstr(result[i],"PAS")|| strstr(result[i],"pas") ) 
        if(strContains(result[k],"non"))
       {
          char *justNot=&result[k][5];
         //char motifNot[strlen(justNot)-1]; 
        //  for (size_t j = 0; j < strlen(justNot)-2; j++) 
        //  {
        //     motifNot[j]=justNot[j];
        //  }
        //  motifNot[strlen(justNot)-2]='\0';

        //  printf("\n motif == %s ==",motifNot);
        //  search_criteria_result.not_in[i]=malloc(sizeof(motifNot));
        //  search_criteria_result.not_in[i]=motifNot;
        //  printf("\n == %s ==",search_criteria_result.not_in[i]);

        //  search_criteria_result.not_in_size+=1;


        //  char motifNot[strlen(justNot)-1]; 
        //  search_criteria_result.not_in[i]=malloc(strlen(justNot)-1);
        //  for (size_t j = 0; j < strlen(justNot)-2; j++) 
        //  {
        //     search_criteria_result.not_in[i][j]=justNot[j];
        //  }
        // search_criteria_result.not_in[i][strlen(justNot)-2]='\0';
        // printf("\n == %s ==",search_criteria_result.not_in[i]);
        // search_criteria_result.not_in_size+=1;
          char *motifNot=malloc(strlen(justNot)-1);
          strncpy ( motifNot, &result[k][5],strlen(justNot)-2);
          motifNot[strlen(justNot)-2]='\0';
          // search_criteria_result.not_in[i]=malloc(sizeof(motifNot));
          search_criteria_result.not_in[i]=motifNot;
         search_criteria_result.not_in_size+=1;
         i++;

        }
        else
        {
          search_criteria_result.in[j]=result[k];
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
  arguments.output_file = "-";

  /* Parse our arguments; every option seen by parse_opt will
     be reflected in arguments. */
  argp_parse (&argp, argc, argv, 0, 0, &arguments);

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

    if(strcmp(catego_tmp,"y")== 0 || strcmp(catego_tmp,"Y")== 0 || strcmp(catego_tmp,"yes")== 0 ||strcmp(catego_tmp,"YES")== 0)
    {
      supprimerCategorie(arguments.args[0],arguments.rm_category);
    } 
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
    printf("\n yoooohooo searching !\n  %s  \n",arguments.search_files_criteria);
    char** res=malloc(50);
    char* w=malloc(50);
    search_criteria_t search_criteria_result =tokenize(res,w,arguments.search_files_criteria,"et");
  
    printCriteriaT(search_criteria_result);

    printf("\n----- %s -----\n",search_criteria_result.not_in[0]);


    free(res);
    free(w);
    

    // char * strToken = strtok ( arguments.search_files_criteria, delimit );
    // while ( strToken != NULL ) {
    //     printf ( "%s\n", strToken );
    //     // On demande le token suivant.
    //     strToken = strtok ( NULL, delimit );
    // }
  
    
  }
  

  // printf ("FILE = %s\nADDED_TAG = %s\n"
  //         "REMOVED_TAG = %s\nADDED_CATEGORY = %s\n",
  //         arguments.args[0],
  //         arguments.add_tag,
  //         arguments.rm_tag ? arguments.rm_tag:"no_rm",
  //         arguments.add_category? arguments.add_category:"no_add_category");

  exit (0);
}