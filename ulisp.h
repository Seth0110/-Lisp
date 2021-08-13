#ifndef LISP
#define LISP

typedef struct Lisp {
  char *atom;
  struct Lisp *fst;
  struct Lisp *snd;
} lisp;

void freeLisp(lisp *);
lisp *cons(lisp *, lisp *);
lisp *car(lisp *);
lisp *cdr(lisp *);
lisp *mkAtom(char *);
int atomcmp(lisp *, char*);
int ltoi(lisp *);
lisp *eq(lisp *, lisp *);
lisp *atom(lisp *);
lisp *null(lisp *);
lisp *caar(lisp *);
lisp *cadr(lisp *);
lisp *cdar(lisp *);
lisp *cadar(lisp *);
lisp *caddr(lisp *);
lisp *equal(lisp *, lisp *);
lisp *pairlis(lisp *, lisp *, lisp *);
lisp *assoc(lisp *, lisp *);
lisp *evalquote(lisp *, lisp *);
lisp *apply(lisp *, lisp *);
lisp *evcon(lisp *, lisp *);
lisp *evlis(lisp *, lisp *);
lisp *eval(lisp *, lisp *);
void showLisp(lisp *);
int length(lisp *);
lisp *nth(lisp *, int);
void prettyPrint(lisp *);

#endif
