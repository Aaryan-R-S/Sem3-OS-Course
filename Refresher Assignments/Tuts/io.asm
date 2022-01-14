section	.data
    ;text db "Hello world", 10
    query db "Enter your name: "
    greet db "Hello, "
    
section .bss
    name resb 16
    
section .text
    ;Running : https://ideone.com/
    global _start

_start:
    ;sub-routines
    call _printQuery
    call _inputName
    call _printGreet
    call _printName
    mov rax, 60
    mov rdi, 0
    syscall
    
_printQuery:
    ;rax/rdi : read=0 : write=1
    ;rsi : store name
    ;rdx : max bits=16
    mov rax, 1
    mov rdi, 1
    mov rsi, query
    mov rdx, 24
    syscall
    ret
    
_inputName:
    mov rax, 0
    mov rdi, 0
    mov rsi, name
    mov rdx, 16
    syscall
    ret
    
_printGreet:
    mov rax, 1
    mov rdi, 1
    mov rsi, greet
    mov rdx, 7
    syscall
    ret
    
_printName:
    mov rax, 1
    mov rdi, 1
    mov rsi, name
    mov rdx, 16
    syscall
    ret
    

    