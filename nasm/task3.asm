section .data
    first  dd 1
    second dd 2 
    third  dd 3

section .bss
    result resd 1

section .text
    global _start

_start:
    mov eax, [first]
    mov ebx, [second]
    mov ecx, [third]

    cmp eax, ebx
    jge first_greater
    mov eax, ebx

first_greater:
    cmp eax, ecx
    jge store   ; First is the biggest
    mov eax, ecx    ; Third is bigger

store:
    mov [result], eax
exit:
    mov eax, 1
    mov ebx, [result]   ; Set as error code for simple res validation
    int 0x80