;;=============================================================
;; CS 2110 - Fall 2021
;; Homework 5 - Array Modify
;;=============================================================
;; Name: (Your name Here)
;;=============================================================

;; Pseudocode (see PDF for explanation)
;;
;;    i = 0; // first index 
;;    len = Len(ARR_X);
;;
;;    while (i < len) {
;;        if (i % 2 == 0) {
;;            //if we are at an even index, subtract 10 and save it to the array at that index 
;;    	    ARR_Y[i] = ARR_X[i] - 10];
;;        } else {
;;            //if we are at odd index, multiply by 2 and save it to the array at that index 
;;    	    ARR_Y[i] = ARR_X[i] * 2;
;;        }
;;        	i++;
;;    }

.orig x3000

AND R5, R5, #0		;R5 IS COUNTER ++
LD R1, LENGTH		;R1 IS POSITIVE LENGTH
AND R3, R3, #0
ADD R3, R3, R1
NOT R3, R3			;R3 IS NEGATIVE LENGTH
ADD R3, R3, #1
AND R2, R2, #0
 
LOOP	ADD R2, R2, R3
	BRz END 				;IF I < LEN
		;AND R2, R2, #1
		;AND R2, R2, R5		;IF R2 % 2 == 0
		AND R2, R5, #1
		BRnp IFE1
			;ARR_Y[i] = ARR_X[i] - 10;
		;	LEA R5, ARR_X
		;	LEA R4, ARR_Y
		;	ADD R4, R4, R0
		;	ADD R5, R5, R0
		;	LDR R5, R5, #0
		;	ADD R5, R5, #-10
		;	STR R5, R4, #0
			LD R0, ARR_X
			ADD R0, R0, R5
			LDR R4, R0, #0
			ADD R4, R4, #-10
			LD R0, ARR_Y
			ADD R0, R0, R5
			STR R4, R0, #0

		IFE1
		;AND R2, R2, #1
		;AND R2, R2, R0		;IF R2 % 2 != 0				ODDS
		AND R2, R5, #1
		BRnz IFE2
			;ARR_Y[i] = ARR_X[i] * 2
		;	LEA R5, ARR_X
		;	LEA R4, ARR_Y
		;	ADD R4, R4, R0
		;	ADD R5, R5, R0
		;	LDR R5, R5, #0
		;	ADD R5, R5, R5
		;	STR R5, R4, #0
			LD R0, ARR_X
			ADD R0, R0, R5
			LDR R4, R0, #0
			ADD R4, R4, R4
			LD R0, ARR_Y
			ADD R0, R0, R5
			STR R4, R0, #0
		IFE2
	AND R2, R2, #0
	ADD R2, R2, R5
	ADD R5 , R5, #1
	BR LOOP

;XXXXXXX current issue is that im not storing in right location. needs to store at x4100 but is not i think.
;CURRENT ISSUE IS THAT THE IF STATEMENTS ARE INCORRECT AND NOT SAVING CORRECT VALUES FOR THE ODD INDEXES

;;put your code here
END

HALT

ARR_X       .fill x4000
ARR_Y       .fill x4100
LENGTH      .fill 4
.end

.orig x4000
.fill 1
.fill 5
.fill 10
.fill 11
.end

.orig x4100
.blkw 4
.end
