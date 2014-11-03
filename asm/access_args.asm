	.section .rodata
fmt_1:	.string "%d\n"

	.section .text

f:
	movq %rdi, %rax
	movq %rdx, %r8
	imulq %rsi
	addq %r8, %rax
	ret


	.globl main
main:
	movq $2, %rdi
	movq $3, %rsi
	movq $4, %rdx
	call f

	movq $fmt_1, %rdi
	movq %rax, %rsi
	xorl %eax, %eax
	call printf

	xorl %eax, %eax
	ret

	