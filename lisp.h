#ifndef LISP
#define LISP

typedef struct Lisp {
  char *atom;
  struct Lisp *fst;
  struct Lisp *snd;
} lisp;

void freeLisp(lisp *);
lisp *cons(lisp *, lisp *);
lisp *append(lisp *, lisp *);
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
lisp *apply(lisp *, lisp *, lisp *);
lisp *evcon(lisp *, lisp *);
lisp *evlis(lisp *, lisp *);
lisp *eval(lisp *, lisp *);
void showLisp(lisp *);
int length(lisp *);
lisp *nth(lisp *, int);
void prettyPrint(lisp *);

#define NIL mkAtom("nil")
#define CONS mkAtom("cons")
#define CAR mkAtom("car")
#define CDR mkAtom("cdr")
#define ATOM mkAtom("atom")
#define EQ mkAtom("eq")
#define LAMBDA mkAtom("lambda")
#define LABEL mkAtom("label")
#define QUOTE mkAtom("quote")
#define COND mkAtom("cond")

#define A mkAtom("a")
#define B mkAtom("b")
#define C mkAtom("c")
#define D mkAtom("d")
#define T mkAtom("t")
#define F mkAtom("f")
#define FF mkAtom("ff")
#define X mkAtom("x")
#define Y mkAtom("y")

#endif
