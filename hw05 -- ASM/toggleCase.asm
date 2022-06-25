;;=============================================================
;; CS 2110 - Fall 2021
;; Homework 5 - Toggle Case
;;=============================================================
;; Name: (Your name Here)
;;=============================================================

;; Pseudocode (see PDF for explanation):
;;
;;	string = "Assembly is interesting"; // given string
;;	Array[string.len()] answer; // array to store the result string
;;	i = 0;
;;
;;	while (string[i] != '\0') {
;;	    if (string[i] == " ") {
;;	        answer[i] = " ";
;;	    } else if (string[i] >= "A" && string[i] <= "Z") {
;;	        answer[i] = string[i].lowerCase();
;;	    } else {
;;	        answer[i] = string[i].upperCase();
;;	    }
;;	    i++;
;;	}


.orig x3000

AND R0, R0, #0		;SETS COUNTER
ADD R0, R0, #-1

LOOP
	ADD R0, R0, #1
	LD R1, STRING
	ADD R1, R1, R0
	LDR R1, R1, #0		;LOADED STRING CHAR INTO R1
	NOT R2, R1
	ADD R2, R2, #1		;NEGATIVE STRING CHAR
	AND R3, R2, #-1
	BRz ENDLOOP			;ENDS LOOP IF THE CHAR IS \0

	LD R3, SPACE		;ADDS SPACE TO ANSWER
	ADD R3, R3, R2
	BRnp IF1END
			LD R3, ANSWER
			ADD R3, R3, R0
			STR R1, R3, #0
			BR LOOP

	IF1END

	LD R3, A
	NOT R3, R3
	ADD R3, R3, #1
	ADD R3, R1, R3
	BRn IF2END
			LD R3, Z
			ADD R3, R3, R2
			BRzp IF2A
			BR IF2END
				IF2A
					LD R3, ANSWER
					LD R4, SPACE
					ADD R3, R3, R0
					ADD R5, R1, R4
					STR R5, R3, #0
					BR LOOP
	IF2END
	
	LD R3, ANSWER
	LD R4, SPACE
	NOT R4, R4
	ADD R4, R4, #1
	ADD R3, R3, R0		;ANSWER ADDRESS
	ADD R5, R1, R4		;TO upper CASE
	STR R5, R3, #0
	BR LOOP


ENDLOOP

;; READ LINE 40
;; put your code here

			LD R3, ANSWER
			ADD R3, R3, R0
			LD R4, SZ
			STR R4, R3, #0

HALT


;; ASCII table: https://www.asciitable.com/


;; FILL OUT THESE ASCII CHARACTER VALUE FIRST TO USE IT IN YOUR CODE
SPACE	.fill x20
SZ 		.fill x00
A		.fill x41
Z		.fill x5a
a       .fill x61
z       .fill x7a
BREAK	.fill x5D	;; this is the middle of uppercase and lowercase characters

STRING .fill x4000
ANSWER .fill x4100
.end

.orig x4000
.stringz "Assembly is INTERESTING"
.end

.orig x4100
.blkw 23
.end

;COMMENTS ON CODE
;error on the br... need to change nzp
	;the to lower case is not working