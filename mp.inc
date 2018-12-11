MovePlayer MACRO
	LOCAL Drw, L
	push ax
	push bx
	push cx
	push dx
	push si

	mov ah,2
	mov bx,0
	mov dl,posx
	mov dh,posy
	int 10h

	mov ah,8
    	mov bh,0
    	int 10h

    	cmp al,ori
    	jnz Drw      ;Not Equal, rotates in its place

	mov cl,al
	mov si,0ffffh
	L:
	cmp si,4
	jz Drw
	inc si
	cmp cl,conf[si]
	jnz L

	mov ah,2
	mov bl,chngx[si]
	mov bh,0
	mov dl,posx
	add dl,bl
	mov bl,chngy[si]
	mov dh,posy
	add dh,bl
	int 10h

	mov ah,8
    	mov bh,0
    	int 10h

    	cmp al,' '
    	jnz Drw
	cmp dl,80
	jz Drw
	cmp dh,24
	jz Drw
	cmp dl,17
	jz Drw

    	mov ah,2
	mov dl,posx
	mov dh,posy
	int 10h

	mov ori,cl
	mov al,' '
	mov ah,9
	mov cx,1
	mov bx,7
	int 10h
	mov bl,chngx[si]
	mov bh,0
	mov dl,posx
	add dl,bl
	mov bl,chngy[si]
	mov dh,posy
	add dh,bl
	mov posx,dl
	mov posy,dh

    	Drw:
    	DrawPlayer

    	pop si
	pop dx
	pop cx
	pop bx
	pop ax
ENDM MovePlayer

DrawPlayer MACRO
	push si
	push bx
	mov ah,2
	mov dl,posx
	mov dh,posy
	int 10h

	mov al,ori
	mov ah,9
	mov bh,0
	mov cx,1
	mov bl,pnum
	add bl,0DH
	int 10h
	pop bx
	pop si
ENDM DrawPlayer
