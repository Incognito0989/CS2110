;;=============================================================
;; CS 2110 - Fall 2021
;; Homework 5 - Square
;;=============================================================
;; Name: Andrew Jones
;;=============================================================

;; Pseudocode (see PDF for explanation)
;; a = (argument 1);
;; ANSWER = 0;
;; for (int i = 0; i < a; i++) {
;;		ANSWER += a;
;; }
;; return ANSWER;

.orig x3000

;R3 = A
LD R1, A    ;ITERATOR --
LD R2, ANSWER
AND R2, R2, #0
LD R3, A

;while R1 > 0
LOOP ADD R1, R1, #0
	BRnz ENDLOOP
	ADD R2, R2, R3;
	ADD R1, R1, #-1
	BR LOOP
;;put your code here
ENDLOOP
ST R2, ANSWER
HALT


A .fill 9

ANSWER .blkw 1

.end
