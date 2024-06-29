DATA SEGMENT
      PORT0 EQU 280H
      PORT1 EQU 281H
      PORT2 EQU 282H
      PORTZ EQU 283H      
DATA ENDS
CODE SEGMENT
           ASSUME CS:CODE, DS:DATA
      MAIN:
           MOV    AX, DATA
           MOV    DS, AX


           MOV    DX,PORTZ
           MOV    AL,00110100B
           OUT    DX,AL

           MOV    DX,PORT0
           MOV    AX,03E8H
           OUT    DX,AL
           MOV    AL,AH
           OUT    DX,AL


      EXIT:
           MOV    AH,4CH
           INT    21H
CODE ENDS
    END MAIN