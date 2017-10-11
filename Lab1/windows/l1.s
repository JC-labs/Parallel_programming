	.file	"l1.adb"
	.text
	.def	l1___finalizer.4148;	.scl	3;	.type	32;	.endef
	.seh_proc	l1___finalizer.4148
l1___finalizer.4148:
.LFB2:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movq	%r10, -8(%rbp)
	movq	.refptr.system__soft_links__abort_defer(%rip), %rax
	movq	(%rax), %rax
	call	*%rax
	movq	.refptr.system__soft_links__complete_master(%rip), %rax
	movq	(%rax), %rax
	call	*%rax
	movq	.refptr.system__soft_links__abort_undefer(%rip), %rax
	movq	(%rax), %rax
	call	*%rax
	nop
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.def	__enable_execute_stack;	.scl	2;	.type	32;	.endef
	.def	__enable_execute_stack;	.scl	2;	.type	32;	.endef
	.def	__enable_execute_stack;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
	.align 8
.LC0:
	.long	1
	.long	2
	.text
	.globl	_ada_l1
	.def	_ada_l1;	.scl	2;	.type	32;	.endef
	.seh_proc	_ada_l1
_ada_l1:
.LFB1:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%r15
	.seh_pushreg	%r15
	pushq	%r14
	.seh_pushreg	%r14
	pushq	%r13
	.seh_pushreg	%r13
	pushq	%r12
	.seh_pushreg	%r12
	pushq	%rdi
	.seh_pushreg	%rdi
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
.LEHB0:
	subq	$216, %rsp
	.seh_stackalloc	216
	leaq	128(%rsp), %rbp
	.seh_setframe	%rbp, 128
.LEHE0:
	.seh_endprologue
	movq	%rbp, %rax
	addq	$51, %rax
	movq	%rbp, %rdx
	movw	$-17591, (%rax)
	leaq	l1__f1TKB.4762(%rip), %rcx
	movq	%rcx, 2(%rax)
	movw	$-17847, 10(%rax)
	movq	%rdx, 12(%rax)
	movl	$-1864106167, 20(%rax)
	movq	%rax, %rcx
	call	__enable_execute_stack
	movq	%rbp, %rax
	addq	$27, %rax
	movq	%rbp, %rdx
	movw	$-17591, (%rax)
	leaq	l1__f2TKB.4765(%rip), %rcx
	movq	%rcx, 2(%rax)
	movw	$-17847, 10(%rax)
	movq	%rdx, 12(%rax)
	movl	$-1864106167, 20(%rax)
	movq	%rax, %rcx
	call	__enable_execute_stack
	movq	%rbp, %rax
	addq	$3, %rax
	movq	%rbp, %rdx
	movw	$-17591, (%rax)
	leaq	l1__f3TKB.4768(%rip), %rcx
	movq	%rcx, 2(%rax)
	movw	$-17847, 10(%rax)
	movq	%rdx, 12(%rax)
	movl	$-1864106167, 20(%rax)
	movq	%rax, %rcx
	call	__enable_execute_stack
	movq	.refptr.system__soft_links__enter_master(%rip), %rax
	movq	(%rax), %rax
.LEHB1:
	call	*%rax
	movq	.refptr.system__soft_links__current_master(%rip), %rax
	movq	(%rax), %rax
	call	*%rax
	movl	%eax, %edi
	leaq	-16(%rbp), %rax
	movq	%rax, %rcx
	call	system__tasking__activation_chainIP
	movl	$0, %eax
	movb	%al, 2(%rbp)
	leaq	f1T1.4708(%rip), %r14
	leaq	.LC0(%rip), %r15
	movq	%r14, -80(%rbp)
	movq	%r15, -72(%rbp)
	leaq	-80(%rbp), %rcx
	leaq	-16(%rbp), %rdx
	leaq	-32(%rbp), %rax
	movq	%rbp, %r8
	movq	%r8, %r10
	movq	%rcx, %r9
	movq	%rdx, %r8
	movl	%edi, %edx
	movq	%rax, %rcx
	call	l1__f1TKVIP.4698
	movl	$0, %eax
	movb	%al, 1(%rbp)
	leaq	f2T1.4734(%rip), %r12
	leaq	.LC0(%rip), %r13
	movq	%r12, -80(%rbp)
	movq	%r13, -72(%rbp)
	leaq	-80(%rbp), %rcx
	leaq	-16(%rbp), %rdx
	leaq	-48(%rbp), %rax
	movq	%rbp, %r8
	movq	%r8, %r10
	movq	%rcx, %r9
	movq	%rdx, %r8
	movl	%edi, %edx
	movq	%rax, %rcx
	call	l1__f2TKVIP.4724
	movl	$0, %eax
	movb	%al, 0(%rbp)
	leaq	f3T1.4760(%rip), %rbx
	leaq	.LC0(%rip), %rsi
	movq	%rbx, -80(%rbp)
	movq	%rsi, -72(%rbp)
	leaq	-80(%rbp), %rcx
	leaq	-16(%rbp), %rdx
	leaq	-64(%rbp), %rax
	movq	%rbp, %r8
	movq	%r8, %r10
	movq	%rcx, %r9
	movq	%rdx, %r8
	movl	%edi, %edx
	movq	%rax, %rcx
	call	l1__f3TKVIP.4750
	movl	$1, %eax
	movb	%al, 2(%rbp)
	movl	$1, %eax
	movb	%al, 1(%rbp)
	movl	$1, %eax
	movb	%al, 0(%rbp)
	leaq	-16(%rbp), %rax
	movq	%rax, %rcx
	call	system__tasking__stages__activate_tasks
.LEHE1:
	nop
	movl	$0, %ebx
	nop
.L10:
	movq	%rbp, %rax
	movq	%rax, %r10
.LEHB2:
	call	l1___finalizer.4148
.LEHE2:
	cmpl	$1, %ebx
	je	.L6
	movl	$0, %eax
.L12:
	cmpl	$1, %eax
	je	.L8
	jmp	.L15
.L13:
	movq	%rax, -96(%rbp)
	movl	$1, %ebx
	jmp	.L10
.L6:
	movq	-96(%rbp), %rax
	movq	%rax, -88(%rbp)
	jmp	.L11
.L14:
	movq	%rax, -88(%rbp)
.L11:
	movl	$1, %eax
	jmp	.L12
.L8:
	movq	-88(%rbp), %rax
	movq	%rax, %rcx
.LEHB3:
	call	_Unwind_Resume
.L15:
	nop
	addq	$216, %rsp
.LEHE3:
	popq	%rbx
	popq	%rsi
	popq	%rdi
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	ret
	.def	__gnat_personality_seh0;	.scl	2;	.type	32;	.endef
	.seh_handler	__gnat_personality_seh0, @unwind, @except
	.seh_handlerdata
.LLSDA1:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE1-.LLSDACSB1
.LLSDACSB1:
	.uleb128 .LEHB0-.LFB1
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB1-.LFB1
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L13-.LFB1
	.uleb128 0
	.uleb128 .LEHB2-.LFB1
	.uleb128 .LEHE2-.LEHB2
	.uleb128 .L14-.LFB1
	.uleb128 0
	.uleb128 .LEHB3-.LFB1
	.uleb128 .LEHE3-.LEHB3
	.uleb128 0
	.uleb128 0
.LLSDACSE1:
	.text
	.seh_endproc
	.data
	.align 8
.LC3:
	.space 8
	.text
	.def	l1__f1TKVIP.4698;	.scl	3;	.type	32;	.endef
	.seh_proc	l1__f1TKVIP.4698
l1__f1TKVIP.4698:
.LFB3:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%r12
	.seh_pushreg	%r12
	pushq	%rdi
	.seh_pushreg	%rdi
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$176, %rsp
	.seh_stackalloc	176
	.seh_endprologue
	movq	%rcx, 48(%rbp)
	movl	%edx, 56(%rbp)
	movq	%r8, 64(%rbp)
	movq	%r9, %rbx
	movq	(%rbx), %rax
	movq	8(%rbx), %rdx
	movq	%rax, -16(%rbp)
	movq	%rdx, -8(%rbp)
	movq	%r10, %rbx
	movq	%r10, -24(%rbp)
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	movq	-8(%rbp), %rdx
	movl	4(%rdx), %edx
	cmpl	%eax, %edx
	cmpl	%eax, %edx
	jl	.L20
	movslq	%edx, %r8
	movslq	%eax, %rcx
	subq	%rcx, %r8
	movq	%r8, %rcx
	addq	$1, %rcx
	movq	%rcx, %rsi
	movl	$0, %edi
.L20:
	cmpl	%eax, %edx
	movq	48(%rbp), %rax
	movq	$0, (%rax)
	movq	48(%rbp), %rax
	movq	(%rax), %r9
	leaq	2(%rbx), %r8
	movq	48(%rbp), %rcx
	movl	$0, %r11d
	leaq	.LC3(%rip), %r12
	leaq	51(%rbx), %rax
	movq	%rax, %r10
	movq	%r11, -48(%rbp)
	movq	%r12, -40(%rbp)
	movq	-16(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rax, -64(%rbp)
	movq	%rdx, -56(%rbp)
	movq	%r9, 104(%rsp)
	leaq	-64(%rbp), %rax
	movq	%rax, 96(%rsp)
	movq	64(%rbp), %rax
	movq	%rax, 88(%rsp)
	movq	%r8, 80(%rsp)
	movq	%rcx, 72(%rsp)
	movq	%r10, 64(%rsp)
	movl	56(%rbp), %eax
	movl	%eax, 56(%rsp)
	movl	$0, 48(%rsp)
	leaq	-48(%rbp), %rax
	movq	%rax, 40(%rsp)
	movq	$0, 32(%rsp)
	movl	$-1, %r9d
	movl	$0, %r8d
	movl	$-2147483648, %edx
	movl	$-1, %ecx
	call	system__tasking__stages__create_task
	movq	%rax, %rdx
	movq	48(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	addq	$176, %rsp
	popq	%rbx
	popq	%rsi
	popq	%rdi
	popq	%r12
	popq	%rbp
	ret
	.seh_endproc
	.def	l1__f2TKVIP.4724;	.scl	3;	.type	32;	.endef
	.seh_proc	l1__f2TKVIP.4724
l1__f2TKVIP.4724:
.LFB4:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%r12
	.seh_pushreg	%r12
	pushq	%rdi
	.seh_pushreg	%rdi
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$176, %rsp
	.seh_stackalloc	176
	.seh_endprologue
	movq	%rcx, 48(%rbp)
	movl	%edx, 56(%rbp)
	movq	%r8, 64(%rbp)
	movq	%r9, %rbx
	movq	(%rbx), %rax
	movq	8(%rbx), %rdx
	movq	%rax, -16(%rbp)
	movq	%rdx, -8(%rbp)
	movq	%r10, %rbx
	movq	%r10, -24(%rbp)
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	movq	-8(%rbp), %rdx
	movl	4(%rdx), %edx
	cmpl	%eax, %edx
	cmpl	%eax, %edx
	jl	.L28
	movslq	%edx, %r8
	movslq	%eax, %rcx
	subq	%rcx, %r8
	movq	%r8, %rcx
	addq	$1, %rcx
	movq	%rcx, %rsi
	movl	$0, %edi
.L28:
	cmpl	%eax, %edx
	movq	48(%rbp), %rax
	movq	$0, (%rax)
	movq	48(%rbp), %rax
	movq	(%rax), %r9
	leaq	1(%rbx), %r8
	movq	48(%rbp), %rcx
	movl	$0, %r11d
	leaq	.LC3(%rip), %r12
	leaq	27(%rbx), %rax
	movq	%rax, %r10
	movq	%r11, -48(%rbp)
	movq	%r12, -40(%rbp)
	movq	-16(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rax, -64(%rbp)
	movq	%rdx, -56(%rbp)
	movq	%r9, 104(%rsp)
	leaq	-64(%rbp), %rax
	movq	%rax, 96(%rsp)
	movq	64(%rbp), %rax
	movq	%rax, 88(%rsp)
	movq	%r8, 80(%rsp)
	movq	%rcx, 72(%rsp)
	movq	%r10, 64(%rsp)
	movl	56(%rbp), %eax
	movl	%eax, 56(%rsp)
	movl	$0, 48(%rsp)
	leaq	-48(%rbp), %rax
	movq	%rax, 40(%rsp)
	movq	$0, 32(%rsp)
	movl	$-1, %r9d
	movl	$0, %r8d
	movl	$-2147483648, %edx
	movl	$-1, %ecx
	call	system__tasking__stages__create_task
	movq	%rax, %rdx
	movq	48(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	addq	$176, %rsp
	popq	%rbx
	popq	%rsi
	popq	%rdi
	popq	%r12
	popq	%rbp
	ret
	.seh_endproc
	.def	l1__f3TKVIP.4750;	.scl	3;	.type	32;	.endef
	.seh_proc	l1__f3TKVIP.4750
l1__f3TKVIP.4750:
.LFB5:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%r12
	.seh_pushreg	%r12
	pushq	%rdi
	.seh_pushreg	%rdi
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$176, %rsp
	.seh_stackalloc	176
	.seh_endprologue
	movq	%rcx, 48(%rbp)
	movl	%edx, 56(%rbp)
	movq	%r8, 64(%rbp)
	movq	%r9, %rbx
	movq	(%rbx), %rax
	movq	8(%rbx), %rdx
	movq	%rax, -16(%rbp)
	movq	%rdx, -8(%rbp)
	movq	%r10, %r9
	movq	%r10, -24(%rbp)
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	movq	-8(%rbp), %rdx
	movl	4(%rdx), %edx
	cmpl	%eax, %edx
	cmpl	%eax, %edx
	jl	.L36
	movslq	%edx, %r8
	movslq	%eax, %rcx
	subq	%rcx, %r8
	movq	%r8, %rcx
	addq	$1, %rcx
	movq	%rcx, %rsi
	movl	$0, %edi
.L36:
	cmpl	%eax, %edx
	movq	48(%rbp), %rax
	movq	$0, (%rax)
	movq	48(%rbp), %rax
	movq	(%rax), %r8
	movq	%r9, %r10
	movq	48(%rbp), %rcx
	movl	$0, %r11d
	leaq	.LC3(%rip), %r12
	leaq	3(%r9), %rax
	movq	%rax, %r9
	movq	%r11, -48(%rbp)
	movq	%r12, -40(%rbp)
	movq	-16(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rax, -64(%rbp)
	movq	%rdx, -56(%rbp)
	movq	%r8, 104(%rsp)
	leaq	-64(%rbp), %rax
	movq	%rax, 96(%rsp)
	movq	64(%rbp), %rax
	movq	%rax, 88(%rsp)
	movq	%r10, 80(%rsp)
	movq	%rcx, 72(%rsp)
	movq	%r9, 64(%rsp)
	movl	56(%rbp), %eax
	movl	%eax, 56(%rsp)
	movl	$0, 48(%rsp)
	leaq	-48(%rbp), %rax
	movq	%rax, 40(%rsp)
	movq	$0, 32(%rsp)
	movl	$-1, %r9d
	movl	$0, %r8d
	movl	$-2147483648, %edx
	movl	$-1, %ecx
	call	system__tasking__stages__create_task
	movq	%rax, %rdx
	movq	48(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	addq	$176, %rsp
	popq	%rbx
	popq	%rsi
	popq	%rdi
	popq	%r12
	popq	%rbp
	ret
	.seh_endproc
	.def	l1__f1TK___finalizer.4804;	.scl	3;	.type	32;	.endef
	.seh_proc	l1__f1TK___finalizer.4804
l1__f1TK___finalizer.4804:
.LFB7:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movq	%r10, -8(%rbp)
	movq	.refptr.system__soft_links__abort_defer(%rip), %rax
	movq	(%rax), %rax
	call	*%rax
	call	system__tasking__stages__complete_task
	movq	.refptr.system__soft_links__abort_undefer(%rip), %rax
	movq	(%rax), %rax
	call	*%rax
	nop
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC4:
	.ascii "Task #1 was initialized."
.LC5:
	.ascii "Task #1 was finished."
	.align 8
.LC1:
	.long	1
	.long	24
	.align 8
.LC2:
	.long	1
	.long	21
	.text
	.def	l1__f1TKB.4762;	.scl	3;	.type	32;	.endef
	.seh_proc	l1__f1TKB.4762
l1__f1TKB.4762:
.LFB6:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%r13
	.seh_pushreg	%r13
	pushq	%r12
	.seh_pushreg	%r12
	pushq	%rdi
	.seh_pushreg	%rdi
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
.LEHB4:
	subq	$72, %rsp
	.seh_stackalloc	72
	leaq	128(%rsp), %rbp
	.seh_setframe	%rbp, 128
.LEHE4:
	.seh_endprologue
	movq	%rcx, 0(%rbp)
	movq	%r10, -72(%rbp)
	movq	.refptr.system__soft_links__abort_undefer(%rip), %rax
	movq	(%rax), %rax
.LEHB5:
	call	*%rax
	call	system__tasking__stages__complete_activation
	leaq	.LC4(%rip), %r12
	leaq	.LC1(%rip), %r13
	movq	%r12, -96(%rbp)
	movq	%r13, -88(%rbp)
	leaq	-96(%rbp), %rax
	movq	%rax, %rcx
	call	ada__text_io__put_line__2
	leaq	.LC5(%rip), %rbx
	leaq	.LC2(%rip), %rsi
	movq	%rbx, -96(%rbp)
	movq	%rsi, -88(%rbp)
	leaq	-96(%rbp), %rax
	movq	%rax, %rcx
	call	ada__text_io__put_line__2
.LEHE5:
	movl	$0, %ebx
	nop
.L46:
	leaq	-64(%rbp), %r10
.LEHB6:
	call	l1__f1TK___finalizer.4804
	cmpl	$1, %ebx
	je	.L44
	jmp	.L48
.L47:
	movq	%rax, %rdi
	movl	$1, %ebx
	jmp	.L46
.L44:
	movq	%rdi, %rax
	movq	%rax, %rcx
	call	_Unwind_Resume
.L48:
	nop
	addq	$72, %rsp
.LEHE6:
	popq	%rbx
	popq	%rsi
	popq	%rdi
	popq	%r12
	popq	%r13
	popq	%rbp
	ret
	.seh_handler	__gnat_personality_seh0, @unwind, @except
	.seh_handlerdata
.LLSDA6:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE6-.LLSDACSB6
.LLSDACSB6:
	.uleb128 .LEHB4-.LFB6
	.uleb128 .LEHE4-.LEHB4
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB5-.LFB6
	.uleb128 .LEHE5-.LEHB5
	.uleb128 .L47-.LFB6
	.uleb128 0
	.uleb128 .LEHB6-.LFB6
	.uleb128 .LEHE6-.LEHB6
	.uleb128 0
	.uleb128 0
.LLSDACSE6:
	.text
	.seh_endproc
	.def	l1__f2TK___finalizer.4817;	.scl	3;	.type	32;	.endef
	.seh_proc	l1__f2TK___finalizer.4817
l1__f2TK___finalizer.4817:
.LFB9:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movq	%r10, -8(%rbp)
	movq	.refptr.system__soft_links__abort_defer(%rip), %rax
	movq	(%rax), %rax
	call	*%rax
	call	system__tasking__stages__complete_task
	movq	.refptr.system__soft_links__abort_undefer(%rip), %rax
	movq	(%rax), %rax
	call	*%rax
	nop
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC6:
	.ascii "Task #2 was initialized."
.LC7:
	.ascii "Task #2 was finished."
	.text
	.def	l1__f2TKB.4765;	.scl	3;	.type	32;	.endef
	.seh_proc	l1__f2TKB.4765
l1__f2TKB.4765:
.LFB8:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%r13
	.seh_pushreg	%r13
	pushq	%r12
	.seh_pushreg	%r12
	pushq	%rdi
	.seh_pushreg	%rdi
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
.LEHB7:
	subq	$72, %rsp
	.seh_stackalloc	72
	leaq	128(%rsp), %rbp
	.seh_setframe	%rbp, 128
.LEHE7:
	.seh_endprologue
	movq	%rcx, 0(%rbp)
	movq	%r10, -72(%rbp)
	movq	.refptr.system__soft_links__abort_undefer(%rip), %rax
	movq	(%rax), %rax
.LEHB8:
	call	*%rax
	call	system__tasking__stages__complete_activation
	leaq	.LC6(%rip), %r12
	leaq	.LC1(%rip), %r13
	movq	%r12, -96(%rbp)
	movq	%r13, -88(%rbp)
	leaq	-96(%rbp), %rax
	movq	%rax, %rcx
	call	ada__text_io__put_line__2
	leaq	.LC7(%rip), %rbx
	leaq	.LC2(%rip), %rsi
	movq	%rbx, -96(%rbp)
	movq	%rsi, -88(%rbp)
	leaq	-96(%rbp), %rax
	movq	%rax, %rcx
	call	ada__text_io__put_line__2
.LEHE8:
	movl	$0, %ebx
	nop
.L55:
	leaq	-64(%rbp), %r10
.LEHB9:
	call	l1__f2TK___finalizer.4817
	cmpl	$1, %ebx
	je	.L53
	jmp	.L57
.L56:
	movq	%rax, %rdi
	movl	$1, %ebx
	jmp	.L55
.L53:
	movq	%rdi, %rax
	movq	%rax, %rcx
	call	_Unwind_Resume
.L57:
	nop
	addq	$72, %rsp
.LEHE9:
	popq	%rbx
	popq	%rsi
	popq	%rdi
	popq	%r12
	popq	%r13
	popq	%rbp
	ret
	.seh_handler	__gnat_personality_seh0, @unwind, @except
	.seh_handlerdata
.LLSDA8:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE8-.LLSDACSB8
.LLSDACSB8:
	.uleb128 .LEHB7-.LFB8
	.uleb128 .LEHE7-.LEHB7
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB8-.LFB8
	.uleb128 .LEHE8-.LEHB8
	.uleb128 .L56-.LFB8
	.uleb128 0
	.uleb128 .LEHB9-.LFB8
	.uleb128 .LEHE9-.LEHB9
	.uleb128 0
	.uleb128 0
.LLSDACSE8:
	.text
	.seh_endproc
	.def	l1__f3TK___finalizer.4823;	.scl	3;	.type	32;	.endef
	.seh_proc	l1__f3TK___finalizer.4823
l1__f3TK___finalizer.4823:
.LFB11:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movq	%r10, -8(%rbp)
	movq	.refptr.system__soft_links__abort_defer(%rip), %rax
	movq	(%rax), %rax
	call	*%rax
	call	system__tasking__stages__complete_task
	movq	.refptr.system__soft_links__abort_undefer(%rip), %rax
	movq	(%rax), %rax
	call	*%rax
	nop
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC8:
	.ascii "Task #3 was initialized."
.LC9:
	.ascii "Task #3 was finished."
	.text
	.def	l1__f3TKB.4768;	.scl	3;	.type	32;	.endef
	.seh_proc	l1__f3TKB.4768
l1__f3TKB.4768:
.LFB10:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%r13
	.seh_pushreg	%r13
	pushq	%r12
	.seh_pushreg	%r12
	pushq	%rdi
	.seh_pushreg	%rdi
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
.LEHB10:
	subq	$72, %rsp
	.seh_stackalloc	72
	leaq	128(%rsp), %rbp
	.seh_setframe	%rbp, 128
.LEHE10:
	.seh_endprologue
	movq	%rcx, 0(%rbp)
	movq	%r10, -72(%rbp)
	movq	.refptr.system__soft_links__abort_undefer(%rip), %rax
	movq	(%rax), %rax
.LEHB11:
	call	*%rax
	call	system__tasking__stages__complete_activation
	leaq	.LC8(%rip), %r12
	leaq	.LC1(%rip), %r13
	movq	%r12, -96(%rbp)
	movq	%r13, -88(%rbp)
	leaq	-96(%rbp), %rax
	movq	%rax, %rcx
	call	ada__text_io__put_line__2
	leaq	.LC9(%rip), %rbx
	leaq	.LC2(%rip), %rsi
	movq	%rbx, -96(%rbp)
	movq	%rsi, -88(%rbp)
	leaq	-96(%rbp), %rax
	movq	%rax, %rcx
	call	ada__text_io__put_line__2
.LEHE11:
	movl	$0, %ebx
	nop
.L64:
	leaq	-64(%rbp), %r10
.LEHB12:
	call	l1__f3TK___finalizer.4823
	cmpl	$1, %ebx
	je	.L62
	jmp	.L66
.L65:
	movq	%rax, %rdi
	movl	$1, %ebx
	jmp	.L64
.L62:
	movq	%rdi, %rax
	movq	%rax, %rcx
	call	_Unwind_Resume
.L66:
	nop
	addq	$72, %rsp
.LEHE12:
	popq	%rbx
	popq	%rsi
	popq	%rdi
	popq	%r12
	popq	%r13
	popq	%rbp
	ret
	.seh_handler	__gnat_personality_seh0, @unwind, @except
	.seh_handlerdata
.LLSDA10:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE10-.LLSDACSB10
.LLSDACSB10:
	.uleb128 .LEHB10-.LFB10
	.uleb128 .LEHE10-.LEHB10
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB11-.LFB10
	.uleb128 .LEHE11-.LEHB11
	.uleb128 .L65-.LFB10
	.uleb128 0
	.uleb128 .LEHB12-.LFB10
	.uleb128 .LEHE12-.LEHB12
	.uleb128 0
	.uleb128 0
.LLSDACSE10:
	.text
	.seh_endproc
	.section .rdata,"dr"
	.align 2
f1T1.4708:
	.ascii "f1"
	.align 2
f2T1.4734:
	.ascii "f2"
	.align 2
f3T1.4760:
	.ascii "f3"
	.ident	"GCC: (tdm64-1) 5.1.0"
	.def	system__tasking__activation_chainIP;	.scl	2;	.type	32;	.endef
	.def	system__tasking__stages__activate_tasks;	.scl	2;	.type	32;	.endef
	.def	_Unwind_Resume;	.scl	2;	.type	32;	.endef
	.def	system__tasking__stages__create_task;	.scl	2;	.type	32;	.endef
	.def	system__tasking__stages__complete_task;	.scl	2;	.type	32;	.endef
	.def	system__tasking__stages__complete_activation;	.scl	2;	.type	32;	.endef
	.def	ada__text_io__put_line__2;	.scl	2;	.type	32;	.endef
	.section	.rdata$.refptr.system__soft_links__current_master, "dr"
	.globl	.refptr.system__soft_links__current_master
	.linkonce	discard
.refptr.system__soft_links__current_master:
	.quad	system__soft_links__current_master
	.section	.rdata$.refptr.system__soft_links__enter_master, "dr"
	.globl	.refptr.system__soft_links__enter_master
	.linkonce	discard
.refptr.system__soft_links__enter_master:
	.quad	system__soft_links__enter_master
	.section	.rdata$.refptr.system__soft_links__abort_undefer, "dr"
	.globl	.refptr.system__soft_links__abort_undefer
	.linkonce	discard
.refptr.system__soft_links__abort_undefer:
	.quad	system__soft_links__abort_undefer
	.section	.rdata$.refptr.system__soft_links__complete_master, "dr"
	.globl	.refptr.system__soft_links__complete_master
	.linkonce	discard
.refptr.system__soft_links__complete_master:
	.quad	system__soft_links__complete_master
	.section	.rdata$.refptr.system__soft_links__abort_defer, "dr"
	.globl	.refptr.system__soft_links__abort_defer
	.linkonce	discard
.refptr.system__soft_links__abort_defer:
	.quad	system__soft_links__abort_defer
