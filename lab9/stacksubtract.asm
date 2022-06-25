;;=======================================
;; CS 2110 - Fall 2021
;; Lab 9 - stacksubtract.asm
;;=======================================
;; Name:
;;=======================================

;; Welcome to your Stack Safari!
;; You are implementing the following pseudocode.
;; Please check the lab slides for additional details on the stack.
;;
;; void main () {
;;     int a = MEM[A];
;;     int b = MEM[B];
;;     MEM[RESULT] = subtract(a,b);
;; }
;;
;; int subtract (int a, int b) {
;;     return a + (-b);
;; }

.orig x3000
LD R6, STACK

;; WRITE MAIN HERE

;; END MAIN
HALT


A      .fill 4
B      .fill -9
RESULT .blkw 1


;; calculate a - b
subtract
;; WRITE SUBTRACT HERE

;; STACK SETUP

;; EXTRACT ARGUMENTS

;; PERFORM SUBTRACTION

;; STORE RETURN VALUE

;; STACK TEARDOWN AND RETURN

;; END SUBTRACT CODE

STACK .fill xF000
.end
