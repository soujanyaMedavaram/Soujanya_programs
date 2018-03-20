	.file	"sum_digi.c"
	.section	.rodata
.LC0:
	.string	"%d"
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
	subl	$8, %esp
	leal	-4(%ebp), %eax
	pushl	%eax
	pushl	$.LC0
	call	scanf
	addl	$16, %esp
	subl	$12, %esp
	pushl	-4(%ebp)
	call	sum
	addl	$16, %esp
	movl	%eax, -4(%ebp)
	subl	$8, %esp
	pushl	-4(%ebp)
	pushl	$.LC1
	call	printf
	addl	$16, %esp
	leave
	ret
.Lfe1:
	.size	main,.Lfe1-main
	.data
	.align 4
	.type	sum_num.0,@object
	.size	sum_num.0,4
sum_num.0:
	.long	0
	.section	.rodata
.LC2:
	.string	"%d->sum_sub\n"
.LC3:
	.string	"%d->num\n"
	.text
.globl sum
	.type	sum,@function
sum:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	cmpl	$0, 8(%ebp)
	je	.L3
	movl	8(%ebp), %edx
	movl	%edx, %eax
	movl	$10, %ecx
	cltd
	idivl	%ecx
	addl	%edx, sum_num.0
	subl	$8, %esp
	pushl	sum_num.0
	pushl	$.LC2
	call	printf
	addl	$16, %esp
	subl	$12, %esp
	movl	8(%ebp), %ecx
	movl	$1717986919, %eax
	imull	%ecx
	sarl	$2, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	pushl	%eax
	call	sum
	addl	$16, %esp
.L3:
	subl	$8, %esp
	pushl	8(%ebp)
	pushl	$.LC3
	call	printf
	addl	$16, %esp
	movl	sum_num.0, %eax
	leave
	ret
.Lfe2:
	.size	sum,.Lfe2-sum
	.ident	"GCC: (GNU) 3.2.2 20030222 (Red Hat Linux 3.2.2-5)"
