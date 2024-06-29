; 比较两个数组的对应位，
; 将大的数放在 ary1 数组中，小的数放在 ary2 中（要求采用子程序格式）。
ASSUME CS:CODE,DS:DATA,SS:STACK
DATA SEGMENT
    ARY1 DB  12,-35,0,126,-90,-5,68,120,1,-19,0,126,-90,-5,68,120
    CNT1 EQU $-ARY1
    ARY2 DB  24,25,0,-38,-89,99,68,100,2,-20,0,126,-90,-5,68,120

DATA ENDS

STACK SEGMENT
STACK ENDS

CODE SEGMENT
    MAIN: 
          MOV  AX,DATA
          MOV  DS,AX
    
          LEA  BX,ARY1

          MOV  CX,CNT1
    LOOP1:
          CALL FUNC
          INC  BX
          LOOP LOOP1
    EXIT: 
          MOV  AH,4CH
          INT  21H

FUNC PROC NEAR
          MOV  AH,[BX]
          MOV  AL,[BX+CNT1]
          CMP  AH,AL
          JG   NEXT1
          XCHG AH,AL
    NEXT1:
          MOV  [BX],AH
          MOV  [BX+CNT1],AL
          RET
FUNC ENDP

CODE ENDS
    END MAIN 