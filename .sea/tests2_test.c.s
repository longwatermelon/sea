.global f
f:
	push %rbp
	movq %rsp, %rbp

	subq $8, %rsp
	pushq $4
	pushq $4
	movq -16(%rbp), %rax
	movq -24(%rbp), %rbx
	# tighten_stack
	addq $16, %rsp
	cmp %rbx, %rax
	sete %al
	movzbl %al, %eax
	movq %rax, -8(%rbp)
	movq -8(%rbp), %rax
	# tighten_stack
	addq $8, %rsp
	test %rax, %rax
	jz .L_else_1
	pushq $90
	movq -8(%rbp), %rax
	movq %rbp, %rsp
	pop %rbp
	ret
	# restore_rsp_scope
	addq $8, %rsp
	jmp .L_end_1
.L_else_1:
.L_end_1:
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

