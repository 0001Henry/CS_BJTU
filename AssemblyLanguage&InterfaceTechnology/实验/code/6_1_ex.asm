; 对键盘输入的小写字母用大写字母显示出来
; （要求采用子程序格式，即采用子程序完成将小写字母转化成大写字母）。
ASSUME CS:CODE,DS:DATA,SS:STACK

DATA SEGMENT
DATA ENDS

STACK SEGMENT
STACK ENDS

CODE SEGMENT
MAIN:
    MOV AX,DATA
    MOV DS,AX

    MOV AH,1
    INT 21H

    CALL TRANS 

    MOV DL,AL
    MOV AH,2
    INT 21H

    MOV AH,4CH
    INT 21H

TRANS PROC NEAR
    CMP AL,'a'
    JGE NEXT1
    ADD AL,20H
NEXT1:
    RET
TRANS ENDP


CODE ENDS
    END MAIN 