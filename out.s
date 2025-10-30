.text
	.global _start

_start:
	bl _main
	mov x8, #93
	svc #0

.data
.align 3
READ_BUFFER_CAP: .quad 1048576
WRITE_BUFFER_CAP: .quad 32768
_galloc_array_0: .zero 1048576
input_buffer: .byte _galloc_array_0
input_index: .quad 0
_galloc_array_1: .zero 32768
output_buffer: .byte _galloc_array_1
output_index: .quad 0
n: .quad 0
m: .quad 0
_galloc_array_2: .zero 1600040
heights: .quad _galloc_array_2

.text
.global _init_input
_init_input:
	stp x29, x30, [sp, #-16]!
	mov x29, sp
	mov x9, #3
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
	mov x9, #4
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
	ldr x9, [x29, #-9]
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
	ldrb w9, [x29, #16]
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
.L_start_3:
	sub sp, sp, #16
	mov x9, #10
	str x9, [x29, #-48]
	ldr x0, [x29, #-8]
	ldr x1, [x29, #-48]
	cmp x0, x1
	cset x0, eq
	str x0, [x29, #-40]
	mov x9, #32
	sub sp, sp, #16
	str x9, [x29, #-56]
	ldr x0, [x29, #-8]
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
	ldr x9, [x29, #-32]
	cbz x9, .L_end_3
	bl _read_char
	sub sp, sp, #16
	str x0, [x29, #-40]
	ldr x9, [x29, #-40]
	str x9, [x29, #-8]
	add sp, sp, #16
	b .L_start_3
.L_end_3:
.L_start_4:
	sub sp, sp, #16
	mov x9, #10
	sub sp, sp, #16
	str x9, [x29, #-56]
	ldr x0, [x29, #-8]
	ldr x1, [x29, #-56]
	add sp, sp, #16
	cmp x0, x1
	cset x0, ne
	str x0, [x29, #-48]
	sub sp, sp, #16
	mov x9, #32
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
	mov x9, #0
	sub sp, sp, #16
	str x9, [x29, #-56]
	ldr x0, [x29, #-8]
	ldr x1, [x29, #-56]
	add sp, sp, #16
	cmp x0, x1
	cset x0, ne
	str x0, [x29, #-48]
	ldr x0, [x29, #-40]
	ldr x1, [x29, #-48]
	add sp, sp, #16
	and x0, x0, x1
	str x0, [x29, #-32]
	ldr x9, [x29, #-32]
	cbz x9, .L_end_4
	sub sp, sp, #16
	mov x9, #10
	sub sp, sp, #16
	str x9, [x29, #-56]
	ldr x0, [x29, #-24]
	ldr x1, [x29, #-56]
	add sp, sp, #16
	mul x0, x0, x1
	str x0, [x29, #-48]
	ldr x0, [x29, #-48]
	ldr x1, [x29, #-8]
	add x0, x0, x1
	str x0, [x29, #-40]
	mov x9, #48
	str x9, [x29, #-48]
	ldr x0, [x29, #-40]
	ldr x1, [x29, #-48]
	add sp, sp, #16
	sub x0, x0, x1
	str x0, [x29, #-32]
	ldr x9, [x29, #-32]
	str x9, [x29, #-24]
	bl _read_char
	sub sp, sp, #16
	str x0, [x29, #-40]
	ldr x9, [x29, #-40]
	str x9, [x29, #-8]
	add sp, sp, #16
	b .L_start_4
.L_end_4:
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
	cbz x9, .L_else_5
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
	b .L_end_5
.L_else_5:
.L_end_5:
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
	sub sp, sp, #16
	add x9, x29, #-168
	str x9, [x29, #-176]
	ldr x9, [x29, #-176]
	str x9, [x29, #-8]
	mov x9, #0
	sub sp, sp, #16
	str x9, [x29, #-184]
	ldr x9, [x29, #-184]
	str x9, [x29, #-176]
	add sp, sp, #16
.L_start_6:
	sub sp, sp, #16
	mov x9, #0
	str x9, [x29, #-192]
	ldr x0, [x29, #16]
	ldr x1, [x29, #-192]
	cmp x0, x1
	cset x0, gt
	str x0, [x29, #-184]
	ldr x9, [x29, #-184]
	add sp, sp, #16
	cbz x9, .L_end_6
	sub sp, sp, #16
	mov x9, #10
	sub sp, sp, #16
	str x9, [x29, #-200]
	ldr x0, [x29, #16]
	ldr x1, [x29, #-200]
	add sp, sp, #16
	sdiv x2, x0, x1
	msub x0, x2, x1, x0
	str x0, [x29, #-192]
	ldr x9, [x29, #-192]
	str x9, [x29, #-184]
	mov x9, #10
	sub sp, sp, #16
	str x9, [x29, #-200]
	ldr x0, [x29, #16]
	ldr x1, [x29, #-200]
	add sp, sp, #16
	sdiv x0, x0, x1
	str x0, [x29, #-192]
	ldr x9, [x29, #-192]
	str x9, [x29, #16]
	mov x9, #48
	sub sp, sp, #16
	str x9, [x29, #-200]
	ldr x0, [x29, #-184]
	ldr x1, [x29, #-200]
	add sp, sp, #16
	add x0, x0, x1
	str x0, [x29, #-192]
	sub sp, sp, #16
	mov x9, #8
	sub sp, sp, #16
	str x9, [x29, #-216]
	ldr x0, [x29, #-176]
	ldr x1, [x29, #-216]
	add sp, sp, #16
	mul x0, x0, x1
	str x0, [x29, #-208]
	ldr x0, [x29, #-8]
	ldr x1, [x29, #-208]
	add x0, x0, x1
	str x0, [x29, #-200]
	ldr x10, [x29, #-200]
	ldr x9, [x29, #-192]
	str x9, [x10]
	add sp, sp, #16
	sub sp, sp, #16
	mov x9, #1
	str x9, [x29, #-208]
	ldr x0, [x29, #-176]
	ldr x1, [x29, #-208]
	add x0, x0, x1
	str x0, [x29, #-200]
	ldr x9, [x29, #-200]
	str x9, [x29, #-176]
	add sp, sp, #16
	add sp, sp, #16
	b .L_start_6
.L_end_6:
.L_start_7:
	sub sp, sp, #16
	mov x9, #0
	str x9, [x29, #-192]
	ldr x0, [x29, #-176]
	ldr x1, [x29, #-192]
	cmp x0, x1
	cset x0, gt
	str x0, [x29, #-184]
	ldr x9, [x29, #-184]
	add sp, sp, #16
	cbz x9, .L_end_7
	sub sp, sp, #16
	mov x9, #1
	str x9, [x29, #-192]
	ldr x0, [x29, #-176]
	ldr x1, [x29, #-192]
	sub x0, x0, x1
	str x0, [x29, #-184]
	ldr x9, [x29, #-184]
	str x9, [x29, #-176]
	add sp, sp, #16
	sub sp, sp, #16
	mov x9, #8
	sub sp, sp, #16
	str x9, [x29, #-200]
	ldr x0, [x29, #-176]
	ldr x1, [x29, #-200]
	add sp, sp, #16
	mul x0, x0, x1
	str x0, [x29, #-192]
	ldr x0, [x29, #-8]
	ldr x1, [x29, #-192]
	add x0, x0, x1
	str x0, [x29, #-184]
	ldr x9, [x29, #-184]
	add sp, sp, #16
	sub sp, sp, #16
	ldr x10, [x9]
	str x10, [x29, #-184]
	ldr x9, [x29, #-184]
	str x9, [x29, #-192]
	bl _print_char
	add sp, sp, #16
	b .L_start_7
.L_end_7:

	mov sp, x29
	ldp x29, x30, [sp], #16
	ret

.global _max
_max:
	stp x29, x30, [sp, #-16]!
	mov x29, sp
	sub sp, sp, #16
	ldr x0, [x29, #16]
	ldr x1, [x29, #24]
	cmp x0, x1
	cset x0, gt
	str x0, [x29, #-8]
	ldr x9, [x29, #-8]
	add sp, sp, #16
	cbz x9, .L_else_8
	ldr x0, [x29, #16]

	mov sp, x29
	ldp x29, x30, [sp], #16
	ret

	b .L_end_8
.L_else_8:
	ldr x0, [x29, #24]

	mov sp, x29
	ldp x29, x30, [sp], #16
	ret

.L_end_8:

	mov sp, x29
	ldp x29, x30, [sp], #16
	ret

.global _min
_min:
	stp x29, x30, [sp, #-16]!
	mov x29, sp
	sub sp, sp, #16
	ldr x0, [x29, #16]
	ldr x1, [x29, #24]
	cmp x0, x1
	cset x0, lt
	str x0, [x29, #-8]
	ldr x9, [x29, #-8]
	add sp, sp, #16
	cbz x9, .L_else_9
	ldr x0, [x29, #16]

	mov sp, x29
	ldp x29, x30, [sp], #16
	ret

	b .L_end_9
.L_else_9:
	ldr x0, [x29, #24]

	mov sp, x29
	ldp x29, x30, [sp], #16
	ret

.L_end_9:

	mov sp, x29
	ldp x29, x30, [sp], #16
	ret

.global _main
_main:
	stp x29, x30, [sp, #-16]!
	mov x29, sp
	bl _init_input
	bl _read_int
	sub sp, sp, #16
	str x0, [x29, #-8]
	ldr x9, [x29, #-8]
	adrp x10, n@PAGE
	str x9, [x10, n@PAGEOFF]
	add sp, sp, #16
	bl _read_int
	sub sp, sp, #16
	str x0, [x29, #-8]
	ldr x9, [x29, #-8]
	adrp x10, m@PAGE
	str x9, [x10, m@PAGEOFF]
	add sp, sp, #16
	sub sp, sp, #16
	mov x9, #0
	str x9, [x29, #-16]
	ldr x9, [x29, #-16]
	str x9, [x29, #-8]
.L_start_10:
	ldr x0, [x29, #-8]
	adrp x9, n@PAGE
	ldr x1, [x9, n@PAGEOFF]
	cmp x0, x1
	cset x0, lt
	str x0, [x29, #-16]
	ldr x9, [x29, #-16]
	cbz x9, .L_end_10
	bl _read_int
	sub sp, sp, #16
	str x0, [x29, #-24]
	sub sp, sp, #16
	mov x9, #8
	str x9, [x29, #-48]
	ldr x0, [x29, #-8]
	ldr x1, [x29, #-48]
	mul x0, x0, x1
	str x0, [x29, #-40]
	adrp x9, heights@PAGE
	ldr x0, [x9, heights@PAGEOFF]
	ldr x1, [x29, #-40]
	add sp, sp, #16
	add x0, x0, x1
	str x0, [x29, #-32]
	ldr x10, [x29, #-32]
	ldr x9, [x29, #-24]
	str x9, [x10]
	mov x9, #1
	sub sp, sp, #16
	str x9, [x29, #-40]
	ldr x0, [x29, #-8]
	ldr x1, [x29, #-40]
	add sp, sp, #16
	add x0, x0, x1
	str x0, [x29, #-32]
	ldr x9, [x29, #-32]
	str x9, [x29, #-8]
	add sp, sp, #16
	b .L_start_10
.L_end_10:
	mov x9, #0
	str x9, [x29, #-16]
	ldr x9, [x29, #-16]
	str x9, [x29, #-8]
.L_start_11:
	ldr x0, [x29, #-8]
	adrp x9, m@PAGE
	ldr x1, [x9, m@PAGEOFF]
	cmp x0, x1
	cset x0, lt
	str x0, [x29, #-16]
	ldr x9, [x29, #-16]
	cbz x9, .L_end_11
	bl _read_int
	sub sp, sp, #16
	str x0, [x29, #-24]
	ldr x9, [x29, #-24]
	str x9, [x29, #-16]
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
.L_start_12:
	sub sp, sp, #16
	ldr x0, [x29, #-32]
	adrp x9, n@PAGE
	ldr x1, [x9, n@PAGEOFF]
	cmp x0, x1
	cset x0, lt
	str x0, [x29, #-48]
	sub sp, sp, #16
	ldr x0, [x29, #-24]
	ldr x1, [x29, #-16]
	cmp x0, x1
	cset x0, lt
	str x0, [x29, #-56]
	ldr x0, [x29, #-48]
	ldr x1, [x29, #-56]
	add sp, sp, #16
	and x0, x0, x1
	str x0, [x29, #-40]
	ldr x9, [x29, #-40]
	add sp, sp, #16
	cbz x9, .L_end_12
	sub sp, sp, #16
	mov x9, #0
	str x9, [x29, #-48]
	sub sp, sp, #16
	sub sp, sp, #16
	mov x9, #8
	str x9, [x29, #-80]
	ldr x0, [x29, #-32]
	ldr x1, [x29, #-80]
	mul x0, x0, x1
	str x0, [x29, #-72]
	adrp x9, heights@PAGE
	ldr x0, [x9, heights@PAGEOFF]
	ldr x1, [x29, #-72]
	add sp, sp, #16
	add x0, x0, x1
	str x0, [x29, #-64]
	ldr x9, [x29, #-64]
	ldr x10, [x9]
	str x10, [x29, #-64]
	sub sp, sp, #16
	ldr x9, [x29, #-16]
	str x9, [x29, #-72]
	ldr x9, [x29, #-64]
	str x9, [x29, #-80]
	bl _min
	add sp, sp, #16
	str x0, [x29, #-64]
	ldr x0, [x29, #-64]
	ldr x1, [x29, #-24]
	sub x0, x0, x1
	str x0, [x29, #-56]
	sub sp, sp, #16
	ldr x9, [x29, #-56]
	str x9, [x29, #-72]
	ldr x9, [x29, #-48]
	str x9, [x29, #-80]
	bl _max
	add sp, sp, #16
	sub sp, sp, #16
	str x0, [x29, #-72]
	ldr x9, [x29, #-72]
	str x9, [x29, #-40]
	add sp, sp, #16
	sub sp, sp, #16
	sub sp, sp, #16
	mov x9, #8
	str x9, [x29, #-96]
	ldr x0, [x29, #-32]
	ldr x1, [x29, #-96]
	mul x0, x0, x1
	str x0, [x29, #-88]
	adrp x9, heights@PAGE
	ldr x0, [x9, heights@PAGEOFF]
	ldr x1, [x29, #-88]
	add sp, sp, #16
	add x0, x0, x1
	str x0, [x29, #-80]
	ldr x9, [x29, #-80]
	ldr x10, [x9]
	str x10, [x29, #-80]
	ldr x0, [x29, #-80]
	ldr x1, [x29, #-40]
	add x0, x0, x1
	str x0, [x29, #-72]
	sub sp, sp, #16
	mov x9, #8
	str x9, [x29, #-96]
	ldr x0, [x29, #-32]
	ldr x1, [x29, #-96]
	mul x0, x0, x1
	str x0, [x29, #-88]
	adrp x9, heights@PAGE
	ldr x0, [x9, heights@PAGEOFF]
	ldr x1, [x29, #-88]
	add sp, sp, #16
	add x0, x0, x1
	str x0, [x29, #-80]
	ldr x10, [x29, #-80]
	ldr x9, [x29, #-72]
	str x9, [x10]
	ldr x0, [x29, #-24]
	ldr x1, [x29, #-40]
	add x0, x0, x1
	str x0, [x29, #-80]
	ldr x9, [x29, #-80]
	str x9, [x29, #-24]
	mov x9, #1
	sub sp, sp, #16
	str x9, [x29, #-88]
	ldr x0, [x29, #-32]
	ldr x1, [x29, #-88]
	add sp, sp, #16
	add x0, x0, x1
	str x0, [x29, #-80]
	ldr x9, [x29, #-80]
	str x9, [x29, #-32]
	add sp, sp, #16
	add sp, sp, #16
	add sp, sp, #16
	b .L_start_12
.L_end_12:
	sub sp, sp, #16
	mov x9, #1
	str x9, [x29, #-48]
	ldr x0, [x29, #-8]
	ldr x1, [x29, #-48]
	add x0, x0, x1
	str x0, [x29, #-40]
	ldr x9, [x29, #-40]
	str x9, [x29, #-8]
	add sp, sp, #16
	add sp, sp, #16
	b .L_start_11
.L_end_11:
	mov x9, #0
	str x9, [x29, #-16]
	ldr x9, [x29, #-16]
	str x9, [x29, #-8]
.L_start_13:
	ldr x0, [x29, #-8]
	adrp x9, n@PAGE
	ldr x1, [x9, n@PAGEOFF]
	cmp x0, x1
	cset x0, lt
	str x0, [x29, #-16]
	ldr x9, [x29, #-16]
	cbz x9, .L_end_13
	sub sp, sp, #16
	mov x9, #8
	str x9, [x29, #-32]
	ldr x0, [x29, #-8]
	ldr x1, [x29, #-32]
	mul x0, x0, x1
	str x0, [x29, #-24]
	adrp x9, heights@PAGE
	ldr x0, [x9, heights@PAGEOFF]
	ldr x1, [x29, #-24]
	add sp, sp, #16
	add x0, x0, x1
	str x0, [x29, #-16]
	ldr x9, [x29, #-16]
	ldr x10, [x9]
	str x10, [x29, #-16]
	sub sp, sp, #16
	ldr x9, [x29, #-16]
	str x9, [x29, #-32]
	bl _print_int
	mov x9, #10
	str x9, [x29, #-32]
	sub sp, sp, #16
	ldr x9, [x29, #-32]
	str x9, [x29, #-48]
	bl _print_char
	mov x9, #1
	sub sp, sp, #16
	str x9, [x29, #-56]
	ldr x0, [x29, #-8]
	ldr x1, [x29, #-56]
	add sp, sp, #16
	add x0, x0, x1
	str x0, [x29, #-48]
	ldr x9, [x29, #-48]
	str x9, [x29, #-8]
	add sp, sp, #16
	add sp, sp, #16
	b .L_start_13
.L_end_13:
	bl _flush_output

	mov sp, x29
	ldp x29, x30, [sp], #16
	ret

