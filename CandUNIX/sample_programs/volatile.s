	.file	"volatile.c"
	.text
.globl sub
	.type	sub,@function
sub:
	pushl	%ebp
	movl	%esp, %ebp
	movl	$-2097152, mem_io
	movl	$-2097152, %eax
	movb	(%eax), %al
	andl	$1, %eax
.L2:
	testb	%al, %al
	jne	.L2
	leave
	ret
.Lfe1:
	.size	sub,.Lfe1-sub
.globl main
	.type	main,@function
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	andl	$-16, %esp
	call	sub
	leave
	ret
.Lfe2:
	.size	main,.Lfe2-main
	.comm	mem_io,4,4
	.ident	"GCC: (GNU) 3.2.2 20030222 (Red Hat Linux 3.2.2-5)"
