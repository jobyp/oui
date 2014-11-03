	.text

get_some_values:

	leaq 1(%rsi), %rdx
	movq %rdx, (%rdi)

	leaq 2(%rsi), %rdx
	movq %rdx, 8(%rdi)

	addq $3, %rsi
	movq %rsi, 16(%rdi)

	ret



	.globl main
main:
	pushq %rbp
	movq %rsp, %rbp

	subq $24, %rsp

	leaq -24(%rbp), %rdi
	movq $20, %rsi

	call get_some_values

	movq -8(%rbp), %rax
	addq -16(%rbp), %rax
	addq -24(%rbp), %rax

	movq %rbp, %rsp
	popq %rbp

	ret
