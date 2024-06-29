STACK SEGMENT
    DW 100 DUP(?)
STACK ENDS

DATA SEGMENT
    ; LED1,2用于设定点亮的LED灯的位置
    LED1 DB 00110000B
    LED2 DB 11000000B
    ; LED_CURR表示当前哪些灯亮，亮灯对应位为1
    LED_CURR DB 00000000B
    ; 存原中断向量
    IV1_OFF DW ?
    IV1_SEG DW ?
    IV2_OFF DW ?
    IV2_SEG DW ?
    NUM DW 10
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE,DS:DATA,SS:STACK
START:
    MOV AX,DATA
    MOV DS,AX

    ;初始化8255：0方式，B出
    MOV DX,283H
    MOV AL,10000000B
    OUT DX,AL

    ; 设置中断向量
    CALL SET_IV

    ;主片开中断屏蔽
    IN AL,21H
    AND AL,11110011B
    OUT 21H,AL
    ;从片开中断屏蔽
    IN AL,0A1H
    AND AL,11111011B
    OUT 0A1H,AL

    ;清空计数器CX
    XOR CX,CX
LP1:
    STI
    HLT
    CMP CX,NUM
    JNZ LP1

    ; 恢复中断向量表    
    CALL RECOVER_IV

    ;主片恢复中断屏蔽
    IN AL,21H
    OR AL,00001100B
    OUT 21H,AL
    ;从片恢复中断屏蔽
    IN AL,0A1H
    OR AL,00000100B
    OUT 0A1H,AL

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

    ; 存原中断向量
    MOV BX,4*0BH
    MOV CX,[BX]
    MOV IV1_OFF,CX
    MOV CX,[BX+2]
    MOV IV1_SEG,CX

    MOV CX,OFFSET INT_PROC_1
    MOV [BX],CX
    MOV CX,SEG INT_PROC_1
    MOV [BX+2],CX

    ; 写入新中断向量
    MOV BX,4*72H
    MOV CX,[BX]
    MOV IV2_OFF,CX
    MOV CX,[BX+2]
    MOV IV2_SEG,CX

    MOV CX,OFFSET INT_PROC_2
    MOV [BX],CX
    MOV CX,SEG INT_PROC_2
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

    MOV BX,4*72H
    MOV CX,IV2_OFF
    MOV [BX],CX
    MOV CX,IV2_SEG
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
    CLI ;关中断
    INC CX
    MOV AL,LED_CURR   
    XOR AL,LED1
    MOV DX,281H
    OUT DX,AL

    MOV LED_CURR,AL

    ;主片中断结束
    MOV AL,20H
    OUT 20H,AL

    POP DX
    POP AX
    STI ;开中断
    IRET
INT_PROC_1 ENDP

;中断服务程序2
INT_PROC_2 PROC
    PUSH AX
    PUSH DX
    CLI ;关中断
    INC CX
    MOV AL,LED_CURR
    XOR AL,LED2    
    MOV DX,281H
    OUT DX,AL
    MOV LED_CURR,AL

    MOV AL,20H ; 主片发EOI命令
    OUT 20H,AL
    MOV AL,62H ; 从片发EOI命令
    OUT 0A0H,AL

    POP DX
    POP AX
    STI ;开中断
    IRET
INT_PROC_2 ENDP

CODE ENDS
    END START