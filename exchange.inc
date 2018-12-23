areYouReady macro
    local s, mend
    mov tmp, 0DDh
    send tmp
    receive tmp
    cmp tmp, 0
    jz s
    mov playerNumber, 1
    jmp mend
    s:
    notify waiting
    mov playerNumber, 0
    blockReceive tmp
    notify emptyStatus
    mend:
endm areYouReady

exchangeNames macro
    local player2, mend, sendUser1, receiveUser2, receiveUser1, sendUser2, finish1, finish2
    cmp playerNumber, 1
    jz player2
    mov ch, 0
    mov cl, user1[1]
    mov bx, 0
    sendUser1:
    send player1Name[bx]
    inc bx
    loop sendUser1
    mov tmp, 0FFh
    send tmp
    mov bx, 0
    receiveUser1:
    blockReceive tmp
    cmp tmp, 0FFh
    jz finish1
    mov al, tmp
    mov player2Name[bx], al
    inc bx
    jmp receiveUser1
    finish1:
    mov player2Name[bx], '$'
    jmp mend
    player2:
    mov si, offset player1Name
    mov di, offset player2Name
    mov ch, 0
    mov cl, user1[1]
    rep movsb
    mov bx, 0
    receiveUser2:
    blockReceive tmp
    cmp tmp, 0FFh
    jz finish2
    mov al, tmp
    mov player1Name[bx], al
    inc bx
    jmp receiveUser2
    finish2:
    mov player1Name[bx], '$'
    mov bx, 0
    mov ch, 0
    mov cl, user1[1]
    sendUser2:
    send player2Name[bx]
    inc bx
    loop sendUser2
    mov tmp, 0FFh
    send tmp
    mend:
endm exchangeNames
