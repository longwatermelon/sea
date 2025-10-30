asm(R"(
.section .data
READ_BUFFER_CAP: .quad 1048576
WRITE_BUFFER_CAP: .quad 32768
_galloc_array_0: .zero 1048576
input_buffer: .quad _galloc_array_0
input_index: .quad 0
_galloc_array_1: .zero 32768
output_buffer: .quad _galloc_array_1
output_index: .quad 0
n: .quad 0
m: .quad 0
_galloc_array_2: .zero 1600040
heights: .quad _galloc_array_2

.section .text
.global init_input
init_input:
	push %rbp
	movq %rsp, %rbp

	movq $0, %r10
	subq $16, %rsp
	movq %r10, -8(%rbp)
	movq $0, %r10
	movq %r10, -16(%rbp)
	movq -8(%rbp), %rax
	movq -16(%rbp), %rdi
	movq input_buffer(%rip), %rsi
	movq READ_BUFFER_CAP(%rip), %rdx
	syscall
	addq $16, %rsp

	movq %rbp, %rsp
	pop %rbp
	ret

.global flush_output
flush_output:
	push %rbp
	movq %rsp, %rbp

	subq $16, %rsp
	movq $0, %r10
	movq %r10, -16(%rbp)
	movq output_index(%rip), %rax
	movq -16(%rbp), %rbx
	cmp %rbx, %rax
	setg %al
	movzbl %al, %eax
	movq %rax, -8(%rbp)
	movq -8(%rbp), %r10
	addq $16, %rsp
	test %r10, %r10
	jz .L_else_0
	movq $1, %r10
	subq $16, %rsp
	movq %r10, -8(%rbp)
	movq $1, %r10
	movq %r10, -16(%rbp)
	movq -8(%rbp), %rax
	movq -16(%rbp), %rdi
	movq output_buffer(%rip), %rsi
	movq output_index(%rip), %rdx
	syscall
	addq $16, %rsp
	movq $0, %r10
	subq $16, %rsp
	movq %r10, -8(%rbp)
	movq -8(%rbp), %r10
	movq %r10, output_index(%rip)
	addq $16, %rsp
	jmp .L_end_0
.L_else_0:
.L_end_0:

	movq %rbp, %rsp
	pop %rbp
	ret

.global read_char
read_char:
	push %rbp
	movq %rsp, %rbp

	subq $16, %rsp
	movq input_index(%rip), %rax
	movq READ_BUFFER_CAP(%rip), %rbx
	cmp %rbx, %rax
	setge %al
	movzbl %al, %eax
	movq %rax, -8(%rbp)
	movq -8(%rbp), %r10
	addq $16, %rsp
	test %r10, %r10
	jz .L_else_1
	movq $0, %r10
	subq $16, %rsp
	movq %r10, -8(%rbp)
	movq -8(%rbp), %rax

	movq %rbp, %rsp
	pop %rbp
	ret

	addq $16, %rsp
	jmp .L_end_1
.L_else_1:
.L_end_1:
	subq $16, %rsp
	subq $16, %rsp
	movq $1, %r10
	movq %r10, -32(%rbp)
	movq input_index(%rip), %rax
	movq -32(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -24(%rbp)
	movq input_buffer(%rip), %rax
	movq -24(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %r10
	movb (%r10), %r11b
	movb %r11b, -9(%rbp)
	movq -9(%rbp), %r10
	movq %r10, -8(%rbp)
	movq $1, %r10
	subq $16, %rsp
	movq %r10, -24(%rbp)
	movq input_index(%rip), %rax
	movq -24(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %r10
	movq %r10, input_index(%rip)
	movq -8(%rbp), %rax

	movq %rbp, %rsp
	pop %rbp
	ret


	movq %rbp, %rsp
	pop %rbp
	ret

.global print_char
print_char:
	push %rbp
	movq %rsp, %rbp

	subq $16, %rsp
	movq $1, %r10
	subq $16, %rsp
	movq %r10, -24(%rbp)
	movq output_index(%rip), %rax
	movq -24(%rbp), %rbx
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -16(%rbp)
	movq output_buffer(%rip), %rax
	movq -16(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -8(%rbp)
	movq -8(%rbp), %r11
	movb 16(%rbp), %r10b
	movb %r10b, (%r11)
	addq $16, %rsp
	subq $16, %rsp
	movq $1, %r10
	movq %r10, -16(%rbp)
	movq output_index(%rip), %rax
	movq -16(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -8(%rbp)
	movq -8(%rbp), %r10
	movq %r10, output_index(%rip)
	addq $16, %rsp
	subq $16, %rsp
	movq output_index(%rip), %rax
	movq WRITE_BUFFER_CAP(%rip), %rbx
	cmp %rbx, %rax
	sete %al
	movzbl %al, %eax
	movq %rax, -8(%rbp)
	movq -8(%rbp), %r10
	addq $16, %rsp
	test %r10, %r10
	jz .L_else_2
	call flush_output
	jmp .L_end_2
.L_else_2:
.L_end_2:

	movq %rbp, %rsp
	pop %rbp
	ret

.global read_int
read_int:
	push %rbp
	movq %rsp, %rbp

	subq $16, %rsp
	call read_char
	subq $16, %rsp
	movq %rax, -24(%rbp)
	movq -24(%rbp), %r10
	movq %r10, -8(%rbp)
	addq $16, %rsp
	subq $16, %rsp
	movq $0, %r10
	movq %r10, -32(%rbp)
	movq -32(%rbp), %r10
	movq %r10, -24(%rbp)
.L_start_3:
	subq $16, %rsp
	movq $10, %r10
	movq %r10, -48(%rbp)
	movq -8(%rbp), %rax
	movq -48(%rbp), %rbx
	cmp %rbx, %rax
	sete %al
	movzbl %al, %eax
	movq %rax, -40(%rbp)
	movq $32, %r10
	subq $16, %rsp
	movq %r10, -56(%rbp)
	movq -8(%rbp), %rax
	movq -56(%rbp), %rbx
	addq $16, %rsp
	cmp %rbx, %rax
	sete %al
	movzbl %al, %eax
	movq %rax, -48(%rbp)
	movq -40(%rbp), %rax
	movq -48(%rbp), %rbx
	addq $16, %rsp
	or %rbx, %rax
	movq %rax, -32(%rbp)
	movq -32(%rbp), %r10
	test %r10, %r10
	jz .L_end_3
	call read_char
	subq $16, %rsp
	movq %rax, -40(%rbp)
	movq -40(%rbp), %r10
	movq %r10, -8(%rbp)
	addq $16, %rsp
	jmp .L_start_3
.L_end_3:
.L_start_4:
	subq $16, %rsp
	movq $10, %r10
	subq $16, %rsp
	movq %r10, -56(%rbp)
	movq -8(%rbp), %rax
	movq -56(%rbp), %rbx
	addq $16, %rsp
	cmp %rbx, %rax
	setne %al
	movzbl %al, %eax
	movq %rax, -48(%rbp)
	subq $16, %rsp
	movq $32, %r10
	movq %r10, -64(%rbp)
	movq -8(%rbp), %rax
	movq -64(%rbp), %rbx
	cmp %rbx, %rax
	setne %al
	movzbl %al, %eax
	movq %rax, -56(%rbp)
	movq -48(%rbp), %rax
	movq -56(%rbp), %rbx
	addq $16, %rsp
	and %rbx, %rax
	movq %rax, -40(%rbp)
	movq $0, %r10
	subq $16, %rsp
	movq %r10, -56(%rbp)
	movq -8(%rbp), %rax
	movq -56(%rbp), %rbx
	addq $16, %rsp
	cmp %rbx, %rax
	setne %al
	movzbl %al, %eax
	movq %rax, -48(%rbp)
	movq -40(%rbp), %rax
	movq -48(%rbp), %rbx
	addq $16, %rsp
	and %rbx, %rax
	movq %rax, -32(%rbp)
	movq -32(%rbp), %r10
	test %r10, %r10
	jz .L_end_4
	subq $16, %rsp
	movq $10, %r10
	subq $16, %rsp
	movq %r10, -56(%rbp)
	movq -24(%rbp), %rax
	movq -56(%rbp), %rbx
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -48(%rbp)
	movq -48(%rbp), %rax
	movq -8(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -40(%rbp)
	movq $48, %r10
	movq %r10, -48(%rbp)
	movq -40(%rbp), %rax
	movq -48(%rbp), %rbx
	addq $16, %rsp
	subq %rbx, %rax
	movq %rax, -32(%rbp)
	movq -32(%rbp), %r10
	movq %r10, -24(%rbp)
	call read_char
	subq $16, %rsp
	movq %rax, -40(%rbp)
	movq -40(%rbp), %r10
	movq %r10, -8(%rbp)
	addq $16, %rsp
	jmp .L_start_4
.L_end_4:
	movq -24(%rbp), %rax

	movq %rbp, %rsp
	pop %rbp
	ret


	movq %rbp, %rsp
	pop %rbp
	ret

.global print_int
print_int:
	push %rbp
	movq %rsp, %rbp

	subq $16, %rsp
	movq $0, %r10
	movq %r10, -16(%rbp)
	movq 16(%rbp), %rax
	movq -16(%rbp), %rbx
	cmp %rbx, %rax
	sete %al
	movzbl %al, %eax
	movq %rax, -8(%rbp)
	movq -8(%rbp), %r10
	addq $16, %rsp
	test %r10, %r10
	jz .L_else_5
	movq $48, %r10
	subq $16, %rsp
	movq %r10, -8(%rbp)
	movq -8(%rbp), %r10
	movq %r10, -16(%rbp)
	call print_char
	addq $16, %rsp
	movq $0, %r10
	subq $16, %rsp
	movq %r10, -8(%rbp)
	movq -8(%rbp), %rax

	movq %rbp, %rsp
	pop %rbp
	ret

	addq $16, %rsp
	jmp .L_end_5
.L_else_5:
.L_end_5:
	subq $16, %rsp
	subq $16, %rsp
	subq $16, %rsp
	subq $16, %rsp
	subq $16, %rsp
	subq $16, %rsp
	subq $16, %rsp
	subq $16, %rsp
	subq $16, %rsp
	subq $16, %rsp
	subq $16, %rsp
	leaq -168(%rbp), %r10
	movq %r10, -176(%rbp)
	movq -176(%rbp), %r10
	movq %r10, -8(%rbp)
	movq $0, %r10
	subq $16, %rsp
	movq %r10, -184(%rbp)
	movq -184(%rbp), %r10
	movq %r10, -176(%rbp)
	addq $16, %rsp
.L_start_6:
	subq $16, %rsp
	movq $0, %r10
	movq %r10, -192(%rbp)
	movq 16(%rbp), %rax
	movq -192(%rbp), %rbx
	cmp %rbx, %rax
	setg %al
	movzbl %al, %eax
	movq %rax, -184(%rbp)
	movq -184(%rbp), %r10
	addq $16, %rsp
	test %r10, %r10
	jz .L_end_6
	subq $16, %rsp
	movq $10, %r10
	subq $16, %rsp
	movq %r10, -200(%rbp)
	movq 16(%rbp), %rax
	movq -200(%rbp), %rbx
	addq $16, %rsp
	cqto
	idivq %rbx
	movq %rdx, -192(%rbp)
	movq -192(%rbp), %r10
	movq %r10, -184(%rbp)
	movq $10, %r10
	subq $16, %rsp
	movq %r10, -200(%rbp)
	movq 16(%rbp), %rax
	movq -200(%rbp), %rbx
	addq $16, %rsp
	cqto
	idivq %rbx
	movq %rax, -192(%rbp)
	movq -192(%rbp), %r10
	movq %r10, 16(%rbp)
	movq $48, %r10
	subq $16, %rsp
	movq %r10, -200(%rbp)
	movq -184(%rbp), %rax
	movq -200(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -192(%rbp)
	subq $16, %rsp
	movq $8, %r10
	subq $16, %rsp
	movq %r10, -216(%rbp)
	movq -176(%rbp), %rax
	movq -216(%rbp), %rbx
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -208(%rbp)
	movq -8(%rbp), %rax
	movq -208(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -200(%rbp)
	movq -200(%rbp), %r11
	movq -192(%rbp), %r10
	movq %r10, (%r11)
	addq $16, %rsp
	subq $16, %rsp
	movq $1, %r10
	movq %r10, -208(%rbp)
	movq -176(%rbp), %rax
	movq -208(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -200(%rbp)
	movq -200(%rbp), %r10
	movq %r10, -176(%rbp)
	addq $16, %rsp
	addq $16, %rsp
	jmp .L_start_6
.L_end_6:
.L_start_7:
	subq $16, %rsp
	movq $0, %r10
	movq %r10, -192(%rbp)
	movq -176(%rbp), %rax
	movq -192(%rbp), %rbx
	cmp %rbx, %rax
	setg %al
	movzbl %al, %eax
	movq %rax, -184(%rbp)
	movq -184(%rbp), %r10
	addq $16, %rsp
	test %r10, %r10
	jz .L_end_7
	subq $16, %rsp
	movq $1, %r10
	movq %r10, -192(%rbp)
	movq -176(%rbp), %rax
	movq -192(%rbp), %rbx
	subq %rbx, %rax
	movq %rax, -184(%rbp)
	movq -184(%rbp), %r10
	movq %r10, -176(%rbp)
	addq $16, %rsp
	subq $16, %rsp
	movq $8, %r10
	subq $16, %rsp
	movq %r10, -200(%rbp)
	movq -176(%rbp), %rax
	movq -200(%rbp), %rbx
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -192(%rbp)
	movq -8(%rbp), %rax
	movq -192(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -184(%rbp)
	movq -184(%rbp), %r10
	addq $16, %rsp
	subq $16, %rsp
	movq (%r10), %r11
	movq %r11, -184(%rbp)
	movq -184(%rbp), %r10
	movq %r10, -192(%rbp)
	call print_char
	addq $16, %rsp
	jmp .L_start_7
.L_end_7:

	movq %rbp, %rsp
	pop %rbp
	ret

.global max
max:
	push %rbp
	movq %rsp, %rbp

	subq $16, %rsp
	movq 16(%rbp), %rax
	movq 24(%rbp), %rbx
	cmp %rbx, %rax
	setg %al
	movzbl %al, %eax
	movq %rax, -8(%rbp)
	movq -8(%rbp), %r10
	addq $16, %rsp
	test %r10, %r10
	jz .L_else_8
	movq 16(%rbp), %rax

	movq %rbp, %rsp
	pop %rbp
	ret

	jmp .L_end_8
.L_else_8:
	movq 24(%rbp), %rax

	movq %rbp, %rsp
	pop %rbp
	ret

.L_end_8:

	movq %rbp, %rsp
	pop %rbp
	ret

.global min
min:
	push %rbp
	movq %rsp, %rbp

	subq $16, %rsp
	movq 16(%rbp), %rax
	movq 24(%rbp), %rbx
	cmp %rbx, %rax
	setl %al
	movzbl %al, %eax
	movq %rax, -8(%rbp)
	movq -8(%rbp), %r10
	addq $16, %rsp
	test %r10, %r10
	jz .L_else_9
	movq 16(%rbp), %rax

	movq %rbp, %rsp
	pop %rbp
	ret

	jmp .L_end_9
.L_else_9:
	movq 24(%rbp), %rax

	movq %rbp, %rsp
	pop %rbp
	ret

.L_end_9:

	movq %rbp, %rsp
	pop %rbp
	ret

.global main
main:
	push %rbp
	movq %rsp, %rbp

	call init_input
	call read_int
	subq $16, %rsp
	movq %rax, -8(%rbp)
	movq -8(%rbp), %r10
	movq %r10, n(%rip)
	addq $16, %rsp
	call read_int
	subq $16, %rsp
	movq %rax, -8(%rbp)
	movq -8(%rbp), %r10
	movq %r10, m(%rip)
	addq $16, %rsp
	subq $16, %rsp
	movq $0, %r10
	movq %r10, -16(%rbp)
	movq -16(%rbp), %r10
	movq %r10, -8(%rbp)
.L_start_10:
	movq -8(%rbp), %rax
	movq n(%rip), %rbx
	cmp %rbx, %rax
	setl %al
	movzbl %al, %eax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %r10
	test %r10, %r10
	jz .L_end_10
	call read_int
	subq $16, %rsp
	movq %rax, -24(%rbp)
	subq $16, %rsp
	movq $8, %r10
	movq %r10, -48(%rbp)
	movq -8(%rbp), %rax
	movq -48(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -40(%rbp)
	movq heights(%rip), %rax
	movq -40(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -32(%rbp)
	movq -32(%rbp), %r11
	movq -24(%rbp), %r10
	movq %r10, (%r11)
	movq $1, %r10
	subq $16, %rsp
	movq %r10, -40(%rbp)
	movq -8(%rbp), %rax
	movq -40(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -32(%rbp)
	movq -32(%rbp), %r10
	movq %r10, -8(%rbp)
	addq $16, %rsp
	jmp .L_start_10
.L_end_10:
	movq $0, %r10
	movq %r10, -16(%rbp)
	movq -16(%rbp), %r10
	movq %r10, -8(%rbp)
.L_start_11:
	movq -8(%rbp), %rax
	movq m(%rip), %rbx
	cmp %rbx, %rax
	setl %al
	movzbl %al, %eax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %r10
	test %r10, %r10
	jz .L_end_11
	call read_int
	subq $16, %rsp
	movq %rax, -24(%rbp)
	movq -24(%rbp), %r10
	movq %r10, -16(%rbp)
	addq $16, %rsp
	subq $16, %rsp
	movq $0, %r10
	movq %r10, -32(%rbp)
	movq -32(%rbp), %r10
	movq %r10, -24(%rbp)
	movq $0, %r10
	subq $16, %rsp
	movq %r10, -40(%rbp)
	movq -40(%rbp), %r10
	movq %r10, -32(%rbp)
	addq $16, %rsp
.L_start_12:
	subq $16, %rsp
	movq -32(%rbp), %rax
	movq n(%rip), %rbx
	cmp %rbx, %rax
	setl %al
	movzbl %al, %eax
	movq %rax, -48(%rbp)
	subq $16, %rsp
	movq -24(%rbp), %rax
	movq -16(%rbp), %rbx
	cmp %rbx, %rax
	setl %al
	movzbl %al, %eax
	movq %rax, -56(%rbp)
	movq -48(%rbp), %rax
	movq -56(%rbp), %rbx
	addq $16, %rsp
	and %rbx, %rax
	movq %rax, -40(%rbp)
	movq -40(%rbp), %r10
	addq $16, %rsp
	test %r10, %r10
	jz .L_end_12
	subq $16, %rsp
	movq $0, %r10
	movq %r10, -48(%rbp)
	subq $16, %rsp
	subq $16, %rsp
	movq $8, %r10
	movq %r10, -80(%rbp)
	movq -32(%rbp), %rax
	movq -80(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -72(%rbp)
	movq heights(%rip), %rax
	movq -72(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -64(%rbp)
	movq -64(%rbp), %r10
	movq (%r10), %r11
	movq %r11, -64(%rbp)
	subq $16, %rsp
	movq -16(%rbp), %r10
	movq %r10, -72(%rbp)
	movq -64(%rbp), %r10
	movq %r10, -80(%rbp)
	call min
	addq $16, %rsp
	movq %rax, -64(%rbp)
	movq -64(%rbp), %rax
	movq -24(%rbp), %rbx
	subq %rbx, %rax
	movq %rax, -56(%rbp)
	subq $16, %rsp
	movq -56(%rbp), %r10
	movq %r10, -72(%rbp)
	movq -48(%rbp), %r10
	movq %r10, -80(%rbp)
	call max
	addq $16, %rsp
	subq $16, %rsp
	movq %rax, -72(%rbp)
	movq -72(%rbp), %r10
	movq %r10, -40(%rbp)
	addq $16, %rsp
	subq $16, %rsp
	subq $16, %rsp
	movq $8, %r10
	movq %r10, -96(%rbp)
	movq -32(%rbp), %rax
	movq -96(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -88(%rbp)
	movq heights(%rip), %rax
	movq -88(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -80(%rbp)
	movq -80(%rbp), %r10
	movq (%r10), %r11
	movq %r11, -80(%rbp)
	movq -80(%rbp), %rax
	movq -40(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -72(%rbp)
	subq $16, %rsp
	movq $8, %r10
	movq %r10, -96(%rbp)
	movq -32(%rbp), %rax
	movq -96(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -88(%rbp)
	movq heights(%rip), %rax
	movq -88(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -80(%rbp)
	movq -80(%rbp), %r11
	movq -72(%rbp), %r10
	movq %r10, (%r11)
	movq -24(%rbp), %rax
	movq -40(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -80(%rbp)
	movq -80(%rbp), %r10
	movq %r10, -24(%rbp)
	movq $1, %r10
	subq $16, %rsp
	movq %r10, -88(%rbp)
	movq -32(%rbp), %rax
	movq -88(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -80(%rbp)
	movq -80(%rbp), %r10
	movq %r10, -32(%rbp)
	addq $16, %rsp
	addq $16, %rsp
	addq $16, %rsp
	jmp .L_start_12
.L_end_12:
	subq $16, %rsp
	movq $1, %r10
	movq %r10, -48(%rbp)
	movq -8(%rbp), %rax
	movq -48(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -40(%rbp)
	movq -40(%rbp), %r10
	movq %r10, -8(%rbp)
	addq $16, %rsp
	addq $16, %rsp
	jmp .L_start_11
.L_end_11:
	movq $0, %r10
	movq %r10, -16(%rbp)
	movq -16(%rbp), %r10
	movq %r10, -8(%rbp)
.L_start_13:
	movq -8(%rbp), %rax
	movq n(%rip), %rbx
	cmp %rbx, %rax
	setl %al
	movzbl %al, %eax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %r10
	test %r10, %r10
	jz .L_end_13
	subq $16, %rsp
	movq $8, %r10
	movq %r10, -32(%rbp)
	movq -8(%rbp), %rax
	movq -32(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -24(%rbp)
	movq heights(%rip), %rax
	movq -24(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %r10
	movq (%r10), %r11
	movq %r11, -16(%rbp)
	subq $16, %rsp
	movq -16(%rbp), %r10
	movq %r10, -32(%rbp)
	call print_int
	movq $10, %r10
	movq %r10, -32(%rbp)
	subq $16, %rsp
	movq -32(%rbp), %r10
	movq %r10, -48(%rbp)
	call print_char
	movq $1, %r10
	subq $16, %rsp
	movq %r10, -56(%rbp)
	movq -8(%rbp), %rax
	movq -56(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -48(%rbp)
	movq -48(%rbp), %r10
	movq %r10, -8(%rbp)
	addq $16, %rsp
	addq $16, %rsp
	jmp .L_start_13
.L_end_13:
	call flush_output

	movq %rbp, %rsp
	pop %rbp
	ret

.section .data

.section .text
)");
