.section .data

.section .text
.global f
f:
	push %rbp
	movq %rsp, %rbp

	subq $8, %rsp
	subq $8, %rsp
	subq $8, %rsp
	pushq $2
	movq -32(%rbp), %rax
	movq 16(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	imulq %rbx, %rax
	movq %rax, -24(%rbp)
	subq $8, %rsp
	pushq $3
	movq -40(%rbp), %rax
	movq 24(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	imulq %rbx, %rax
	movq %rax, -32(%rbp)
	movq -24(%rbp), %rax
	movq -32(%rbp), %rbx
	# tighten_stack
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %rax
	movq %rax, -8(%rbp)
	# tighten_stack
	addq $8, %rsp
	subq $8, %rsp
	pushq $5
	movq -8(%rbp), %rax
	movq -24(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	addq %rbx, %rax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %rax
	movq %rbp, %rsp
	pop %rbp
	ret

	movq %rbp, %rsp
	pop %rbp
	ret

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
	pushq $2
	movq -24(%rbp), %rax
	movq %rax, -16(%rbp)
	# tighten_stack
	addq $8, %rsp
	subq $8, %rsp
	pushq $1
	movq -16(%rbp), %rax
	pushq %rax
	movq -32(%rbp), %rax
	pushq %rax
	call f
	# tighten_stack
	addq $24, %rsp
	pushq %rax
	pushq $1
	pushq $1
	movq -48(%rbp), %rax
	pushq %rax
	movq -40(%rbp), %rax
	pushq %rax
	call f
	# tighten_stack
	addq $32, %rsp
	pushq %rax
	movq -40(%rbp), %rax
	pushq %rax
	movq -8(%rbp), %rax
	pushq %rax
	call f
	# tighten_stack
	addq $24, %rsp
	pushq %rax
	movq -40(%rbp), %rax
	pushq %rax
	movq -32(%rbp), %rax
	pushq %rax
	call f
	# tighten_stack
	addq $32, %rsp
	pushq %rax
	movq -32(%rbp), %rax
	movq %rax, -24(%rbp)
	# tighten_stack
	addq $8, %rsp
	subq $8, %rsp
	pushq $1
	pushq $2
	movq -48(%rbp), %rax
	pushq %rax
	movq -40(%rbp), %rax
	pushq %rax
	call f
	# tighten_stack
	addq $32, %rsp
	pushq %rax
	movq -24(%rbp), %rax
	movq -40(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	addq %rbx, %rax
	movq %rax, -32(%rbp)
	movq -32(%rbp), %rax
	movq %rbp, %rsp
	pop %rbp
	ret

	movq %rbp, %rsp
	pop %rbp
	ret

