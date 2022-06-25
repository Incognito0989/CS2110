;; Timed Lab 3
;; Student Name:

;; Please read the PDF for full directions.
;; The pseudocode for the program you must implement is listed below; it is also listed in the PDF.
;; If there are any discrepancies between the PDF's pseudocode and the pseudocode below, notify a TA immediately.
;; However, in the end, the pseudocode is just an example of a program that would fulfill the requirements specified in the PDF.

;; Pseudocode:
;; // (checkpoint 1)
;; int MAX(int a, int b) {
;;   if (a > b) {
;;       return 0;
;;   } else {
;;       return 1;
;;   }
;; }
;;
;;
;;
;;
;; DIV(x, y) {
;;	   // (checkpoint 2) - Base Case
;;     if (y > x) {
;;         return 0;
;;     // (checkpoint 3) - Recursion
;;     } else {
;;         return 1 + DIV(x - y, y);
;;     }
;; }
;;
;;
;;
;; // (checkpoint 4)
;; void MAP(array, length) {
;;   int i = 0;
;;   while (i < length) {
;;      int firstElem = arr[i];
;;      int secondElem = arr[i + 1];
;;      int div = DIV(firstElem, secondElem);
;;      int offset = MAX(firstElem, secondElem);
;;      arr[i + offset] = div;
;;      i += 2;
;;   }
;; }


.orig x3000
HALT

STACK .fill xF000

; DO NOT MODIFY ABOVE


; START MAX SUBROUTINE
MAX


    ADD R6, R6, -4  ; make space for RA, RV, old FP and one local
    STR R7, R6, 2   ; save return address
    STR R5, R6, 1   ; saves old frame pointer
    ADD R5, R6, 0   ; point frame pointer at the first local variable
    ADD R6, R6, -5  ; allocate space to save all five registers R0-R4 and space for 
                                    ;four local variables
    ; save registers
    STR R0, R6, 0
    STR R1, R6, 1
    STR R2, R6, 2
    STR R3, R6, 3
    STR R4, R6, 4

;main method
LDR R1, R5, 5			;LOAD B
LDR R2, R5, 4			;LOAD A

NOT R1, R1				;NEATIVE B
ADD R1, R1, 1

ADD R3, R2, R1			;A - B
BRnz ELSE
	AND R0, R0, 0		;RETURN 0
	BR TEARDOWN
ELSE
	AND R0, R0, 0		;RETURN 1
	ADD R0, R0, 1
	BR TEARDOWN


 TEARDOWN               ;SAVE THE VALUE IN R0 IN THE STACK AS OUR RETURN VALUE
    ; save the value in R0 on the stack as our return value
    STR R0, R5, 3

    ; restore registers
    LDR R0, R6, 0
    LDR R1, R6, 1
    LDR R2, R6, 2
    LDR R3, R6, 3
    LDR R4, R6, 4

    ; restore return address, frame pointer, and move R6 to RV
    ADD R6, R5, 0
    LDR R5, R6, 1
    LDR R7, R6, 2
    ADD R6, R6, 3



; !!!!! WRITE YOUR CODE HERE !!!!!



RET
; END MAX SUBROUTINE




; START DIV SUBROUTINE
DIV

    ADD R6, R6, -4  ; make space for RA, RV, old FP and one local
    STR R7, R6, 2   ; save return address
    STR R5, R6, 1   ; saves old frame pointer
    ADD R5, R6, 0   ; point frame pointer at the first local variable
    ADD R6, R6, -5  ; allocate space to save all five registers R0-R4 and space for 
                                    ;four local variables
    ; save registers
    STR R0, R6, 0
    STR R1, R6, 1
    STR R2, R6, 2
    STR R3, R6, 3
    STR R4, R6, 4


;MAIN METHOD
	LDR R1, R5, 5		;LOAD Y
	LDR R2, R5, 4		;LOAD X
	
	ADD R6, R6, -1
	STR R2, R6, 0		;STORE Y

	ADD R6, R6, -1
	STR R1, R6, 0		;STORE X
	JSR MAX				;CALL MAX
	LDR R0, R6, 0		;LOAD RETURN
	ADD R6, R6, 3		;POP R6

	ADD R0, R0, 0		;Y>X THEN RETURN WILL BE 1
						;x>y max is 0
						;x<= y
	BRp ELSE1
		AND R0, R0, 0
		BR TEARDOWN


	ELSE1
		NOT R4, R1		;NOT Y
		ADD R4, R4, 1	;ADD 1

		ADD R3, R4, R2	;X-Y
		ADD R6, R6, -1	;MAKE SPACE ON STACK
		STR R1, R6, 0	;PUSH Y
		ADD R6, R6, -1	;MAKE SPACE ON STACK
		STR R3, R6, 0	;PUSH X-Y
		JSR DIV
		LDR R0, R6, 0	;LOAD RETURN
		ADD R6, R6, 3	;POP R6
		ADD R0, R0, 1	;PLUS 1
		BR TEARDOWN



RET
; END DIV SUBROUTINE



; START MAP SUBROUTINE
MAP

    ADD R6, R6, -4  ; make space for RA, RV, old FP and one local
    STR R7, R6, 2   ; save return address
    STR R5, R6, 1   ; saves old frame pointer
    ADD R5, R6, 0   ; point frame pointer at the first local variable
    ADD R6, R6, -5  ; allocate space to save all five registers R0-R4 and space for 
                                    ;four local variables
    ; save registers
    STR R0, R6, 0
    STR R1, R6, 1
    STR R2, R6, 2
    STR R3, R6, 3
    STR R4, R6, 4


;MAIN METHOD
	LDR R1, R5, 5		;LOAD LENGTH IN R1
	LDR R2, R5, 4		;LOAD ARRAY IN R2
	AND R0, R0, 0
	STR R0, R5, 0		;LOCAL VAR IS COUNTER

	LOOP
		LDR R3, R5, 0	;LOAD I
		NOT R4, R3
		ADD R4, R4, 1	;NEGATIVE I
		LDR R1, R5, 5	;LOAD LENGTH
		ADD R4, R1, R4 	;I < LENGTH     length - i
		BRnz TEARDOWN
			LD R0, ARRAY 	;LOAD ARRAY
			LDR R2, R5, 0	;LOAD COUNTER

			ADD R1, R0, R2	;GO TO ADDRESS ARR[I]
			LDR R1, R1, 0	;GET VAL OF ARR[I]

			ADD R3, R0, R2	;GO TO ADDRESS ARR[I]
			ADD R4, R3, 1	;GO TO ADDRESS ARR[I + 1]
			LDR R4, R4, 0	;GET VAR AT ARR[I + 1]

			ADD R6, R6, -1	;MAKE SPACE ON STACK
			STR R4, R6, 0	;STORE ARR[I + 1]
			ADD R6, R6, -1	;MAKE SPACE ON STACK
			STR R1, R6, 0	;PUSH ARR[I]
			
			JSR DIV
			LDR R0, R6, 0	;LOAD RETURN
			AND R4, R4, 0
			ADD R4, R4, R0
			ADD R6, R6, 1	;POP RETURN VAL
			JSR MAX
			LDR R1, R6, 0	;LOAD RETURN OFFSET
			ADD R6, R6, 3	;RESTORE R6

			;R0,R1 CANT CHANGE RN
			LD R2, ARRAY 	;LOAD ARRAY
			LDR R3, R5, 0	;LOAD COUNTER I
			ADD R2, R2, R3	;ARR[I]
			ADD R2, R2, R1	;ARR[I + OFFSET]
			STR R4, R2, 0	;STORE DIV IN ARR[I + OFFSET]
			ADD R3, R3, 2	;I += 2
			STR R3, R5, 0	;STORE I AS LOCAL VAR

			BR LOOP




RET
; END MAP SUBROUTINE


; LENGTH FOR TESTING

LENGTH .fill x12

; ARRAY FOR TESTING
ARRAY .fill x4000

.end

.orig x4000
.fill 12
.fill 3
.fill 5
.fill 7
.fill 16
.fill 2
.fill 5
.fill 5
.fill 25
.fill 7
.fill 48
.fill 60
.end
