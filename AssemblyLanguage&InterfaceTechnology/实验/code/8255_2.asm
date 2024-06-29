DATA SEGMENT
    PORTA EQU 290H   ; 定义端口A的地址为290H，用于段码输入
    PORTB EQU 291H   ; 定义端口B的地址为291H，用于位码选择
    PORTO EQU 293H   ; 定义端口O的地址为293H，用于8255A的控制寄存器
    ARRAY DB 7FH,5BH,6DH,6DH,40H,77H ; 定义要显示的“8255-A”对应的段码
DATA ENDS

STACK SEGMENT
STACK ENDS            

CODE SEGMENT
ASSUME CS:CODE, DS:DATA, SS:STACK  

MAIN:                     
    MOV AX, DATA    
    MOV DS, AX        

    MOV DX, PORTO      ; 将控制口的地址加载到DX寄存器
    MOV AL, 10000000B ; 0方式，端口A 端口B输出
    OUT DX, AL          ; 将控制字输出到控制口

    LEA SI, ARRAY      ; 将数组的地址加载到SI寄存器，准备读取段码
    MOV BL, 00100000B  ; 初始化位选寄存器的位选码，选择第一个数码管

LP:   
    MOV DX, PORTA      ; 准备向端口A输出段码
    MOV AL, [SI]       ; 从数组中读取当前的段码到AL寄存器
    INC SI              ; 增加SI寄存器的值，指向下一个段码
    OUT DX, AL          ; 将段码输出到端口A

    MOV DX, PORTB      ; 准备向端口B输出位选码
    MOV AL, BL         ; 将位选码加载到AL寄存器
    OUT DX, AL          ; 将位选码输出到端口B，选择相应的数码管

    CALL DELAY         ; 调用延时程序

    SHR BL, 1          ; 将位选码右移一位，准备选择下一个数码管
    CMP BL, 0          ; 检查位选码是否为0
    JNZ LP             ; 如果不为0，跳转回LP继续循环

    LEA SI, ARRAY      ; 如果所有数码管都已显示一遍，则重置数组指针
    MOV BL, 00100000B  ; 重置位选码，重新开始显示
    JMP LP              ; 跳转回LP继续循环

EXIT: 
    MOV AH, 4CH      
    INT 21H           

; 延时程序
DELAY PROC
    PUSH BX           
    PUSH CX            
    MOV BX, 0FFFFH     
DL1:  MOV CX, 06FH     
DL2:  DEC CX            
    JNZ DL2            
    DEC BX            
    JNZ DL1           

    POP CX            
    POP BX             
    RET                 
DELAY ENDP

CODE ENDS              

; DATA SEGMENT
;     PORTA EQU 290H
;     PORTB EQU 291H
;     PORTC EQU 292H
;     PORTO EQU 293H
;     ARRAY DB  7FH,5BH,6DH,6DH,40H,77H ;8255-A
; DATA ENDS

; STACK SEGMENT
; STACK ENDS

; CODE SEGMENT                  
; ASSUME CS:CODE, DS:DATA, SS:STACK
;     MAIN:                     
;           MOV  AX, DATA
;           MOV  DS, AX

;           MOV  DX,PORTO        ;送入命令口地址
;           MOV  AL,10000000B    ;传入命令字
;           OUT  DX,AL

;           LEA  SI,ARRAY
;           MOV BL,00100000B
;     LP:   
;           MOV  DX,PORTB
;           MOV  AL,00H
;           OUT  DX,AL
;           MOV  DX,PORTA
;           MOV  AL,[SI]
;           INC  SI
;           OUT  DX,AL
;           MOV  DX,PORTB
;           MOV  AL,BL
;           OUT  DX,AL
;           CALL DELAY

;           SHR BL,1
;           CMP BL,0
;           JNZ LP
;           LEA  SI,ARRAY
;           MOV BX,00100000B
;           JMP LP
 
;        EXIT: 
;             MOV    AH,4CH
;             INT    21H
            
;     ;延时程序
; DELAY PROC
;           PUSH BX
;           PUSH CX
;           MOV  BX,0FFFFH
;     DL1:  MOV  CX,06FH
;     DL2:  DEC  CX
;           JNZ  DL2
;           DEC  BX
;           JNZ  DL1
;           POP  CX
;           POP  BX
;           RET
; DELAY ENDP

; CODE ENDS
