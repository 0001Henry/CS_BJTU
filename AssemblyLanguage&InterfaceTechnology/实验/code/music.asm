; reference: https://www.bilibili.com/video/BV1Wu411B72F?p=79&vd_source=d312c66700fc64b66258a994f0a117ad

ASSUME CS:CODESEG, DS:DATASEG, SS:STACKSEG
DATASEG SEGMENT
        ; MUS_FREQ DW 220,220,220,262,220,220
        ;         DW 262,294,330,294,262,294
        ;         DW 220,220,220,262,220,220
        ;         DW 262,294,330,294,262,294,-1
        ; MUS_TIME DW 12,12,12,12,24,12
        ;         DW 12,12,6,6,12,48
        ;         DW 12,12,12,12,24,12
        ;         DW 12,12,6,6,12,48
        ; MUS_FREQ DW 165,220,220,247,262,220
        ;          DW 349,330,262
        ;          DW 294,294,330,294,262
        ;          DW 247,220,165
        ;          DW 220,220,247,262,220
        ;          DW 440,392,330
        ;          DW 349,349,330,349,392
        ;          DW 330,330
        ;          DW 440,524
        ;          DW 494,440,392,440
        ;          DW 494,440,392,440
        ;          DW 330,262
        ;          DW 440,392,349
        ;          DW 330,294,349
        ;          DW 330,294,330,349,330
        ;          DW 440,-1

        ; MUS_TIME DW 24,24,12,12,24,24
        ;          DW 24,48,24
        ;          DW 24,24,24,12,12
        ;          DW 24,48,24
        ;          DW 24,12,12,24,24
        ;          DW 24,48,24
        ;          DW 24,12,12,24,24
        ;          DW 72,24
        ;          DW 48,48
        ;          DW 24,48,12,12
        ;          DW 36,12,24,24
        ;          DW 72,24
        ;          DW 48,36,12
        ;          DW 24,48,24
        ;          DW 24,12,12,24,24
        ;          DW 72
        MUS_FREQ DW 262,262,262,196,330,330,330,262
                 DW 262,330,392,392,349,330,294
                 DW 294,330,349,349,330,294,330,262
                 DW 262,330,294,196,247,294,262,-1
        MUS_TIME DW 3 DUP(12,12,25,25),12,12,50
                 DW 3 DUP(12,12,25,25),12,12,50
DATASEG ENDS
STACKSEG SEGMENT
                 DB 100H DUP (0)
STACKSEG ENDS
CODESEG SEGMENT
        START:   
                 MOV  AX, STACKSEG
                 MOV  SS, AX
                 MOV  SP, 100H
                 MOV  AX, DATASEG
                 MOV  DS, AX
                 LEA  SI, MUS_FREQ
                 LEA  DI, MUS_TIME
        PLAY:    
                 MOV  DX, [SI]
                 CMP  DX, -1
                 JE   END_PLAY
                 CALL SOUND
                 ADD  SI, 2
                 ADD  DI, 2
                 JMP  PLAY
        END_PLAY:
                 MOV  AX, 4C00H
                 INT  21H

        SOUND:   
                 PUSH AX
                 PUSH DX
                 PUSH CX
                 
                 MOV  AL,0B6H
                 OUT  43H,AL    ;8253
                 MOV  DX,12H
                 MOV  AX,34DCH
                 DIV  WORD PTR [SI]
                 OUT  42H, AL
                 MOV  AL, AH
                 OUT  42H, AL
                 IN   AL,61H    ;8255
                 MOV  AH,AL
                 OR   AL,3
                 OUT  61H,AL
                 MOV  DX, [DI]
        WAIT1:   
                 MOV  CX, 28000
        DELAY:   
                 NOP
                 LOOP DELAY
                 DEC  DX
                 JNZ  WAIT1
                 MOV  AL, AH
                 OUT  61H, AL

                 POP  CX
                 POP  DX
                 POP  AX
                 RET

CODESEG ENDS
END START