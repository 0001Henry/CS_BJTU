STACK SEGMENT
    DW 100 DUP(?)
STACK ENDS

DATA SEGMENT
    ; LED用于设定点亮的LED灯的位置
    LED DB 00000011B
    ; LED_CURR表示当前哪些灯亮，亮灯对应位为1
    LED_CURR DB 00000000B
    ; 存原中断向量
    IV1_OFF DW ?
    IV1_SEG DW ?
    ; 存中断总次数
    NUM DW 0005H
    CNT DW 0000H
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE,DS:DATA,SS:STACK
START:
    MOV AX,DATA
    MOV DS,AX

    ;初始化8255：0方式，B出,C出
    MOV DX,283H
    MOV AL,10000000B
    OUT DX,AL

    CALL SET_IV

    ;主片开中断
    IN AL,21H
    AND AL,11110111B
    OUT 21H,AL

    ;8255的PC6初始化为0
    MOV DX,283H
    MOV AL,00001100B    
    OUT DX,AL    

    ;清空计数器DI
    XOR DI,DI
    
LP1:
    STI
    
    ;设置8255的PC6输出低->高->低，触发中断
    MOV AL,00001100B    
    OUT DX,AL
    MOV AL,00001101B    
    OUT DX,AL
    NOP
    NOP
    MOV AL,00001100B    
    OUT DX,AL
    CALL DELAY;延时

    CMP DI,NUM
    JNZ LP1

    CALL RECOVER_IV

    ;主片恢复中断屏蔽
    IN AL,21H
    OR AL,00001000B
    OUT 21H,AL

EXIT:
    MOV AH,4CH        ;程序结束
    INT 21H

; 设置中断向量子程序
SET_IV PROC
    CLI ;关中断
    PUSH AX
    PUSH BX
    PUSH CX
    PUSH DS

    MOV AX,0
    MOV DS,AX

    MOV BX,4*0BH
    MOV CX,[BX]
    MOV IV1_OFF,CX
    MOV CX,[BX+2]
    MOV IV1_SEG,CX

    MOV CX,OFFSET INT_PROC_1
    MOV [BX],CX
    MOV CX,SEG INT_PROC_1
    MOV [BX+2],CX

    POP DS
    POP CX
    POP BX
    POP AX
    STI ;开中断
    RET
SET_IV ENDP

; 恢复中断向量子程序
RECOVER_IV PROC
    CLI ;关中断
    PUSH AX
    PUSH BX
    PUSH CX
    PUSH DS

    MOV AX,0

    MOV DS,AX
    MOV BX,4*0BH
    MOV CX,IV1_OFF
    MOV [BX],CX
    MOV CX,IV1_SEG
    MOV [BX+2],CX

    POP DS
    POP CX
    POP BX
    POP AX
    STI ;开中断
    RET
RECOVER_IV ENDP

;中断服务程序1
INT_PROC_1 PROC
    PUSH AX
    PUSH DX
    CLI
    
    INC DI

    MOV AL,LED_CURR   
    XOR AL,LED
    MOV DX,281H
    OUT DX,AL
    MOV LED_CURR,AL

    ;主片中断结束
    MOV AL,63H
    OUT 20H,AL

    POP DX
    POP AX
    STI
    IRET
INT_PROC_1 ENDP


;延时子程序
DELAY PROC
    PUSH CX
    PUSH DX
    MOV CX,0AFFH
DL1:  
    MOV DX,0FFFH
DL2:  
    DEC DX
    JNZ DL2
    LOOP DL1
           
    POP DX
    POP CX
    RET
DELAY ENDP


CODE ENDS
    END START