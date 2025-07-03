.section .data

.section .text
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
	jz .L_else_0
	pushq $90
	movq -8(%rbp), %rax
	movq %rbp, %rsp
	pop %rbp
	ret
	# restore_rsp_scope
	addq $8, %rsp
	jmp .L_end_0
.L_else_0:
	# tighten_stack
	addq $-8, %rsp
	# restore_rsp_scope
	addq $8, %rsp
.L_end_0:
	# tighten_stack
	addq $-8, %rsp
	subq $8, %rsp
	movq 16(%rbp), %rax
	movq 24(%rbp), %rbx
	imulq %rbx, %rax
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

