	.section .rodata

a_lt_b:
	.string "a < b"

a_eq_b:
	.string "a == b"

a_gt_b:
	.string "a > b"


	.section .text

f_signed:
	cmpq %rdi, %rsi
	cmovg $a_gt_b, %rdi
	cmoveq $a_eq_b, %rdi
	cmovlq $a_lt_b, %rdi
	
	xorq %rax, %rax
	call puts

	ret

f_unsigned:
	cmpq %rdi, %rsi
	cmovaq $a_gt_b, %rdi
	cmoveq $a_eq_b, %rdi
	cmovbq $a_lt_b, %rdi

	xorq %rax, %rax
	call puts

	ret

	.globl main
main:
	movq $1, %rdi
	movq $2, %rsi
	call f_signed
	
	movq $1, %rdi
	movq $2, %rsi
	call f_unsigned

	ret


	
	
