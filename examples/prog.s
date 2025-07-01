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

	pushq $5
	movq -8(%rbp), %rax
	pushq %rax
	pushq $1
	popq %rbx
	popq %rax
	addq %rbx, %rax
	pushq %rax
	movq -8(%rbp), %rax
	pushq %rax
	pushq $2
	movq -16(%rbp), %rax
	pushq %rax
	popq %rbx
	popq %rax
	imulq %rbx, %rax
	pushq %rax
	popq %rbx
	popq %rax
	addq %rbx, %rax
	pushq %rax
	pushq $1
	popq %rbx
	popq %rax
	addq %rbx, %rax
	pushq %rax
	pushq $1
	movq -24(%rbp), %rax
	pushq %rax
	popq %rbx
	popq %rax
	addq %rbx, %rax
	pushq %rax
	movq -32(%rbp), %rax

	movq %rbp, %rsp
	pop %rbp
	ret

