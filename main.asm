include general.inc
include network.inc
include mp.inc
include input.inc
include init.inc
include Macros.inc
include Bullet.inc
include exchange.inc
.model small
.386
.stack 64
.data
tmp db ?
waiting db 'Waiting for player 2$'
player1 label byte
player1x db 21
player1y db 0
player1Ori db 16
user1 db 16, ?
player1Name db 17 dup('$')
player2 label byte
player2x db 76
player2y db 22
player2Ori db 18         
user2 db 16, ?
player2Name db 17 dup('$')

pausedStatus db 'The game is paused$'
emptyStatus db 78 dup (' '), '$'
firstLetter db 'The first letter of the name should be a letter$'

playerNumber db 0 ; The number of player on this device
key1 db ? ;player 1 key
isDir1 db ? ; is key 1 a direction key?
key2 db ? ;player 2 key                
isDir2 db ? ; is key 2 a direction key?
pnum db  ?          ;Player number = pnum (0 or 1)
generalPlayer label byte
posx  db  ?        ;Positon x of general player
posy db  ?        ;Positon y of general player
ori  db  ?          ;Orintation of player: Right = 16, Left = 17, Up = 30, Down = 31

sendx db ?
sendy db ?
recx db ?
recy db ?

conf  db 16,17,30,31
chngx db 01,-1,00,00
chngy db 00,00,-1,01

blt1 db 3 dup(0ffh, ?, ?)
blt2 db 3 dup(0FFh, ?, ?)
Msg1  db 'Please Enter Your Name: $' 
          
Noti11 db 'You Sent A Normal Game Invitaion to $'   
Noti12 db 'You Sent An Advanced Game Invitaion to $'
Noti13 db 'You Sent A Chat Invitaion to $'  
Noti21 db ' Sent You A Normal Game Invitaion, To Accept Press F2$'
Noti22 db ' Sent You An Advanced Game Invitaion, To Accept Press F2$' 
Noti23 db ' Sent You A Chat Invitaion, To Accept Press F2$'
recInv db 5

;Msg2  db 'USER2: Please Enter Your Name: $'
spaces   db '                $'

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
                 db    '                             ',16,' Normal Mode                                      $'
                 db    '                               Advanced Mode                                    $'
                 db    '                               Chatting Mode                                    $'
                 db    '                               Exit                                             $'
                 db    '                                                                                $'
                 db    '                                                                                $' 
                 db    '                                                                                $' 
                 db    '                                                                                $'
                 db    '                                                                                $'

map1            db     '                 넬께                                                           '
                db     '                 넬께                께     께께께께            께께께께 �  께  '
                db     '                 남께          께�         께께께께께   께께께  께께께께 �    께'      
                db     '                 남께   께께  께 �        께께께께께께  께께께  께       �      '
                db     '                 �     �         께      께께께께께께께 께께께    께�    �   께 '
                db     '                 �   께   께� 께 께     께께께께께께께� 께께께    께�    �      ' 
                db     '                 �        께� 께 께     께께께께께께께� 께께께       께� �  께  '
                db     '                 � 께께   께�    �   께 께께께께께께께�              �          '
                db     '                 �   �           �      께�  께께  께께         께께께     께   '
                db     '                 �  �      께께께   께  께   께께   께�            께께    께   '
                db     '컴컴컴컴컴컴컴컴캐께   께께             �    께께    께            께께  께     '
                db     '                 남께께께�  �   께      께께께께께께께� 께께께      께�  께     '
                db     '                 남�  께�       �   �   께께께께께께께�         께께께께 �      '
                db     '                 � �     께께께           께께께께께�           께께께께께  께  '
                db     '                 � 께    께께께�          � 께께께 께        께께          께   '
                db     '                 � 께    께께께께    께   께께께께께�       께     께   께      '
                db     '                 �  �            께    께 께께께께께�      께께        께       '
                db     '                 �   께       �   께      � � � � � �      께   께    께        '
                db     '                 �    께�  �   �    께    � � � � � �     께    께   께         '
                db     '                 �    �  께 �  께    께께  � � � � �    께   께    께           ' 
                db     '                 �   �          �      께              께    께              께�'
                db     '                 � 께   � � 께 �         께께께께께께께                      께�'
                db     '                 �                                                           께�'    
                db     '                 남께께께께께께께께께께께께께께께께께께께께께께께께께께께께� 께�$'
                
                
                
                
map2            db     '                 넬께                                                           '
                db     '                 넬께   *            께     께께께께            께께께께 �  께  '
                db     '                 남께       *  께�         께께*께께�   께께께  께�*께께 �    *�'      
                db     '                 �*께   께께  께 �        께께께께께께  께께께  께       �      '
                db     '                 �     *         께  *   께께께께*께께� 께*께�    께�    �   *� '
                db     '                 �   께   *께 께 *�     께�*께께께께께� 께께께    *께 *  �      ' 
                db     '                 �        께� 께 께     께께께께께**께� 께께께       께� *  께  '
                db     '                 � 께께   *께    �   께 께께*께께께께께              �          '
                db     '                 �   �           �      께�  께*�  께께    *    께�*께     께   '
                db     '                 �  �    * 께께�*   께  께   께께   께�            께께    께   '
                db     '컴컴컴컴컴컴컴컴캐께   께께        *    �    께*�    께            께께  께     '
                db     '                 남께께께�  �   께      께께께께께께께� 께�*께     *께�  �*     '
                db     '                 남�  께�       �   �   께께*께께께께께         께께께께 �      '
                db     '                 � �     께*께�           께께께께께�           께�*께께께  께  '
                db     '                 � 께    께께*께          �*께께께*께    *   께께          께   '
                db     '                 � �*    께께께께    께   께께�*께께�       *�     께   께      '
                db     '                 �  �            께    께 께께께께께*      께께        께  *    '
                db     '                 �   께  *    �   께      � � � � � �      께*  께    께        '
                db     '                 �    께�  �   �    *�    � � � � � �     께    께   께    *    '
                db     '                 �    �  께 �  께  * 께께  � � � � �    께   께    께           ' 
                db     '                 �   �          �      께              께    께        *     께�'
                db     '                 � �*   � � 께 �         께*께께께께께�      *   *           *께'
                db     '                 �           *                                               께�'    
                db     '                 남께께께께께께께께께께께께께께께께께께께께께께께께께께께께� 께�$'                
                
              
                

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
level db ?
won db " won ","$"

.code
main proc far
; set segment registers:
    mov ax, @data
    mov ds, ax
    mov es, ax
    WriteNames
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

