;;=======================================
;; CS 2110 - Fall 2021
;; Final Exam - Modulo
;;=======================================
;; Name: ANDREW JONES
;;=======================================

;; In this file, you must implement the 'mod' subroutine.

;; Little reminder from your friendly neighborhood 2110 TA staff:
;; don't run this directly by pressing 'RUN' in Complx, since there is nothing
;; put at address x3000. Instead, load it and use 'Debug' -> 'Simulate
;; Subroutine Call' and choose the 'mod' label.


.orig x3000
HALT

mod
;; See the PDF for more information on what this subroutine should do.
;;
;; Arguments of mod: integer a, positive integer b
;;
;; Pseudocode:
;; 
;; mod(a, b) {
;;     if (a < 0) {
;;         return mod(a + b, b);
;;     }
;;
;;     if (a < b) {
;;         return a;
;;     }
;;
;;     return mod(a - b, b);
;; }
;;
    ;;pre setup of stack stuff

ADD R6, R6, -4			; Allocate space
STR R7, R6, 2			; Save Ret Addr
STR R5, R6, 1			; Save Old FP
ADD R5, R6, 0			; Copy SP to FP
ADD R6, R6, -5			; Make room for saved regs & l.v. 1-n
STR R0, R5, -1			;Save R0
STR R1, R5, -2			;Save R1
STR R2, R5, -3			;Save R2
STR R3, R5, -4			;Save R3
STR R4, R5, -5			;Save R4


LDR R1, R5, 5			;LOAD B INTO R1
LDR R2, R5, 4			;LOAD A INTO R2

;IF A < 0
NOT R3, R2
ADD R3, R3, 1
ADD R3, R2, R3			;A-A
BRzp ELSE
	ADD R2, R2, R1		;A + B
	ADD R6, R6, -1		;MAKE SPACE ON STACK
	STR R1, R6, 0		;PUSH B
	ADD R6, R6, -1		;MAKE SPACE ON STACK
	STR R2, R6, 0		;PUSH (A + B)
	JSR mod
	LDR R0, R6, 0		;SAVE RETURN
	ADD R6, R6, 3		;POPS RETURN AND PARAMS
	BR TEARDOWN

ELSE
	NOT R3, R1
	ADD R3, R3, 1		;NOT B
	ADD R3, R3, R2		;A - B
	BRzp ELSE2
		AND R0, R0, 0	;RO = 0
		ADD R0, R0, R2	;R0 = A
		BR TEARDOWN
	ELSE2
		NOT R3, R1		;NOT B
		ADD R3, R3, 1
		ADD R2, R2, R3	;A-B
		ADD R6, R6, -1		;MAKE SPACE ON STACK
		STR R1, R6, 0		;PUSH B
		ADD R6, R6, -1		;MAKE SPACE ON STACK
		STR R2, R6, 0		;PUSH (A + B)
		JSR mod
		LDR R0, R6, 0		;SAVE RETURN
		ADD R6, R6, 3		;POPS RETURN AND PARAMS
		BR TEARDOWN

 TEARDOWN

;;post method
;LDR R0, R5, 0
STR R0, R5, 3			; save return value on stack
LDR R4, R5, -5			; Restore R4
LDR R3, R5, -4			; Restore R3
LDR R2, R5, -3			; Restore R2
LDR R1, R5, -2			; Restore R1
LDR R0, R5, -1			; Restore R0
ADD R6, R5, 0			; Restore SP
LDR R5, R6, 1			; Restore FP
LDR R7, R6, 2			; Restore RA
ADD R6, R6, 3			; Pop RA,FP,1st local variable
    
    ;; YOUR CODE HERE


RET

;; Needed by Simulate Subroutine Call in Complx
STACK .fill xF000
.end