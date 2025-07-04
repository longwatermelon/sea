.section .data

.section .text
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
	pushq $10
	movq -8(%rbp), %rbx
	movq -48(%rbp), %rax
	movq %rax, (%rbx)
	pushq $20
	subq $8, %rsp
	subq $8, %rsp
	pushq $1
	pushq $8
	movq -80(%rbp), %rax
	movq -88(%rbp), %rbx
	# tighten_stack
	addq $16, %rsp
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
	pushq $30
	subq $8, %rsp
	subq $8, %rsp
	pushq $2
	pushq $8
	movq -96(%rbp), %rax
	movq -104(%rbp), %rbx
	# tighten_stack
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -88(%rbp)
	movq -8(%rbp), %rax
	movq -88(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	addq %rbx, %rax
	movq %rax, -80(%rbp)
	movq -80(%rbp), %rbx
	movq -72(%rbp), %rax
	movq %rax, (%rbx)
	pushq $40
	subq $8, %rsp
	subq $8, %rsp
	pushq $3
	pushq $8
	movq -112(%rbp), %rax
	movq -120(%rbp), %rbx
	# tighten_stack
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -104(%rbp)
	movq -8(%rbp), %rax
	movq -104(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	addq %rbx, %rax
	movq %rax, -96(%rbp)
	movq -96(%rbp), %rbx
	movq -88(%rbp), %rax
	movq %rax, (%rbx)
	subq $8, %rsp
	subq $8, %rsp
	pushq $2
	pushq $8
	movq -120(%rbp), %rax
	movq -128(%rbp), %rbx
	# tighten_stack
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -112(%rbp)
	movq -8(%rbp), %rax
	movq -112(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	addq %rbx, %rax
	movq %rax, -104(%rbp)
	movq -104(%rbp), %rax
	# tighten_stack
	addq $8, %rsp
	pushq (%rax)
	movq -104(%rbp), %rax
	movq %rbp, %rsp
	pop %rbp
	ret

	movq %rbp, %rsp
	pop %rbp
	ret

