global _start:
section .text
_start:
		cmp		rax, 1
		je		no_args
		cmp		rax, 2
		jg		too_many_args
		mov		rax, [rsp + 16]
		call		fibonacci
		call 		print
		call		exit
	no_args:
		mov		rax, msg_no_args
		call		print
		call		exit
	too_many_args:
		mov		rax, msg_too_many_args
		call		print
		call		exit
fibonacci:
		cmp		rax, 2
		jl		fibe
		dec		rax
		push		rax
		call		fibonacci
		mov		r8, rax
		pop		rax
		dec		rax
		call		fibonacci
		add		rax, r8
	fibe:
		ret
print:
		mov		rsi, rax
		call		get_length
		mov		rax, 1
		mov		rdi, 1
		syscall
		ret
get_length:
		mov		rdx, rax
	l1s:
		cmp		byte[rdx], 0
		jz		l1e
		inc		rdx
		jmp		l1s
	l1e:
		sub		rdx, rax
		ret
exit:
		mov		rax, 60
		xor		rdi, rdi
		syscall
		ret
section .data
	msg_no_args:
		DB		"fib n returns the nth fibonacci number.", 0xA, 0xD, 0
	msg_too_many_args:
		DB		"fib only takes one argument.", 0xA, 0xD, 0
