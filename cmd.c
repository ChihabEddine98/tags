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
  arguments.output_file = "-";

  /* Parse our arguments; every option seen by parse_opt will
     be reflected in arguments. */
  argp_parse (&argp, argc, argv, 0, 0, &arguments);

  // Case of tag -d TAG -c CATEGORY file.txt
  if(arguments.rm_tag)
  {
     // Case ok !
    if(arguments.add_category)
    {
      removeTagCategory(arguments.args[0],arguments.add_category,arguments.rm_tag);
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

  // printf ("FILE = %s\nADDED_TAG = %s\n"
  //         "REMOVED_TAG = %s\nADDED_CATEGORY = %s\n",
  //         arguments.args[0],
  //         arguments.add_tag,
  //         arguments.rm_tag ? arguments.rm_tag:"no_rm",
  //         arguments.add_category? arguments.add_category:"no_add_category");

  exit (0);
}