MovePlayer MACRO	
	push ax		
	push bx	
	push cx		
	push dx			    
	push si
	
	mov ah,2
	mov dl,posx
	mov dh,posy
	int 10h
	
	mov ah,8
    	mov bh,0
    	int 10h
    
    	cmp al,ori
    	jnz NE      ;Not Equal, rotates in its place
	
	mov cl,al
	mov si,0ffffh
	L:
	cmp si,4
	jz Drw
	inc si
	cmp cl,conf+si
	jnz L
	
	mov ah,2
	mov bl,chngx+si
	mov bh,0
	mov dl,posx
	add dl,bl
	mov bl,chngy+si
	mov dh,posy+
	add dh,bl
	int 10h
	
	mov ah,8
    	mov bh,0
    	int 10h
    
    	cmp al,' '
    	jnz Drw
    
    	mov ah,2
	mov dl,posx
	mov dh,posy
	int 10h
	
	mov dl,cl
	
    	mov al,' '
	mov ah,9 
	mov cx,1
	mov bx,0
	int 10h
	
	mov al,dl
	mov bl,chngx+si
	mov bh,0
	mov dl,posx
	add dl,bl
	mov bl,chngy+si
	mov dh,posy
	add dl,bl
	mov posx,dl
	mov posy,dh
    
    	NE:
   	mov ori,al
    
    	Drw:
    	DrawPlayer
	
    	pop si
	pop dx
	pop bx
	pop cx
	pop dx
ENDM MovePlayer

DrawPlayer MACRO
	mov ah,2
	mov dl,posx
	mov dh,posy
	int 10h
	
	mov al,ori
	mov ah,9 
	mov bh,0
	mov cx,1
	mov bl,pnum
	inc bl
	int 10h
ENDM DrawPlayer