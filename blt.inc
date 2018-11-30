;;;needed variabless
;;blt1 db 3 dup(3 dup(?))
;;blt2 db 3 dup(3 dup(?))
;;post1 db ?,?,?
;;post2 db ?,?,?





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
	local mend,nwpost,move,chk1,chk2,chk3,chk4,cont,cont2,cont3,cont4,dead

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
	je dead
	sub dh,1					;; next move
	jmp nwpost


cont:
	cmp bullet+2,31				;;if one move down
	je chk2
	jne cont2
chk2:
	cmp dh,24             ;; check border
	je dead
	add dh,1					;; next move
	jmp nwpost

cont2:
	cmp bullet+2,17			;;if two move left
	je chk3
	jne cont3
chk3:
	cmp dl,0
	je dead
	sub dl,1					;; next move
	jmp nwpost

cont3:
	cmp bullet+2,16				;;if three move right
	je chk4
	jne mend
chk4:
	cmp dl,79
	je dead
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
dead:	mov bullet,0ffh
	mov bullet+1,0ffH
	jmp mend
	;;hit wall
	;;hit tank
	;;hit flag

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
