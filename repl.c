#include <ctype.h>
#include <editline/history.h>
#include <editline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <lisp.h>

lisp *parseAtom(char *s, int *i)
{
  char *astr = calloc(sizeof(char), 1);

  while (isalnum(s[*i])) {
    astr = realloc(astr, strlen(astr)+1);
    astr[strlen(astr)] = s[*i];
    astr[strlen(astr)+1] = '\0';
    (*i)++;
  }
  (*i)--;

  lisp *a = mkAtom(astr);
  free(astr);
  
  return a;
}

/* Parse an S-Expression */
lisp *parse(char *s, int *i) {
  lisp *l = NULL;
  
  while (*i < strlen(s)) {
    if (s[*i] == '(') {
      (*i)++;
      l = cons(l, parse(s, i));
    } else if (s[*i] == ')') {
      return cons(l, NIL);
    } else if (s[*i] == ' ') {
      (*i)++;
      l = cons(l, parse(s, i));
    } else if (isalnum(s[*i])) {
      l = cons(l, parseAtom(s, i));
    } else {
      puts("Invalid character detected!");
      (*i)++;
    }
    (*i)++;
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
    int *i = malloc(sizeof(int));
    *i = 0;
    l = parse(input, i);

    printf(";; ");
    showLisp(l);
    puts("");
    
    printf(";; ");
    prettyPrint(l);
    puts("");

    /* l = evalquote(car(l), cdr(l)); */
    /* prettyPrint(l); */
    /* puts(""); */

    free(i);
    freeLisp(l);
    free(input);

  }

  return 0;
}
