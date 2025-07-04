.section .data

.section .text
.global main
main:
	push %rbp
	movq %rsp, %rbp

	subq $8, %rsp
	pushq $5
	movq -16(%rbp), %rax
	movq %rax, -8(%rbp)
	# tighten_stack
	addq $8, %rsp
	subq $8, %rsp
	subq $8, %rsp
	pushq $1
	movq -8(%rbp), %rax
	movq -32(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	addq %rbx, %rax
	movq %rax, -24(%rbp)
	movq -24(%rbp), %rax
	movq %rax, -16(%rbp)
	# tighten_stack
	addq $8, %rsp
	subq $8, %rsp
	subq $8, %rsp
	subq $8, %rsp
	subq $8, %rsp
	subq $8, %rsp
	subq $8, %rsp
	subq $8, %rsp
	subq $8, %rsp
	subq $8, %rsp
	subq $8, %rsp
	subq $8, %rsp
	pushq $2
	movq -112(%rbp), %rax
	movq -16(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	imulq %rbx, %rax
	movq %rax, -104(%rbp)
	movq -8(%rbp), %rax
	movq -104(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	addq %rbx, %rax
	movq %rax, -96(%rbp)
	pushq $1
	movq -96(%rbp), %rax
	movq -104(%rbp), %rbx
	# tighten_stack
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -88(%rbp)
	movq -88(%rbp), %rax
	movq -8(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	subq %rbx, %rax
	movq %rax, -80(%rbp)
	movq -80(%rbp), %rax
	movq -8(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	addq %rbx, %rax
	movq %rax, -72(%rbp)
	movq -72(%rbp), %rax
	movq -8(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	subq %rbx, %rax
	movq %rax, -64(%rbp)
	subq $8, %rsp
	subq $8, %rsp
	subq $8, %rsp
	pushq $2
	movq -8(%rbp), %rax
	movq -96(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	imulq %rbx, %rax
	movq %rax, -88(%rbp)
	subq $8, %rsp
	subq $8, %rsp
	pushq $3
	pushq $1
	movq -112(%rbp), %rax
	movq -120(%rbp), %rbx
	# tighten_stack
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -104(%rbp)
	movq -104(%rbp), %rax
	movq -8(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	imulq %rbx, %rax
	movq %rax, -96(%rbp)
	movq -88(%rbp), %rax
	movq -96(%rbp), %rbx
	# tighten_stack
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -80(%rbp)
	pushq $5
	movq -80(%rbp), %rax
	movq -88(%rbp), %rbx
	# tighten_stack
	addq $16, %rsp
	subq %rbx, %rax
	movq %rax, -72(%rbp)
	movq -64(%rbp), %rax
	movq -72(%rbp), %rbx
	# tighten_stack
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -56(%rbp)
	pushq $5
	movq -56(%rbp), %rax
	movq -64(%rbp), %rbx
	# tighten_stack
	addq $16, %rsp
	subq %rbx, %rax
	movq %rax, -48(%rbp)
	pushq $2
	movq -48(%rbp), %rax
	movq -56(%rbp), %rbx
	# tighten_stack
	addq $16, %rsp
	subq %rbx, %rax
	movq %rax, -40(%rbp)
	movq -40(%rbp), %rax
	movq -16(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	addq %rbx, %rax
	movq %rax, -32(%rbp)
	subq $8, %rsp
	pushq $2
	subq $8, %rsp
	subq $8, %rsp
	pushq $3
	movq -72(%rbp), %rax
	movq -16(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	imulq %rbx, %rax
	movq %rax, -64(%rbp)
	movq -16(%rbp), %rax
	movq -64(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	addq %rbx, %rax
	movq %rax, -56(%rbp)
	movq -48(%rbp), %rax
	movq -56(%rbp), %rbx
	# tighten_stack
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -40(%rbp)
	movq -32(%rbp), %rax
	movq -40(%rbp), %rbx
	# tighten_stack
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -24(%rbp)
	movq -24(%rbp), %rax
	movq %rax, -16(%rbp)
	# tighten_stack
	addq $8, %rsp
	subq $8, %rsp
	pushq $1
	movq -32(%rbp), %rax
	movq -16(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	addq %rbx, %rax
	movq %rax, -24(%rbp)
	movq -24(%rbp), %rax
	movq %rbp, %rsp
	pop %rbp
	ret
	# tighten_stack
	addq $24, %rsp

	movq %rbp, %rsp
	pop %rbp
	ret

