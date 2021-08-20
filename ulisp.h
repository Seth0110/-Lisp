/* Header file of ulisp.c
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

#ifndef LISP
#define LISP

typedef struct Lisp {
  char *atom;
  struct Lisp *fst;
  struct Lisp *snd;
} lisp;

void freeLisp(lisp *);
lisp *list(int, ...);
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
lisp *the_global_environment();

#endif
