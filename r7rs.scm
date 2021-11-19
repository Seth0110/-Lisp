;; R7RS Base library

;; This file is part of µLisp.

;; µLisp is free software: you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation, either version 3 of the License, or
;; (at your option) any later version.

;; µLisp is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.

;; You should have received a copy of the GNU General Public License
;; along with µLisp.  If not, see <https://www.gnu.org/licenses/>.

;; ...

(define (<= x y)
  (or (< x y) (= x y)))

(define (>= x y)
  (or (> x y) (= x y)))

(define (abs x)
  (if (< x 0)
      (- x)
      x))

(define (append list1 list2)
  (if (null? list1)
      list2
      (cons (car list1) (append (cdr list1) list2))))

;; apply ; Implement in C
;; assoc
;; assq
;; assv
;; binary-port?
;; boolean=?

(define (boolean? x)
  (or (= x #t) (= x #f)))

(define (boolean? b)
  (or (eq? b #t)
      (eq? b #f)))

;; bytevector
;; bytevector-append
;; bytevector-copy
;; bytevector-copy!
;; bytevector-length
;; bytevector-u8-ref
;; bytevector-u8-set!
;; bytevector?

(define (caar x)
  (car (car x)))

(define (cadr x)
  (car (cdr x)))

;; call-with-current-continuation
;; call-with-port
;; call-with-values
;; call/cc
;; case

(define (cdar x)
  (cdr (car x)))

(define (cddr x)
  (cdr (cdr x)))

(define (ceiling x)
  (+ (floor x) 1))

;; char->integer
;; char-ready?
;; char<=?
;; char<?
;; char=?
;; char>=?
;; char>?
;; char?
;; close-input-port
;; close-output-port
;; close-port
;; complex?
;; cond-expand
;; current-error-port
;; current-input-port
;; current-output-port
;; define-record-type
;; define-syntax
;; define-values
;; denominator
;; do
;; dynamic-wind
;; 74
;; Revised7
;; Scheme
;; eof-object
;; eof-object?
;; eqv?
;; error
;; error-object-irritants
;; error-object-message
;; error-object?

(define (even? x)
  (= 0 (remainder x 2)))

;; exact
;; exact-integer-sqrt
;; exact-integer?
;; exact?

(define (expt b n)
  (if (= n 0)
      1
      (* b (expt b (- n 1)))))

;; features
;; file-error?

(define (floor n)
  (- n (remainder n 1)))

;; floor-quotient
;; floor-remainder
;; floor/
;; flush-output-port
;; for-each

(define (gcd a b)
  (if (= b 0)
      a
      (gcd b (remainder a b))))

;; get-output-bytevector
;; get-output-string
;; guard
;; include
;; include-ci
;; inexact
;; inexact?
;; input-port-open?
;; input-port?
;; integer->char
;; integer?
;; lcm

(define (length items)
  (if (null? items)
      0
      (+ 1 (length (cdr items)))))

;; let*
;; let*-values
;; let-syntax
;; let-values
;; letrec
;; letrec*
;; letrec-syntax
;; list->string
;; list->vector
;; list-copy
;; list-ref
;; list-set!
;; list-tail

(define (list? a)
  (not (atom? a)))
  
;; make-bytevector
;; make-list
;; make-parameter
;; make-string
;; make-vector

(define (map proc items)
  (if (null? items)
      nil
      (cons (proc (car items))
            (map proc (cdr items)))))

;; max ; Implement ibn C?

(define (max a b)
  (if (>= a b)
      a
      b))

(define (member item x)
  (cond ((null? x) false)
        ((equal? item (car x)) x)
        (else (memq item (cdr x)))))

(define (memq item x)
  (cond ((null? x) false)
        ((eq? item (car x)) x)
        (else (memq item (cdr x)))))

;; memv
;; min ; Implement in C?

(define (min a b)
  (if (<= a b)
      a
      b))

(define (modulo x y)
  (remainder x y))

(define (negative? n)
  (< n 0))

;; newline

(define nil
  (quote ()))

;; number->string
;; number? ; Implement in C
;; numerator

(define (odd? n)
  (not (even? n)))

;; open-input-bytevector
;; open-input-string
;; open-output-bytevector
;; open-output-string
;; output-port-open?
;; output-port?
;; pair?
;; parameterize
;; peek-char
;; peek-u8
;; port?

(define (positive? n)
  (> n 0))

;; procedure?
;; quasiquote
;; quotient
;; raise
;; raise-continuable
;; rational?
;; rationalize
;; read-bytevector
;; read-bytevector!
;; read-char
;; read-error?
;; read-line
;; read-string
;; read-u8
;; real?

(define (reverse l)
  (if (null? l)
      nil
      (append (reverse (cdr l)) (list (car l)))))

;; round
;; set-car!
;; set-cdr!

(define (square x) (* x x))

;; string
;; string->list
;; string->number
;; string->symbol
;; string->utf8
;; string->vector
;; string-append
;; string-copy
;; string-copy!
;; string-fill!
;; string-for-each
;; string-length
;; string-map
;; string-ref
;; string-set!
;; string<=?
;; string<?
;; string=?
;; string>=?
;; string>?
;; string?
;; substring
;; symbol->string
;; symbol=?
;; symbol?
;; syntax-error
;; syntax-rules
;; textual-port?
;; truncate
;; truncate-quotient
;; truncate-remainder
;; truncate/
;; u8-ready?
;; unless
;; unquote
;; unquote-splicing
;; utf8->string
;; values
;; vector
;; vector->list
;; vector->string
;; vector-append
;; vector-copy
;; vector-copy!
;; vector-fill!
;; vector-for-each
;; vector-length
;; vector-map
;; vector-ref
;; vector-set!
;; vector?
;; when
;; with-exception-handler
;; write-bytevector
;; write-char
;; write-string
;; write-u8

(define (zero? x)
  (= x 0))
