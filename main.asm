data segment

pnum db  ?          ;Player number = pnum (0 or 1)
pos  db  ?,?        ;Positon of player = (x: pos, y: pos+1)
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
