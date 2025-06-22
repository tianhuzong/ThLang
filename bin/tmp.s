	.text
	.file	"main"
	.globl	"加法"
	.p2align	4, 0x90
	.type	"加法",@function
"加法":
	.cfi_startproc
	xorl	%eax, %eax
	retq
.Lfunc_end0:
	.size	"加法", .Lfunc_end0-"加法"
	.cfi_endproc

	.globl	"减法"
	.p2align	4, 0x90
	.type	"减法",@function
"减法":
	.cfi_startproc
	movl	%edi, %eax
	movl	%edi, -4(%rsp)
	movl	%esi, -8(%rsp)
	subl	%esi, %eax
	retq
.Lfunc_end1:
	.size	"减法", .Lfunc_end1-"减法"
	.cfi_endproc

	.section	.rodata.cst8,"aM",@progbits,8
	.p2align	3, 0x0
.LCPI2_0:
	.quad	0x3ff0000000000000
	.text
	.globl	add11
	.p2align	4, 0x90
	.type	add11,@function
add11:
	.cfi_startproc
	movsd	%xmm0, -8(%rsp)
	movl	%edi, -12(%rsp)
	addsd	.LCPI2_0(%rip), %xmm0
	retq
.Lfunc_end2:
	.size	add11, .Lfunc_end2-add11
	.cfi_endproc

	.section	.rodata.cst8,"aM",@progbits,8
	.p2align	3, 0x0
.LCPI3_0:
	.quad	0x4016666666666666
	.text
	.globl	main
	.p2align	4, 0x90
	.type	main,@function
main:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%r15
	pushq	%r14
	pushq	%rbx
	pushq	%rax
	.cfi_offset %rbx, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	movl	$0, -28(%rbp)
	movl	$1, -32(%rbp)
	movb	$1, %al
	testb	%al, %al
	je	.LBB3_18
	cmpl	$20, -28(%rbp)
	je	.LBB3_18
	cmpl	$18, -28(%rbp)
	je	.LBB3_18
	cmpl	$18, -28(%rbp)
	je	.LBB3_18
	cmpl	$11, -32(%rbp)
	je	.LBB3_18
	cmpl	$18, -28(%rbp)
	je	.LBB3_18
	cmpl	$7, -32(%rbp)
	je	.LBB3_18
	cmpl	$10, -28(%rbp)
	je	.LBB3_18
	cmpl	$5, -28(%rbp)
	je	.LBB3_18
	cmpl	$7, -28(%rbp)
	je	.LBB3_18
	cmpl	$17, -28(%rbp)
	je	.LBB3_18
	cmpl	$11, -28(%rbp)
	je	.LBB3_18
	cmpl	$13, -28(%rbp)
	je	.LBB3_18
	cmpl	$8, -28(%rbp)
	je	.LBB3_18
	cmpl	$13, -32(%rbp)
	je	.LBB3_18
	cmpl	$8, -28(%rbp)
	je	.LBB3_18
	cmpl	$8, -28(%rbp)
	je	.LBB3_18
	cmpl	$10, -32(%rbp)
	jne	.LBB3_19
.LBB3_18:
	movl	$1, -28(%rbp)
.LBB3_19:
	movq	%rsp, %rax
	leaq	-16(%rax), %rcx
	movq	%rcx, %rsp
	movl	$0, -16(%rax)
	movq	%rsp, %r11
	leaq	-16(%r11), %rax
	movq	%rax, %rsp
	movl	$0, -16(%r11)
	movq	%rsp, %rdx
	leaq	-16(%rdx), %rdi
	movq	%rdi, %rsp
	movl	$0, -16(%rdx)
	movq	%rsp, %rdx
	leaq	-16(%rdx), %rbx
	movq	%rbx, %rsp
	movl	$0, -16(%rdx)
	movq	%rsp, %rdx
	leaq	-16(%rdx), %rsi
	movq	%rsi, %rsp
	movl	$0, -16(%rdx)
	movq	%rsp, %rdx
	leaq	-16(%rdx), %r10
	movq	%r10, %rsp
	movl	$0, -16(%rdx)
	movq	%rsp, %rdx
	leaq	-16(%rdx), %r9
	movq	%r9, %rsp
	movl	$0, -16(%rdx)
	movq	%rsp, %r8
	leaq	-16(%r8), %rdx
	movq	%rdx, %rsp
	movl	$0, -16(%r8)
	movq	%rsp, %r14
	leaq	-16(%r14), %r8
	movq	%r8, %rsp
	movl	$0, -16(%r14)
	movq	%rsp, %r15
	leaq	-16(%r15), %r14
	movq	%r14, %rsp
	movl	$0, -16(%r15)
	cmpl	$14, -16(%r11)
	je	.LBB3_18
	cmpl	$20, (%r14)
	je	.LBB3_18
	cmpl	$12, (%r10)
	je	.LBB3_18
	cmpl	$14, (%rbx)
	je	.LBB3_18
	cmpl	$6, (%r10)
	je	.LBB3_18
	cmpl	$8, (%rax)
	je	.LBB3_18
	cmpl	$17, (%rcx)
	je	.LBB3_18
	cmpl	$5, (%r10)
	je	.LBB3_18
	cmpl	$5, (%r9)
	je	.LBB3_18
	cmpl	$8, (%r9)
	je	.LBB3_18
	cmpl	$13, (%rdi)
	je	.LBB3_18
	cmpl	$13, (%rdx)
	je	.LBB3_18
	cmpl	$11, (%r8)
	je	.LBB3_18
	cmpl	$10, (%rcx)
	je	.LBB3_18
	cmpl	$8, (%rsi)
	je	.LBB3_18
	cmpl	$7, (%r8)
	je	.LBB3_18
	cmpl	$9, (%rdx)
	je	.LBB3_18
	cmpl	$10, (%r8)
	je	.LBB3_18
	cmpl	$7, (%rax)
	je	.LBB3_18
	cmpl	$8, (%rdx)
	jne	.LBB3_40
	movl	$1, -28(%rbp)
.LBB3_40:
	movq	%rsp, %rax
	leaq	-16(%rax), %rsp
	movl	$0, -16(%rax)
	movq	%rsp, %rax
	leaq	-16(%rax), %rsp
	movl	$0, -16(%rax)
	movq	%rsp, %rax
	leaq	-16(%rax), %rsp
	movl	$0, -16(%rax)
	movq	%rsp, %rax
	leaq	-16(%rax), %rsp
	movl	$0, -16(%rax)
	movq	%rsp, %rax
	leaq	-16(%rax), %rsp
	movl	$0, -16(%rax)
	movq	%rsp, %rax
	leaq	-16(%rax), %rsp
	movl	$0, -16(%rax)
	movq	%rsp, %rax
	leaq	-16(%rax), %rsp
	movl	$0, -16(%rax)
	movq	%rsp, %rax
	leaq	-16(%rax), %rsp
	movl	$0, -16(%rax)
	movq	%rsp, %rax
	leaq	-16(%rax), %rsp
	movl	$0, -16(%rax)
	movq	%rsp, %rax
	leaq	-16(%rax), %rsp
	movl	$0, -16(%rax)
	movq	%rsp, %rax
	leaq	-16(%rax), %rsp
	movl	$0, -16(%rax)
	movq	%rsp, %rax
	leaq	-16(%rax), %rsp
	movl	$0, -16(%rax)
	movq	%rsp, %rax
	leaq	-16(%rax), %rsp
	movl	$0, -16(%rax)
	movq	%rsp, %rax
	leaq	-16(%rax), %rsp
	movl	$0, -16(%rax)
	movq	%rsp, %rax
	leaq	-16(%rax), %rsp
	movl	$0, -16(%rax)
	movq	%rsp, %rax
	leaq	-16(%rax), %rsp
	movl	$0, -16(%rax)
	movq	%rsp, %rax
	leaq	-16(%rax), %rsp
	movabsq	$4609434218613702656, %rcx
	movq	%rcx, -16(%rax)
	movq	%rsp, %rax
	leaq	-16(%rax), %rsp
	movl	$0, -16(%rax)
	movq	%rsp, %rbx
	leaq	-16(%rbx), %rsp
	movabsq	$4617991057905706598, %rcx
	movq	%rcx, -16(%rbx)
	movl	-16(%rax), %edi
	movsd	.LCPI3_0(%rip), %xmm0
	callq	add11@PLT
	movsd	%xmm0, -16(%rbx)
	callq	"加法"@PLT
	movl	%eax, %ebx
	callq	"加法"@PLT
	addl	%eax, %eax
	leal	(%rax,%rax,2), %edi
	subl	%ebx, %edi
	addl	$47, %edi
	movl	$47, %esi
	callq	"减法"@PLT
	leaq	-24(%rbp), %rsp
	popq	%rbx
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end3:
	.size	main, .Lfunc_end3-main
	.cfi_endproc

	.section	".note.GNU-stack","",@progbits
