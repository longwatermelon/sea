.section .data

.section .text
.global main
main:
	push %rbp
	movq %rsp, %rbp

	subq $8, %rsp
	subq $8, %rsp
	movq %rsp, %rax
	pushq %rax
	movq -24(%rbp), %rax
	movq %rax, -8(%rbp)
	# tighten_stack
	addq $8, %rsp
	subq $8, %rsp
	pushq $0
	movq -32(%rbp), %rax
	movq %rax, -24(%rbp)
	# tighten_stack
	addq $8, %rsp
.L_start_0:
	subq $8, %rsp
	pushq $1
	movq -24(%rbp), %rax
	movq -40(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	cmp %rbx, %rax
	setne %al
	movzbl %al, %eax
	movq %rax, -32(%rbp)
	movq -32(%rbp), %rax
	# tighten_stack
	addq $8, %rsp
	test %rax, %rax
	jz .L_end_0
	subq $8, %rsp
	pushq $1
	movq -24(%rbp), %rax
	movq -40(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	addq %rbx, %rax
	movq %rax, -32(%rbp)
	movq -32(%rbp), %rax
	movq %rax, -24(%rbp)
	# tighten_stack
	addq $8, %rsp
	jmp .L_start_0
.L_end_0:
	pushq $5
	movq -8(%rbp), %rbx
	movq -32(%rbp), %rax
	movq %rax, (%rbx)
	pushq $0
	movq -40(%rbp), %rax
	movq %rbp, %rsp
	pop %rbp
	ret
	# restore_rsp_scope
	addq $40, %rsp

	movq %rbp, %rsp
	pop %rbp
	ret

