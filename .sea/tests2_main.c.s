.section .data
buffer: .quad 0

.section .text
.global read_char
read_char:
	push %rbp
	movq %rsp, %rbp

	pushq $0
	pushq $0
	leaq buffer(%rip), %rax
	pushq %rax
	pushq %rax
	pushq $1
	movq -8(%rbp), %rax
	movq -16(%rbp), %rdi
	movq -32(%rbp), %rsi
	movq -40(%rbp), %rdx
	syscall
	# tighten_stack
	addq $16, %rsp
	movq buffer(%rip), %rax
	movq %rbp, %rsp
	pop %rbp
	ret
	# restore_rsp_scope
	addq $24, %rsp

	movq %rbp, %rsp
	pop %rbp
	ret

.global print_char
print_char:
	push %rbp
	movq %rsp, %rbp

	movq 16(%rbp), %rax
	movq %rax, buffer(%rip)
	pushq $1
	pushq $1
	leaq buffer(%rip), %rax
	pushq %rax
	pushq %rax
	pushq $1
	movq -8(%rbp), %rax
	movq -16(%rbp), %rdi
	movq -32(%rbp), %rsi
	movq -40(%rbp), %rdx
	syscall
	# tighten_stack
	addq $16, %rsp
	# restore_rsp_scope
	addq $24, %rsp

	movq %rbp, %rsp
	pop %rbp
	ret

.global main
main:
	push %rbp
	movq %rsp, %rbp

	subq $8, %rsp
	call read_char
	pushq %rax
	movq -16(%rbp), %rax
	movq %rax, -8(%rbp)
	# tighten_stack
	addq $8, %rsp
	movq -8(%rbp), %rax
	pushq %rax
	call print_char
	# tighten_stack
	addq $8, %rsp
	pushq %rax
	# tighten_stack
	addq $8, %rsp
	pushq $10
	movq -16(%rbp), %rax
	pushq %rax
	call print_char
	# tighten_stack
	addq $16, %rsp
	pushq %rax
	# tighten_stack
	addq $8, %rsp
	movq -8(%rbp), %rax
	movq %rbp, %rsp
	pop %rbp
	ret
	# restore_rsp_scope
	addq $8, %rsp

	movq %rbp, %rsp
	pop %rbp
	ret

