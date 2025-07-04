.section .data

.section .text
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
	movq -8(%rbp), %rax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %rax
	movq %rbp, %rsp
	pop %rbp
	ret
	# restore_rsp_scope
	addq $16, %rsp

	movq %rbp, %rsp
	pop %rbp
	ret

