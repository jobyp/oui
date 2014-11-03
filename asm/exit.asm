	.section .rodata
fmt_1:
	.string "sum = %d, product = %d\n"

	.data
sum:
	.quad 0
product:
	.quad 0


	.text
f1:
	movq %rdi, %rax
	addq %rsi, %rax
	movq %rax, (%rdx)

	movq %rdi, %rax
	imul %rsi
	movq %rax, (%rcx)

	ret


	.globl main
main:
	movq $123, %rdi
	movq $456, %rsi
	movq $sum, %rdx
	movq $product, %rcx
	call f1

	movq $fmt_1, %rdi
	movq sum, %rsi
	movq product, %rdx
	xorq %rax, %rax
	call printf

	xorq %rax, %rax
	ret


	