/* Behold, Lisp!
 *
 * Core Lisp implementation built using:
 * http://www.softwarepreservation.org/projects/LISP/book/LISP%201.5%20Programmers%20Manual.pdf
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lisp.h"

void freeLisp (lisp *l)
{
  if (l != NULL) {
    if (l->atom != NULL)
      free(l->atom);
    if (l->fst != NULL)
      freeLisp(l->fst);
    if (l->snd != NULL)
      freeLisp(l->snd);
    free(l);
  }
}

lisp *cons(lisp *a, lisp *b)
{
  lisp *l = malloc(sizeof(lisp));
  l->atom = NULL;
  l->fst = a;
  l->snd = b;
  return l;
}

/* Undefined for Atom */
lisp *car(lisp *l)
{
  return l->fst;
}

/* Undefined for Atom */
lisp *cdr(lisp *l)
{
  return l->snd;
}

lisp *mkAtom(char *val)
{
  lisp *l = malloc(sizeof(lisp));
  l->atom = malloc(sizeof(char)*(strlen(val)+1));
  l->fst = NULL;
  l->snd = NULL;
  strcpy(l->atom, val);
  return l;
}

int atomcmp(lisp *l, char *s) {
  return strcmp(l->atom, s);
}

int ltoi(lisp *l)
{
  int i;
  if (!atomcmp(l, "F"))
    i = 0;
  else
    i = 1;
  freeLisp(l);
  return i;
}

/* Undefined for S-Expression */
lisp *eq(lisp *a, lisp *b)
{
  if (!strcmp(a->atom, b->atom))
    return mkAtom("T");
  else
    return mkAtom("F");
}

lisp *atom(lisp *l)
{
  if (l->atom != NULL)
    return mkAtom("T");
  else
    return mkAtom("F");
}

lisp *null(lisp *l)
{
  lisp *nil = mkAtom("NIL");
  lisp *result;

  if (l->atom == NULL)
    result = mkAtom("F");
  else
    result = eq(l, nil);

  freeLisp(nil);
  return result;
}

lisp *caar(lisp *l)
{
  return car(car(l));
}

lisp *cadr(lisp *l)
{
  return car(cdr(l));
}

lisp *cdar(lisp *l)
{
  return cdr(car(l));
}

lisp *cadar(lisp *l)
{
  return car(cdr(car(l)));
}

lisp *caddr(lisp *l)
{
  return car(cdr(cdr(l)));
}

lisp *equal(lisp *x, lisp *y) {
  if (ltoi(atom(x)) && ltoi(atom(y))) {
    return eq(x, y);
  }
  else if (ltoi(equal(car(x), car(y))))
    return equal(cdr(x), cdr(y));
  else
    return mkAtom("F");
}

lisp *pairlis(lisp *x, lisp *y, lisp *a)
{
  if (x == NULL)
    return a;
  else
    return cons(cons(car(x), car(y)),
		pairlis(cdr(x), cdr(y), a));
}

lisp *assoc(lisp *x, lisp *a)
{
  if (ltoi(equal(car(a), x)))
    return car(a);
  else
    return assoc(x, cdr(a));
}

lisp *evalquote(lisp *fn, lisp *x)
{
  lisp *nil = mkAtom("NIL");
  lisp *result = apply(fn, x, nil);
  freeLisp(nil);
  return result;
}

lisp *apply(lisp *fn, lisp *x, lisp *a)
{
  if (ltoi(atom(fn))) {
    if (!atomcmp(fn, "CAR"))
      return caar(x);
    else if (!atomcmp(fn, "CDR"))
      return cdar(x);
    else if (!atomcmp(fn, "CONS"))
      return cons(car(x), cadr(x));
    else if (!atomcmp(fn, "ATOM"))
      return atom(car(x));
    else if (!atomcmp(fn, "EQ"))
      return eq(car(x), cadr(x));
    else
      return apply(eval(fn, a), x, a);
  } else if (!atomcmp(car(fn), "LAMBDA")) {
    return eval(caddr(fn), pairlis(cadr(fn), x, a));
  } else if (!atomcmp(car(fn), "LABEL")) {
    return apply(caddr(fn), x, cons(cons(cadr(fn),
					 caddr(fn)), a));
  }
}

lisp *evcon(lisp *c, lisp *a)
{
  if (ltoi(eval(caar(c), a)))
    return eval(cadar(c), a);
  else
    return evcon(cdr(c), a);
}

lisp *evlis(lisp *m, lisp *a)
{
  if (ltoi(null(m)))
    return m;
  else
    return cons(eval(car(m), a),
		evlis(cdr(m), a));
}

lisp *eval(lisp *e, lisp *a)
{
  if (ltoi(atom(e))) {
    return cdr(assoc(e, a));
  } else if (ltoi(null(atom(car(e))))) {
    if (!atomcmp(car(e), "QUOTE"))
      return cadr(e);
    else if (!atomcmp(car(e), "COND"))
      return evcon(cdr(e), a);
    else
      return apply(car(e), evlis(cdr(e), a), a);
  }
}

int length(lisp *l) {
  if (ltoi(null(l)))
    return 0;
  else
    return 1 + length(cdr(l));
}

void showLisp (lisp *l)
{
  if (l->atom != NULL)
    printf("%s", l->atom);
  if (l->fst != NULL) {
    putchar('(');
    showLisp(car(l));
  }
  if (l->snd != NULL) {
    putchar(' ');
    showLisp(cdr(l));
    putchar(')');
  }
}
