.section .data

.section .text
.global main
main:
	push %rbp
	movq %rsp, %rbp

	subq $8, %rsp
	pushq $1
	movq -16(%rbp), %rax
	movq %rax, -8(%rbp)
	# tighten_stack
	addq $8, %rsp
	subq $8, %rsp
	pushq $2
	movq -8(%rbp), %rax
	movq -24(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	addq %rbx, %rax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %rax
	movq %rbp, %rsp
	pop %rbp
	ret

	movq %rbp, %rsp
	pop %rbp
	ret

