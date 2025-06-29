	.text
	.file	"_start.c"
	.globl	_start                  # -- Begin function _start
	.p2align	4, 0x90
	.type	_start,@function
_start:                                 # @_start
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$64, %rsp
	xorl	%eax, %eax
	movl	%eax, %ecx
	movq	%rbp, %rdx
	addq	$8, %rdx
	movq	%rdx, -8(%rbp)
	movq	-8(%rbp), %rdx
	movq	(%rdx), %rdx
                                        # kill: def $edx killed $edx killed $rdx
	movl	%edx, -12(%rbp)
	movq	-8(%rbp), %rsi
	addq	$8, %rsi
	movq	%rsi, -24(%rbp)
	movq	-24(%rbp), %rsi
	movslq	-12(%rbp), %rdi
	shlq	$3, %rdi
	addq	%rdi, %rsi
	addq	$8, %rsi
	movq	%rsi, -32(%rbp)
	movl	-12(%rbp), %esi
	movq	-24(%rbp), %rdx
	movq	%rbp, %rdi
	movabsq	$main, %r8
	movq	%rdi, -40(%rbp)         # 8-byte Spill
	movq	%r8, %rdi
	movq	%rcx, -48(%rbp)         # 8-byte Spill
	movq	-48(%rbp), %r8          # 8-byte Reload
	movq	-48(%rbp), %r9          # 8-byte Reload
	movq	-40(%rbp), %r10         # 8-byte Reload
	movq	%r10, (%rsp)
	callq	__libc_start_main
	ud2
	addq	$64, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end0:
	.size	_start, .Lfunc_end0-_start
	.cfi_endproc
                                        # -- End function
	.ident	"clang version 10.0.0-4ubuntu1 "
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym __libc_start_main
	.addrsig_sym main
