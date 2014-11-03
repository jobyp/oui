	.section .rodata
fmt_1:	.string "Enter x: "
fmt_2:	.string "%d"
fmt_3:	.string "You entered %d...\n"


	.section .data
x:	.quad 0

	.section .text
	.globl main
main:
	pushq %rbp
	movq %rsp, %rbp 

	movq $fmt_1, %rdi
	xorl %eax, %eax	
	call printf

	movq $fmt_2, %rdi
	movq $x, %rsi
	xorl %eax, %eax	
	call scanf
	
	movq $fmt_3, %rdi
	movq x, %rsi
	xorl %eax, %eax	
	call printf

	movq %rbp, %rsp
	popq %rbp
	
	xorl %eax, %eax
	ret
