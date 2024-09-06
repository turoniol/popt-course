section .data:
    arr db 1, 8, 3, 5, 2
    len equ $ - arr

section .bss
    sorted resb len
    print_str resb len + 1

section .text
    global _start

; Excpects input arr in rsi
print_array:
    mov rcx, len
    mov rdi, print_str

    print_body:
        mov byte al, [rsi]
        mov byte [rdi], al
        add byte [rdi], '0'

        inc rsi
        inc rdi

    loop print_body

    mov byte [rdi], 0xa

    mov eax, 4
    mov ebx, 1
    mov ecx, print_str
    mov edx, len + 1
    int 0x80
    ret
    
_start:
    lea rsi, [arr]
    call print_array

exit:
    mov eax, 1
    mov ebx, 0
    int 0x80
