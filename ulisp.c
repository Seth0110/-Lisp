/* Core Lisp implementation built using SICP
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
 *
 * Naming conventions:
 * null?           -> is_null
 * primitive-apply -> primitive_apply
 * set-car!        -> set_car_i
 */

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ulisp.h"

char *primitive_procedures[6] = { "car", "cdr", "cons", "atom", "eq", "null" };

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

lisp *list(int argc, ...)
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

lisp *set_car_i(lisp *x, lisp *y)
{
  return cons(y, cdr(x));
}

lisp *set_cdr_i(lisp *x, lisp *y)
{
  return cons(car(x), y);
}

int is_eq(lisp *a, char *b) {
  if (a && a->atom)
    return !strcmp(a->atom, b);
  else
    return 0;
}

int is_null(lisp *l)
{
  return is_eq(l, "nil");
}

lisp *append_i(lisp *x, lisp *y)
{
  if (is_null(x))
    return y;
  else
    return cons(car(x), append_i(cdr(x), y));
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

int is_false(lisp *x)
{
  return is_eq(x, "f");
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

lisp *error(char *msg, int lispc, ...)
{
  fprintf(stderr, "%s\n", msg);
  
  va_list valist;
  lisp *l;
  va_start(valist, lispc);
  for (int i = 0; i < lispc; i++) {
    l = va_arg(valist, lisp *);
    if (!is_null(l)) {
      prettyPrint(l);
      puts("");
    }
  }

  va_end(valist);

  return mkAtom("nil");
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
  int is_prim = 0;
  if (p && p->atom) {
    for (int i = 0; i < 6; i++)
      is_prim = is_prim || !strcmp(p->atom, (char *) primitive_procedures[i]);
  }
  return is_prim;
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
  if (is_eq(procedure, "car"))
    return car(car(arguments));
  else if (is_eq(procedure, "cdr"))
    return cdr(car(arguments));
  else if (is_eq(procedure, "cons"))
    return cons(car(arguments), cadr(arguments));
  else if (is_eq(procedure, "atom"))
    return atom(car(arguments));
  else if (is_eq(procedure, "eq"))
    return eq(car(arguments), cadr(arguments));
  else if (is_eq(procedure, "null"))
    return null(car(arguments));
  else
    return error("Tried to apply non-primitive procedure", 2, procedure, arguments);
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
      return error("Too many arguments supplied", 2, vars, vals);
    else
      return error("Too few arguments supplied", 2, vars, vals);
}

lisp *enclosing_environment(lisp *env)
{
  return cdr(env);
}

lisp *first_frame(lisp *env)
{
  return car(env);
}

lisp *the_empty_environment()
{
  return mkAtom("nil");
}

lisp *scan(lisp *var, lisp *vars, lisp *vals, lisp *env);

lisp *env_loop(lisp *var, lisp *env)
{
  if (is_eq(env, "nil")) {
    return error("Unbound variable", 1, var);
  } else {
    lisp *frame = first_frame(env);
    return scan(var,
		frame_variables(frame),
		frame_values(frame),
		env);
  }
}

lisp *scan(lisp *var, lisp *vars, lisp *vals, lisp *env)
{
  if (is_null(vars))
    return env_loop(var, enclosing_environment(env));
  if (is_eq(var, car(vars)->atom))
    return car(vals);
  else
    return scan(var, cdr(vars), cdr(vals), env);
}

lisp *lookup_variable_value(lisp *var, lisp *env)
{
  return env_loop(var, env);
}

lisp *apply(lisp *procedure, lisp *arguments)
{
  /* printf("apply : "); */
  /* prettyPrint(procedure); */
  /* printf(" -> "); */
  /* prettyPrint(arguments); */
  /* puts(""); */
  if (is_primitive_procedure(procedure))
    return apply_primitive_procedure(procedure, arguments);
  else if (is_compound_procedure(procedure))
    return eval_sequence(procedure_body(procedure),
			 extend_environment(procedure_parameters(procedure),
					    arguments,
					    procedure_environment(procedure)));
  else
    return error("Unknown procedure type -- APPLY", 1, procedure);
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

int is_symbol(lisp *e)
{
  int isnum = 0;
  if (e && e->atom) {
    isnum = 1;
    for (int i = 0; i < strlen(e->atom); i++)
      isnum = isnum && isalnum(e->atom[i]);
  } 
  return isnum;
}

int is_number(lisp *e)
{
  int isnum = 0;
  if (e && e->atom) {
    isnum = 1;
    for (int i = 0; i < strlen(e->atom); i++)
      isnum = isnum && isdigit(e->atom[i]);
  }
  return isnum;
}

int is_string(lisp *e)
{
  if (e && e->atom) {
    char first = e->atom[0];
    char last = e->atom[strlen(e->atom)-1];
    return (first == '"' && last == '"');
  } else {
    return 0;
  }
}

int is_self_evaluating(lisp *exp)
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

lisp *make_lambda(lisp *parameters, lisp *body)
{
  return cons(mkAtom("lambda"),
	      cons(parameters,
		   body));
}

lisp *definition_value(lisp *exp)
{
  if (is_symbol(cadr(exp)))
    return caddr(exp);
  else
    return make_lambda(cdadr(exp),
		       cddr(exp));
}

lisp *set_variable_value_i(lisp *var, lisp *val, lisp *env)
{
  if (is_eq(env, "nil")) {
    error("Unbound variable -- SET!", 1, var);
  } else {
    lisp *frame = first_frame(env);
    scan(var,
	 frame_variables(frame),
	 frame_values(frame),
	 env);
  }

  return mkAtom("ok");
}

lisp *eval_assignment(lisp *exp, lisp *env)
{
  set_variable_value_i(assignment_variable(exp),
		       eval(assignment_value(exp), env),
		       env);
  return mkAtom("ok");
}

lisp *define_variable_i(lisp *var, lisp *val, lisp *env)
{
  lisp *frame = first_frame(env);
  return scan(var,
	      frame_variables(frame),
	      frame_values(frame),
	      env);
}

lisp *eval_definition(lisp *exp, lisp *env)
{
  define_variable_i(definition_variable(exp),
		    eval(definition_value(exp), env),
		    env);
  return mkAtom("ok");
}

int is_lambda(lisp *exp)
{
  return is_tagged_list(exp, "lambda") || is_tagged_list(exp, "λ");
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
	return error("ELSE clause isn't last -- COND->IF", 1, clauses);
    }
    return NULL;
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
  /* printf("eval  : "); */
  /* prettyPrint(exp); */
  /* puts(""); */
  if (is_self_evaluating(exp))
    return exp;
  else if (is_variable(exp))
    return lookup_variable_value(exp, env);
  else if (is_quoted(exp))
    return text_of_quotation(exp);
  else if (is_assignment(exp))
    return eval_assignment(exp, env);
  else if (is_definition(exp))
    return eval_definition(exp, env);
  else if (is_if(exp))
    return eval_if(exp, env);
  else if (is_lambda(exp)) {
    return make_procedure(lambda_parameters(exp),
			  lambda_body(exp),
			  env);
  }
  else if (is_begin(exp))
    return eval_sequence(begin_actions(exp), env);
  else if (is_cond(exp))
    return eval(cond_if(exp), env);
  else if (is_application(exp)) {
    return apply(operator(exp),
		 list_of_values(operands(exp), env));
  }
  else
    return error("Unknown expression type -- EVAL", 1, exp);
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
