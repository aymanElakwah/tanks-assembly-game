initialize macro
mov blt1,0ffh
    mov blt1+3,0ffh
    mov blt1+6,0ffh
    mov blt2,0ffh
    mov blt2+3,0ffh
    mov blt2+6,0ffh
    mov lives1,3 
    mov lives2,3
    mov player1x,21
    mov player1y,0  
    mov player1ori,16
    mov player2x,76
    mov player2y,22  
    mov player2ori,17
	cmp playerNumber,1
	jz ply1
	mov	sendx,0
	mov	sendy,13
	mov	recx,0
	mov	recy,2

		jmp E
ply1:	mov	sendx,0
		mov	sendy,2
		mov	recx,0
		mov	recy,13
E:
	endm initialize