.global main
main:
	push %rbp
	movq %rsp, %rbp

	subq $8, %rsp
	pushq $1
	pushq $2
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
	pushq $5
	movq -8(%rbp), %rax
	movq %rbp, %rsp
	pop %rbp
	ret
	# restore_rsp_scope
	addq $8, %rsp
	jmp .L_end_0
.L_else_0:
.L_end_0:
	pushq $2
	pushq $3
	movq -16(%rbp), %rax
	pushq %rax
	movq -8(%rbp), %rax
	pushq %rax
	call f
	# tighten_stack
	addq $32, %rsp
	pushq %rax
	movq -8(%rbp), %rax
	movq %rbp, %rsp
	pop %rbp
	ret
	# restore_rsp_scope
	addq $8, %rsp

	movq %rbp, %rsp
	pop %rbp
	ret

