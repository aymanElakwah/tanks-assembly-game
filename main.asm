include general.inc
include mp.inc
include akwah.inc
include init.inc
include Macros.inc
include Bullet.inc
.model small
;.386
.stack 64

.data
player1 label byte
player1x db 21
player1y db 0
player1Ori db 16
player1Name db 17 dup('$')
player2 label byte
player2x db 76
player2y db 22
player2Ori db 17
player2Name db 17 dup('$')

pausedStatus db 'The game is paused$'
emptyStatus db 79 dup (' '), '$'


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

Startinterface   db    '      _________       _______        _              _              _______      $'
                 db    '      \__   __/      (  ___  )      ( (    /|      | \    /\      (  ____ \     $'
                 db    '         ) (         | (   ) |      |  \  ( |      |  \  / /      | (    \/     $'
                 db    '         | |         | (___) |      |   \ | |      |  (_/ /       | (_____      $'
                 db    '         | |         |  ___  |      | (\ \) |      |   _ (        (_____  )     $'
                 db    '         | |         | (   ) |      | | \   |      |  ( \ \             ) |     $'
                 db    '         | |         | )   ( |      | )  \  |      |  /  \ \      /\____) |     $'
                 db    '         )_(         |/     \|      |/    )_)      |_/    \/      \_______)     $'
                 db    '                                                                                $'
                 db    '                                                                                $'
                 db    '                                                                                $'
                 db    '                                                                                $'
                 db    '                                                                                $'
                 db    '                                                                                $'
                 db    '                                                                                $'
                 db    '                                                                                $'
                 db    '                             ',16,' Normal  mode                                $'
                 db    '                                         Network mode (Coming Soon)             $'
                 db    '                                                                                $'
                 db    '                                                                                $'
                 db    '                                                                                $'
                 db    '                                                                                $' 
                 db    '                                                                                $'
                 db    '                                                                                $'

map             db     '                 ³Ú²²                                                           '
                db     '                 ³Ú²²                ²²     ²²²²²²²²            ²²²²²²²² ²  ²²  '
                db     '                 ³²²²          ²²²         ²²²²²²²²²²   ²²²²²²  ²²²²²²²² ²    ²²'      
                db     '                 ³²²²   ²²²²  ²² ²        ²²²²²²²²²²²²  ²²²²²²  ²²       ²      '
                db     '                 ³     ²         ²²      ²²²²²²²²²²²²²² ²²²²²²    ²²²    ²   ²² '
                db     '                 ³   ²²   ²²² ²² ²²     ²²²²²²²²²²²²²²² ²²²²²²    ²²²    ²      ' 
                db     '                 ³        ²²² ²² ²²     ²²²²²²²²²²²²²²² ²²²²²²       ²²² ²  ²²  '
                db     '                 ³ ²²²²   ²²²    ²   ²² ²²²²²²²²²²²²²²²              ²          '
                db     '                 ³   ²           ²      ²²²  ²²²²  ²²²²         ²²²²²²     ²²   '
                db     '                 ³  ²      ²²²²²²   ²²  ²²   ²²²²   ²²²            ²²²²    ²²   '
                db     '                 ³²²   ²²²²             ²    ²²²²    ²²            ²²²²  ²²     '
                db     'ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ³²²²²²²²²  ²   ²²      ²²²²²²²²²²²²²²² ²²²²²²      ²²²  ²²     '
                db     '                 ³²²  ²²²       ²   ²   ²²²²²²²²²²²²²²²         ²²²²²²²² ²      '
                db     '                 ³ ²     ²²²²²²           ²²²²²²²²²²²           ²²²²²²²²²²  ²²  '
                db     '                 ³ ²²    ²²²²²²²          ² ²²²²²² ²²        ²²²²          ²²   '
                db     '                 ³ ²²    ²²²²²²²²    ²²   ²²²²²²²²²²²       ²²     ²²   ²²      '
                db     '                 ³  ²            ²²    ²² ²²²²²²²²²²²      ²²²²        ²²       '
                db     '                 ³   ²²       ²   ²²      ² ² ² ² ² ²      ²²   ²²    ²²        '
                db     '                 ³    ²²²  ²   ²    ²²    ² ² ² ² ² ²     ²²    ²²   ²²         '
                db     '                 ³    ²  ²² ²  ²²    ²²²²  ² ² ² ² ²    ²²   ²²    ²²           ' 
                db     '                 ³   ²          ²      ²²              ²²    ²²              ²²²'
                db     '                 ³ ²²   ² ² ²² ²         ²²²²²²²²²²²²²²                      ²²²'
                db     '                 ³                                                           ²²¿'    
                db     '                 ³²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²² ²²¿$'
temp db 0
lives1 db 3 
lives2 db 3
 Sartcheckx dw ?
 Sartchecky dw ?
 Edcheckx dw ?
 Edchecky dw ?
 Cnterx dw ?
 Cntery dw ?
 Rquare dw ?
 color db ?
 won db " won ","$"

.code
main proc far
; set segment registers:
    mov ax, @data
    mov ds, ax
thebegining:
	initialize
    mov al, 3
    mov ah, 0
    int 10h
    mov ch, 32
    mov ah, 1
    int 10h
    loadinterface
    mov pnum, 1
    mov si, offset player1
    mov bx, offset generalPlayer
    draw
    mov pnum, 2
    mov si, offset player2
    mov bx, offset generalPlayer
    draw
    ; add your code here
    mov bp, 10000
    game:
    mainGameLoop
    jmp game


    mov ax, 4c00h ; exit to operating system.
    int 21h
main endp

end main ; set entry point and stop the assembler.
