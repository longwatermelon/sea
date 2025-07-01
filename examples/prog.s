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

	pushq $3
	movq -8(%rbp), %rax

	movq %rbp, %rsp
	pop %rbp
	ret

main:
	push %rbp
	movq %rsp, %rbp

	pushq $4
	pushq $1
	popq %rbx
	popq %rax
	subq %rbx, %rax
	pushq %rax
	pushq $2
	popq %rbx
	popq %rax
	addq %rbx, %rax
	pushq %rax
	pushq $1
	popq %rbx
	popq %rax
	subq %rbx, %rax
	pushq %rax
	pushq $1
	popq %rbx
	popq %rax
	subq %rbx, %rax
	pushq %rax
	movq -8(%rbp), %rax

	movq %rbp, %rsp
	pop %rbp
	ret

