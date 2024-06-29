DATA SEGMENT
      PORT0 EQU 280H
      PORT1 EQU 281H
      PORT2 EQU 282H
      PORTZ EQU 283H    ;命令口  
DATA ENDS
CODE SEGMENT
           ASSUME CS:CODE, DS:DATA
      MAIN:
           MOV    AX, DATA
           MOV    DS, AX


           MOV    DX,PORTO
           MOV    AL,00110110B
           OUT    DX,AL

           MOV    DX,PORTZ
           MOV    AX,01F4H
           OUT    DX,AL
           MOV    AL,AH
           OUT    DX,AL


      EXIT:
           MOV    AH,4CH
           INT    21H
CODE ENDS
    END MAIN