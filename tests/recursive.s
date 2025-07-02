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
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -24(%rbp)
	subq $8, %rsp
	pushq $3
	movq 24(%rbp), %rax
	pushq %rax
	movq -40(%rbp), %rax
	movq -48(%rbp), %rbx
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -32(%rbp)
	movq -24(%rbp), %rax
	movq -32(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %rax
	movq %rax, -8(%rbp)
	addq $8, %rsp
	subq $8, %rsp
	movq -8(%rbp), %rax
	pushq %rax
	pushq $5
	movq -24(%rbp), %rax
	movq -32(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %rax
	movq %rbp, %rsp
	pop %rbp
	ret
	addq $16, %rsp

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
	addq $32, %rsp
	pushq %rax
	movq -8(%rbp), %rax
	pushq %rax
	pushq $1
	pushq $1
	movq -56(%rbp), %rax
	pushq %rax
	movq -48(%rbp), %rax
	pushq %rax
	call f
	addq $32, %rsp
	pushq %rax
	movq -48(%rbp), %rax
	pushq %rax
	movq -40(%rbp), %rax
	pushq %rax
	call f
	addq $32, %rsp
	pushq %rax
	movq -40(%rbp), %rax
	pushq %rax
	movq -32(%rbp), %rax
	pushq %rax
	call f
	addq $32, %rsp
	pushq %rax
	movq -32(%rbp), %rax
	movq %rax, -24(%rbp)
	addq $8, %rsp
	subq $8, %rsp
	movq -24(%rbp), %rax
	pushq %rax
	pushq $1
	pushq $2
	movq -56(%rbp), %rax
	pushq %rax
	movq -48(%rbp), %rax
	pushq %rax
	call f
	addq $32, %rsp
	pushq %rax
	movq -40(%rbp), %rax
	movq -48(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -32(%rbp)
	movq -32(%rbp), %rax
	movq %rbp, %rsp
	pop %rbp
	ret
	addq $32, %rsp

	movq %rbp, %rsp
	pop %rbp
	ret

