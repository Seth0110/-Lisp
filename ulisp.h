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

#ifndef ULISP
#define ULISP

typedef struct Lisp {
  char *atom;
  struct Lisp *fst;
  struct Lisp *snd;
} lisp;

/* Generated via:
 * grep -E '^[a-z]+ .+\(*?\)$' ulisp.c | sed -E 's/\)$/\);/g; s/^[0-9]+://g'
 */

void freeLisp (lisp *l);
lisp *cons(lisp *a, lisp *b);
lisp *append(lisp *list1, lisp *list2);
lisp *list(int argc, ...);
lisp *primitive_procedures_list();
lisp *car(lisp *l);
void set_car_i(lisp *x, lisp *y);
void set_cdr_i(lisp *x, lisp *y);
int is_eq_str(lisp *a, char *b);
int is_eq(lisp *a, lisp *b);
int is_null(lisp *l);
lisp *cdr(lisp *l);
lisp *mkAtom(char *val);
int atomcmp(lisp *l, char *s);
int is_false(lisp *x);
int is_true(lisp *x);
int ltoi(lisp *l);
int is_atom(lisp *l);
lisp *caar(lisp *l);
lisp *cadr(lisp *l);
lisp *cdar(lisp *l);
lisp *cddr(lisp *l);
lisp *cadar(lisp *l);
lisp *caadr(lisp *l);
lisp *caddr(lisp *l);
lisp *cdadr(lisp *l);
lisp *cadddr(lisp *l);
lisp *cdddr(lisp *l);
int is_equal(lisp *x, lisp *y);
lisp *pairlis(lisp *x, lisp *y, lisp *a);
lisp *assoc(lisp *x, lisp *a);
lisp *error(char *msg, int lispc, ...);
int is_last_exp(lisp *seq);
lisp *first_exp(lisp *seq);
lisp *rest_exps(lisp *seq);
int is_pair(lisp *seq);
int is_tagged_list(lisp *exp, char *tag);
int is_if(lisp *exp);
lisp *if_predicate(lisp *exp);
lisp *if_consequent(lisp *exp);
lisp *if_alternative(lisp *exp);
lisp *make_if(lisp *predicate, lisp *consequent, lisp *alternative);
lisp *eval_if(lisp *exp, lisp *env);
lisp *eval_sequence(lisp *exps, lisp *env);
int is_elem(lisp *a, lisp *l);
int is_primitive_procedure(lisp *p);
lisp *the_empty_environment();
lisp *setup_environment();
lisp *the_global_environment();
int is_compound_procedure(lisp *p);
lisp *make_procedure(lisp *parameters, lisp *body, lisp *env);
lisp *procedure_parameters(lisp *p);
lisp *procedure_body(lisp *p);
lisp *procedure_environment(lisp *p);
int plus(lisp *l);
int subtract(lisp *l);
int minus(lisp *l);
int multiply(lisp *l);
int divide(lisp *l);
int rem(lisp *x, lisp *y);
lisp *num_eq(lisp *l);
lisp *num_gt(lisp *l);
lisp *num_lt(lisp *l);
lisp *itol(int i);
lisp *btol(int b);
lisp *apply_primitive_procedure(lisp *procedure, lisp *arguments);
lisp *make_frame(lisp *variables, lisp *values);
lisp *frame_variables(lisp *frame);
lisp *frame_values(lisp *frame);
void add_binding_to_frame_i(lisp *var, lisp *val, lisp *frame);
lisp *extend_environment(lisp *vars, lisp *vals, lisp *base_env);
lisp *enclosing_environment(lisp *env);
lisp *first_frame(lisp *env);
lisp *env_loop(lisp *var, lisp *env);
lisp *env_scan(lisp *var, lisp *vars, lisp *vals, lisp *env);
lisp *lookup_variable_value(lisp *var, lisp *env);
lisp *apply(lisp *procedure, lisp *arguments);
lisp *evcon(lisp *c, lisp *a);
lisp *evlis(lisp *m, lisp *a);
int is_symbol(lisp *e);
int is_number(lisp *e);
int is_string(lisp *e);
int is_self_evaluating(lisp *exp);
int is_variable(lisp *exp);
int is_quoted(lisp *exp);
lisp *text_of_quotation(lisp *exp);
int is_assignment(lisp *exp);
lisp *assignment_variable(lisp *exp);
lisp *assignment_value(lisp *exp);
int is_definition(lisp *exp);
lisp *definition_variable(lisp *exp);
lisp *make_lambda(lisp *parameters, lisp *body);
lisp *definition_value(lisp *exp);
lisp *set_variable_value_i(lisp *var, lisp *val, lisp *env);
void def_scan(lisp *var, lisp *val, lisp *vars, lisp *vals, lisp *frame);
lisp *eval_assignment(lisp *exp, lisp *env);
void define_variable_i(lisp *var, lisp *val, lisp *env);
lisp *eval_definition(lisp *exp, lisp *env);
int is_lambda(lisp *exp);
lisp *lambda_parameters(lisp *exp);
lisp *lambda_body(lisp *exp);
lisp *make_begin(lisp *seq);
lisp *sequence_exp(lisp *seq);
int is_application(lisp *exp);
lisp *operator(lisp *exp);
lisp *operands(lisp *exp);
int is_no_operands(lisp *ops);
lisp *first_operand(lisp *ops);
lisp *rest_operands(lisp *ops);
int is_cond(lisp *exp);
lisp *cond_clauses(lisp *exp);
lisp *cond_predicate(lisp *clause);
int is_cond_else_clause(lisp *clause);
lisp *cond_actions(lisp *clause);
lisp *expand_clauses(lisp *clauses);
lisp *cond_if(lisp *exp);
lisp *list_of_values(lisp *exps, lisp *env);
lisp *begin_actions(lisp *exp);
int is_begin(lisp *exp);
lisp *eval(lisp *exp, lisp *env);
int length(lisp *l);
void showLisp (lisp *l);
lisp *nth(lisp *l, int i);
void prettyPrint(lisp *l);

#endif
