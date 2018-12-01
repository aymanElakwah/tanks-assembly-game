loadinterface Macro          ;if pos(dh)=11h->normalmode , if pos(dl)==12H->network mode

local back,normalmode
push ax
push dx
push cx
mov ah,9
mov dx,startinterface
int 21h

;movecursor (up and Down)
;takeinputs( up and down and enter)
;compare (dh==12 and enter )


back:	cmp dx,1100h				;normal mode
	jz normalmode
	jnz back 

normalmode :loadmap

pop cx
pop dx
pop ax

Endm loadinterface