mem2mem macro index ;bx = si ; put the byte located at si in bx (memory)
    mov dl, [si + index]
    mov [bx + index], dl
endm mem2mem

translateKeyPress macro ;input:scan code in ah/output:symbol in ah, al: playerNumber
local right, down, left, w, a, s, d, notDirectionKey
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
    jnz w
    mov ah, 11h
    jmp finish
    ; w, a, s, d
    w:
    mov al, 2 ; player 2
    cmp ah, 11h
    jnz d
    mov ah, 1Eh
    jmp finish
    d:
    cmp ah, 20h
    jnz s
    mov ah, 10h
    jmp finish
    s:
    cmp ah, 1Fh
    jnz a
    mov ah, 1Fh
    jmp finish
    a:
    cmp ah, 1Eh
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
    local pause_game
    notify pausedStatus
    pause_game:
    mov ah, 1
    int 16h
    jz pause_game
    mov ah, 0
    int 16h
    cmp ah, 1Ch
    jnz pause_game
    notify emptyStatus
endm pauseGame

mainGameLoop macro
    local player2Check, continue, checkBuild, checkBuild2, checkFire1, checkFire2, finish, pause, notExit
    ;delay
    dec bp
    jnz finish
    ; get input from user
    mov ah, 1
    int 16h
    jz continue ; if no input continue
    ; clear buffer
    mov ah, 0
    int 16h
    cmp ah, 1 ;is ESC?
    jnz notExit
    exitGame
    jz finish
    notExit:
    translateKeyPress ; translate the key pressed to get the Orintation
    mov pnum, al
    cmp al, 1 ; is player1?
    jnz player2Check
    mov player1Ori, ah
    mov si, offset player1
    mov bx, offset generalPlayer
    move ; move player1
    jmp continue
    player2Check:
    cmp al, 2 ; is player2?
    jnz checkBuild
    mov player2Ori, ah
    mov si, offset player2
    mov bx, offset generalPlayer
    move ; move player2
    jmp continue
    checkBuild:
    cmp ah, 35h ; is player1 trying to build?
    jnz checkBuild2
    mov dl, player1x
    mov dh, player1y
    mov ch, player1Ori
    build
    jmp continue
    checkBuild2:
    cmp ah, 12h ; is player2 trying to build?
    jnz checkFire1
    mov dl, player2x
    mov dh, player2y
    mov ch, player2Ori
    build
    jmp continue
    checkFire1:
    cmp ah, 34h ; is player1 trying to fire?
    jnz checkFire2
    nwblt blt1, player1x
    jmp continue
    checkFire2:
    cmp ah, 13h ; is player2 trying to fire?
    jnz pause
    nwblt blt2, player2x
    jmp continue
    pause:
    cmp ah, 1Ch
    jnz continue
    pauseGame
    continue:
    chkmovblt blt1
    chkmovblt blt2
    mov bp, 10000
    finish:
endm mainGameLoop
