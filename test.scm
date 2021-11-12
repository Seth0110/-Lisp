;; Test script for uLisp

;; Self-evaluating
1
"a"
#t

;; Primitive procedures
(car (quote (a b)))
(cdr (quote (a b)))
(cons (quote a) (quote (b)))
(atom? (quote a))
(eq? (quote a) (quote a))
(null? (quote nil))

;; Special forms
(if #t (quote a) (quote b))
((lambda (x) (atom? x)) (quote a))
(begin (eq? 1 0) (eq? 1 1))
(cond ((eq? 1 0) (quote a)) (else (quote b)))
(define ten 10)
ten

;; Compound procedures
(define (succ x)
  (+ x 1))
(succ 1)

;; Recursion
(define (factorial n)
  (if (= n 1)
      1
      (* n (factorial (- n 1)))))
(factorial 6)

;; Let
(let ((x 3) (y 4) (z 5)) (+ x y z))

;; Inner Defines
(define (f x)
  (define (g y)
    (+ y 1))
  (g x))
(f 2)
