#include <stdio.h>
#include <stdlib.h>

#include "lisp.h"

lisp *mkLisp(char **v, int size) {
  lisp *l = NIL;

  for (int i = size; i > 0; i--)
    l = cons(mkAtom(v[i-1]), l);

  return l;
}

lisp *mkTestLisp() {
  char *v[4] = { "a", "b", "c" };
  lisp *l = mkLisp((char **) v, 3);

  return l;
}

void testEq()
{
  lisp *args = cons(A, cons(A, NIL));
  lisp *l = cons(EQ,
		 args);

  printf("Test: ");
  prettyPrint(l);
  puts("");

  lisp *result = evalquote(car(l), cdr(l));
  prettyPrint(result);
  puts("");

  freeLisp(l);
  freeLisp(result);
}

void testCar() {
  lisp *args = cons(mkTestLisp(),
		    NIL);
  lisp *l = cons(CAR,
		 args);

  printf("Test: ");
  prettyPrint(l);
  puts("");

  lisp *result = evalquote(car(l), cdr(l));
  prettyPrint(result);
  puts("");

  freeLisp(l);
  // freeLisp(result);
}

void testCdr() {
  lisp *args = cons(mkTestLisp(),
		    NIL);
  lisp *l = cons(CDR,
		 args);

  printf("Test: ");
  prettyPrint(l);
  puts("");

  lisp *result = evalquote(car(l), cdr(l));
  prettyPrint(result);
  puts("");

  freeLisp(l);
  // freeLisp(result);
}

void testCons() {
  lisp *args = cons(D,
		    cons(mkTestLisp(),
			 NIL));
  lisp *l = cons(CONS,
		 args);

  printf("Test: ");
  prettyPrint(l);
  puts("");

  lisp *result = evalquote(car(l), cdr(l));
  prettyPrint(result);
  puts("");

  freeLisp(l);
  // freeLisp(result);
}

void testAtom() {
  lisp *args = cons(T, NIL);
  lisp *l = cons(ATOM,
		 args);

  printf("Test: ");
  prettyPrint(l);
  puts("");

  lisp *result = evalquote(car(l), cdr(l));
  prettyPrint(result);
  puts("");

  freeLisp(l);
  freeLisp(result);
}

void testLambda() {
  lisp *arg1 = cons(A,
		    cons(B,
			 NIL));
  lisp *arg2 = cons(C,
		    cons(D,
			 NIL));
  lisp *args = cons(arg1,
		    cons(arg2,
			 NIL));

  lisp *largs = cons(X,
		     cons(Y,
			  NIL));
  lisp *lbody = cons(CONS,
		     cons(cons(CAR,
			       cons(X,
				    NIL)),
			  cons(Y,
			       NIL)));
  lisp *fn = cons(LAMBDA,
		  cons(largs,
		       cons(lbody,
			    NIL)));
  lisp *l = cons(fn, args);
  
  printf("Test: ");
  prettyPrint(l);
  puts("");

  lisp *result = evalquote(car(l), cdr(l));

  prettyPrint(result);
  puts("");

  freeLisp(l);
  // freeLisp(result);
}

void testLabel() {
  lisp *l1 = cons(LABEL,
		  cons(FF,
		       cons(cons(LAMBDA,
				 cons(cons(X,
					   NIL),
				      cons(cons(CAR,
						(cons(X,
						      NIL))),
					   NIL))),
			    NIL)));
				 
  lisp *l2 = cons(FF,
		  cons(cons(A,
			    cons(B,
				 NIL)),
		       NIL));
		       

  printf("Test: ");
  prettyPrint(l1);
  puts("");
  prettyPrint(l2);
  puts("");

  freeLisp(evalquote(l1, l2));

  freeLisp(l1);
  freeLisp(l2);
}

void testQuote() {
  lisp *l = cons(QUOTE,
		 cons(A,
		      NIL));

  printf("Test: ");
  prettyPrint(l);
  puts("");

  lisp *n = NIL;
  lisp *result = evalquote(l, n);

  prettyPrint(result);
  puts("");
 
  freeLisp(n);
  freeLisp(l);
  // freeLisp(result);
}

void testCond() {
  lisp *l = cons(COND,
		 cons(cons(cons(EQ,
				cons(NIL,
				     cons(NIL,
					  NIL))),
			   cons(cons(QUOTE,
				     cons(A, NIL)),
				NIL)),
		      NIL));

  lisp *n = NIL;

  printf("Test: ");
  prettyPrint(l);
  puts("");

  lisp *result = evalquote(l, n);

  freeLisp(n);
  freeLisp(l);
  freeLisp(result);
}

void testDisplay() {
  /* lisp *l = cons(mkAtom("a"), */
  /* 		 cons(cons(mkAtom("b"), */
  /* 			   cons(mkAtom("c"), */
  /* 				cons(mkAtom("d"), */
  /* 				     NIL))), */
  /* 		      cons(mkAtom("e"), */
  /* 			   NIL))); */
  lisp *l = cons(cons(mkAtom("a"),
		      cons(mkAtom("b"),
			   NIL)),
		 NIL);
		 

  puts("Test: Display");
  showLisp(l);
  puts("");
  prettyPrint(l);
  puts("");
  freeLisp(l);
}

int main(int argc, char **argv)
{
  /* testCar(); */
  /* testCdr(); */
  /* testCons(); */
  /* testAtom(); */
  /* testEq(); */
  /* testLambda(); */
  /* testLabel(); */
  // testQuote();
  // testCond();

  testDisplay();
  
  return 0;
}
