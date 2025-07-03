.global main
main:
	push %rbp
	movq %rsp, %rbp

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

