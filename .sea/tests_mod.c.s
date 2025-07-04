.section .data

.section .text
.global main
main:
	push %rbp
	movq %rsp, %rbp

	subq $8, %rsp
	pushq $5
	pushq $2
	movq -16(%rbp), %rax
	movq -24(%rbp), %rbx
	# tighten_stack
	addq $16, %rsp
	cqto
	idivq %rbx
	movq %rdx, -8(%rbp)
	movq -8(%rbp), %rax
	movq %rbp, %rsp
	pop %rbp
	ret
	# tighten_stack
	addq $8, %rsp

	movq %rbp, %rsp
	pop %rbp
	ret

