;;=============================================================
;; CS 2110 - Fall 2021
;; Homework 6 - Linked List Sum
;;=============================================================
;; Name: ANDREW JONES
;;============================================================

;; In this file, you must implement the 'llsum' subroutine.

;; Little reminder from your friendly neighborhood 2110 TA staff: don't run
;; this directly by pressing 'RUN' in complx, since there is nothing put at
;; address x3000. Instead, load it and use 'Debug' -> 'Simulate
;; Subroutine Call' and choose the 'reverseCopy' label.

.orig x3000
HALT

;; Pseudocode (see PDF for explanation):
;;
;; Arguments of llsum: Node head
;;
;; llsum(Node head) {
;;     // note that a NULL address is the same thing as the value 0
;;     if (head == NULL) {
;;         return 0;
;;     }
;;     Node next = head.next;
;;     sum = head.data + llsum(next);
;;     return sum;
;; }

llsum

;; YOUR CODE HERE
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


    LDR R0, R5, 4   	; R0 = N
    BRz RETURN0    	; if node = 0 return 0
    	LDR R4, R0, 1		;DATA AT CURR
    	LDR R1, R0, 0		;curr DATA = head.next
    	ADD R6, R6, -1		
    	STR R1, R6, 0		;ADD CURR DATA TO STACK
  		
  		JSR llsum

  		LDR R0, R6, 0		;RETURN VALUE
  		ADD R0, R4, R0
  		ADD R6, R6, 2		;POP

  		BR TEARDOWN

    RETURN0				;RETURN 1 teardown
    AND R0, R0, 0		;R0 = 0
    STR R0, R5, 0



 TEARDOWN 				;SAVE THE VALUE IN R0 IN THE STACK AS OUR RETURN VALUE
STR R0, R5, 3

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

RET

;; used by the autograder
STACK .fill xF000
.end

;; The following is an example of a small linked list that starts at x4000.
;;
;; The first number (offset 0) contains the address of the next node in the
;; linked list, or zero if this is the final node.
;;
;; The second number (offset 1) contains the data of this node.

.orig x4000
.fill x4008
.fill 5
.end

.orig x4008
.fill x4010
.fill 12
.end

.orig x4010
.fill 0
.fill -7
.end
