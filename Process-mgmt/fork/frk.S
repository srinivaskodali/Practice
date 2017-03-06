	.file	"frk1.c"
	.section	.rodata
.LC0:
	.string	" My pid = %d \n"
.LC1:
	.string	" child: My pid = %d \n"
	.align 4
.LC2:
	.string	" Newly created child pid = %d \n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	subl	$32, %esp
	call	getpid
	movl	%eax, 4(%esp)
	movl	$.LC0, (%esp)
	call	printf
	call	getchar
	call	fork
	movl	%eax, 28(%esp)
	cmpl	$0, 28(%esp)
	jne	.L2
	call	getpid
	movl	%eax, 4(%esp)
	movl	$.LC1, (%esp)
	call	printf
	jmp	.L6
.L2:
	call	getpid
	movl	%eax, 4(%esp)
	movl	$.LC0, (%esp)
	call	printf
	movl	28(%esp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC2, (%esp)
	call	printf
.L4:
	jmp	.L4
.L6:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
