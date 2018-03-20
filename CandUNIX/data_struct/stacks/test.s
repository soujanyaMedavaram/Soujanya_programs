	.file	"test.c"
	.section	.rodata
.LC0:
	.string	"exec failed\n"
.LC1:
	.string	"\n fork failed\n"
.LC2:
	.string	"\n program is success\n"
	.text
.globl main
	.type	main,@function
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	andl	$-16, %esp
	movl	$0, %eax
	subl	%eax, %esp
	call	fork
	movl	%eax, -4(%ebp)
	cmpl	$-1, -4(%ebp)
	je	.L4
	cmpl	$0, -4(%ebp)
	je	.L3
	jmp	.L2
.L3:
	subl	$8, %esp
	pushl	12(%ebp)
	movl	12(%ebp), %eax
	pushl	(%eax)
	call	execvp
	addl	$16, %esp
	subl	$8, %esp
	pushl	$.LC0
	pushl	stderr
	call	fprintf
	addl	$16, %esp
	subl	$12, %esp
	pushl	$1
	call	exit
.L4:
	subl	$12, %esp
	pushl	$.LC1
	call	printf
	addl	$16, %esp
.L2:
	subl	$12, %esp
	pushl	$.LC2
	call	printf
	addl	$16, %esp
	subl	$12, %esp
	pushl	$0
	call	exit
.Lfe1:
	.size	main,.Lfe1-main
	.ident	"GCC: (GNU) 3.2.2 20030222 (Red Hat Linux 3.2.2-5)"
