.section .data

.section .text
.global f
f:
	push %rbp
	movq %rsp, %rbp

	movq 16(%rbp), %rax
	pushq (%rax)
	movq -8(%rbp), %rax
	movq %rbp, %rsp
	pop %rbp
	ret
	# tighten_stack
	addq $8, %rsp

	movq %rbp, %rsp
	pop %rbp
	ret

.global main
main:
	push %rbp
	movq %rsp, %rbp

	subq $8, %rsp
	pushq $5
	movq -16(%rbp), %rax
	movq %rax, -8(%rbp)
	# tighten_stack
	addq $8, %rsp
	subq $8, %rsp
	leaq -8(%rbp), %rax
	pushq %rax
	pushq %rax
	movq -32(%rbp), %rax
	movq %rax, -16(%rbp)
	# tighten_stack
	addq $8, %rsp
	subq $8, %rsp
	subq $8, %rsp
	pushq $1
	leaq -16(%rbp), %rax
	pushq %rax
	pushq %rax
	movq -64(%rbp), %rax
	pushq %rax
	call f
	# tighten_stack
	addq $16, %rsp
	pushq %rax
	movq -64(%rbp), %rax
	# tighten_stack
	addq $8, %rsp
	pushq (%rax)
	movq -48(%rbp), %rax
	movq -64(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	addq %rbx, %rax
	movq %rax, -40(%rbp)
	pushq $1
	movq -40(%rbp), %rax
	movq -64(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	addq %rbx, %rax
	movq %rax, -32(%rbp)
	movq -32(%rbp), %rax
	movq %rbp, %rsp
	pop %rbp
	ret
	# tighten_stack
	addq $56, %rsp

	movq %rbp, %rsp
	pop %rbp
	ret

