.section .text
	.global _start

_start:
	call main
	movq %rax, %rdi
	movq $60, %rax
	syscall

f:
	push %rbp
	movq %rsp, %rbp

	subq $8, %rsp
	movq 16(%rbp), %rax
	pushq (%rax)
	movq 16(%rbp), %rax
	pushq (%rax)
	movq -16(%rbp), %rax
	movq -24(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -8(%rbp)
	movq 16(%rbp), %rbx
	movq -8(%rbp), %rax
	movq %rax, (%rbx)
	addq $8, %rsp

	movq %rbp, %rsp
	pop %rbp
	ret

main:
	push %rbp
	movq %rsp, %rbp

	subq $8, %rsp
	pushq $5
	movq -16(%rbp), %rax
	movq %rax, -8(%rbp)
	addq $8, %rsp
	subq $8, %rsp
	leaq -8(%rbp), %rax
	pushq %rax
	pushq %rax
	movq -32(%rbp), %rax
	movq %rax, -16(%rbp)
	addq $8, %rsp
	subq $8, %rsp
	leaq -16(%rbp), %rax
	pushq %rax
	pushq %rax
	movq -48(%rbp), %rax
	movq %rax, -32(%rbp)
	addq $8, %rsp
	leaq -16(%rbp), %rax
	pushq %rax
	pushq %rax
	movq -56(%rbp), %rax
	pushq %rax
	movq -64(%rbp), %rax
	addq $8, %rsp
	pushq (%rax)
	movq -64(%rbp), %rax
	pushq %rax
	call f
	addq $16, %rsp
	pushq %rax
	addq $8, %rsp
	movq -32(%rbp), %rax
	pushq (%rax)
	movq -64(%rbp), %rax
	pushq %rax
	call f
	addq $16, %rsp
	pushq %rax
	addq $8, %rsp
	movq -8(%rbp), %rax
	movq %rbp, %rsp
	pop %rbp
	ret
	addq $56, %rsp

	movq %rbp, %rsp
	pop %rbp
	ret

