	.file	"matrix_math.c"
	.version	"01.01"
gcc2_compiled.:
.text
	.align 4
.globl calculate_normal
	.type	 calculate_normal,@function
calculate_normal:
	pushl %ebp
	movl %esp,%ebp
	subl $72,%esp
	flds 20(%ebp)
	fsubs 8(%ebp)
	fstps -4(%ebp)
	flds 24(%ebp)
	fsubs 12(%ebp)
	fstps -8(%ebp)
	flds 28(%ebp)
	fsubs 16(%ebp)
	fstps -12(%ebp)
	flds 32(%ebp)
	fsubs 8(%ebp)
	fstps -16(%ebp)
	flds 36(%ebp)
	fsubs 12(%ebp)
	fstps -20(%ebp)
	flds 40(%ebp)
	fsubs 16(%ebp)
	fstps -24(%ebp)
	flds -8(%ebp)
	fmuls -24(%ebp)
	flds -20(%ebp)
	fmuls -24(%ebp)
	fsubrp %st,%st(1)
	fstps -28(%ebp)
	flds -16(%ebp)
	fmuls -12(%ebp)
	flds -4(%ebp)
	fmuls -24(%ebp)
	fsubrp %st,%st(1)
	fstps -32(%ebp)
	flds -4(%ebp)
	fmuls -20(%ebp)
	flds -16(%ebp)
	fmuls -8(%ebp)
	fsubrp %st,%st(1)
	fstps -36(%ebp)
	addl $-8,%esp
	flds -28(%ebp)
	fmuls -28(%ebp)
	flds -32(%ebp)
	fmuls -32(%ebp)
	faddp %st,%st(1)
	flds -36(%ebp)
	fmuls -36(%ebp)
	faddp %st,%st(1)
	subl $8,%esp
	fstpl (%esp)
	call sqrt
	addl $16,%esp
	fstps -40(%ebp)
	movl 44(%ebp),%eax
	flds -28(%ebp)
	fdivs -40(%ebp)
	fstps (%eax)
	movl 48(%ebp),%eax
	flds -32(%ebp)
	fdivs -40(%ebp)
	fstps (%eax)
	movl 52(%ebp),%eax
	flds -36(%ebp)
	fdivs -40(%ebp)
	fstps (%eax)
	xorl %eax,%eax
	jmp .L2
	.p2align 4,,7
.L2:
	leave
	ret
.Lfe1:
	.size	 calculate_normal,.Lfe1-calculate_normal
	.ident	"GCC: (GNU) 2.95.3 20010315 (release)"
