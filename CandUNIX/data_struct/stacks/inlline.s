	.file	"inlline.c"
	.section	.rodata
.LC0:
	.string	"hai"
	.text
.globl sub1
	.type	sub1,@function
sub1:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	subl	$12, %esp
	pushl	$.LC0
	call	printf
	addl	$16, %esp
	leave
	ret
.Lfe1:
	.size	sub1,.Lfe1-sub1
	.section	.rodata
.LC1:
	.string	"%d\n"
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
	movl	$20, -4(%ebp)
	subl	$8, %esp
	pushl	-4(%ebp)
	pushl	$.LC1
	call	printf
	addl	$16, %esp
	call	sub1
	leave
	ret
.Lfe2:
	.size	main,.Lfe2-main
	.ident	"GCC: (GNU) 3.2.2 20030222 (Red Hat Linux 3.2.2-5)"
