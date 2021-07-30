#include <stdio.h>

#include "lisp.h"

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

  freeLisp(args);
  freeLisp(f);
  freeLisp(result);
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

  lisp *result = evalquote(f, args);
  showLisp(result);
  puts("");

  freeLisp(args);
  freeLisp(f);
  // freeLisp(result);
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

  freeLisp(args);
  freeLisp(f);
  // freeLisp(result);
}

void testCons() {
  lisp *f = mkAtom("CONS");
  lisp *args = cons(mkAtom("A"),
		    cons(cons(mkAtom("B"),
			      cons(mkAtom("C"),
				   mkAtom("NIL"))),
			 mkAtom("NIL")));

  printf("Test: ");
  showLisp(f);
  puts("");
  showLisp(args);
  puts("");

  lisp *result = evalquote(f, args);
  showLisp(result);
  puts("");

  freeLisp(args);
  freeLisp(f);
  // freeLisp(result);
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

  freeLisp(args);
  freeLisp(f);
  freeLisp(result);
}

int main(int argc, char **argv)
{
  // testCar();
  // testCdr();
  // testCons();
  // testAtom();
  // testEq();

  return 0;
}
