; load 'dh' sectors from drive 'dl' into ES:BX
disk_load:
    pusha
    push dx       ; Save the requested sector count (in dh)

    mov ah, 0x02
    mov al, dh    ; Number of sectors to read
    mov cl, 0x02
    mov ch, 0x00
    mov dh, 0x00
    int 0x13
    jc disk_error

    pop dx        ; Restore the requested count into dx
    cmp al, dh    ; Now compare sectors read (al) to sectors requested (dh)
    jne sectors_error
    popa
    ret


disk_error:
    mov bx, DISK_ERROR
    call print
    call print_nl
    mov dh, ah ; ah = error code, dl = disk drive that dropped the error
    call print_hex ; check out the code at http://stanislavs.org/helppc/int_13-1.html
    jmp disk_loop

sectors_error:
    mov bx, SECTORS_ERROR
    call print

disk_loop:
    jmp $

DISK_ERROR: db "Disk read error", 0
SECTORS_ERROR: db "Incorrect number of sectors read", 0
