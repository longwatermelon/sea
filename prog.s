.section .text
	.global _start

_start:
	call main
	movq %rax, %rdi
	movq $60, %rax
	syscall

main:
	push %rbp
	movq %rsp, %rbp
	sub $8, %rsp
	movq $4, 0(%rsp)
	movq 0(%rsp), %rax
	movq %rbp, %rsp
	pop %rbp
	ret
