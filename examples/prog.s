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
	subq $8, %rsp
	subq $8, %rsp
	pushq $2
	movq 16(%rbp), %rax
	pushq %rax
	movq -32(%rbp), %rax
	movq -40(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -24(%rbp)
	addq $16, %rsp
	subq $8, %rsp
	pushq $3
	movq 24(%rbp), %rax
	pushq %rax
	movq -40(%rbp), %rax
	movq -48(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -32(%rbp)
	addq $16, %rsp
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
	pushq $5
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
	movq %rax, -8(%rbp)
	addq $8, %rsp
	subq $8, %rsp
	pushq $2
	movq -24(%rbp), %rax
	movq %rax, -16(%rbp)
	addq $8, %rsp
	subq $8, %rsp
	pushq $1
	movq -16(%rbp), %rax
	pushq %rax
	movq -40(%rbp), %rax
	pushq %rax
	movq -32(%rbp), %rax
	pushq %rax
	call f
	pushq %rax
	movq -8(%rbp), %rax
	pushq %rax
	pushq $1
	pushq $1
	movq -88(%rbp), %rax
	pushq %rax
	movq -80(%rbp), %rax
	pushq %rax
	call f
	pushq %rax
	movq -112(%rbp), %rax
	pushq %rax
	movq -72(%rbp), %rax
	pushq %rax
	call f
	pushq %rax
	movq -136(%rbp), %rax
	pushq %rax
	movq -64(%rbp), %rax
	pushq %rax
	call f
	pushq %rax
	movq -160(%rbp), %rax
	movq %rax, -24(%rbp)
	addq $8, %rsp
	subq $8, %rsp
	movq -24(%rbp), %rax
	pushq %rax
	pushq $1
	pushq $2
	movq -184(%rbp), %rax
	pushq %rax
	movq -176(%rbp), %rax
	pushq %rax
	call f
	pushq %rax
	movq -168(%rbp), %rax
	movq -208(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -160(%rbp)
	addq $8, %rsp
	movq -160(%rbp), %rax
	addq $200, %rsp

	movq %rbp, %rsp
	pop %rbp
	ret

