.section .text
	.global _start

_start:
	call main
	movq %rax, %rdi
	movq $60, %rax
	syscall

fib:
	push %rbp
	movq %rsp, %rbp

	movq -1(%rbp), %rax
	call if
	pushq %rax
	movq 16(%rbp), %rax
	pushq %rax
	movq -16(%rbp), %rax
	movq 16(%rbp), %rax
	pushq %rax
	pushq $1
	popq %rbx
	popq %rax
	subq %rbx, %rax
	pushq %rax
	movq -24(%rbp), %rax
	call fib
	pushq %rax
	movq 16(%rbp), %rax
	pushq %rax
	pushq $2
	popq %rbx
	popq %rax
	subq %rbx, %rax
	pushq %rax
	movq -40(%rbp), %rax
	call fib
	pushq %rax
	popq %rbx
	popq %rax
	addq %rbx, %rax
	pushq %rax
	movq -40(%rbp), %rax

	movq %rbp, %rsp
	pop %rbp
	ret

main:
	push %rbp
	movq %rsp, %rbp

	pushq $9
	movq -8(%rbp), %rax
	call fib
	pushq %rax
	movq -16(%rbp), %rax

	movq %rbp, %rsp
	pop %rbp
	ret

