	.section .data
a:	.quad 4
b:	.double 4.4
c:	.rept 10
	.long 0
	.endr
d:	.word 1, 2
e:	.byte 0xfb
f:	.string "Hello, World"

	.section .text
	.globl main
main:
	pushq %rbp
	movq  %rsp, %rbp
	subq $16, %rsp

	xorl %eax, %eax
	leave
	ret
