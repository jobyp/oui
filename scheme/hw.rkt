#!/usr/bin/env racket

#lang racket

(define extract
  (lambda (str)
    (substring str 4 7)))

(extract "the cat is out of the bag")

(define (startswith s prefix)
  (equal? prefix (substring s 0 (string-length prefix))))

(define reply-more
  (lambda (s)
    (cond 
     ((startswith s "hello") "hi!")
     (else "huh?"))))

(define (game)
  (let ((x (random 4))
	(y (random 4)))
    (cond 
     ((> x y) "X wins")
     ((> y x) "Y wins")
     (else "cat's game"))))
  
