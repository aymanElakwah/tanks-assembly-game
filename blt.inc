;;;needed variabless
;;blt1 db 3 dup(3 dup(?))
;;blt2 db 3 dup(3 dup(?))  
;;post1 db ?,?,?
;;post2 db ?,?,?





nwblt MACRO bullet,position
    local adblt,mend
	 
	mov bx,offset bullet
	cmp bullet,0FFH
    jne adblt
	mov bx,offset bullet+3
	cmp bullet,0FFH
	jne adblt
	mov bx,offset bullet+6
	cmp bullet,0FFH
	je mend
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
	
	cmp bullet,0FFH				;;if first bullet exist move it
	jne movblt bullet 
	cmp bullet+3,0FFH			;;if second bullet exist move it
	jne movblt bullet+3			
	cmp bullet+6,0FFH			;;if third bullet exist move it
	jne movblt bullet+6			

ENDM chkmovblt

movblt MACRO bullet 
	local mend,nwpost,move,chk1,chk2,chk3,chk4,cont
	
	mov dl,bullet				;;get bullet current position in dx
	mov dh,bullet+1
	cmp bullet+2,0				;;if zero move up
	je chk1
	jne cont
chk1:
	cmp dh,0
	je mend
	sub dh,1					;; next move
	jmp nwpost

cont:	
	cmp bullet+2,1				;;if one move down
	je chk2
	jne cont2
chk2:
	cmp dh,24
	je mend
	add dh,1					;; next move
	jmp nwpost

cont2:	
	cmp bullet+2,2				;;if two move left
	je chk3
	jne cont3
chk3:
	cmp dl,0
	je mend
	sub dl,1					;; next move
	jmp nwpost

cont3:	
	cmp bullet+2,3				;;if three move right
	je chk4
	jne mend
chk4:
	cmp dl,79
	je mend
	add dl,1					;; next move
	jmp nwpost

nwpost:							
	mov ah,2					;;change the cursor position
	int 10h

	mov ah,8					;;get char in new position
	mov bh,0
	int 10

	cmp al,0                    ;;the position is free
	je move
	;;hit wall
	;;hit tank
	;;hit flag 

move:
	mov bullet,dx

mend:
ENDM movblt 
	