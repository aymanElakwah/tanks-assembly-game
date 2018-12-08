nwblt MACRO bullet,position
    local adblt,mend

	mov bx,offset bullet
	cmp bullet,0FFH
    	je adblt
	mov bx,offset bullet+3
	cmp bullet+3,0FFH
	je adblt
	mov bx,offset bullet+6
	cmp bullet+6,0FFH
	jne mend
adblt:                 ;;setting new position and direction
	mov al,position
    	mov [bx],al
	mov al,position+1
	mov [bx+1],al
	mov al,position+2
	mov [bx+2],al
mend:

ENDM nwblt

chkmovblt MACRO bullet
	local second,third,finish
		cmp bullet,0FFH				;;if first bullet exist move it
		je second
		movblt bullet
		drawblt bullet
second:	cmp bullet+3,0FFH			;;if second bullet exist move it
		je third
		movblt bullet+3
		drawblt bullet+3
third:	cmp bullet+6,0FFH			;;if third bullet exist move it
	je finish
		movblt bullet+6
		drawblt bullet+6
finish:
ENDM chkmovblt

movblt MACRO bullet
	local mend,nwpost,move,chk1,chk2,chk3,chk4,cont,cont2,cont3,cont4,dead,borders

	mov dl,bullet				;;get bullet current position in dx
	mov dh,bullet+1
	push dx
	mov ah, 2
	int 10h
	mov ah, 8
	mov bh, 0
	int 10h
	cmp al, 250
	jnz cont4
	mov ah, 2
	mov dl, ' '
	int 21h
cont4:
	pop dx
	cmp bullet+2,30				;;if zero move up
	je chk1
	jne cont
chk1:
	cmp dh,0		;; check border
	je borders
	sub dh,1					;; next move
	jmp nwpost


cont:
	cmp bullet+2,31				;;if one move down
	je chk2
	jne cont2
chk2:
	cmp dh,24             ;; check border
	je borders
	add dh,1					;; next move
	jmp nwpost

cont2:
	cmp bullet+2,17			;;if two move left
	je chk3
	jne cont3
chk3:
	cmp dl,0
	je borders
	sub dl,1					;; next move
	jmp nwpost

cont3:
	cmp bullet+2,16				;;if three move right
	je chk4
	jne mend
chk4:
	cmp dl,79
	je borders
	add dl,1					;; next move
	jmp nwpost

nwpost:
	mov ah,2					;;change the cursor position
	int 10h

	mov ah,8					;;get char in new position
	mov bh,0
	int 10h

	cmp al, ' '                   ;;the position is free
	je move
	cmp al, 250
	je move
dead:	
	Collide
borders:
	mov bullet,0ffh
	mov bullet+1,0ffH
	jmp mend

move:
	mov bullet + 1, dh
	mov bullet, dl

mend:

ENDM movblt

drawblt macro bullet
	push bx
	mov ah,2
	mov bx,0
	mov dl,bullet
	mov dh,bullet+1
	int 10h
	pop bx


	mov ah,2
	mov dl,250
	int 21h
endm drawblt		

Collide Macro
	LOCAL E, Update1, Update2, Destroy, Game1, Gamme2,lines,hhh,linnes2,hh2 
	cmp al,178			;if (Block) destroy
	jz destroy
	cmp ah,0EH			;if (player1) update1 //check by position
	jz update1
	cmp ah,0FH			;if (player2) update2 //check by position
	jz update2
	cmp al,218			;if (flag1) Game1 //the first player lost
	jz Game1
	cmp al,217
	jz Gamme2			;else flage2 Game2 //the second player lost
	jmp E

	update1:
	mov ah,2			;destroy from its current position
	int 10h
	mov dl,' '
	int 21h
	mov cl,lives1			;check for remaining lives & decrement it
	dec cl
	jz Game1			;if dead, lives = 0, first player lost
	mov lives1,cl
	UpadateHearts 1			;redraw hearts
	mov dl,21			;return player to respawn position
	mov dh,0
	mov posx,dl
	mov posy,dh
	mov player1x,dl
	mov player1y,dh
	mov dl,1
	mov pnum,dl
	mov dl,16
	mov ori,dl
	DrawPlayer
	Destroy_Sound
	jmp E				

	Update2:
	mov ah,2			;destroy from its current position
	int 10h
	mov dl,' '
	int 21h	
	mov cl,lives2			;check for remaining lives & decrement it
	dec cl
	jz Gamme2			;if dead, lives = 0, second player lost
	mov lives2,cl
	UpadateHearts 2			;redraw hearts
	mov dl,76			;return player to respawn position
	mov dh,22
	mov posx,dl
	mov posy,dh
	mov player2x,dl
	mov player2y,dh
	mov dl,2
	mov pnum,dl
	mov dl,17
	mov ori,dl
	DrawPlayer
	Destroy_Sound
	jmp E			

	Game1:
    mov ah,0
    mov al,13h
    int 10h 
	Destroy_Sound
       mov si,0
    lines:
    mov ax,0fffh
 hhh: dec ax
      cmp ax,0
      jne hhh  
     mov cx,50
    mov dx,105
    mov al,0ch  
    mov ah,0ch
    add dx,si 
    int 10h  
    add cx,si
    int 10h
    sub dx,si
    int 10h
    sub dx,si
    int 10h
    sub cx,si
    int 10h
    sub cx,si
    int 10h
    add dx,si
    int 10h
    add dx,si
    int 10h  
    inc bp
    add si,2
    cmp bp,1000
    jne lines
	mov ah,2
	mov dx,0A0Ah
	int 10h 
	mov ah, 9
	mov dx, offset user1
	int 21h
	mov ah, 9
	mov dx, offset won
	int 21h
	mov ah,0
	int 16h
	jmp thebegining

	Gamme2:
    mov ah,0
    mov al,13h
    int 10h 
	Destroy_Sound
       mov si,0
    linnes2:
    mov ax,0fffh
 hh2:
	dec ax
      cmp ax,0
      jne hh2  
     mov cx,50
    mov dx,105
    mov al,0ch  
    mov ah,0ch
    add dx,si 
    int 10h  
    add cx,si
    int 10h
    sub dx,si
    int 10h
    sub dx,si
    int 10h
    sub cx,si
    int 10h
    sub cx,si
    int 10h
    add dx,si
    int 10h
    add dx,si
    int 10h  
    inc bp
    add si,2
    cmp bp,1000
    jne linnes2
	mov ah,2
	mov dx,0A0Ah
	int 10h 
	mov ah, 9
	mov dx, offset user2
	int 21h
	mov ah, 9
	mov dx, offset won
	int 21h
	mov ah,0
	int 16h
	jmp thebegining

	destroy:
	mov ah,2
	int 10h

	mov ah,9 ;
	mov bh,0 ;
	mov al,' ' ;
	mov cx,1 ;
	mov bl,07h;
	int 10h 
	Destroy_Sound

	
	E:
	
ENDM Collide






Destroy_Sound Macro
	local delay1,delay2
        mov     al, 182         ; Prepare the speaker for the
        out     43h, al         ;  note.
        mov     ax, 4560        ; Frequency number (in decimal)
                                ;  for middle C.
        out     42h, al         ; Output low byte.
        mov     al, ah          ; Output high byte.
        out     42h, al 
        in      al, 61h         ; Turn on note (get value from
                                ;  port 61h).
        or      al, 00000011b   ; Set bits 1 and 0.
        out     61h, al         ; Send new value.
        mov     bx, 1			; Pause for duration of note.
delay1:
        mov     cx, 65535
delay2:
        dec     cx
        jne     delay2
        dec     bx
        jne     delay1
        in      al, 61h         ; Turn off note (get value from
                                ;  port 61h).
        and     al, 11111100b   ; Reset bits 1 and 0.
        out     61h, al         ; Send new value

  ENDM Destroy_Sound
