asm(R"(
.section .data
.align 8

.section .bss
.align 8

.section .text
.global lower_bound_int
lower_bound_int:
push %rbp
movq %rsp,%rbp

movq $0,%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq -8(%rbp),%r10
movq %r10,-16(%rbp)
subq $16,%rsp
movq 24(%rbp),%r10
movq %r10,-24(%rbp)
.L_start_0:
movq -16(%rbp),%rax
movq -24(%rbp),%rbx
cmp %rbx,%rax
setl %al
movzbl %al,%eax
movq %rax,-32(%rbp)
movq -32(%rbp),%r10
test %r10,%r10
jz .L_end_0
subq $16,%rsp
movq -24(%rbp),%rax
movq -16(%rbp),%rbx
subq %rbx,%rax
movq %rax,-48(%rbp)
movq $2,%r10
subq $16,%rsp
movq %r10,-56(%rbp)
movq -48(%rbp),%rax
movq -56(%rbp),%rbx
addq $16,%rsp
cqto
idivq %rbx
movq %rax,-40(%rbp)
movq -16(%rbp),%rax
movq -40(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-32(%rbp)
subq $16,%rsp
movq -32(%rbp),%r10
movq %r10,-40(%rbp)
subq $16,%rsp
movq $8,%r10
subq $16,%rsp
movq %r10,-72(%rbp)
movq -40(%rbp),%rax
movq -72(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-64(%rbp)
movq 16(%rbp),%rax
movq -64(%rbp),%rbx
addq %rbx,%rax
movq %rax,-56(%rbp)
movq -56(%rbp),%r10
addq $16,%rsp
subq $16,%rsp
movq (%r10),%r11
movq %r11,-56(%rbp)
movq -56(%rbp),%rax
movq 32(%rbp),%rbx
addq $16,%rsp
cmp %rbx,%rax
setl %al
movzbl %al,%eax
movq %rax,-48(%rbp)
movq -48(%rbp),%r10
test %r10,%r10
jz .L_else_1
movq $1,%r10
subq $16,%rsp
movq %r10,-56(%rbp)
movq -40(%rbp),%rax
movq -56(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-48(%rbp)
movq -48(%rbp),%r10
movq %r10,-16(%rbp)
jmp .L_end_1
.L_else_1:
movq -40(%rbp),%r10
movq %r10,-24(%rbp)
.L_end_1:
addq $16,%rsp
jmp .L_start_0
.L_end_0:
movq -16(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret


movq %rbp,%rsp
pop %rbp
ret

.global present_insert
present_insert:
push %rbp
movq %rsp,%rbp

movq 24(%rbp),%r10
subq $16,%rsp
movq (%r10),%r11
movq %r11,-8(%rbp)
movq -8(%rbp),%r10
movq %r10,-16(%rbp)
subq $16,%rsp
subq $16,%rsp
movq 32(%rbp),%r10
movq %r10,-32(%rbp)
movq -16(%rbp),%r10
movq %r10,-40(%rbp)
movq 16(%rbp),%r10
movq %r10,-48(%rbp)
call lower_bound_int
addq $16,%rsp
addq $16,%rsp
subq $16,%rsp
movq %rax,-24(%rbp)
movq -24(%rbp),%r10
movq %r10,-32(%rbp)
subq $16,%rsp
movq -16(%rbp),%r10
movq %r10,-40(%rbp)
.L_start_2:
movq -40(%rbp),%rax
movq -32(%rbp),%rbx
cmp %rbx,%rax
setg %al
movzbl %al,%eax
movq %rax,-48(%rbp)
movq -48(%rbp),%r10
test %r10,%r10
jz .L_end_2
subq $16,%rsp
movq $1,%r10
subq $16,%rsp
movq %r10,-72(%rbp)
movq -40(%rbp),%rax
movq -72(%rbp),%rbx
addq $16,%rsp
subq %rbx,%rax
movq %rax,-64(%rbp)
movq $8,%r10
subq $16,%rsp
movq %r10,-72(%rbp)
movq -64(%rbp),%rax
movq -72(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-56(%rbp)
movq 16(%rbp),%rax
movq -56(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-48(%rbp)
movq -48(%rbp),%r10
movq (%r10),%r11
movq %r11,-48(%rbp)
subq $16,%rsp
movq $8,%r10
subq $16,%rsp
movq %r10,-72(%rbp)
movq -40(%rbp),%rax
movq -72(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-64(%rbp)
movq 16(%rbp),%rax
movq -64(%rbp),%rbx
addq %rbx,%rax
movq %rax,-56(%rbp)
movq -56(%rbp),%r11
movq -48(%rbp),%r10
movq %r10,(%r11)
addq $16,%rsp
subq $16,%rsp
movq $1,%r10
movq %r10,-64(%rbp)
movq -40(%rbp),%rax
movq -64(%rbp),%rbx
subq %rbx,%rax
movq %rax,-56(%rbp)
movq -56(%rbp),%r10
movq %r10,-40(%rbp)
addq $16,%rsp
jmp .L_start_2
.L_end_2:
subq $16,%rsp
movq $8,%r10
movq %r10,-64(%rbp)
movq -32(%rbp),%rax
movq -64(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-56(%rbp)
movq 16(%rbp),%rax
movq -56(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-48(%rbp)
movq -48(%rbp),%r11
movq 32(%rbp),%r10
movq %r10,(%r11)
movq $1,%r10
subq $16,%rsp
movq %r10,-56(%rbp)
movq -16(%rbp),%rax
movq -56(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-48(%rbp)
movq 24(%rbp),%r11
movq -48(%rbp),%r10
movq %r10,(%r11)

movq %rbp,%rsp
pop %rbp
ret

.global present_erase
present_erase:
push %rbp
movq %rsp,%rbp

movq 24(%rbp),%r10
subq $16,%rsp
movq (%r10),%r11
movq %r11,-8(%rbp)
movq -8(%rbp),%r10
movq %r10,-16(%rbp)
subq $16,%rsp
subq $16,%rsp
movq 32(%rbp),%r10
movq %r10,-32(%rbp)
movq -16(%rbp),%r10
movq %r10,-40(%rbp)
movq 16(%rbp),%r10
movq %r10,-48(%rbp)
call lower_bound_int
addq $16,%rsp
addq $16,%rsp
subq $16,%rsp
movq %rax,-24(%rbp)
movq -24(%rbp),%r10
movq %r10,-32(%rbp)
subq $16,%rsp
movq -32(%rbp),%rax
movq -16(%rbp),%rbx
cmp %rbx,%rax
setge %al
movzbl %al,%eax
movq %rax,-40(%rbp)
movq -40(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_3
movq $0,%r10
subq $16,%rsp
movq %r10,-40(%rbp)
movq -40(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

addq $16,%rsp
jmp .L_end_3
.L_else_3:
.L_end_3:
subq $16,%rsp
subq $16,%rsp
movq $8,%r10
movq %r10,-64(%rbp)
movq -32(%rbp),%rax
movq -64(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-56(%rbp)
movq 16(%rbp),%rax
movq -56(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-48(%rbp)
movq -48(%rbp),%r10
movq (%r10),%r11
movq %r11,-48(%rbp)
movq -48(%rbp),%rax
movq 32(%rbp),%rbx
cmp %rbx,%rax
setne %al
movzbl %al,%eax
movq %rax,-40(%rbp)
movq -40(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_4
movq $0,%r10
subq $16,%rsp
movq %r10,-40(%rbp)
movq -40(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

addq $16,%rsp
jmp .L_end_4
.L_else_4:
.L_end_4:
subq $16,%rsp
movq -32(%rbp),%r10
movq %r10,-40(%rbp)
.L_start_5:
subq $16,%rsp
movq $1,%r10
movq %r10,-64(%rbp)
movq -40(%rbp),%rax
movq -64(%rbp),%rbx
addq %rbx,%rax
movq %rax,-56(%rbp)
movq -56(%rbp),%rax
movq -16(%rbp),%rbx
addq $16,%rsp
cmp %rbx,%rax
setl %al
movzbl %al,%eax
movq %rax,-48(%rbp)
movq -48(%rbp),%r10
test %r10,%r10
jz .L_end_5
subq $16,%rsp
movq $1,%r10
subq $16,%rsp
movq %r10,-72(%rbp)
movq -40(%rbp),%rax
movq -72(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-64(%rbp)
movq $8,%r10
subq $16,%rsp
movq %r10,-72(%rbp)
movq -64(%rbp),%rax
movq -72(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-56(%rbp)
movq 16(%rbp),%rax
movq -56(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-48(%rbp)
movq -48(%rbp),%r10
movq (%r10),%r11
movq %r11,-48(%rbp)
subq $16,%rsp
movq $8,%r10
subq $16,%rsp
movq %r10,-72(%rbp)
movq -40(%rbp),%rax
movq -72(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-64(%rbp)
movq 16(%rbp),%rax
movq -64(%rbp),%rbx
addq %rbx,%rax
movq %rax,-56(%rbp)
movq -56(%rbp),%r11
movq -48(%rbp),%r10
movq %r10,(%r11)
addq $16,%rsp
subq $16,%rsp
movq $1,%r10
movq %r10,-64(%rbp)
movq -40(%rbp),%rax
movq -64(%rbp),%rbx
addq %rbx,%rax
movq %rax,-56(%rbp)
movq -56(%rbp),%r10
movq %r10,-40(%rbp)
addq $16,%rsp
jmp .L_start_5
.L_end_5:
movq $1,%r10
subq $16,%rsp
movq %r10,-56(%rbp)
movq -16(%rbp),%rax
movq -56(%rbp),%rbx
addq $16,%rsp
subq %rbx,%rax
movq %rax,-48(%rbp)
movq 24(%rbp),%r11
movq -48(%rbp),%r10
movq %r10,(%r11)

movq %rbp,%rsp
pop %rbp
ret

.global heap_top_valid
heap_top_valid:
push %rbp
movq %rsp,%rbp

.L_start_6:
subq $16,%rsp
movq 16(%rbp),%r10
movq %r10,-16(%rbp)
call heap_size
movq %rax,-16(%rbp)
movq $0,%r10
subq $16,%rsp
movq %r10,-24(%rbp)
movq -16(%rbp),%rax
movq -24(%rbp),%rbx
addq $16,%rsp
cmp %rbx,%rax
setg %al
movzbl %al,%eax
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_end_6
subq $16,%rsp
movq 16(%rbp),%r10
movq %r10,-16(%rbp)
call heap_peek
addq $16,%rsp
subq $16,%rsp
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
movq %r10,-16(%rbp)
subq $16,%rsp
subq $16,%rsp
movq $8,%r10
movq %r10,-48(%rbp)
movq -16(%rbp),%rax
movq -48(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-40(%rbp)
movq 24(%rbp),%rax
movq -40(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-32(%rbp)
movq -32(%rbp),%r10
movq (%r10),%r11
movq %r11,-32(%rbp)
movq -32(%rbp),%rax
movq 32(%rbp),%rbx
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-24(%rbp)
movq -24(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_7
movq -16(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

jmp .L_end_7
.L_else_7:
.L_end_7:
subq $16,%rsp
movq 16(%rbp),%r10
movq %r10,-32(%rbp)
call heap_pop
addq $16,%rsp
subq $16,%rsp
movq %rax,-24(%rbp)
addq $16,%rsp
addq $16,%rsp
jmp .L_start_6
.L_end_6:
movq $0,%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq -8(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret


movq %rbp,%rsp
pop %rbp
ret

.global change
change:
push %rbp
movq %rsp,%rbp

subq $16,%rsp
movq $8,%r10
subq $16,%rsp
movq %r10,-24(%rbp)
movq 64(%rbp),%rax
movq -24(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-16(%rbp)
movq 16(%rbp),%rax
movq -16(%rbp),%rbx
addq %rbx,%rax
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
addq $16,%rsp
subq $16,%rsp
movq (%r10),%r11
movq %r11,-8(%rbp)
movq -8(%rbp),%r10
movq %r10,-16(%rbp)
subq $16,%rsp
subq $16,%rsp
movq $8,%r10
movq %r10,-48(%rbp)
movq -16(%rbp),%rax
movq -48(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-40(%rbp)
movq 24(%rbp),%rax
movq -40(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-32(%rbp)
movq -32(%rbp),%r10
movq (%r10),%r11
movq %r11,-32(%rbp)
movq $1,%r10
subq $16,%rsp
movq %r10,-40(%rbp)
movq -32(%rbp),%rax
movq -40(%rbp),%rbx
addq $16,%rsp
subq %rbx,%rax
movq %rax,-24(%rbp)
subq $16,%rsp
movq $8,%r10
movq %r10,-48(%rbp)
movq -16(%rbp),%rax
movq -48(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-40(%rbp)
movq 24(%rbp),%rax
movq -40(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-32(%rbp)
movq -32(%rbp),%r11
movq -24(%rbp),%r10
movq %r10,(%r11)
movq $1,%r10
subq $16,%rsp
movq %r10,-40(%rbp)
movq -16(%rbp),%rax
movq -40(%rbp),%rbx
addq $16,%rsp
cmp %rbx,%rax
setge %al
movzbl %al,%eax
movq %rax,-32(%rbp)
movq -32(%rbp),%r10
test %r10,%r10
jz .L_else_8
subq $16,%rsp
movq $8,%r10
subq $16,%rsp
movq %r10,-56(%rbp)
movq -16(%rbp),%rax
movq -56(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-48(%rbp)
movq 24(%rbp),%rax
movq -48(%rbp),%rbx
addq %rbx,%rax
movq %rax,-40(%rbp)
movq -40(%rbp),%r10
addq $16,%rsp
subq $16,%rsp
movq (%r10),%r11
movq %r11,-40(%rbp)
movq $0,%r10
movq %r10,-48(%rbp)
movq -40(%rbp),%rax
movq -48(%rbp),%rbx
addq $16,%rsp
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-32(%rbp)
movq -32(%rbp),%r10
test %r10,%r10
jz .L_else_9
subq $16,%rsp
movq -16(%rbp),%r10
movq %r10,-32(%rbp)
movq 40(%rbp),%r10
movq %r10,-40(%rbp)
movq 32(%rbp),%r10
movq %r10,-48(%rbp)
call present_erase
addq $16,%rsp
jmp .L_end_9
.L_else_9:
.L_end_9:
jmp .L_end_8
.L_else_8:
.L_end_8:
movq -16(%rbp),%rax
movq 72(%rbp),%rbx
addq %rbx,%rax
movq %rax,-32(%rbp)
subq $16,%rsp
movq -32(%rbp),%r10
movq %r10,-40(%rbp)
subq $16,%rsp
movq $8,%r10
movq %r10,-64(%rbp)
movq 64(%rbp),%rax
movq -64(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-56(%rbp)
movq 16(%rbp),%rax
movq -56(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-48(%rbp)
movq -48(%rbp),%r11
movq -40(%rbp),%r10
movq %r10,(%r11)
subq $16,%rsp
movq $8,%r10
subq $16,%rsp
movq %r10,-72(%rbp)
movq -40(%rbp),%rax
movq -72(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-64(%rbp)
movq 24(%rbp),%rax
movq -64(%rbp),%rbx
addq %rbx,%rax
movq %rax,-56(%rbp)
movq -56(%rbp),%r10
addq $16,%rsp
subq $16,%rsp
movq (%r10),%r11
movq %r11,-56(%rbp)
movq $1,%r10
movq %r10,-64(%rbp)
movq -56(%rbp),%rax
movq -64(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-48(%rbp)
subq $16,%rsp
movq $8,%r10
subq $16,%rsp
movq %r10,-72(%rbp)
movq -40(%rbp),%rax
movq -72(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-64(%rbp)
movq 24(%rbp),%rax
movq -64(%rbp),%rbx
addq %rbx,%rax
movq %rax,-56(%rbp)
movq -56(%rbp),%r11
movq -48(%rbp),%r10
movq %r10,(%r11)
addq $16,%rsp
subq $16,%rsp
movq $1,%r10
movq %r10,-64(%rbp)
movq -40(%rbp),%rax
movq -64(%rbp),%rbx
cmp %rbx,%rax
setge %al
movzbl %al,%eax
movq %rax,-56(%rbp)
movq -56(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_10
subq $16,%rsp
subq $16,%rsp
movq $8,%r10
movq %r10,-80(%rbp)
movq -40(%rbp),%rax
movq -80(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-72(%rbp)
movq 24(%rbp),%rax
movq -72(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-64(%rbp)
movq -64(%rbp),%r10
movq (%r10),%r11
movq %r11,-64(%rbp)
movq $1,%r10
subq $16,%rsp
movq %r10,-72(%rbp)
movq -64(%rbp),%rax
movq -72(%rbp),%rbx
addq $16,%rsp
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-56(%rbp)
movq -56(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_11
subq $16,%rsp
subq $16,%rsp
movq -40(%rbp),%r10
movq %r10,-64(%rbp)
movq 40(%rbp),%r10
movq %r10,-72(%rbp)
movq 32(%rbp),%r10
movq %r10,-80(%rbp)
call present_insert
addq $16,%rsp
addq $16,%rsp
jmp .L_end_11
.L_else_11:
.L_end_11:
subq $16,%rsp
subq $16,%rsp
movq $8,%r10
movq %r10,-80(%rbp)
movq -40(%rbp),%rax
movq -80(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-72(%rbp)
movq 48(%rbp),%rax
movq -72(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-64(%rbp)
movq -64(%rbp),%r10
movq (%r10),%r11
movq %r11,-64(%rbp)
movq $0,%r10
subq $16,%rsp
movq %r10,-72(%rbp)
movq -64(%rbp),%rax
movq -72(%rbp),%rbx
addq $16,%rsp
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-56(%rbp)
movq -56(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_12
movq $0,%r10
subq $16,%rsp
movq %r10,-56(%rbp)
movq -56(%rbp),%r10
movq %r10,-64(%rbp)
call heap_new
addq $16,%rsp
subq $16,%rsp
movq %rax,-56(%rbp)
subq $16,%rsp
movq $8,%r10
movq %r10,-80(%rbp)
movq -40(%rbp),%rax
movq -80(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-72(%rbp)
movq 48(%rbp),%rax
movq -72(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-64(%rbp)
movq -64(%rbp),%r11
movq -56(%rbp),%r10
movq %r10,(%r11)
addq $16,%rsp
jmp .L_end_12
.L_else_12:
.L_end_12:
subq $16,%rsp
subq $16,%rsp
movq $8,%r10
movq %r10,-80(%rbp)
movq -40(%rbp),%rax
movq -80(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-72(%rbp)
movq 56(%rbp),%rax
movq -72(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-64(%rbp)
movq -64(%rbp),%r10
movq (%r10),%r11
movq %r11,-64(%rbp)
movq $0,%r10
subq $16,%rsp
movq %r10,-72(%rbp)
movq -64(%rbp),%rax
movq -72(%rbp),%rbx
addq $16,%rsp
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-56(%rbp)
movq -56(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_13
movq $1,%r10
subq $16,%rsp
movq %r10,-56(%rbp)
movq -56(%rbp),%r10
movq %r10,-64(%rbp)
call heap_new
addq $16,%rsp
subq $16,%rsp
movq %rax,-56(%rbp)
subq $16,%rsp
movq $8,%r10
movq %r10,-80(%rbp)
movq -40(%rbp),%rax
movq -80(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-72(%rbp)
movq 56(%rbp),%rax
movq -72(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-64(%rbp)
movq -64(%rbp),%r11
movq -56(%rbp),%r10
movq %r10,(%r11)
addq $16,%rsp
jmp .L_end_13
.L_else_13:
.L_end_13:
subq $16,%rsp
movq $8,%r10
subq $16,%rsp
movq %r10,-72(%rbp)
movq -40(%rbp),%rax
movq -72(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-64(%rbp)
movq 48(%rbp),%rax
movq -64(%rbp),%rbx
addq %rbx,%rax
movq %rax,-56(%rbp)
movq -56(%rbp),%r10
addq $16,%rsp
subq $16,%rsp
movq (%r10),%r11
movq %r11,-56(%rbp)
subq $16,%rsp
movq 64(%rbp),%r10
movq %r10,-72(%rbp)
movq -56(%rbp),%r10
movq %r10,-80(%rbp)
call heap_push
addq $16,%rsp
addq $16,%rsp
subq $16,%rsp
movq $8,%r10
subq $16,%rsp
movq %r10,-72(%rbp)
movq -40(%rbp),%rax
movq -72(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-64(%rbp)
movq 56(%rbp),%rax
movq -64(%rbp),%rbx
addq %rbx,%rax
movq %rax,-56(%rbp)
movq -56(%rbp),%r10
addq $16,%rsp
subq $16,%rsp
movq (%r10),%r11
movq %r11,-56(%rbp)
subq $16,%rsp
movq 64(%rbp),%r10
movq %r10,-72(%rbp)
movq -56(%rbp),%r10
movq %r10,-80(%rbp)
call heap_push
addq $16,%rsp
addq $16,%rsp
jmp .L_end_10
.L_else_10:
.L_end_10:

movq %rbp,%rsp
pop %rbp
ret

.global main
main:
push %rbp
movq %rsp,%rbp

call init_input
call read_int
subq $16,%rsp
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
movq %r10,-16(%rbp)
call read_int
subq $16,%rsp
movq %rax,-24(%rbp)
movq -24(%rbp),%r10
movq %r10,-32(%rbp)
subq $16,%rsp
movq $8,%r10
movq %r10,-48(%rbp)
movq -16(%rbp),%rax
movq -48(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-40(%rbp)
movq -40(%rbp),%r10
movq %r10,-48(%rbp)
call malloc
addq $16,%rsp
subq $16,%rsp
movq %rax,-40(%rbp)
movq -40(%rbp),%r10
movq %r10,-48(%rbp)
movq $0,%r10
subq $16,%rsp
movq %r10,-56(%rbp)
movq -56(%rbp),%r10
movq %r10,-64(%rbp)
.L_start_14:
subq $16,%rsp
movq -64(%rbp),%rax
movq -16(%rbp),%rbx
cmp %rbx,%rax
setl %al
movzbl %al,%eax
movq %rax,-72(%rbp)
movq -72(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_end_14
call read_int
subq $16,%rsp
movq %rax,-72(%rbp)
subq $16,%rsp
movq $8,%r10
movq %r10,-96(%rbp)
movq -64(%rbp),%rax
movq -96(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-88(%rbp)
movq -48(%rbp),%rax
movq -88(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-80(%rbp)
movq -80(%rbp),%r11
movq -72(%rbp),%r10
movq %r10,(%r11)
movq $1,%r10
subq $16,%rsp
movq %r10,-88(%rbp)
movq -64(%rbp),%rax
movq -88(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-80(%rbp)
movq -80(%rbp),%r10
movq %r10,-64(%rbp)
addq $16,%rsp
jmp .L_start_14
.L_end_14:
subq $16,%rsp
movq $1,%r10
subq $16,%rsp
movq %r10,-88(%rbp)
movq -16(%rbp),%rax
movq -88(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-80(%rbp)
movq $8,%r10
subq $16,%rsp
movq %r10,-88(%rbp)
movq -80(%rbp),%rax
movq -88(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-72(%rbp)
movq -72(%rbp),%r10
movq %r10,-80(%rbp)
call malloc
addq $16,%rsp
subq $16,%rsp
movq %rax,-72(%rbp)
movq -72(%rbp),%r10
movq %r10,-80(%rbp)
movq $0,%r10
subq $16,%rsp
movq %r10,-88(%rbp)
movq -88(%rbp),%r10
movq %r10,-64(%rbp)
addq $16,%rsp
.L_start_15:
subq $16,%rsp
movq -64(%rbp),%rax
movq -16(%rbp),%rbx
cmp %rbx,%rax
setle %al
movzbl %al,%eax
movq %rax,-88(%rbp)
movq -88(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_end_15
movq $0,%r10
subq $16,%rsp
movq %r10,-88(%rbp)
subq $16,%rsp
movq $8,%r10
movq %r10,-112(%rbp)
movq -64(%rbp),%rax
movq -112(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-104(%rbp)
movq -80(%rbp),%rax
movq -104(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-96(%rbp)
movq -96(%rbp),%r11
movq -88(%rbp),%r10
movq %r10,(%r11)
movq $1,%r10
subq $16,%rsp
movq %r10,-104(%rbp)
movq -64(%rbp),%rax
movq -104(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-96(%rbp)
movq -96(%rbp),%r10
movq %r10,-64(%rbp)
addq $16,%rsp
jmp .L_start_15
.L_end_15:
movq $0,%r10
subq $16,%rsp
movq %r10,-88(%rbp)
movq -88(%rbp),%r10
movq %r10,-64(%rbp)
addq $16,%rsp
.L_start_16:
subq $16,%rsp
movq -64(%rbp),%rax
movq -16(%rbp),%rbx
cmp %rbx,%rax
setl %al
movzbl %al,%eax
movq %rax,-88(%rbp)
movq -88(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_end_16
subq $16,%rsp
movq $8,%r10
subq $16,%rsp
movq %r10,-104(%rbp)
movq -64(%rbp),%rax
movq -104(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-96(%rbp)
movq -48(%rbp),%rax
movq -96(%rbp),%rbx
addq %rbx,%rax
movq %rax,-88(%rbp)
movq -88(%rbp),%r10
addq $16,%rsp
subq $16,%rsp
movq (%r10),%r11
movq %r11,-88(%rbp)
movq -88(%rbp),%r10
movq %r10,-96(%rbp)
subq $16,%rsp
subq $16,%rsp
movq $8,%r10
movq %r10,-128(%rbp)
movq -96(%rbp),%rax
movq -128(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-120(%rbp)
movq -80(%rbp),%rax
movq -120(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-112(%rbp)
movq -112(%rbp),%r10
movq (%r10),%r11
movq %r11,-112(%rbp)
movq $1,%r10
subq $16,%rsp
movq %r10,-120(%rbp)
movq -112(%rbp),%rax
movq -120(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-104(%rbp)
subq $16,%rsp
movq $8,%r10
movq %r10,-128(%rbp)
movq -96(%rbp),%rax
movq -128(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-120(%rbp)
movq -80(%rbp),%rax
movq -120(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-112(%rbp)
movq -112(%rbp),%r11
movq -104(%rbp),%r10
movq %r10,(%r11)
movq $1,%r10
subq $16,%rsp
movq %r10,-120(%rbp)
movq -64(%rbp),%rax
movq -120(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-112(%rbp)
movq -112(%rbp),%r10
movq %r10,-64(%rbp)
addq $16,%rsp
addq $16,%rsp
jmp .L_start_16
.L_end_16:
subq $16,%rsp
movq $1,%r10
subq $16,%rsp
movq %r10,-104(%rbp)
movq -16(%rbp),%rax
movq -104(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-96(%rbp)
movq $8,%r10
subq $16,%rsp
movq %r10,-104(%rbp)
movq -96(%rbp),%rax
movq -104(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-88(%rbp)
movq -88(%rbp),%r10
movq %r10,-96(%rbp)
call malloc
addq $16,%rsp
subq $16,%rsp
movq %rax,-88(%rbp)
movq -88(%rbp),%r10
movq %r10,-96(%rbp)
movq $0,%r10
subq $16,%rsp
movq %r10,-104(%rbp)
movq -104(%rbp),%r10
movq %r10,-64(%rbp)
addq $16,%rsp
.L_start_17:
subq $16,%rsp
movq -64(%rbp),%rax
movq -16(%rbp),%rbx
cmp %rbx,%rax
setle %al
movzbl %al,%eax
movq %rax,-104(%rbp)
movq -104(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_end_17
movq $0,%r10
subq $16,%rsp
movq %r10,-104(%rbp)
subq $16,%rsp
movq $8,%r10
movq %r10,-128(%rbp)
movq -64(%rbp),%rax
movq -128(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-120(%rbp)
movq -96(%rbp),%rax
movq -120(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-112(%rbp)
movq -112(%rbp),%r11
movq -104(%rbp),%r10
movq %r10,(%r11)
movq $1,%r10
subq $16,%rsp
movq %r10,-120(%rbp)
movq -64(%rbp),%rax
movq -120(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-112(%rbp)
movq -112(%rbp),%r10
movq %r10,-64(%rbp)
addq $16,%rsp
jmp .L_start_17
.L_end_17:
subq $16,%rsp
movq $1,%r10
subq $16,%rsp
movq %r10,-120(%rbp)
movq -16(%rbp),%rax
movq -120(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-112(%rbp)
movq $8,%r10
subq $16,%rsp
movq %r10,-120(%rbp)
movq -112(%rbp),%rax
movq -120(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-104(%rbp)
movq -104(%rbp),%r10
movq %r10,-112(%rbp)
call malloc
addq $16,%rsp
subq $16,%rsp
movq %rax,-104(%rbp)
movq -104(%rbp),%r10
movq %r10,-112(%rbp)
subq $16,%rsp
movq $1,%r10
subq $16,%rsp
movq %r10,-136(%rbp)
movq -16(%rbp),%rax
movq -136(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-128(%rbp)
movq $8,%r10
subq $16,%rsp
movq %r10,-136(%rbp)
movq -128(%rbp),%rax
movq -136(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-120(%rbp)
movq -120(%rbp),%r10
movq %r10,-128(%rbp)
call malloc
addq $16,%rsp
subq $16,%rsp
movq %rax,-120(%rbp)
movq -120(%rbp),%r10
movq %r10,-128(%rbp)
movq $0,%r10
subq $16,%rsp
movq %r10,-136(%rbp)
movq -136(%rbp),%r10
movq %r10,-64(%rbp)
addq $16,%rsp
.L_start_18:
subq $16,%rsp
movq -64(%rbp),%rax
movq -16(%rbp),%rbx
cmp %rbx,%rax
setle %al
movzbl %al,%eax
movq %rax,-136(%rbp)
movq -136(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_end_18
movq $0,%r10
subq $16,%rsp
movq %r10,-136(%rbp)
subq $16,%rsp
movq $8,%r10
movq %r10,-160(%rbp)
movq -64(%rbp),%rax
movq -160(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-152(%rbp)
movq -112(%rbp),%rax
movq -152(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-144(%rbp)
movq -144(%rbp),%r11
movq -136(%rbp),%r10
movq %r10,(%r11)
movq $0,%r10
movq %r10,-144(%rbp)
subq $16,%rsp
movq $8,%r10
subq $16,%rsp
movq %r10,-168(%rbp)
movq -64(%rbp),%rax
movq -168(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-160(%rbp)
movq -128(%rbp),%rax
movq -160(%rbp),%rbx
addq %rbx,%rax
movq %rax,-152(%rbp)
movq -152(%rbp),%r11
movq -144(%rbp),%r10
movq %r10,(%r11)
addq $16,%rsp
subq $16,%rsp
movq $1,%r10
movq %r10,-160(%rbp)
movq -64(%rbp),%rax
movq -160(%rbp),%rbx
addq %rbx,%rax
movq %rax,-152(%rbp)
movq -152(%rbp),%r10
movq %r10,-64(%rbp)
addq $16,%rsp
addq $16,%rsp
jmp .L_start_18
.L_end_18:
movq $1,%r10
subq $16,%rsp
movq %r10,-136(%rbp)
movq -136(%rbp),%r10
movq %r10,-64(%rbp)
addq $16,%rsp
.L_start_19:
subq $16,%rsp
movq -64(%rbp),%rax
movq -16(%rbp),%rbx
cmp %rbx,%rax
setle %al
movzbl %al,%eax
movq %rax,-136(%rbp)
movq -136(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_end_19
subq $16,%rsp
movq $8,%r10
subq $16,%rsp
movq %r10,-152(%rbp)
movq -64(%rbp),%rax
movq -152(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-144(%rbp)
movq -80(%rbp),%rax
movq -144(%rbp),%rbx
addq %rbx,%rax
movq %rax,-136(%rbp)
movq -136(%rbp),%r10
addq $16,%rsp
subq $16,%rsp
movq (%r10),%r11
movq %r11,-136(%rbp)
movq -136(%rbp),%r10
movq %r10,-144(%rbp)
subq $16,%rsp
subq $16,%rsp
movq $8,%r10
movq %r10,-176(%rbp)
movq -144(%rbp),%rax
movq -176(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-168(%rbp)
movq -96(%rbp),%rax
movq -168(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-160(%rbp)
movq -160(%rbp),%r10
movq (%r10),%r11
movq %r11,-160(%rbp)
movq $1,%r10
subq $16,%rsp
movq %r10,-168(%rbp)
movq -160(%rbp),%rax
movq -168(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-152(%rbp)
subq $16,%rsp
movq $8,%r10
movq %r10,-176(%rbp)
movq -144(%rbp),%rax
movq -176(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-168(%rbp)
movq -96(%rbp),%rax
movq -168(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-160(%rbp)
movq -160(%rbp),%r11
movq -152(%rbp),%r10
movq %r10,(%r11)
movq $1,%r10
subq $16,%rsp
movq %r10,-168(%rbp)
movq -64(%rbp),%rax
movq -168(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-160(%rbp)
movq -160(%rbp),%r10
movq %r10,-64(%rbp)
addq $16,%rsp
addq $16,%rsp
jmp .L_start_19
.L_end_19:
subq $16,%rsp
movq $1,%r10
subq $16,%rsp
movq %r10,-152(%rbp)
movq -16(%rbp),%rax
movq -152(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-144(%rbp)
movq $8,%r10
subq $16,%rsp
movq %r10,-152(%rbp)
movq -144(%rbp),%rax
movq -152(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-136(%rbp)
movq -136(%rbp),%r10
movq %r10,-144(%rbp)
call malloc
addq $16,%rsp
subq $16,%rsp
movq %rax,-136(%rbp)
movq -136(%rbp),%r10
movq %r10,-144(%rbp)
movq $0,%r10
subq $16,%rsp
movq %r10,-152(%rbp)
movq -152(%rbp),%r10
movq %r10,-160(%rbp)
movq $1,%r10
subq $16,%rsp
movq %r10,-168(%rbp)
movq -168(%rbp),%r10
movq %r10,-64(%rbp)
addq $16,%rsp
.L_start_20:
subq $16,%rsp
movq -64(%rbp),%rax
movq -16(%rbp),%rbx
cmp %rbx,%rax
setle %al
movzbl %al,%eax
movq %rax,-168(%rbp)
movq -168(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_end_20
subq $16,%rsp
subq $16,%rsp
movq $8,%r10
movq %r10,-192(%rbp)
movq -64(%rbp),%rax
movq -192(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-184(%rbp)
movq -96(%rbp),%rax
movq -184(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-176(%rbp)
movq -176(%rbp),%r10
movq (%r10),%r11
movq %r11,-176(%rbp)
movq $0,%r10
subq $16,%rsp
movq %r10,-184(%rbp)
movq -176(%rbp),%rax
movq -184(%rbp),%rbx
addq $16,%rsp
cmp %rbx,%rax
setg %al
movzbl %al,%eax
movq %rax,-168(%rbp)
movq -168(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_21
subq $16,%rsp
movq $8,%r10
subq $16,%rsp
movq %r10,-184(%rbp)
movq -160(%rbp),%rax
movq -184(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-176(%rbp)
movq -144(%rbp),%rax
movq -176(%rbp),%rbx
addq %rbx,%rax
movq %rax,-168(%rbp)
movq -168(%rbp),%r11
movq -64(%rbp),%r10
movq %r10,(%r11)
addq $16,%rsp
subq $16,%rsp
movq $1,%r10
movq %r10,-176(%rbp)
movq -160(%rbp),%rax
movq -176(%rbp),%rbx
addq %rbx,%rax
movq %rax,-168(%rbp)
movq -168(%rbp),%r10
movq %r10,-160(%rbp)
addq $16,%rsp
jmp .L_end_21
.L_else_21:
.L_end_21:
subq $16,%rsp
movq $1,%r10
movq %r10,-176(%rbp)
movq -64(%rbp),%rax
movq -176(%rbp),%rbx
addq %rbx,%rax
movq %rax,-168(%rbp)
movq -168(%rbp),%r10
movq %r10,-64(%rbp)
addq $16,%rsp
jmp .L_start_20
.L_end_20:
movq $1,%r10
subq $16,%rsp
movq %r10,-168(%rbp)
movq -168(%rbp),%r10
movq %r10,-64(%rbp)
addq $16,%rsp
.L_start_22:
subq $16,%rsp
movq -64(%rbp),%rax
movq -16(%rbp),%rbx
cmp %rbx,%rax
setle %al
movzbl %al,%eax
movq %rax,-168(%rbp)
movq -168(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_end_22
subq $16,%rsp
subq $16,%rsp
movq $8,%r10
movq %r10,-192(%rbp)
movq -64(%rbp),%rax
movq -192(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-184(%rbp)
movq -96(%rbp),%rax
movq -184(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-176(%rbp)
movq -176(%rbp),%r10
movq (%r10),%r11
movq %r11,-176(%rbp)
movq $0,%r10
subq $16,%rsp
movq %r10,-184(%rbp)
movq -176(%rbp),%rax
movq -184(%rbp),%rbx
addq $16,%rsp
cmp %rbx,%rax
setg %al
movzbl %al,%eax
movq %rax,-168(%rbp)
movq -168(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_23
movq $0,%r10
subq $16,%rsp
movq %r10,-168(%rbp)
movq -168(%rbp),%r10
movq %r10,-176(%rbp)
call heap_new
addq $16,%rsp
subq $16,%rsp
movq %rax,-168(%rbp)
subq $16,%rsp
movq $8,%r10
movq %r10,-192(%rbp)
movq -64(%rbp),%rax
movq -192(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-184(%rbp)
movq -112(%rbp),%rax
movq -184(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-176(%rbp)
movq -176(%rbp),%r11
movq -168(%rbp),%r10
movq %r10,(%r11)
movq $1,%r10
movq %r10,-176(%rbp)
subq $16,%rsp
movq -176(%rbp),%r10
movq %r10,-192(%rbp)
call heap_new
addq $16,%rsp
movq %rax,-176(%rbp)
subq $16,%rsp
movq $8,%r10
subq $16,%rsp
movq %r10,-200(%rbp)
movq -64(%rbp),%rax
movq -200(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-192(%rbp)
movq -128(%rbp),%rax
movq -192(%rbp),%rbx
addq %rbx,%rax
movq %rax,-184(%rbp)
movq -184(%rbp),%r11
movq -176(%rbp),%r10
movq %r10,(%r11)
addq $16,%rsp
addq $16,%rsp
jmp .L_end_23
.L_else_23:
.L_end_23:
subq $16,%rsp
movq $1,%r10
movq %r10,-176(%rbp)
movq -64(%rbp),%rax
movq -176(%rbp),%rbx
addq %rbx,%rax
movq %rax,-168(%rbp)
movq -168(%rbp),%r10
movq %r10,-64(%rbp)
addq $16,%rsp
jmp .L_start_22
.L_end_22:
movq $1,%r10
subq $16,%rsp
movq %r10,-168(%rbp)
movq -168(%rbp),%r10
movq %r10,-64(%rbp)
addq $16,%rsp
.L_start_24:
subq $16,%rsp
movq -64(%rbp),%rax
movq -16(%rbp),%rbx
cmp %rbx,%rax
setle %al
movzbl %al,%eax
movq %rax,-168(%rbp)
movq -168(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_end_24
subq $16,%rsp
movq $8,%r10
subq $16,%rsp
movq %r10,-184(%rbp)
movq -64(%rbp),%rax
movq -184(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-176(%rbp)
movq -80(%rbp),%rax
movq -176(%rbp),%rbx
addq %rbx,%rax
movq %rax,-168(%rbp)
movq -168(%rbp),%r10
addq $16,%rsp
subq $16,%rsp
movq (%r10),%r11
movq %r11,-168(%rbp)
movq -168(%rbp),%r10
movq %r10,-176(%rbp)
subq $16,%rsp
movq $1,%r10
movq %r10,-192(%rbp)
movq -176(%rbp),%rax
movq -192(%rbp),%rbx
cmp %rbx,%rax
setge %al
movzbl %al,%eax
movq %rax,-184(%rbp)
movq -184(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_25
subq $16,%rsp
movq $8,%r10
subq $16,%rsp
movq %r10,-200(%rbp)
movq -176(%rbp),%rax
movq -200(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-192(%rbp)
movq -112(%rbp),%rax
movq -192(%rbp),%rbx
addq %rbx,%rax
movq %rax,-184(%rbp)
movq -184(%rbp),%r10
addq $16,%rsp
subq $16,%rsp
movq (%r10),%r11
movq %r11,-184(%rbp)
subq $16,%rsp
movq -64(%rbp),%r10
movq %r10,-200(%rbp)
movq -184(%rbp),%r10
movq %r10,-208(%rbp)
call heap_push
addq $16,%rsp
addq $16,%rsp
subq $16,%rsp
movq $8,%r10
subq $16,%rsp
movq %r10,-200(%rbp)
movq -176(%rbp),%rax
movq -200(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-192(%rbp)
movq -128(%rbp),%rax
movq -192(%rbp),%rbx
addq %rbx,%rax
movq %rax,-184(%rbp)
movq -184(%rbp),%r10
addq $16,%rsp
subq $16,%rsp
movq (%r10),%r11
movq %r11,-184(%rbp)
subq $16,%rsp
movq -64(%rbp),%r10
movq %r10,-200(%rbp)
movq -184(%rbp),%r10
movq %r10,-208(%rbp)
call heap_push
addq $16,%rsp
addq $16,%rsp
jmp .L_end_25
.L_else_25:
.L_end_25:
subq $16,%rsp
movq $1,%r10
movq %r10,-192(%rbp)
movq -64(%rbp),%rax
movq -192(%rbp),%rbx
addq %rbx,%rax
movq %rax,-184(%rbp)
movq -184(%rbp),%r10
movq %r10,-64(%rbp)
addq $16,%rsp
addq $16,%rsp
jmp .L_start_24
.L_end_24:
subq $16,%rsp
movq -32(%rbp),%r10
movq %r10,-168(%rbp)
.L_start_26:
movq $0,%r10
subq $16,%rsp
movq %r10,-184(%rbp)
movq -168(%rbp),%rax
movq -184(%rbp),%rbx
addq $16,%rsp
cmp %rbx,%rax
setg %al
movzbl %al,%eax
movq %rax,-176(%rbp)
movq -176(%rbp),%r10
test %r10,%r10
jz .L_end_26
call read_int
movq %rax,-176(%rbp)
subq $16,%rsp
movq -176(%rbp),%r10
movq %r10,-184(%rbp)
call read_int
movq %rax,-192(%rbp)
subq $16,%rsp
movq -192(%rbp),%r10
movq %r10,-200(%rbp)
movq $1,%r10
subq $16,%rsp
movq %r10,-216(%rbp)
movq -184(%rbp),%rax
movq -216(%rbp),%rbx
addq $16,%rsp
subq %rbx,%rax
movq %rax,-208(%rbp)
movq -208(%rbp),%r10
movq %r10,-184(%rbp)
movq $0,%r10
subq $16,%rsp
movq %r10,-216(%rbp)
movq $1,%r10
movq %r10,-224(%rbp)
movq -216(%rbp),%rax
movq -224(%rbp),%rbx
addq $16,%rsp
subq %rbx,%rax
movq %rax,-208(%rbp)
subq $16,%rsp
movq -208(%rbp),%r10
movq %r10,-216(%rbp)
leaq -160(%rbp),%r10
movq %r10,-224(%rbp)
subq $16,%rsp
movq $8,%r10
subq $16,%rsp
movq %r10,-248(%rbp)
movq -184(%rbp),%rax
movq -248(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-240(%rbp)
movq -48(%rbp),%rax
movq -240(%rbp),%rbx
addq %rbx,%rax
movq %rax,-232(%rbp)
movq -232(%rbp),%r10
addq $16,%rsp
subq $16,%rsp
movq (%r10),%r11
movq %r11,-232(%rbp)
subq $16,%rsp
subq $16,%rsp
subq $16,%rsp
subq $16,%rsp
movq -216(%rbp),%r10
movq %r10,-248(%rbp)
movq -232(%rbp),%r10
movq %r10,-256(%rbp)
movq -128(%rbp),%r10
movq %r10,-264(%rbp)
movq -112(%rbp),%r10
movq %r10,-272(%rbp)
movq -224(%rbp),%r10
movq %r10,-280(%rbp)
movq -144(%rbp),%r10
movq %r10,-288(%rbp)
movq -96(%rbp),%r10
movq %r10,-296(%rbp)
movq -80(%rbp),%r10
movq %r10,-304(%rbp)
call change
addq $16,%rsp
addq $16,%rsp
addq $16,%rsp
addq $16,%rsp
addq $16,%rsp
subq $16,%rsp
movq $8,%r10
movq %r10,-240(%rbp)
movq -184(%rbp),%rax
movq -240(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-232(%rbp)
movq -48(%rbp),%rax
movq -232(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-224(%rbp)
movq -224(%rbp),%r11
movq -200(%rbp),%r10
movq %r10,(%r11)
leaq -160(%rbp),%r10
movq %r10,-224(%rbp)
subq $16,%rsp
movq $8,%r10
subq $16,%rsp
movq %r10,-248(%rbp)
movq -184(%rbp),%rax
movq -248(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-240(%rbp)
movq -48(%rbp),%rax
movq -240(%rbp),%rbx
addq %rbx,%rax
movq %rax,-232(%rbp)
movq -232(%rbp),%r10
addq $16,%rsp
subq $16,%rsp
movq (%r10),%r11
movq %r11,-232(%rbp)
movq $1,%r10
movq %r10,-240(%rbp)
subq $16,%rsp
subq $16,%rsp
subq $16,%rsp
subq $16,%rsp
movq -240(%rbp),%r10
movq %r10,-248(%rbp)
movq -232(%rbp),%r10
movq %r10,-256(%rbp)
movq -128(%rbp),%r10
movq %r10,-264(%rbp)
movq -112(%rbp),%r10
movq %r10,-272(%rbp)
movq -224(%rbp),%r10
movq %r10,-280(%rbp)
movq -144(%rbp),%r10
movq %r10,-288(%rbp)
movq -96(%rbp),%r10
movq %r10,-296(%rbp)
movq -80(%rbp),%r10
movq %r10,-304(%rbp)
call change
addq $16,%rsp
addq $16,%rsp
addq $16,%rsp
addq $16,%rsp
addq $16,%rsp
movq $0,%r10
movq %r10,-224(%rbp)
subq $16,%rsp
movq -224(%rbp),%r10
movq %r10,-232(%rbp)
movq $0,%r10
subq $16,%rsp
movq %r10,-248(%rbp)
movq -160(%rbp),%rax
movq -248(%rbp),%rbx
addq $16,%rsp
cmp %rbx,%rax
setg %al
movzbl %al,%eax
movq %rax,-240(%rbp)
movq -240(%rbp),%r10
test %r10,%r10
jz .L_else_27
subq $16,%rsp
movq $1,%r10
subq $16,%rsp
movq %r10,-264(%rbp)
movq -160(%rbp),%rax
movq -264(%rbp),%rbx
addq $16,%rsp
subq %rbx,%rax
movq %rax,-256(%rbp)
movq $8,%r10
subq $16,%rsp
movq %r10,-264(%rbp)
movq -256(%rbp),%rax
movq -264(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-248(%rbp)
movq -144(%rbp),%rax
movq -248(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-240(%rbp)
movq -240(%rbp),%r10
movq (%r10),%r11
movq %r11,-240(%rbp)
subq $16,%rsp
movq -240(%rbp),%r10
movq %r10,-248(%rbp)
movq $8,%r10
subq $16,%rsp
movq %r10,-264(%rbp)
movq -160(%rbp),%rax
movq -264(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-256(%rbp)
subq $16,%rsp
movq -256(%rbp),%r10
movq %r10,-272(%rbp)
call malloc
addq $16,%rsp
movq %rax,-256(%rbp)
subq $16,%rsp
movq -256(%rbp),%r10
movq %r10,-264(%rbp)
movq $8,%r10
subq $16,%rsp
movq %r10,-280(%rbp)
movq -160(%rbp),%rax
movq -280(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-272(%rbp)
subq $16,%rsp
movq -272(%rbp),%r10
movq %r10,-288(%rbp)
call malloc
addq $16,%rsp
movq %rax,-272(%rbp)
subq $16,%rsp
movq -272(%rbp),%r10
movq %r10,-280(%rbp)
movq $0,%r10
movq %r10,-288(%rbp)
movq -288(%rbp),%r10
movq %r10,-64(%rbp)
.L_start_28:
movq -64(%rbp),%rax
movq -160(%rbp),%rbx
cmp %rbx,%rax
setl %al
movzbl %al,%eax
movq %rax,-288(%rbp)
movq -288(%rbp),%r10
test %r10,%r10
jz .L_end_28
subq $16,%rsp
movq $8,%r10
movq %r10,-304(%rbp)
movq -64(%rbp),%rax
movq -304(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-296(%rbp)
movq -144(%rbp),%rax
movq -296(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-288(%rbp)
movq -288(%rbp),%r10
movq (%r10),%r11
movq %r11,-288(%rbp)
subq $16,%rsp
movq -288(%rbp),%r10
movq %r10,-296(%rbp)
subq $16,%rsp
movq $8,%r10
movq %r10,-320(%rbp)
movq -296(%rbp),%rax
movq -320(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-312(%rbp)
movq -112(%rbp),%rax
movq -312(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-304(%rbp)
movq -304(%rbp),%r10
movq (%r10),%r11
movq %r11,-304(%rbp)
subq $16,%rsp
subq $16,%rsp
movq -296(%rbp),%r10
movq %r10,-320(%rbp)
movq -80(%rbp),%r10
movq %r10,-328(%rbp)
movq -304(%rbp),%r10
movq %r10,-336(%rbp)
call heap_top_valid
addq $16,%rsp
addq $16,%rsp
movq %rax,-304(%rbp)
subq $16,%rsp
movq $8,%r10
subq $16,%rsp
movq %r10,-328(%rbp)
movq -64(%rbp),%rax
movq -328(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-320(%rbp)
movq -264(%rbp),%rax
movq -320(%rbp),%rbx
addq %rbx,%rax
movq %rax,-312(%rbp)
movq -312(%rbp),%r11
movq -304(%rbp),%r10
movq %r10,(%r11)
addq $16,%rsp
subq $16,%rsp
movq $8,%r10
subq $16,%rsp
movq %r10,-328(%rbp)
movq -296(%rbp),%rax
movq -328(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-320(%rbp)
movq -128(%rbp),%rax
movq -320(%rbp),%rbx
addq %rbx,%rax
movq %rax,-312(%rbp)
movq -312(%rbp),%r10
addq $16,%rsp
subq $16,%rsp
movq (%r10),%r11
movq %r11,-312(%rbp)
subq $16,%rsp
movq -296(%rbp),%r10
movq %r10,-320(%rbp)
movq -80(%rbp),%r10
movq %r10,-328(%rbp)
movq -312(%rbp),%r10
movq %r10,-336(%rbp)
call heap_top_valid
addq $16,%rsp
addq $16,%rsp
subq $16,%rsp
movq %rax,-312(%rbp)
subq $16,%rsp
movq $8,%r10
movq %r10,-336(%rbp)
movq -64(%rbp),%rax
movq -336(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-328(%rbp)
movq -280(%rbp),%rax
movq -328(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-320(%rbp)
movq -320(%rbp),%r11
movq -312(%rbp),%r10
movq %r10,(%r11)
movq $1,%r10
subq $16,%rsp
movq %r10,-328(%rbp)
movq -64(%rbp),%rax
movq -328(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-320(%rbp)
movq -320(%rbp),%r10
movq %r10,-64(%rbp)
addq $16,%rsp
addq $16,%rsp
jmp .L_start_28
.L_end_28:
movq $2,%r10
subq $16,%rsp
movq %r10,-296(%rbp)
movq -160(%rbp),%rax
movq -296(%rbp),%rbx
addq $16,%rsp
subq %rbx,%rax
movq %rax,-288(%rbp)
movq -288(%rbp),%r10
movq %r10,-64(%rbp)
.L_start_29:
movq $0,%r10
subq $16,%rsp
movq %r10,-296(%rbp)
movq -64(%rbp),%rax
movq -296(%rbp),%rbx
addq $16,%rsp
cmp %rbx,%rax
setge %al
movzbl %al,%eax
movq %rax,-288(%rbp)
movq -288(%rbp),%r10
test %r10,%r10
jz .L_end_29
subq $16,%rsp
movq $8,%r10
subq $16,%rsp
movq %r10,-312(%rbp)
movq -64(%rbp),%rax
movq -312(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-304(%rbp)
movq -280(%rbp),%rax
movq -304(%rbp),%rbx
addq %rbx,%rax
movq %rax,-296(%rbp)
movq -296(%rbp),%r10
addq $16,%rsp
subq $16,%rsp
movq (%r10),%r11
movq %r11,-296(%rbp)
subq $16,%rsp
movq $1,%r10
subq $16,%rsp
movq %r10,-328(%rbp)
movq -64(%rbp),%rax
movq -328(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-320(%rbp)
movq $8,%r10
subq $16,%rsp
movq %r10,-328(%rbp)
movq -320(%rbp),%rax
movq -328(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-312(%rbp)
movq -280(%rbp),%rax
movq -312(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-304(%rbp)
movq -304(%rbp),%r10
movq (%r10),%r11
movq %r11,-304(%rbp)
movq -296(%rbp),%rax
movq -304(%rbp),%rbx
addq $16,%rsp
cmp %rbx,%rax
setl %al
movzbl %al,%eax
movq %rax,-288(%rbp)
movq -288(%rbp),%r10
test %r10,%r10
jz .L_else_30
subq $16,%rsp
movq $1,%r10
subq $16,%rsp
movq %r10,-312(%rbp)
movq -64(%rbp),%rax
movq -312(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-304(%rbp)
movq $8,%r10
subq $16,%rsp
movq %r10,-312(%rbp)
movq -304(%rbp),%rax
movq -312(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-296(%rbp)
movq -280(%rbp),%rax
movq -296(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-288(%rbp)
movq -288(%rbp),%r10
movq (%r10),%r11
movq %r11,-288(%rbp)
subq $16,%rsp
movq $8,%r10
subq $16,%rsp
movq %r10,-312(%rbp)
movq -64(%rbp),%rax
movq -312(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-304(%rbp)
movq -280(%rbp),%rax
movq -304(%rbp),%rbx
addq %rbx,%rax
movq %rax,-296(%rbp)
movq -296(%rbp),%r11
movq -288(%rbp),%r10
movq %r10,(%r11)
addq $16,%rsp
jmp .L_end_30
.L_else_30:
.L_end_30:
movq $1,%r10
subq $16,%rsp
movq %r10,-296(%rbp)
movq -64(%rbp),%rax
movq -296(%rbp),%rbx
addq $16,%rsp
subq %rbx,%rax
movq %rax,-288(%rbp)
movq -288(%rbp),%r10
movq %r10,-64(%rbp)
jmp .L_start_29
.L_end_29:
movq $0,%r10
movq %r10,-288(%rbp)
subq $16,%rsp
movq -288(%rbp),%r10
movq %r10,-296(%rbp)
movq $1,%r10
subq $16,%rsp
movq %r10,-312(%rbp)
movq -160(%rbp),%rax
movq -312(%rbp),%rbx
addq $16,%rsp
subq %rbx,%rax
movq %rax,-304(%rbp)
subq $16,%rsp
movq -304(%rbp),%r10
movq %r10,-312(%rbp)
.L_start_31:
movq -296(%rbp),%rax
movq -160(%rbp),%rbx
cmp %rbx,%rax
setl %al
movzbl %al,%eax
movq %rax,-320(%rbp)
movq -320(%rbp),%r10
test %r10,%r10
jz .L_end_31
.L_start_32:
subq $16,%rsp
movq $1,%r10
movq %r10,-336(%rbp)
movq -312(%rbp),%rax
movq -336(%rbp),%rbx
subq %rbx,%rax
movq %rax,-328(%rbp)
movq $0,%r10
movq %r10,-336(%rbp)
movq -328(%rbp),%rax
movq -336(%rbp),%rbx
addq $16,%rsp
cmp %rbx,%rax
setge %al
movzbl %al,%eax
movq %rax,-320(%rbp)
movq -320(%rbp),%r10
test %r10,%r10
jz .L_end_32
subq $16,%rsp
subq $16,%rsp
movq $1,%r10
subq $16,%rsp
movq %r10,-360(%rbp)
movq -312(%rbp),%rax
movq -360(%rbp),%rbx
addq $16,%rsp
subq %rbx,%rax
movq %rax,-352(%rbp)
movq $8,%r10
subq $16,%rsp
movq %r10,-360(%rbp)
movq -352(%rbp),%rax
movq -360(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-344(%rbp)
movq -144(%rbp),%rax
movq -344(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-336(%rbp)
movq -336(%rbp),%r10
movq (%r10),%r11
movq %r11,-336(%rbp)
subq $16,%rsp
movq $8,%r10
subq $16,%rsp
movq %r10,-360(%rbp)
movq -296(%rbp),%rax
movq -360(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-352(%rbp)
movq -144(%rbp),%rax
movq -352(%rbp),%rbx
addq %rbx,%rax
movq %rax,-344(%rbp)
movq -344(%rbp),%r10
addq $16,%rsp
subq $16,%rsp
movq (%r10),%r11
movq %r11,-344(%rbp)
movq -336(%rbp),%rax
movq -344(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-328(%rbp)
movq -328(%rbp),%rax
movq -248(%rbp),%rbx
addq $16,%rsp
cmp %rbx,%rax
setge %al
movzbl %al,%eax
movq %rax,-320(%rbp)
movq -320(%rbp),%r10
test %r10,%r10
jz .L_else_33
movq $1,%r10
subq $16,%rsp
movq %r10,-328(%rbp)
movq -312(%rbp),%rax
movq -328(%rbp),%rbx
addq $16,%rsp
subq %rbx,%rax
movq %rax,-320(%rbp)
movq -320(%rbp),%r10
movq %r10,-312(%rbp)
jmp .L_end_33
.L_else_33:
jmp .L_end_32
.L_end_33:
jmp .L_start_32
.L_end_32:
subq $16,%rsp
movq $8,%r10
subq $16,%rsp
movq %r10,-344(%rbp)
movq -312(%rbp),%rax
movq -344(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-336(%rbp)
movq -280(%rbp),%rax
movq -336(%rbp),%rbx
addq %rbx,%rax
movq %rax,-328(%rbp)
movq -328(%rbp),%r10
addq $16,%rsp
subq $16,%rsp
movq (%r10),%r11
movq %r11,-328(%rbp)
subq $16,%rsp
movq $8,%r10
movq %r10,-352(%rbp)
movq -296(%rbp),%rax
movq -352(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-344(%rbp)
movq -264(%rbp),%rax
movq -344(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-336(%rbp)
movq -336(%rbp),%r10
movq (%r10),%r11
movq %r11,-336(%rbp)
movq -328(%rbp),%rax
movq -336(%rbp),%rbx
addq $16,%rsp
subq %rbx,%rax
movq %rax,-320(%rbp)
subq $16,%rsp
movq -320(%rbp),%r10
movq %r10,-328(%rbp)
movq $0,%r10
subq $16,%rsp
movq %r10,-344(%rbp)
movq -328(%rbp),%rax
movq -344(%rbp),%rbx
addq $16,%rsp
cmp %rbx,%rax
setl %al
movzbl %al,%eax
movq %rax,-336(%rbp)
movq -336(%rbp),%r10
test %r10,%r10
jz .L_else_34
movq $0,%r10
subq $16,%rsp
movq %r10,-344(%rbp)
movq -344(%rbp),%rax
movq -328(%rbp),%rbx
addq $16,%rsp
subq %rbx,%rax
movq %rax,-336(%rbp)
movq -336(%rbp),%r10
movq %r10,-328(%rbp)
jmp .L_end_34
.L_else_34:
.L_end_34:
movq -328(%rbp),%rax
movq -232(%rbp),%rbx
cmp %rbx,%rax
setg %al
movzbl %al,%eax
movq %rax,-336(%rbp)
movq -336(%rbp),%r10
test %r10,%r10
jz .L_else_35
movq -328(%rbp),%r10
movq %r10,-232(%rbp)
jmp .L_end_35
.L_else_35:
.L_end_35:
movq $1,%r10
subq $16,%rsp
movq %r10,-344(%rbp)
movq -296(%rbp),%rax
movq -344(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-336(%rbp)
movq -336(%rbp),%r10
movq %r10,-296(%rbp)
addq $16,%rsp
jmp .L_start_31
.L_end_31:
movq -280(%rbp),%r10
movq %r10,-320(%rbp)
call free
movq -264(%rbp),%r10
movq %r10,-320(%rbp)
call free
addq $16,%rsp
addq $16,%rsp
addq $16,%rsp
addq $16,%rsp
addq $16,%rsp
jmp .L_end_27
.L_else_27:
.L_end_27:
movq -232(%rbp),%r10
movq %r10,-240(%rbp)
call print_int
movq $10,%r10
movq %r10,-240(%rbp)
subq $16,%rsp
movq -240(%rbp),%r10
movq %r10,-256(%rbp)
call print_char
addq $16,%rsp
movq $1,%r10
subq $16,%rsp
movq %r10,-248(%rbp)
movq -168(%rbp),%rax
movq -248(%rbp),%rbx
addq $16,%rsp
subq %rbx,%rax
movq %rax,-240(%rbp)
movq -240(%rbp),%r10
movq %r10,-168(%rbp)
addq $16,%rsp
addq $16,%rsp
addq $16,%rsp
addq $16,%rsp
jmp .L_start_26
.L_end_26:
call flush_output
movq $0,%r10
movq %r10,-176(%rbp)
movq -176(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret


movq %rbp,%rsp
pop %rbp
ret

.section .data
.align 8

.section .bss
.align 8

.section .text
.global heap_cmp
heap_cmp:
push %rbp
movq %rsp,%rbp

subq $16,%rsp
movq 16(%rbp),%r11
addq $16,%r11
movq (%r11),%r10
movq %r10,-16(%rbp)
movq $1,%r10
subq $16,%rsp
movq %r10,-24(%rbp)
movq -16(%rbp),%rax
movq -24(%rbp),%rbx
addq $16,%rsp
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_36
subq $16,%rsp
movq 24(%rbp),%rax
movq 32(%rbp),%rbx
cmp %rbx,%rax
setg %al
movzbl %al,%eax
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_37
movq $1,%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq -8(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

addq $16,%rsp
jmp .L_end_37
.L_else_37:
movq $0,%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq -8(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

addq $16,%rsp
.L_end_37:
jmp .L_end_36
.L_else_36:
subq $16,%rsp
movq 24(%rbp),%rax
movq 32(%rbp),%rbx
cmp %rbx,%rax
setl %al
movzbl %al,%eax
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_38
movq $1,%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq -8(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

addq $16,%rsp
jmp .L_end_38
.L_else_38:
movq $0,%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq -8(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

addq $16,%rsp
.L_end_38:
.L_end_36:

movq %rbp,%rsp
pop %rbp
ret

.global heap_new
heap_new:
push %rbp
movq %rsp,%rbp

subq $16,%rsp
movq $4,%r10
movq %r10,-16(%rbp)
movq $8,%r10
subq $16,%rsp
movq %r10,-24(%rbp)
movq -16(%rbp),%rax
movq -24(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
movq %r10,-16(%rbp)
call malloc
addq $16,%rsp
subq $16,%rsp
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
movq %r10,-16(%rbp)
subq $16,%rsp
movq $0,%r10
movq %r10,-32(%rbp)
movq -16(%rbp),%rax
movq -32(%rbp),%rbx
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-24(%rbp)
movq -24(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_39
movq $0,%r10
subq $16,%rsp
movq %r10,-24(%rbp)
movq -24(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

addq $16,%rsp
jmp .L_end_39
.L_else_39:
.L_end_39:
movq $8,%r10
subq $16,%rsp
movq %r10,-24(%rbp)
movq -16(%rbp),%r11
movq -24(%rbp),%r10
movq %r10,(%r11)
addq $16,%rsp
movq $0,%r10
subq $16,%rsp
movq %r10,-24(%rbp)
movq -16(%rbp),%r11
addq $8,%r11
movq -24(%rbp),%r10
movq %r10,(%r11)
addq $16,%rsp
movq -16(%rbp),%r11
addq $16,%r11
movq 16(%rbp),%r10
movq %r10,(%r11)
subq $16,%rsp
movq $8,%r10
movq %r10,-32(%rbp)
movq $8,%r10
subq $16,%rsp
movq %r10,-40(%rbp)
movq -32(%rbp),%rax
movq -40(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-24(%rbp)
movq -24(%rbp),%r10
movq %r10,-32(%rbp)
call malloc
addq $16,%rsp
subq $16,%rsp
movq %rax,-24(%rbp)
movq -16(%rbp),%r11
addq $24,%r11
movq -24(%rbp),%r10
movq %r10,(%r11)
addq $16,%rsp
subq $16,%rsp
movq -16(%rbp),%r11
addq $24,%r11
movq (%r11),%r10
movq %r10,-32(%rbp)
movq $0,%r10
subq $16,%rsp
movq %r10,-40(%rbp)
movq -32(%rbp),%rax
movq -40(%rbp),%rbx
addq $16,%rsp
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-24(%rbp)
movq -24(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_40
subq $16,%rsp
movq -16(%rbp),%r10
movq %r10,-32(%rbp)
call free
addq $16,%rsp
movq $0,%r10
subq $16,%rsp
movq %r10,-24(%rbp)
movq -24(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

addq $16,%rsp
jmp .L_end_40
.L_else_40:
.L_end_40:
movq -16(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret


movq %rbp,%rsp
pop %rbp
ret

.global heap_free
heap_free:
push %rbp
movq %rsp,%rbp

subq $16,%rsp
movq $0,%r10
movq %r10,-16(%rbp)
movq 16(%rbp),%rax
movq -16(%rbp),%rbx
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_41
movq $0,%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq -8(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

addq $16,%rsp
jmp .L_end_41
.L_else_41:
.L_end_41:
subq $16,%rsp
movq 16(%rbp),%r11
addq $24,%r11
movq (%r11),%r10
movq %r10,-16(%rbp)
movq $0,%r10
subq $16,%rsp
movq %r10,-24(%rbp)
movq -16(%rbp),%rax
movq -24(%rbp),%rbx
addq $16,%rsp
cmp %rbx,%rax
setne %al
movzbl %al,%eax
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_42
movq 16(%rbp),%r11
addq $24,%r11
movq (%r11),%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq -8(%rbp),%r10
movq %r10,-16(%rbp)
call free
addq $16,%rsp
jmp .L_end_42
.L_else_42:
.L_end_42:
subq $16,%rsp
movq 16(%rbp),%r10
movq %r10,-16(%rbp)
call free
addq $16,%rsp

movq %rbp,%rsp
pop %rbp
ret

.global heap_size
heap_size:
push %rbp
movq %rsp,%rbp

subq $16,%rsp
movq $0,%r10
movq %r10,-16(%rbp)
movq 16(%rbp),%rax
movq -16(%rbp),%rbx
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_43
movq $0,%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq -8(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

addq $16,%rsp
jmp .L_end_43
.L_else_43:
.L_end_43:
movq 16(%rbp),%r11
addq $8,%r11
movq (%r11),%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq -8(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret


movq %rbp,%rsp
pop %rbp
ret

.global heap_swap
heap_swap:
push %rbp
movq %rsp,%rbp

subq $16,%rsp
movq $8,%r10
subq $16,%rsp
movq %r10,-24(%rbp)
movq 24(%rbp),%rax
movq -24(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-16(%rbp)
movq 16(%rbp),%rax
movq -16(%rbp),%rbx
addq %rbx,%rax
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
addq $16,%rsp
subq $16,%rsp
movq (%r10),%r11
movq %r11,-8(%rbp)
movq -8(%rbp),%r10
movq %r10,-16(%rbp)
subq $16,%rsp
movq $8,%r10
subq $16,%rsp
movq %r10,-40(%rbp)
movq 32(%rbp),%rax
movq -40(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-32(%rbp)
movq 16(%rbp),%rax
movq -32(%rbp),%rbx
addq %rbx,%rax
movq %rax,-24(%rbp)
movq -24(%rbp),%r10
addq $16,%rsp
subq $16,%rsp
movq (%r10),%r11
movq %r11,-24(%rbp)
subq $16,%rsp
movq $8,%r10
movq %r10,-48(%rbp)
movq 24(%rbp),%rax
movq -48(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-40(%rbp)
movq 16(%rbp),%rax
movq -40(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-32(%rbp)
movq -32(%rbp),%r11
movq -24(%rbp),%r10
movq %r10,(%r11)
subq $16,%rsp
movq $8,%r10
movq %r10,-48(%rbp)
movq 32(%rbp),%rax
movq -48(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-40(%rbp)
movq 16(%rbp),%rax
movq -40(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-32(%rbp)
movq -32(%rbp),%r11
movq -16(%rbp),%r10
movq %r10,(%r11)

movq %rbp,%rsp
pop %rbp
ret

.global heap_sift_up
heap_sift_up:
push %rbp
movq %rsp,%rbp

movq 16(%rbp),%r11
addq $24,%r11
movq (%r11),%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq -8(%rbp),%r10
movq %r10,-16(%rbp)
.L_start_44:
subq $16,%rsp
movq $0,%r10
movq %r10,-32(%rbp)
movq 24(%rbp),%rax
movq -32(%rbp),%rbx
cmp %rbx,%rax
setg %al
movzbl %al,%eax
movq %rax,-24(%rbp)
movq -24(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_end_44
subq $16,%rsp
movq $1,%r10
subq $16,%rsp
movq %r10,-40(%rbp)
movq 24(%rbp),%rax
movq -40(%rbp),%rbx
addq $16,%rsp
subq %rbx,%rax
movq %rax,-32(%rbp)
movq $2,%r10
subq $16,%rsp
movq %r10,-40(%rbp)
movq -32(%rbp),%rax
movq -40(%rbp),%rbx
addq $16,%rsp
cqto
idivq %rbx
movq %rax,-24(%rbp)
movq -24(%rbp),%r10
movq %r10,-32(%rbp)
subq $16,%rsp
movq $8,%r10
subq $16,%rsp
movq %r10,-56(%rbp)
movq 24(%rbp),%rax
movq -56(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-48(%rbp)
movq -16(%rbp),%rax
movq -48(%rbp),%rbx
addq %rbx,%rax
movq %rax,-40(%rbp)
movq -40(%rbp),%r10
addq $16,%rsp
subq $16,%rsp
movq (%r10),%r11
movq %r11,-40(%rbp)
subq $16,%rsp
movq $8,%r10
movq %r10,-64(%rbp)
movq -32(%rbp),%rax
movq -64(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-56(%rbp)
movq -16(%rbp),%rax
movq -56(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-48(%rbp)
movq -48(%rbp),%r10
movq (%r10),%r11
movq %r11,-48(%rbp)
subq $16,%rsp
subq $16,%rsp
movq -48(%rbp),%r10
movq %r10,-64(%rbp)
movq -40(%rbp),%r10
movq %r10,-72(%rbp)
movq 16(%rbp),%r10
movq %r10,-80(%rbp)
call heap_cmp
addq $16,%rsp
addq $16,%rsp
addq $16,%rsp
subq $16,%rsp
movq %rax,-40(%rbp)
movq -40(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_45
subq $16,%rsp
subq $16,%rsp
movq -32(%rbp),%r10
movq %r10,-48(%rbp)
movq 24(%rbp),%r10
movq %r10,-56(%rbp)
movq -16(%rbp),%r10
movq %r10,-64(%rbp)
call heap_swap
addq $16,%rsp
addq $16,%rsp
movq -32(%rbp),%r10
movq %r10,24(%rbp)
jmp .L_end_45
.L_else_45:
addq $16,%rsp
jmp .L_end_44
.L_end_45:
addq $16,%rsp
jmp .L_start_44
.L_end_44:

movq %rbp,%rsp
pop %rbp
ret

.global heap_sift_down
heap_sift_down:
push %rbp
movq %rsp,%rbp

movq 16(%rbp),%r11
addq $8,%r11
movq (%r11),%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq -8(%rbp),%r10
movq %r10,-16(%rbp)
movq 16(%rbp),%r11
addq $24,%r11
movq (%r11),%r10
subq $16,%rsp
movq %r10,-24(%rbp)
movq -24(%rbp),%r10
movq %r10,-32(%rbp)
.L_start_46:
movq $1,%r10
subq $16,%rsp
movq %r10,-40(%rbp)
movq -40(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_end_46
subq $16,%rsp
movq $2,%r10
subq $16,%rsp
movq %r10,-56(%rbp)
movq -56(%rbp),%rax
movq 24(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-48(%rbp)
movq $1,%r10
subq $16,%rsp
movq %r10,-56(%rbp)
movq -48(%rbp),%rax
movq -56(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-40(%rbp)
movq -40(%rbp),%r10
movq %r10,-48(%rbp)
subq $16,%rsp
movq $2,%r10
subq $16,%rsp
movq %r10,-72(%rbp)
movq -72(%rbp),%rax
movq 24(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-64(%rbp)
movq $2,%r10
subq $16,%rsp
movq %r10,-72(%rbp)
movq -64(%rbp),%rax
movq -72(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-56(%rbp)
movq -56(%rbp),%r10
movq %r10,-64(%rbp)
subq $16,%rsp
movq 24(%rbp),%r10
movq %r10,-72(%rbp)
movq -48(%rbp),%rax
movq -16(%rbp),%rbx
cmp %rbx,%rax
setl %al
movzbl %al,%eax
movq %rax,-80(%rbp)
movq -80(%rbp),%r10
test %r10,%r10
jz .L_else_47
subq $16,%rsp
movq $8,%r10
movq %r10,-96(%rbp)
movq -48(%rbp),%rax
movq -96(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-88(%rbp)
movq -32(%rbp),%rax
movq -88(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-80(%rbp)
movq -80(%rbp),%r10
movq (%r10),%r11
movq %r11,-80(%rbp)
subq $16,%rsp
movq $8,%r10
subq $16,%rsp
movq %r10,-104(%rbp)
movq -72(%rbp),%rax
movq -104(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-96(%rbp)
movq -32(%rbp),%rax
movq -96(%rbp),%rbx
addq %rbx,%rax
movq %rax,-88(%rbp)
movq -88(%rbp),%r10
addq $16,%rsp
subq $16,%rsp
movq (%r10),%r11
movq %r11,-88(%rbp)
subq $16,%rsp
movq -88(%rbp),%r10
movq %r10,-96(%rbp)
movq -80(%rbp),%r10
movq %r10,-104(%rbp)
movq 16(%rbp),%r10
movq %r10,-112(%rbp)
call heap_cmp
addq $16,%rsp
addq $16,%rsp
movq %rax,-80(%rbp)
movq -80(%rbp),%r10
test %r10,%r10
jz .L_else_48
movq -48(%rbp),%r10
movq %r10,-72(%rbp)
jmp .L_end_48
.L_else_48:
.L_end_48:
jmp .L_end_47
.L_else_47:
.L_end_47:
movq -64(%rbp),%rax
movq -16(%rbp),%rbx
cmp %rbx,%rax
setl %al
movzbl %al,%eax
movq %rax,-80(%rbp)
movq -80(%rbp),%r10
test %r10,%r10
jz .L_else_49
subq $16,%rsp
movq $8,%r10
movq %r10,-96(%rbp)
movq -64(%rbp),%rax
movq -96(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-88(%rbp)
movq -32(%rbp),%rax
movq -88(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-80(%rbp)
movq -80(%rbp),%r10
movq (%r10),%r11
movq %r11,-80(%rbp)
subq $16,%rsp
movq $8,%r10
subq $16,%rsp
movq %r10,-104(%rbp)
movq -72(%rbp),%rax
movq -104(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-96(%rbp)
movq -32(%rbp),%rax
movq -96(%rbp),%rbx
addq %rbx,%rax
movq %rax,-88(%rbp)
movq -88(%rbp),%r10
addq $16,%rsp
subq $16,%rsp
movq (%r10),%r11
movq %r11,-88(%rbp)
subq $16,%rsp
movq -88(%rbp),%r10
movq %r10,-96(%rbp)
movq -80(%rbp),%r10
movq %r10,-104(%rbp)
movq 16(%rbp),%r10
movq %r10,-112(%rbp)
call heap_cmp
addq $16,%rsp
addq $16,%rsp
movq %rax,-80(%rbp)
movq -80(%rbp),%r10
test %r10,%r10
jz .L_else_50
movq -64(%rbp),%r10
movq %r10,-72(%rbp)
jmp .L_end_50
.L_else_50:
.L_end_50:
jmp .L_end_49
.L_else_49:
.L_end_49:
movq -72(%rbp),%rax
movq 24(%rbp),%rbx
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-80(%rbp)
movq -80(%rbp),%r10
test %r10,%r10
jz .L_else_51
addq $16,%rsp
addq $16,%rsp
addq $16,%rsp
jmp .L_end_46
jmp .L_end_51
.L_else_51:
.L_end_51:
subq $16,%rsp
movq -72(%rbp),%r10
movq %r10,-80(%rbp)
movq 24(%rbp),%r10
movq %r10,-88(%rbp)
movq -32(%rbp),%r10
movq %r10,-96(%rbp)
call heap_swap
addq $16,%rsp
movq -72(%rbp),%r10
movq %r10,24(%rbp)
addq $16,%rsp
addq $16,%rsp
addq $16,%rsp
jmp .L_start_46
.L_end_46:

movq %rbp,%rsp
pop %rbp
ret

.global heap_ensure_cap
heap_ensure_cap:
push %rbp
movq %rsp,%rbp

movq 16(%rbp),%r11
movq (%r11),%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq -8(%rbp),%r10
movq %r10,-16(%rbp)
subq $16,%rsp
movq 24(%rbp),%rax
movq -16(%rbp),%rbx
cmp %rbx,%rax
setle %al
movzbl %al,%eax
movq %rax,-24(%rbp)
movq -24(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_52
movq $0,%r10
subq $16,%rsp
movq %r10,-24(%rbp)
movq -24(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

addq $16,%rsp
jmp .L_end_52
.L_else_52:
.L_end_52:
subq $16,%rsp
movq $2,%r10
movq %r10,-32(%rbp)
movq -16(%rbp),%rax
movq -32(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-24(%rbp)
movq -24(%rbp),%r10
movq %r10,-32(%rbp)
.L_start_53:
subq $16,%rsp
movq -32(%rbp),%rax
movq 24(%rbp),%rbx
cmp %rbx,%rax
setl %al
movzbl %al,%eax
movq %rax,-40(%rbp)
movq -40(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_end_53
subq $16,%rsp
movq $2,%r10
movq %r10,-48(%rbp)
movq -32(%rbp),%rax
movq -48(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-40(%rbp)
movq -40(%rbp),%r10
movq %r10,-32(%rbp)
addq $16,%rsp
jmp .L_start_53
.L_end_53:
subq $16,%rsp
movq $8,%r10
movq %r10,-48(%rbp)
movq -32(%rbp),%rax
movq -48(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-40(%rbp)
movq -40(%rbp),%r10
movq %r10,-48(%rbp)
call malloc
addq $16,%rsp
subq $16,%rsp
movq %rax,-40(%rbp)
movq -40(%rbp),%r10
movq %r10,-48(%rbp)
subq $16,%rsp
movq $0,%r10
movq %r10,-64(%rbp)
movq -48(%rbp),%rax
movq -64(%rbp),%rbx
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-56(%rbp)
movq -56(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_54
movq $0,%r10
subq $16,%rsp
movq %r10,-56(%rbp)
movq -56(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

addq $16,%rsp
jmp .L_end_54
.L_else_54:
.L_end_54:
movq 16(%rbp),%r11
addq $8,%r11
movq (%r11),%r10
subq $16,%rsp
movq %r10,-56(%rbp)
movq -56(%rbp),%r10
movq %r10,-64(%rbp)
subq $16,%rsp
movq $0,%r10
movq %r10,-80(%rbp)
movq -64(%rbp),%rax
movq -80(%rbp),%rbx
cmp %rbx,%rax
setg %al
movzbl %al,%eax
movq %rax,-72(%rbp)
movq -72(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_55
subq $16,%rsp
movq -48(%rbp),%r10
movq %r10,-72(%rbp)
movq 16(%rbp),%r11
addq $24,%r11
movq (%r11),%r10
movq %r10,-80(%rbp)
subq $16,%rsp
movq -80(%rbp),%r10
movq %r10,-88(%rbp)
movq $8,%r10
subq $16,%rsp
movq %r10,-104(%rbp)
movq -64(%rbp),%rax
movq -104(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-96(%rbp)
subq $16,%rsp
subq $16,%rsp
movq -96(%rbp),%r10
movq %r10,-112(%rbp)
movq -88(%rbp),%r10
movq %r10,-120(%rbp)
movq -72(%rbp),%r10
movq %r10,-128(%rbp)
call memcpy
addq $16,%rsp
addq $16,%rsp
addq $16,%rsp
addq $16,%rsp
jmp .L_end_55
.L_else_55:
.L_end_55:
movq 16(%rbp),%r11
addq $24,%r11
movq (%r11),%r10
subq $16,%rsp
movq %r10,-72(%rbp)
movq -72(%rbp),%r10
movq %r10,-80(%rbp)
call free
addq $16,%rsp
movq 16(%rbp),%r11
addq $24,%r11
movq -48(%rbp),%r10
movq %r10,(%r11)
movq 16(%rbp),%r11
movq -32(%rbp),%r10
movq %r10,(%r11)

movq %rbp,%rsp
pop %rbp
ret

.global heap_peek
heap_peek:
push %rbp
movq %rsp,%rbp

subq $16,%rsp
movq 16(%rbp),%r11
addq $24,%r11
movq (%r11),%r10
movq %r10,-16(%rbp)
subq $16,%rsp
movq $0,%r10
movq %r10,-32(%rbp)
movq $8,%r10
subq $16,%rsp
movq %r10,-40(%rbp)
movq -32(%rbp),%rax
movq -40(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-24(%rbp)
movq -16(%rbp),%rax
movq -24(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
addq $16,%rsp
subq $16,%rsp
movq (%r10),%r11
movq %r11,-8(%rbp)
movq -8(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret


movq %rbp,%rsp
pop %rbp
ret

.global heap_push
heap_push:
push %rbp
movq %rsp,%rbp

movq 16(%rbp),%r11
addq $8,%r11
movq (%r11),%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq -8(%rbp),%r10
movq %r10,-16(%rbp)
subq $16,%rsp
movq $1,%r10
movq %r10,-32(%rbp)
movq -16(%rbp),%rax
movq -32(%rbp),%rbx
addq %rbx,%rax
movq %rax,-24(%rbp)
subq $16,%rsp
movq -24(%rbp),%r10
movq %r10,-40(%rbp)
movq 16(%rbp),%r10
movq %r10,-48(%rbp)
call heap_ensure_cap
addq $16,%rsp
addq $16,%rsp
movq 16(%rbp),%r11
addq $24,%r11
movq (%r11),%r10
subq $16,%rsp
movq %r10,-24(%rbp)
movq -24(%rbp),%r10
movq %r10,-32(%rbp)
subq $16,%rsp
movq $8,%r10
subq $16,%rsp
movq %r10,-56(%rbp)
movq -16(%rbp),%rax
movq -56(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-48(%rbp)
movq -32(%rbp),%rax
movq -48(%rbp),%rbx
addq %rbx,%rax
movq %rax,-40(%rbp)
movq -40(%rbp),%r11
movq 24(%rbp),%r10
movq %r10,(%r11)
addq $16,%rsp
subq $16,%rsp
movq $1,%r10
movq %r10,-48(%rbp)
movq -16(%rbp),%rax
movq -48(%rbp),%rbx
addq %rbx,%rax
movq %rax,-40(%rbp)
movq 16(%rbp),%r11
addq $8,%r11
movq -40(%rbp),%r10
movq %r10,(%r11)
addq $16,%rsp
subq $16,%rsp
movq -16(%rbp),%r10
movq %r10,-40(%rbp)
movq 16(%rbp),%r10
movq %r10,-48(%rbp)
call heap_sift_up
addq $16,%rsp

movq %rbp,%rsp
pop %rbp
ret

.global heap_pop
heap_pop:
push %rbp
movq %rsp,%rbp

subq $16,%rsp
movq 16(%rbp),%r11
addq $8,%r11
movq (%r11),%r10
movq %r10,-16(%rbp)
movq $0,%r10
subq $16,%rsp
movq %r10,-24(%rbp)
movq -16(%rbp),%rax
movq -24(%rbp),%rbx
addq $16,%rsp
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_56
movq $0,%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq -8(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

addq $16,%rsp
jmp .L_end_56
.L_else_56:
.L_end_56:
movq 16(%rbp),%r11
addq $24,%r11
movq (%r11),%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq -8(%rbp),%r10
movq %r10,-16(%rbp)
subq $16,%rsp
movq $0,%r10
subq $16,%rsp
movq %r10,-40(%rbp)
movq $8,%r10
movq %r10,-48(%rbp)
movq -40(%rbp),%rax
movq -48(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-32(%rbp)
movq -16(%rbp),%rax
movq -32(%rbp),%rbx
addq %rbx,%rax
movq %rax,-24(%rbp)
movq -24(%rbp),%r10
addq $16,%rsp
subq $16,%rsp
movq (%r10),%r11
movq %r11,-24(%rbp)
movq -24(%rbp),%r10
movq %r10,-32(%rbp)
subq $16,%rsp
movq 16(%rbp),%r11
addq $8,%r11
movq (%r11),%r10
movq %r10,-48(%rbp)
movq $1,%r10
subq $16,%rsp
movq %r10,-56(%rbp)
movq -48(%rbp),%rax
movq -56(%rbp),%rbx
addq $16,%rsp
subq %rbx,%rax
movq %rax,-40(%rbp)
movq -40(%rbp),%r10
movq %r10,-48(%rbp)
subq $16,%rsp
movq $8,%r10
subq $16,%rsp
movq %r10,-72(%rbp)
movq -48(%rbp),%rax
movq -72(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-64(%rbp)
movq -16(%rbp),%rax
movq -64(%rbp),%rbx
addq %rbx,%rax
movq %rax,-56(%rbp)
movq -56(%rbp),%r10
addq $16,%rsp
subq $16,%rsp
movq (%r10),%r11
movq %r11,-56(%rbp)
subq $16,%rsp
movq $0,%r10
movq %r10,-80(%rbp)
movq $8,%r10
subq $16,%rsp
movq %r10,-88(%rbp)
movq -80(%rbp),%rax
movq -88(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-72(%rbp)
movq -16(%rbp),%rax
movq -72(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-64(%rbp)
movq -64(%rbp),%r11
movq -56(%rbp),%r10
movq %r10,(%r11)
movq 16(%rbp),%r11
addq $8,%r11
movq -48(%rbp),%r10
movq %r10,(%r11)
movq $0,%r10
subq $16,%rsp
movq %r10,-72(%rbp)
movq -48(%rbp),%rax
movq -72(%rbp),%rbx
addq $16,%rsp
cmp %rbx,%rax
setg %al
movzbl %al,%eax
movq %rax,-64(%rbp)
movq -64(%rbp),%r10
test %r10,%r10
jz .L_else_57
movq $0,%r10
movq %r10,-64(%rbp)
subq $16,%rsp
movq -64(%rbp),%r10
movq %r10,-72(%rbp)
movq 16(%rbp),%r10
movq %r10,-80(%rbp)
call heap_sift_down
addq $16,%rsp
jmp .L_end_57
.L_else_57:
.L_end_57:
movq -32(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret


movq %rbp,%rsp
pop %rbp
ret

.section .data
.align 8

.section .bss
.align 8

.section .text
.global lower_bound
lower_bound:
push %rbp
movq %rsp,%rbp

movq $0,%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq -8(%rbp),%r10
movq %r10,-16(%rbp)
subq $16,%rsp
movq 24(%rbp),%r10
movq %r10,-24(%rbp)
.L_start_58:
movq -16(%rbp),%rax
movq -24(%rbp),%rbx
cmp %rbx,%rax
setl %al
movzbl %al,%eax
movq %rax,-32(%rbp)
movq -32(%rbp),%r10
test %r10,%r10
jz .L_end_58
subq $16,%rsp
movq -24(%rbp),%rax
movq -16(%rbp),%rbx
subq %rbx,%rax
movq %rax,-48(%rbp)
movq $2,%r10
subq $16,%rsp
movq %r10,-56(%rbp)
movq -48(%rbp),%rax
movq -56(%rbp),%rbx
addq $16,%rsp
cqto
idivq %rbx
movq %rax,-40(%rbp)
movq -16(%rbp),%rax
movq -40(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-32(%rbp)
subq $16,%rsp
movq -32(%rbp),%r10
movq %r10,-40(%rbp)
subq $16,%rsp
movq $8,%r10
subq $16,%rsp
movq %r10,-72(%rbp)
movq -40(%rbp),%rax
movq -72(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-64(%rbp)
movq 16(%rbp),%rax
movq -64(%rbp),%rbx
addq %rbx,%rax
movq %rax,-56(%rbp)
movq -56(%rbp),%r10
addq $16,%rsp
subq $16,%rsp
movq (%r10),%r11
movq %r11,-56(%rbp)
movq -56(%rbp),%rax
movq 32(%rbp),%rbx
addq $16,%rsp
cmp %rbx,%rax
setl %al
movzbl %al,%eax
movq %rax,-48(%rbp)
movq -48(%rbp),%r10
test %r10,%r10
jz .L_else_59
movq $1,%r10
subq $16,%rsp
movq %r10,-56(%rbp)
movq -40(%rbp),%rax
movq -56(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-48(%rbp)
movq -48(%rbp),%r10
movq %r10,-16(%rbp)
jmp .L_end_59
.L_else_59:
movq -40(%rbp),%r10
movq %r10,-24(%rbp)
.L_end_59:
addq $16,%rsp
jmp .L_start_58
.L_end_58:
movq -16(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret


movq %rbp,%rsp
pop %rbp
ret

.global set_new
set_new:
push %rbp
movq %rsp,%rbp

subq $16,%rsp
movq $3,%r10
movq %r10,-16(%rbp)
movq $8,%r10
subq $16,%rsp
movq %r10,-24(%rbp)
movq -16(%rbp),%rax
movq -24(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
movq %r10,-16(%rbp)
call malloc
addq $16,%rsp
subq $16,%rsp
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
movq %r10,-16(%rbp)
subq $16,%rsp
movq $0,%r10
movq %r10,-32(%rbp)
movq -16(%rbp),%rax
movq -32(%rbp),%rbx
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-24(%rbp)
movq -24(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_60
movq $0,%r10
subq $16,%rsp
movq %r10,-24(%rbp)
movq -24(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

addq $16,%rsp
jmp .L_end_60
.L_else_60:
.L_end_60:
movq $8,%r10
subq $16,%rsp
movq %r10,-24(%rbp)
movq -16(%rbp),%r11
movq -24(%rbp),%r10
movq %r10,(%r11)
addq $16,%rsp
movq $0,%r10
subq $16,%rsp
movq %r10,-24(%rbp)
movq -16(%rbp),%r11
addq $8,%r11
movq -24(%rbp),%r10
movq %r10,(%r11)
addq $16,%rsp
subq $16,%rsp
movq $8,%r10
movq %r10,-32(%rbp)
movq $8,%r10
subq $16,%rsp
movq %r10,-40(%rbp)
movq -32(%rbp),%rax
movq -40(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-24(%rbp)
movq -24(%rbp),%r10
movq %r10,-32(%rbp)
call malloc
addq $16,%rsp
subq $16,%rsp
movq %rax,-24(%rbp)
movq -16(%rbp),%r11
addq $16,%r11
movq -24(%rbp),%r10
movq %r10,(%r11)
addq $16,%rsp
subq $16,%rsp
movq -16(%rbp),%r11
addq $16,%r11
movq (%r11),%r10
movq %r10,-32(%rbp)
movq $0,%r10
subq $16,%rsp
movq %r10,-40(%rbp)
movq -32(%rbp),%rax
movq -40(%rbp),%rbx
addq $16,%rsp
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-24(%rbp)
movq -24(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_61
subq $16,%rsp
movq -16(%rbp),%r10
movq %r10,-32(%rbp)
call free
addq $16,%rsp
movq $0,%r10
subq $16,%rsp
movq %r10,-24(%rbp)
movq -24(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

addq $16,%rsp
jmp .L_end_61
.L_else_61:
.L_end_61:
movq -16(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret


movq %rbp,%rsp
pop %rbp
ret

.global set_free
set_free:
push %rbp
movq %rsp,%rbp

subq $16,%rsp
movq $0,%r10
movq %r10,-16(%rbp)
movq 16(%rbp),%rax
movq -16(%rbp),%rbx
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_62
movq $0,%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq -8(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

addq $16,%rsp
jmp .L_end_62
.L_else_62:
.L_end_62:
subq $16,%rsp
movq 16(%rbp),%r11
addq $16,%r11
movq (%r11),%r10
movq %r10,-16(%rbp)
movq $0,%r10
subq $16,%rsp
movq %r10,-24(%rbp)
movq -16(%rbp),%rax
movq -24(%rbp),%rbx
addq $16,%rsp
cmp %rbx,%rax
setne %al
movzbl %al,%eax
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_63
movq 16(%rbp),%r11
addq $16,%r11
movq (%r11),%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq -8(%rbp),%r10
movq %r10,-16(%rbp)
call free
addq $16,%rsp
jmp .L_end_63
.L_else_63:
.L_end_63:
subq $16,%rsp
movq 16(%rbp),%r10
movq %r10,-16(%rbp)
call free
addq $16,%rsp

movq %rbp,%rsp
pop %rbp
ret

.global set_size
set_size:
push %rbp
movq %rsp,%rbp

subq $16,%rsp
movq $0,%r10
movq %r10,-16(%rbp)
movq 16(%rbp),%rax
movq -16(%rbp),%rbx
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_64
movq $0,%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq -8(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

addq $16,%rsp
jmp .L_end_64
.L_else_64:
.L_end_64:
movq 16(%rbp),%r11
addq $8,%r11
movq (%r11),%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq -8(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret


movq %rbp,%rsp
pop %rbp
ret

.global set_contains
set_contains:
push %rbp
movq %rsp,%rbp

subq $16,%rsp
movq $0,%r10
movq %r10,-16(%rbp)
movq 16(%rbp),%rax
movq -16(%rbp),%rbx
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_65
movq $0,%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq -8(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

addq $16,%rsp
jmp .L_end_65
.L_else_65:
.L_end_65:
movq 16(%rbp),%r11
addq $8,%r11
movq (%r11),%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq -8(%rbp),%r10
movq %r10,-16(%rbp)
movq 16(%rbp),%r11
addq $16,%r11
movq (%r11),%r10
subq $16,%rsp
movq %r10,-24(%rbp)
movq -24(%rbp),%r10
movq %r10,-32(%rbp)
subq $16,%rsp
subq $16,%rsp
movq 24(%rbp),%r10
movq %r10,-48(%rbp)
movq -16(%rbp),%r10
movq %r10,-56(%rbp)
movq -32(%rbp),%r10
movq %r10,-64(%rbp)
call lower_bound
addq $16,%rsp
addq $16,%rsp
subq $16,%rsp
movq %rax,-40(%rbp)
movq -40(%rbp),%r10
movq %r10,-48(%rbp)
subq $16,%rsp
movq -48(%rbp),%rax
movq -16(%rbp),%rbx
cmp %rbx,%rax
setl %al
movzbl %al,%eax
movq %rax,-56(%rbp)
movq -56(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_66
subq $16,%rsp
subq $16,%rsp
movq $8,%r10
movq %r10,-80(%rbp)
movq -48(%rbp),%rax
movq -80(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-72(%rbp)
movq -32(%rbp),%rax
movq -72(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-64(%rbp)
movq -64(%rbp),%r10
movq (%r10),%r11
movq %r11,-64(%rbp)
movq -64(%rbp),%rax
movq 24(%rbp),%rbx
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-56(%rbp)
movq -56(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_67
movq $1,%r10
subq $16,%rsp
movq %r10,-56(%rbp)
movq -56(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

addq $16,%rsp
jmp .L_end_67
.L_else_67:
.L_end_67:
jmp .L_end_66
.L_else_66:
.L_end_66:
movq $0,%r10
subq $16,%rsp
movq %r10,-56(%rbp)
movq -56(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret


movq %rbp,%rsp
pop %rbp
ret

.global set_insert
set_insert:
push %rbp
movq %rsp,%rbp

subq $16,%rsp
movq $0,%r10
movq %r10,-16(%rbp)
movq 16(%rbp),%rax
movq -16(%rbp),%rbx
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_68
movq $0,%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq -8(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

addq $16,%rsp
jmp .L_end_68
.L_else_68:
.L_end_68:
movq 16(%rbp),%r11
addq $8,%r11
movq (%r11),%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq -8(%rbp),%r10
movq %r10,-16(%rbp)
movq 16(%rbp),%r11
movq (%r11),%r10
subq $16,%rsp
movq %r10,-24(%rbp)
movq -24(%rbp),%r10
movq %r10,-32(%rbp)
movq 16(%rbp),%r11
addq $16,%r11
movq (%r11),%r10
subq $16,%rsp
movq %r10,-40(%rbp)
movq -40(%rbp),%r10
movq %r10,-48(%rbp)
subq $16,%rsp
subq $16,%rsp
movq 24(%rbp),%r10
movq %r10,-64(%rbp)
movq -16(%rbp),%r10
movq %r10,-72(%rbp)
movq -48(%rbp),%r10
movq %r10,-80(%rbp)
call lower_bound
addq $16,%rsp
addq $16,%rsp
subq $16,%rsp
movq %rax,-56(%rbp)
movq -56(%rbp),%r10
movq %r10,-64(%rbp)
subq $16,%rsp
movq -64(%rbp),%rax
movq -16(%rbp),%rbx
cmp %rbx,%rax
setl %al
movzbl %al,%eax
movq %rax,-72(%rbp)
movq -72(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_69
subq $16,%rsp
subq $16,%rsp
movq $8,%r10
movq %r10,-96(%rbp)
movq -64(%rbp),%rax
movq -96(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-88(%rbp)
movq -48(%rbp),%rax
movq -88(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-80(%rbp)
movq -80(%rbp),%r10
movq (%r10),%r11
movq %r11,-80(%rbp)
movq -80(%rbp),%rax
movq 24(%rbp),%rbx
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-72(%rbp)
movq -72(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_70
movq $0,%r10
subq $16,%rsp
movq %r10,-72(%rbp)
movq -72(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

addq $16,%rsp
jmp .L_end_70
.L_else_70:
.L_end_70:
jmp .L_end_69
.L_else_69:
.L_end_69:
subq $16,%rsp
movq -16(%rbp),%rax
movq -32(%rbp),%rbx
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-72(%rbp)
movq -72(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_71
subq $16,%rsp
movq $2,%r10
movq %r10,-80(%rbp)
movq -32(%rbp),%rax
movq -80(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-72(%rbp)
movq -72(%rbp),%r10
movq %r10,-80(%rbp)
subq $16,%rsp
movq $8,%r10
movq %r10,-96(%rbp)
movq -80(%rbp),%rax
movq -96(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-88(%rbp)
movq -88(%rbp),%r10
movq %r10,-96(%rbp)
call malloc
addq $16,%rsp
subq $16,%rsp
movq %rax,-88(%rbp)
movq -88(%rbp),%r10
movq %r10,-96(%rbp)
subq $16,%rsp
movq $0,%r10
movq %r10,-112(%rbp)
movq -96(%rbp),%rax
movq -112(%rbp),%rbx
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-104(%rbp)
movq -104(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_72
movq $0,%r10
subq $16,%rsp
movq %r10,-104(%rbp)
movq -104(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

addq $16,%rsp
jmp .L_end_72
.L_else_72:
.L_end_72:
subq $16,%rsp
movq $0,%r10
movq %r10,-112(%rbp)
movq -16(%rbp),%rax
movq -112(%rbp),%rbx
cmp %rbx,%rax
setg %al
movzbl %al,%eax
movq %rax,-104(%rbp)
movq -104(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_73
subq $16,%rsp
movq -96(%rbp),%r10
movq %r10,-104(%rbp)
movq -48(%rbp),%r10
movq %r10,-112(%rbp)
subq $16,%rsp
movq $8,%r10
movq %r10,-128(%rbp)
movq -16(%rbp),%rax
movq -128(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-120(%rbp)
subq $16,%rsp
movq -120(%rbp),%r10
movq %r10,-128(%rbp)
movq -112(%rbp),%r10
movq %r10,-136(%rbp)
movq -104(%rbp),%r10
movq %r10,-144(%rbp)
call memcpy
addq $16,%rsp
addq $16,%rsp
addq $16,%rsp
jmp .L_end_73
.L_else_73:
.L_end_73:
subq $16,%rsp
movq -48(%rbp),%r10
movq %r10,-112(%rbp)
call free
addq $16,%rsp
movq 16(%rbp),%r11
addq $16,%r11
movq -96(%rbp),%r10
movq %r10,(%r11)
movq 16(%rbp),%r11
movq -80(%rbp),%r10
movq %r10,(%r11)
movq -96(%rbp),%r10
movq %r10,-48(%rbp)
movq -80(%rbp),%r10
movq %r10,-32(%rbp)
addq $16,%rsp
addq $16,%rsp
jmp .L_end_71
.L_else_71:
.L_end_71:
subq $16,%rsp
movq -16(%rbp),%r10
movq %r10,-72(%rbp)
.L_start_74:
movq -72(%rbp),%rax
movq -64(%rbp),%rbx
cmp %rbx,%rax
setg %al
movzbl %al,%eax
movq %rax,-80(%rbp)
movq -80(%rbp),%r10
test %r10,%r10
jz .L_end_74
subq $16,%rsp
movq $1,%r10
subq $16,%rsp
movq %r10,-104(%rbp)
movq -72(%rbp),%rax
movq -104(%rbp),%rbx
addq $16,%rsp
subq %rbx,%rax
movq %rax,-96(%rbp)
movq $8,%r10
subq $16,%rsp
movq %r10,-104(%rbp)
movq -96(%rbp),%rax
movq -104(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-88(%rbp)
movq -48(%rbp),%rax
movq -88(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-80(%rbp)
movq -80(%rbp),%r10
movq (%r10),%r11
movq %r11,-80(%rbp)
subq $16,%rsp
movq $8,%r10
subq $16,%rsp
movq %r10,-104(%rbp)
movq -72(%rbp),%rax
movq -104(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-96(%rbp)
movq -48(%rbp),%rax
movq -96(%rbp),%rbx
addq %rbx,%rax
movq %rax,-88(%rbp)
movq -88(%rbp),%r11
movq -80(%rbp),%r10
movq %r10,(%r11)
addq $16,%rsp
subq $16,%rsp
movq $1,%r10
movq %r10,-96(%rbp)
movq -72(%rbp),%rax
movq -96(%rbp),%rbx
subq %rbx,%rax
movq %rax,-88(%rbp)
movq -88(%rbp),%r10
movq %r10,-72(%rbp)
addq $16,%rsp
jmp .L_start_74
.L_end_74:
subq $16,%rsp
movq $8,%r10
movq %r10,-96(%rbp)
movq -64(%rbp),%rax
movq -96(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-88(%rbp)
movq -48(%rbp),%rax
movq -88(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-80(%rbp)
movq -80(%rbp),%r11
movq 24(%rbp),%r10
movq %r10,(%r11)
movq $1,%r10
subq $16,%rsp
movq %r10,-88(%rbp)
movq -16(%rbp),%rax
movq -88(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-80(%rbp)
movq 16(%rbp),%r11
addq $8,%r11
movq -80(%rbp),%r10
movq %r10,(%r11)
movq $1,%r10
movq %r10,-80(%rbp)
movq -80(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret


movq %rbp,%rsp
pop %rbp
ret

.global set_erase
set_erase:
push %rbp
movq %rsp,%rbp

subq $16,%rsp
movq $0,%r10
movq %r10,-16(%rbp)
movq 16(%rbp),%rax
movq -16(%rbp),%rbx
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_75
movq $0,%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq -8(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

addq $16,%rsp
jmp .L_end_75
.L_else_75:
.L_end_75:
movq 16(%rbp),%r11
addq $8,%r11
movq (%r11),%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq -8(%rbp),%r10
movq %r10,-16(%rbp)
movq 16(%rbp),%r11
addq $16,%r11
movq (%r11),%r10
subq $16,%rsp
movq %r10,-24(%rbp)
movq -24(%rbp),%r10
movq %r10,-32(%rbp)
subq $16,%rsp
subq $16,%rsp
movq 24(%rbp),%r10
movq %r10,-48(%rbp)
movq -16(%rbp),%r10
movq %r10,-56(%rbp)
movq -32(%rbp),%r10
movq %r10,-64(%rbp)
call lower_bound
addq $16,%rsp
addq $16,%rsp
subq $16,%rsp
movq %rax,-40(%rbp)
movq -40(%rbp),%r10
movq %r10,-48(%rbp)
subq $16,%rsp
movq -48(%rbp),%rax
movq -16(%rbp),%rbx
cmp %rbx,%rax
setge %al
movzbl %al,%eax
movq %rax,-56(%rbp)
movq -56(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_76
movq $0,%r10
subq $16,%rsp
movq %r10,-56(%rbp)
movq -56(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

addq $16,%rsp
jmp .L_end_76
.L_else_76:
.L_end_76:
subq $16,%rsp
subq $16,%rsp
movq $8,%r10
movq %r10,-80(%rbp)
movq -48(%rbp),%rax
movq -80(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-72(%rbp)
movq -32(%rbp),%rax
movq -72(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-64(%rbp)
movq -64(%rbp),%r10
movq (%r10),%r11
movq %r11,-64(%rbp)
movq -64(%rbp),%rax
movq 24(%rbp),%rbx
cmp %rbx,%rax
setne %al
movzbl %al,%eax
movq %rax,-56(%rbp)
movq -56(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_77
movq $0,%r10
subq $16,%rsp
movq %r10,-56(%rbp)
movq -56(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

addq $16,%rsp
jmp .L_end_77
.L_else_77:
.L_end_77:
subq $16,%rsp
movq -48(%rbp),%r10
movq %r10,-56(%rbp)
.L_start_78:
subq $16,%rsp
movq $1,%r10
movq %r10,-80(%rbp)
movq -56(%rbp),%rax
movq -80(%rbp),%rbx
addq %rbx,%rax
movq %rax,-72(%rbp)
movq -72(%rbp),%rax
movq -16(%rbp),%rbx
addq $16,%rsp
cmp %rbx,%rax
setl %al
movzbl %al,%eax
movq %rax,-64(%rbp)
movq -64(%rbp),%r10
test %r10,%r10
jz .L_end_78
subq $16,%rsp
movq $1,%r10
subq $16,%rsp
movq %r10,-88(%rbp)
movq -56(%rbp),%rax
movq -88(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-80(%rbp)
movq $8,%r10
subq $16,%rsp
movq %r10,-88(%rbp)
movq -80(%rbp),%rax
movq -88(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-72(%rbp)
movq -32(%rbp),%rax
movq -72(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-64(%rbp)
movq -64(%rbp),%r10
movq (%r10),%r11
movq %r11,-64(%rbp)
subq $16,%rsp
movq $8,%r10
subq $16,%rsp
movq %r10,-88(%rbp)
movq -56(%rbp),%rax
movq -88(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-80(%rbp)
movq -32(%rbp),%rax
movq -80(%rbp),%rbx
addq %rbx,%rax
movq %rax,-72(%rbp)
movq -72(%rbp),%r11
movq -64(%rbp),%r10
movq %r10,(%r11)
addq $16,%rsp
subq $16,%rsp
movq $1,%r10
movq %r10,-80(%rbp)
movq -56(%rbp),%rax
movq -80(%rbp),%rbx
addq %rbx,%rax
movq %rax,-72(%rbp)
movq -72(%rbp),%r10
movq %r10,-56(%rbp)
addq $16,%rsp
jmp .L_start_78
.L_end_78:
movq $1,%r10
subq $16,%rsp
movq %r10,-72(%rbp)
movq -16(%rbp),%rax
movq -72(%rbp),%rbx
addq $16,%rsp
subq %rbx,%rax
movq %rax,-64(%rbp)
movq 16(%rbp),%r11
addq $8,%r11
movq -64(%rbp),%r10
movq %r10,(%r11)
movq $1,%r10
movq %r10,-64(%rbp)
movq -64(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret


movq %rbp,%rsp
pop %rbp
ret

.global set_min
set_min:
push %rbp
movq %rsp,%rbp

subq $16,%rsp
movq $0,%r10
movq %r10,-16(%rbp)
movq 16(%rbp),%rax
movq -16(%rbp),%rbx
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_79
movq $0,%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq -8(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

addq $16,%rsp
jmp .L_end_79
.L_else_79:
.L_end_79:
subq $16,%rsp
movq 16(%rbp),%r11
addq $8,%r11
movq (%r11),%r10
movq %r10,-16(%rbp)
movq $0,%r10
subq $16,%rsp
movq %r10,-24(%rbp)
movq -16(%rbp),%rax
movq -24(%rbp),%rbx
addq $16,%rsp
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_80
movq $0,%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq -8(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

addq $16,%rsp
jmp .L_end_80
.L_else_80:
.L_end_80:
subq $16,%rsp
movq 16(%rbp),%r11
addq $16,%r11
movq (%r11),%r10
movq %r10,-16(%rbp)
subq $16,%rsp
movq $0,%r10
movq %r10,-32(%rbp)
movq $8,%r10
subq $16,%rsp
movq %r10,-40(%rbp)
movq -32(%rbp),%rax
movq -40(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-24(%rbp)
movq -16(%rbp),%rax
movq -24(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
addq $16,%rsp
subq $16,%rsp
movq (%r10),%r11
movq %r11,-8(%rbp)
movq -8(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret


movq %rbp,%rsp
pop %rbp
ret

.global set_max
set_max:
push %rbp
movq %rsp,%rbp

subq $16,%rsp
movq $0,%r10
movq %r10,-16(%rbp)
movq 16(%rbp),%rax
movq -16(%rbp),%rbx
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_81
movq $0,%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq -8(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

addq $16,%rsp
jmp .L_end_81
.L_else_81:
.L_end_81:
movq 16(%rbp),%r11
addq $8,%r11
movq (%r11),%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq -8(%rbp),%r10
movq %r10,-16(%rbp)
subq $16,%rsp
movq $0,%r10
movq %r10,-32(%rbp)
movq -16(%rbp),%rax
movq -32(%rbp),%rbx
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-24(%rbp)
movq -24(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_82
movq $0,%r10
subq $16,%rsp
movq %r10,-24(%rbp)
movq -24(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

addq $16,%rsp
jmp .L_end_82
.L_else_82:
.L_end_82:
subq $16,%rsp
movq 16(%rbp),%r11
addq $16,%r11
movq (%r11),%r10
movq %r10,-32(%rbp)
subq $16,%rsp
movq $1,%r10
subq $16,%rsp
movq %r10,-56(%rbp)
movq -16(%rbp),%rax
movq -56(%rbp),%rbx
addq $16,%rsp
subq %rbx,%rax
movq %rax,-48(%rbp)
movq $8,%r10
subq $16,%rsp
movq %r10,-56(%rbp)
movq -48(%rbp),%rax
movq -56(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-40(%rbp)
movq -32(%rbp),%rax
movq -40(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-24(%rbp)
movq -24(%rbp),%r10
addq $16,%rsp
subq $16,%rsp
movq (%r10),%r11
movq %r11,-24(%rbp)
movq -24(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret


movq %rbp,%rsp
pop %rbp
ret

.section .data
.align 8
READ_BUFFER_CAP: .quad 5242880
WRITE_BUFFER_CAP: .quad 32768
input_buffer: .quad _galloc_array_0
input_index: .quad 0
output_buffer: .quad _galloc_array_1
output_index: .quad 0

.section .bss
.align 8
_galloc_array_0: .zero 5242880
_galloc_array_1: .zero 32768

.section .text
.global init_input
init_input:
push %rbp
movq %rsp,%rbp

movq $0,%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq $0,%r10
movq %r10,-16(%rbp)
movq -8(%rbp),%rax
movq -16(%rbp),%rdi
movq input_buffer(%rip),%rsi
movq READ_BUFFER_CAP(%rip),%rdx
syscall
addq $16,%rsp

movq %rbp,%rsp
pop %rbp
ret

.global flush_output
flush_output:
push %rbp
movq %rsp,%rbp

subq $16,%rsp
movq $0,%r10
movq %r10,-16(%rbp)
movq output_index(%rip),%rax
movq -16(%rbp),%rbx
cmp %rbx,%rax
setg %al
movzbl %al,%eax
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_83
movq $1,%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq $1,%r10
movq %r10,-16(%rbp)
movq -8(%rbp),%rax
movq -16(%rbp),%rdi
movq output_buffer(%rip),%rsi
movq output_index(%rip),%rdx
syscall
addq $16,%rsp
movq $0,%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq -8(%rbp),%r10
movq %r10,output_index(%rip)
addq $16,%rsp
jmp .L_end_83
.L_else_83:
.L_end_83:

movq %rbp,%rsp
pop %rbp
ret

.global read_char
read_char:
push %rbp
movq %rsp,%rbp

subq $16,%rsp
movq input_index(%rip),%rax
movq READ_BUFFER_CAP(%rip),%rbx
cmp %rbx,%rax
setge %al
movzbl %al,%eax
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_84
movq $0,%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq -8(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

addq $16,%rsp
jmp .L_end_84
.L_else_84:
.L_end_84:
subq $16,%rsp
movq $1,%r10
subq $16,%rsp
movq %r10,-24(%rbp)
movq input_index(%rip),%rax
movq -24(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-16(%rbp)
movq input_buffer(%rip),%rax
movq -16(%rbp),%rbx
addq %rbx,%rax
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
addq $16,%rsp
subq $16,%rsp
movzbq (%r10),%r11
movb %r11b,-1(%rbp)
movzbq -1(%rbp),%r10
movq %r10,-9(%rbp)
subq $16,%rsp
movq $1,%r10
movq %r10,-25(%rbp)
movq input_index(%rip),%rax
movq -25(%rbp),%rbx
addq %rbx,%rax
movq %rax,-17(%rbp)
movq -17(%rbp),%r10
movq %r10,input_index(%rip)
addq $16,%rsp
movq -9(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret


movq %rbp,%rsp
pop %rbp
ret

.global print_char
print_char:
push %rbp
movq %rsp,%rbp

subq $16,%rsp
movq $1,%r10
subq $16,%rsp
movq %r10,-24(%rbp)
movq output_index(%rip),%rax
movq -24(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-16(%rbp)
movq output_buffer(%rip),%rax
movq -16(%rbp),%rbx
addq %rbx,%rax
movq %rax,-8(%rbp)
movq -8(%rbp),%r11
movq 16(%rbp),%r10
movb %r10b,(%r11)
addq $16,%rsp
subq $16,%rsp
movq $1,%r10
movq %r10,-16(%rbp)
movq output_index(%rip),%rax
movq -16(%rbp),%rbx
addq %rbx,%rax
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
movq %r10,output_index(%rip)
addq $16,%rsp
subq $16,%rsp
movq output_index(%rip),%rax
movq WRITE_BUFFER_CAP(%rip),%rbx
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_85
call flush_output
jmp .L_end_85
.L_else_85:
.L_end_85:

movq %rbp,%rsp
pop %rbp
ret

.global read_int
read_int:
push %rbp
movq %rsp,%rbp

call read_char
subq $16,%rsp
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
movq %r10,-16(%rbp)
movq $0,%r10
subq $16,%rsp
movq %r10,-24(%rbp)
movq -24(%rbp),%r10
movq %r10,-32(%rbp)
movq $0,%r10
subq $16,%rsp
movq %r10,-40(%rbp)
movq -40(%rbp),%r10
movq %r10,-48(%rbp)
.L_start_86:
subq $16,%rsp
subq $16,%rsp
movq $10,%r10
movq %r10,-80(%rbp)
movq -16(%rbp),%rax
movq -80(%rbp),%rbx
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-72(%rbp)
movq $32,%r10
subq $16,%rsp
movq %r10,-88(%rbp)
movq -16(%rbp),%rax
movq -88(%rbp),%rbx
addq $16,%rsp
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-80(%rbp)
movq -72(%rbp),%rax
movq -80(%rbp),%rbx
addq $16,%rsp
or %rbx,%rax
movq %rax,-64(%rbp)
subq $16,%rsp
movq $13,%r10
movq %r10,-80(%rbp)
movq -16(%rbp),%rax
movq -80(%rbp),%rbx
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-72(%rbp)
movq -64(%rbp),%rax
movq -72(%rbp),%rbx
addq $16,%rsp
or %rbx,%rax
movq %rax,-56(%rbp)
movq -56(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_end_86
call read_char
subq $16,%rsp
movq %rax,-56(%rbp)
movq -56(%rbp),%r10
movq %r10,-16(%rbp)
addq $16,%rsp
jmp .L_start_86
.L_end_86:
subq $16,%rsp
movq $45,%r10
movq %r10,-64(%rbp)
movq -16(%rbp),%rax
movq -64(%rbp),%rbx
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-56(%rbp)
movq -56(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_87
movq $1,%r10
subq $16,%rsp
movq %r10,-56(%rbp)
movq -56(%rbp),%r10
movq %r10,-48(%rbp)
addq $16,%rsp
call read_char
subq $16,%rsp
movq %rax,-56(%rbp)
movq -56(%rbp),%r10
movq %r10,-16(%rbp)
addq $16,%rsp
jmp .L_end_87
.L_else_87:
.L_end_87:
.L_start_88:
subq $16,%rsp
subq $16,%rsp
movq $10,%r10
subq $16,%rsp
movq %r10,-88(%rbp)
movq -16(%rbp),%rax
movq -88(%rbp),%rbx
addq $16,%rsp
cmp %rbx,%rax
setne %al
movzbl %al,%eax
movq %rax,-80(%rbp)
subq $16,%rsp
movq $32,%r10
movq %r10,-96(%rbp)
movq -16(%rbp),%rax
movq -96(%rbp),%rbx
cmp %rbx,%rax
setne %al
movzbl %al,%eax
movq %rax,-88(%rbp)
movq -80(%rbp),%rax
movq -88(%rbp),%rbx
addq $16,%rsp
and %rbx,%rax
movq %rax,-72(%rbp)
movq $13,%r10
subq $16,%rsp
movq %r10,-88(%rbp)
movq -16(%rbp),%rax
movq -88(%rbp),%rbx
addq $16,%rsp
cmp %rbx,%rax
setne %al
movzbl %al,%eax
movq %rax,-80(%rbp)
movq -72(%rbp),%rax
movq -80(%rbp),%rbx
addq $16,%rsp
and %rbx,%rax
movq %rax,-64(%rbp)
subq $16,%rsp
movq $0,%r10
movq %r10,-80(%rbp)
movq -16(%rbp),%rax
movq -80(%rbp),%rbx
cmp %rbx,%rax
setne %al
movzbl %al,%eax
movq %rax,-72(%rbp)
movq -64(%rbp),%rax
movq -72(%rbp),%rbx
addq $16,%rsp
and %rbx,%rax
movq %rax,-56(%rbp)
movq -56(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_end_88
subq $16,%rsp
subq $16,%rsp
movq $10,%r10
movq %r10,-80(%rbp)
movq -32(%rbp),%rax
movq -80(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-72(%rbp)
movq -72(%rbp),%rax
movq -16(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-64(%rbp)
movq $48,%r10
subq $16,%rsp
movq %r10,-72(%rbp)
movq -64(%rbp),%rax
movq -72(%rbp),%rbx
addq $16,%rsp
subq %rbx,%rax
movq %rax,-56(%rbp)
movq -56(%rbp),%r10
movq %r10,-32(%rbp)
addq $16,%rsp
call read_char
subq $16,%rsp
movq %rax,-56(%rbp)
movq -56(%rbp),%r10
movq %r10,-16(%rbp)
addq $16,%rsp
jmp .L_start_88
.L_end_88:
subq $16,%rsp
movq $1,%r10
movq %r10,-64(%rbp)
movq -48(%rbp),%rax
movq -64(%rbp),%rbx
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-56(%rbp)
movq -56(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_89
subq $16,%rsp
movq $0,%r10
movq %r10,-64(%rbp)
movq -64(%rbp),%rax
movq -32(%rbp),%rbx
subq %rbx,%rax
movq %rax,-56(%rbp)
movq -56(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

addq $16,%rsp
jmp .L_end_89
.L_else_89:
.L_end_89:
movq -32(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret


movq %rbp,%rsp
pop %rbp
ret

.global print_int
print_int:
push %rbp
movq %rsp,%rbp

subq $16,%rsp
movq $0,%r10
movq %r10,-16(%rbp)
movq 16(%rbp),%rax
movq -16(%rbp),%rbx
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_90
movq $48,%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq -8(%rbp),%r10
movq %r10,-16(%rbp)
call print_char
addq $16,%rsp
movq $0,%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq -8(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

addq $16,%rsp
jmp .L_end_90
.L_else_90:
.L_end_90:
movq $0,%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq -8(%rbp),%r10
movq %r10,-16(%rbp)
subq $16,%rsp
movq $0,%r10
movq %r10,-32(%rbp)
movq 16(%rbp),%rax
movq -32(%rbp),%rbx
cmp %rbx,%rax
setl %al
movzbl %al,%eax
movq %rax,-24(%rbp)
movq -24(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_91
movq $1,%r10
subq $16,%rsp
movq %r10,-24(%rbp)
movq -24(%rbp),%r10
movq %r10,-16(%rbp)
addq $16,%rsp
subq $16,%rsp
movq $0,%r10
movq %r10,-32(%rbp)
movq -32(%rbp),%rax
movq 16(%rbp),%rbx
subq %rbx,%rax
movq %rax,-24(%rbp)
movq -24(%rbp),%r10
movq %r10,16(%rbp)
addq $16,%rsp
jmp .L_end_91
.L_else_91:
.L_end_91:
subq $16,%rsp
subq $16,%rsp
subq $16,%rsp
subq $16,%rsp
subq $16,%rsp
subq $16,%rsp
subq $16,%rsp
subq $16,%rsp
subq $16,%rsp
subq $16,%rsp
leaq -176(%rbp),%r10
subq $16,%rsp
movq %r10,-184(%rbp)
movq -184(%rbp),%r10
movq %r10,-192(%rbp)
movq $0,%r10
subq $16,%rsp
movq %r10,-200(%rbp)
movq -200(%rbp),%r10
movq %r10,-208(%rbp)
.L_start_92:
subq $16,%rsp
movq $0,%r10
movq %r10,-224(%rbp)
movq 16(%rbp),%rax
movq -224(%rbp),%rbx
cmp %rbx,%rax
setg %al
movzbl %al,%eax
movq %rax,-216(%rbp)
movq -216(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_end_92
subq $16,%rsp
movq $10,%r10
movq %r10,-224(%rbp)
movq 16(%rbp),%rax
movq -224(%rbp),%rbx
cqto
idivq %rbx
movq %rdx,-216(%rbp)
movq -216(%rbp),%r10
movq %r10,-224(%rbp)
subq $16,%rsp
movq $10,%r10
movq %r10,-240(%rbp)
movq 16(%rbp),%rax
movq -240(%rbp),%rbx
cqto
idivq %rbx
movq %rax,-232(%rbp)
movq -232(%rbp),%r10
movq %r10,16(%rbp)
addq $16,%rsp
subq $16,%rsp
movq $48,%r10
movq %r10,-240(%rbp)
movq -224(%rbp),%rax
movq -240(%rbp),%rbx
addq %rbx,%rax
movq %rax,-232(%rbp)
subq $16,%rsp
movq $8,%r10
movq %r10,-256(%rbp)
movq -208(%rbp),%rax
movq -256(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-248(%rbp)
movq -192(%rbp),%rax
movq -248(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-240(%rbp)
movq -240(%rbp),%r11
movq -232(%rbp),%r10
movq %r10,(%r11)
movq $1,%r10
subq $16,%rsp
movq %r10,-248(%rbp)
movq -208(%rbp),%rax
movq -248(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-240(%rbp)
movq -240(%rbp),%r10
movq %r10,-208(%rbp)
addq $16,%rsp
addq $16,%rsp
jmp .L_start_92
.L_end_92:
subq $16,%rsp
movq $1,%r10
movq %r10,-224(%rbp)
movq -16(%rbp),%rax
movq -224(%rbp),%rbx
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-216(%rbp)
movq -216(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_93
movq $45,%r10
subq $16,%rsp
movq %r10,-216(%rbp)
movq -216(%rbp),%r10
movq %r10,-224(%rbp)
call print_char
addq $16,%rsp
jmp .L_end_93
.L_else_93:
.L_end_93:
.L_start_94:
subq $16,%rsp
movq $0,%r10
movq %r10,-224(%rbp)
movq -208(%rbp),%rax
movq -224(%rbp),%rbx
cmp %rbx,%rax
setg %al
movzbl %al,%eax
movq %rax,-216(%rbp)
movq -216(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_end_94
subq $16,%rsp
movq $1,%r10
movq %r10,-224(%rbp)
movq -208(%rbp),%rax
movq -224(%rbp),%rbx
subq %rbx,%rax
movq %rax,-216(%rbp)
movq -216(%rbp),%r10
movq %r10,-208(%rbp)
addq $16,%rsp
subq $16,%rsp
movq $8,%r10
subq $16,%rsp
movq %r10,-232(%rbp)
movq -208(%rbp),%rax
movq -232(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-224(%rbp)
movq -192(%rbp),%rax
movq -224(%rbp),%rbx
addq %rbx,%rax
movq %rax,-216(%rbp)
movq -216(%rbp),%r10
addq $16,%rsp
subq $16,%rsp
movq (%r10),%r11
movq %r11,-216(%rbp)
movq -216(%rbp),%r10
movq %r10,-224(%rbp)
call print_char
addq $16,%rsp
jmp .L_start_94
.L_end_94:

movq %rbp,%rsp
pop %rbp
ret

.global read_string
read_string:
push %rbp
movq %rsp,%rbp

movq $0,%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq -8(%rbp),%r10
movq %r10,-16(%rbp)
.L_start_95:
subq $16,%rsp
movq -16(%rbp),%rax
movq 24(%rbp),%rbx
cmp %rbx,%rax
setl %al
movzbl %al,%eax
movq %rax,-24(%rbp)
movq -24(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_end_95
call read_char
subq $16,%rsp
movq %rax,-24(%rbp)
movq -24(%rbp),%r10
movq %r10,-32(%rbp)
subq $16,%rsp
movq $0,%r10
movq %r10,-48(%rbp)
movq -32(%rbp),%rax
movq -48(%rbp),%rbx
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-40(%rbp)
movq -40(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_96
addq $16,%rsp
jmp .L_end_95
jmp .L_end_96
.L_else_96:
.L_end_96:
subq $16,%rsp
subq $16,%rsp
movq $10,%r10
movq %r10,-64(%rbp)
movq -32(%rbp),%rax
movq -64(%rbp),%rbx
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-56(%rbp)
movq $13,%r10
subq $16,%rsp
movq %r10,-72(%rbp)
movq -32(%rbp),%rax
movq -72(%rbp),%rbx
addq $16,%rsp
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-64(%rbp)
movq -56(%rbp),%rax
movq -64(%rbp),%rbx
addq $16,%rsp
or %rbx,%rax
movq %rax,-48(%rbp)
subq $16,%rsp
movq $32,%r10
movq %r10,-64(%rbp)
movq -32(%rbp),%rax
movq -64(%rbp),%rbx
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-56(%rbp)
movq -48(%rbp),%rax
movq -56(%rbp),%rbx
addq $16,%rsp
or %rbx,%rax
movq %rax,-40(%rbp)
movq -40(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_97
addq $16,%rsp
jmp .L_start_95
jmp .L_end_97
.L_else_97:
.L_end_97:
subq $16,%rsp
movq $1,%r10
subq $16,%rsp
movq %r10,-56(%rbp)
movq -16(%rbp),%rax
movq -56(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-48(%rbp)
movq 16(%rbp),%rax
movq -48(%rbp),%rbx
addq %rbx,%rax
movq %rax,-40(%rbp)
movq -40(%rbp),%r11
movq -32(%rbp),%r10
movb %r10b,(%r11)
addq $16,%rsp
subq $16,%rsp
movq $1,%r10
movq %r10,-48(%rbp)
movq -16(%rbp),%rax
movq -48(%rbp),%rbx
addq %rbx,%rax
movq %rax,-40(%rbp)
movq -40(%rbp),%r10
movq %r10,-16(%rbp)
addq $16,%rsp
addq $16,%rsp
jmp .L_start_95
.L_end_95:

movq %rbp,%rsp
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
movq %rsp,%rbp

subq $16,%rsp
movq 16(%rbp),%rax
movq 24(%rbp),%rbx
cmp %rbx,%rax
setl %al
movzbl %al,%eax
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_98
movq 16(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

jmp .L_end_98
.L_else_98:
movq 24(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

.L_end_98:

movq %rbp,%rsp
pop %rbp
ret

.global max
max:
push %rbp
movq %rsp,%rbp

subq $16,%rsp
movq 16(%rbp),%rax
movq 24(%rbp),%rbx
cmp %rbx,%rax
setg %al
movzbl %al,%eax
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_99
movq 16(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

jmp .L_end_99
.L_else_99:
movq 24(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

.L_end_99:

movq %rbp,%rsp
pop %rbp
ret

.global abs_int
abs_int:
push %rbp
movq %rsp,%rbp

subq $16,%rsp
movq $0,%r10
movq %r10,-16(%rbp)
movq 16(%rbp),%rax
movq -16(%rbp),%rbx
cmp %rbx,%rax
setl %al
movzbl %al,%eax
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_100
subq $16,%rsp
movq $0,%r10
movq %r10,-16(%rbp)
movq -16(%rbp),%rax
movq 16(%rbp),%rbx
subq %rbx,%rax
movq %rax,-8(%rbp)
movq -8(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

addq $16,%rsp
jmp .L_end_100
.L_else_100:
.L_end_100:
movq 16(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret


movq %rbp,%rsp
pop %rbp
ret

.global ceil_div
ceil_div:
push %rbp
movq %rsp,%rbp

subq $16,%rsp
subq $16,%rsp
movq 16(%rbp),%rax
movq 24(%rbp),%rbx
addq %rbx,%rax
movq %rax,-24(%rbp)
movq $1,%r10
movq %r10,-32(%rbp)
movq -24(%rbp),%rax
movq -32(%rbp),%rbx
addq $16,%rsp
subq %rbx,%rax
movq %rax,-16(%rbp)
movq -16(%rbp),%rax
movq 24(%rbp),%rbx
cqto
idivq %rbx
movq %rax,-8(%rbp)
movq -8(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret


movq %rbp,%rsp
pop %rbp
ret

.section .data
.align 8
HEAP_CAP: .quad 16777216
HEAP: .quad _galloc_array_2
heap_top: .quad 0
ALIGN: .quad 8
HDR: .quad 8

.section .bss
.align 8
_galloc_array_2: .zero 16777216

.section .text
.global align_up
align_up:
push %rbp
movq %rsp,%rbp

subq $16,%rsp
movq 16(%rbp),%rax
movq 24(%rbp),%rbx
addq %rbx,%rax
movq %rax,-16(%rbp)
movq $1,%r10
subq $16,%rsp
movq %r10,-24(%rbp)
movq -16(%rbp),%rax
movq -24(%rbp),%rbx
addq $16,%rsp
subq %rbx,%rax
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
movq %r10,-16(%rbp)
subq $16,%rsp
movq -16(%rbp),%rax
movq 24(%rbp),%rbx
cqto
idivq %rbx
movq %rdx,-32(%rbp)
movq -16(%rbp),%rax
movq -32(%rbp),%rbx
subq %rbx,%rax
movq %rax,-24(%rbp)
movq -24(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret


movq %rbp,%rsp
pop %rbp
ret

.global memcpy
memcpy:
push %rbp
movq %rsp,%rbp

movq $0,%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq -8(%rbp),%r10
movq %r10,-16(%rbp)
.L_start_101:
subq $16,%rsp
movq -16(%rbp),%rax
movq 32(%rbp),%rbx
cmp %rbx,%rax
setl %al
movzbl %al,%eax
movq %rax,-24(%rbp)
movq -24(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_end_101
subq $16,%rsp
movq $1,%r10
subq $16,%rsp
movq %r10,-40(%rbp)
movq -16(%rbp),%rax
movq -40(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-32(%rbp)
movq 24(%rbp),%rax
movq -32(%rbp),%rbx
addq %rbx,%rax
movq %rax,-24(%rbp)
movq -24(%rbp),%r10
addq $16,%rsp
subq $16,%rsp
movzbq (%r10),%r11
movb %r11b,-17(%rbp)
subq $16,%rsp
movq $1,%r10
movq %r10,-41(%rbp)
movq -16(%rbp),%rax
movq -41(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-33(%rbp)
movq 16(%rbp),%rax
movq -33(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-25(%rbp)
movq -25(%rbp),%r11
movzbq -17(%rbp),%r10
movb %r10b,(%r11)
movq $1,%r10
subq $16,%rsp
movq %r10,-33(%rbp)
movq -16(%rbp),%rax
movq -33(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-25(%rbp)
movq -25(%rbp),%r10
movq %r10,-16(%rbp)
addq $16,%rsp
jmp .L_start_101
.L_end_101:

movq %rbp,%rsp
pop %rbp
ret

.global malloc
malloc:
push %rbp
movq %rsp,%rbp

subq $16,%rsp
movq $0,%r10
movq %r10,-16(%rbp)
movq 16(%rbp),%rax
movq -16(%rbp),%rbx
cmp %rbx,%rax
setle %al
movzbl %al,%eax
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_102
movq $0,%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq -8(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

addq $16,%rsp
jmp .L_end_102
.L_else_102:
.L_end_102:
subq $16,%rsp
movq ALIGN(%rip),%r10
movq %r10,-8(%rbp)
movq heap_top(%rip),%r10
movq %r10,-16(%rbp)
call align_up
addq $16,%rsp
subq $16,%rsp
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
movq %r10,-16(%rbp)
subq $16,%rsp
movq HDR(%rip),%rax
movq 16(%rbp),%rbx
addq %rbx,%rax
movq %rax,-24(%rbp)
movq -24(%rbp),%r10
movq %r10,-32(%rbp)
subq $16,%rsp
movq -16(%rbp),%rax
movq -32(%rbp),%rbx
addq %rbx,%rax
movq %rax,-48(%rbp)
movq -48(%rbp),%rax
movq HEAP_CAP(%rip),%rbx
cmp %rbx,%rax
setg %al
movzbl %al,%eax
movq %rax,-40(%rbp)
movq -40(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_103
movq $0,%r10
subq $16,%rsp
movq %r10,-40(%rbp)
movq -40(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

addq $16,%rsp
jmp .L_end_103
.L_else_103:
.L_end_103:
subq $16,%rsp
movq $1,%r10
subq $16,%rsp
movq %r10,-56(%rbp)
movq -16(%rbp),%rax
movq -56(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-48(%rbp)
movq HEAP(%rip),%rax
movq -48(%rbp),%rbx
addq %rbx,%rax
movq %rax,-40(%rbp)
movq -40(%rbp),%r10
movq %r10,-48(%rbp)
movq -48(%rbp),%r11
movq 16(%rbp),%r10
movq %r10,(%r11)
subq $16,%rsp
movq -16(%rbp),%rax
movq -32(%rbp),%rbx
addq %rbx,%rax
movq %rax,-56(%rbp)
movq -56(%rbp),%r10
movq %r10,heap_top(%rip)
addq $16,%rsp
subq $16,%rsp
subq $16,%rsp
movq $1,%r10
movq %r10,-80(%rbp)
movq -16(%rbp),%rax
movq -80(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-72(%rbp)
movq HEAP(%rip),%rax
movq -72(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-64(%rbp)
subq $16,%rsp
movq $1,%r10
movq %r10,-80(%rbp)
movq HDR(%rip),%rax
movq -80(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-72(%rbp)
movq -64(%rbp),%rax
movq -72(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-56(%rbp)
movq -56(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret


movq %rbp,%rsp
pop %rbp
ret

.global free
free:
push %rbp
movq %rsp,%rbp

subq $16,%rsp
movq $0,%r10
movq %r10,-16(%rbp)
movq 16(%rbp),%rax
movq -16(%rbp),%rbx
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_104
movq $0,%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq -8(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

addq $16,%rsp
jmp .L_end_104
.L_else_104:
.L_end_104:
subq $16,%rsp
movq 16(%rbp),%rax
movq HDR(%rip),%rbx
subq %rbx,%rax
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
movq %r10,-16(%rbp)
subq $16,%rsp
movq -16(%rbp),%r10
movq %r10,-24(%rbp)
movq -24(%rbp),%r10
movq (%r10),%r11
movq %r11,-32(%rbp)
subq $16,%rsp
movq -32(%rbp),%r10
movq %r10,-40(%rbp)
subq $16,%rsp
movq $1,%r10
subq $16,%rsp
movq %r10,-72(%rbp)
movq -40(%rbp),%rax
movq -72(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-64(%rbp)
movq 16(%rbp),%rax
movq -64(%rbp),%rbx
addq %rbx,%rax
movq %rax,-56(%rbp)
subq $16,%rsp
movq $1,%r10
movq %r10,-80(%rbp)
movq heap_top(%rip),%rax
movq -80(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-72(%rbp)
movq HEAP(%rip),%rax
movq -72(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-64(%rbp)
movq -56(%rbp),%rax
movq -64(%rbp),%rbx
addq $16,%rsp
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-48(%rbp)
movq -48(%rbp),%r10
test %r10,%r10
jz .L_else_105
subq $16,%rsp
movq HDR(%rip),%rax
movq -40(%rbp),%rbx
addq %rbx,%rax
movq %rax,-56(%rbp)
movq heap_top(%rip),%rax
movq -56(%rbp),%rbx
addq $16,%rsp
subq %rbx,%rax
movq %rax,-48(%rbp)
movq -48(%rbp),%r10
movq %r10,heap_top(%rip)
jmp .L_end_105
.L_else_105:
.L_end_105:

movq %rbp,%rsp
pop %rbp
ret

.global realloc
realloc:
push %rbp
movq %rsp,%rbp

subq $16,%rsp
movq $0,%r10
movq %r10,-16(%rbp)
movq 16(%rbp),%rax
movq -16(%rbp),%rbx
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_106
subq $16,%rsp
movq 24(%rbp),%r10
movq %r10,-16(%rbp)
call malloc
addq $16,%rsp
subq $16,%rsp
movq %rax,-8(%rbp)
movq -8(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

addq $16,%rsp
jmp .L_end_106
.L_else_106:
.L_end_106:
subq $16,%rsp
movq $0,%r10
movq %r10,-16(%rbp)
movq 24(%rbp),%rax
movq -16(%rbp),%rbx
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
addq $16,%rsp
test %r10,%r10
jz .L_else_107
subq $16,%rsp
movq 16(%rbp),%r10
movq %r10,-16(%rbp)
call free
addq $16,%rsp
movq $0,%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq -8(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

addq $16,%rsp
jmp .L_end_107
.L_else_107:
.L_end_107:
subq $16,%rsp
movq 16(%rbp),%rax
movq HDR(%rip),%rbx
subq %rbx,%rax
movq %rax,-8(%rbp)
movq -8(%rbp),%r10
movq %r10,-16(%rbp)
subq $16,%rsp
movq -16(%rbp),%r10
movq %r10,-24(%rbp)
movq -24(%rbp),%r10
movq (%r10),%r11
movq %r11,-32(%rbp)
subq $16,%rsp
movq -32(%rbp),%r10
movq %r10,-40(%rbp)
subq $16,%rsp
movq $1,%r10
subq $16,%rsp
movq %r10,-72(%rbp)
movq -40(%rbp),%rax
movq -72(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-64(%rbp)
movq 16(%rbp),%rax
movq -64(%rbp),%rbx
addq %rbx,%rax
movq %rax,-56(%rbp)
subq $16,%rsp
movq $1,%r10
movq %r10,-80(%rbp)
movq heap_top(%rip),%rax
movq -80(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-72(%rbp)
movq HEAP(%rip),%rax
movq -72(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-64(%rbp)
movq -56(%rbp),%rax
movq -64(%rbp),%rbx
addq $16,%rsp
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-48(%rbp)
movq -48(%rbp),%r10
test %r10,%r10
jz .L_else_108
subq $16,%rsp
movq HDR(%rip),%rax
movq -40(%rbp),%rbx
addq %rbx,%rax
movq %rax,-56(%rbp)
movq heap_top(%rip),%rax
movq -56(%rbp),%rbx
addq $16,%rsp
subq %rbx,%rax
movq %rax,-48(%rbp)
subq $16,%rsp
movq -48(%rbp),%r10
movq %r10,-56(%rbp)
movq HDR(%rip),%rax
movq 24(%rbp),%rbx
addq %rbx,%rax
movq %rax,-64(%rbp)
subq $16,%rsp
movq -64(%rbp),%r10
movq %r10,-72(%rbp)
subq $16,%rsp
movq -56(%rbp),%rax
movq -72(%rbp),%rbx
addq %rbx,%rax
movq %rax,-88(%rbp)
movq -88(%rbp),%rax
movq HEAP_CAP(%rip),%rbx
addq $16,%rsp
cmp %rbx,%rax
setle %al
movzbl %al,%eax
movq %rax,-80(%rbp)
movq -80(%rbp),%r10
test %r10,%r10
jz .L_else_109
subq $16,%rsp
movq $1,%r10
movq %r10,-96(%rbp)
movq -56(%rbp),%rax
movq -96(%rbp),%rbx
imulq %rbx,%rax
movq %rax,-88(%rbp)
movq HEAP(%rip),%rax
movq -88(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-80(%rbp)
subq $16,%rsp
movq -80(%rbp),%r10
movq %r10,-88(%rbp)
movq -88(%rbp),%r11
movq 24(%rbp),%r10
movq %r10,(%r11)
movq -56(%rbp),%rax
movq -72(%rbp),%rbx
addq %rbx,%rax
movq %rax,-96(%rbp)
movq -96(%rbp),%r10
movq %r10,heap_top(%rip)
subq $16,%rsp
movq $1,%r10
subq $16,%rsp
movq %r10,-120(%rbp)
movq -56(%rbp),%rax
movq -120(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-112(%rbp)
movq HEAP(%rip),%rax
movq -112(%rbp),%rbx
addq %rbx,%rax
movq %rax,-104(%rbp)
movq $1,%r10
subq $16,%rsp
movq %r10,-120(%rbp)
movq HDR(%rip),%rax
movq -120(%rbp),%rbx
addq $16,%rsp
imulq %rbx,%rax
movq %rax,-112(%rbp)
movq -104(%rbp),%rax
movq -112(%rbp),%rbx
addq $16,%rsp
addq %rbx,%rax
movq %rax,-96(%rbp)
movq -96(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

addq $16,%rsp
jmp .L_end_109
.L_else_109:
.L_end_109:
addq $16,%rsp
addq $16,%rsp
jmp .L_end_108
.L_else_108:
.L_end_108:
movq 24(%rbp),%r10
movq %r10,-48(%rbp)
call malloc
movq %rax,-48(%rbp)
subq $16,%rsp
movq -48(%rbp),%r10
movq %r10,-56(%rbp)
movq $0,%r10
subq $16,%rsp
movq %r10,-72(%rbp)
movq -56(%rbp),%rax
movq -72(%rbp),%rbx
addq $16,%rsp
cmp %rbx,%rax
sete %al
movzbl %al,%eax
movq %rax,-64(%rbp)
movq -64(%rbp),%r10
test %r10,%r10
jz .L_else_110
movq $0,%r10
movq %r10,-64(%rbp)
movq -64(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret

jmp .L_end_110
.L_else_110:
.L_end_110:
subq $16,%rsp
movq 24(%rbp),%r10
movq %r10,-72(%rbp)
movq -40(%rbp),%r10
movq %r10,-80(%rbp)
call min
addq $16,%rsp
movq %rax,-64(%rbp)
subq $16,%rsp
subq $16,%rsp
movq -64(%rbp),%r10
movq %r10,-80(%rbp)
movq 16(%rbp),%r10
movq %r10,-88(%rbp)
movq -56(%rbp),%r10
movq %r10,-96(%rbp)
call memcpy
addq $16,%rsp
addq $16,%rsp
movq 16(%rbp),%r10
movq %r10,-64(%rbp)
call free
movq -56(%rbp),%rax

movq %rbp,%rsp
pop %rbp
ret


movq %rbp,%rsp
pop %rbp
ret

.global arena_reset
arena_reset:
push %rbp
movq %rsp,%rbp

movq $0,%r10
subq $16,%rsp
movq %r10,-8(%rbp)
movq -8(%rbp),%r10
movq %r10,heap_top(%rip)
addq $16,%rsp

movq %rbp,%rsp
pop %rbp
ret

)");
