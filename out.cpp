asm(R"(
.section .data
.align 8
MAX_N: .quad 200005
MOD: .quad 1000000007
INF: .quad 1000000000000000000
c: .quad _galloc_array_0

.section .bss
.align 8
_galloc_array_0: .zero 1600040

.section .text
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
	call read_int
	subq $16, %rsp
	movq %rax, -40(%rbp)
	movq -40(%rbp), %r10
	movq %r10, -32(%rbp)
	addq $16, %rsp
	subq $16, %rsp
	movq $0, %r10
	movq %r10, -48(%rbp)
	movq -48(%rbp), %r10
	movq %r10, -40(%rbp)
.L_start_0:
	movq -40(%rbp), %rax
	movq -8(%rbp), %rbx
	cmp %rbx, %rax
	setl %al
	movzbl %al, %eax
	movq %rax, -48(%rbp)
	movq -48(%rbp), %r10
	test %r10, %r10
	jz .L_end_0
	call read_int
	movq %rax, -48(%rbp)
	subq $16, %rsp
	movq $8, %r10
	subq $16, %rsp
	movq %r10, -72(%rbp)
	movq -40(%rbp), %rax
	movq -72(%rbp), %rbx
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -64(%rbp)
	movq c(%rip), %rax
	movq -64(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -56(%rbp)
	movq -56(%rbp), %r11
	movq -48(%rbp), %r10
	movq %r10, (%r11)
	addq $16, %rsp
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
	jmp .L_start_0
.L_end_0:
	subq $16, %rsp
	movq -8(%rbp), %r10
	movq %r10, -56(%rbp)
	movq c(%rip), %r10
	movq %r10, -64(%rbp)
	call quicksort
	addq $16, %rsp
	subq $16, %rsp
	movq -8(%rbp), %rax
	movq -24(%rbp), %rbx
	subq %rbx, %rax
	movq %rax, -56(%rbp)
	movq -56(%rbp), %r10
	movq %r10, -48(%rbp)
	addq $16, %rsp
	subq $16, %rsp
	subq $16, %rsp
	movq -8(%rbp), %rax
	movq -32(%rbp), %rbx
	subq %rbx, %rax
	movq %rax, -72(%rbp)
	movq $1, %r10
	movq %r10, -80(%rbp)
	movq -72(%rbp), %rax
	movq -80(%rbp), %rbx
	addq $16, %rsp
	subq %rbx, %rax
	movq %rax, -64(%rbp)
	movq -64(%rbp), %r10
	movq %r10, -56(%rbp)
	movq -56(%rbp), %r10
	movq %r10, -64(%rbp)
	subq $16, %rsp
	movq -56(%rbp), %r10
	movq %r10, -72(%rbp)
.L_start_1:
	subq $16, %rsp
	movq -64(%rbp), %rax
	movq -48(%rbp), %rbx
	cmp %rbx, %rax
	setg %al
	movzbl %al, %eax
	movq %rax, -88(%rbp)
	subq $16, %rsp
	subq $16, %rsp
	movq $1, %r10
	movq %r10, -128(%rbp)
	movq -64(%rbp), %rax
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
	movq c(%rip), %rax
	movq -112(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -104(%rbp)
	movq -104(%rbp), %r10
	addq $16, %rsp
	subq $16, %rsp
	movq (%r10), %r11
	movq %r11, -104(%rbp)
	subq $16, %rsp
	movq $8, %r10
	movq %r10, -128(%rbp)
	movq -56(%rbp), %rax
	movq -128(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -120(%rbp)
	movq c(%rip), %rax
	movq -120(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -112(%rbp)
	movq -112(%rbp), %r10
	movq (%r10), %r11
	movq %r11, -112(%rbp)
	movq -104(%rbp), %rax
	movq -112(%rbp), %rbx
	addq $16, %rsp
	cmp %rbx, %rax
	sete %al
	movzbl %al, %eax
	movq %rax, -96(%rbp)
	movq -88(%rbp), %rax
	movq -96(%rbp), %rbx
	addq $16, %rsp
	and %rbx, %rax
	movq %rax, -80(%rbp)
	movq -80(%rbp), %r10
	test %r10, %r10
	jz .L_end_1
	movq $1, %r10
	subq $16, %rsp
	movq %r10, -88(%rbp)
	movq -64(%rbp), %rax
	movq -88(%rbp), %rbx
	addq $16, %rsp
	subq %rbx, %rax
	movq %rax, -80(%rbp)
	movq -80(%rbp), %r10
	movq %r10, -64(%rbp)
	jmp .L_start_1
.L_end_1:
.L_start_2:
	subq $16, %rsp
	movq $1, %r10
	subq $16, %rsp
	movq %r10, -104(%rbp)
	movq -72(%rbp), %rax
	movq -104(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -96(%rbp)
	movq -96(%rbp), %rax
	movq -8(%rbp), %rbx
	cmp %rbx, %rax
	setl %al
	movzbl %al, %eax
	movq %rax, -88(%rbp)
	subq $16, %rsp
	subq $16, %rsp
	movq $1, %r10
	movq %r10, -128(%rbp)
	movq -72(%rbp), %rax
	movq -128(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -120(%rbp)
	movq $8, %r10
	movq %r10, -128(%rbp)
	movq -120(%rbp), %rax
	movq -128(%rbp), %rbx
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -112(%rbp)
	movq c(%rip), %rax
	movq -112(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -104(%rbp)
	movq -104(%rbp), %r10
	addq $16, %rsp
	subq $16, %rsp
	movq (%r10), %r11
	movq %r11, -104(%rbp)
	subq $16, %rsp
	movq $8, %r10
	movq %r10, -128(%rbp)
	movq -56(%rbp), %rax
	movq -128(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -120(%rbp)
	movq c(%rip), %rax
	movq -120(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -112(%rbp)
	movq -112(%rbp), %r10
	movq (%r10), %r11
	movq %r11, -112(%rbp)
	movq -104(%rbp), %rax
	movq -112(%rbp), %rbx
	addq $16, %rsp
	cmp %rbx, %rax
	sete %al
	movzbl %al, %eax
	movq %rax, -96(%rbp)
	movq -88(%rbp), %rax
	movq -96(%rbp), %rbx
	addq $16, %rsp
	and %rbx, %rax
	movq %rax, -80(%rbp)
	movq -80(%rbp), %r10
	test %r10, %r10
	jz .L_end_2
	movq $1, %r10
	subq $16, %rsp
	movq %r10, -88(%rbp)
	movq -72(%rbp), %rax
	movq -88(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -80(%rbp)
	movq -80(%rbp), %r10
	movq %r10, -72(%rbp)
	jmp .L_start_2
.L_end_2:
	movq $0, %r10
	subq $16, %rsp
	movq %r10, -88(%rbp)
	movq -88(%rbp), %r10
	movq %r10, -80(%rbp)
	addq $16, %rsp
	subq $16, %rsp
	movq $0, %r10
	movq %r10, -96(%rbp)
	movq -96(%rbp), %r10
	movq %r10, -88(%rbp)
	subq $16, %rsp
	movq $8, %r10
	subq $16, %rsp
	movq %r10, -120(%rbp)
	movq -56(%rbp), %rax
	movq -120(%rbp), %rbx
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -112(%rbp)
	movq c(%rip), %rax
	movq -112(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -104(%rbp)
	movq -104(%rbp), %r10
	addq $16, %rsp
	subq $16, %rsp
	movq (%r10), %r11
	movq %r11, -104(%rbp)
	movq -104(%rbp), %r10
	movq %r10, -96(%rbp)
	addq $16, %rsp
.L_start_3:
	subq $16, %rsp
	movq $1, %r10
	movq %r10, -112(%rbp)
	movq $1, %r10
	subq $16, %rsp
	movq %r10, -120(%rbp)
	movq -112(%rbp), %rax
	movq -120(%rbp), %rbx
	addq $16, %rsp
	cmp %rbx, %rax
	sete %al
	movzbl %al, %eax
	movq %rax, -104(%rbp)
	movq -104(%rbp), %r10
	addq $16, %rsp
	test %r10, %r10
	jz .L_end_3
	subq $16, %rsp
	subq $16, %rsp
	movq -72(%rbp), %rax
	movq -64(%rbp), %rbx
	subq %rbx, %rax
	movq %rax, -120(%rbp)
	movq $1, %r10
	movq %r10, -128(%rbp)
	movq -120(%rbp), %rax
	movq -128(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -112(%rbp)
	movq -112(%rbp), %r10
	movq %r10, -104(%rbp)
	subq $16, %rsp
	movq -56(%rbp), %rax
	movq -64(%rbp), %rbx
	subq %rbx, %rax
	movq %rax, -128(%rbp)
	movq $1, %r10
	subq $16, %rsp
	movq %r10, -136(%rbp)
	movq -128(%rbp), %rax
	movq -136(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -120(%rbp)
	movq -120(%rbp), %r10
	movq %r10, -112(%rbp)
	addq $16, %rsp
	subq $16, %rsp
	movq INF(%rip), %r10
	movq %r10, -120(%rbp)
	subq $16, %rsp
	movq $1, %r10
	movq %r10, -144(%rbp)
	movq -72(%rbp), %rax
	movq -144(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -136(%rbp)
	movq -136(%rbp), %rax
	movq -8(%rbp), %rbx
	addq $16, %rsp
	cmp %rbx, %rax
	setl %al
	movzbl %al, %eax
	movq %rax, -128(%rbp)
	movq -128(%rbp), %r10
	test %r10, %r10
	jz .L_else_4
	subq $16, %rsp
	subq $16, %rsp
	movq $1, %r10
	subq $16, %rsp
	movq %r10, -168(%rbp)
	movq -72(%rbp), %rax
	movq -168(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -160(%rbp)
	movq $8, %r10
	subq $16, %rsp
	movq %r10, -168(%rbp)
	movq -160(%rbp), %rax
	movq -168(%rbp), %rbx
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -152(%rbp)
	movq c(%rip), %rax
	movq -152(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -144(%rbp)
	movq -144(%rbp), %r10
	movq (%r10), %r11
	movq %r11, -144(%rbp)
	movq -144(%rbp), %rax
	movq -96(%rbp), %rbx
	subq %rbx, %rax
	movq %rax, -136(%rbp)
	movq -136(%rbp), %r10
	movq %r10, -128(%rbp)
	addq $16, %rsp
	subq $16, %rsp
	subq $16, %rsp
	movq -128(%rbp), %rax
	movq -104(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -152(%rbp)
	movq -152(%rbp), %rax
	movq -88(%rbp), %rbx
	addq $16, %rsp
	subq %rbx, %rax
	movq %rax, -144(%rbp)
	movq -144(%rbp), %r10
	movq %r10, -136(%rbp)
	subq $16, %rsp
	movq -112(%rbp), %r10
	movq %r10, -152(%rbp)
	movq -136(%rbp), %r10
	movq %r10, -160(%rbp)
	call ceil_div
	addq $16, %rsp
	movq %rax, -144(%rbp)
	movq -144(%rbp), %r10
	movq %r10, -120(%rbp)
	addq $16, %rsp
	jmp .L_end_4
.L_else_4:
.L_end_4:
	movq INF(%rip), %r10
	movq %r10, -128(%rbp)
	subq $16, %rsp
	movq -64(%rbp), %rax
	movq -48(%rbp), %rbx
	cmp %rbx, %rax
	setg %al
	movzbl %al, %eax
	movq %rax, -144(%rbp)
	subq $16, %rsp
	movq -56(%rbp), %rax
	movq -72(%rbp), %rbx
	cmp %rbx, %rax
	setne %al
	movzbl %al, %eax
	movq %rax, -152(%rbp)
	movq -144(%rbp), %rax
	movq -152(%rbp), %rbx
	addq $16, %rsp
	and %rbx, %rax
	movq %rax, -136(%rbp)
	movq -136(%rbp), %r10
	addq $16, %rsp
	test %r10, %r10
	jz .L_else_5
	subq $16, %rsp
	subq $16, %rsp
	subq $16, %rsp
	subq $16, %rsp
	movq $1, %r10
	subq $16, %rsp
	movq %r10, -200(%rbp)
	movq -64(%rbp), %rax
	movq -200(%rbp), %rbx
	addq $16, %rsp
	subq %rbx, %rax
	movq %rax, -192(%rbp)
	movq $8, %r10
	subq $16, %rsp
	movq %r10, -200(%rbp)
	movq -192(%rbp), %rax
	movq -200(%rbp), %rbx
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -184(%rbp)
	movq c(%rip), %rax
	movq -184(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -176(%rbp)
	movq -176(%rbp), %r10
	movq (%r10), %r11
	movq %r11, -176(%rbp)
	movq -176(%rbp), %rax
	movq -80(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -168(%rbp)
	movq -96(%rbp), %rax
	movq -168(%rbp), %rbx
	addq $16, %rsp
	subq %rbx, %rax
	movq %rax, -160(%rbp)
	movq -104(%rbp), %rax
	movq -160(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -152(%rbp)
	movq -152(%rbp), %rax
	movq -88(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -144(%rbp)
	movq -144(%rbp), %r10
	movq %r10, -136(%rbp)
	subq $16, %rsp
	movq -72(%rbp), %rax
	movq -56(%rbp), %rbx
	subq %rbx, %rax
	movq %rax, -152(%rbp)
	movq -152(%rbp), %r10
	movq %r10, -144(%rbp)
	addq $16, %rsp
	subq $16, %rsp
	movq -136(%rbp), %rax
	movq -144(%rbp), %rbx
	cqto
	idivq %rbx
	movq %rax, -152(%rbp)
	movq -152(%rbp), %r10
	movq %r10, -128(%rbp)
	addq $16, %rsp
	addq $16, %rsp
	jmp .L_end_5
.L_else_5:
.L_end_5:
	subq $16, %rsp
	subq $16, %rsp
	movq -128(%rbp), %r10
	movq %r10, -152(%rbp)
	movq -120(%rbp), %r10
	movq %r10, -160(%rbp)
	call min
	addq $16, %rsp
	movq %rax, -144(%rbp)
	movq -144(%rbp), %r10
	movq %r10, -136(%rbp)
	subq $16, %rsp
	movq -80(%rbp), %rax
	movq -136(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -152(%rbp)
	movq -152(%rbp), %rax
	movq -16(%rbp), %rbx
	addq $16, %rsp
	cmp %rbx, %rax
	setg %al
	movzbl %al, %eax
	movq %rax, -144(%rbp)
	movq -144(%rbp), %r10
	test %r10, %r10
	jz .L_else_6
	addq $16, %rsp
	addq $16, %rsp
	addq $16, %rsp
	jmp .L_end_3
	jmp .L_end_6
.L_else_6:
.L_end_6:
	subq $16, %rsp
	movq -136(%rbp), %rax
	movq -112(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -160(%rbp)
	movq -160(%rbp), %rax
	movq -88(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -152(%rbp)
	movq -152(%rbp), %r10
	movq %r10, -144(%rbp)
	addq $16, %rsp
	subq $16, %rsp
	movq -144(%rbp), %rax
	movq -104(%rbp), %rbx
	cqto
	idivq %rbx
	movq %rax, -160(%rbp)
	movq -96(%rbp), %rax
	movq -160(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -152(%rbp)
	movq -152(%rbp), %r10
	movq %r10, -96(%rbp)
	addq $16, %rsp
	subq $16, %rsp
	movq -144(%rbp), %rax
	movq -104(%rbp), %rbx
	cqto
	idivq %rbx
	movq %rdx, -152(%rbp)
	movq -152(%rbp), %r10
	movq %r10, -88(%rbp)
	addq $16, %rsp
	subq $16, %rsp
	movq -80(%rbp), %rax
	movq -136(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -152(%rbp)
	movq -152(%rbp), %r10
	movq %r10, -80(%rbp)
	addq $16, %rsp
.L_start_7:
	subq $16, %rsp
	subq $16, %rsp
	movq $1, %r10
	movq %r10, -176(%rbp)
	movq -72(%rbp), %rax
	movq -176(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -168(%rbp)
	movq -168(%rbp), %rax
	movq -8(%rbp), %rbx
	addq $16, %rsp
	cmp %rbx, %rax
	setl %al
	movzbl %al, %eax
	movq %rax, -160(%rbp)
	subq $16, %rsp
	subq $16, %rsp
	movq $1, %r10
	subq $16, %rsp
	movq %r10, -200(%rbp)
	movq -72(%rbp), %rax
	movq -200(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -192(%rbp)
	movq $8, %r10
	subq $16, %rsp
	movq %r10, -200(%rbp)
	movq -192(%rbp), %rax
	movq -200(%rbp), %rbx
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -184(%rbp)
	movq c(%rip), %rax
	movq -184(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -176(%rbp)
	movq -176(%rbp), %r10
	movq (%r10), %r11
	movq %r11, -176(%rbp)
	movq -176(%rbp), %rax
	movq -96(%rbp), %rbx
	cmp %rbx, %rax
	sete %al
	movzbl %al, %eax
	movq %rax, -168(%rbp)
	movq -160(%rbp), %rax
	movq -168(%rbp), %rbx
	addq $16, %rsp
	and %rbx, %rax
	movq %rax, -152(%rbp)
	movq -152(%rbp), %r10
	addq $16, %rsp
	test %r10, %r10
	jz .L_end_7
	subq $16, %rsp
	movq $1, %r10
	movq %r10, -160(%rbp)
	movq -72(%rbp), %rax
	movq -160(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -152(%rbp)
	movq -152(%rbp), %r10
	movq %r10, -72(%rbp)
	addq $16, %rsp
	jmp .L_start_7
.L_end_7:
.L_start_8:
	subq $16, %rsp
	movq -64(%rbp), %rax
	movq -48(%rbp), %rbx
	cmp %rbx, %rax
	setg %al
	movzbl %al, %eax
	movq %rax, -160(%rbp)
	subq $16, %rsp
	subq $16, %rsp
	subq $16, %rsp
	movq $1, %r10
	movq %r10, -208(%rbp)
	movq -64(%rbp), %rax
	movq -208(%rbp), %rbx
	subq %rbx, %rax
	movq %rax, -200(%rbp)
	movq $8, %r10
	movq %r10, -208(%rbp)
	movq -200(%rbp), %rax
	movq -208(%rbp), %rbx
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -192(%rbp)
	movq c(%rip), %rax
	movq -192(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -184(%rbp)
	movq -184(%rbp), %r10
	addq $16, %rsp
	subq $16, %rsp
	movq (%r10), %r11
	movq %r11, -184(%rbp)
	movq -184(%rbp), %rax
	movq -80(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -176(%rbp)
	movq -176(%rbp), %rax
	movq -96(%rbp), %rbx
	cmp %rbx, %rax
	sete %al
	movzbl %al, %eax
	movq %rax, -168(%rbp)
	movq -160(%rbp), %rax
	movq -168(%rbp), %rbx
	addq $16, %rsp
	and %rbx, %rax
	movq %rax, -152(%rbp)
	movq -152(%rbp), %r10
	addq $16, %rsp
	test %r10, %r10
	jz .L_end_8
	subq $16, %rsp
	movq $1, %r10
	movq %r10, -160(%rbp)
	movq -64(%rbp), %rax
	movq -160(%rbp), %rbx
	subq %rbx, %rax
	movq %rax, -152(%rbp)
	movq -152(%rbp), %r10
	movq %r10, -64(%rbp)
	addq $16, %rsp
	jmp .L_start_8
.L_end_8:
	addq $16, %rsp
	addq $16, %rsp
	addq $16, %rsp
	jmp .L_start_3
.L_end_3:
	subq $16, %rsp
	subq $16, %rsp
	movq -72(%rbp), %rax
	movq -64(%rbp), %rbx
	subq %rbx, %rax
	movq %rax, -120(%rbp)
	movq $1, %r10
	movq %r10, -128(%rbp)
	movq -120(%rbp), %rax
	movq -128(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -112(%rbp)
	movq -112(%rbp), %r10
	movq %r10, -104(%rbp)
	subq $16, %rsp
	movq -56(%rbp), %rax
	movq -64(%rbp), %rbx
	subq %rbx, %rax
	movq %rax, -128(%rbp)
	movq $1, %r10
	subq $16, %rsp
	movq %r10, -136(%rbp)
	movq -128(%rbp), %rax
	movq -136(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -120(%rbp)
	movq -120(%rbp), %r10
	movq %r10, -112(%rbp)
	addq $16, %rsp
	subq $16, %rsp
	movq -16(%rbp), %rax
	movq -80(%rbp), %rbx
	subq %rbx, %rax
	movq %rax, -128(%rbp)
	movq -128(%rbp), %r10
	movq %r10, -120(%rbp)
	subq $16, %rsp
	subq $16, %rsp
	movq -120(%rbp), %rax
	movq -112(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -152(%rbp)
	movq -152(%rbp), %rax
	movq -88(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -144(%rbp)
	movq -144(%rbp), %rax
	movq -104(%rbp), %rbx
	cqto
	idivq %rbx
	movq %rax, -136(%rbp)
	movq -136(%rbp), %r10
	movq %r10, -128(%rbp)
	addq $16, %rsp
	subq $16, %rsp
	subq $16, %rsp
	movq -120(%rbp), %rax
	movq -112(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -160(%rbp)
	movq -160(%rbp), %rax
	movq -88(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -152(%rbp)
	movq -128(%rbp), %rax
	movq -104(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -160(%rbp)
	movq -152(%rbp), %rax
	movq -160(%rbp), %rbx
	addq $16, %rsp
	subq %rbx, %rax
	movq %rax, -144(%rbp)
	movq -144(%rbp), %r10
	movq %r10, -136(%rbp)
	movq -96(%rbp), %rax
	movq -128(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -144(%rbp)
	movq -144(%rbp), %r10
	movq %r10, -96(%rbp)
	movq -136(%rbp), %r10
	movq %r10, -88(%rbp)
	movq -16(%rbp), %r10
	movq %r10, -80(%rbp)
	movq -48(%rbp), %r10
	movq %r10, -40(%rbp)
.L_start_9:
	movq -40(%rbp), %rax
	movq -64(%rbp), %rbx
	cmp %rbx, %rax
	setl %al
	movzbl %al, %eax
	movq %rax, -144(%rbp)
	movq -144(%rbp), %r10
	test %r10, %r10
	jz .L_end_9
	subq $16, %rsp
	movq $8, %r10
	subq $16, %rsp
	movq %r10, -168(%rbp)
	movq -40(%rbp), %rax
	movq -168(%rbp), %rbx
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -160(%rbp)
	movq c(%rip), %rax
	movq -160(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -152(%rbp)
	movq -152(%rbp), %r10
	addq $16, %rsp
	subq $16, %rsp
	movq (%r10), %r11
	movq %r11, -152(%rbp)
	movq -152(%rbp), %rax
	movq -16(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -144(%rbp)
	subq $16, %rsp
	movq $8, %r10
	subq $16, %rsp
	movq %r10, -168(%rbp)
	movq -40(%rbp), %rax
	movq -168(%rbp), %rbx
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -160(%rbp)
	movq c(%rip), %rax
	movq -160(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -152(%rbp)
	movq -152(%rbp), %r11
	movq -144(%rbp), %r10
	movq %r10, (%r11)
	addq $16, %rsp
	subq $16, %rsp
	movq $1, %r10
	movq %r10, -160(%rbp)
	movq -40(%rbp), %rax
	movq -160(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -152(%rbp)
	movq -152(%rbp), %r10
	movq %r10, -40(%rbp)
	addq $16, %rsp
	jmp .L_start_9
.L_end_9:
	movq -64(%rbp), %r10
	movq %r10, -40(%rbp)
.L_start_10:
	movq -40(%rbp), %rax
	movq -72(%rbp), %rbx
	cmp %rbx, %rax
	setle %al
	movzbl %al, %eax
	movq %rax, -144(%rbp)
	movq -144(%rbp), %r10
	test %r10, %r10
	jz .L_end_10
	subq $16, %rsp
	movq -72(%rbp), %rax
	movq -40(%rbp), %rbx
	subq %rbx, %rax
	movq %rax, -152(%rbp)
	movq -152(%rbp), %rax
	movq -88(%rbp), %rbx
	addq $16, %rsp
	cmp %rbx, %rax
	setl %al
	movzbl %al, %eax
	movq %rax, -144(%rbp)
	movq -144(%rbp), %r10
	test %r10, %r10
	jz .L_else_11
	movq $1, %r10
	subq $16, %rsp
	movq %r10, -152(%rbp)
	movq -96(%rbp), %rax
	movq -152(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -144(%rbp)
	subq $16, %rsp
	movq $8, %r10
	subq $16, %rsp
	movq %r10, -168(%rbp)
	movq -40(%rbp), %rax
	movq -168(%rbp), %rbx
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -160(%rbp)
	movq c(%rip), %rax
	movq -160(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -152(%rbp)
	movq -152(%rbp), %r11
	movq -144(%rbp), %r10
	movq %r10, (%r11)
	addq $16, %rsp
	jmp .L_end_11
.L_else_11:
	subq $16, %rsp
	movq $8, %r10
	movq %r10, -160(%rbp)
	movq -40(%rbp), %rax
	movq -160(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -152(%rbp)
	movq c(%rip), %rax
	movq -152(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -144(%rbp)
	movq -144(%rbp), %r11
	movq -96(%rbp), %r10
	movq %r10, (%r11)
.L_end_11:
	movq $1, %r10
	subq $16, %rsp
	movq %r10, -152(%rbp)
	movq -40(%rbp), %rax
	movq -152(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -144(%rbp)
	movq -144(%rbp), %r10
	movq %r10, -40(%rbp)
	jmp .L_start_10
.L_end_10:
	movq $0, %r10
	subq $16, %rsp
	movq %r10, -152(%rbp)
	movq -152(%rbp), %r10
	movq %r10, -144(%rbp)
	addq $16, %rsp
	movq $0, %r10
	subq $16, %rsp
	movq %r10, -152(%rbp)
	movq -152(%rbp), %r10
	movq %r10, -40(%rbp)
	addq $16, %rsp
.L_start_12:
	subq $16, %rsp
	movq -40(%rbp), %rax
	movq -8(%rbp), %rbx
	cmp %rbx, %rax
	setl %al
	movzbl %al, %eax
	movq %rax, -152(%rbp)
	movq -152(%rbp), %r10
	addq $16, %rsp
	test %r10, %r10
	jz .L_end_12
	subq $16, %rsp
	subq $16, %rsp
	movq $8, %r10
	subq $16, %rsp
	movq %r10, -184(%rbp)
	movq -40(%rbp), %rax
	movq -184(%rbp), %rbx
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -176(%rbp)
	movq c(%rip), %rax
	movq -176(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -168(%rbp)
	movq -168(%rbp), %r10
	addq $16, %rsp
	subq $16, %rsp
	movq (%r10), %r11
	movq %r11, -168(%rbp)
	movq -168(%rbp), %rax
	movq MOD(%rip), %rbx
	addq $16, %rsp
	cqto
	idivq %rbx
	movq %rdx, -160(%rbp)
	movq -160(%rbp), %r10
	movq %r10, -152(%rbp)
	subq $16, %rsp
	subq $16, %rsp
	movq -152(%rbp), %rax
	movq -152(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -184(%rbp)
	movq -184(%rbp), %rax
	movq MOD(%rip), %rbx
	addq $16, %rsp
	cqto
	idivq %rbx
	movq %rdx, -176(%rbp)
	movq -144(%rbp), %rax
	movq -176(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -168(%rbp)
	movq -168(%rbp), %rax
	movq MOD(%rip), %rbx
	addq $16, %rsp
	cqto
	idivq %rbx
	movq %rdx, -160(%rbp)
	movq -160(%rbp), %r10
	movq %r10, -144(%rbp)
	movq $1, %r10
	subq $16, %rsp
	movq %r10, -168(%rbp)
	movq -40(%rbp), %rax
	movq -168(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -160(%rbp)
	movq -160(%rbp), %r10
	movq %r10, -40(%rbp)
	addq $16, %rsp
	jmp .L_start_12
.L_end_12:
	subq $16, %rsp
	movq -144(%rbp), %r10
	movq %r10, -160(%rbp)
	call print_int
	addq $16, %rsp
	movq $10, %r10
	subq $16, %rsp
	movq %r10, -152(%rbp)
	movq -152(%rbp), %r10
	movq %r10, -160(%rbp)
	call print_char
	addq $16, %rsp
	call flush_output

	movq %rbp, %rsp
	pop %rbp
	ret

.section .data
.align 8
READ_BUFFER_CAP: .quad 5242880
WRITE_BUFFER_CAP: .quad 32768
input_buffer: .quad _galloc_array_1
input_index: .quad 0
output_buffer: .quad _galloc_array_2
output_index: .quad 0

.section .bss
.align 8
_galloc_array_1: .zero 5242880
_galloc_array_2: .zero 32768

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
	jz .L_else_13
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
	jmp .L_end_13
.L_else_13:
.L_end_13:

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
	jz .L_else_14
	movq $0, %r10
	subq $16, %rsp
	movq %r10, -8(%rbp)
	movq -8(%rbp), %rax

	movq %rbp, %rsp
	pop %rbp
	ret

	addq $16, %rsp
	jmp .L_end_14
.L_else_14:
.L_end_14:
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
	jz .L_else_15
	call flush_output
	jmp .L_end_15
.L_else_15:
.L_end_15:

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
.L_start_16:
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
	jz .L_end_16
	call read_char
	movq %rax, -32(%rbp)
	movq -32(%rbp), %r10
	movq %r10, -8(%rbp)
	jmp .L_start_16
.L_end_16:
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
	jz .L_else_17
	movq $1, %r10
	movq %r10, -32(%rbp)
	movq -32(%rbp), %r10
	movq %r10, -24(%rbp)
	call read_char
	movq %rax, -32(%rbp)
	movq -32(%rbp), %r10
	movq %r10, -8(%rbp)
	jmp .L_end_17
.L_else_17:
.L_end_17:
.L_start_18:
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
	jz .L_end_18
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
	jmp .L_start_18
.L_end_18:
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
	jz .L_else_19
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

	jmp .L_end_19
.L_else_19:
.L_end_19:
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
	jz .L_else_20
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
	jmp .L_end_20
.L_else_20:
.L_end_20:
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
	jz .L_else_21
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
	jmp .L_end_21
.L_else_21:
.L_end_21:
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
.L_start_22:
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
	jz .L_end_22
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
	jmp .L_start_22
.L_end_22:
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
	jz .L_else_23
	movq $45, %r10
	movq %r10, -192(%rbp)
	subq $16, %rsp
	movq -192(%rbp), %r10
	movq %r10, -208(%rbp)
	call print_char
	addq $16, %rsp
	jmp .L_end_23
.L_else_23:
.L_end_23:
.L_start_24:
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
	jz .L_end_24
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
	jmp .L_start_24
.L_end_24:

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
.L_start_25:
	movq -8(%rbp), %rax
	movq 24(%rbp), %rbx
	cmp %rbx, %rax
	setl %al
	movzbl %al, %eax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %r10
	test %r10, %r10
	jz .L_end_25
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
	jz .L_else_26
	jmp .L_end_25
	jmp .L_end_26
.L_else_26:
.L_end_26:
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
	jz .L_else_27
	jmp .L_start_25
	jmp .L_end_27
.L_else_27:
.L_end_27:
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
	jmp .L_start_25
.L_end_25:

	movq %rbp, %rsp
	pop %rbp
	ret

.section .data
.align 8
HEAP_CAP: .quad 16777216
HEAP: .quad _galloc_array_3
heap_top: .quad 0
ALIGN: .quad 8
HDR: .quad 8

.section .bss
.align 8
_galloc_array_3: .zero 16777216

.section .text
.global align_up
align_up:
	push %rbp
	movq %rsp, %rbp

	subq $16, %rsp
	subq $16, %rsp
	movq 16(%rbp), %rax
	movq 24(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -24(%rbp)
	movq $1, %r10
	movq %r10, -32(%rbp)
	movq -24(%rbp), %rax
	movq -32(%rbp), %rbx
	addq $16, %rsp
	subq %rbx, %rax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %r10
	movq %r10, -8(%rbp)
	subq $16, %rsp
	movq -8(%rbp), %rax
	movq 24(%rbp), %rbx
	cqto
	idivq %rbx
	movq %rdx, -24(%rbp)
	movq -8(%rbp), %rax
	movq -24(%rbp), %rbx
	addq $16, %rsp
	subq %rbx, %rax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %rax

	movq %rbp, %rsp
	pop %rbp
	ret


	movq %rbp, %rsp
	pop %rbp
	ret

.global memcpy
memcpy:
	push %rbp
	movq %rsp, %rbp

	subq $16, %rsp
	movq $0, %r10
	movq %r10, -16(%rbp)
	movq -16(%rbp), %r10
	movq %r10, -8(%rbp)
.L_start_28:
	movq -8(%rbp), %rax
	movq 32(%rbp), %rbx
	cmp %rbx, %rax
	setl %al
	movzbl %al, %eax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %r10
	test %r10, %r10
	jz .L_end_28
	subq $16, %rsp
	movq $1, %r10
	movq %r10, -32(%rbp)
	movq -8(%rbp), %rax
	movq -32(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -24(%rbp)
	movq 24(%rbp), %rax
	movq -24(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %r10
	movzbq (%r10), %r11
	movb %r11b, -9(%rbp)
	subq $16, %rsp
	movq $1, %r10
	subq $16, %rsp
	movq %r10, -33(%rbp)
	movq -8(%rbp), %rax
	movq -33(%rbp), %rbx
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -25(%rbp)
	movq 16(%rbp), %rax
	movq -25(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -17(%rbp)
	movq -17(%rbp), %r11
	movzbq -9(%rbp), %r10
	movb %r10b, (%r11)
	addq $16, %rsp
	subq $16, %rsp
	movq $1, %r10
	movq %r10, -25(%rbp)
	movq -8(%rbp), %rax
	movq -25(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -17(%rbp)
	movq -17(%rbp), %r10
	movq %r10, -8(%rbp)
	addq $16, %rsp
	jmp .L_start_28
.L_end_28:

	movq %rbp, %rsp
	pop %rbp
	ret

.global malloc
malloc:
	push %rbp
	movq %rsp, %rbp

	subq $16, %rsp
	movq $0, %r10
	movq %r10, -16(%rbp)
	movq 16(%rbp), %rax
	movq -16(%rbp), %rbx
	cmp %rbx, %rax
	setle %al
	movzbl %al, %eax
	movq %rax, -8(%rbp)
	movq -8(%rbp), %r10
	addq $16, %rsp
	test %r10, %r10
	jz .L_else_29
	movq $0, %r10
	subq $16, %rsp
	movq %r10, -8(%rbp)
	movq -8(%rbp), %rax

	movq %rbp, %rsp
	pop %rbp
	ret

	addq $16, %rsp
	jmp .L_end_29
.L_else_29:
.L_end_29:
	subq $16, %rsp
	subq $16, %rsp
	movq ALIGN(%rip), %r10
	movq %r10, -24(%rbp)
	movq heap_top(%rip), %r10
	movq %r10, -32(%rbp)
	call align_up
	addq $16, %rsp
	movq %rax, -16(%rbp)
	movq -16(%rbp), %r10
	movq %r10, -8(%rbp)
	subq $16, %rsp
	movq HDR(%rip), %rax
	movq 16(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -24(%rbp)
	movq -24(%rbp), %r10
	movq %r10, -16(%rbp)
	addq $16, %rsp
	subq $16, %rsp
	movq -8(%rbp), %rax
	movq -16(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -32(%rbp)
	movq -32(%rbp), %rax
	movq HEAP_CAP(%rip), %rbx
	cmp %rbx, %rax
	setg %al
	movzbl %al, %eax
	movq %rax, -24(%rbp)
	movq -24(%rbp), %r10
	addq $16, %rsp
	test %r10, %r10
	jz .L_else_30
	movq $0, %r10
	subq $16, %rsp
	movq %r10, -24(%rbp)
	movq -24(%rbp), %rax

	movq %rbp, %rsp
	pop %rbp
	ret

	addq $16, %rsp
	jmp .L_end_30
.L_else_30:
.L_end_30:
	subq $16, %rsp
	subq $16, %rsp
	movq $1, %r10
	movq %r10, -48(%rbp)
	movq -8(%rbp), %rax
	movq -48(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -40(%rbp)
	movq HEAP(%rip), %rax
	movq -40(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -32(%rbp)
	movq -32(%rbp), %r10
	movq %r10, -24(%rbp)
	movq -24(%rbp), %r11
	movq 16(%rbp), %r10
	movq %r10, (%r11)
	movq -8(%rbp), %rax
	movq -16(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -32(%rbp)
	movq -32(%rbp), %r10
	movq %r10, heap_top(%rip)
	subq $16, %rsp
	movq $1, %r10
	subq $16, %rsp
	movq %r10, -56(%rbp)
	movq -8(%rbp), %rax
	movq -56(%rbp), %rbx
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -48(%rbp)
	movq HEAP(%rip), %rax
	movq -48(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -40(%rbp)
	movq $1, %r10
	subq $16, %rsp
	movq %r10, -56(%rbp)
	movq HDR(%rip), %rax
	movq -56(%rbp), %rbx
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -48(%rbp)
	movq -40(%rbp), %rax
	movq -48(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -32(%rbp)
	movq -32(%rbp), %rax

	movq %rbp, %rsp
	pop %rbp
	ret


	movq %rbp, %rsp
	pop %rbp
	ret

.global free
free:
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
	jz .L_else_31
	movq $0, %r10
	subq $16, %rsp
	movq %r10, -8(%rbp)
	movq -8(%rbp), %rax

	movq %rbp, %rsp
	pop %rbp
	ret

	addq $16, %rsp
	jmp .L_end_31
.L_else_31:
.L_end_31:
	subq $16, %rsp
	movq 16(%rbp), %rax
	movq HDR(%rip), %rbx
	subq %rbx, %rax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %r10
	movq %r10, -8(%rbp)
	movq -8(%rbp), %r10
	movq %r10, -16(%rbp)
	subq $16, %rsp
	movq -16(%rbp), %r10
	movq (%r10), %r11
	movq %r11, -32(%rbp)
	movq -32(%rbp), %r10
	movq %r10, -24(%rbp)
	subq $16, %rsp
	movq $1, %r10
	subq $16, %rsp
	movq %r10, -56(%rbp)
	movq -24(%rbp), %rax
	movq -56(%rbp), %rbx
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -48(%rbp)
	movq 16(%rbp), %rax
	movq -48(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -40(%rbp)
	subq $16, %rsp
	movq $1, %r10
	movq %r10, -64(%rbp)
	movq heap_top(%rip), %rax
	movq -64(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -56(%rbp)
	movq HEAP(%rip), %rax
	movq -56(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -48(%rbp)
	movq -40(%rbp), %rax
	movq -48(%rbp), %rbx
	addq $16, %rsp
	cmp %rbx, %rax
	sete %al
	movzbl %al, %eax
	movq %rax, -32(%rbp)
	movq -32(%rbp), %r10
	test %r10, %r10
	jz .L_else_32
	subq $16, %rsp
	movq HDR(%rip), %rax
	movq -24(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -40(%rbp)
	movq heap_top(%rip), %rax
	movq -40(%rbp), %rbx
	addq $16, %rsp
	subq %rbx, %rax
	movq %rax, -32(%rbp)
	movq -32(%rbp), %r10
	movq %r10, heap_top(%rip)
	jmp .L_end_32
.L_else_32:
.L_end_32:

	movq %rbp, %rsp
	pop %rbp
	ret

.global realloc
realloc:
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
	jz .L_else_33
	subq $16, %rsp
	movq 24(%rbp), %r10
	movq %r10, -16(%rbp)
	call malloc
	addq $16, %rsp
	subq $16, %rsp
	movq %rax, -8(%rbp)
	movq -8(%rbp), %rax

	movq %rbp, %rsp
	pop %rbp
	ret

	addq $16, %rsp
	jmp .L_end_33
.L_else_33:
.L_end_33:
	subq $16, %rsp
	movq $0, %r10
	movq %r10, -16(%rbp)
	movq 24(%rbp), %rax
	movq -16(%rbp), %rbx
	cmp %rbx, %rax
	sete %al
	movzbl %al, %eax
	movq %rax, -8(%rbp)
	movq -8(%rbp), %r10
	addq $16, %rsp
	test %r10, %r10
	jz .L_else_34
	subq $16, %rsp
	movq 16(%rbp), %r10
	movq %r10, -16(%rbp)
	call free
	addq $16, %rsp
	movq $0, %r10
	subq $16, %rsp
	movq %r10, -8(%rbp)
	movq -8(%rbp), %rax

	movq %rbp, %rsp
	pop %rbp
	ret

	addq $16, %rsp
	jmp .L_end_34
.L_else_34:
.L_end_34:
	subq $16, %rsp
	movq 16(%rbp), %rax
	movq HDR(%rip), %rbx
	subq %rbx, %rax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %r10
	movq %r10, -8(%rbp)
	movq -8(%rbp), %r10
	movq %r10, -16(%rbp)
	subq $16, %rsp
	movq -16(%rbp), %r10
	movq (%r10), %r11
	movq %r11, -32(%rbp)
	movq -32(%rbp), %r10
	movq %r10, -24(%rbp)
	subq $16, %rsp
	movq $1, %r10
	subq $16, %rsp
	movq %r10, -56(%rbp)
	movq -24(%rbp), %rax
	movq -56(%rbp), %rbx
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -48(%rbp)
	movq 16(%rbp), %rax
	movq -48(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -40(%rbp)
	subq $16, %rsp
	movq $1, %r10
	movq %r10, -64(%rbp)
	movq heap_top(%rip), %rax
	movq -64(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -56(%rbp)
	movq HEAP(%rip), %rax
	movq -56(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -48(%rbp)
	movq -40(%rbp), %rax
	movq -48(%rbp), %rbx
	addq $16, %rsp
	cmp %rbx, %rax
	sete %al
	movzbl %al, %eax
	movq %rax, -32(%rbp)
	movq -32(%rbp), %r10
	test %r10, %r10
	jz .L_else_35
	subq $16, %rsp
	movq HDR(%rip), %rax
	movq -24(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -48(%rbp)
	movq heap_top(%rip), %rax
	movq -48(%rbp), %rbx
	subq %rbx, %rax
	movq %rax, -40(%rbp)
	movq -40(%rbp), %r10
	movq %r10, -32(%rbp)
	addq $16, %rsp
	subq $16, %rsp
	movq HDR(%rip), %rax
	movq 24(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -48(%rbp)
	movq -48(%rbp), %r10
	movq %r10, -40(%rbp)
	subq $16, %rsp
	movq -32(%rbp), %rax
	movq -40(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -56(%rbp)
	movq -56(%rbp), %rax
	movq HEAP_CAP(%rip), %rbx
	addq $16, %rsp
	cmp %rbx, %rax
	setle %al
	movzbl %al, %eax
	movq %rax, -48(%rbp)
	movq -48(%rbp), %r10
	test %r10, %r10
	jz .L_else_36
	subq $16, %rsp
	movq $1, %r10
	subq $16, %rsp
	movq %r10, -72(%rbp)
	movq -32(%rbp), %rax
	movq -72(%rbp), %rbx
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -64(%rbp)
	movq HEAP(%rip), %rax
	movq -64(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -56(%rbp)
	movq -56(%rbp), %r10
	movq %r10, -48(%rbp)
	addq $16, %rsp
	movq -48(%rbp), %r11
	movq 24(%rbp), %r10
	movq %r10, (%r11)
	subq $16, %rsp
	movq -32(%rbp), %rax
	movq -40(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -56(%rbp)
	movq -56(%rbp), %r10
	movq %r10, heap_top(%rip)
	addq $16, %rsp
	subq $16, %rsp
	subq $16, %rsp
	movq $1, %r10
	movq %r10, -80(%rbp)
	movq -32(%rbp), %rax
	movq -80(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -72(%rbp)
	movq HEAP(%rip), %rax
	movq -72(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -64(%rbp)
	subq $16, %rsp
	movq $1, %r10
	movq %r10, -80(%rbp)
	movq HDR(%rip), %rax
	movq -80(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -72(%rbp)
	movq -64(%rbp), %rax
	movq -72(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -56(%rbp)
	movq -56(%rbp), %rax

	movq %rbp, %rsp
	pop %rbp
	ret

	addq $16, %rsp
	jmp .L_end_36
.L_else_36:
.L_end_36:
	addq $16, %rsp
	jmp .L_end_35
.L_else_35:
.L_end_35:
	subq $16, %rsp
	movq 24(%rbp), %r10
	movq %r10, -48(%rbp)
	call malloc
	addq $16, %rsp
	subq $16, %rsp
	movq %rax, -40(%rbp)
	movq -40(%rbp), %r10
	movq %r10, -32(%rbp)
	addq $16, %rsp
	subq $16, %rsp
	movq $0, %r10
	movq %r10, -48(%rbp)
	movq -32(%rbp), %rax
	movq -48(%rbp), %rbx
	cmp %rbx, %rax
	sete %al
	movzbl %al, %eax
	movq %rax, -40(%rbp)
	movq -40(%rbp), %r10
	addq $16, %rsp
	test %r10, %r10
	jz .L_else_37
	movq $0, %r10
	subq $16, %rsp
	movq %r10, -40(%rbp)
	movq -40(%rbp), %rax

	movq %rbp, %rsp
	pop %rbp
	ret

	addq $16, %rsp
	jmp .L_end_37
.L_else_37:
.L_end_37:
	subq $16, %rsp
	movq 24(%rbp), %r10
	movq %r10, -40(%rbp)
	movq -24(%rbp), %r10
	movq %r10, -48(%rbp)
	call min
	addq $16, %rsp
	subq $16, %rsp
	movq %rax, -40(%rbp)
	subq $16, %rsp
	movq -40(%rbp), %r10
	movq %r10, -48(%rbp)
	movq 16(%rbp), %r10
	movq %r10, -56(%rbp)
	movq -32(%rbp), %r10
	movq %r10, -64(%rbp)
	call memcpy
	addq $16, %rsp
	addq $16, %rsp
	subq $16, %rsp
	movq 16(%rbp), %r10
	movq %r10, -48(%rbp)
	call free
	addq $16, %rsp
	movq -32(%rbp), %rax

	movq %rbp, %rsp
	pop %rbp
	ret


	movq %rbp, %rsp
	pop %rbp
	ret

.global arena_reset
arena_reset:
	push %rbp
	movq %rsp, %rbp

	movq $0, %r10
	subq $16, %rsp
	movq %r10, -8(%rbp)
	movq -8(%rbp), %r10
	movq %r10, heap_top(%rip)
	addq $16, %rsp

	movq %rbp, %rsp
	pop %rbp
	ret

.section .data
.align 8

.section .bss
.align 8

.section .text
.global swap
swap:
	push %rbp
	movq %rsp, %rbp

	subq $16, %rsp
	movq 16(%rbp), %r10
	movq (%r10), %r11
	movq %r11, -16(%rbp)
	movq -16(%rbp), %r10
	movq %r10, -8(%rbp)
	movq 24(%rbp), %r10
	movq (%r10), %r11
	movq %r11, -16(%rbp)
	movq 16(%rbp), %r11
	movq -16(%rbp), %r10
	movq %r10, (%r11)
	movq 24(%rbp), %r11
	movq -8(%rbp), %r10
	movq %r10, (%r11)

	movq %rbp, %rsp
	pop %rbp
	ret

.global qsort_rec
qsort_rec:
	push %rbp
	movq %rsp, %rbp

	subq $16, %rsp
	movq 24(%rbp), %rax
	movq 32(%rbp), %rbx
	cmp %rbx, %rax
	setge %al
	movzbl %al, %eax
	movq %rax, -8(%rbp)
	movq -8(%rbp), %r10
	addq $16, %rsp
	test %r10, %r10
	jz .L_else_38
	movq $0, %r10
	subq $16, %rsp
	movq %r10, -8(%rbp)
	movq -8(%rbp), %rax

	movq %rbp, %rsp
	pop %rbp
	ret

	addq $16, %rsp
	jmp .L_end_38
.L_else_38:
.L_end_38:
	subq $16, %rsp
	movq 24(%rbp), %r10
	movq %r10, -8(%rbp)
	movq 32(%rbp), %r10
	movq %r10, -16(%rbp)
	subq $16, %rsp
	subq $16, %rsp
	movq 32(%rbp), %rax
	movq 24(%rbp), %rbx
	subq %rbx, %rax
	movq %rax, -48(%rbp)
	movq $2, %r10
	subq $16, %rsp
	movq %r10, -56(%rbp)
	movq -48(%rbp), %rax
	movq -56(%rbp), %rbx
	addq $16, %rsp
	cqto
	idivq %rbx
	movq %rax, -40(%rbp)
	movq 24(%rbp), %rax
	movq -40(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -32(%rbp)
	movq -32(%rbp), %r10
	movq %r10, -24(%rbp)
	subq $16, %rsp
	movq $8, %r10
	subq $16, %rsp
	movq %r10, -56(%rbp)
	movq -24(%rbp), %rax
	movq -56(%rbp), %rbx
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -48(%rbp)
	movq 16(%rbp), %rax
	movq -48(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -40(%rbp)
	movq -40(%rbp), %r10
	addq $16, %rsp
	subq $16, %rsp
	movq (%r10), %r11
	movq %r11, -40(%rbp)
	movq -40(%rbp), %r10
	movq %r10, -32(%rbp)
	addq $16, %rsp
.L_start_39:
	subq $16, %rsp
	movq -8(%rbp), %rax
	movq -16(%rbp), %rbx
	cmp %rbx, %rax
	setle %al
	movzbl %al, %eax
	movq %rax, -40(%rbp)
	movq -40(%rbp), %r10
	addq $16, %rsp
	test %r10, %r10
	jz .L_end_39
.L_start_40:
	subq $16, %rsp
	subq $16, %rsp
	movq $8, %r10
	movq %r10, -64(%rbp)
	movq -8(%rbp), %rax
	movq -64(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -56(%rbp)
	movq 16(%rbp), %rax
	movq -56(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -48(%rbp)
	movq -48(%rbp), %r10
	movq (%r10), %r11
	movq %r11, -48(%rbp)
	movq -48(%rbp), %rax
	movq -32(%rbp), %rbx
	cmp %rbx, %rax
	setl %al
	movzbl %al, %eax
	movq %rax, -40(%rbp)
	movq -40(%rbp), %r10
	addq $16, %rsp
	test %r10, %r10
	jz .L_end_40
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
	jmp .L_start_40
.L_end_40:
.L_start_41:
	subq $16, %rsp
	subq $16, %rsp
	movq $8, %r10
	movq %r10, -64(%rbp)
	movq -16(%rbp), %rax
	movq -64(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -56(%rbp)
	movq 16(%rbp), %rax
	movq -56(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -48(%rbp)
	movq -48(%rbp), %r10
	movq (%r10), %r11
	movq %r11, -48(%rbp)
	movq -48(%rbp), %rax
	movq -32(%rbp), %rbx
	cmp %rbx, %rax
	setg %al
	movzbl %al, %eax
	movq %rax, -40(%rbp)
	movq -40(%rbp), %r10
	addq $16, %rsp
	test %r10, %r10
	jz .L_end_41
	subq $16, %rsp
	movq $1, %r10
	movq %r10, -48(%rbp)
	movq -16(%rbp), %rax
	movq -48(%rbp), %rbx
	subq %rbx, %rax
	movq %rax, -40(%rbp)
	movq -40(%rbp), %r10
	movq %r10, -16(%rbp)
	addq $16, %rsp
	jmp .L_start_41
.L_end_41:
	subq $16, %rsp
	movq -8(%rbp), %rax
	movq -16(%rbp), %rbx
	cmp %rbx, %rax
	setle %al
	movzbl %al, %eax
	movq %rax, -40(%rbp)
	movq -40(%rbp), %r10
	addq $16, %rsp
	test %r10, %r10
	jz .L_else_42
	subq $16, %rsp
	movq $8, %r10
	subq $16, %rsp
	movq %r10, -56(%rbp)
	movq -8(%rbp), %rax
	movq -56(%rbp), %rbx
	addq $16, %rsp
	imulq %rbx, %rax
	movq %rax, -48(%rbp)
	movq 16(%rbp), %rax
	movq -48(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -40(%rbp)
	subq $16, %rsp
	movq $8, %r10
	movq %r10, -64(%rbp)
	movq -16(%rbp), %rax
	movq -64(%rbp), %rbx
	imulq %rbx, %rax
	movq %rax, -56(%rbp)
	movq 16(%rbp), %rax
	movq -56(%rbp), %rbx
	addq $16, %rsp
	addq %rbx, %rax
	movq %rax, -48(%rbp)
	subq $16, %rsp
	movq -48(%rbp), %r10
	movq %r10, -56(%rbp)
	movq -40(%rbp), %r10
	movq %r10, -64(%rbp)
	call swap
	addq $16, %rsp
	addq $16, %rsp
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
	subq $16, %rsp
	movq $1, %r10
	movq %r10, -48(%rbp)
	movq -16(%rbp), %rax
	movq -48(%rbp), %rbx
	subq %rbx, %rax
	movq %rax, -40(%rbp)
	movq -40(%rbp), %r10
	movq %r10, -16(%rbp)
	addq $16, %rsp
	jmp .L_end_42
.L_else_42:
.L_end_42:
	jmp .L_start_39
.L_end_39:
	subq $16, %rsp
	movq 24(%rbp), %rax
	movq -16(%rbp), %rbx
	cmp %rbx, %rax
	setl %al
	movzbl %al, %eax
	movq %rax, -40(%rbp)
	movq -40(%rbp), %r10
	addq $16, %rsp
	test %r10, %r10
	jz .L_else_43
	subq $16, %rsp
	subq $16, %rsp
	movq -16(%rbp), %r10
	movq %r10, -48(%rbp)
	movq 24(%rbp), %r10
	movq %r10, -56(%rbp)
	movq 16(%rbp), %r10
	movq %r10, -64(%rbp)
	call qsort_rec
	addq $16, %rsp
	addq $16, %rsp
	jmp .L_end_43
.L_else_43:
.L_end_43:
	subq $16, %rsp
	movq -8(%rbp), %rax
	movq 32(%rbp), %rbx
	cmp %rbx, %rax
	setl %al
	movzbl %al, %eax
	movq %rax, -40(%rbp)
	movq -40(%rbp), %r10
	addq $16, %rsp
	test %r10, %r10
	jz .L_else_44
	subq $16, %rsp
	subq $16, %rsp
	movq 32(%rbp), %r10
	movq %r10, -48(%rbp)
	movq -8(%rbp), %r10
	movq %r10, -56(%rbp)
	movq 16(%rbp), %r10
	movq %r10, -64(%rbp)
	call qsort_rec
	addq $16, %rsp
	addq $16, %rsp
	jmp .L_end_44
.L_else_44:
.L_end_44:

	movq %rbp, %rsp
	pop %rbp
	ret

.global quicksort
quicksort:
	push %rbp
	movq %rsp, %rbp

	subq $16, %rsp
	movq $1, %r10
	movq %r10, -16(%rbp)
	movq 24(%rbp), %rax
	movq -16(%rbp), %rbx
	cmp %rbx, %rax
	setle %al
	movzbl %al, %eax
	movq %rax, -8(%rbp)
	movq -8(%rbp), %r10
	addq $16, %rsp
	test %r10, %r10
	jz .L_else_45
	movq $0, %r10
	subq $16, %rsp
	movq %r10, -8(%rbp)
	movq -8(%rbp), %rax

	movq %rbp, %rsp
	pop %rbp
	ret

	addq $16, %rsp
	jmp .L_end_45
.L_else_45:
.L_end_45:
	movq $0, %r10
	subq $16, %rsp
	movq %r10, -8(%rbp)
	movq $1, %r10
	subq $16, %rsp
	movq %r10, -24(%rbp)
	movq 24(%rbp), %rax
	movq -24(%rbp), %rbx
	addq $16, %rsp
	subq %rbx, %rax
	movq %rax, -16(%rbp)
	subq $16, %rsp
	subq $16, %rsp
	movq -16(%rbp), %r10
	movq %r10, -32(%rbp)
	movq -8(%rbp), %r10
	movq %r10, -40(%rbp)
	movq 16(%rbp), %r10
	movq %r10, -48(%rbp)
	call qsort_rec
	addq $16, %rsp
	addq $16, %rsp
	addq $16, %rsp

	movq %rbp, %rsp
	pop %rbp
	ret

.section .data
.align 8

.section .bss
.align 8

.section .text
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
	jz .L_else_46
	movq 16(%rbp), %rax

	movq %rbp, %rsp
	pop %rbp
	ret

	jmp .L_end_46
.L_else_46:
	movq 24(%rbp), %rax

	movq %rbp, %rsp
	pop %rbp
	ret

.L_end_46:

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
	jz .L_else_47
	movq 16(%rbp), %rax

	movq %rbp, %rsp
	pop %rbp
	ret

	jmp .L_end_47
.L_else_47:
	movq 24(%rbp), %rax

	movq %rbp, %rsp
	pop %rbp
	ret

.L_end_47:

	movq %rbp, %rsp
	pop %rbp
	ret

.global abs_int
abs_int:
	push %rbp
	movq %rsp, %rbp

	subq $16, %rsp
	movq $0, %r10
	movq %r10, -16(%rbp)
	movq 16(%rbp), %rax
	movq -16(%rbp), %rbx
	cmp %rbx, %rax
	setl %al
	movzbl %al, %eax
	movq %rax, -8(%rbp)
	movq -8(%rbp), %r10
	addq $16, %rsp
	test %r10, %r10
	jz .L_else_48
	subq $16, %rsp
	movq $0, %r10
	movq %r10, -16(%rbp)
	movq -16(%rbp), %rax
	movq 16(%rbp), %rbx
	subq %rbx, %rax
	movq %rax, -8(%rbp)
	movq -8(%rbp), %rax

	movq %rbp, %rsp
	pop %rbp
	ret

	addq $16, %rsp
	jmp .L_end_48
.L_else_48:
.L_end_48:
	movq 16(%rbp), %rax

	movq %rbp, %rsp
	pop %rbp
	ret


	movq %rbp, %rsp
	pop %rbp
	ret

.global ceil_div
ceil_div:
	push %rbp
	movq %rsp, %rbp

	subq $16, %rsp
	subq $16, %rsp
	movq 16(%rbp), %rax
	movq 24(%rbp), %rbx
	addq %rbx, %rax
	movq %rax, -24(%rbp)
	movq $1, %r10
	movq %r10, -32(%rbp)
	movq -24(%rbp), %rax
	movq -32(%rbp), %rbx
	addq $16, %rsp
	subq %rbx, %rax
	movq %rax, -16(%rbp)
	movq -16(%rbp), %rax
	movq 24(%rbp), %rbx
	cqto
	idivq %rbx
	movq %rax, -8(%rbp)
	movq -8(%rbp), %rax

	movq %rbp, %rsp
	pop %rbp
	ret


	movq %rbp, %rsp
	pop %rbp
	ret

)");
