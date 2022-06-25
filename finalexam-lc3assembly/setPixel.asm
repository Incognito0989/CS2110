;;=============================================================
;; CS 2110 - Fall 2021
;; Final Exam - Set Pixel
;;=============================================================
;; Name: ANDREW JONES
;;=============================================================

;; Pseudocode (see PDF for additional information)
;; 
;; offset = 0;
;; for (i = 0; i < ROW; i++) {
;;		offset += WIDTH;
;; }
;; offset += COL;
;; VIDEOBUFFER[offset] = COLOR

.orig x3000

;; YOUR CODE HERE

AND R0, R0, 0		;SET R0 TO 0 THIS WILL BE OFFSET
AND R1, R1, 0		;SET COUNTER 0


LOOP
LD R2, ROW			;R2 = ROW
LD R3, COL 			;R3 = COL
LD R4, WIDTH		;R4 = WIDTH
NOT R5, R2			;R5 = NOT ROW
ADD R5, R5, 1		;R5 = -ROW
ADD R5, R5, R1		;COUNTER - ROW
	BRzp ENDLOOP
	ADD R0, R0, R4		;OFSSET + WIDTH


	ADD R1, R1, 1		;COUNTER++
	BR LOOP

ENDLOOP
LD R3, COL
ADD R0, R0, R3			;COL + OFFSWT
LD R3, VIDEOBUFFER		;LOAD VIDEO BUFFER
ADD R3, R3, R0
LD R5, COLOR			;LOAD COLOR
STR R5, R3, 0			;STORE COLOR INTO VIDEOBUFFER[OFFSET]

HALT

COLOR .fill xFFFF
ROW .fill 1
COL .fill 1

HEIGHT .fill 2
WIDTH .fill 2

VIDEOBUFFER .fill x4000

.end

.orig x4000
    .fill 2
    .fill 1
    .fill 1
    .fill 0
.end