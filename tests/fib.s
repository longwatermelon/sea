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

	subq $8, %rsp
	subq $8, %rsp
	movq 16(%rbp), %rax
	pushq %rax
	pushq $0
	movq -24(%rbp), %rax
	movq -32(%rbp), %rbx
	cmp %rbx, %rax
	sete %al
	movzbl %al, %eax
	movq %rax, -16(%rbp)
	addq $16, %rsp
	subq $8, %rsp
	movq 16(%rbp), %rax
	pushq %rax
	pushq $1
	movq -32(%rbp), %rax
	movq -40(%rbp), %rbx
	cmp %rbx, %rax
	sete %al
	movzbl %al, %eax
	movq %rax, -24(%rbp)
	addq $16, %rsp
	movq -16(%rbp), %rax
	movq -24(%rbp), %rbx
	or %rbx, %rax
	movq %rax, -8(%rbp)
	addq $16, %rsp
	movq -8(%rbp), %rax
	test %rax, %rax
	jz .L_else_0
	movq 16(%rbp), %rax
	pushq %rax
	movq -16(%rbp), %rax
	movq %rbp, %rsp
	pop %rbp
	ret
	addq $8, %rsp
	jmp .L_end_0
.L_else_0:
.L_end_0:
	addq $8, %rsp
	subq $8, %rsp
	subq $8, %rsp
	movq 16(%rbp), %rax
	pushq %rax
	pushq $1
	movq -24(%rbp), %rax
	movq -32(%rbp), %rbx
	subq %rbx, %rax
	movq %rax, -16(%rbp)
	addq $16, %rsp
	movq -16(%rbp), %rax
	pushq %rax
	call fib
	pushq %rax
	subq $8, %rsp
	movq 16(%rbp), %rax
	pushq %rax
	pushq $2
	movq -48(%rbp), %rax
	movq -56(%rbp), %rbx
	subq %rbx, %rax
	movq %rax, -40(%rbp)
	addq $16, %rsp
	movq -40(%rbp), %rax
	pushq %rax
	call fib
	pushq %rax
	movq -32(%rbp), %rax
	movq -56(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -8(%rbp)
	addq $8, %rsp
	movq -8(%rbp), %rax
	movq %rbp, %rsp
	pop %rbp
	ret
	addq $48, %rsp

	movq %rbp, %rsp
	pop %rbp
	ret

main:
	push %rbp
	movq %rsp, %rbp

	pushq $9
	movq -8(%rbp), %rax
	pushq %rax
	call fib
	pushq %rax
	movq -24(%rbp), %rax
	movq %rbp, %rsp
	pop %rbp
	ret
	addq $8, %rsp
	addq $16, %rsp

	movq %rbp, %rsp
	pop %rbp
	ret

