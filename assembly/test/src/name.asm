global _start
section .data
	endl		DB 0xA, 0xD
	prompt		DB "What is your name?", endl
	response	DB "Your name is "
section .bss
	name		RESB 255
section .text
	_start:
		mov		rax, prompt
		call		print_rax
		call		exit

print_rax:
		mov		rsi, rax
		mov		rax, prompt
		;call		len_rax
		mov		rdx, 10
		mov		rax, 1
		mov		rdi, 1
		syscall
		ret

len_rax:
		mov		rbx, rax
	nextchar:
		cmp		byte [rax], 0
		jz		end_of_string
		inc		rax
		jmp		nextchar
	end_of_string:
		sub		rax, rbx
		ret

exit:
		mov		rax, 60
		mov		rdi, 0
		syscall
		ret
