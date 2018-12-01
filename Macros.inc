
loadmap MACRO

        ;drawing whole map with 
        ;mov es,ax
        ;mov ah,13h
        ;mov bp,offset uppermap
        ;mov bh,0
        ;mov bl,6
        ;mov cx,1920d
        ;mov dl,0d                                             
        ;mov dh,0d
        ;int 10h

	mov dx,offset map
	mov ah, 9
	int 21h
        
        ;drawing flag of first player and hearts
        mov dx,0012h
        mov ah,2
        int 10h
        mov ah,9
        mov bh,0
        mov al,218d
        mov cx,1
        mov bl,0004
        int 10h
        inc dh
        mov ah,2
        int 10h
        mov ah,9
        mov al,219d
        int 10h
	UpadateHearts 1

        
        ;drawing flag of second player and hearts
	mov ah,2
	mov dx,0c00h
	int 10h
	mov ah,9
	mov bl,0001
	int 10h
	mov cx,1
        mov dx,174fh
        mov ah,2
        int 10h
        mov ah,9
	mov al,219d
        int 10h 
        dec dh
        mov ah,2
        int 10h
        mov ah,9
        mov al,218d
        int 10h
	UpadateHearts 2
ENDM loadmap


;---------------------------------------------------------------------------------------------------------------

;postion in dx ;direction in ch(16D for right,17D for left,30D for top,31D for bot)
build MACRO
local checkright, checkleft, checktop, checkbot, okright, okleft, oktop, okbot,checkfree,construct,Exit

push ax
push bx
push cx
push dx



;moving cursor in tank's position(dx)
mov ah,2
mov bx,0
int 10h

cmp ch,16D					;direction is right
jz checkright

cmp ch,17D					;direction is left
jz checkleft

cmp ch,30D					;direction is top
jz checktop

cmp ch,31D					;direction is bot
jz checkbot


checkright:cmp dl,79d			;if at last right edge the map
		   jnz okright	
		   jz Exit
checkleft: cmp dl,18d			;if at first left edge of the map
		   jnz okleft
		   jz Exit
checktop:  cmp dh,0				;if at first top edge of the map
		   jnz	oktop
		   jz Exit				
checkbot:	cmp dh,23d			;if at last bot edge of the map
			jnz okbot
			jz Exit

okright:inc dl
		jmp checkfree
okleft: dec dl
		jmp checkfree
oktop:  dec dh
		jmp checkfree
okbot:	inc dh

checkfree:
		  mov ah,2				
		  int 10h				;moving cursor infront of the tank
		  mov ah,8				;if there is a space or not
	      mov bh,0
		  int 10h
		  cmp al,' '
		  jz construct
		  jnz Exit 							

;build the block with brown color
construct: mov ah,9
		   mov bh,0
		   mov al,178d				;block symbol
		   mov cx,1
		   mov bl,0006h
		   int 10h

Exit:	pop dx
		pop cx
		pop bx
		pop ax

ENDM build

UpadateHearts MACRO playernum 
	
	local player2,E

	push ax
	push bx
	push cx
	push dx
	mov cx,playernum
	mov bx,0
	cmp cx,1
	jnz player2

	mov dx,0000
	mov cl,lives1
	jmp E
	player2:
	mov dx,0c00h
	mov cl,lives2


	E:
	mov ah,2
	int 10h
	
	push cx
	mov ah,9
	mov bl,0004
	mov al,' '
	mov cl,3
	mov ch,0
	int 10h
	pop cx

	mov ah,9
	mov bl,0004
	mov al,3
	mov ch,0
	int 10h

	pop dx
	pop cx
	pop bx
	pop ax

ENDM UpadateHearts
;---------------------------------------------------------------------------------------------------------------
