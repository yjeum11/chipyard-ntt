	.file	"rocctest.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$3, -4(%rbp)
	movl	$3, -8(%rbp)
	movl	-4(%rbp), %eax
	movl	-8(%rbp), %edx
#APP
# 8 "rocctest.c" 1
	.insn r 0b0101011, 0x7,0x43, %eax, %eax, %edx
# 0 "" 2
#NO_APP
	movl	%eax, -12(%rbp)
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (conda-forge gcc 11.4.0-5) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
