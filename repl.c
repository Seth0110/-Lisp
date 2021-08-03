#include <ctype.h>
#include <editline/history.h>
#include <editline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <lisp.h>

/* Parse an S-Expression */
lisp *parse(char *s) {
  lisp *l = NIL;
  int i = 0;
  while (i < strlen(s)) {
    if (s[i] == '(') {
      l = cons(parse(s+i-1), l);
    } else if (s[i] == ')') {
      return NIL;
    } else if (s[i] == ' ') {
      ;
    } else if (isalnum(s[i])) {
      char *astr = calloc(sizeof(char), 1);
      while (isalnum(s[i])) {
	astr = realloc(astr, strlen(astr)+1);
	astr[strlen(astr)] = s[i];
	astr[strlen(astr)+1] = '\0';
	i++;
      }
      lisp *atom = mkAtom(astr);
      l = cons(atom, l);
    } else {
      puts("Invalid character detected!");
    }
    i++;
  }
  return l;
}

int main(int argc, char **argv)
{
  puts("µLisp v0.0.1");
  puts("C-c to exit");

  while (1) {
    char *input = readline("> ");
    
    add_history(input);

    lisp *l;
    l = parse(input);
    showLisp(l);
    puts("");
    prettyPrint(l);
    puts("");

    freeLisp(l);
    free(input);
  }

  return 0;
}
