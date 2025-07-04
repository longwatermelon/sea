
.global main
main:
	push %rbp
	movq %rsp, %rbp

	subq $8, %rsp
	subq $32, %rsp
	movq %rsp, %rax
	pushq %rax
	movq -48(%rbp), %rax
	movq %rax, -8(%rbp)
	# tighten_stack
	addq $8, %rsp
	subq $8, %rsp
	pushq $0
	movq -56(%rbp), %rax
	movq %rax, -48(%rbp)
	# tighten_stack
	addq $8, %rsp
.L_start_3:
	subq $8, %rsp
	pushq $3
	movq -48(%rbp), %rax
	movq -64(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	cmp %rbx, %rax
	setne %al
	movzbl %al, %eax
	movq %rax, -56(%rbp)
	movq -56(%rbp), %rax
	# tighten_stack
	addq $8, %rsp
	test %rax, %rax
	jz .L_end_3
	call read_int
	pushq %rax
	subq $8, %rsp
	subq $8, %rsp
	pushq $8
	movq -48(%rbp), %rax
	movq -80(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	imulq %rbx, %rax
	movq %rax, -72(%rbp)
	movq -8(%rbp), %rax
	movq -72(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	addq %rbx, %rax
	movq %rax, -64(%rbp)
	movq -64(%rbp), %rbx
	movq -56(%rbp), %rax
	movq %rax, (%rbx)
	subq $8, %rsp
	pushq $1
	movq -48(%rbp), %rax
	movq -80(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	addq %rbx, %rax
	movq %rax, -72(%rbp)
	movq -72(%rbp), %rax
	movq %rax, -48(%rbp)
	# tighten_stack
	addq $8, %rsp
	# restore_rsp_scope
	addq $16, %rsp
	jmp .L_start_3
.L_end_3:
	subq $8, %rsp
	call read_int
	pushq %rax
	movq -64(%rbp), %rax
	movq %rax, -56(%rbp)
	# tighten_stack
	addq $8, %rsp
	subq $8, %rsp
	subq $8, %rsp
	subq $8, %rsp
	movq -8(%rbp), %rax
	pushq (%rax)
	subq $8, %rsp
	pushq $8
	movq -8(%rbp), %rax
	movq -104(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	addq %rbx, %rax
	movq %rax, -96(%rbp)
	movq -96(%rbp), %rax
	# tighten_stack
	addq $8, %rsp
	pushq (%rax)
	movq -88(%rbp), %rax
	movq -96(%rbp), %rbx
	# tighten_stack
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -80(%rbp)
	subq $8, %rsp
	pushq $16
	movq -8(%rbp), %rax
	movq -96(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	addq %rbx, %rax
	movq %rax, -88(%rbp)
	movq -88(%rbp), %rax
	# tighten_stack
	addq $8, %rsp
	pushq (%rax)
	movq -80(%rbp), %rax
	movq -88(%rbp), %rbx
	# tighten_stack
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -72(%rbp)
	subq $8, %rsp
	pushq $24
	movq -8(%rbp), %rax
	movq -88(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	addq %rbx, %rax
	movq %rax, -80(%rbp)
	movq -80(%rbp), %rax
	# tighten_stack
	addq $8, %rsp
	pushq (%rax)
	movq -72(%rbp), %rax
	movq -80(%rbp), %rbx
	# tighten_stack
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -64(%rbp)
	movq -64(%rbp), %rax
	pushq %rax
	call print_int
	# tighten_stack
	addq $16, %rsp
	pushq %rax
	# tighten_stack
	addq $8, %rsp
	pushq $0
	movq -64(%rbp), %rax
	movq %rbp, %rsp
	pop %rbp
	ret
	# restore_rsp_scope
	addq $64, %rsp

	movq %rbp, %rsp
	pop %rbp
	ret
