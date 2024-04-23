	.text
	.file	"test.c"
	.globl	routine                         # -- Begin function routine
	.p2align	4, 0x90
	.type	routine,@function
routine:                                # @routine
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movl	$0, -12(%rbp)
.LBB0_1:                                # =>This Inner Loop Header: Depth=1
	cmpl	$1000000, -12(%rbp)             # imm = 0xF4240
	jge	.LBB0_4
# %bb.2:                                #   in Loop: Header=BB0_1 Depth=1
	movabsq	$mutex, %rdi
	callq	pthread_mutex_lock
	movl	mails, %eax
	addl	$1, %eax
	movl	%eax, mails
	movabsq	$mutex, %rdi
	callq	pthread_mutex_unlock
# %bb.3:                                #   in Loop: Header=BB0_1 Depth=1
	movl	-12(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -12(%rbp)
	jmp	.LBB0_1
.LBB0_4:
	movq	-8(%rbp), %rax
	addq	$16, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end0:
	.size	routine, .Lfunc_end0-routine
	.cfi_endproc
                                        # -- End function
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movl	$0, -4(%rbp)
	movl	%edi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movabsq	$mutex, %rdi
	xorl	%eax, %eax
	movl	%eax, %esi
	callq	pthread_mutex_init
	leaq	-24(%rbp), %rdi
	xorl	%eax, %eax
	movl	%eax, %ecx
	movabsq	$routine, %rdx
	movq	%rcx, %rsi
	callq	pthread_create
	cmpl	$0, %eax
	je	.LBB1_2
# %bb.1:
	movl	$1, -4(%rbp)
	jmp	.LBB1_9
.LBB1_2:
	leaq	-32(%rbp), %rdi
	xorl	%eax, %eax
	movl	%eax, %ecx
	movabsq	$routine, %rdx
	movq	%rcx, %rsi
	callq	pthread_create
	cmpl	$0, %eax
	je	.LBB1_4
# %bb.3:
	movl	$2, -4(%rbp)
	jmp	.LBB1_9
.LBB1_4:
	movq	-24(%rbp), %rdi
	xorl	%eax, %eax
	movl	%eax, %esi
	callq	pthread_join
	cmpl	$0, %eax
	je	.LBB1_6
# %bb.5:
	movl	$3, -4(%rbp)
	jmp	.LBB1_9
.LBB1_6:
	movq	-32(%rbp), %rdi
	xorl	%eax, %eax
	movl	%eax, %esi
	callq	pthread_join
	cmpl	$0, %eax
	je	.LBB1_8
# %bb.7:
	movl	$4, -4(%rbp)
	jmp	.LBB1_9
.LBB1_8:
	movabsq	$mutex, %rdi
	callq	pthread_mutex_destroy
	movl	mails, %esi
	movabsq	$.L.str, %rdi
	movb	$0, %al
	callq	printf
	movl	$0, -4(%rbp)
.LBB1_9:
	movl	-4(%rbp), %eax
	addq	$32, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc
                                        # -- End function
	.type	mails,@object                   # @mails
	.bss
	.globl	mails
	.p2align	2
mails:
	.long	0                               # 0x0
	.size	mails, 4

	.type	mutex,@object                   # @mutex
	.globl	mutex
	.p2align	3
mutex:
	.zero	40
	.size	mutex, 40

	.type	.L.str,@object                  # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"Number of mails %d\n"
	.size	.L.str, 20

	.ident	"Ubuntu clang version 12.0.1-19ubuntu3"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym routine
	.addrsig_sym pthread_mutex_lock
	.addrsig_sym pthread_mutex_unlock
	.addrsig_sym pthread_mutex_init
	.addrsig_sym pthread_create
	.addrsig_sym pthread_join
	.addrsig_sym pthread_mutex_destroy
	.addrsig_sym printf
	.addrsig_sym mails
	.addrsig_sym mutex
