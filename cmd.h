#ifndef SYSTPROJET_CMD_H
#define SYSTPROJET_CMD_H
#include <argp.h>

const char *argp_program_version =
  "tags 1.0";
const char *argp_program_bug_address =
  "\n<ga_benamara@esi.dz>\n<aknoun@gmail.com>\n<ga_djelid@esi.dz>";

/* Program documentation. */
static char doc[] =
  "Cmd example for tags managing -- a program with options and arguments using argp";

/* A description of the arguments we accept. */
static char args_doc[] = "ARG1 ARG2";

/* The options we understand. */
static struct argp_option options[] = {
  {"verbose",  'v', 0,      0,  "Produce verbose output" },
  {"quiet",    'q', 0,      0,  "Don't produce any output" },
  {"silent",   's', 0,      OPTION_ALIAS },
  {"output",   'o', "FILE", 0,
   "Output to FILE instead of standard output" },
  { 0 }
};

/* Used by main to communicate with parse_opt. */
struct arguments
{
  char *args[2];                /* arg1 & arg2 */
  int silent, verbose;
  char *output_file;
};


/* Functions prototype ! */
static error_t parse_opt (int key, char *arg, struct argp_state *state);




#endif //SYSTPROJET_CMD_H
