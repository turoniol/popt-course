section  .text
  global _start
_start:
    mov eax, [a]
    mov ebx, [b]
    mov ecx, [c]
    
    add eax, [b]
    add eax, [c]
    
    add [result], eax

  mov  eax, 1
  mov ebx, 0
  int  0x80

section .bss
result resb 1

section  .data
a db 1
b db 2
c db 3
