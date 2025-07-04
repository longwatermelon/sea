.section .data
var: .quad 4

.section .text
.global f
f:
	push %rbp
	movq %rsp, %rbp

	subq $8, %rsp
	pushq $2
	movq 16(%rbp), %rax
	pushq (%rax)
	movq -16(%rbp), %rax
	movq -24(%rbp), %rbx
	# tighten_stack
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -8(%rbp)
	movq 16(%rbp), %rbx
	movq -8(%rbp), %rax
	movq %rax, (%rbx)

	movq %rbp, %rsp
	pop %rbp
	ret

.global main
main:
	push %rbp
	movq %rsp, %rbp

	subq $8, %rsp
	pushq $2
	movq -16(%rbp), %rax
	movq %rax, -8(%rbp)
	# tighten_stack
	addq $8, %rsp
	subq $8, %rsp
	leaq var(%rip), %rax
	pushq %rax
	pushq %rax
	movq -32(%rbp), %rax
	movq %rax, -16(%rbp)
	# tighten_stack
	addq $8, %rsp
	movq -16(%rbp), %rax
	pushq %rax
	movq -32(%rbp), %rax
	pushq %rax
	movq -40(%rbp), %rax
	pushq %rax
	movq -48(%rbp), %rax
	pushq %rax
	movq -56(%rbp), %rax
	pushq %rax
	movq -64(%rbp), %rax
	pushq %rax
	movq -72(%rbp), %rax
	pushq %rax
	call f
	# tighten_stack
	addq $16, %rsp
	pushq %rax
	# tighten_stack
	addq $8, %rsp
	subq $8, %rsp
	movq -8(%rbp), %rax
	movq var(%rip), %rbx
	addq %rbx, %rax
	movq %rax, -72(%rbp)
	movq -72(%rbp), %rax
	movq %rbp, %rsp
	pop %rbp
	ret

	movq %rbp, %rsp
	pop %rbp
	ret

