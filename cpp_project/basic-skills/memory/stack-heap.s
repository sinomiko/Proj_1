	.file	"stack-heap.cpp"
	.intel_syntax noprefix
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.globl	g_int1
	.data
	.align 4
	.type	g_int1, @object
	.size	g_int1, 4
g_int1:
	.long	10
	.globl	g_int2
	.align 4
	.type	g_int2, @object
	.size	g_int2, 4
g_int2:
	.long	9
	.globl	g_char
	.type	g_char, @object
	.size	g_char, 1
g_char:
	.byte	97
	.text
	.globl	main
	.type	main, @function
main:
.LFB969:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA969
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 80
	mov	DWORD PTR [rbp-68], edi
	mov	QWORD PTR [rbp-80], rsi
	mov	DWORD PTR [rbp-64], 1
	mov	DWORD PTR [rbp-60], 2
	mov	DWORD PTR [rbp-56], 3
	mov	DWORD PTR [rbp-52], 4
	mov	DWORD PTR [rbp-48], 5
	mov	DWORD PTR [rbp-44], 6
	mov	DWORD PTR [rbp-40], 7
	mov	DWORD PTR [rbp-36], 8
	mov	DWORD PTR [rbp-32], 9
	mov	DWORD PTR [rbp-28], 10
	lea	rax, [rbp-64]
	add	rax, 20
	mov	QWORD PTR [rbp-8], rax
	mov	rax, QWORD PTR [rbp-8]
	mov	DWORD PTR [rax], 100
	mov	edi, 4
.LEHB0:
	call	_Znwm
	mov	DWORD PTR [rax], 2
	mov	QWORD PTR [rbp-16], rax
	mov	edi, 4
	call	_Znwm
.LEHE0:
	mov	DWORD PTR [rax], 2
	mov	QWORD PTR [rbp-24], rax
	mov	rax, QWORD PTR [rbp-16]
	mov	rdi, rax
	call	_ZdlPv
	mov	eax, 0
	jmp	.L5
.L4:
	mov	rdi, rax
.LEHB1:
	call	_Unwind_Resume
.LEHE1:
.L5:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE969:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA969:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE969-.LLSDACSB969
.LLSDACSB969:
	.uleb128 .LEHB0-.LFB969
	.uleb128 .LEHE0-.LEHB0
	.uleb128 .L4-.LFB969
	.uleb128 0
	.uleb128 .LEHB1-.LFB969
	.uleb128 .LEHE1-.LEHB1
	.uleb128 0
	.uleb128 0
.LLSDACSE969:
	.text
	.size	main, .-main
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB970:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	DWORD PTR [rbp-4], edi
	mov	DWORD PTR [rbp-8], esi
	cmp	DWORD PTR [rbp-4], 1
	jne	.L6
	cmp	DWORD PTR [rbp-8], 65535
	jne	.L6
	mov	edi, OFFSET FLAT:_ZStL8__ioinit
	call	_ZNSt8ios_base4InitC1Ev
	mov	edx, OFFSET FLAT:__dso_handle
	mov	esi, OFFSET FLAT:_ZStL8__ioinit
	mov	edi, OFFSET FLAT:_ZNSt8ios_base4InitD1Ev
	call	__cxa_atexit
.L6:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE970:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.type	_GLOBAL__sub_I_g_int1, @function
_GLOBAL__sub_I_g_int1:
.LFB971:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	esi, 65535
	mov	edi, 1
	call	_Z41__static_initialization_and_destruction_0ii
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE971:
	.size	_GLOBAL__sub_I_g_int1, .-_GLOBAL__sub_I_g_int1
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I_g_int1
	.hidden	__dso_handle
	.ident	"GCC: (GNU) 4.8.2 20140120 (Red Hat 4.8.2-15)"
	.section	.note.GNU-stack,"",@progbits
