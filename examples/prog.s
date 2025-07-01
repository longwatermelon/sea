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
	pushq %rax
	movq -16(%rbp), %rax
	movq %rax, -8(%rbp)
	addq $8, %rsp
	subq $8, %rsp
	movq -8(%rbp), %rax
	pushq %rax
	pushq $5
	movq -24(%rbp), %rax
	movq -32(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -16(%rbp)
	addq $16, %rsp
	movq -16(%rbp), %rax
	movq %rax, -8(%rbp)
	addq $8, %rsp
	subq $8, %rsp
	movq -8(%rbp), %rax
	pushq %rax
	pushq $1
	movq -24(%rbp), %rax
	movq -32(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -16(%rbp)
	addq $16, %rsp
	movq -16(%rbp), %rax
	addq $8, %rsp
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
	call f
	pushq %rax
	pushq $2
	movq -24(%rbp), %rax
	movq -32(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -8(%rbp)
	addq $24, %rsp
	movq -8(%rbp), %rax
	addq $8, %rsp

	movq %rbp, %rsp
	pop %rbp
	ret

