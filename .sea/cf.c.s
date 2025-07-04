.section .data
buffer: .quad 0
n: .quad 0
k: .quad 0
_galloc_array_0: .zero 808
a: .quad _galloc_array_0

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

.global read_skip
read_skip:
	push %rbp
	movq %rsp, %rbp

	call read_char
	pushq %rax
	# tighten_stack
	addq $8, %rsp

	movq %rbp, %rsp
	pop %rbp
	ret

.global read_int
read_int:
	push %rbp
	movq %rsp, %rbp

	subq $8, %rsp
	call read_char
	pushq %rax
	movq -16(%rbp), %rax
	movq %rax, -8(%rbp)
	# tighten_stack
	addq $8, %rsp
	subq $8, %rsp
	pushq $0
	movq -24(%rbp), %rax
	movq %rax, -16(%rbp)
	# tighten_stack
	addq $8, %rsp
.L_start_0:
	subq $8, %rsp
	subq $8, %rsp
	pushq $10
	movq -8(%rbp), %rax
	movq -40(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	cmp %rbx, %rax
	setne %al
	movzbl %al, %eax
	movq %rax, -32(%rbp)
	subq $8, %rsp
	pushq $32
	movq -8(%rbp), %rax
	movq -48(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	cmp %rbx, %rax
	setne %al
	movzbl %al, %eax
	movq %rax, -40(%rbp)
	movq -32(%rbp), %rax
	movq -40(%rbp), %rbx
	# tighten_stack
	addq $16, %rsp
	and %rbx, %rax
	movq %rax, -24(%rbp)
	movq -24(%rbp), %rax
	# tighten_stack
	addq $8, %rsp
	test %rax, %rax
	jz .L_end_0
	subq $8, %rsp
	subq $8, %rsp
	subq $8, %rsp
	pushq $10
	movq -16(%rbp), %rax
	movq -48(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	imulq %rbx, %rax
	movq %rax, -40(%rbp)
	movq -40(%rbp), %rax
	movq -8(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	addq %rbx, %rax
	movq %rax, -32(%rbp)
	pushq $48
	movq -32(%rbp), %rax
	movq -40(%rbp), %rbx
	# tighten_stack
	addq $16, %rsp
	subq %rbx, %rax
	movq %rax, -24(%rbp)
	movq -24(%rbp), %rax
	movq %rax, -16(%rbp)
	# tighten_stack
	addq $8, %rsp
	call read_char
	pushq %rax
	movq -24(%rbp), %rax
	movq %rax, -8(%rbp)
	# tighten_stack
	addq $8, %rsp
	jmp .L_start_0
.L_end_0:
	movq -16(%rbp), %rax
	movq %rbp, %rsp
	pop %rbp
	ret
	# restore_rsp_scope
	addq $16, %rsp

	movq %rbp, %rsp
	pop %rbp
	ret

.global print_int
print_int:
	push %rbp
	movq %rsp, %rbp

	subq $8, %rsp
	pushq $0
	movq 16(%rbp), %rax
	movq -16(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	cmp %rbx, %rax
	sete %al
	movzbl %al, %eax
	movq %rax, -8(%rbp)
	movq -8(%rbp), %rax
	# tighten_stack
	addq $8, %rsp
	test %rax, %rax
	jz .L_else_1
	pushq $48
	movq -8(%rbp), %rax
	pushq %rax
	call print_char
	# tighten_stack
	addq $16, %rsp
	pushq %rax
	# tighten_stack
	addq $8, %rsp
	pushq $0
	movq -8(%rbp), %rax
	movq %rbp, %rsp
	pop %rbp
	ret
	# restore_rsp_scope
	addq $8, %rsp
	jmp .L_end_1
.L_else_1:
.L_end_1:
	subq $8, %rsp
	subq $160, %rsp
	movq %rsp, %rax
	pushq %rax
	movq -176(%rbp), %rax
	movq %rax, -8(%rbp)
	# tighten_stack
	addq $8, %rsp
	subq $8, %rsp
	pushq $0
	movq -184(%rbp), %rax
	movq %rax, -176(%rbp)
	# tighten_stack
	addq $8, %rsp
.L_start_2:
	subq $8, %rsp
	pushq $0
	movq 16(%rbp), %rax
	movq -192(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	cmp %rbx, %rax
	setne %al
	movzbl %al, %eax
	movq %rax, -184(%rbp)
	movq -184(%rbp), %rax
	# tighten_stack
	addq $8, %rsp
	test %rax, %rax
	jz .L_end_2
	subq $8, %rsp
	subq $8, %rsp
	pushq $10
	movq 16(%rbp), %rax
	movq -200(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	cqto
	idivq %rbx
	movq %rdx, -192(%rbp)
	movq -192(%rbp), %rax
	movq %rax, -184(%rbp)
	# tighten_stack
	addq $8, %rsp
	subq $8, %rsp
	pushq $10
	movq 16(%rbp), %rax
	movq -200(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	cqto
	idivq %rbx
	movq %rax, -192(%rbp)
	movq -192(%rbp), %rax
	movq %rax, 16(%rbp)
	# tighten_stack
	addq $8, %rsp
	subq $8, %rsp
	pushq $48
	movq -184(%rbp), %rax
	movq -200(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	addq %rbx, %rax
	movq %rax, -192(%rbp)
	subq $8, %rsp
	subq $8, %rsp
	pushq $8
	movq -176(%rbp), %rax
	movq -216(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	imulq %rbx, %rax
	movq %rax, -208(%rbp)
	movq -8(%rbp), %rax
	movq -208(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	addq %rbx, %rax
	movq %rax, -200(%rbp)
	movq -200(%rbp), %rbx
	movq -192(%rbp), %rax
	movq %rax, (%rbx)
	subq $8, %rsp
	pushq $1
	movq -176(%rbp), %rax
	movq -216(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	addq %rbx, %rax
	movq %rax, -208(%rbp)
	movq -208(%rbp), %rax
	movq %rax, -176(%rbp)
	# tighten_stack
	addq $8, %rsp
	# restore_rsp_scope
	addq $24, %rsp
	jmp .L_start_2
.L_end_2:
.L_start_3:
	subq $8, %rsp
	pushq $0
	movq -176(%rbp), %rax
	movq -192(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	cmp %rbx, %rax
	setne %al
	movzbl %al, %eax
	movq %rax, -184(%rbp)
	movq -184(%rbp), %rax
	# tighten_stack
	addq $8, %rsp
	test %rax, %rax
	jz .L_end_3
	subq $8, %rsp
	pushq $1
	movq -176(%rbp), %rax
	movq -192(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	subq %rbx, %rax
	movq %rax, -184(%rbp)
	movq -184(%rbp), %rax
	movq %rax, -176(%rbp)
	# tighten_stack
	addq $8, %rsp
	subq $8, %rsp
	subq $8, %rsp
	pushq $8
	movq -176(%rbp), %rax
	movq -200(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	imulq %rbx, %rax
	movq %rax, -192(%rbp)
	movq -8(%rbp), %rax
	movq -192(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	addq %rbx, %rax
	movq %rax, -184(%rbp)
	movq -184(%rbp), %rax
	# tighten_stack
	addq $8, %rsp
	pushq (%rax)
	movq -184(%rbp), %rax
	pushq %rax
	call print_char
	# tighten_stack
	addq $16, %rsp
	pushq %rax
	# tighten_stack
	addq $8, %rsp
	jmp .L_start_3
.L_end_3:
	# restore_rsp_scope
	addq $176, %rsp

	movq %rbp, %rsp
	pop %rbp
	ret

.global solve
solve:
	push %rbp
	movq %rsp, %rbp

	subq $8, %rsp
	pushq $1
	movq -16(%rbp), %rax
	movq %rax, -8(%rbp)
	# tighten_stack
	addq $8, %rsp
.L_start_4:
	subq $8, %rsp
	subq $8, %rsp
	movq -8(%rbp), %rax
	movq n(%rip), %rbx
	cmp %rbx, %rax
	setne %al
	movzbl %al, %eax
	movq %rax, -24(%rbp)
	subq $8, %rsp
	pushq $0
	movq k(%rip), %rax
	movq -40(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	cmp %rbx, %rax
	setne %al
	movzbl %al, %eax
	movq %rax, -32(%rbp)
	movq -24(%rbp), %rax
	movq -32(%rbp), %rbx
	# tighten_stack
	addq $16, %rsp
	and %rbx, %rax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %rax
	# tighten_stack
	addq $8, %rsp
	test %rax, %rax
	jz .L_end_4
.L_start_5:
	subq $8, %rsp
	subq $8, %rsp
	pushq $0
	movq k(%rip), %rax
	movq -32(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	cmp %rbx, %rax
	setne %al
	movzbl %al, %eax
	movq %rax, -24(%rbp)
	subq $8, %rsp
	subq $8, %rsp
	subq $8, %rsp
	pushq $8
	movq -8(%rbp), %rax
	movq -56(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	imulq %rbx, %rax
	movq %rax, -48(%rbp)
	movq a(%rip), %rax
	movq -48(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	addq %rbx, %rax
	movq %rax, -40(%rbp)
	movq -40(%rbp), %rax
	# tighten_stack
	addq $8, %rsp
	pushq (%rax)
	pushq $0
	movq -40(%rbp), %rax
	movq -48(%rbp), %rbx
	# tighten_stack
	addq $16, %rsp
	cmp %rbx, %rax
	setne %al
	movzbl %al, %eax
	movq %rax, -32(%rbp)
	movq -24(%rbp), %rax
	movq -32(%rbp), %rbx
	# tighten_stack
	addq $16, %rsp
	and %rbx, %rax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %rax
	# tighten_stack
	addq $8, %rsp
	test %rax, %rax
	jz .L_end_5
	subq $8, %rsp
	subq $8, %rsp
	subq $8, %rsp
	pushq $8
	movq -8(%rbp), %rax
	movq -40(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	imulq %rbx, %rax
	movq %rax, -32(%rbp)
	movq a(%rip), %rax
	movq -32(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	addq %rbx, %rax
	movq %rax, -24(%rbp)
	movq -24(%rbp), %rax
	# tighten_stack
	addq $8, %rsp
	pushq (%rax)
	pushq $1
	movq -24(%rbp), %rax
	movq -32(%rbp), %rbx
	# tighten_stack
	addq $16, %rsp
	subq %rbx, %rax
	movq %rax, -16(%rbp)
	subq $8, %rsp
	subq $8, %rsp
	pushq $8
	movq -8(%rbp), %rax
	movq -40(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	imulq %rbx, %rax
	movq %rax, -32(%rbp)
	movq a(%rip), %rax
	movq -32(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	addq %rbx, %rax
	movq %rax, -24(%rbp)
	movq -24(%rbp), %rbx
	movq -16(%rbp), %rax
	movq %rax, (%rbx)
	subq $8, %rsp
	subq $8, %rsp
	subq $8, %rsp
	pushq $8
	movq n(%rip), %rax
	movq -56(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	imulq %rbx, %rax
	movq %rax, -48(%rbp)
	movq a(%rip), %rax
	movq -48(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	addq %rbx, %rax
	movq %rax, -40(%rbp)
	movq -40(%rbp), %rax
	# tighten_stack
	addq $8, %rsp
	pushq (%rax)
	pushq $1
	movq -40(%rbp), %rax
	movq -48(%rbp), %rbx
	# tighten_stack
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -32(%rbp)
	subq $8, %rsp
	subq $8, %rsp
	pushq $8
	movq n(%rip), %rax
	movq -56(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	imulq %rbx, %rax
	movq %rax, -48(%rbp)
	movq a(%rip), %rax
	movq -48(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	addq %rbx, %rax
	movq %rax, -40(%rbp)
	movq -40(%rbp), %rbx
	movq -32(%rbp), %rax
	movq %rax, (%rbx)
	subq $8, %rsp
	pushq $1
	movq k(%rip), %rax
	movq -56(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	subq %rbx, %rax
	movq %rax, -48(%rbp)
	movq -48(%rbp), %rax
	movq %rax, k(%rip)
	# tighten_stack
	addq $8, %rsp
	# restore_rsp_scope
	addq $32, %rsp
	jmp .L_start_5
.L_end_5:
	subq $8, %rsp
	pushq $1
	movq -8(%rbp), %rax
	movq -24(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	addq %rbx, %rax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %rax
	movq %rax, -8(%rbp)
	# tighten_stack
	addq $8, %rsp
	jmp .L_start_4
.L_end_4:
	movq n(%rip), %rax
	pushq %rax
	call print_int
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
	pushq $1
	movq -16(%rbp), %rax
	movq %rax, -8(%rbp)
	# tighten_stack
	addq $8, %rsp
.L_start_6:
	subq $8, %rsp
	movq -8(%rbp), %rax
	movq n(%rip), %rbx
	cmp %rbx, %rax
	setne %al
	movzbl %al, %eax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %rax
	# tighten_stack
	addq $8, %rsp
	test %rax, %rax
	jz .L_end_6
	subq $8, %rsp
	subq $8, %rsp
	pushq $8
	movq -8(%rbp), %rax
	movq -32(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	imulq %rbx, %rax
	movq %rax, -24(%rbp)
	movq a(%rip), %rax
	movq -24(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	addq %rbx, %rax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %rax
	# tighten_stack
	addq $8, %rsp
	pushq (%rax)
	movq -16(%rbp), %rax
	pushq %rax
	call print_int
	# tighten_stack
	addq $16, %rsp
	pushq %rax
	# tighten_stack
	addq $8, %rsp
	pushq $32
	movq -16(%rbp), %rax
	pushq %rax
	call print_char
	# tighten_stack
	addq $16, %rsp
	pushq %rax
	# tighten_stack
	addq $8, %rsp
	subq $8, %rsp
	pushq $1
	movq -8(%rbp), %rax
	movq -24(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	addq %rbx, %rax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %rax
	movq %rax, -8(%rbp)
	# tighten_stack
	addq $8, %rsp
	jmp .L_start_6
.L_end_6:
	subq $8, %rsp
	subq $8, %rsp
	pushq $8
	movq n(%rip), %rax
	movq -32(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	imulq %rbx, %rax
	movq %rax, -24(%rbp)
	movq a(%rip), %rax
	movq -24(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	addq %rbx, %rax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %rax
	# tighten_stack
	addq $8, %rsp
	pushq (%rax)
	movq -16(%rbp), %rax
	pushq %rax
	call print_int
	# tighten_stack
	addq $16, %rsp
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
	# restore_rsp_scope
	addq $8, %rsp

	movq %rbp, %rsp
	pop %rbp
	ret

.global main
main:
	push %rbp
	movq %rsp, %rbp

	subq $8, %rsp
	call read_int
	pushq %rax
	movq -16(%rbp), %rax
	movq %rax, -8(%rbp)
	# tighten_stack
	addq $8, %rsp
.L_start_7:
	subq $8, %rsp
	pushq $0
	movq -8(%rbp), %rax
	movq -24(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	cmp %rbx, %rax
	setne %al
	movzbl %al, %eax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %rax
	# tighten_stack
	addq $8, %rsp
	test %rax, %rax
	jz .L_end_7
	subq $8, %rsp
	pushq $1
	movq -8(%rbp), %rax
	movq -24(%rbp), %rbx
	# tighten_stack
	addq $8, %rsp
	subq %rbx, %rax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %rax
	movq %rax, -8(%rbp)
	# tighten_stack
	addq $8, %rsp
	call read_int
	pushq %rax
	movq -16(%rbp), %rax
	movq %rax, n(%rip)
	# tighten_stack
	addq $8, %rsp
	call read_int
	pushq %rax
	movq -16(%rbp), %rax
	movq %rax, k(%rip)
	# tighten_stack
	addq $8, %rsp
	subq $8, %rsp
	pushq $1
	movq -24(%rbp), %rax
	movq %rax, -16(%rbp)
	# tighten_stack
	addq $8, %rsp
.L_start_8:
	subq $8, %rsp
	movq -16(%rbp), %rax
	movq n(%rip), %rbx
	cmp %rbx, %rax
	setne %al
	movzbl %al, %eax
	movq %rax, -24(%rbp)
	movq -24(%rbp), %rax
	# tighten_stack
	addq $8, %rsp
	test %rax, %rax
	jz .L_end_8
	call read_int
	pushq %rax
	# restore_rsp_scope
	addq $8, %rsp
	jmp .L_start_8
.L_end_8:
	# tighten_stack
	addq $-8, %rsp
	call solve
	pushq %rax
	# tighten_stack
	addq $8, %rsp
	# restore_rsp_scope
	addq $16, %rsp
	jmp .L_start_7
.L_end_7:
	# restore_rsp_scope
	addq $8, %rsp

	movq %rbp, %rsp
	pop %rbp
	ret

