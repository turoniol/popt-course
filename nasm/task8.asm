section .data:
    arr db 1, 8, 3, 5, 2
    len equ $ - arr

section .bss
    arraySize resb 1
    sorted resb len
    print_str resb len + 1

section .text
    global _start

; bublesort:
;     mov rcx, len

;     lea rsi, [arr]
;     lea rdi, [arr]

;     next:
;         mov r8, 0

;         mov r9, rsi
;         mov r10, rdi

;         body:
;             mov al, [r9]
;             mov bl, [r10]

;             cmp al, bl
;             jge next1

;             mov [r9], bl
;             mov [r10], al

;             mov r8, 1

;         next1:
;             inc r9
;             inc r10

;         loop body

;         cmp r8, 0
;         jne next

;     ret

; Excpects len in rcx, arr in rsi, result in rdi
print_array:
    mov [arraySize], cl

    print_body:
        mov eax, [rsi]
        mov [rdi], eax
        add byte [rdi], '0'

        inc rsi
        inc rdi

    loop print_body

    mov byte [rdi], 0xa
    sub byte [rdi], arraySize

    mov eax, 4
    mov ebx, 1
        
    mov ecx, rdi
    mov edx, [arraySize]
    int 0x80
    ret

_start:
    mov rcx, len
    lea rsi, [arr]
    lea rdi, [print_str]
    call print_array

exit:
    mov eax, 1
    mov ebx, 0
    int 0x80
