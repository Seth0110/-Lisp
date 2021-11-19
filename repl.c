/* Interactive REPL
 *
 * This file is part of µLisp.
 *
 * µLisp is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * µLisp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with µLisp.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <ctype.h>
#include <editline/history.h>
#include <editline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "ulisp.h"

char *version_string = "µLisp v0.0.1";

char *gpl_string = 
  "µLisp v0.0.1 Copyright (C) 2021 Seth Sevier\n"
  "µLisp comes with ABSOLUTELY NO WARRANTY.\n"
  "You may redistribute copies of µLisp\n"
  "under the terms of the GNU General Public License.\n";

char *help_string =
  "Usage: repl OPTION\n\n"
  "µLisp, a Scheme based on Structure and Interpretation of Computer Programs.\n\n"
  "Initialization options:\n\n"
  "-h, --help     \tShow this help and exit\n"
  "-l, --load FILE\tImport a Scheme file\n"
  "-v, --version  \tShow version information and exit\n\n"
  "Please report bugs to https://github.com/Seth0110/uLisp/issues\n";

char *repl_help_string =
  "Help commands:\n\n"
  ",c\tClear the terminal screen\n"
  ",h\tShow this help\n"
  ",q\tQuit µLisp\n"
  ",v\tShow version information\n";

void process_repl_arg(char arg)
{  
  switch (arg) {
  case 'c':
    printf("\033[2J\033[1;1H");
    break;
  case 'h':
    printf("%s", repl_help_string);
    break;
  case 'q':
    fputs("Goodbye!\n", stderr);
    exit(0);
  case 'v':
    printf("%s", gpl_string);
    break;
  default:
    printf("Unknown repl argument\n");
    break;
  }
}

int main(int argc, char **argv)
{
  char *import_fn = NULL;
  
  for (int i = 1; i < argc; i++) {
    if (!strcmp(argv[i], "-v") || !strcmp(argv[i], "--version")) {
      fprintf(stderr, "%s", gpl_string);
      return 0;
    } else if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
      fprintf(stderr, "%s", help_string);
      return 0;
    } else if (!strcmp(argv[i], "-l") || !strcmp(argv[i], "--load")) {
      import_fn = argv[++i];
    }
  }

  srand(time(0));

  fputs("µLisp v0.0.1\n", stderr);
  fputs("C-c to exit\n", stderr);

  lisp *env = the_global_environment();
  load_file(mkStrAtom("ulisp.scm"), env);

  if (import_fn)
    load_file(mkStrAtom(import_fn), env);
  
  while (1) {
    char *buffer = calloc(1, sizeof(char));
    int lines = 0;
    do {
      char *line;
      if (!lines)
	line = readline("> ");
      else
	line = readline("");

      if (!line) {
	return 0;
      } else {
	buffer = realloc(buffer, strlen(buffer) + strlen(line) + 1);
	buffer = strcat(buffer, line);	
	add_history(line);
      }
      
      lines++;
      free(line);
    } while (parens(buffer) > 0);

    if (buffer[0] == ',') {
      process_repl_arg(buffer[1]);
    } else if (parens(buffer) == 0) {
      int i = 0;
      lisp *input = parse(buffer, &i);
      free(buffer);
      if (input) {
	lisp *output = eval(input, env);
	printf("; ");
	s(output);
	// freeLisp(output);
	freeLisp(input);
      }
    } else {
      fputs("Unbalanced S-Expression!\n", stderr);
    }
  }

  freeLisp(env);

  return 0;
}
