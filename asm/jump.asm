	.section .rodata
begin:
	.string "begin"
skip:
	.string "skip"

end:
	.string "end"


	.text
	.globl main
main:
	movq $begin, %rdi
	xorq %rax, %rax
	call puts

	jmp goto_end

	movq $skip, %rdi
	xorq %rax, %rax
	call puts

goto_end:
	movq $end, %rdi
	xorq %rax, %rax
	call puts

	ret


	