#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
    case 'a': 
      arguments->add_tag = arg;
      break;
    case 'd':
      arguments->rm_tag = arg;
      break;
    case 'c': case 'g':
      arguments->add_category = arg;
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
  char catego_tmp[MAX_STRING];

  /* Default values. */
  arguments.add_tag = 0;
  arguments.rm_tag = 0;
  arguments.add_category = 0;
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
        scanf("%s",&catego_tmp);

        if(catego_tmp =='\n')
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