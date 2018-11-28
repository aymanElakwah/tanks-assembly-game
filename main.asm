include MovePlayer.inc
include akwah.inc
data segment

player1 label byte
player1x db ?
player1y db ?
player1Ori db ?
player2 label byte
player2x db ?
player2y db ?
player2Ori db ?

pnum db  ?          ;Player number = pnum (0 or 1)
generalPlayer label byte
posx  db  ?        ;Positon x of general player
posy db  ?        ;Positon y of general player
ori  db  ?          ;Orintation of player: Right = 16, Left = 17, Up = 30, Down = 31

conf  db 16,17,30,31
chngx db 01,-1,00,00
chngy db 00,00,-1,01

message db 300 dup(' '), '$'

ends

stack segment
    dw   128  dup(0)
ends

code segment
start:
; set segment registers:
    mov ax, data
    mov ds, ax
    
    mov dx, offset message
    mov ah, 9
    int 21h
    mov dx, 0
    mov ah, 2
    int 10h
    mov pnum, 1
    mov player1ori, 16
    mov ori, 16
    DrawPlayer
    ; add your code here
    label:
    mainGameLoop
    jmp label        
    
    
    mov ax, 4c00h ; exit to operating system.
    int 21h    
ends

end start ; set entry point and stop the assembler.
