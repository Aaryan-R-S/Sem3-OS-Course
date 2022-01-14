	.file	"b.c"
	.intel_syntax noprefix
	.text
	.section	.rodata
.LC0:
	.string	"Inside B\n"
	.text
	.globl	B
	.type	B, @function
B:
.LFB6:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 48
	mov	QWORD PTR -40[rbp], rdi
	mov	edx, 10
	lea	rax, .LC0[rip]
	mov	rsi, rax
	mov	edi, 1
	call	write@PLT
	mov	edi, 8
	call	malloc@PLT
	mov	QWORD PTR -8[rbp], rax
	mov	DWORD PTR -24[rbp], 0
	mov	DWORD PTR -20[rbp], 0
	jmp	.L2
.L5:
	mov	DWORD PTR -24[rbp], 0
	mov	DWORD PTR -16[rbp], 0
	jmp	.L3
.L4:
	mov	eax, DWORD PTR -20[rbp]
	lea	edx, 0[0+rax*8]
	mov	eax, DWORD PTR -16[rbp]
	add	eax, edx
	mov	rdx, QWORD PTR -40[rbp]
	mov	ecx, eax
	sar	rdx, cl
	mov	rax, rdx
	and	eax, 1
	mov	edx, eax
	mov	eax, DWORD PTR -16[rbp]
	mov	ecx, eax
	sal	edx, cl
	mov	eax, DWORD PTR -24[rbp]
	add	eax, edx
	mov	DWORD PTR -24[rbp], eax
	add	DWORD PTR -16[rbp], 1
.L3:
	cmp	DWORD PTR -16[rbp], 7
	jle	.L4
	mov	eax, 7
	sub	eax, DWORD PTR -20[rbp]
	movsx	rdx, eax
	mov	rax, QWORD PTR -8[rbp]
	add	rax, rdx
	mov	edx, DWORD PTR -24[rbp]
	mov	BYTE PTR [rax], dl
	add	DWORD PTR -20[rbp], 1
.L2:
	cmp	DWORD PTR -20[rbp], 7
	jle	.L5
	mov	DWORD PTR -12[rbp], 0
	jmp	.L6
.L7:
	mov	eax, DWORD PTR -12[rbp]
	movsx	rdx, eax
	mov	rax, QWORD PTR -8[rbp]
	add	rax, rdx
	movzx	eax, BYTE PTR [rax]
	movsx	eax, al
	mov	edi, eax
	call	putchar@PLT
	add	DWORD PTR -12[rbp], 1
.L6:
	cmp	DWORD PTR -12[rbp], 7
	jle	.L7
	mov	edi, 10
	call	putchar@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	B, .-B
	.ident	"GCC: (GNU) 11.1.0"
	.section	.note.GNU-stack,"",@progbits
