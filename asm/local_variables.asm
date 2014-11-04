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
	pushq %rbp
	movq %rsp, %rbp

	subq $16, %rsp
	movq $123, %rdi
	movq $456, %rsi
	leaq -16(%rbp), %rdx 	# -16(%rbp) is sum
	leaq -8(%rbp), %rcx	# -8(%rbp) is product
	call f1

	movq $fmt_1, %rdi
	movq -16(%rbp), %rsi
	movq -8(%rbp), %rdx
	xorq %rax, %rax
	call printf

	movq %rbp, %rsp
	popq %rbp
	
	xorq %rax, %rax
	ret
