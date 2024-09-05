section .data
    arr dd 1, 8, 3, 5, 2
    len equ ($ - arr) / 4

section .bss
    result resd 1

section .text
    global _start

_start:
    mov ecx, len

    ; Pointer to array
    lea rsi, [arr]

    mov eax, [rsi]

    add rsi, 4

body:
    mov ebx, [rsi]
    cmp eax, ebx

    jge next

    mov eax, ebx

next:
    add rsi, 4
    loop body

    mov [result], eax

exit:
    mov eax, 1
    mov ebx, [result]   ; Set as error code for simple res validation
    int 0x80