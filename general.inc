exitGame macro
    mov ah, 0
    mov al, 3
    int 10h
    mov ax, 4c00h ; exit to operating system.
    int 21h
endm exitGame

users macro
    mov dl, 0
    mov dh, 1
    mov ah, 2
    int 10h
    mov dx, offset player1Name
    mov ah, 9
    int 21h
    mov dl, 0
    mov dh, 12
    mov ah, 2
    int 10h
    mov dx, offset player2Name
    mov ah, 9
    int 21h
endm users

notify macro string
    mov dl, 1
    mov dh, 24
    mov ah, 2
    int 10h
    mov dx, offset string
    mov ah, 9
    int 21h
endm status

readInput macro memory
    push bx
    mov dx, offset memory
    mov ah, 0Ah
    int 21h
    mov bh, 0
    mov bl, memory + 1
    add bx, 2
    mov memory[bx], '$'
    pop bx
endm readInput
