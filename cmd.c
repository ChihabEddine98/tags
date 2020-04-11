#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cmd.h"

/* Parse a single option. */
static error_t parse_opt (int key, char *arg, struct argp_state *state)
{
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
  struct arguments *arguments = state->input;

  switch (key)
    {
    case 'a': case 'n':
      arguments->add_tag = arg;
      break;
    case 'r': case 'd':
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

  /* Default values. */
  arguments.add_tag = "";
  arguments.rm_tag = "";
  arguments.add_category = "";
  arguments.output_file = "-";

  /* Parse our arguments; every option seen by parse_opt will
     be reflected in arguments. */
  argp_parse (&argp, argc, argv, 0, 0, &arguments);

  printf ("FILE = %s\nADDED_TAG = %s\n"
          "REMOVED_TAG = %s\nADDED_CATEGORY = %s\n",
          arguments.args[0],
          arguments.add_tag,
          arguments.rm_tag ? arguments.rm_tag:"no_rm",
          arguments.add_category? arguments.add_category:"no_add_category");

  exit (0);
}