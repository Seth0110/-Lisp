;; R7RS Base library
;; ...

(define (<= x y)
  (if (or (< x y) (= x y))
      true
      false))

(define (>= x y)
  (if (or (> x y) (= x y))
      true
      false))

(define (abs x)
  (if (< x 0)
      (- x)
      x))

(define (and xs)
  (if (not (car xs))
      #f
      (and (cdr xs))))

(define (append x y)
  (if (null? x)
      y
      (cons (car x) (append (cdr x) y))))

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
;; call-with-current-continuation
;; call-with-port
;; call-with-values
;; call/cc
;; case
;; ceiling
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

(define (even? n)
  (= 0 (remainder x 2)))

;; exact
;; exact-integer-sqrt
;; exact-integer?
;; exact?
;; expt
;; features
;; file-error?

(define (floor n)
  (+ n (remainder 1 n)))

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

;; (define (map f xs)
;;   (if (null? xs)
;;       nil
;;       (cons (f (car x))
;; 	    (map f (cdr xs)))))

;; max

;; (define (member item x)
;;   (cond ((null? x) false)
;; 	((equal? item (car x)) x)
;; 	(else (member item (cdr x)))))

;; (define (memq item x)
;;   (cond ((null? x) false)
;; 	((eq? item (car x)) x)
;; 	(else (memq item (cdr x)))))

;; memv
;; min

(define (modulo x y)
  (remainder x y))

(define (negative? n)
  (< 0 n))

;; newline

(define (not x)
  (if x
      #f
      #t))

;; number->string
;; number?
;; numerator

(define (odd? n)
  (not (even? n)))

;; open-input-bytevector
;; open-input-string
;; open-output-bytevector
;; open-output-string

(define (or xs)
  (if (car xs)
      #t
      (or (cdr xs))))

;; output-port-open?
;; output-port?
;; pair?
;; parameterize
;; peek-char
;; peek-u8
;; port?

(define (positive? n)
  (> 0 n))

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
  (eq? x 0))

;;(<= 0 1)
;;(>= 1 0)
(abs -1)
;; (and #t #t)
;; (append (quote (a)) (quote b))
;; (even? 10)
(floor 1.5)
(modulo 3 2)
;; (negative? -1)
;; (not #f)
;; (odd? 3)
;; (or #f #t)
;; (positive? 3)
;; (square 3)
(zero? 0)
