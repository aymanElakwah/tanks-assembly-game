include MovePlayer.inc
include akwah.inc
include circle.inc
include Macros.inc
include Bullet.inc
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

map             db     '                 �ڲ�                                                           '
                db     '                 �ڲ�                ��     ��������            �������� �  ��  '
                db     '                 ����          ���         ����������   ������  �������� �    ��'      
                db     '                 ����   ����  �� �        ������������  ������  ��       �      '
                db     '                 �     �         ��      �������������� ������    ���    �   �� '
                db     '                 �   ��   ��� �� ��     ��������������� ������    ���    �      ' 
                db     '                 �        ��� �� ��     ��������������� ������       ��� �  ��  '
                db     '                 � ����   ���    �   �� ���������������              �          '
                db     '                 �   �           �      ���  ����  ����         ������     ��   '
                db     '                 �  �      ������   ��  ��   ����   ���            ����    ��   '
                db     '                 ���   ����             �    ����    ��            ����  ��     '
                db     '����������������ĳ��������  �   ��      ��������������� ������      ���  ��     '
                db     '                 ���  ���       �   �   ���������������         �������� �      '
                db     '                 � �     ������           �����������           ����������  ��  '
                db     '                 � ��    �������          � ������ ��        ����          ��   '
                db     '                 � ��    ��������    ��   �����������       ��     ��   ��      '
                db     '                 �  �            ��    �� �����������      ����        ��       '
                db     '                 �   ��       �   ��      � � � � � �      ��   ��    ��        '
                db     '                 �    ���  �   �    ��    � � � � � �     ��    ��   ��         '
                db     '                 �    �  �� �  ��    ����  � � � � �    ��   ��    ��           ' 
                db     '                 �   �          �      ��              ��    ��              ���'
                db     '                 � ��   � � �� �         ��������������                      ���'
                db     '                 �                                                           ���'    
                db     '                 ����������������������������������������������������������� ���$'
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