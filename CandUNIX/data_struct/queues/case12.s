	.file	"case12.c"
	.text
.globl openQ
	.type	openQ,@function
openQ:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	subl	$12, %esp
	pushl	$28
	call	malloc
	addl	$16, %esp
	movl	%eax, -8(%ebp)
	cmpl	$0, -8(%ebp)
	jne	.L2
	movl	$0, -4(%ebp)
	jmp	.L1
.L2:
	subl	$12, %esp
	movl	8(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	pushl	%eax
	call	malloc
	addl	$16, %esp
	movl	-8(%ebp), %edx
	movl	%eax, 24(%edx)
	movl	-8(%ebp), %edx
	movl	24(%edx), %eax
	movl	-8(%ebp), %edx
	movl	%eax, 20(%edx)
	movl	-8(%ebp), %edx
	movl	24(%edx), %eax
	movl	-8(%ebp), %edx
	movl	%eax, 16(%edx)
	movl	8(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	movl	-8(%ebp), %edx
	addl	24(%edx), %eax
	movl	-8(%ebp), %edx
	movl	%eax, 12(%edx)
	movl	-8(%ebp), %eax
	movl	$5, (%eax)
	movl	8(%ebp), %eax
	movl	-8(%ebp), %edx
	movl	%eax, 4(%edx)
	movl	-8(%ebp), %eax
	movl	$0, 8(%eax)
	movl	-8(%ebp), %edx
	movl	%edx, -4(%ebp)
.L1:
	movl	-4(%ebp), %eax
	leave
	ret
.Lfe1:
	.size	openQ,.Lfe1-openQ
	.section	.rodata
.LC0:
	.string	"allocating maemory\n"
	.text
.globl enQ
	.type	enQ,@function
enQ:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	8(%ebp), %edx
	movl	8(%edx), %eax
	movl	8(%ebp), %ecx
	cmpl	(%ecx), %eax
	jne	.L4
	subl	$12, %esp
	pushl	$.LC0
	call	printf
	addl	$16, %esp
	movl	8(%ebp), %eax
	movl	24(%eax), %edx
	movl	8(%ebp), %ecx
	movl	12(%ecx), %eax
	subl	%edx, %eax
	movl	%eax, -4(%ebp)
	movl	8(%ebp), %eax
	movl	20(%eax), %edx
	movl	8(%ebp), %ecx
	movl	12(%ecx), %eax
	subl	%edx, %eax
	movl	%eax, -12(%ebp)
	movl	8(%ebp), %eax
	movl	24(%eax), %edx
	movl	8(%ebp), %ecx
	movl	16(%ecx), %eax
	subl	%edx, %eax
	movl	%eax, -8(%ebp)
	subl	$8, %esp
	movl	8(%ebp), %eax
	addl	$5, (%eax)
	movl	8(%ebp), %edx
	movl	(%edx), %eax
	sall	$2, %eax
	pushl	%eax
	movl	8(%ebp), %ecx
	pushl	24(%ecx)
	call	realloc
	addl	$16, %esp
	movl	8(%ebp), %edx
	movl	%eax, 24(%edx)
	movl	8(%ebp), %ecx
	movl	(%ecx), %eax
	movl	8(%ebp), %edx
	imull	4(%edx), %eax
	movl	8(%ebp), %ecx
	addl	24(%ecx), %eax
	movl	8(%ebp), %edx
	movl	%eax, 12(%edx)
	movl	8(%ebp), %ecx
	movl	16(%ecx), %eax
	movl	8(%ebp), %edx
	cmpl	24(%edx), %eax
	jne	.L5
	movl	8(%ebp), %ecx
	movl	20(%ecx), %eax
	movl	8(%ebp), %edx
	cmpl	24(%edx), %eax
	jne	.L5
	movl	-12(%ebp), %eax
	movl	8(%ebp), %ecx
	addl	24(%ecx), %eax
	movl	8(%ebp), %edx
	movl	%eax, 16(%edx)
	movl	8(%ebp), %ecx
	movl	24(%ecx), %eax
	movl	8(%ebp), %edx
	movl	%eax, 20(%edx)
	jmp	.L4
.L5:
	subl	$4, %esp
	pushl	-12(%ebp)
	movl	-8(%ebp), %eax
	movl	8(%ebp), %ecx
	addl	24(%ecx), %eax
	pushl	%eax
	movl	-12(%ebp), %edx
	movl	8(%ebp), %ecx
	movl	12(%ecx), %eax
	subl	%edx, %eax
	pushl	%eax
	call	memmove
	addl	$16, %esp
	movl	-12(%ebp), %edx
	movl	8(%ebp), %ecx
	movl	12(%ecx), %eax
	subl	%edx, %eax
	movl	8(%ebp), %edx
	movl	%eax, 20(%edx)
	movl	-8(%ebp), %eax
	movl	8(%ebp), %ecx
	addl	24(%ecx), %eax
	movl	8(%ebp), %edx
	movl	%eax, 16(%edx)
.L4:
	subl	$4, %esp
	movl	8(%ebp), %ecx
	pushl	4(%ecx)
	pushl	12(%ebp)
	movl	8(%ebp), %eax
	pushl	16(%eax)
	call	memcpy
	addl	$16, %esp
	movl	8(%ebp), %edx
	incl	8(%edx)
	movl	8(%ebp), %ecx
	movl	4(%ecx), %eax
	movl	8(%ebp), %edx
	addl	%eax, 16(%edx)
	movl	8(%ebp), %ecx
	movl	16(%ecx), %eax
	movl	8(%ebp), %edx
	cmpl	12(%edx), %eax
	jb	.L7
	movl	8(%ebp), %ecx
	movl	24(%ecx), %eax
	movl	8(%ebp), %edx
	movl	%eax, 16(%edx)
.L7:
	movl	$0, %eax
	leave
	ret
.Lfe2:
	.size	enQ,.Lfe2-enQ
.globl deQ
	.type	deQ,@function
deQ:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	8(%ebp), %eax
	cmpl	$0, 8(%eax)
	jne	.L9
	movl	$-2, -4(%ebp)
	jmp	.L8
.L9:
	movl	8(%ebp), %edx
	decl	8(%edx)
	subl	$4, %esp
	movl	8(%ebp), %eax
	pushl	4(%eax)
	movl	8(%ebp), %edx
	pushl	20(%edx)
	pushl	12(%ebp)
	call	memcpy
	addl	$16, %esp
	movl	8(%ebp), %edx
	movl	4(%edx), %eax
	movl	8(%ebp), %edx
	addl	%eax, 20(%edx)
	movl	8(%ebp), %edx
	movl	20(%edx), %eax
	movl	8(%ebp), %edx
	cmpl	12(%edx), %eax
	jb	.L10
	movl	8(%ebp), %edx
	movl	24(%edx), %eax
	movl	8(%ebp), %edx
	movl	%eax, 20(%edx)
.L10:
	movl	$0, -4(%ebp)
.L8:
	movl	-4(%ebp), %eax
	leave
	ret
.Lfe3:
	.size	deQ,.Lfe3-deQ
.globl closeQ
	.type	closeQ,@function
closeQ:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	subl	$12, %esp
	pushl	8(%ebp)
	call	free
	addl	$16, %esp
	movl	$0, %eax
	leave
	ret
.Lfe4:
	.size	closeQ,.Lfe4-closeQ
	.ident	"GCC: (GNU) 3.2.2 20030222 (Red Hat Linux 3.2.2-5)"
