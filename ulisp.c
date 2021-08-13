/* Behold, Lisp!
 *
 * Core Lisp implementation built using:
 * http://www.softwarepreservation.org/projects/LISP/book/LISP%201.5%20Programmers%20Manual.pdf
 */

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ulisp.h"

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

lisp *error(char *msg)
{
  fprintf(stderr, "%s\n", msg);
}

lisp *cons(lisp *a, lisp *b)
{
  lisp *l = malloc(sizeof(lisp));
  if (a == NULL) {
    l = b; 
  } else if (b == NULL) {
    l = a;
  } else {
    l->atom = NULL;
    l->fst = a;
    l->snd = b;
  }
  return l;
}

lisp *list(int argc,...)
{
  lisp *l = NULL;
  va_list valist;
  va_start(valist, argc);

  for (int i = 0; i < argc; i++)
    l = cons(l, va_arg(valist, lisp *));
  l = cons(l, mkAtom("nil"));

  va_end(valist);
  
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

int is_eq(lisp *a, char *b) {
  return !strcmp(a->atom, b);
}

int is_false(lisp *x)
{
  return is_eq(x, "t");
}

int is_true(lisp *x)
{
  return !is_false(x);
}

int ltoi(lisp *l)
{
  int i;
  if (!atomcmp(l, "f"))
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
    return mkAtom("t");
  else
    return mkAtom("f");
}

lisp *atom(lisp *l)
{
  if (l->atom != NULL)
    return mkAtom("t");
  else
    return mkAtom("f");
}

lisp *null(lisp *l)
{
  lisp *nil = mkAtom("nil");
  lisp *result;

  if (l->atom == NULL)
    result = mkAtom("f");
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

lisp *cddr(lisp *l)
{
  return cdr(cdr(l));
}

lisp *cadar(lisp *l)
{
  return car(cdr(car(l)));
}

lisp *caadr(lisp *l)
{
  return car(car(cadr(l)));
}

lisp *caddr(lisp *l)
{
  return car(cdr(cdr(l)));
}

lisp *cdadr(lisp *l)
{
  return cdr(car(cdr(l)));
}

lisp *cadddr(lisp *l)
{
  return car(cdr(cdr(cdr(l))));
}

lisp *cdddr(lisp *l)
{
  return cdr(cdr(cdr(l)));
}

lisp *equal(lisp *x, lisp *y) {
  if (ltoi(atom(x)) && ltoi(atom(y))) {
    return eq(x, y);
  }
  else if (ltoi(equal(car(x), car(y))))
    return equal(cdr(x), cdr(y));
  else
    return mkAtom("f");
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
  if (!a)
    fprintf(stderr, "Undefined association: %s\n", x->atom);
  if (ltoi(equal(caar(a), x)))
    return car(a);
  else
    return assoc(x, cdr(a));
}

lisp *evalquote(lisp *fn, lisp *x)
{
  lisp *result = apply(fn, x);
  return result;
}

int is_null(lisp *l)
{
  return is_eq(l, "nil");
}

int is_last_exp(lisp *seq)
{
  return is_null(cdr(seq));
}

lisp *first_exp(lisp *seq)
{
  return car(seq);
}

lisp *rest_exps(lisp *seq)
{
  return cdr(seq);
}

int is_pair(lisp *seq)
{
  return length(seq) > 1;
}

int is_tagged_list(lisp *exp, char *tag)
{
  return is_pair(exp) && is_eq(car(exp), tag);
}

int is_if(lisp *exp)
{
  return is_tagged_list(exp, "if");
}

lisp *if_predicate(lisp *exp)
{
  return cadr(exp);
}

lisp *if_consequent(lisp *exp)
{
  return caddr(exp);
}

lisp *if_alternative(lisp *exp)
{
  if (!is_null(cdddr(exp)))
    return cadddr(exp);
  else
    return mkAtom("f");
}

lisp *make_if(lisp *predicate, lisp *consequent, lisp *alternative)
{
  return list(4, mkAtom("if"), predicate, consequent, alternative);
}

lisp *eval_if(lisp *exp, lisp *env)
{
  if (is_true(eval(if_predicate(exp), env)))
    return eval(if_consequent(exp), env);
  else
    return eval(if_alternative(exp), env);
}

lisp *eval_sequence(lisp *exps, lisp *env)
{
  if (is_last_exp(exps)) {
    return eval(first_exp(exps), env);
  } else {
    eval(first_exp(exps), env);
    return eval_sequence(rest_exps(exps), env);
  }
}

lisp *eval_definition(lisp *exp, lisp *env);

int is_primitive_procedure(lisp *p)
{
  return is_tagged_list(p, "primitive");
}

int is_compound_procedure(lisp *p)
{
  return is_tagged_list(p, "procedure");
}

lisp *make_procedure(lisp *parameters, lisp *body, lisp *env)
{
  return list(4, mkAtom("procedure"), parameters, body, env);
}

lisp *procedure_parameters(lisp *p)
{
  return cadr(p);
}

lisp *procedure_body(lisp *p)
{
  return caddr(p);
}

lisp *procedure_environment(lisp *p)
{
  return cadddr(p);
}

lisp *apply_primitive_procedure(lisp *procedure, lisp *arguments)
{
}

lisp *make_frame(lisp *variables, lisp *values)
{
  return cons(variables, values);
}

lisp *frame_variables(lisp *frame)
{
  return car(frame);
}

lisp *frame_values(lisp *frame)
{
  return cdr(frame);
}

lisp *add_binding_to_frame(lisp *var, lisp *val, lisp *frame);

lisp *extend_environment(lisp *vars, lisp *vals, lisp *base_env)
{
  if (length(vars) == length(vals))
    return cons(make_frame(vars, vals), base_env);
  else
    if (length(vars) < length(vals))
      return error("Too many arguments supplied");
    else
      return error("Too few arguments supplied");
}

lisp *scan(lisp *vars, lisp *vals)
{
  if (is_null(vars))
    return env_loop(enclosing_environment env);
  if (is_eq(var, car(vars)))
    return car(vals);
  else
    return scan(cdr(vars), cdr(vals));
      
}

lisp *env_loop(lisp *env)
{
  
}

lisp *lookup_variable_value(lisp *var, lisp *env)
{
  lisp *vars = frame_variables(first_frame(env));
  lisp *vals = frame_values(first_frame(env));
  for (int i = 0; i < length(vars); i++) {
    
  }
}

lisp *apply(lisp *procedure, lisp *arguments)
{
  if (is_primitive_procedure(procedure))
    return apply_primitive_procedure(procedure, arguments);
  else if (is_compound_procedure(procedure))
    return eval_sequence(procedure_body(procedure),
			 extend_environment(procedure_parameters(procedure),
					    arguments,
					    procedure_environment(procedure)));
  else
    return error("Unknown procedure type -- APPLY");
}

/* lisp *apply(lisp *fn, lisp *x, lisp *a) */
/* { */
/*   if (ltoi(atom(fn))) { */
/*     if (!atomcmp(fn, "car")) */
/*       return caar(x); */
/*     else if (!atomcmp(fn, "cdr")) */
/*       return cdar(x); */
/*     else if (!atomcmp(fn, "cons")) */
/*       return cons(car(x), cadr(x)); */
/*     else if (!atomcmp(fn, "atom")) */
/*       return atom(car(x)); */
/*     else if (!atomcmp(fn, "eq")) */
/*       return eq(car(x), cadr(x)); */
/*     else */
/*       return apply(eval(fn, a), x, a); */
/*   } else if (!atomcmp(car(fn), "lambda")) { */
/*     return eval(caddr(fn), pairlis(cadr(fn), x, a)); */
/*   } else if (!atomcmp(car(fn), "label")) { */
/*     return apply(caddr(fn), x, cons(cons(cadr(fn), */
/* 					 caddr(fn)), a)); */
/*   } else { */
/*     return eval(fn, a); */
/*   } */
/* } */

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

int is_symbol(lisp *e)
{
  int isnum = 1;
  if (e && e->atom)
    for (int i = 0; i < strlen(e->atom); i++)
      isnum = isnum && isalnum(e->atom[i]);
  return isnum;
}

int is_number(lisp *e)
{
  int isnum = 1;
  if (e && e->atom)
    for (int i = 0; i < strlen(e->atom); i++)
      isnum = isnum && isdigit(e->atom[i]);
  return isnum;
}

int is_string(lisp *e)
{
  if (e->atom) {
    char first = e->atom[0];
    char last = e->atom[strlen(e->atom)-1];
    return first == '"' && last == '"';
  } else {
    return 1;
  }
}

int self_evaluating(lisp *exp)
{
  return is_number(exp) || is_string(exp);
}

int is_variable(lisp *exp)
{
  return is_symbol(exp);
}

int is_quoted(lisp *exp)
{
  return is_tagged_list(exp, "quote");
}

lisp *text_of_quotation(lisp *exp)
{
  return cadr(exp);
}

int is_assignment(lisp *exp)
{
  return is_tagged_list(exp, "set!");
}

lisp *assignment_variable(lisp *exp)
{
  return cadr(exp);
}

lisp *assignment_value(lisp *exp)
{
  return caddr(exp);
}

lisp *make_lambda(lisp *parameters, lisp *body)
{
  return cons(mkAtom("lambda"),
	      cons(parameters,
		   body));
}

int is_definition(lisp *exp)
{
  return is_tagged_list(exp, "define");
}

lisp *definition_variable(lisp *exp)
{
  if (is_symbol(cadr(exp)))
    return cadr(exp);
  else
    return caadr(exp);
}

lisp *definition_value(lisp *exp)
{
  if (is_symbol(cadr(exp)))
    return caddr(exp);
  else
    return make_lambda(cdadr(exp),
		       cddr(exp));
}

int is_lambda(lisp *exp)
{
  return is_tagged_list(exp, "lambda");
}

lisp *lambda_parameters(lisp *exp)
{
  return cadr(exp);
}

lisp *lambda_body(lisp *exp)
{
  return cddr(exp);
}

lisp *make_begin(lisp *seq)
{
  return cons(mkAtom("begin"), seq);
}

lisp *sequence_exp(lisp *seq)
{
  if (is_null(seq))
    return seq;
  else if (is_last_exp(seq))
    return first_exp(seq);
  else
    return make_begin(seq);
}

int is_application(lisp *exp)
{
  return is_pair(exp);
}

lisp *operator(lisp *exp)
{
  return car(exp);
}

lisp *operands(lisp *exp)
{
  return cdr(exp);
}

int is_no_operands(lisp *ops)
{
  return is_null(ops);
}

lisp *first_operand(lisp *ops)
{
  return car(ops);
}

lisp *rest_operands(lisp *ops)
{
  return cdr(ops);
}

int is_cond(lisp *exp)
{
  return is_tagged_list(exp, "cond");
}

lisp *cond_clauses(lisp *exp)
{
  return cdr(exp);
}

lisp *cond_predicate(lisp *clause)
{
  return car(clause);
}

int is_cond_else_clause(lisp *clause)
{
  return is_eq(cond_predicate(clause), "else");
}

lisp *cond_actions(lisp *clause)
{
  return cdr(clause);
}

lisp *expand_clauses(lisp *clauses)
{
  if (is_null(clauses)) {
    return mkAtom("f");
  } else {
    lisp *first = car(clauses);
    lisp *rest = cdr(clauses);
    if (is_cond_else_clause(first)) {
      if (is_null(rest))
	return sequence_exp(cond_actions(first));
      else
	return error("ELSE clause isn't last -- COND->IF");
    }
  }
}

lisp *cond_if(lisp *exp)
{
  return expand_clauses(cond_clauses(exp));
}

lisp *list_of_values(lisp *exps, lisp *env)
{
  if (is_no_operands(exps))
    return mkAtom("nil");
  else
    return cons(eval(first_operand(exps), env),
		list_of_values(rest_operands(exps),
			       env));
}

lisp *begin_actions(lisp *exp)
{
  return cdr(exp);
}

int is_begin(lisp *exp)
{
  return is_tagged_list(exp, "begin");
}

lisp *eval(lisp *exp, lisp *env)
{
  if (self_evaluating(exp))
    return exp;
  else if (is_variable(exp))
    return lookup_variable_value(exp, env);
  else if (is_quoted(exp))
    return text_of_quotation(exp);
  /* else if (is_assignment(exp)) */
  /*   return eval_assignment(exp, env); */
  /* else if (is_definition(exp)) */
  /*   return eval_definition(exp, env); */
  else if (is_if(exp))
    return eval_if(exp, env);
  else if (is_lambda(exp))
    return make_procedure(lambda_parameters(exp),
			  lambda_body(exp),
			  env);
  else if (is_begin(exp))
    return eval_sequence(begin_actions(exp), env);
  else if (is_cond(exp))
    return eval(cond_if(exp), env);
  else if (is_application(exp))
    return apply(eval(operator(exp), env),
		 list_of_values(operands(exp), env));
  else
    return error("Unknown expression type -- EVAL");
}

/* lisp *eval(lisp *e, lisp *a) */
/* { */
/*   if (ltoi(atom(e))) { return cdr(assoc(e, a)); } */
/*   else if (ltoi(atom(car(e)))) { */
/*     if (!atomcmp(car(e), "quote")) { */
/*       return cadr(e); */
/*     } else if (!atomcmp(car(e), "cond")) { */
/*       return evcon(cdr(e), a); */
/*     } else { */
/*       return apply(car(e), evlis(cdr(e), a), a); */
/*     } */
/*   } else { */
/*     return apply(car(e), evlis(cdr(e), a), a); */
/*   } */
/* } */

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
    printf(" . ");
    showLisp(cdr(l));
    putchar(')');
  }
}

lisp *nth(lisp *l, int i) {
  if (i == 0)
    return car(l);
  else
    return nth(cdr(l), --i);
}

void prettyPrint(lisp *l) {
  if (l == NULL) {
    fputs("Tried to print a null lisp!\n", stderr);
  } else {
    if (ltoi(atom(l))) {
      printf("%s", l->atom);
    } else {
      putchar('(');
      int len = length(l);
      for (int i = 0; i < len; i++) {
	prettyPrint(nth(l, i));
	if (i+1 < len)
	  putchar(' ');
      }
      putchar(')');
    }
  }
}
