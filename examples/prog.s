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
	pushq $5
	movq -16(%rbp), %rax
	movq %rax, -8(%rbp)
	addq $8, %rsp
	subq $8, %rsp
	subq $8, %rsp
	movq -8(%rbp), %rax
	pushq %rax
	pushq $1
	movq -32(%rbp), %rax
	movq -40(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -24(%rbp)
	addq $16, %rsp
	movq -24(%rbp), %rax
	movq %rax, -16(%rbp)
	addq $8, %rsp
	subq $8, %rsp
	subq $8, %rsp
	subq $8, %rsp
	subq $8, %rsp
	subq $8, %rsp
	subq $8, %rsp
	subq $8, %rsp
	subq $8, %rsp
	subq $8, %rsp
	subq $8, %rsp
	movq -8(%rbp), %rax
	pushq %rax
	subq $8, %rsp
	pushq $2
	movq -16(%rbp), %rax
	pushq %rax
	movq -120(%rbp), %rax
	movq -128(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -112(%rbp)
	addq $16, %rsp
	movq -104(%rbp), %rax
	movq -112(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -96(%rbp)
	addq $16, %rsp
	pushq $1
	movq -96(%rbp), %rax
	movq -104(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -88(%rbp)
	addq $16, %rsp
	movq -8(%rbp), %rax
	pushq %rax
	movq -88(%rbp), %rax
	movq -96(%rbp), %rbx
	subq %rbx, %rax
	movq %rax, -80(%rbp)
	addq $16, %rsp
	movq -8(%rbp), %rax
	pushq %rax
	movq -80(%rbp), %rax
	movq -88(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -72(%rbp)
	addq $16, %rsp
	movq -8(%rbp), %rax
	pushq %rax
	movq -72(%rbp), %rax
	movq -80(%rbp), %rbx
	subq %rbx, %rax
	movq %rax, -64(%rbp)
	addq $16, %rsp
	subq $8, %rsp
	subq $8, %rsp
	subq $8, %rsp
	movq -8(%rbp), %rax
	pushq %rax
	pushq $2
	movq -96(%rbp), %rax
	movq -104(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -88(%rbp)
	addq $16, %rsp
	subq $8, %rsp
	subq $8, %rsp
	pushq $3
	pushq $1
	movq -112(%rbp), %rax
	movq -120(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -104(%rbp)
	addq $16, %rsp
	movq -8(%rbp), %rax
	pushq %rax
	movq -104(%rbp), %rax
	movq -112(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -96(%rbp)
	addq $16, %rsp
	movq -88(%rbp), %rax
	movq -96(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -80(%rbp)
	addq $16, %rsp
	pushq $5
	movq -80(%rbp), %rax
	movq -88(%rbp), %rbx
	subq %rbx, %rax
	movq %rax, -72(%rbp)
	addq $16, %rsp
	movq -64(%rbp), %rax
	movq -72(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -56(%rbp)
	addq $16, %rsp
	pushq $5
	movq -56(%rbp), %rax
	movq -64(%rbp), %rbx
	subq %rbx, %rax
	movq %rax, -48(%rbp)
	addq $16, %rsp
	pushq $2
	movq -48(%rbp), %rax
	movq -56(%rbp), %rbx
	subq %rbx, %rax
	movq %rax, -40(%rbp)
	addq $16, %rsp
	movq -16(%rbp), %rax
	pushq %rax
	movq -40(%rbp), %rax
	movq -48(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -32(%rbp)
	addq $16, %rsp
	subq $8, %rsp
	pushq $2
	subq $8, %rsp
	movq -16(%rbp), %rax
	pushq %rax
	subq $8, %rsp
	pushq $3
	movq -16(%rbp), %rax
	pushq %rax
	movq -80(%rbp), %rax
	movq -88(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -72(%rbp)
	addq $16, %rsp
	movq -64(%rbp), %rax
	movq -72(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -56(%rbp)
	addq $16, %rsp
	movq -48(%rbp), %rax
	movq -56(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -40(%rbp)
	addq $16, %rsp
	movq -32(%rbp), %rax
	movq -40(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -24(%rbp)
	addq $16, %rsp
	movq -24(%rbp), %rax
	movq %rax, -16(%rbp)
	addq $8, %rsp
	subq $8, %rsp
	pushq $1
	movq -16(%rbp), %rax
	pushq %rax
	movq -32(%rbp), %rax
	movq -40(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -24(%rbp)
	addq $16, %rsp
	movq -24(%rbp), %rax
	addq $8, %rsp
	addq $16, %rsp

	movq %rbp, %rsp
	pop %rbp
	ret

