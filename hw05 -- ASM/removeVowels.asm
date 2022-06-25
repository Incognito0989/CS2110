;;=============================================================
;; CS 2110 - Fall 2021
;; Homework 5 - Remove Vowels
;;=============================================================
;; Name: Andrew Jones
;;=============================================================

;; Pseudocode (see PDF for explanation)
;; STRING = (argument 1);
;; ANSWER = "";
;; for (int i = 0; i < a.length; i++) {
;;       if (string[i] == '\0'){
;;          break
;;        }

;;       if (string[i] == ’A’) {
;;           continue;
;;        } else if (string[i] == ’E’) {
;;            continue;
;;        } else if (string[i] == ’I’) {
;;            continue;
;;        } else if (string[i] == ’O’) {
;;            continue;
;;        } else if (string[i] == ’U’) {
;;            continue;
;;        } else if (string[i] == ’a’) {
;;            continue;
;;        } else if (string[i] == ’e’) {
;;            continue;
;;        } else if (string[i] == ’i’) {
;;            continue;
;;        } else if (string[i] == ’o’) {
;;            continue;
;;        } else if (string[i] == 'u') {
;;            continue;
;;        }
;;
;;        ANSWER += STRING[i];
;;	}
;;  ANSWER += '\0';
;;
;;  return ANSWER;
;; }


.orig x3000

AND R0, R0, #0		;COUNTER OF ANSWER STRING
AND R1, R1, #0		;COUNTER OF STRING CHAR LOCATION
ADD R1, R1, #-1

LOOP
	ADD R1, R1, #1		;COUNTS STRING CHAR

		LD R3, STRING
		ADD R3, R3, R1	
		LDR R3, R3, #0		;DATA IN STRING[I]
		NOT R4, R3			
		ADD R4, R4, #1		;NEGATIVE DATA


		LD R5, SZ 			;IF \0
		ADD R5, R5, R4
		BRz ENDCONDITION

		AND R5, R3, #-1
		BRz ENDCONDITION
		
		LD R5, A 			;IF A
		ADD R5, R5, R4
		BRz LOOP
		LD R5, LOWERA
		ADD R5, R5, R4
		BRz LOOP


		LD R5, E 			;IF E
		ADD R5, R5, R4
		BRz LOOP
		LD R5, LOWERE
		ADD R5, R5, R4
		BRz LOOP

		
		LD R5, I 			;IF I
		ADD R5, R5, R4
		BRz LOOP
		LD R5, LOWERI
		ADD R5, R5, R4
		BRz LOOP


		LD R5, O 			;IF O
		ADD R5, R5, R4
		BRz LOOP
		LD R5, LOWERO
		ADD R5, R5, R4
		BRz LOOP


		LD R5, U 			;IF U
		ADD R5, R5, R4
		BRz LOOP
		LD R5, LOWERU
		ADD R5, R5, R4
		BRz LOOP



		LD R5, ANSWER
		ADD R5, R5, R0
		STR R3, R5, #0
		ADD R0, R0, #1
		BR LOOP

ENDCONDITION
	LD R3, SZ
	LD R5, ANSWER
	ADD R5, R5, R0
	STR R3, R5, #0
	

HALT

STRING .fill x4000
ANSWER .fill x4100



;;NOTE: For your convenience, you can make new labels for
;;the ASCII values of other vowels here! 2 have been done
;;here as an example.

LOWERA .fill x61    ;; a in ASCII

A .fill x41     ;; A in ASCII

LOWERE .fill x65
E .fill x45

LOWERI .fill x69
I .fill x49

LOWERO .fill x6f
O .fill x4f

LOWERU .fill x75
U .fill x55

SLASH .fill x5c
ZERO .fill x30
SZ .fill x00


.end

.orig x4000

.stringz "spongebob and SQUIDWARD"

.end
