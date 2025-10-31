asm(R"(
.section .data
.align 8
READ_BUFFER_CAP: .quad 5242880
WRITE_BUFFER_CAP: .quad 32768
MOD: .quad 1000000007
input_buffer: .quad _galloc_array_0
input_index: .quad 0
output_buffer: .quad _galloc_array_1
output_index: .quad 0
str: .quad _galloc_array_2
fact: .quad _galloc_array_3
ifact: .quad _galloc_array_4

.section .bss
.align 8
_galloc_array_0: .zero 5242880
_galloc_array_1: .zero 32768
_galloc_array_2: .zero 1000008
_galloc_array_3: .zero 8000040
_galloc_array_4: .zero 8000040

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
	movzbq (%r10), %r11
	movb %r11b, -9(%rbp)
	movzbq -9(%rbp), %r10
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
	movq 16(%rbp), %r10
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
	movq %rax, -16(%rbp)
	movq -16(%rbp), %r10
	movq %r10, -8(%rbp)
	movq $0, %r10
	subq $16, %rsp
	movq %r10, -24(%rbp)
	movq -24(%rbp), %r10
	movq %r10, -16(%rbp)
	addq $16, %rsp
	subq $16, %rsp
	movq $0, %r10
	movq %r10, -32(%rbp)
	movq -32(%rbp), %r10
	movq %r10, -24(%rbp)
.L_start_3:
	subq $16, %rsp
	movq $10, %r10
	subq $16, %rsp
	movq %r10, -56(%rbp)
	movq -8(%rbp), %rax
	movq -56(%rbp), %rbx
	addq $16, %rsp
	cmp %rbx, %rax
	sete %al
	movzbl %al, %eax
	movq %rax, -48(%rbp)
	subq $16, %rsp
	movq $32, %r10
	movq %r10, -64(%rbp)
	movq -8(%rbp), %rax
	movq -64(%rbp), %rbx
	cmp %rbx, %rax
	sete %al
	movzbl %al, %eax
	movq %rax, -56(%rbp)
	movq -48(%rbp), %rax
	movq -56(%rbp), %rbx
	addq $16, %rsp
	or %rbx, %rax
	movq %rax, -40(%rbp)
	movq $13, %r10
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
	movq %rax, -32(%rbp)
	movq -32(%rbp), %r10
	movq %r10, -8(%rbp)
	jmp .L_start_3
.L_end_3:
	movq $45, %r10
	subq $16, %rsp
	movq %r10, -40(%rbp)
	movq -8(%rbp), %rax
	movq -40(%rbp), %rbx
	addq $16, %rsp
	cmp %rbx, %rax
	sete %al
	movzbl %al, %eax
	movq %rax, -32(%rbp)
	movq -32(%rbp), %r10
	test %r10, %r10
	jz .L_else_4
	movq $1, %r10
	movq %r10, -32(%rbp)
	movq -32(%rbp), %r10
	movq %r10, -24(%rbp)
	call read_char
	movq %rax, -32(%rbp)
	movq -32(%rbp), %r10
	movq %r10, -8(%rbp)
	jmp .L_end_4
.L_else_4:
.L_end_4:
.L_start_5:
	subq $16, %rsp
	subq $16, %rsp
	movq $10, %r10
	movq %r10, -64(%rbp)
	movq -8(%rbp), %rax
	movq -64(%rbp), %rbx
	cmp %rbx, %rax
	setne %al
	movzbl %al, %eax
	movq %rax, -56(%rbp)
	movq $32, %r10
	subq $16, %rsp
	movq %r10, -72(%rbp)
	movq -8(%rbp), %rax
	movq -72(%rbp), %rbx
	addq $16, %rsp
	cmp %rbx, %rax
	setne %al
	movzbl %al, %eax
	movq %rax, -64(%rbp)
	movq -56(%rbp), %rax
	movq -64(%rbp), %rbx
	addq $16, %rsp
	and %rbx, %rax
	movq %rax, -48(%rbp)
	subq $16, %rsp
	movq $13, %r10
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
	jz .L_end_5
	subq $16, %rsp
	movq $10, %r10
	subq $16, %rsp
	movq %r10, -56(%rbp)
	movq -16(%rbp), %rax
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
	movq %r10, -16(%rbp)
	call read_char
	movq %rax, -32(%rbp)
	movq -32(%rbp), %r10
	movq %r10, -8(%rbp)
	jmp .L_start_5
.L_end_5:
	movq $1, %r10
	subq $16, %rsp
	movq %r10, -40(%rbp)
	movq -24(%rbp), %rax
	movq -40(%rbp), %rbx
	addq $16, %rsp
	cmp %rbx, %rax
	sete %al
	movzbl %al, %eax
	movq %rax, -32(%rbp)
	movq -32(%rbp), %r10
	test %r10, %r10
	jz .L_else_6
	movq $0, %r10
	subq $16, %rsp
	movq %r10, -40(%rbp)
	movq -40(%rbp), %rax
	movq -16(%rbp), %rbx
	addq $16, %rsp
	subq %rbx, %rax
	movq %rax, -32(%rbp)
	movq -32(%rbp), %rax

	movq %rbp, %rsp
	pop %rbp
	ret

	jmp .L_end_6
.L_else_6:
.L_end_6:
	movq -16(%rbp), %rax

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
	jz .L_else_7
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
	jmp .L_end_7
.L_else_7:
.L_end_7:
	subq $16, %rsp
	movq $0, %r10
	movq %r10, -16(%rbp)
	movq -16(%rbp), %r10
	movq %r10, -8(%rbp)
	movq $0, %r10
	subq $16, %rsp
	movq %r10, -24(%rbp)
	movq 16(%rbp), %rax
	movq -24(%rbp), %rbx
	addq $16, %rsp
	cmp %rbx, %rax
	setl %al
	movzbl %al, %eax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %r10
	test %r10, %r10
	jz .L_else_8
	movq $1, %r10
	movq %r10, -16(%rbp)
	movq -16(%rbp), %r10
	movq %r10, -8(%rbp)
	movq $0, %r10
	subq $16, %rsp
	movq %r10, -24(%rbp)
	movq -24(%rbp), %rax
	movq 16(%rbp), %rbx
	addq $16, %rsp
	subq %rbx, %rax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %r10
	movq %r10, 16(%rbp)
	jmp .L_end_8
.L_else_8:
.L_end_8:
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
	leaq -176(%rbp), %r10
	subq $16, %rsp
	movq %r10, -184(%rbp)
	movq -184(%rbp), %r10
	movq %r10, -16(%rbp)
	addq $16, %rsp
	subq $16, %rsp
	movq $0, %r10
	movq %r10, -192(%rbp)
	movq -192(%rbp), %r10
	movq %r10, -184(%rbp)
.L_start_9:
	movq $0, %r10
	subq $16, %rsp
	movq %r10, -200(%rbp)
	movq 16(%rbp), %rax
	movq -200(%rbp), %rbx
	addq $16, %rsp
	cmp %rbx, %rax
	setg %al
	movzbl %al, %eax
	movq %rax, -192(%rbp)
	movq -192(%rbp), %r10
	test %r10, %r10
	jz .L_end_9
	subq $16, %rsp
	movq $10, %r10
	movq %r10, -208(%rbp)
	movq 16(%rbp), %rax
	movq -208(%rbp), %rbx
	cqto
	idivq %rbx
	movq %rdx, -200(%rbp)
	movq -200(%rbp), %r10
	movq %r10, -192(%rbp)
	addq $16, %rsp
	subq $16, %rsp
	movq $10, %r10
	movq %r10, -208(%rbp)
	movq 16(%rbp), %rax
	movq -208(%rbp), %rbx
	cqto
	idivq %rbx
	movq %rax, -200(%rbp)
	movq -200(%rbp), %r10
	movq %r10, 16(%rbp)
	addq $16, %rsp
	subq $16, %rsp
	movq $48, %r10
	movq %r10, -208(%rbp)
	movq -192(%rbp), %rax
	movq -208(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -200(%rbp)
	subq $16, %rsp
	movq $8, %r10
	movq %r10, -224(%rbp)
	movq -184(%rbp), %rax
	movq -224(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -216(%rbp)
	movq -16(%rbp), %rax
	movq -216(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -208(%rbp)
	movq -208(%rbp), %r11
	movq -200(%rbp), %r10
	movq %r10, (%r11)
	movq $1, %r10
	subq $16, %rsp
	movq %r10, -216(%rbp)
	movq -184(%rbp), %rax
	movq -216(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -208(%rbp)
	movq -208(%rbp), %r10
	movq %r10, -184(%rbp)
	addq $16, %rsp
	jmp .L_start_9
.L_end_9:
	movq $1, %r10
	subq $16, %rsp
	movq %r10, -200(%rbp)
	movq -8(%rbp), %rax
	movq -200(%rbp), %rbx
	addq $16, %rsp
	cmp %rbx, %rax
	sete %al
	movzbl %al, %eax
	movq %rax, -192(%rbp)
	movq -192(%rbp), %r10
	test %r10, %r10
	jz .L_else_10
	movq $45, %r10
	movq %r10, -192(%rbp)
	subq $16, %rsp
	movq -192(%rbp), %r10
	movq %r10, -208(%rbp)
	call print_char
	addq $16, %rsp
	jmp .L_end_10
.L_else_10:
.L_end_10:
.L_start_11:
	movq $0, %r10
	subq $16, %rsp
	movq %r10, -200(%rbp)
	movq -184(%rbp), %rax
	movq -200(%rbp), %rbx
	addq $16, %rsp
	cmp %rbx, %rax
	setg %al
	movzbl %al, %eax
	movq %rax, -192(%rbp)
	movq -192(%rbp), %r10
	test %r10, %r10
	jz .L_end_11
	movq $1, %r10
	subq $16, %rsp
	movq %r10, -200(%rbp)
	movq -184(%rbp), %rax
	movq -200(%rbp), %rbx
	addq $16, %rsp
	subq %rbx, %rax
	movq %rax, -192(%rbp)
	movq -192(%rbp), %r10
	movq %r10, -184(%rbp)
	subq $16, %rsp
	movq $8, %r10
	movq %r10, -208(%rbp)
	movq -184(%rbp), %rax
	movq -208(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -200(%rbp)
	movq -16(%rbp), %rax
	movq -200(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -192(%rbp)
	movq -192(%rbp), %r10
	movq (%r10), %r11
	movq %r11, -192(%rbp)
	subq $16, %rsp
	movq -192(%rbp), %r10
	movq %r10, -208(%rbp)
	call print_char
	addq $16, %rsp
	jmp .L_start_11
.L_end_11:

	movq %rbp, %rsp
	pop %rbp
	ret

.global read_string
read_string:
	push %rbp
	movq %rsp, %rbp

	subq $16, %rsp
	movq $0, %r10
	movq %r10, -16(%rbp)
	movq -16(%rbp), %r10
	movq %r10, -8(%rbp)
.L_start_12:
	movq -8(%rbp), %rax
	movq 24(%rbp), %rbx
	cmp %rbx, %rax
	setl %al
	movzbl %al, %eax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %r10
	test %r10, %r10
	jz .L_end_12
	call read_char
	subq $16, %rsp
	movq %rax, -24(%rbp)
	movq -24(%rbp), %r10
	movq %r10, -16(%rbp)
	addq $16, %rsp
	subq $16, %rsp
	movq $0, %r10
	movq %r10, -32(%rbp)
	movq -16(%rbp), %rax
	movq -32(%rbp), %rbx
	cmp %rbx, %rax
	sete %al
	movzbl %al, %eax
	movq %rax, -24(%rbp)
	movq -24(%rbp), %r10
	addq $16, %rsp
	test %r10, %r10
	jz .L_else_13
	jmp .L_end_12
	jmp .L_end_13
.L_else_13:
.L_end_13:
	subq $16, %rsp
	subq $16, %rsp
	movq $10, %r10
	movq %r10, -48(%rbp)
	movq -16(%rbp), %rax
	movq -48(%rbp), %rbx
	cmp %rbx, %rax
	sete %al
	movzbl %al, %eax
	movq %rax, -40(%rbp)
	movq $13, %r10
	subq $16, %rsp
	movq %r10, -56(%rbp)
	movq -16(%rbp), %rax
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
	subq $16, %rsp
	movq $32, %r10
	movq %r10, -48(%rbp)
	movq -16(%rbp), %rax
	movq -48(%rbp), %rbx
	cmp %rbx, %rax
	sete %al
	movzbl %al, %eax
	movq %rax, -40(%rbp)
	movq -32(%rbp), %rax
	movq -40(%rbp), %rbx
	addq $16, %rsp
	or %rbx, %rax
	movq %rax, -24(%rbp)
	movq -24(%rbp), %r10
	addq $16, %rsp
	test %r10, %r10
	jz .L_else_14
	jmp .L_start_12
	jmp .L_end_14
.L_else_14:
.L_end_14:
	subq $16, %rsp
	movq $1, %r10
	subq $16, %rsp
	movq %r10, -40(%rbp)
	movq -8(%rbp), %rax
	movq -40(%rbp), %rbx
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -32(%rbp)
	movq 16(%rbp), %rax
	movq -32(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -24(%rbp)
	movq -24(%rbp), %r11
	movq -16(%rbp), %r10
	movb %r10b, (%r11)
	addq $16, %rsp
	subq $16, %rsp
	movq $1, %r10
	movq %r10, -32(%rbp)
	movq -8(%rbp), %rax
	movq -32(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -24(%rbp)
	movq -24(%rbp), %r10
	movq %r10, -8(%rbp)
	addq $16, %rsp
	jmp .L_start_12
.L_end_12:

	movq %rbp, %rsp
	pop %rbp
	ret

.global mod_pow
mod_pow:
	push %rbp
	movq %rsp, %rbp

	subq $16, %rsp
	movq 16(%rbp), %rax
	movq MOD(%rip), %rbx
	cqto
	idivq %rbx
	movq %rdx, -16(%rbp)
	movq -16(%rbp), %r10
	movq %r10, -8(%rbp)
	movq $0, %r10
	subq $16, %rsp
	movq %r10, -24(%rbp)
	movq -8(%rbp), %rax
	movq -24(%rbp), %rbx
	addq $16, %rsp
	cmp %rbx, %rax
	setl %al
	movzbl %al, %eax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %r10
	test %r10, %r10
	jz .L_else_15
	movq -8(%rbp), %rax
	movq MOD(%rip), %rbx
	addq %rbx, %rax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %r10
	movq %r10, -8(%rbp)
	jmp .L_end_15
.L_else_15:
.L_end_15:
	movq $1, %r10
	subq $16, %rsp
	movq %r10, -24(%rbp)
	movq -24(%rbp), %r10
	movq %r10, -16(%rbp)
	addq $16, %rsp
	subq $16, %rsp
	movq -8(%rbp), %r10
	movq %r10, -24(%rbp)
	movq 24(%rbp), %r10
	movq %r10, -32(%rbp)
.L_start_16:
	subq $16, %rsp
	movq $0, %r10
	movq %r10, -48(%rbp)
	movq -32(%rbp), %rax
	movq -48(%rbp), %rbx
	cmp %rbx, %rax
	setg %al
	movzbl %al, %eax
	movq %rax, -40(%rbp)
	movq -40(%rbp), %r10
	addq $16, %rsp
	test %r10, %r10
	jz .L_end_16
	subq $16, %rsp
	movq $2, %r10
	subq $16, %rsp
	movq %r10, -56(%rbp)
	movq -32(%rbp), %rax
	movq -56(%rbp), %rbx
	addq $16, %rsp
	cqto
	idivq %rbx
	movq %rdx, -48(%rbp)
	movq $1, %r10
	subq $16, %rsp
	movq %r10, -56(%rbp)
	movq -48(%rbp), %rax
	movq -56(%rbp), %rbx
	addq $16, %rsp
	cmp %rbx, %rax
	sete %al
	movzbl %al, %eax
	movq %rax, -40(%rbp)
	movq -40(%rbp), %r10
	addq $16, %rsp
	test %r10, %r10
	jz .L_else_17
	subq $16, %rsp
	movq -16(%rbp), %rax
	movq -24(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -48(%rbp)
	movq -48(%rbp), %rax
	movq MOD(%rip), %rbx
	cqto
	idivq %rbx
	movq %rdx, -40(%rbp)
	movq -40(%rbp), %r10
	movq %r10, -16(%rbp)
	addq $16, %rsp
	jmp .L_end_17
.L_else_17:
.L_end_17:
	subq $16, %rsp
	movq -24(%rbp), %rax
	movq -24(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -48(%rbp)
	movq -48(%rbp), %rax
	movq MOD(%rip), %rbx
	cqto
	idivq %rbx
	movq %rdx, -40(%rbp)
	movq -40(%rbp), %r10
	movq %r10, -24(%rbp)
	addq $16, %rsp
	subq $16, %rsp
	movq $2, %r10
	movq %r10, -48(%rbp)
	movq -32(%rbp), %rax
	movq -48(%rbp), %rbx
	cqto
	idivq %rbx
	movq %rax, -40(%rbp)
	movq -40(%rbp), %r10
	movq %r10, -32(%rbp)
	addq $16, %rsp
	jmp .L_start_16
.L_end_16:
	movq -16(%rbp), %rax

	movq %rbp, %rsp
	pop %rbp
	ret


	movq %rbp, %rsp
	pop %rbp
	ret

.global choose
choose:
	push %rbp
	movq %rsp, %rbp

	subq $16, %rsp
	movq $0, %r10
	subq $16, %rsp
	movq %r10, -24(%rbp)
	movq 24(%rbp), %rax
	movq -24(%rbp), %rbx
	addq $16, %rsp
	cmp %rbx, %rax
	setl %al
	movzbl %al, %eax
	movq %rax, -16(%rbp)
	subq $16, %rsp
	movq 24(%rbp), %rax
	movq 16(%rbp), %rbx
	cmp %rbx, %rax
	setg %al
	movzbl %al, %eax
	movq %rax, -24(%rbp)
	movq -16(%rbp), %rax
	movq -24(%rbp), %rbx
	addq $16, %rsp
	or %rbx, %rax
	movq %rax, -8(%rbp)
	movq -8(%rbp), %r10
	addq $16, %rsp
	test %r10, %r10
	jz .L_else_18
	movq $0, %r10
	subq $16, %rsp
	movq %r10, -8(%rbp)
	movq -8(%rbp), %rax

	movq %rbp, %rsp
	pop %rbp
	ret

	addq $16, %rsp
	jmp .L_end_18
.L_else_18:
.L_end_18:
	subq $16, %rsp
	subq $16, %rsp
	movq $8, %r10
	movq %r10, -32(%rbp)
	movq 16(%rbp), %rax
	movq -32(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -24(%rbp)
	movq 32(%rbp), %rax
	movq -24(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %r10
	movq (%r10), %r11
	movq %r11, -16(%rbp)
	movq -16(%rbp), %r10
	movq %r10, -8(%rbp)
	subq $16, %rsp
	subq $16, %rsp
	movq $8, %r10
	subq $16, %rsp
	movq %r10, -56(%rbp)
	movq 24(%rbp), %rax
	movq -56(%rbp), %rbx
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -48(%rbp)
	movq 40(%rbp), %rax
	movq -48(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -40(%rbp)
	movq -40(%rbp), %r10
	addq $16, %rsp
	subq $16, %rsp
	movq (%r10), %r11
	movq %r11, -40(%rbp)
	movq -8(%rbp), %rax
	movq -40(%rbp), %rbx
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -32(%rbp)
	movq -32(%rbp), %rax
	movq MOD(%rip), %rbx
	cqto
	idivq %rbx
	movq %rdx, -24(%rbp)
	movq -24(%rbp), %r10
	movq %r10, -16(%rbp)
	addq $16, %rsp
	subq $16, %rsp
	subq $16, %rsp
	subq $16, %rsp
	movq 16(%rbp), %rax
	movq 24(%rbp), %rbx
	subq %rbx, %rax
	movq %rax, -56(%rbp)
	movq $8, %r10
	movq %r10, -64(%rbp)
	movq -56(%rbp), %rax
	movq -64(%rbp), %rbx
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -48(%rbp)
	movq 40(%rbp), %rax
	movq -48(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -40(%rbp)
	movq -40(%rbp), %r10
	addq $16, %rsp
	subq $16, %rsp
	movq (%r10), %r11
	movq %r11, -40(%rbp)
	movq -16(%rbp), %rax
	movq -40(%rbp), %rbx
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -32(%rbp)
	movq -32(%rbp), %rax
	movq MOD(%rip), %rbx
	cqto
	idivq %rbx
	movq %rdx, -24(%rbp)
	movq -24(%rbp), %rax

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

	call init_input
	subq $16, %rsp
	call read_int
	movq %rax, -16(%rbp)
	movq -16(%rbp), %r10
	movq %r10, -8(%rbp)
	call read_int
	subq $16, %rsp
	movq %rax, -24(%rbp)
	movq -24(%rbp), %r10
	movq %r10, -16(%rbp)
	addq $16, %rsp
	subq $16, %rsp
	call read_int
	movq %rax, -32(%rbp)
	movq -32(%rbp), %r10
	movq %r10, -24(%rbp)
	subq $16, %rsp
	movq -16(%rbp), %r10
	movq %r10, -40(%rbp)
	movq str(%rip), %r10
	movq %r10, -48(%rbp)
	call read_string
	addq $16, %rsp
	movq $0, %r10
	subq $16, %rsp
	movq %r10, -40(%rbp)
	movq -40(%rbp), %r10
	movq %r10, -32(%rbp)
	addq $16, %rsp
	subq $16, %rsp
	movq $0, %r10
	movq %r10, -48(%rbp)
	movq -48(%rbp), %r10
	movq %r10, -40(%rbp)
	movq $0, %r10
	subq $16, %rsp
	movq %r10, -56(%rbp)
	movq -56(%rbp), %r10
	movq %r10, -48(%rbp)
	addq $16, %rsp
.L_start_19:
	subq $16, %rsp
	movq -48(%rbp), %rax
	movq -16(%rbp), %rbx
	cmp %rbx, %rax
	setl %al
	movzbl %al, %eax
	movq %rax, -56(%rbp)
	movq -56(%rbp), %r10
	addq $16, %rsp
	test %r10, %r10
	jz .L_end_19
	subq $16, %rsp
	subq $16, %rsp
	movq $1, %r10
	movq %r10, -73(%rbp)
	movq -48(%rbp), %rax
	movq -73(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -65(%rbp)
	movq str(%rip), %rax
	movq -65(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -57(%rbp)
	movq -57(%rbp), %r10
	movzbq (%r10), %r11
	movb %r11b, -50(%rbp)
	movq $77, %r10
	movq %r10, -58(%rbp)
	movzbq -50(%rbp), %rax
	movq -58(%rbp), %rbx
	cmp %rbx, %rax
	sete %al
	movzbl %al, %eax
	movb %al, -49(%rbp)
	movzbq -49(%rbp), %r10
	addq $16, %rsp
	test %r10, %r10
	jz .L_else_20
	subq $16, %rsp
	movq $1, %r10
	movq %r10, -64(%rbp)
	movq -32(%rbp), %rax
	movq -64(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -56(%rbp)
	movq -56(%rbp), %r10
	movq %r10, -32(%rbp)
	addq $16, %rsp
	jmp .L_end_20
.L_else_20:
	subq $16, %rsp
	movq $1, %r10
	movq %r10, -64(%rbp)
	movq -40(%rbp), %rax
	movq -64(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -56(%rbp)
	movq -56(%rbp), %r10
	movq %r10, -40(%rbp)
	addq $16, %rsp
.L_end_20:
	subq $16, %rsp
	movq $1, %r10
	movq %r10, -64(%rbp)
	movq -48(%rbp), %rax
	movq -64(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -56(%rbp)
	movq -56(%rbp), %r10
	movq %r10, -48(%rbp)
	addq $16, %rsp
	jmp .L_start_19
.L_end_19:
	subq $16, %rsp
	movq -8(%rbp), %rax
	movq -32(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -64(%rbp)
	movq -40(%rbp), %rax
	movq -64(%rbp), %rbx
	cmp %rbx, %rax
	setne %al
	movzbl %al, %eax
	movq %rax, -56(%rbp)
	movq -56(%rbp), %r10
	addq $16, %rsp
	test %r10, %r10
	jz .L_else_21
	movq $0, %r10
	subq $16, %rsp
	movq %r10, -56(%rbp)
	movq -56(%rbp), %r10
	movq %r10, -64(%rbp)
	call print_int
	addq $16, %rsp
	movq $10, %r10
	subq $16, %rsp
	movq %r10, -56(%rbp)
	movq -56(%rbp), %r10
	movq %r10, -64(%rbp)
	call print_char
	addq $16, %rsp
	call flush_output
	movq $0, %r10
	subq $16, %rsp
	movq %r10, -56(%rbp)
	movq -56(%rbp), %rax

	movq %rbp, %rsp
	pop %rbp
	ret

	addq $16, %rsp
	jmp .L_end_21
.L_else_21:
.L_end_21:
	subq $16, %rsp
	movq -40(%rbp), %r10
	movq %r10, -56(%rbp)
	movq $1, %r10
	movq %r10, -64(%rbp)
	subq $16, %rsp
	movq $0, %r10
	subq $16, %rsp
	movq %r10, -88(%rbp)
	movq $8, %r10
	movq %r10, -96(%rbp)
	movq -88(%rbp), %rax
	movq -96(%rbp), %rbx
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -80(%rbp)
	movq fact(%rip), %rax
	movq -80(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -72(%rbp)
	movq -72(%rbp), %r11
	movq -64(%rbp), %r10
	movq %r10, (%r11)
	addq $16, %rsp
	subq $16, %rsp
	movq $1, %r10
	movq %r10, -80(%rbp)
	movq -80(%rbp), %r10
	movq %r10, -72(%rbp)
.L_start_22:
	movq -72(%rbp), %rax
	movq -56(%rbp), %rbx
	cmp %rbx, %rax
	setle %al
	movzbl %al, %eax
	movq %rax, -80(%rbp)
	movq -80(%rbp), %r10
	test %r10, %r10
	jz .L_end_22
	subq $16, %rsp
	subq $16, %rsp
	movq $1, %r10
	subq $16, %rsp
	movq %r10, -120(%rbp)
	movq -72(%rbp), %rax
	movq -120(%rbp), %rbx
	addq $16, %rsp
	subq %rbx, %rax
	movq %rax, -112(%rbp)
	movq $8, %r10
	subq $16, %rsp
	movq %r10, -120(%rbp)
	movq -112(%rbp), %rax
	movq -120(%rbp), %rbx
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -104(%rbp)
	movq fact(%rip), %rax
	movq -104(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -96(%rbp)
	movq -96(%rbp), %r10
	movq (%r10), %r11
	movq %r11, -96(%rbp)
	movq -96(%rbp), %rax
	movq -72(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -88(%rbp)
	movq -88(%rbp), %rax
	movq MOD(%rip), %rbx
	addq $16, %rsp
	cqto
	idivq %rbx
	movq %rdx, -80(%rbp)
	subq $16, %rsp
	movq $8, %r10
	subq $16, %rsp
	movq %r10, -104(%rbp)
	movq -72(%rbp), %rax
	movq -104(%rbp), %rbx
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -96(%rbp)
	movq fact(%rip), %rax
	movq -96(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -88(%rbp)
	movq -88(%rbp), %r11
	movq -80(%rbp), %r10
	movq %r10, (%r11)
	addq $16, %rsp
	subq $16, %rsp
	movq $1, %r10
	movq %r10, -96(%rbp)
	movq -72(%rbp), %rax
	movq -96(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -88(%rbp)
	movq -88(%rbp), %r10
	movq %r10, -72(%rbp)
	addq $16, %rsp
	jmp .L_start_22
.L_end_22:
	subq $16, %rsp
	movq $8, %r10
	movq %r10, -96(%rbp)
	movq -56(%rbp), %rax
	movq -96(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -88(%rbp)
	movq fact(%rip), %rax
	movq -88(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -80(%rbp)
	movq -80(%rbp), %r10
	movq (%r10), %r11
	movq %r11, -80(%rbp)
	subq $16, %rsp
	movq $2, %r10
	movq %r10, -96(%rbp)
	movq MOD(%rip), %rax
	movq -96(%rbp), %rbx
	subq %rbx, %rax
	movq %rax, -88(%rbp)
	subq $16, %rsp
	movq -88(%rbp), %r10
	movq %r10, -104(%rbp)
	movq -80(%rbp), %r10
	movq %r10, -112(%rbp)
	call mod_pow
	addq $16, %rsp
	addq $16, %rsp
	movq %rax, -80(%rbp)
	subq $16, %rsp
	movq $8, %r10
	subq $16, %rsp
	movq %r10, -104(%rbp)
	movq -56(%rbp), %rax
	movq -104(%rbp), %rbx
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -96(%rbp)
	movq ifact(%rip), %rax
	movq -96(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -88(%rbp)
	movq -88(%rbp), %r11
	movq -80(%rbp), %r10
	movq %r10, (%r11)
	addq $16, %rsp
	subq $16, %rsp
	movq -56(%rbp), %r10
	movq %r10, -88(%rbp)
.L_start_23:
	movq $0, %r10
	subq $16, %rsp
	movq %r10, -104(%rbp)
	movq -88(%rbp), %rax
	movq -104(%rbp), %rbx
	addq $16, %rsp
	cmp %rbx, %rax
	setg %al
	movzbl %al, %eax
	movq %rax, -96(%rbp)
	movq -96(%rbp), %r10
	test %r10, %r10
	jz .L_end_23
	subq $16, %rsp
	subq $16, %rsp
	movq $8, %r10
	movq %r10, -128(%rbp)
	movq -88(%rbp), %rax
	movq -128(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -120(%rbp)
	movq ifact(%rip), %rax
	movq -120(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -112(%rbp)
	movq -112(%rbp), %r10
	movq (%r10), %r11
	movq %r11, -112(%rbp)
	movq -112(%rbp), %rax
	movq -88(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -104(%rbp)
	movq -104(%rbp), %rax
	movq MOD(%rip), %rbx
	addq $16, %rsp
	cqto
	idivq %rbx
	movq %rdx, -96(%rbp)
	subq $16, %rsp
	subq $16, %rsp
	movq $1, %r10
	movq %r10, -128(%rbp)
	movq -88(%rbp), %rax
	movq -128(%rbp), %rbx
	subq %rbx, %rax
	movq %rax, -120(%rbp)
	movq $8, %r10
	movq %r10, -128(%rbp)
	movq -120(%rbp), %rax
	movq -128(%rbp), %rbx
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -112(%rbp)
	movq ifact(%rip), %rax
	movq -112(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -104(%rbp)
	movq -104(%rbp), %r11
	movq -96(%rbp), %r10
	movq %r10, (%r11)
	addq $16, %rsp
	subq $16, %rsp
	movq $1, %r10
	movq %r10, -112(%rbp)
	movq -88(%rbp), %rax
	movq -112(%rbp), %rbx
	subq %rbx, %rax
	movq %rax, -104(%rbp)
	movq -104(%rbp), %r10
	movq %r10, -88(%rbp)
	addq $16, %rsp
	jmp .L_start_23
.L_end_23:
	movq $0, %r10
	subq $16, %rsp
	movq %r10, -104(%rbp)
	movq -104(%rbp), %r10
	movq %r10, -96(%rbp)
	addq $16, %rsp
	subq $16, %rsp
	movq $0, %r10
	movq %r10, -112(%rbp)
	movq -112(%rbp), %r10
	movq %r10, -104(%rbp)
	movq $1, %r10
	subq $16, %rsp
	movq %r10, -120(%rbp)
	movq -120(%rbp), %r10
	movq %r10, -112(%rbp)
	addq $16, %rsp
	subq $16, %rsp
	movq $1, %r10
	subq $16, %rsp
	movq %r10, -136(%rbp)
	movq -16(%rbp), %rax
	movq -136(%rbp), %rbx
	addq $16, %rsp
	subq %rbx, %rax
	movq %rax, -128(%rbp)
	movq -128(%rbp), %r10
	movq %r10, -120(%rbp)
.L_start_24:
	movq $0, %r10
	subq $16, %rsp
	movq %r10, -136(%rbp)
	movq -120(%rbp), %rax
	movq -136(%rbp), %rbx
	addq $16, %rsp
	cmp %rbx, %rax
	setge %al
	movzbl %al, %eax
	movq %rax, -128(%rbp)
	movq -128(%rbp), %r10
	test %r10, %r10
	jz .L_end_24
	subq $16, %rsp
	movq $1, %r10
	subq $16, %rsp
	movq %r10, -152(%rbp)
	movq -120(%rbp), %rax
	movq -152(%rbp), %rbx
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -144(%rbp)
	movq str(%rip), %rax
	movq -144(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -136(%rbp)
	movq -136(%rbp), %r10
	addq $16, %rsp
	subq $16, %rsp
	movzbq (%r10), %r11
	movb %r11b, -129(%rbp)
	movzbq -129(%rbp), %r10
	movq %r10, -128(%rbp)
	addq $16, %rsp
	subq $16, %rsp
	movq $79, %r10
	movq %r10, -144(%rbp)
	movq -128(%rbp), %rax
	movq -144(%rbp), %rbx
	cmp %rbx, %rax
	sete %al
	movzbl %al, %eax
	movq %rax, -136(%rbp)
	movq -136(%rbp), %r10
	addq $16, %rsp
	test %r10, %r10
	jz .L_else_25
	subq $16, %rsp
	movq $1, %r10
	movq %r10, -144(%rbp)
	movq -104(%rbp), %rax
	movq -144(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -136(%rbp)
	movq -136(%rbp), %r10
	movq %r10, -104(%rbp)
	addq $16, %rsp
	subq $16, %rsp
	movq $1, %r10
	movq %r10, -144(%rbp)
	movq -120(%rbp), %rax
	movq -144(%rbp), %rbx
	subq %rbx, %rax
	movq %rax, -136(%rbp)
	movq -136(%rbp), %r10
	movq %r10, -120(%rbp)
	addq $16, %rsp
	jmp .L_start_24
	jmp .L_end_25
.L_else_25:
.L_end_25:
	subq $16, %rsp
	subq $16, %rsp
	movq -8(%rbp), %rax
	movq -96(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -152(%rbp)
	movq -104(%rbp), %rax
	movq -152(%rbp), %rbx
	addq $16, %rsp
	subq %rbx, %rax
	movq %rax, -144(%rbp)
	movq -144(%rbp), %r10
	movq %r10, -136(%rbp)
	subq $16, %rsp
	movq -136(%rbp), %rax
	movq -8(%rbp), %rbx
	cmp %rbx, %rax
	setl %al
	movzbl %al, %eax
	movq %rax, -152(%rbp)
	movq $0, %r10
	subq $16, %rsp
	movq %r10, -168(%rbp)
	movq -136(%rbp), %rax
	movq -168(%rbp), %rbx
	addq $16, %rsp
	cmp %rbx, %rax
	setl %al
	movzbl %al, %eax
	movq %rax, -160(%rbp)
	movq -152(%rbp), %rax
	movq -160(%rbp), %rbx
	addq $16, %rsp
	or %rbx, %rax
	movq %rax, -144(%rbp)
	movq -144(%rbp), %r10
	test %r10, %r10
	jz .L_else_26
	movq $0, %r10
	movq %r10, -144(%rbp)
	movq -144(%rbp), %r10
	movq %r10, -112(%rbp)
	addq $16, %rsp
	jmp .L_end_24
	jmp .L_end_26
.L_else_26:
.L_end_26:
	subq $16, %rsp
	subq $16, %rsp
	movq ifact(%rip), %r10
	movq %r10, -152(%rbp)
	movq fact(%rip), %r10
	movq %r10, -160(%rbp)
	movq -8(%rbp), %r10
	movq %r10, -168(%rbp)
	movq -136(%rbp), %r10
	movq %r10, -176(%rbp)
	call choose
	addq $16, %rsp
	addq $16, %rsp
	subq $16, %rsp
	movq %rax, -152(%rbp)
	movq -152(%rbp), %r10
	movq %r10, -144(%rbp)
	addq $16, %rsp
	subq $16, %rsp
	movq -112(%rbp), %rax
	movq -144(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -160(%rbp)
	movq -160(%rbp), %rax
	movq MOD(%rip), %rbx
	cqto
	idivq %rbx
	movq %rdx, -152(%rbp)
	movq -152(%rbp), %r10
	movq %r10, -112(%rbp)
	addq $16, %rsp
	subq $16, %rsp
	movq $1, %r10
	movq %r10, -160(%rbp)
	movq -96(%rbp), %rax
	movq -160(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -152(%rbp)
	movq -152(%rbp), %r10
	movq %r10, -96(%rbp)
	addq $16, %rsp
	subq $16, %rsp
	movq $1, %r10
	movq %r10, -160(%rbp)
	movq -120(%rbp), %rax
	movq -160(%rbp), %rbx
	subq %rbx, %rax
	movq %rax, -152(%rbp)
	movq -152(%rbp), %r10
	movq %r10, -120(%rbp)
	addq $16, %rsp
	addq $16, %rsp
	jmp .L_start_24
.L_end_24:
	subq $16, %rsp
	movq -24(%rbp), %r10
	movq %r10, -136(%rbp)
	movq -112(%rbp), %r10
	movq %r10, -144(%rbp)
	call mod_pow
	addq $16, %rsp
	subq $16, %rsp
	movq %rax, -136(%rbp)
	movq -136(%rbp), %r10
	movq %r10, -128(%rbp)
	addq $16, %rsp
	subq $16, %rsp
	movq -128(%rbp), %r10
	movq %r10, -144(%rbp)
	call print_int
	addq $16, %rsp
	movq $10, %r10
	subq $16, %rsp
	movq %r10, -136(%rbp)
	movq -136(%rbp), %r10
	movq %r10, -144(%rbp)
	call print_char
	addq $16, %rsp
	call flush_output

	movq %rbp, %rsp
	pop %rbp
	ret

)");
