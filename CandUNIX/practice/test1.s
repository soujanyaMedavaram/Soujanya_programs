	.file	"test1.c"
	.text
.globl main
	.type	main,@function
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	andl	$-16, %esp
	movl	$0, %eax
	subl	%eax, %esp
	movl	$10, -4(%ebp)
	movl	$20, -8(%ebp)
	movl	-4(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	-8(%ebp), %edx
	movl	-4(%ebp), %eax
	subl	%edx, %eax
	movl	%eax, -12(%ebp)
	movl	-8(%ebp), %eax
	addl	-4(%ebp), %eax
	movl	%eax, -12(%ebp)
	leave
	ret
.Lfe1:
	.size	main,.Lfe1-main
	.ident	"GCC: (GNU) 3.2.2 20030222 (Red Hat Linux 3.2.2-5)"
