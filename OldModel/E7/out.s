# FIXED INIT
.text
.section .rodata
printintstr: .string "%d\n"
printfloatstr: .string "%f\n"
printcharstr: .string "%c\n"
printstringstr: .string "%s\n"
.text
	# BEGIN_FUN
	.globl	func
	.type	func, @function
func:
	pushq	%rbp
	movq	%rsp, %rbp
	movl	%edi, _a(%rip)
	movl	%esi, _b(%rip)
	movl	%edx, _c(%rip)
# TAC_ADD
	movl	_a(%rip), %edx
	movl	_b(%rip), %eax
	addl	%edx, %eax
	movl	%eax, _______Temp_____var_0(%rip)
# TAC_ADD
	movl	_______Temp_____var_0(%rip), %edx
	movl	_c(%rip), %eax
	addl	%edx, %eax
	movl	%eax, _______Temp_____var_1(%rip)
# TAC_RET
	movl	_______Temp_____var_1(%rip), %eax
	popq	%rbp
	ret
	# TAC_ENDFUN
	popq	%rbp
	ret
	# BEGIN_FUN
	.globl	func_real
	.type	func_real, @function
func_real:
	pushq	%rbp
	movq	%rsp, %rbp
	movl	%edi, _r1(%rip)
	movl	%esi, _r2(%rip)
	movss	_r1(%rip), %xmm0
	addss	_r2(%rip), %xmm0
	movss	%xmm0, _______Temp_____var_2(%rip)
# TAC_RET
	movss	_______Temp_____var_2(%rip), %xmm0
	popq	%rbp
	ret
	# TAC_ENDFUN
	popq	%rbp
	ret
	# BEGIN_FUN
	.globl	main
	.type	main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
# TAC_ARG
# TAC_ARG
# TAC_CALL func_real
	movl	_real1(%rip), %edi
	movl	_real2(%rip), %esi
	call	func_real
	movl	%eax, _______Temp_____var_3(%rip)
# TAC PRINT
# PRINT RETORNO DE FUNCAO func_real
	cvtps2pd	%xmm0, %xmm0
	leaq	printfloatstr(%rip), %rdi
	movl	$1, %eax
	call	printf@PLT
# TAC_ARG
# TAC_ARG
# TAC_ARG
# TAC_CALL func
	movl	_arg1(%rip), %edi
	movl	_arg2(%rip), %esi
	movl	_arg3(%rip), %edx
	call	func
	movl	%eax, _______Temp_____var_4(%rip)
# TAC PRINT
# PRINT RETORNO DE FUNCAO func
	movl	%eax, %esi
	leaq	printintstr(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
# TAC_ARG
# TAC_ARG
# TAC_ARG
# TAC_CALL func
	movl	_arg1(%rip), %edi
	movl	_arg2(%rip), %esi
	movl	_arg3(%rip), %edx
	call	func
	movl	%eax, _______Temp_____var_5(%rip)
# TAC COPY x = ______Temp_____var_5
	movl	_______Temp_____var_5(%rip), %eax
	movl	%eax, _x(%rip)
# TAC PRINT
	movl	_x(%rip), %esi
	leaq	printintstr(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax;
# TAC_VET_LOAD
	movl	_x(%rip), %eax
	leaq	_vet2(%rip), %rdi
	movl	(%rdi,%rax,4), %edx
	movl	%edx, _______Temp_____var_6(%rip)
# TAC PRINT
# PRINT VETOR vet2[x]
	movl	_x(%rip), %eax
	leaq	_vet2(%rip), %rdi
	movl	(%rdi,%rax,4), %esi
	leaq	printintstr(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
# TAC_ARG
# TAC_ARG
# TAC_ARG
# TAC_CALL func
	movl	_arg1(%rip), %edi
	movl	_arg2(%rip), %esi
	movl	_arg3(%rip), %edx
	call	func
	movl	%eax, _______Temp_____var_7(%rip)
# TAC_VET_LOAD
	movl	_______Temp_____var_7(%rip), %eax
	leaq	_vet2(%rip), %rdi
	movl	(%rdi,%rax,4), %edx
	movl	%edx, _______Temp_____var_8(%rip)
# TAC PRINT
# PRINT VETOR vet2[______Temp_____var_7]
	movl	_______Temp_____var_7(%rip), %eax
	leaq	_vet2(%rip), %rdi
	movl	(%rdi,%rax,4), %esi
	leaq	printintstr(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
# TAC_RET
	movl	__0(%rip), %eax
	popq	%rbp
	ret
	# TAC_ENDFUN
	popq	%rbp
	ret
.section .data
# DATA SECTION
.globl __char_d
__char_d:	.byte	'd'
.globl __0
__0:	.long	0
.globl __01
__01:	.long	10
.globl __1
__1:	.long	1
.globl __1barra2
__1barra2:	.float	0.5
.globl __1234123barra12
__1234123barra12:	.float	102843.585938
.globl __1324
__1324:	.long	4231
.globl __2
__2:	.long	2
.globl __3
__3:	.long	3
.globl __3barra5
__3barra5:	.float	0.6
.globl __323
__323:	.long	323
.globl __4
__4:	.long	4
.globl __5
__5:	.long	5
.globl _______Temp_____var_0
_______Temp_____var_0:	.long	0
.globl _______Temp_____var_1
_______Temp_____var_1:	.long	0
.globl _______Temp_____var_2
_______Temp_____var_2:	.long	0
.globl _______Temp_____var_3
_______Temp_____var_3:	.long	0
.globl _______Temp_____var_4
_______Temp_____var_4:	.long	0
.globl _______Temp_____var_5
_______Temp_____var_5:	.long	0
.globl _______Temp_____var_6
_______Temp_____var_6:	.long	0
.globl _______Temp_____var_7
_______Temp_____var_7:	.long	0
.globl _______Temp_____var_8
_______Temp_____var_8:	.long	0
.globl _a
_a:	.long	0	# Parâmetro da função
.globl _arg1
_arg1:	.long	1
.globl _arg2
_arg2:	.long	2
.globl _arg3
_arg3:	.long	1
.globl _b
_b:	.long	0	# Parâmetro da função
.globl _c
_c:	.long	0	# Parâmetro da função
.globl _func
_func:	.long	0	# Função retorna inteiro
.globl _func_real
_func_real:	.long	0	# Função retorna inteiro
.globl _main
_main:	.long	0
.globl _r1
_r1:	.float	0.0	# Parâmetro float da função
.globl _r2
_r2:	.float	0.0	# Parâmetro float da função
.globl _real1
_real1:	.float	0.500000
.globl _real2
_real2:	.float	0.600000
.globl _realzin
_realzin:	.float	102843.585938
.globl _vet1
_vet1:	.long 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
.globl _vet2
_vet2:	.long 1, 2, 3, 4, 5
.globl _w
_w:	.long	3
.globl _x
_x:	.long	4231
.globl _x1
_x1:	.long	'd'
.globl _y
_y:	.long	323
.globl _z
_z:	.long	0
