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

#include "ulisp.h"

char *version_string = "µLisp v0.0.1";

char *gpl_string = 
  "µLisp v0.0.1 Copyright (C) 2021 Seth Sevier\n"
  "µLisp comes with ABSOLUTELY NO WARRANTY.\n"
  "You may redistribute copies of µLisp\n"
  "under the terms of the GNU General Public License.\n";

char *help_string =
  "Usage: repl OPTION\n\n"
  "µLisp, a simple Lisp based on Structure and Interpretation of Computer Programs.\n\n"
  "Initialization options:\n\n"
  "-h\tShow this help and exit\n"
  "-v\tShow version information and exit\n\n"
  "Please report bugs to https://github.com/Seth0110/uLisp/issues\n";

char *repl_help_string =
  "Help commands:\n\n"
  ",c\tClear the terminal screen\n"
  ",h\tShow this help\n"
  ",q\tQuit µLisp\n"
  ",v\tShow version information\n";

lisp *parseAtom(char *s, int *i)
{
  char *astr = calloc(sizeof(char), 1);
  int len = 0;

  while (is_atom_char(s[*i])) {
    astr = realloc(astr, sizeof(char) * len+2);
    astr[len] = s[*i];
    astr[len+1] = '\0';
    ++len;
    ++*i;
  }

  lisp *a = mkAtom(astr);
  free(astr);

  return a;
}

int parens(char *s)
{
  int depth = 0;
  for (int i = 0; i < strlen(s); i++)
    if (s[i] == '(')
      depth++;
    else if (s[i] == ')')
      depth--;
  return depth;
}

/* Parse an S-Expression */
lisp *parse(char *s, int *i) {
  if (*i < strlen(s)) {
    if (is_atom_char(s[*i])) {
      lisp *a = parseAtom(s, i);
      lisp *b = parse(s, i);
      return cons(a, b);
    } else if (s[*i] == '(') {
      ++*i;
      lisp *a = parse(s, i);
      ++*i;
      lisp *b = parse(s, i);
      return cons(a, b);
    } else if (s[*i] == ')') {
      return mkAtom("nil");
    } else if (s[*i] == ' ' || s[*i] == '\n') {
      ++*i;
      return parse(s, i);
    } else if (s[*i] == '\'') {
      ++*i;
      lisp *a = parse(s, i);
      return list(2, mkAtom("quote"), a);
    } else if (s[*i] == ';') {
      while (s[*i] != '\n' && *i < strlen(s))
	++*i;
      return parse(s, i);
    } else {
      return NULL;
    }
  } else {
    return NULL;
  }
}

void process_repl_arg(char arg)
{
  
  switch (arg) {
  case 'c':
    printf("\033[2J\033[1;1H");
    break;
  case 'h':
    printf("%s", repl_help_string);
    break;
  case 'v':
    printf("%s", gpl_string);
    break;
  }
}

int main(int argc, char **argv)
{
  if (argc == 2) {
    if (!strcmp(argv[1], "-v"))
      fprintf(stderr, "%s", gpl_string);
    else if (!strcmp(argv[1], "-h"))
      fprintf(stderr, "%s", help_string);
    return 0;
  }

  fputs("µLisp v0.0.1\n", stderr);
  fputs("C-c to exit\n", stderr);

  lisp *env = the_global_environment();
  
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

    if (!strcmp(buffer, ",q")) {
      // TODO: Say "Goodbye!" in a random language
      fputs("Goodbye!\n", stderr);
      free(buffer);
      return 0;
    } else if (buffer[0] == ',') {
      process_repl_arg(buffer[1]);
    } else if (parens(buffer) == 0) {
      int i = 0;
      lisp *input = parse(buffer, &i);
      free(buffer);
      if (input) {
	lisp *output = eval(input, env);
	prettyPrint(output);
	puts("");
	freeLisp(output);
	freeLisp(input);
      }
    } else {
      fputs("Unbalanced S-Expression!\n", stderr);
    }
  }

  freeLisp(env);

  return 0;
}
