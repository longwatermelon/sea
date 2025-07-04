.section .data

.section .text
.global main
main:
	push %rbp
	movq %rsp, %rbp

	subq $8, %rsp
	pushq $2
	pushq $8
	movq -16(%rbp), %rax
	movq -24(%rbp), %rbx
	# tighten_stack
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -8(%rbp)
	movq -8(%rbp), %rax
	movq %rbp, %rsp
	pop %rbp
	ret
	# restore_rsp_scope
	addq $8, %rsp

	movq %rbp, %rsp
	pop %rbp
	ret

