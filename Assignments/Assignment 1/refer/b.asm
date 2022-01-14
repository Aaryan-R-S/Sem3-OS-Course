extern	C

section .bss
	num resb 8
	
section .data
	text1 db "Inside B", 10
	text2 db 10

section .text
	global B 

B:
	mov [num], rdi

	mov rax, 1
	mov rdi, 1
	mov rsi, text1
	mov rdx, 9
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, num
	mov rdx, 8
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, text2
	mov rdx, 1
	syscall

	push C
	ret