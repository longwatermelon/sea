.section .text
	.global _start

_start:
	call main
	movq %rax, %rdi
	movq $60, %rax
	syscall

main:
	push %rbp
	movq %rsp, %rbp

	subq $8, %rsp
	pushq $0
	movq -16(%rbp), %rax
	movq %rax, -8(%rbp)
	addq $8, %rsp
	movq -8(%rbp), %rax
	pushq %rax
	movq -16(%rbp), %rax
	test %rax, %rax
	jz .L_else_0
	subq $8, %rsp
	pushq $2
	movq -32(%rbp), %rax
	movq %rax, -24(%rbp)
	addq $8, %rsp
	addq $8, %rsp
	jmp .L_end_0
.L_else_0:
	pushq $4
	movq -24(%rbp), %rax
	movq %rbp, %rsp
	pop %rbp
	ret
	addq $24, %rsp
	addq $-16, %rsp
.L_end_0:
	addq $8, %rsp
	pushq $5
	movq -16(%rbp), %rax
	movq %rbp, %rsp
	pop %rbp
	ret
	addq $8, %rsp
	addq $8, %rsp

	movq %rbp, %rsp
	pop %rbp
	ret

