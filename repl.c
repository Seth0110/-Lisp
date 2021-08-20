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
  "-h\tdisplay this help and exit\n"
  "-v\toutput version information and exit\n\n"
  "Please report bugs to https://github.com/Seth0110/uLisp/issues\n";

int is_atom_char(char s)
{
  return (isalnum(s) || s == '.' || s == '"' || s == '!');
}

lisp *parseAtom(char *s, int *i)
{
  char *astr = calloc(sizeof(char), 1);

  while (is_atom_char(s[*i])) {
    astr = realloc(astr, strlen(astr)+1);
    astr[strlen(astr)] = s[*i];
    astr[strlen(astr)+1] = '\0';
    (*i)++;
  }

  lisp *a = mkAtom(astr);
  free(astr);

  return a;
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
    } else if (s[*i] == ' ') {
      ++*i;
      return parse(s, i);
    } else if (s[*i] == '\'') {
      ++*i;
      lisp *a = parse(s, i);
      return cons(mkAtom("quote"),
		  cons(a,
		       mkAtom("nil")));
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
    char *input = readline("> ");
    if (!input)
      break;

    add_history(input);

    lisp *l = NULL;
    int *i = calloc(1, sizeof(int));
    l = parse(input, i);
    /* showLisp(l); */
    /* puts(""); */
    /* prettyPrint(l); */
    /* puts(""); */    

    if (l != NULL) {
      l = eval(l, env);
      prettyPrint(l);
      puts("");
      freeLisp(l);
    }

    free(i);
    free(input);
  }

  return 0;
}
