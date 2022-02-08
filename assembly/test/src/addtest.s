global _start
section .text
_start:
		mov		rbx, string
		lea		rax, [rbx+3]
		mov		rcx, 1
		call		print
		mov		rax, 60
		xor		rdi, rdi
		syscall
print:
		mov		rsi, rax
		mov		rdx, rcx
		mov		rax, 1
		mov		rdi, 1
		syscall
		ret
section .data
	string:
			DB "abcdefghijklmnopqrstuvwxyz"
	endl:
			DB 0xA, 0xD
section .bss