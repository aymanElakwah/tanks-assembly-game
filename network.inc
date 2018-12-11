initPort macro
    mov dx,3fbh 			; Line Control Register
    mov al,10000000b		;Set Divisor Latch Access Bit
    out dx,al				;Out it
    mov dx,3f8h
    mov al,0ch
    out dx,al
    mov dx,3f9h
    mov al,00h
    out dx,al
    mov dx,3fbh
    mov al,00011011b
    out dx,al
endm

send macro VALUE
    local AGAIN
    mov dx , 3FDH		; Line Status Register
    AGAIN:  	In al , dx 			;Read Line Status
      	AND al , 00100000b
      	JZ AGAIN
    mov dx , 3F8H		; Transmit data register
  	mov  al,VALUE
  	out dx , al
endm

receive macro VALUE
    local mend
    mov dx , 3FDH		; Line Status Register
    in al , dx
    AND al , 1
    mov ah, 1
    mov VALUE, 0
  	JZ mend
    ;If Ready read the VALUE in Receive data register
  	mov dx , 03F8H
  	in al , dx
  	mov VALUE , al
  	mend:
endm receive
