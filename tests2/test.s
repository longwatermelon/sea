.global f
f:
	push %rbp
	movq %rsp, %rbp

	subq $8, %rsp
	movq 16(%rbp), %rax
	movq 24(%rbp), %rbx
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

