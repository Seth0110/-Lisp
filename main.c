#include <stdio.h>

#include "lisp.h"

void showLispFancy(lisp *l)
{ /* Currently displays the ) right, but can't get ( working
   *  A -> A
   * (A (B NIL)) -> (A B)
   * (A ((B C) NIL)) -> (A (B C))
   */
  if (l->atom != NULL)
    if (atomcmp(l, "NIL"))
      printf("%s", l->atom);
    else
      putchar(')');

  if (l->fst != NULL) {
    putchar('(');
    if (car(l)->atom != NULL)
      showLisp(car(l));
    showLisp(cdr(l));
  }
}

void testEq()
{
  lisp *f = mkAtom("EQ");
  lisp *args = cons(mkAtom("F"), cons(mkAtom("F"), mkAtom("NIL")));

  printf("Test: ");

  showLisp(f);
  puts("");
  showLisp(args);
  puts("");

  lisp *result = evalquote(f, args);
  showLisp(result);
  puts("");

  freeLisp(result);
  freeLisp(f);
  freeLisp(args);
}

void testCar() {
  lisp *f = mkAtom("CAR");
  lisp *args = cons(cons(mkAtom("A"),
			 cons(mkAtom("B"),
			      mkAtom("NIL"))),
		    mkAtom("NIL"));

  printf("Test: ");
  showLisp(f);
  puts("");
  showLisp(args);
  puts("");

  showLisp(evalquote(f, args));
  puts("");

  freeLisp(f);
  freeLisp(args);
}

void testCdr() {
  lisp *f = mkAtom("CDR");
  lisp *args = cons(cons(mkAtom("A"),
			 cons(mkAtom("B"),
			      mkAtom("NIL"))),
		    mkAtom("NIL"));

  printf("Test: ");
  showLisp(f);
  puts("");
  showLisp(args);
  puts("");

  lisp *result = evalquote(f, args);
  showLisp(result);
  puts("");

  freeLisp(f);
  freeLisp(args);
}

void testCons() {
  lisp *f = mkAtom("CONS");
  lisp *args = cons(mkAtom("T"), cons(mkAtom("F"), mkAtom("NIL")));

  printf("Test: ");
  showLisp(f);
  puts("");
  showLisp(args);
  puts("");

  lisp *result = evalquote(f, args);
  showLisp(result);
  puts("");

  freeLisp(result);
}

void testAtom() {
  lisp *f = mkAtom("ATOM");
  lisp *args = cons(mkAtom("T"), mkAtom("NIL"));

  printf("Test: ");
  showLisp(f);
  puts("");
  showLisp(args);
  puts("");

  lisp *result = evalquote(f, args);
  showLisp(result);
  puts("");

  freeLisp(f);
  freeLisp(args);
  freeLisp(result);
}

int main(int argc, char **argv)
{
  // testCar();
  // testCdr();
  // testCons();
  // testAtom();
  testEq();

  return 0;
}
