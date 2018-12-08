exitGame macro
    mov ah, 0
    mov al, 3
    int 10h
    mov ax, 4c00h ; exit to operating system.
    int 21h
endm exitGame
