
.data
buffer: .quad 0

.text
.global _print_char
_print_char:
	stp x29, x30, [sp, #-16]!
	mov x29, sp
	ldr x9, [x29, #16]
	adrp x10, buffer@PAGE
	str x9, [x10, buffer@PAGEOFF]
	mov x9, #4
	sub sp, sp, #16
	str x9, [x29, #-8]
	mov x9, #1
	str x9, [x29, #-16]
	adrp x9, buffer@PAGE
	add x9, x9, buffer@PAGEOFF
	sub sp, sp, #16
	str x9, [x29, #-24]
	mov x9, #1
	str x9, [x29, #-32]
	ldr x16, [x29, #-8]
	ldr x0, [x29, #-16]
	ldr x1, [x29, #-24]
	ldr x2, [x29, #-32]
	svc #0
	add sp, sp, #16
	add sp, sp, #16

	mov sp, x29
	ldp x29, x30, [sp], #16
	ret

.global _main
_main:
	stp x29, x30, [sp, #-16]!
	mov x29, sp
	sub sp, sp, #16
	sub sp, sp, #16
	sub sp, sp, #16
	sub sp, sp, #16
	add x9, x29, #-56
	str x9, [x29, #-64]
	ldr x9, [x29, #-64]
	str x9, [x29, #-8]
	mov x9, #0
	sub sp, sp, #16
	str x9, [x29, #-72]
	ldr x9, [x29, #-72]
	str x9, [x29, #-64]
	add sp, sp, #16
.L_start_0:
	sub sp, sp, #16
	mov x9, #3
	str x9, [x29, #-80]
	ldr x0, [x29, #-64]
	ldr x1, [x29, #-80]
	cmp x0, x1
	cset x0, ne
	str x0, [x29, #-72]
	ldr x9, [x29, #-72]
	add sp, sp, #16
	cbz x0, .L_end_0
	sub sp, sp, #16
	mov x9, #48
	str x9, [x29, #-80]
	ldr x0, [x29, #-80]
	ldr x1, [x29, #-64]
	add x0, x0, x1
	str x0, [x29, #-72]
	sub sp, sp, #16
	mov x9, #8
	str x9, [x29, #-96]
	ldr x0, [x29, #-64]
	ldr x1, [x29, #-96]
	mul x0, x0, x1
	str x0, [x29, #-88]
	ldr x0, [x29, #-8]
	ldr x1, [x29, #-88]
	add sp, sp, #16
	add x0, x0, x1
	str x0, [x29, #-80]
	ldr x10, [x29, #-80]
	ldr x9, [x29, #-72]
	str x9, [x10]
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
	add sp, sp, #16
	b .L_start_0
.L_end_0:
	mov x9, #0
	sub sp, sp, #16
	str x9, [x29, #-72]
	ldr x9, [x29, #-72]
	str x9, [x29, #-64]
	add sp, sp, #16
.L_start_1:
	sub sp, sp, #16
	mov x9, #3
	str x9, [x29, #-80]
	ldr x0, [x29, #-64]
	ldr x1, [x29, #-80]
	cmp x0, x1
	cset x0, ne
	str x0, [x29, #-72]
	ldr x9, [x29, #-72]
	add sp, sp, #16
	cbz x0, .L_end_1
	sub sp, sp, #16
	mov x9, #8
	sub sp, sp, #16
	str x9, [x29, #-88]
	ldr x0, [x29, #-64]
	ldr x1, [x29, #-88]
	add sp, sp, #16
	mul x0, x0, x1
	str x0, [x29, #-80]
	ldr x0, [x29, #-8]
	ldr x1, [x29, #-80]
	add x0, x0, x1
	str x0, [x29, #-72]
	ldr x9, [x29, #-72]
	add sp, sp, #16
	sub sp, sp, #16
	ldr x10, [x9]
	str x10, [x29, #-72]
	ldr x9, [x29, #-72]
	str x9, [x29, #-80]
	bl _print_char
	add sp, sp, #16
	str x0, [x29, #-64]
	sub sp, sp, #16
	mov x9, #1
	str x9, [x29, #-80]
	ldr x0, [x29, #-64]
	ldr x1, [x29, #-80]
	add x0, x0, x1
	str x0, [x29, #-72]
	ldr x9, [x29, #-72]
	str x9, [x29, #-64]
	add sp, sp, #16
	b .L_start_1
.L_end_1:
	mov x9, #10
	sub sp, sp, #16
	str x9, [x29, #-72]
	ldr x9, [x29, #-72]
	str x9, [x29, #-80]
	bl _print_char
	add sp, sp, #16
	str x0, [x29, #-64]

	mov sp, x29
	ldp x29, x30, [sp], #16
	ret

