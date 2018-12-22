mem2mem macro index ;bx = si ; put the byte located at si in bx (memory)
    mov dl, [si + index]
    mov [bx + index], dl
endm mem2mem

translateKeyPress macro ;input:scan code in ah/output:symbol in ah, al: playerNumber
local right, down, left, w, a, s, d, notDirectionKey, finish
    ;48 up, 4D right, 50 down, 4B left
    mov al, 1; player 1
    cmp ah, 48h ; is it up?
    jnz right
    mov ah, 1Eh
    jmp finish
    right:
    cmp ah, 4Dh ; is it right?
    jnz down
    mov ah, 10h
    jmp finish
    down:
    cmp ah, 50h ; is it down?
    jnz left
    mov ah, 1Fh
    jmp finish
    left:
    cmp ah, 4Bh ; is it left?
    jnz notDirectionKey
    mov ah, 11h
    jmp finish
    notDirectionKey:
    mov al, 0
    finish:
endm translateKeyPress

move macro ; moves general player
    ; copy certain player data in general player data
    mem2mem 0
    mem2mem 1
    mem2mem 2
    ; move the general player
    movePlayer
    ; copy general player data in the specific player again
    xchg bx, si
    mem2mem 0
    mem2mem 1
    mem2mem 2
    endm move

draw macro ; this macro is responsible for the players at initinal positions
    mem2mem 0
    mem2mem 1
    mem2mem 2
    drawPlayer
    xchg bx, si
    mem2mem 0
    mem2mem 1
    mem2mem 2
    endm draw

pauseGame macro
    local pause_game, cont, AGAIN, E, ext
    pauseSound
    notify pausedStatus
    pause_game:
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
  	Disp 2,9,13,16
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
    JZ pause_game
    mov dx , 03F8H
  	in al , dx
    cmp al,254
    jz ext
    mov dl,recx    ;Displaying at receive
    mov dh,recy
    mov ah,2
    int 10h
  	Disp 2,9,13,16
  	mov ah,3h
    mov bh,0h
    int 10h
  	mov recx,dl
  	mov recy,dh
    jmp pause_game
    ;-----------END CHAT------------------
    cont:
    mov al,254
    mov dx , 3F8H		; Transmit data register
  	out dx , al
    ext:
    notify emptyStatus
    pauseSound
endm pauseGame

Disp MACRO ymin1,ymax1,ymin2,x
    LOCAL D, backspace, enter, S1, S2
    mov bl,al
    cmp bl,8
    jz backspace
    cmp bl,13
    jz enter
    cmp bl,9
    jz D
    mov ah,3h
    mov bh,0h
    int 10h
    cmp dl,79
    jz D
    mov ah,8
    mov bh,0
    int 10h
    cmp al,179
    jz D

    mov ah,2
    mov dl,bl
    int 21h
    jmp D    

    backspace: ;if pressed back space 
    mov ah,3h
    mov bh,0h
    int 10h
    cmp dl,0
    jz D
    dec dl
    mov ah,2
    int 10h
    mov al,' ' ;write space in the previous position
        
    mov ah,2
    mov dl,al
    int 21h

    mov ah,3h
    mov bh,0h
    int 10h
    dec dl
    mov ah,2  ;set cursor at this position
    int 10h 
    jmp D

    enter:    ;if pressed enter
    mov ah,3h
    mov bh,0h
    int 10h
    cmp dh,ymax1
    jz S1
    cmp dh,23
    jz S2
    inc dh
    mov dl,0
    mov ah,2
    int 10h   ;set cursor at the next line
    jmp D
    
    S1:
    mov ah,6 ; function 6
    mov al,1 ; scroll by 1 line
    mov bh,7 ; normal video attribute
    mov ch,ymin1 ; upper left Y
    mov cl,0 ; upper left X
    mov dh,ymax1 ; lower right Y
    mov dl,x ; lower right X
    int 10h
    mov dl,0
    mov bx,0
    mov ah,2
    int 10h 
    jmp D
    
    S2:
    mov ah,6 ; function 6
    mov al,1 ; scroll by 1 line
    mov bh,7 ; normal video attribute
    mov ch,ymin2 ; upper left Y
    mov cl,0 ; upper left X
    mov dh,23 ; lower right Y
    mov dl,x ; lower right X
    int 10h
    mov dl,0
    mov bx,0
    mov ah,2
    int 10h
    
    D:
ENDM Disp
getKeys macro
    local mend, other_player, p2, p2_receive_only
    mov ah, 1
    int 16h
    jz other_player ; if no input continue
    ; clear buffer
    mov ah, 0
    int 16h
    cmp playerNumber, 1
    jnz p2
    ; I'm player 1
    mov key1, ah
    mov isDir1, al
    send key1
    ;send isDir1
    receive key2
    ;receive isDir2
    ;receive2 key2, isDir2
    jmp mend
    p2:
    ; I'm player 2
    mov key2, ah
    mov isDir2, al
    send key2
    ;send isDir2
    receive key1
    ;receive isDir1
    ;receive2 key1, isDir1
    jmp mend
    other_player:
    cmp playerNumber, 1
    jnz p2_receive_only
    ; I'm player 1, He's player 2
    mov key1, 0
    receive key2
    ;receive isDir2
    ;receive2 key2, isDir2
    jmp mend
    p2_receive_only:
    ; I'm player 2, He's player 1
    mov key2, 0
    receive key1
    ;receive isDir1
    ;receive2 key1, isDir1
    mend:
    mov ah, key1
    translateKeyPress
    mov key1, ah
    mov isDir1, al
    mov ah, key2
    translateKeyPress
    mov key2, ah
    mov isDir2, al
endm getKeys

mainGameLoop macro
    local mend, p2, direction_key1, build1, fire1, pause
    getKeys
    cmp key1, 0
    jz p2
    cmp isDir1, 1
    jz direction_key1
    cmp key1, 10h
    jz build1
    cmp key1, 11h
    jz fire1
    cmp key1, 3Bh
    jz pause
    jmp p2; error: shouldn't reach this line of code
    direction_key1:
    mov pnum, 1
    mov ah, key1
    mov player1Ori, ah
    mov si, offset player1
    mov bx, offset generalPlayer
    move ; move player1
    jmp p2
    build1:
    mov dl, player1x
    mov dh, player1y
    mov ch, player1Ori
    build
    jmp p2
    fire1:
    nwblt blt1, player1x
    p2:
    cmp key2, 0
    jz mend
    cmp isDir2, 1
    jz direction_key2
    cmp key2, 10h
    jz build2
    cmp key2, 11h
    jz fire2
    cmp key2, 3Bh
    jz pause
    jmp mend ; error shouldn't reach this line of code
    direction_key2:
    mov pnum, 2
    mov ah, key2
    mov player2Ori, ah
    mov si, offset player2
    mov bx, offset generalPlayer
    move ; move player2
    jmp mend
    build2:
    mov dl, player2x
    mov dh, player2y
    mov ch, player2Ori
    build
    jmp mend
    fire2:
    nwblt blt2, player2x
    jmp mend
    pause:
    pauseGame
    mend:
    chkmovblt blt1
    chkmovblt blt2
    delay 10000
endm mainGameLoop

pauseSound macro
	local delay1,delay2
        mov     al, 182         ; Prepare the speaker for the
        out     43h, al         ;  note.
        mov     ax, 4560        ; Frequency number (in decimal)
                                ;  for middle C.
        out     42h, al         ; Output low byte.
        mov     al, ah          ; Output high byte.
        out     42h, al
        xchg ax, dx
        mov     bx, 3			; Pause for duration of note.
delay1:
        in      al, 61h         ; Turn on note (get value from
                                ;  port 61h).
        or      al, 00000011b   ; Set bits 1 and 0.
        out     61h, al         ; Send new value.
        mov     cx, 65535
        xchg ax, dx
        sub ax, 500
        out     42h, al         ; Output low byte.
        mov     al, ah          ; Output high byte.
        out     42h, al
        xchg ax, dx

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
