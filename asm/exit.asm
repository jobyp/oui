	.section .rodata
my_name:
	.string "Joby Poriyath"

format_str_1:
	.string "I'm %s"
	
	.section .text
	.globl main
main:
	pushq %rbp
	movq  %rsp, %rbp

	subq  $1024, %rsp

	movq  %rsp, %rdi
	movq  $1024, %rsi
	movq  $format_str_1, %rdx
	movq  $my_name, %rcx
	xorl %eax, %eax
	call snprintf
	
	movq %rsp, %rdi
	xorl %eax, %eax
	call puts

	xorl %eax, %eax
	movq %rbp, %rsp
	popq %rbp
	ret
