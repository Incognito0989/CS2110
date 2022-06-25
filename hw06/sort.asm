;;=============================================================
;; CS 2110 - Fall 2021
;; Homework 6 - Selection Sort
;;=============================================================
;; Name: andrew jones
;;=============================================================

;; In this file, you must implement the 'SORT' subroutine.

;; Little reminder from your friendly neighborhood 2110 TA staff: don't run
;; this directly by pressing 'RUN' in complx, since there is nothing put at
;; address x3000. Instead, load it and use 'Debug' -> 'Simulate
;; Subroutine Call' and choose the 'sort' label.

.orig x3000
HALT

;;Pseudocode (see PDF for explanation)
;;  arr: memory address of the first element in the array
;;  n: integer value of the number of elements in the array
;;
;;  sort(array, len, function compare) {
;;      i = 0;
;;      while (i < len - 1) {
;;          j = i;
;;          k = i + 1;
;;          while (k < len) {
;;              // update j if ARRAY[j] > ARRAY[k]
;;              if (compare(ARRAY[j], ARRAY[k]) > 0) {
;;                  j = k;
;;              }
;;              k++;
;;          }
;;          temp = ARRAY[i];
;;          ARRAY[i] = ARRAY[j];
;;          ARRAY[j] = temp;
;;          i++;
;;      }
;;  }

sort

;;YOUR CODE HERE

;CMPGT(5,2) CMPGT(2,1) CMPGT(2,5) CMPGT(1,1)

    ADD R6, R6, -4  ; make space for RA, RV, old FP and one local
    STR R7, R6, 2   ; save return address
    STR R5, R6, 1   ; saves old frame pointer
    ADD R5, R6, 0   ; point frame pointer at the first local variable
    ADD R6, R6, -8  ; allocate space to save all five registers R0-R4 and space for 
                                    ;four local variables
    ; save registers
    STR R0, R6, 0
    STR R1, R6, 1
    STR R2, R6, 2
    STR R3, R6, 3
    STR R4, R6, 4



    AND R1, R1, 0       ;COUNTER  I
    LDR R2, R5, 5       ;LOAD LENGTH INTO R2
    STR R2, R5, 0       ;STORE LENGTH AS LOCAL VARIABLE1
    STR R1, R5, -1      ;STORE I AS LOCAL VARIABLE2
    ADD R2, R2, -1
    NOT R2, R2
    ADD R2, R2, 1       ;NEGATIVE LENGTH
    ADD R3, R2, R1      ;I - LEN + 1 < 0

LOOP1
    LDR R1, R5, -1      ;LOAD I
    LDR R2, R5, 0       ;LOAD LEN
    ADD R2, R2, -1      ;R2 = -R2 + 1
    NOT R2, R2
    ADD R2, R2, 1
    ADD R3, R2, R1      ;I - LEN + 1 < 0
    
    BRzp TEARDOWN
    ADD R3, R1, 0       ;J = I
    ADD R4, R1, 1       ;K = I + 1

    STR R1, R5, -1      ;STORE I AS LOCAL VARIABLE2
    STR R3, R5, -2      ;STORE J AS LOCAL VARIABLE3
    STR R4, R5, -3      ;STORE K AS LOCAL VARIABLE4

LOOP2
    LDR R2, R5, 5       ;LOAD LENGTH IN R2
    NOT R2, R2
    ADD R2, R2, 1       ;NEGATIVE LENGTH IN R2
    LDR R4, R5, -3
    ADD R2, R2, R4      ;WHILE(K < LEN)
        BRzp ENDWHILE
        LDR R0, R5, 6   ;LOAD COMPARE INTO R0
        LDR R2, R5, 4   ;LOAD ARRAY INTO R2
        LDR R1, R5, -2  ;LOAD J
        LDR R3, R5, -3  ;LOAD K
        ADD R4, R2, R3  ;GO TO ADDRESS OF ARR[K]
        LDR R4, R4, 0   ;LOAD ARR[K] DATA INTO R4

        ADD R6, R6, -1  ;MAKE SPACE FOR ARE[K]
        STR R4, R6, 0   ;PUSH ARR[K]

        ADD R4, R2, R1  ;GO TO ADDRESS OF ARR[J]
        LDR R4, R4, 0   ;LOAD ARR[J] DATA INTO R4

        ADD R6, R6, -1  ;MAKE SPACE FOR ARR[J]
        STR R4, R6, 0   ;PUSH ARR[J]

        JSRR R0         ;CALL COMPARE


        LDR R0, R6, 0   ;SAVE RETURN VAL
        ADD R6, R6, 3   ;POP TWO ARGS AND RETURN VAL
        ADD R0, R0, 0   ;SET NZP TO THE COMPARE VALUE
        BRnz ENDIF
            LDR R3, R5, -3      ;LOAD K INTO R3
            STR R3, R5, -2      ;STORE J = K
        ENDIF
        LDR R3, R5, -3      ;LOAD K INTO R3
        ADD R3, R3, 1       ;K++
        STR R3, R5, -3
        BR LOOP2
ENDWHILE
LDR R2, R5, 4           ;LOAD ARRAY INTO R2
LDR R1, R5, -1          ;LOAD I INTO R1
ADD R4, R2, R1          ;GO TO ARR[I] MEM LOCATION
LDR R3, R4, 0           ;"temp"   R3 = ARR[I]
LDR R1, R5, -2          ;LOAD J
ADD R1, R2, R1          ;GO TO ARR[J] ADDRESS
LDR R1, R1, 0           ;R1 = ARR[J]
STR R1, R4, 0           ;ARR[I] = ARR[J]

LDR R1, R5, -2          ;LOAD J
ADD R1, R2, R1          ;GO TO ARR[J] ADDRESS
STR R3, R1, 0           ;ARR[J] = TEMP

LDR R1, R5, -1          ;I++
ADD R1, R1, 1
STR R1, R5, -1
BR LOOP1



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

RET

;; used by the autograder
STACK .fill xF000
.end

;; USE FOR DEBUGGING IN COMPLX
;; load array at x4000 and put the length as 7

;; ARRAY
.orig x4000
    .fill 4
    .fill -9
    .fill 0
    .fill -2
    .fill 9
    .fill 3
    .fill -10
.end

;; The following subroutine is the compare function that is passed  
;; as the function address parameter into the sorting function. It   
;; will work perfectly fine as long as you follow the   
;; convention on the caller's side. 
;; DO NOT edit the code below; it will be used by the autograder.   
.orig x5000 
    ;;greater than  
CMPGT   
    .fill x1DBD
    .fill x7180
    .fill x7381
    .fill x6183
    .fill x6384
    .fill x927F
    .fill x1261
    .fill x1201
    .fill x0C03
    .fill x5020
    .fill x1021
    .fill x0E01
    .fill x5020
    .fill x7182
    .fill x6180
    .fill x6381
    .fill x1DA2
    .fill xC1C0
    .fill x9241
.end