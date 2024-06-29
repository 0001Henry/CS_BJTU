DATA SEGMENT
      PORTA EQU 280H      ; 定义8255A的端口A地址，连接到拨动开关K1-K8
      PORTB EQU 281H      ; 定义8255A的端口B地址，连接到LED灯
      PORTC EQU 282H      ; 定义8255A的端口C地址，用于控制口
      PORTO EQU 283H      ; 定义8255A的控制字寄存器地址
DATA ENDS

CODE SEGMENT
            ASSUME CS:CODE, DS:DATA

      MAIN: 
            MOV    AX, DATA
            MOV    DS, AX

      ; 初始化8255A
            MOV    AL,98H                ;10011000H; 方式0，端口A为输入，端口B为输出
            MOV    DX, PORTC
            OUT    DX, AL

      ; 读取端口A的状态（拨动开关K1-K8的状态）
            MOV    DX, PORTA
            IN     AL, DX

      ; 将读取的状态输出到端口B（LED点亮）
            MOV    DX, PORTB
            OUT    DX, AL

      ; 流水点亮LED的循环程序
      LIGHT:
            MOV    DX, PORTB
            OUT    DX, AL

            CALL   DELAY
            ROL    AL, 1
            JMP    LIGHT

      EXIT: 
            MOV    AH,4CH
            INT    21H

      ; 延时子程序
DELAY PROC
            PUSH   CX
            PUSH   DX
            MOV    CX,0FFH
      DL1:  
            MOV    DX,0FFFFH
      DL2:  
            DEC    DX
            JNZ    DL2
            LOOP   DL1
           
            POP    DX
            POP    CX
            RET
DELAY ENDP

CODE ENDS
    END MAIN 


; DATA SEGMENT
;     PORTA EQU 280H
;     PORTB EQU 281H
;     PORTC EQU 282H
;     PORTO EQU 283H
; DATA ENDS


; CODE SEGMENT
; ASSUME CS:CODE, DS:DATA
;     MAIN: 
;           MOV  AX, DATA
;           MOV  DS, AX

;           MOV  AL,98H ;10011000H
;           MOV  DX,PORTO
;           OUT  DX,AL

;           MOV  AL,00H
;           MOV  DX,PORTB
;           OUT  DX,AL

;           MOV  DX,PORTA
;           IN   AL,DX

;     LIGHT:
;           MOV  DX,PORTB
;           OUT  DX,AL

;           CALL DELAY
;           ROL  AL,1
;           JMP  LIGHT

; DELAY PROC                  ; 延时子程序
;           PUSH CX
;           PUSH DX
;           MOV  CX,0FFH
;     DL1:  
;           MOV  DX,0FFFFH
;     DL2:  
;           DEC  DX
;           JNZ  DL2
;           LOOP DL1
           
;           POP  DX
;           POP  CX
;           RET
; DELAY ENDP

; CODE ENDS
;     END MAIN