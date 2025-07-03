.global helper_function
helper_function:
	push %rbp
	movq %rsp, %rbp

	pushq $42
	movq -8(%rbp), %rax
	movq %rbp, %rsp
	pop %rbp
	ret
	# restore_rsp_scope
	addq $8, %rsp

	movq %rbp, %rsp
	pop %rbp
	ret

.global main
main:
	push %rbp
	movq %rsp, %rbp

	subq $8, %rsp
	call helper_function
	pushq %rax
	movq -16(%rbp), %rax
	movq %rax, -8(%rbp)
	# tighten_stack
	addq $8, %rsp
	subq $8, %rsp
	pushq $5
	movq -24(%rbp), %rax
	movq %rax, -16(%rbp)
	# tighten_stack
	addq $8, %rsp
	subq $8, %rsp
	movq -8(%rbp), %rax
	movq -16(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -24(%rbp)
	movq -24(%rbp), %rax
	movq %rbp, %rsp
	pop %rbp
	ret
	# restore_rsp_scope
	addq $24, %rsp

	movq %rbp, %rsp
	pop %rbp
	ret

