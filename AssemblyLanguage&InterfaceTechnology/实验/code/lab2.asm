ASSUME CS:CODE, DS:DATA, SS:STACK

DATA SEGMENT
    MAXLEN     DB 200            ; 定义最大长度为200的字符数组
    ACTLEN     DB ?              ; 存储实际输入的长度
    STRING     DB 200 DUP(?)     ; 分配200字节的空间用于存储输入的字符串

    CNT_LETTER DW 0    ; 计数器，用于统计字母的数量
    CNT_NUM    DW 0    ; 计数器，用于统计数字的数量
    CNT_OTHERS DW 0    ; 计数器，用于统计其他字符的数量

    CHANGEROW  DB 0DH,0AH,'$'  ; 定义换行字符串
    STRING_LETTER DB  "count of letter:",'$'
    STRING_NUMBER DB  "count of number:",'$'   
    STRING_OTHERS DB  "count of others:",'$'
DATA ENDS

STACK SEGMENT
    DW 200 DUP(?)  ; 分配200字的空间用于堆栈
STACK ENDS

CODE SEGMENT
    MAIN:
        MOV  AX, DATA
        MOV  DS, AX
        MOV  AX, STACK
        MOV  SS, AX

        ; 初始化
        MOV WORD PTR CNT_LETTER, 0
        MOV WORD PTR CNT_NUM, 0
        MOV WORD PTR CNT_OTHERS, 0

        ; 输入字符串
        MOV  DX, OFFSET MAXLEN
        MOV  AH, 10
        INT  21H

        MOV  BX, OFFSET STRING
        MOV  CH, 0
        MOV  CL, ACTLEN
        CMP CL, 0
        JE SHOW

    LP1:
        MOV  AL, [BX]
        CALL CHECK
        INC  BX
        LOOP LP1

    SHOW:
        LEA  DX, CHANGEROW  ; 将CHANGEROW字符串的地址加载到DX寄存器
        MOV  AH, 09H         ; 设置AH寄存器为09H，这是DOS中断的功能号，用于输出字符串
        INT  21H             ; 调用DOS中断，输出DX指向的字符串

        LEA DX, STRING_LETTER
        MOV  AH, 09H
        INT  21H

        MOV  AX, CNT_LETTER
        CALL DISPLAY

        LEA DX, STRING_NUMBER
        MOV  AH, 09H
        INT  21H

        MOV  AX, CNT_NUM
        CALL DISPLAY

        LEA DX, STRING_OTHERS
        MOV  AH, 09H
        INT  21H

        MOV  AX, CNT_OTHERS
        CALL DISPLAY

    EXIT:
        MOV  AH, 4CH
        INT  21H

CHECK PROC NEAR
    ; 检查字符类型并更新计数器
    CMP  AL, '0'
    JL   OTHRES
    CMP  AL, '9'
    JLE  NUMBER

    CMP  AL, 'A'
    JL   OTHRES
    CMP  AL, 'Z'
    JLE  LETTER

    CMP  AL, 'a'
    JL   OTHRES
    CMP  AL, 'z'
    JLE  LETTER

    NUMBER:
        INC  CNT_NUM
        RET
    LETTER:
        INC  CNT_LETTER
        RET
    OTHRES:
        INC  CNT_OTHERS
        RET
CHECK ENDP


DISPLAY PROC NEAR
    PUSH AX          ; 保存AX寄存器，因为接下来的操作会改变它的值
    PUSH BX          
    PUSH CX          
    PUSH DX          

    XOR  CX, CX      ; 将CX寄存器清零，用于计数
    MOV  BX, 10      ; 将10（基数）加载到BX寄存器，用于后续的除法操作

    LP2:             
        XOR  DX, DX    ; 将DX寄存器清零，用于存储除法的余数
        DIV  BX         ; 将AX除以BX（10），商在AX中，余数在DX中
        PUSH DX         ; 将余数压入栈中
        INC  CX          ; 增加计数器，记录有几个余数被压入栈
        CMP  AX, 0       ; 检查商是否为0，如果是，则循环结束
        JNE  LP2         ; 如果商不为0，继续循环

    LP3:             
        POP  DX          ; 弹出栈顶的余数
        ADD  DL, '0'     ; 将余数转换为其对应的ASCII码，以便显示
        MOV  AH, 2       ; 设置AH寄存器为2，准备输出字符
        INT  21H         ; 调用DOS中断，输出DX中的字符
        LOOP LP3         ; 减少CX的值，并检查是否所有字符都已输出

    LEA  DX, CHANGEROW  ; 准备换行字符串的地址
    MOV  AH, 09H       ; 设置AH寄存器为09H，准备输出字符串
    INT  21H           ; 调用DOS中断，输出换行字符串

    POP  DX           
    POP  CX           
    POP  BX            
    POP  AX            
    RET                
DISPLAY ENDP

CODE ENDS
    END MAIN