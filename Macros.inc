loadmap MACRO
	local level0,level1,next
	mov ah,2
	mov dx,0
	mov bh,0
	int 10h
	cmp level,0
	jz level0
	jnz level1
level0:	mov dx,offset map1
		jmp next
level1: mov dx,offset map2
next:	mov ah, 9
		int 21h
																				;rand
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
        mov al,218d
        int 10h
		UpadateHearts 1 
        

        ;drawing flag of second player and hearts
	mov bl,0001
	mov cx,1
        mov dx,174fh
        mov ah,2
        int 10h
        mov ah,9
	mov al,'Ù'
        int 10h 
        dec dh
        mov ah,2
        int 10h
        mov ah,9
        mov al,'Ù'
        int 10h
		UpadateHearts 2
        users
																				;loadmirror
ENDM loadmap



rand macro
local again,delay
            mov si,2
again:
			mov ah,2ch
			int 21h
			mov random[si],dl
			inc si
			mov ax,0ffffh
delay:		dec ax
			cmp ax,0
			jnz delay
			cmp si,22
			jne again
ENDM rand

loadmirror MACRO
		  local again
		  
		  
          mov si,2
          mov di,3
again:    dec di
          mov ah,0
          mov al,random[si];
          mov dl,62d
          div dl
          mov dl,ah
          add dl,18d
          mov ax,si
          mov dh,al
          mov ah,2
          int 10h
          mov dl,0Fh
          int 21h
          cmp di,0
          jnz again
          mov di,2
          inc si 
          cmp si,22d
          jnz again
		  mov si,0
		  mov di,0
ENDM loadmirror

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
	mov dx,0b00h
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

loadinterface Macro							;if pos(dh)=11h->normalmode , if pos(dl)==12H->network mode ; 13h==chatting mode ;  14==Exit
local normalmode,again,check1,check2,continue,makedelay1,makedelay2,wholelogo,draw,Exit,advancemode,here,chatting
push ax
push dx
push cx
push bx


mov ah,0
mov al,3
int 10h
			

mov ah,2												; making animation (changing cursor postion)
mov dx,1900h
int 10h

				mov cx,24d
				mov bx,0
wholelogo:		mov ah,9
				mov dx,offset Startinterface
				add dx,bx
				int 21h
				push cx
				mov cx,0ffffh
makedelay1:	    
				loop makedelay1							
				mov cx,0ffffh
makedelay2:		
				loop makedelay2
				pop cx
				add bx,81d
				loop wholelogo
				


				mov ah,2								; start cursor postion
				mov bh,0
				mov dx,0f1dh
				int 10h


					mov ch, 32
					mov ah, 1
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

check1:				dec dh
					cmp dh,0fh																
					jae Clearpostion1	    ;Clear cusor before drawing 
					jb  fix1													 

check2:				inc dh
					cmp dh,12h
					jbe Clearpostion2       ;Clear cusor before drawing							
					ja 	fix2											

fix1:inc dh
     jmp again                      ; if clicks  up  and at the edge 

                                    ; if clicks down and at the edge
fix2:dec dh
     jmp again
													

Clearpostion1:inc dh
              push dx
              mov ah,2
              int 10h
              mov dl,' '
              int 21h
              pop dx
              dec dh
              int 10h
              jmp Draw
              

Clearpostion2:dec dh
              push dx
              mov ah,2
              int 10h 
              mov dl,' '
              int 21h
              pop dx
              inc dh
              int 10h
              jmp Draw

Draw: push dx
	  mov dl,16
	  int 21h
	  pop dx
	  jmp continue


continue:	cmp ah,1ch
			jz checkgamemode
			jnz again


checkgamemode:  cmp dh,0fh
      			jz normalmode
				cmp dh,10h
				jz advancemode
				cmp dh,11h
				jz chatting
				
				cmp dh,12h					
				jz Exit
				jnz again
				

Exit:           exitGame					

normalmode:
mov al,0
mov level,al
loadmap
jmp here

advancemode:
mov al,1
mov level,al
loadmap
jmp here

chatting:
mov ah,2
loadchatting
jmp here

here:
pop bx
pop cx
pop dx
pop ax

Endm loadinterface





loadchatting macro
	LOCAL ply1, L, E, AGAIN, cont, ext
	mov ah,0
	mov al,3
	int 10h
	mov ah,2
	mov dx,0
	int 10h
	mov dx,offset player1Name
	mov ah, 9
	int 21h

	mov ah,2
	mov dh,13
	mov dl,0
	int 10h
	mov dx,offset player2Name
	mov ah, 9
	int 21h


	mov dh,11
	mov dl,0
	mov ah,2
	int 10h
	mov ah,9 ;Display
	mov bh,0 ;Page 0
	mov al,45 ;Letter D
	mov cx,79 ;5 times
	mov bl,00Fh ;Green (A) on white(F) background
	int 10h
	
	cmp playerNumber,1
	jz ply1
	mov	sendx,0
	mov	sendy,13
	mov	recx,0
	mov	recy,1

	jmp L
	ply1:	mov	sendx,0
		mov	sendy,1
		mov	recx,0
		mov	recy,13
	L:
    	mov dx , 3FDH		; Line Status Register
    	AGAIN:  	In al , dx 			;Read Line Status
  	AND al , 00100000b
  	JZ AGAIN
    	mov ah, 1
    	int 16h
    	jz E
    	mov ah, 0
    	int 16h
    	cmp ah, 3Bh
    	jz cont
    	;-------------CHAT--------------
    	push ax         ;Displaying at send
  	mov dl,sendx
    	mov dh,sendy
    	mov ah,2
    	int 10h
  	Disp 1,10,13,79
  	mov ah,3h
    	mov bh,0h
    	int 10h
  	mov sendx,dl
  	mov sendy,dh
  	pop ax
    	mov dx , 3F8H		; Transmit data register
  	out dx , al
    	E:
    	mov dx , 3FDH		; Line Status Register
    	in al , dx 
    	AND al , 1
    	JZ L
    	mov dx , 03F8H
  	in al , dx
    	cmp al,254
    	jz ext
    	mov dl,recx    ;Displaying at receive
    	mov dh,recy
    	mov ah,2
    	int 10h
  	Disp 1,10,13,79
  	mov ah,3h
    	mov bh,0h
    	int 10h
  	mov recx,dl
  	mov recy,dh
    	jmp L
    	;-----------END CHAT------------------
    	cont:
    	mov al,254
    	mov dx , 3F8H		; Transmit data register
  	out dx , al
    	ext:jmp thebegining
ENDM loadchatting
      


WriteNames macro
		local b1,b2,chk1,chk2,E,fx1,fx2,cont

				mov ah,0
				mov al,3
				int 10h

				mov ah,2
				mov bl,0
				mov dx,0a1Eh
				int 10h

				mov ah,9
				mov dx ,offset msg1
				int 21h
				
        
b1:				mov ah,2
				mov bl,0					
				mov dx,0b1Eh
				int 10h
				
				
                readInput user1
                
              
                cmp player1Name,65d
				jb  fx1
                cmp player1Name,122d
                ja fx1
                cmp player1Name,90d
                ja  chk1
                
                jmp cont
                
chk1:         cmp player1Name,97d
                jb  fx1
                jmp cont
                
fx1:            notify firstLetter
                mov ah,2
				mov bl,0
				mov dx,0b1Eh
				int 10h
                mov ah,9
				mov dx ,offset spaces
				int 21h
                jmp b1
                                 
    
cont:	        notify emptyStatus
                mov ah,2
				mov bl,0					
				mov dx,0c1Eh
				int 10h

;				mov ah,9
;				mov dx , offset msg2
;				int 21h
;
;b2:				mov ah,2
;				mov bl,0					
;				mov dx,0d1Eh
;				int 10h
;
;				readInput user2
;                cmp player2Name,65d
;				jb  fx2
;                cmp player2Name,122d
;                ja fx2
;                cmp player2Name,90d	
;                ja  chk2
;                jmp E
;                
;chk2:         cmp player2Name,97d
;                jb  fx2
;                jmp E
; 
;                
;fx2:            notify firstLetter
;                mov ah,2
;				mov bl,0
;				mov dx,0d1Eh
;				int 10h
;                mov ah,9
;				mov dx ,offset spaces
;				int 21h
;                jmp b2




				 

                                                      
 

Endm WriteNames