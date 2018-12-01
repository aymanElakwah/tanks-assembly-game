loadinterface Macro							;if pos(dh)=11h->normalmode , if pos(dl)==12H->network mode

local back,normalmode,again,check1,continue
push ax
push dx
push cx

mov ah,2								; making animation
mov dx,1900h
int 10h

mov ah,9
mov dx,offset Startinterface
int 21h


mov ah,2								; start cursor postion
mov dx,111dh
int 10h


again:				mov ah,1
					int 16h
					jz	again				;if no input
					mov ah,0
					int 16h
					cmp ah,48h
					jz check1				;check if he can go up or no
					cmp ah,50h
					jz check2				;check if he can go down or no
					jnz continue

check1:				cmp dh,12h						;he is down
					jz ok1							;he can go up
					jmp continue 

check2:				cmp dh,11h						;he is up
					jz ok2							;he can go down
					jmp continue

ok1: mov dx,121dh
	 mov ah,2
	 int 10h
	 mov dl,' '
	 int 21h	
	 mov dx,111dh
	 int 10h
	 mov dl,16
	 int 21h
	 jmp continue

	     
ok2:mov dx,111Dh
	 mov ah,2
	 int 10h
	 mov dl,' '
	 int 21h	
	 mov dx,121dh
	 int 10h
	 mov dl,16
	 int 21h
	 jmp continue


continue:	cmp ah,1ch
			jz checkgamemode
			jnz again


checkgamemode:  cmp dh,11h
      			jz normalmode
				jnz again					; no networkmode yet

normalmode:       ;loadmap

pop cx
pop dx
pop ax

Endm loadinterface
