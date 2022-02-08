global _start
section .data
	endl:			DB 0xA, 0xD
	numprompt:		DB "Enter a number:", 0xA, 0xD
	numprompt_len:	EQU 17 ;$-numprompt
section .bss
	input:			RESB 255
	number:			RESW 1
section .text
	_start:
	call	 	promptfornum
	call		getnum
	mov		rax, [number]
	call		getnum
	mov		rbx, [number]

	sub		rax, rbx
	add		rax, 48

	mov		rcx, rax
	mov		rdi, 1
	mov		rax, 4
	syscall

	mov		rax, 1
	mov		rdi, 0
	syscall

promptfornum:
	push		rbx
	push		rax
	mov		rax, numprompt
	mov		rdx, numprompt_len
	call		print_rax_len_rbx
	pop		rax
	pop		rbx

print_rax_len_rdx:
	push		rdx
	push		rcx
	mov		ecx, eax
	mov		edx, ebx
	push		rbx
	push		rax
	mov		eax, 4
	mov		ebx, 1
	int		0x80
	pop		rax
	pop		rbx
	pop		rcx
	pop		rdx
	ret

getnum:
	push		rdx
	push		rax
	mov		rax, 0
	mov		rdi, 0
	mov		rsi, input
	mov		rdx, 255
	syscall
	mov		rax, input
	call		eax_to_number
	pop		rax
	pop		rdx
	ret

eax_string_to_number:
	push		rbx
	push		rcx
	push		rdx
	mov		ebx, eax
	begin:
		cmp		byte [ebx], 0
		jz		over
		push		rax
		mov		eax, [number]
		mov		edx, 10
		mul		edx
		mov		[number], eax
		mov		cl, [ebx]
		sub		cl, 48
		mov		edx, [number]
		add		edx, ecx
		mov		[number], edx
		pop		rax
		inc		ebx
		jmp		begin
	over:
		pop		rdx
		pop		rcx
		pop		rbx
	ret
