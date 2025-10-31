asm(R"(
.data
.align 3
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

.bss
.align 3
_galloc_array_0: .zero 5242880
_galloc_array_1: .zero 32768
_galloc_array_2: .zero 1000008
_galloc_array_3: .zero 8000040
_galloc_array_4: .zero 8000040

.text
.global _init_input
_init_input:
	stp x29, x30, [sp, #-16]!
	mov x29, sp
	mov x9, #0
	sub sp, sp, #16
	str x9, [x29, #-8]
	mov x9, #0
	str x9, [x29, #-16]
	ldr x16, [x29, #-8]
	ldr x0, [x29, #-16]
	adrp x9, input_buffer@PAGE
	ldr x1, [x9, input_buffer@PAGEOFF]
	adrp x9, READ_BUFFER_CAP@PAGE
	ldr x2, [x9, READ_BUFFER_CAP@PAGEOFF]
	svc #0
	add sp, sp, #16

	mov sp, x29
	ldp x29, x30, [sp], #16
	ret

.global _flush_output
_flush_output:
	stp x29, x30, [sp, #-16]!
	mov x29, sp
	sub sp, sp, #16
	mov x9, #0
	str x9, [x29, #-16]
	adrp x9, output_index@PAGE
	ldr x0, [x9, output_index@PAGEOFF]
	ldr x1, [x29, #-16]
	cmp x0, x1
	cset x0, gt
	str x0, [x29, #-8]
	ldr x9, [x29, #-8]
	add sp, sp, #16
	cbz x9, .L_else_0
	mov x9, #1
	sub sp, sp, #16
	str x9, [x29, #-8]
	mov x9, #1
	str x9, [x29, #-16]
	ldr x16, [x29, #-8]
	ldr x0, [x29, #-16]
	adrp x9, output_buffer@PAGE
	ldr x1, [x9, output_buffer@PAGEOFF]
	adrp x9, output_index@PAGE
	ldr x2, [x9, output_index@PAGEOFF]
	svc #0
	add sp, sp, #16
	mov x9, #0
	sub sp, sp, #16
	str x9, [x29, #-8]
	ldr x9, [x29, #-8]
	adrp x10, output_index@PAGE
	str x9, [x10, output_index@PAGEOFF]
	add sp, sp, #16
	b .L_end_0
.L_else_0:
.L_end_0:

	mov sp, x29
	ldp x29, x30, [sp], #16
	ret

.global _read_char
_read_char:
	stp x29, x30, [sp, #-16]!
	mov x29, sp
	sub sp, sp, #16
	adrp x9, input_index@PAGE
	ldr x0, [x9, input_index@PAGEOFF]
	adrp x9, READ_BUFFER_CAP@PAGE
	ldr x1, [x9, READ_BUFFER_CAP@PAGEOFF]
	cmp x0, x1
	cset x0, ge
	str x0, [x29, #-8]
	ldr x9, [x29, #-8]
	add sp, sp, #16
	cbz x9, .L_else_1
	mov x9, #0
	sub sp, sp, #16
	str x9, [x29, #-8]
	ldr x0, [x29, #-8]

	mov sp, x29
	ldp x29, x30, [sp], #16
	ret

	add sp, sp, #16
	b .L_end_1
.L_else_1:
.L_end_1:
	sub sp, sp, #16
	sub sp, sp, #16
	mov x9, #1
	str x9, [x29, #-32]
	adrp x9, input_index@PAGE
	ldr x0, [x9, input_index@PAGEOFF]
	ldr x1, [x29, #-32]
	mul x0, x0, x1
	str x0, [x29, #-24]
	adrp x9, input_buffer@PAGE
	ldr x0, [x9, input_buffer@PAGEOFF]
	ldr x1, [x29, #-24]
	add sp, sp, #16
	add x0, x0, x1
	str x0, [x29, #-16]
	ldr x9, [x29, #-16]
	ldrb w10, [x9]
	strb w10, [x29, #-9]
	ldrb w9, [x29, #-9]
	str x9, [x29, #-8]
	mov x9, #1
	sub sp, sp, #16
	str x9, [x29, #-24]
	adrp x9, input_index@PAGE
	ldr x0, [x9, input_index@PAGEOFF]
	ldr x1, [x29, #-24]
	add sp, sp, #16
	add x0, x0, x1
	str x0, [x29, #-16]
	ldr x9, [x29, #-16]
	adrp x10, input_index@PAGE
	str x9, [x10, input_index@PAGEOFF]
	ldr x0, [x29, #-8]

	mov sp, x29
	ldp x29, x30, [sp], #16
	ret


	mov sp, x29
	ldp x29, x30, [sp], #16
	ret

.global _print_char
_print_char:
	stp x29, x30, [sp, #-16]!
	mov x29, sp
	sub sp, sp, #16
	mov x9, #1
	sub sp, sp, #16
	str x9, [x29, #-24]
	adrp x9, output_index@PAGE
	ldr x0, [x9, output_index@PAGEOFF]
	ldr x1, [x29, #-24]
	add sp, sp, #16
	mul x0, x0, x1
	str x0, [x29, #-16]
	adrp x9, output_buffer@PAGE
	ldr x0, [x9, output_buffer@PAGEOFF]
	ldr x1, [x29, #-16]
	add x0, x0, x1
	str x0, [x29, #-8]
	ldr x10, [x29, #-8]
	ldr x9, [x29, #16]
	strb w9, [x10]
	add sp, sp, #16
	sub sp, sp, #16
	mov x9, #1
	str x9, [x29, #-16]
	adrp x9, output_index@PAGE
	ldr x0, [x9, output_index@PAGEOFF]
	ldr x1, [x29, #-16]
	add x0, x0, x1
	str x0, [x29, #-8]
	ldr x9, [x29, #-8]
	adrp x10, output_index@PAGE
	str x9, [x10, output_index@PAGEOFF]
	add sp, sp, #16
	sub sp, sp, #16
	adrp x9, output_index@PAGE
	ldr x0, [x9, output_index@PAGEOFF]
	adrp x9, WRITE_BUFFER_CAP@PAGE
	ldr x1, [x9, WRITE_BUFFER_CAP@PAGEOFF]
	cmp x0, x1
	cset x0, eq
	str x0, [x29, #-8]
	ldr x9, [x29, #-8]
	add sp, sp, #16
	cbz x9, .L_else_2
	bl _flush_output
	b .L_end_2
.L_else_2:
.L_end_2:

	mov sp, x29
	ldp x29, x30, [sp], #16
	ret

.global _read_int
_read_int:
	stp x29, x30, [sp, #-16]!
	mov x29, sp
	sub sp, sp, #16
	bl _read_char
	sub sp, sp, #16
	str x0, [x29, #-24]
	ldr x9, [x29, #-24]
	str x9, [x29, #-8]
	add sp, sp, #16
	sub sp, sp, #16
	mov x9, #0
	str x9, [x29, #-32]
	ldr x9, [x29, #-32]
	str x9, [x29, #-24]
	mov x9, #0
	sub sp, sp, #16
	str x9, [x29, #-40]
	ldr x9, [x29, #-40]
	str x9, [x29, #-32]
	add sp, sp, #16
.L_start_3:
	sub sp, sp, #16
	sub sp, sp, #16
	mov x9, #10
	str x9, [x29, #-64]
	ldr x0, [x29, #-8]
	ldr x1, [x29, #-64]
	cmp x0, x1
	cset x0, eq
	str x0, [x29, #-56]
	mov x9, #32
	sub sp, sp, #16
	str x9, [x29, #-72]
	ldr x0, [x29, #-8]
	ldr x1, [x29, #-72]
	add sp, sp, #16
	cmp x0, x1
	cset x0, eq
	str x0, [x29, #-64]
	ldr x0, [x29, #-56]
	ldr x1, [x29, #-64]
	add sp, sp, #16
	orr x0, x0, x1
	str x0, [x29, #-48]
	sub sp, sp, #16
	mov x9, #13
	str x9, [x29, #-64]
	ldr x0, [x29, #-8]
	ldr x1, [x29, #-64]
	cmp x0, x1
	cset x0, eq
	str x0, [x29, #-56]
	ldr x0, [x29, #-48]
	ldr x1, [x29, #-56]
	add sp, sp, #16
	orr x0, x0, x1
	str x0, [x29, #-40]
	ldr x9, [x29, #-40]
	add sp, sp, #16
	cbz x9, .L_end_3
	bl _read_char
	sub sp, sp, #16
	str x0, [x29, #-40]
	ldr x9, [x29, #-40]
	str x9, [x29, #-8]
	add sp, sp, #16
	b .L_start_3
.L_end_3:
	sub sp, sp, #16
	mov x9, #45
	str x9, [x29, #-48]
	ldr x0, [x29, #-8]
	ldr x1, [x29, #-48]
	cmp x0, x1
	cset x0, eq
	str x0, [x29, #-40]
	ldr x9, [x29, #-40]
	add sp, sp, #16
	cbz x9, .L_else_4
	mov x9, #1
	sub sp, sp, #16
	str x9, [x29, #-40]
	ldr x9, [x29, #-40]
	str x9, [x29, #-32]
	add sp, sp, #16
	bl _read_char
	sub sp, sp, #16
	str x0, [x29, #-40]
	ldr x9, [x29, #-40]
	str x9, [x29, #-8]
	add sp, sp, #16
	b .L_end_4
.L_else_4:
.L_end_4:
.L_start_5:
	sub sp, sp, #16
	sub sp, sp, #16
	mov x9, #10
	sub sp, sp, #16
	str x9, [x29, #-72]
	ldr x0, [x29, #-8]
	ldr x1, [x29, #-72]
	add sp, sp, #16
	cmp x0, x1
	cset x0, ne
	str x0, [x29, #-64]
	sub sp, sp, #16
	mov x9, #32
	str x9, [x29, #-80]
	ldr x0, [x29, #-8]
	ldr x1, [x29, #-80]
	cmp x0, x1
	cset x0, ne
	str x0, [x29, #-72]
	ldr x0, [x29, #-64]
	ldr x1, [x29, #-72]
	add sp, sp, #16
	and x0, x0, x1
	str x0, [x29, #-56]
	mov x9, #13
	sub sp, sp, #16
	str x9, [x29, #-72]
	ldr x0, [x29, #-8]
	ldr x1, [x29, #-72]
	add sp, sp, #16
	cmp x0, x1
	cset x0, ne
	str x0, [x29, #-64]
	ldr x0, [x29, #-56]
	ldr x1, [x29, #-64]
	add sp, sp, #16
	and x0, x0, x1
	str x0, [x29, #-48]
	sub sp, sp, #16
	mov x9, #0
	str x9, [x29, #-64]
	ldr x0, [x29, #-8]
	ldr x1, [x29, #-64]
	cmp x0, x1
	cset x0, ne
	str x0, [x29, #-56]
	ldr x0, [x29, #-48]
	ldr x1, [x29, #-56]
	add sp, sp, #16
	and x0, x0, x1
	str x0, [x29, #-40]
	ldr x9, [x29, #-40]
	add sp, sp, #16
	cbz x9, .L_end_5
	sub sp, sp, #16
	sub sp, sp, #16
	mov x9, #10
	str x9, [x29, #-64]
	ldr x0, [x29, #-24]
	ldr x1, [x29, #-64]
	mul x0, x0, x1
	str x0, [x29, #-56]
	ldr x0, [x29, #-56]
	ldr x1, [x29, #-8]
	add sp, sp, #16
	add x0, x0, x1
	str x0, [x29, #-48]
	mov x9, #48
	sub sp, sp, #16
	str x9, [x29, #-56]
	ldr x0, [x29, #-48]
	ldr x1, [x29, #-56]
	add sp, sp, #16
	sub x0, x0, x1
	str x0, [x29, #-40]
	ldr x9, [x29, #-40]
	str x9, [x29, #-24]
	add sp, sp, #16
	bl _read_char
	sub sp, sp, #16
	str x0, [x29, #-40]
	ldr x9, [x29, #-40]
	str x9, [x29, #-8]
	add sp, sp, #16
	b .L_start_5
.L_end_5:
	sub sp, sp, #16
	mov x9, #1
	str x9, [x29, #-48]
	ldr x0, [x29, #-32]
	ldr x1, [x29, #-48]
	cmp x0, x1
	cset x0, eq
	str x0, [x29, #-40]
	ldr x9, [x29, #-40]
	add sp, sp, #16
	cbz x9, .L_else_6
	sub sp, sp, #16
	mov x9, #0
	str x9, [x29, #-48]
	ldr x0, [x29, #-48]
	ldr x1, [x29, #-24]
	sub x0, x0, x1
	str x0, [x29, #-40]
	ldr x0, [x29, #-40]

	mov sp, x29
	ldp x29, x30, [sp], #16
	ret

	add sp, sp, #16
	b .L_end_6
.L_else_6:
.L_end_6:
	ldr x0, [x29, #-24]

	mov sp, x29
	ldp x29, x30, [sp], #16
	ret


	mov sp, x29
	ldp x29, x30, [sp], #16
	ret

.global _print_int
_print_int:
	stp x29, x30, [sp, #-16]!
	mov x29, sp
	sub sp, sp, #16
	mov x9, #0
	str x9, [x29, #-16]
	ldr x0, [x29, #16]
	ldr x1, [x29, #-16]
	cmp x0, x1
	cset x0, eq
	str x0, [x29, #-8]
	ldr x9, [x29, #-8]
	add sp, sp, #16
	cbz x9, .L_else_7
	mov x9, #48
	sub sp, sp, #16
	str x9, [x29, #-8]
	ldr x9, [x29, #-8]
	str x9, [x29, #-16]
	bl _print_char
	add sp, sp, #16
	mov x9, #0
	sub sp, sp, #16
	str x9, [x29, #-8]
	ldr x0, [x29, #-8]

	mov sp, x29
	ldp x29, x30, [sp], #16
	ret

	add sp, sp, #16
	b .L_end_7
.L_else_7:
.L_end_7:
	sub sp, sp, #16
	mov x9, #0
	str x9, [x29, #-16]
	ldr x9, [x29, #-16]
	str x9, [x29, #-8]
	mov x9, #0
	sub sp, sp, #16
	str x9, [x29, #-24]
	ldr x0, [x29, #16]
	ldr x1, [x29, #-24]
	add sp, sp, #16
	cmp x0, x1
	cset x0, lt
	str x0, [x29, #-16]
	ldr x9, [x29, #-16]
	cbz x9, .L_else_8
	mov x9, #1
	str x9, [x29, #-16]
	ldr x9, [x29, #-16]
	str x9, [x29, #-8]
	mov x9, #0
	sub sp, sp, #16
	str x9, [x29, #-24]
	ldr x0, [x29, #-24]
	ldr x1, [x29, #16]
	add sp, sp, #16
	sub x0, x0, x1
	str x0, [x29, #-16]
	ldr x9, [x29, #-16]
	str x9, [x29, #16]
	b .L_end_8
.L_else_8:
.L_end_8:
	sub sp, sp, #16
	sub sp, sp, #16
	sub sp, sp, #16
	sub sp, sp, #16
	sub sp, sp, #16
	sub sp, sp, #16
	sub sp, sp, #16
	sub sp, sp, #16
	sub sp, sp, #16
	sub sp, sp, #16
	add x9, x29, #-176
	sub sp, sp, #16
	str x9, [x29, #-184]
	ldr x9, [x29, #-184]
	str x9, [x29, #-16]
	add sp, sp, #16
	sub sp, sp, #16
	mov x9, #0
	str x9, [x29, #-192]
	ldr x9, [x29, #-192]
	str x9, [x29, #-184]
.L_start_9:
	mov x9, #0
	sub sp, sp, #16
	str x9, [x29, #-200]
	ldr x0, [x29, #16]
	ldr x1, [x29, #-200]
	add sp, sp, #16
	cmp x0, x1
	cset x0, gt
	str x0, [x29, #-192]
	ldr x9, [x29, #-192]
	cbz x9, .L_end_9
	sub sp, sp, #16
	mov x9, #10
	str x9, [x29, #-208]
	ldr x0, [x29, #16]
	ldr x1, [x29, #-208]
	sdiv x2, x0, x1
	msub x0, x2, x1, x0
	str x0, [x29, #-200]
	ldr x9, [x29, #-200]
	str x9, [x29, #-192]
	add sp, sp, #16
	sub sp, sp, #16
	mov x9, #10
	str x9, [x29, #-208]
	ldr x0, [x29, #16]
	ldr x1, [x29, #-208]
	sdiv x0, x0, x1
	str x0, [x29, #-200]
	ldr x9, [x29, #-200]
	str x9, [x29, #16]
	add sp, sp, #16
	sub sp, sp, #16
	mov x9, #48
	str x9, [x29, #-208]
	ldr x0, [x29, #-192]
	ldr x1, [x29, #-208]
	add x0, x0, x1
	str x0, [x29, #-200]
	sub sp, sp, #16
	mov x9, #8
	str x9, [x29, #-224]
	ldr x0, [x29, #-184]
	ldr x1, [x29, #-224]
	mul x0, x0, x1
	str x0, [x29, #-216]
	ldr x0, [x29, #-16]
	ldr x1, [x29, #-216]
	add sp, sp, #16
	add x0, x0, x1
	str x0, [x29, #-208]
	ldr x10, [x29, #-208]
	ldr x9, [x29, #-200]
	str x9, [x10]
	mov x9, #1
	sub sp, sp, #16
	str x9, [x29, #-216]
	ldr x0, [x29, #-184]
	ldr x1, [x29, #-216]
	add sp, sp, #16
	add x0, x0, x1
	str x0, [x29, #-208]
	ldr x9, [x29, #-208]
	str x9, [x29, #-184]
	add sp, sp, #16
	b .L_start_9
.L_end_9:
	mov x9, #1
	sub sp, sp, #16
	str x9, [x29, #-200]
	ldr x0, [x29, #-8]
	ldr x1, [x29, #-200]
	add sp, sp, #16
	cmp x0, x1
	cset x0, eq
	str x0, [x29, #-192]
	ldr x9, [x29, #-192]
	cbz x9, .L_else_10
	mov x9, #45
	str x9, [x29, #-192]
	sub sp, sp, #16
	ldr x9, [x29, #-192]
	str x9, [x29, #-208]
	bl _print_char
	add sp, sp, #16
	b .L_end_10
.L_else_10:
.L_end_10:
.L_start_11:
	mov x9, #0
	sub sp, sp, #16
	str x9, [x29, #-200]
	ldr x0, [x29, #-184]
	ldr x1, [x29, #-200]
	add sp, sp, #16
	cmp x0, x1
	cset x0, gt
	str x0, [x29, #-192]
	ldr x9, [x29, #-192]
	cbz x9, .L_end_11
	mov x9, #1
	sub sp, sp, #16
	str x9, [x29, #-200]
	ldr x0, [x29, #-184]
	ldr x1, [x29, #-200]
	add sp, sp, #16
	sub x0, x0, x1
	str x0, [x29, #-192]
	ldr x9, [x29, #-192]
	str x9, [x29, #-184]
	sub sp, sp, #16
	mov x9, #8
	str x9, [x29, #-208]
	ldr x0, [x29, #-184]
	ldr x1, [x29, #-208]
	mul x0, x0, x1
	str x0, [x29, #-200]
	ldr x0, [x29, #-16]
	ldr x1, [x29, #-200]
	add sp, sp, #16
	add x0, x0, x1
	str x0, [x29, #-192]
	ldr x9, [x29, #-192]
	ldr x10, [x9]
	str x10, [x29, #-192]
	sub sp, sp, #16
	ldr x9, [x29, #-192]
	str x9, [x29, #-208]
	bl _print_char
	add sp, sp, #16
	b .L_start_11
.L_end_11:

	mov sp, x29
	ldp x29, x30, [sp], #16
	ret

.global _read_string
_read_string:
	stp x29, x30, [sp, #-16]!
	mov x29, sp
	sub sp, sp, #16
	mov x9, #0
	str x9, [x29, #-16]
	ldr x9, [x29, #-16]
	str x9, [x29, #-8]
.L_start_12:
	ldr x0, [x29, #-8]
	ldr x1, [x29, #24]
	cmp x0, x1
	cset x0, lt
	str x0, [x29, #-16]
	ldr x9, [x29, #-16]
	cbz x9, .L_end_12
	bl _read_char
	sub sp, sp, #16
	str x0, [x29, #-24]
	ldr x9, [x29, #-24]
	str x9, [x29, #-16]
	add sp, sp, #16
	sub sp, sp, #16
	mov x9, #0
	str x9, [x29, #-32]
	ldr x0, [x29, #-16]
	ldr x1, [x29, #-32]
	cmp x0, x1
	cset x0, eq
	str x0, [x29, #-24]
	ldr x9, [x29, #-24]
	add sp, sp, #16
	cbz x9, .L_else_13
	b .L_end_12
	b .L_end_13
.L_else_13:
.L_end_13:
	sub sp, sp, #16
	sub sp, sp, #16
	mov x9, #10
	str x9, [x29, #-48]
	ldr x0, [x29, #-16]
	ldr x1, [x29, #-48]
	cmp x0, x1
	cset x0, eq
	str x0, [x29, #-40]
	mov x9, #13
	sub sp, sp, #16
	str x9, [x29, #-56]
	ldr x0, [x29, #-16]
	ldr x1, [x29, #-56]
	add sp, sp, #16
	cmp x0, x1
	cset x0, eq
	str x0, [x29, #-48]
	ldr x0, [x29, #-40]
	ldr x1, [x29, #-48]
	add sp, sp, #16
	orr x0, x0, x1
	str x0, [x29, #-32]
	sub sp, sp, #16
	mov x9, #32
	str x9, [x29, #-48]
	ldr x0, [x29, #-16]
	ldr x1, [x29, #-48]
	cmp x0, x1
	cset x0, eq
	str x0, [x29, #-40]
	ldr x0, [x29, #-32]
	ldr x1, [x29, #-40]
	add sp, sp, #16
	orr x0, x0, x1
	str x0, [x29, #-24]
	ldr x9, [x29, #-24]
	add sp, sp, #16
	cbz x9, .L_else_14
	b .L_start_12
	b .L_end_14
.L_else_14:
.L_end_14:
	sub sp, sp, #16
	mov x9, #1
	sub sp, sp, #16
	str x9, [x29, #-40]
	ldr x0, [x29, #-8]
	ldr x1, [x29, #-40]
	add sp, sp, #16
	mul x0, x0, x1
	str x0, [x29, #-32]
	ldr x0, [x29, #16]
	ldr x1, [x29, #-32]
	add x0, x0, x1
	str x0, [x29, #-24]
	ldr x10, [x29, #-24]
	ldr x9, [x29, #-16]
	strb w9, [x10]
	add sp, sp, #16
	sub sp, sp, #16
	mov x9, #1
	str x9, [x29, #-32]
	ldr x0, [x29, #-8]
	ldr x1, [x29, #-32]
	add x0, x0, x1
	str x0, [x29, #-24]
	ldr x9, [x29, #-24]
	str x9, [x29, #-8]
	add sp, sp, #16
	b .L_start_12
.L_end_12:

	mov sp, x29
	ldp x29, x30, [sp], #16
	ret

.global _mod_pow
_mod_pow:
	stp x29, x30, [sp, #-16]!
	mov x29, sp
	sub sp, sp, #16
	ldr x0, [x29, #16]
	adrp x9, MOD@PAGE
	ldr x1, [x9, MOD@PAGEOFF]
	sdiv x2, x0, x1
	msub x0, x2, x1, x0
	str x0, [x29, #-16]
	ldr x9, [x29, #-16]
	str x9, [x29, #-8]
	mov x9, #0
	sub sp, sp, #16
	str x9, [x29, #-24]
	ldr x0, [x29, #-8]
	ldr x1, [x29, #-24]
	add sp, sp, #16
	cmp x0, x1
	cset x0, lt
	str x0, [x29, #-16]
	ldr x9, [x29, #-16]
	cbz x9, .L_else_15
	ldr x0, [x29, #-8]
	adrp x9, MOD@PAGE
	ldr x1, [x9, MOD@PAGEOFF]
	add x0, x0, x1
	str x0, [x29, #-16]
	ldr x9, [x29, #-16]
	str x9, [x29, #-8]
	b .L_end_15
.L_else_15:
.L_end_15:
	mov x9, #1
	sub sp, sp, #16
	str x9, [x29, #-24]
	ldr x9, [x29, #-24]
	str x9, [x29, #-16]
	add sp, sp, #16
	sub sp, sp, #16
	ldr x9, [x29, #-8]
	str x9, [x29, #-24]
	ldr x9, [x29, #24]
	str x9, [x29, #-32]
.L_start_16:
	sub sp, sp, #16
	mov x9, #0
	str x9, [x29, #-48]
	ldr x0, [x29, #-32]
	ldr x1, [x29, #-48]
	cmp x0, x1
	cset x0, gt
	str x0, [x29, #-40]
	ldr x9, [x29, #-40]
	add sp, sp, #16
	cbz x9, .L_end_16
	sub sp, sp, #16
	mov x9, #2
	sub sp, sp, #16
	str x9, [x29, #-56]
	ldr x0, [x29, #-32]
	ldr x1, [x29, #-56]
	add sp, sp, #16
	sdiv x2, x0, x1
	msub x0, x2, x1, x0
	str x0, [x29, #-48]
	mov x9, #1
	sub sp, sp, #16
	str x9, [x29, #-56]
	ldr x0, [x29, #-48]
	ldr x1, [x29, #-56]
	add sp, sp, #16
	cmp x0, x1
	cset x0, eq
	str x0, [x29, #-40]
	ldr x9, [x29, #-40]
	add sp, sp, #16
	cbz x9, .L_else_17
	sub sp, sp, #16
	ldr x0, [x29, #-16]
	ldr x1, [x29, #-24]
	mul x0, x0, x1
	str x0, [x29, #-48]
	ldr x0, [x29, #-48]
	adrp x9, MOD@PAGE
	ldr x1, [x9, MOD@PAGEOFF]
	sdiv x2, x0, x1
	msub x0, x2, x1, x0
	str x0, [x29, #-40]
	ldr x9, [x29, #-40]
	str x9, [x29, #-16]
	add sp, sp, #16
	b .L_end_17
.L_else_17:
.L_end_17:
	sub sp, sp, #16
	ldr x0, [x29, #-24]
	ldr x1, [x29, #-24]
	mul x0, x0, x1
	str x0, [x29, #-48]
	ldr x0, [x29, #-48]
	adrp x9, MOD@PAGE
	ldr x1, [x9, MOD@PAGEOFF]
	sdiv x2, x0, x1
	msub x0, x2, x1, x0
	str x0, [x29, #-40]
	ldr x9, [x29, #-40]
	str x9, [x29, #-24]
	add sp, sp, #16
	sub sp, sp, #16
	mov x9, #2
	str x9, [x29, #-48]
	ldr x0, [x29, #-32]
	ldr x1, [x29, #-48]
	sdiv x0, x0, x1
	str x0, [x29, #-40]
	ldr x9, [x29, #-40]
	str x9, [x29, #-32]
	add sp, sp, #16
	b .L_start_16
.L_end_16:
	ldr x0, [x29, #-16]

	mov sp, x29
	ldp x29, x30, [sp], #16
	ret


	mov sp, x29
	ldp x29, x30, [sp], #16
	ret

.global _choose
_choose:
	stp x29, x30, [sp, #-16]!
	mov x29, sp
	sub sp, sp, #16
	mov x9, #0
	sub sp, sp, #16
	str x9, [x29, #-24]
	ldr x0, [x29, #24]
	ldr x1, [x29, #-24]
	add sp, sp, #16
	cmp x0, x1
	cset x0, lt
	str x0, [x29, #-16]
	sub sp, sp, #16
	ldr x0, [x29, #24]
	ldr x1, [x29, #16]
	cmp x0, x1
	cset x0, gt
	str x0, [x29, #-24]
	ldr x0, [x29, #-16]
	ldr x1, [x29, #-24]
	add sp, sp, #16
	orr x0, x0, x1
	str x0, [x29, #-8]
	ldr x9, [x29, #-8]
	add sp, sp, #16
	cbz x9, .L_else_18
	mov x9, #0
	sub sp, sp, #16
	str x9, [x29, #-8]
	ldr x0, [x29, #-8]

	mov sp, x29
	ldp x29, x30, [sp], #16
	ret

	add sp, sp, #16
	b .L_end_18
.L_else_18:
.L_end_18:
	sub sp, sp, #16
	sub sp, sp, #16
	mov x9, #8
	str x9, [x29, #-32]
	ldr x0, [x29, #16]
	ldr x1, [x29, #-32]
	mul x0, x0, x1
	str x0, [x29, #-24]
	ldr x0, [x29, #32]
	ldr x1, [x29, #-24]
	add sp, sp, #16
	add x0, x0, x1
	str x0, [x29, #-16]
	ldr x9, [x29, #-16]
	ldr x10, [x9]
	str x10, [x29, #-16]
	ldr x9, [x29, #-16]
	str x9, [x29, #-8]
	sub sp, sp, #16
	sub sp, sp, #16
	mov x9, #8
	sub sp, sp, #16
	str x9, [x29, #-56]
	ldr x0, [x29, #24]
	ldr x1, [x29, #-56]
	add sp, sp, #16
	mul x0, x0, x1
	str x0, [x29, #-48]
	ldr x0, [x29, #40]
	ldr x1, [x29, #-48]
	add x0, x0, x1
	str x0, [x29, #-40]
	ldr x9, [x29, #-40]
	add sp, sp, #16
	sub sp, sp, #16
	ldr x10, [x9]
	str x10, [x29, #-40]
	ldr x0, [x29, #-8]
	ldr x1, [x29, #-40]
	add sp, sp, #16
	mul x0, x0, x1
	str x0, [x29, #-32]
	ldr x0, [x29, #-32]
	adrp x9, MOD@PAGE
	ldr x1, [x9, MOD@PAGEOFF]
	sdiv x2, x0, x1
	msub x0, x2, x1, x0
	str x0, [x29, #-24]
	ldr x9, [x29, #-24]
	str x9, [x29, #-16]
	add sp, sp, #16
	sub sp, sp, #16
	sub sp, sp, #16
	sub sp, sp, #16
	ldr x0, [x29, #16]
	ldr x1, [x29, #24]
	sub x0, x0, x1
	str x0, [x29, #-56]
	mov x9, #8
	str x9, [x29, #-64]
	ldr x0, [x29, #-56]
	ldr x1, [x29, #-64]
	add sp, sp, #16
	mul x0, x0, x1
	str x0, [x29, #-48]
	ldr x0, [x29, #40]
	ldr x1, [x29, #-48]
	add x0, x0, x1
	str x0, [x29, #-40]
	ldr x9, [x29, #-40]
	add sp, sp, #16
	sub sp, sp, #16
	ldr x10, [x9]
	str x10, [x29, #-40]
	ldr x0, [x29, #-16]
	ldr x1, [x29, #-40]
	add sp, sp, #16
	mul x0, x0, x1
	str x0, [x29, #-32]
	ldr x0, [x29, #-32]
	adrp x9, MOD@PAGE
	ldr x1, [x9, MOD@PAGEOFF]
	sdiv x2, x0, x1
	msub x0, x2, x1, x0
	str x0, [x29, #-24]
	ldr x0, [x29, #-24]

	mov sp, x29
	ldp x29, x30, [sp], #16
	ret


	mov sp, x29
	ldp x29, x30, [sp], #16
	ret

.global _main
_main:
	stp x29, x30, [sp, #-16]!
	mov x29, sp
	bl _init_input
	sub sp, sp, #16
	bl _read_int
	sub sp, sp, #16
	str x0, [x29, #-24]
	ldr x9, [x29, #-24]
	str x9, [x29, #-8]
	add sp, sp, #16
	sub sp, sp, #16
	bl _read_int
	sub sp, sp, #16
	str x0, [x29, #-40]
	ldr x9, [x29, #-40]
	str x9, [x29, #-24]
	add sp, sp, #16
	sub sp, sp, #16
	bl _read_int
	sub sp, sp, #16
	str x0, [x29, #-56]
	ldr x9, [x29, #-56]
	str x9, [x29, #-40]
	add sp, sp, #16
	sub sp, sp, #16
	ldr x9, [x29, #-24]
	str x9, [x29, #-56]
	adrp x10, str@PAGE
	ldr x9, [x10, str@PAGEOFF]
	str x9, [x29, #-64]
	bl _read_string
	add sp, sp, #16
	sub sp, sp, #16
	mov x9, #0
	str x9, [x29, #-64]
	ldr x9, [x29, #-64]
	str x9, [x29, #-56]
	mov x9, #0
	sub sp, sp, #16
	str x9, [x29, #-72]
	ldr x9, [x29, #-72]
	str x9, [x29, #-64]
	add sp, sp, #16
	sub sp, sp, #16
	mov x9, #0
	str x9, [x29, #-80]
	ldr x9, [x29, #-80]
	str x9, [x29, #-72]
.L_start_19:
	ldr x0, [x29, #-72]
	ldr x1, [x29, #-24]
	cmp x0, x1
	cset x0, lt
	str x0, [x29, #-80]
	ldr x9, [x29, #-80]
	cbz x9, .L_end_19
	sub sp, sp, #16
	mov x9, #1
	sub sp, sp, #16
	str x9, [x29, #-97]
	ldr x0, [x29, #-72]
	ldr x1, [x29, #-97]
	add sp, sp, #16
	mul x0, x0, x1
	str x0, [x29, #-89]
	adrp x9, str@PAGE
	ldr x0, [x9, str@PAGEOFF]
	ldr x1, [x29, #-89]
	add x0, x0, x1
	str x0, [x29, #-81]
	ldr x9, [x29, #-81]
	add sp, sp, #16
	ldrb w10, [x9]
	strb w10, [x29, #-74]
	mov x9, #77
	sub sp, sp, #16
	str x9, [x29, #-82]
	ldrb w0, [x29, #-74]
	ldr x1, [x29, #-82]
	add sp, sp, #16
	cmp x0, x1
	cset x0, eq
	strb w0, [x29, #-73]
	ldrb w9, [x29, #-73]
	cbz x9, .L_else_20
	mov x9, #1
	sub sp, sp, #16
	str x9, [x29, #-88]
	ldr x0, [x29, #-56]
	ldr x1, [x29, #-88]
	add sp, sp, #16
	add x0, x0, x1
	str x0, [x29, #-80]
	ldr x9, [x29, #-80]
	str x9, [x29, #-56]
	b .L_end_20
.L_else_20:
	mov x9, #1
	sub sp, sp, #16
	str x9, [x29, #-88]
	ldr x0, [x29, #-64]
	ldr x1, [x29, #-88]
	add sp, sp, #16
	add x0, x0, x1
	str x0, [x29, #-80]
	ldr x9, [x29, #-80]
	str x9, [x29, #-64]
.L_end_20:
	mov x9, #1
	sub sp, sp, #16
	str x9, [x29, #-88]
	ldr x0, [x29, #-72]
	ldr x1, [x29, #-88]
	add sp, sp, #16
	add x0, x0, x1
	str x0, [x29, #-80]
	ldr x9, [x29, #-80]
	str x9, [x29, #-72]
	b .L_start_19
.L_end_19:
	sub sp, sp, #16
	ldr x0, [x29, #-8]
	ldr x1, [x29, #-56]
	mul x0, x0, x1
	str x0, [x29, #-88]
	ldr x0, [x29, #-64]
	ldr x1, [x29, #-88]
	add sp, sp, #16
	cmp x0, x1
	cset x0, ne
	str x0, [x29, #-80]
	ldr x9, [x29, #-80]
	cbz x9, .L_else_21
	mov x9, #0
	str x9, [x29, #-80]
	sub sp, sp, #16
	ldr x9, [x29, #-80]
	str x9, [x29, #-96]
	bl _print_int
	mov x9, #10
	str x9, [x29, #-96]
	sub sp, sp, #16
	ldr x9, [x29, #-96]
	str x9, [x29, #-112]
	bl _print_char
	bl _flush_output
	mov x9, #0
	sub sp, sp, #16
	str x9, [x29, #-120]
	ldr x0, [x29, #-120]

	mov sp, x29
	ldp x29, x30, [sp], #16
	ret

	add sp, sp, #16
	add sp, sp, #16
	add sp, sp, #16
	b .L_end_21
.L_else_21:
.L_end_21:
	ldr x9, [x29, #-64]
	str x9, [x29, #-80]
	mov x9, #1
	sub sp, sp, #16
	str x9, [x29, #-88]
	sub sp, sp, #16
	mov x9, #0
	str x9, [x29, #-112]
	mov x9, #8
	sub sp, sp, #16
	str x9, [x29, #-120]
	ldr x0, [x29, #-112]
	ldr x1, [x29, #-120]
	add sp, sp, #16
	mul x0, x0, x1
	str x0, [x29, #-104]
	adrp x9, fact@PAGE
	ldr x0, [x9, fact@PAGEOFF]
	ldr x1, [x29, #-104]
	add sp, sp, #16
	add x0, x0, x1
	str x0, [x29, #-96]
	ldr x10, [x29, #-96]
	ldr x9, [x29, #-88]
	str x9, [x10]
	mov x9, #1
	sub sp, sp, #16
	str x9, [x29, #-104]
	ldr x9, [x29, #-104]
	str x9, [x29, #-96]
	add sp, sp, #16
.L_start_22:
	sub sp, sp, #16
	ldr x0, [x29, #-96]
	ldr x1, [x29, #-80]
	cmp x0, x1
	cset x0, le
	str x0, [x29, #-104]
	ldr x9, [x29, #-104]
	add sp, sp, #16
	cbz x9, .L_end_22
	sub sp, sp, #16
	sub sp, sp, #16
	sub sp, sp, #16
	mov x9, #1
	str x9, [x29, #-144]
	ldr x0, [x29, #-96]
	ldr x1, [x29, #-144]
	sub x0, x0, x1
	str x0, [x29, #-136]
	mov x9, #8
	str x9, [x29, #-144]
	ldr x0, [x29, #-136]
	ldr x1, [x29, #-144]
	add sp, sp, #16
	mul x0, x0, x1
	str x0, [x29, #-128]
	adrp x9, fact@PAGE
	ldr x0, [x9, fact@PAGEOFF]
	ldr x1, [x29, #-128]
	add x0, x0, x1
	str x0, [x29, #-120]
	ldr x9, [x29, #-120]
	add sp, sp, #16
	sub sp, sp, #16
	ldr x10, [x9]
	str x10, [x29, #-120]
	ldr x0, [x29, #-120]
	ldr x1, [x29, #-96]
	add sp, sp, #16
	mul x0, x0, x1
	str x0, [x29, #-112]
	ldr x0, [x29, #-112]
	adrp x9, MOD@PAGE
	ldr x1, [x9, MOD@PAGEOFF]
	sdiv x2, x0, x1
	msub x0, x2, x1, x0
	str x0, [x29, #-104]
	sub sp, sp, #16
	mov x9, #8
	str x9, [x29, #-128]
	ldr x0, [x29, #-96]
	ldr x1, [x29, #-128]
	mul x0, x0, x1
	str x0, [x29, #-120]
	adrp x9, fact@PAGE
	ldr x0, [x9, fact@PAGEOFF]
	ldr x1, [x29, #-120]
	add sp, sp, #16
	add x0, x0, x1
	str x0, [x29, #-112]
	ldr x10, [x29, #-112]
	ldr x9, [x29, #-104]
	str x9, [x10]
	mov x9, #1
	sub sp, sp, #16
	str x9, [x29, #-120]
	ldr x0, [x29, #-96]
	ldr x1, [x29, #-120]
	add sp, sp, #16
	add x0, x0, x1
	str x0, [x29, #-112]
	ldr x9, [x29, #-112]
	str x9, [x29, #-96]
	add sp, sp, #16
	b .L_start_22
.L_end_22:
	sub sp, sp, #16
	mov x9, #8
	sub sp, sp, #16
	str x9, [x29, #-120]
	ldr x0, [x29, #-80]
	ldr x1, [x29, #-120]
	add sp, sp, #16
	mul x0, x0, x1
	str x0, [x29, #-112]
	adrp x9, fact@PAGE
	ldr x0, [x9, fact@PAGEOFF]
	ldr x1, [x29, #-112]
	add x0, x0, x1
	str x0, [x29, #-104]
	ldr x9, [x29, #-104]
	add sp, sp, #16
	sub sp, sp, #16
	ldr x10, [x9]
	str x10, [x29, #-104]
	mov x9, #2
	sub sp, sp, #16
	str x9, [x29, #-120]
	adrp x9, MOD@PAGE
	ldr x0, [x9, MOD@PAGEOFF]
	ldr x1, [x29, #-120]
	add sp, sp, #16
	sub x0, x0, x1
	str x0, [x29, #-112]
	sub sp, sp, #16
	ldr x9, [x29, #-112]
	str x9, [x29, #-120]
	ldr x9, [x29, #-104]
	str x9, [x29, #-128]
	bl _mod_pow
	add sp, sp, #16
	add sp, sp, #16
	sub sp, sp, #16
	str x0, [x29, #-104]
	sub sp, sp, #16
	mov x9, #8
	str x9, [x29, #-128]
	ldr x0, [x29, #-80]
	ldr x1, [x29, #-128]
	mul x0, x0, x1
	str x0, [x29, #-120]
	adrp x9, ifact@PAGE
	ldr x0, [x9, ifact@PAGEOFF]
	ldr x1, [x29, #-120]
	add sp, sp, #16
	add x0, x0, x1
	str x0, [x29, #-112]
	ldr x10, [x29, #-112]
	ldr x9, [x29, #-104]
	str x9, [x10]
	ldr x9, [x29, #-80]
	str x9, [x29, #-112]
.L_start_23:
	sub sp, sp, #16
	mov x9, #0
	str x9, [x29, #-128]
	ldr x0, [x29, #-112]
	ldr x1, [x29, #-128]
	cmp x0, x1
	cset x0, gt
	str x0, [x29, #-120]
	ldr x9, [x29, #-120]
	add sp, sp, #16
	cbz x9, .L_end_23
	sub sp, sp, #16
	sub sp, sp, #16
	mov x9, #8
	sub sp, sp, #16
	str x9, [x29, #-152]
	ldr x0, [x29, #-112]
	ldr x1, [x29, #-152]
	add sp, sp, #16
	mul x0, x0, x1
	str x0, [x29, #-144]
	adrp x9, ifact@PAGE
	ldr x0, [x9, ifact@PAGEOFF]
	ldr x1, [x29, #-144]
	add x0, x0, x1
	str x0, [x29, #-136]
	ldr x9, [x29, #-136]
	add sp, sp, #16
	sub sp, sp, #16
	ldr x10, [x9]
	str x10, [x29, #-136]
	ldr x0, [x29, #-136]
	ldr x1, [x29, #-112]
	add sp, sp, #16
	mul x0, x0, x1
	str x0, [x29, #-128]
	ldr x0, [x29, #-128]
	adrp x9, MOD@PAGE
	ldr x1, [x9, MOD@PAGEOFF]
	sdiv x2, x0, x1
	msub x0, x2, x1, x0
	str x0, [x29, #-120]
	sub sp, sp, #16
	mov x9, #1
	sub sp, sp, #16
	str x9, [x29, #-152]
	ldr x0, [x29, #-112]
	ldr x1, [x29, #-152]
	add sp, sp, #16
	sub x0, x0, x1
	str x0, [x29, #-144]
	mov x9, #8
	sub sp, sp, #16
	str x9, [x29, #-152]
	ldr x0, [x29, #-144]
	ldr x1, [x29, #-152]
	add sp, sp, #16
	mul x0, x0, x1
	str x0, [x29, #-136]
	adrp x9, ifact@PAGE
	ldr x0, [x9, ifact@PAGEOFF]
	ldr x1, [x29, #-136]
	add sp, sp, #16
	add x0, x0, x1
	str x0, [x29, #-128]
	ldr x10, [x29, #-128]
	ldr x9, [x29, #-120]
	str x9, [x10]
	mov x9, #1
	sub sp, sp, #16
	str x9, [x29, #-136]
	ldr x0, [x29, #-112]
	ldr x1, [x29, #-136]
	add sp, sp, #16
	sub x0, x0, x1
	str x0, [x29, #-128]
	ldr x9, [x29, #-128]
	str x9, [x29, #-112]
	add sp, sp, #16
	b .L_start_23
.L_end_23:
	sub sp, sp, #16
	mov x9, #0
	str x9, [x29, #-128]
	ldr x9, [x29, #-128]
	str x9, [x29, #-120]
	mov x9, #0
	sub sp, sp, #16
	str x9, [x29, #-136]
	ldr x9, [x29, #-136]
	str x9, [x29, #-128]
	add sp, sp, #16
	sub sp, sp, #16
	mov x9, #1
	str x9, [x29, #-144]
	ldr x9, [x29, #-144]
	str x9, [x29, #-136]
	sub sp, sp, #16
	mov x9, #1
	str x9, [x29, #-160]
	ldr x0, [x29, #-24]
	ldr x1, [x29, #-160]
	sub x0, x0, x1
	str x0, [x29, #-152]
	ldr x9, [x29, #-152]
	str x9, [x29, #-144]
	add sp, sp, #16
.L_start_24:
	sub sp, sp, #16
	mov x9, #0
	str x9, [x29, #-160]
	ldr x0, [x29, #-144]
	ldr x1, [x29, #-160]
	cmp x0, x1
	cset x0, ge
	str x0, [x29, #-152]
	ldr x9, [x29, #-152]
	add sp, sp, #16
	cbz x9, .L_end_24
	sub sp, sp, #16
	sub sp, sp, #16
	mov x9, #1
	str x9, [x29, #-176]
	ldr x0, [x29, #-144]
	ldr x1, [x29, #-176]
	mul x0, x0, x1
	str x0, [x29, #-168]
	adrp x9, str@PAGE
	ldr x0, [x9, str@PAGEOFF]
	ldr x1, [x29, #-168]
	add sp, sp, #16
	add x0, x0, x1
	str x0, [x29, #-160]
	ldr x9, [x29, #-160]
	ldrb w10, [x9]
	strb w10, [x29, #-153]
	ldrb w9, [x29, #-153]
	str x9, [x29, #-152]
	mov x9, #79
	sub sp, sp, #16
	str x9, [x29, #-168]
	ldr x0, [x29, #-152]
	ldr x1, [x29, #-168]
	add sp, sp, #16
	cmp x0, x1
	cset x0, eq
	str x0, [x29, #-160]
	ldr x9, [x29, #-160]
	cbz x9, .L_else_25
	mov x9, #1
	sub sp, sp, #16
	str x9, [x29, #-168]
	ldr x0, [x29, #-128]
	ldr x1, [x29, #-168]
	add sp, sp, #16
	add x0, x0, x1
	str x0, [x29, #-160]
	ldr x9, [x29, #-160]
	str x9, [x29, #-128]
	mov x9, #1
	sub sp, sp, #16
	str x9, [x29, #-168]
	ldr x0, [x29, #-144]
	ldr x1, [x29, #-168]
	add sp, sp, #16
	sub x0, x0, x1
	str x0, [x29, #-160]
	ldr x9, [x29, #-160]
	str x9, [x29, #-144]
	add sp, sp, #16
	b .L_start_24
	b .L_end_25
.L_else_25:
.L_end_25:
	sub sp, sp, #16
	ldr x0, [x29, #-8]
	ldr x1, [x29, #-120]
	mul x0, x0, x1
	str x0, [x29, #-176]
	ldr x0, [x29, #-128]
	ldr x1, [x29, #-176]
	sub x0, x0, x1
	str x0, [x29, #-168]
	ldr x9, [x29, #-168]
	str x9, [x29, #-160]
	add sp, sp, #16
	sub sp, sp, #16
	ldr x0, [x29, #-160]
	ldr x1, [x29, #-8]
	cmp x0, x1
	cset x0, lt
	str x0, [x29, #-176]
	sub sp, sp, #16
	mov x9, #0
	str x9, [x29, #-192]
	ldr x0, [x29, #-160]
	ldr x1, [x29, #-192]
	cmp x0, x1
	cset x0, lt
	str x0, [x29, #-184]
	ldr x0, [x29, #-176]
	ldr x1, [x29, #-184]
	add sp, sp, #16
	orr x0, x0, x1
	str x0, [x29, #-168]
	ldr x9, [x29, #-168]
	add sp, sp, #16
	cbz x9, .L_else_26
	mov x9, #0
	sub sp, sp, #16
	str x9, [x29, #-168]
	ldr x9, [x29, #-168]
	str x9, [x29, #-136]
	add sp, sp, #16
	add sp, sp, #16
	b .L_end_24
	b .L_end_26
.L_else_26:
.L_end_26:
	sub sp, sp, #16
	sub sp, sp, #16
	sub sp, sp, #16
	adrp x10, ifact@PAGE
	ldr x9, [x10, ifact@PAGEOFF]
	str x9, [x29, #-184]
	adrp x10, fact@PAGE
	ldr x9, [x10, fact@PAGEOFF]
	str x9, [x29, #-192]
	ldr x9, [x29, #-8]
	str x9, [x29, #-200]
	ldr x9, [x29, #-160]
	str x9, [x29, #-208]
	bl _choose
	add sp, sp, #16
	add sp, sp, #16
	sub sp, sp, #16
	str x0, [x29, #-184]
	ldr x9, [x29, #-184]
	str x9, [x29, #-168]
	add sp, sp, #16
	sub sp, sp, #16
	ldr x0, [x29, #-136]
	ldr x1, [x29, #-168]
	mul x0, x0, x1
	str x0, [x29, #-192]
	ldr x0, [x29, #-192]
	adrp x9, MOD@PAGE
	ldr x1, [x9, MOD@PAGEOFF]
	sdiv x2, x0, x1
	msub x0, x2, x1, x0
	str x0, [x29, #-184]
	ldr x9, [x29, #-184]
	str x9, [x29, #-136]
	add sp, sp, #16
	sub sp, sp, #16
	mov x9, #1
	str x9, [x29, #-192]
	ldr x0, [x29, #-120]
	ldr x1, [x29, #-192]
	add x0, x0, x1
	str x0, [x29, #-184]
	ldr x9, [x29, #-184]
	str x9, [x29, #-120]
	add sp, sp, #16
	sub sp, sp, #16
	mov x9, #1
	str x9, [x29, #-192]
	ldr x0, [x29, #-144]
	ldr x1, [x29, #-192]
	sub x0, x0, x1
	str x0, [x29, #-184]
	ldr x9, [x29, #-184]
	str x9, [x29, #-144]
	add sp, sp, #16
	add sp, sp, #16
	add sp, sp, #16
	b .L_start_24
.L_end_24:
	sub sp, sp, #16
	sub sp, sp, #16
	ldr x9, [x29, #-40]
	str x9, [x29, #-168]
	ldr x9, [x29, #-136]
	str x9, [x29, #-176]
	bl _mod_pow
	add sp, sp, #16
	sub sp, sp, #16
	str x0, [x29, #-168]
	ldr x9, [x29, #-168]
	str x9, [x29, #-152]
	add sp, sp, #16
	sub sp, sp, #16
	ldr x9, [x29, #-152]
	str x9, [x29, #-176]
	bl _print_int
	mov x9, #10
	str x9, [x29, #-176]
	sub sp, sp, #16
	ldr x9, [x29, #-176]
	str x9, [x29, #-192]
	bl _print_char
	bl _flush_output

	mov sp, x29
	ldp x29, x30, [sp], #16
	ret

)");
