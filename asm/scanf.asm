	.section .rodata
fmt_1:	.string "Enter x: "
fmt_2:	.string "%d"
fmt_3:	.string "You entered %d...\n"
fmt_4:	.string "What have you entered? Huh?"
	
	.section .text
	.globl main
main:
	pushq %rbp
	movq %rsp, %rbp 

	subq $8, %rsp 		# int x
	
	movq $fmt_1, %rdi
	xorl %eax, %eax	
	call printf

	movq $fmt_2, %rdi
	leaq -8(%rbp), %rsi
	xorl %eax, %eax	
	call scanf

	cmpq $1, %rax
	jne not_equal_to_1

	
	movq $fmt_3, %rdi
	movq -8(%rbp), %rsi
	xorl %eax, %eax	
	call printf
	jmp end_of_if
	
not_equal_to_1:
	movq $fmt_4, %rdi
	call puts
	
end_of_if:	
	movq %rbp, %rsp
	popq %rbp
	
	xorl %eax, %eax
	ret
