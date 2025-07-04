.section .data
_galloc_array_0: .zero 16
arr: .quad _galloc_array_0

.section .text
.global main
main:
	push %rbp
	movq %rsp, %rbp

	pushq $8
	movq arr(%rip), %rbx
	movq -8(%rbp), %rax
	movq %rax, (%rbx)
	pushq $10
	subq $8, %rsp
	pushq $8
	movq arr(%rip), %rax
	movq -32(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	addq %rbx, %rax
	movq %rax, -24(%rbp)
	movq -24(%rbp), %rbx
	movq -16(%rbp), %rax
	movq %rax, (%rbx)
	subq $8, %rsp
	movq arr(%rip), %rax
	pushq (%rax)
	subq $8, %rsp
	subq $8, %rsp
	pushq $8
	movq arr(%rip), %rax
	movq -64(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	addq %rbx, %rax
	movq %rax, -56(%rbp)
	movq -56(%rbp), %rax
	# tighten_stack
	addq $8, %rsp
	pushq (%rax)
	pushq $2
	movq -56(%rbp), %rax
	movq -64(%rbp), %rbx
	# tighten_stack
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -48(%rbp)
	movq -40(%rbp), %rax
	movq -48(%rbp), %rbx
	# tighten_stack
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -32(%rbp)
	subq $8, %rsp
	pushq $8
	movq arr(%rip), %rax
	movq -48(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	addq %rbx, %rax
	movq %rax, -40(%rbp)
	movq -40(%rbp), %rbx
	movq -32(%rbp), %rax
	movq %rax, (%rbx)
	subq $8, %rsp
	pushq $8
	movq arr(%rip), %rax
	movq -56(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	addq %rbx, %rax
	movq %rax, -48(%rbp)
	movq -48(%rbp), %rax
	# tighten_stack
	addq $8, %rsp
	pushq (%rax)
	movq -48(%rbp), %rax
	movq %rbp, %rsp
	pop %rbp
	ret
	# tighten_stack
	addq $48, %rsp

	movq %rbp, %rsp
	pop %rbp
	ret

