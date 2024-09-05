section  .data
    msg db 'Hello World!', 0xa
    len equ $ - msg

section .bss
    reversed resb len

section  .text
    global _start
_start:
    mov rcx, len
    
    ; Pointer to reversed 0 -> n
    mov rsi, reversed
    
    ; Pointer to base n -> 0
    lea rdi, [msg + len - 1]
    
    body:
        mov al, [rdi]
        mov [rsi], al
        
        inc rsi
        dec rdi
            
        loop body
    
    mov byte [rsi], 0

display:
    mov eax, 4
    mov ebx, 1
    mov ecx, reversed
    mov edx, len
    int 0x80
    
exit:
    mov eax, 1
    mov ebx, 0
    int 0x80