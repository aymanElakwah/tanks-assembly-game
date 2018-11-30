include MovePlayer.inc
include akwah.inc
include Macros.inc
include blt.inc
include general.inc
.model small
.stack 64

.data 
    
player1 label byte
player1x db 21
player1y db 0
player1Ori db 16
player2 label byte
player2x db 76
player2y db 22
player2Ori db 17


pnum db  ?          ;Player number = pnum (0 or 1)
generalPlayer label byte
posx  db  ?        ;Positon x of general player
posy db  ?        ;Positon y of general player
ori  db  ?          ;Orintation of player: Right = 16, Left = 17, Up = 30, Down = 31

conf  db 16,17,30,31
chngx db 01,-1,00,00
chngy db 00,00,-1,01

blt1 db 3 dup(0ffh, ?, ?)
blt2 db 3 dup(0FFh, ?, ?)  

message db 0 dup(' '), '$'
uppermap db '                 ³Ú²²                                                                            ³Û²²                ²²     ²²²²²²²²            ²²²²²²²² ²  ²²                   ³²²²          ²²²         ²²²²²²²²²²   ²²²²²²  ²²²²²²²² ²    ²²                 ³²²²   ²²²²  ²² ²        ²²²²²²²²²²²²  ²²²²²²  ²²       ²                       ³     ²         ²²      ²²²²²²²²²²²²²² ²²²²²²    ²²²    ²   ²²                  ³   ²²   ²²² ²² ²²     ²²²²²²²²²²²²²²² ²²²²²²    ²²²    ²                       ³        ²²² ²² ²²     ²²²²²²²²²²²²²²² ²²²²²²       ²²² ²  ²²                   ³ ²²²²   ²²²    ²   ²² ²²²²²²²²²²²²²²²              ²                           ³   ²           ²      ²²²  ²²²²  ²²²²         ²²²²²²     ²²                    ³  ²      ²²²²²²   ²²  ²²   ²²²²   ²²²            ²²²²    ²²                    ³²²   ²²²²             ²    ²²²²    ²²            ²²²²  ²²     ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ³²²²²²²²²  ²   ²²      ²²²²²²²²²²²²²²² ²²²²²²      ²²²  ²²     '
lowermap db '                 ³²²  ²²²       ²   ²   ²²²²²²²²²²²²²²²         ²²²²²²²² ²                       ³ ²     ²²²²²²           ²²²²²²²²²²²           ²²²²²²²²²²  ²²                   ³ ²²    ²²²²²²²          ² ²²²²²² ²²        ²²²²          ²²                    ³ ²²    ²²²²²²²²    ²²   ²²²²²²²²²²²       ²²     ²²   ²²                       ³  ²            ²²    ²² ²²²²²²²²²²²      ²²²²        ²²                        ³   ²²       ²   ²²      ² ² ² ² ² ²      ²²   ²²    ²²                         ³    ²²²  ²   ²    ²²    ² ² ² ² ² ²     ²²    ²²   ²²                          ³    ²  ²² ²  ²²    ²²²²  ² ² ² ² ²    ²²   ²²    ²²                            ³   ²          ²      ²²              ²²    ²²              ²²²                 ³ ²²   ² ² ²² ²         ²²²²²²²²²²²²²²                      ²²²                 ³                                                           ²²Ú                 ³²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²² ²²Û$'
temp db 0



.code
main proc far
; set segment registers:
    mov ax, @data
    mov ds, ax
    mov al, 3
    mov ah, 0
    int 10h
    mov ch, 32
    mov ah, 1
    int 10h
    loadmap 
     

    mov dx, offset message
    mov ah, 9
    int 21h
    mov pnum, 1
    mov si, offset player1
    mov bx, offset generalPlayer
    draw
    mov pnum, 2
    mov si, offset player2
    mov bx, offset generalPlayer
    draw
    ; add your code here
    mov bp, 0ffffh
    label:
    
    mainGameLoop
    
    jmp label


    mov ax, 4c00h ; exit to operating system.
    int 21h
main endp

end main ; set entry point and stop the assembler.
