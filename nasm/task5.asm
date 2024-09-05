section .data
    arr dd 1, 8, 3, 5, 2, 9, 2, 6, 3
    len equ ($ - arr) / 4

section .bss
    result resd 1

section .text
    global _start

_start:
    mov ecx, len

    ; Pointer to array
    lea rsi, [arr]
    ; Max value
    mov eax, [rsi]
    
next:
    add rsi, 4
    dec ecx
    jz end_loop

body:
    mov ebx, [rsi]
    cmp eax, ebx
    jge it1

    mov eax, ebx
it1:
    dec ecx
    jz end_loop
    add rsi, 4

    mov ebx, [rsi]
    cmp eax, ebx
    jge it2

    mov eax, ebx

it2:
    dec ecx
    jz end_loop
    add rsi, 4

    mov ebx, [rsi]
    cmp eax, ebx
    jge it3

    mov eax, ebx
it3:
    dec ecx
    jz end_loop
    add rsi, 4

    mov ebx, [rsi]
    cmp eax, ebx
    jge next

end_loop:
    mov [result], eax

exit:
    mov eax, 1
    mov ebx, [result]   ; Set as error code for simple res validation
    int 0x80