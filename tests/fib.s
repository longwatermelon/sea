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
	pushq $0
	movq 16(%rbp), %rax
	movq -24(%rbp), %rbx
	addq $8, %rsp
	cmp %rbx, %rax
	sete %al
	movzbl %al, %eax
	movq %rax, -16(%rbp)
	subq $8, %rsp
	pushq $1
	movq 16(%rbp), %rax
	movq -32(%rbp), %rbx
	addq $8, %rsp
	cmp %rbx, %rax
	sete %al
	movzbl %al, %eax
	movq %rax, -24(%rbp)
	movq -16(%rbp), %rax
	movq -24(%rbp), %rbx
	addq $16, %rsp
	or %rbx, %rax
	movq %rax, -8(%rbp)
	movq -8(%rbp), %rax
	addq $8, %rsp
	test %rax, %rax
	jz .L_else_0
	movq 16(%rbp), %rax
	movq %rbp, %rsp
	pop %rbp
	ret
	jmp .L_end_0
.L_else_0:
.L_end_0:
	subq $8, %rsp
	subq $8, %rsp
	pushq $1
	movq 16(%rbp), %rax
	movq -24(%rbp), %rbx
	addq $8, %rsp
	subq %rbx, %rax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %rax
	pushq %rax
	call fib
	addq $16, %rsp
	pushq %rax
	subq $8, %rsp
	pushq $2
	movq 16(%rbp), %rax
	movq -32(%rbp), %rbx
	addq $8, %rsp
	subq %rbx, %rax
	movq %rax, -24(%rbp)
	movq -24(%rbp), %rax
	pushq %rax
	call fib
	addq $16, %rsp
	pushq %rax
	movq -16(%rbp), %rax
	movq -24(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -8(%rbp)
	movq -8(%rbp), %rax
	movq %rbp, %rsp
	pop %rbp
	ret
	addq $8, %rsp

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
	addq $16, %rsp
	pushq %rax
	movq -8(%rbp), %rax
	movq %rbp, %rsp
	pop %rbp
	ret
	addq $8, %rsp

	movq %rbp, %rsp
	pop %rbp
	ret

