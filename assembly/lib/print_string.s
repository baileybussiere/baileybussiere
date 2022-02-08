section	.text
global	_start

_start:
		mov		rsi, hello
		;;pars: rsi - null-terminated string pos
		xor		rdx, rdx
		mov		rdx, rsi
	nextchar:
		cmp		byte[rdx], 0
		jz		endstring
		inc		rdx
		jmp		nextchar
	endstring:
		sub		rdx, rsi

		mov		rax, 1
		mov		rdi, 1
		syscall
		mov		rax, 60
		xor		rdi, rdi
		syscall

section	.data
	hello:			DB "Hello", 0xA, 0xD, 0
