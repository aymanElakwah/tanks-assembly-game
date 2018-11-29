mem2mem macro index ;bx = si
    mov dl, [si + index]
    mov [bx + index], dl
endm mem2mem

translateKeyPress macro ;input:scan code in ah/output:symbol in ah, al: playerNumber
local right, down, left, w, a, s, d, notDirectionKey
    ;48 up, 4D right, 50 down, 4B left
    mov al, 1; player 1
    cmp ah, 48h
    jnz right
    mov ah, 1Eh
    jmp finish
    right:
    cmp ah, 4Dh
    jnz down
    mov ah, 10h
    jmp finish
    down:
    cmp ah, 50h
    jnz left
    mov ah, 1Fh
    jmp finish
    left:
    cmp ah, 4Bh
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

move macro
    mem2mem 0
    mem2mem 1
    mem2mem 2
    movePlayer
    xchg bx, si
    mem2mem 0
    mem2mem 1
    mem2mem 2
    endm move

draw macro
    mem2mem 0
    mem2mem 1
    mem2mem 2
    drawPlayer
    xchg bx, si
    mem2mem 0
    mem2mem 1
    mem2mem 2
    endm draw

mainGameLoop macro
    local player2Check, continue
    ; get input from user
    mov ah, 1
    int 16h
    jz continue
    mov ah, 0
    int 16h
    translateKeyPress
    mov pnum, al
    cmp al, 1
    jnz player2Check
    mov player1Ori, ah
    mov si, offset player1
    mov bx, offset generalPlayer
    move
    jmp continue
    player2Check:
    cmp al, 2
    jnz continue
    mov player2Ori, ah
    mov si, offset player2
    mov bx, offset generalPlayer
    move
    continue:
endm mainGameLoop
