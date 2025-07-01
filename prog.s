.section .text
	.global _start

_start:
	call main
	movq %rax, %rdi
	movq $60, %rax
	syscall

function:
	push %rbp
	movq %rsp, %rbp

	sub $8, %rsp
	movq $3, -8(%rbp)
	movq -8(%rbp), %rax

	movq %rbp, %rsp
	pop %rbp
	ret

main:
	push %rbp
	movq %rsp, %rbp

	sub $8, %rsp
	movq $4, -8(%rbp)
	movq -8(%rbp), %rax

	movq %rbp, %rsp
	pop %rbp
	ret

