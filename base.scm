;; R7RS Base library
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

;; apply
;; assoc
;; assq
;; assv
;; binary-port?
;; boolean=?
;; boolean?
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
;; expt
;; features
;; file-error?

(define (floor n)
  (- n (remainder n 1)))

;; floor-quotient
;; floor-remainder
;; floor/
;; flush-output-port
;; for-each
;; gcd
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
;; length
;; let
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
;; list?
;; make-bytevector
;; make-list
;; make-parameter
;; make-string
;; make-vector

(define (map f xs)
  (if (null? xs)
      nil
      (cons (f (car xs))
	    (map f (cdr xs)))))

;; max

;; (define (member item x)
;;   (cond ((null? x) #f)
;; 	((equal? item (car x)) x)
;; 	(else (member item (cdr x)))))

;; (define (memq item x)
;;   (cond ((null? x) #f)
;; 	((eq? item (car x)) x)
;; 	(else (memq item (cdr x)))))

;; memv
;; min

(define (modulo x y)
  (remainder x y))

(define (negative? n)
  (< n 0))

;; newline

(define nil
  (quote ()))

;; number->string
;; number?
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
;; reverse
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

;; Base Test - Everything should return #t
; (<= 0 1)
; (>= 1 0)
; (= (abs -1) 1)
; (equal? (append (quote (a)) (quote (b c))) (quote (a b c)))
; (even? 10)
; (= (floor 1.5) 1)
(map odd? (quote (1 2 3)))
; (= (modulo 17 3) 2)
; (negative? -1)
; (odd? 3)
; (positive? 3)
; (= (square 3) 9)
; (zero? 0)
