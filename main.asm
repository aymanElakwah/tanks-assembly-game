data segment

player1x db ?
player1y db ?
player1Ori db ?
player2x db ?
player2y db ?
player2Ori db ?

pnum db  ?          ;Player number = pnum (0 or 1)
posx  db  ?        ;Positon x of general player
posy db  ?        ;Positon y of general player
ori  db  ?          ;Orintation of player: Right = 16, Left = 17, Up = 30, Down = 31
 
ends

stack segment
    dw   128  dup(0)
ends

code segment
start:
; set segment registers:
    mov ax, data
    mov ds, ax
    mov es, ax
    ; add your code here
            
    
    
    mov ax, 4c00h ; exit to operating system.
    int 21h    
ends

end start ; set entry point and stop the assembler.
