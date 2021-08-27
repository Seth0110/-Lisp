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
 * grep -E '^[a-z]+ .+\(*?\)$' ulisp.c | sed -E 's/\)$/\);/g; s/^[0-9]+://g' | sort
 */

double divide(lisp *l);
double ltof(lisp *l);
double minus(lisp *l);
double multiply(lisp *l);
double plus(lisp *l);
double rem(lisp *x, lisp *y);
double subtract(lisp *l);
int atomcmp(lisp *l, char *s);
int is_application(lisp *exp);
int is_assignment(lisp *exp);
int is_atom(lisp *l);
int is_begin(lisp *exp);
int is_compound_procedure(lisp *p);
int is_cond_else_clause(lisp *clause);
int is_cond(lisp *exp);
int is_definition(lisp *exp);
int is_double(lisp *e);
int is_elem(lisp *a, lisp *l);
int is_eq(lisp *a, lisp *b);
int is_eq_str(lisp *a, char *b);
int is_equal(lisp *x, lisp *y);
int is_false(lisp *x);
int is_if(lisp *exp);
int is_int(lisp *e);
int is_lambda(lisp *exp);
int is_last_exp(lisp *seq);
int is_no_operands(lisp *ops);
int is_null(lisp *l);
int is_number(lisp *e);
int is_pair(lisp *seq);
int is_primitive_procedure(lisp *p);
int is_quoted(lisp *exp);
int is_self_evaluating(lisp *exp);
int is_string(lisp *e);
int is_symbol(lisp *e);
int is_tagged_list(lisp *exp, char *tag);
int is_true(lisp *x);
int is_variable(lisp *exp);
int length(lisp *l);
lisp *append(lisp *list1, lisp *list2);
lisp *apply(lisp *procedure, lisp *arguments);
lisp *apply_primitive_procedure(lisp *procedure, lisp *arguments);
lisp *assignment_value(lisp *exp);
lisp *assignment_variable(lisp *exp);
lisp *assoc(lisp *x, lisp *a);
lisp *begin_actions(lisp *exp);
lisp *btol(int b);
lisp *caadr(lisp *l);
lisp *caar(lisp *l);
lisp *cadar(lisp *l);
lisp *cadddr(lisp *l);
lisp *caddr(lisp *l);
lisp *cadr(lisp *l);
lisp *car(lisp *l);
lisp *cdadr(lisp *l);
lisp *cdar(lisp *l);
lisp *cdddr(lisp *l);
lisp *cddr(lisp *l);
lisp *cdr(lisp *l);
lisp *cond_actions(lisp *clause);
lisp *cond_clauses(lisp *exp);
lisp *cond_if(lisp *exp);
lisp *cond_predicate(lisp *clause);
lisp *cons(lisp *a, lisp *b);
lisp *definition_value(lisp *exp);
lisp *definition_variable(lisp *exp);
lisp *enclosing_environment(lisp *env);
lisp *env_loop(lisp *var, lisp *env);
lisp *env_scan(lisp *var, lisp *vars, lisp *vals, lisp *env);
lisp *error(char *msg, int lispc, ...);
lisp *eval_assignment(lisp *exp, lisp *env);
lisp *eval_definition(lisp *exp, lisp *env);
lisp *eval_if(lisp *exp, lisp *env);
lisp *eval(lisp *exp, lisp *env);
lisp *eval_sequence(lisp *exps, lisp *env);
lisp *expand_clauses(lisp *clauses);
lisp *extend_environment(lisp *vars, lisp *vals, lisp *base_env);
lisp *first_exp(lisp *seq);
lisp *first_frame(lisp *env);
lisp *first_operand(lisp *ops);
lisp *frame_values(lisp *frame);
lisp *frame_variables(lisp *frame);
lisp *ftol(double f);
lisp *if_alternative(lisp *exp);
lisp *if_consequent(lisp *exp);
lisp *if_predicate(lisp *exp);
lisp *lambda_body(lisp *exp);
lisp *lambda_parameters(lisp *exp);
lisp *list(int argc, ...);
lisp *list_of_values(lisp *exps, lisp *env);
lisp *lookup_variable_value(lisp *var, lisp *env);
lisp *make_begin(lisp *seq);
lisp *make_frame(lisp *variables, lisp *values);
lisp *make_if(lisp *predicate, lisp *consequent, lisp *alternative);
lisp *make_lambda(lisp *parameters, lisp *body);
lisp *make_procedure(lisp *parameters, lisp *body, lisp *env);
lisp *mkAtom(char *val);
lisp *nth(lisp *l, int i);
lisp *num_eq(lisp *l);
lisp *num_gt(lisp *l);
lisp *num_lt(lisp *l);
lisp *operands(lisp *exp);
lisp *operator(lisp *exp);
lisp *pairlis(lisp *x, lisp *y, lisp *a);
lisp *primitive_procedures_list();
lisp *procedure_body(lisp *p);
lisp *procedure_environment(lisp *p);
lisp *procedure_parameters(lisp *p);
lisp *rest_exps(lisp *seq);
lisp *rest_operands(lisp *ops);
lisp *sequence_exp(lisp *seq);
lisp *setup_environment();
lisp *set_variable_value_i(lisp *var, lisp *val, lisp *env);
lisp *text_of_quotation(lisp *exp);
lisp *the_empty_environment();
lisp *the_global_environment();
lisp *to_list(lisp *l);
void add_binding_to_frame_i(lisp *var, lisp *val, lisp *frame);
void define_variable_i(lisp *var, lisp *val, lisp *env);
void def_scan(lisp *var, lisp *val, lisp *vars, lisp *vals, lisp *frame);
void freeLisp (lisp *l);
void prettyPrint(lisp *l);
void set_car_i(lisp *x, lisp *y);
void set_cdr_i(lisp *x, lisp *y);
void showLisp (lisp *l);

#endif
