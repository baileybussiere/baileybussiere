global _start
section .data
	endl:			DB 0xA, 0xD, 0
	mesg:			DB "Enter an integer:", 0xA, 0xD, 0
	sum_mesg:		DB "Their sum is: ", 0
	overflow_mesg:
				DB "Too large an argument.", 0xA, 0xD, 0
section .bss
	input:		RESB 255
	output:		RESB 255
section .text
	_start:
		mov 		rax, mesg
		call		print
		call		get_input
		call		string_to_int
		push		rax
		mov		rax, mesg
		call		print
		call		get_input
		call		string_to_int
		mov		rbx, rax
		mov		rax, sum_mesg
		call		print
		pop		rax
		add		rax, rbx
		call		int_to_string
		call		print
		mov		rax, endl
		call		print
		call		exit_program
overflow_warning:
		mov		rax, overflow_mesg
		call		print
		jmp		_start

int_to_string:
		xor		rdx, rdx
		lea		rbx, [output + 254]
		mov		[rbx], rdx
		mov		rcx, 10
	loop_start:
		xor		rdx, rdx
		idiv		rcx
		add		rdx, 48
		dec		rbx
		mov		byte [rbx], dl
		test		rax, rax
		jnz		loop_start
		mov		rax, rbx
		ret

string_to_int:
		clc
		mov		rdx, rax
		xor		rax, rax
	nextdigit:
		movzx		rcx, byte [rdx]
		cmp		rcx, 48
		jb		end
		cmp		rcx, 57
		ja		end
		imul		rax, 10
		sub		rcx, 48
		add		rax, rcx
		jc		overflow_warning
		inc		rdx
		jmp		nextdigit
	end:
		ret

get_input:
		xor		rax, rax
		xor		rdi, rdi
		mov		rsi, input
		mov		rdx, 255
		syscall
		mov		rax, input
		ret

print:
		mov		rsi, rax
		call		get_len
		mov		rdx, rax
		mov		rax, 1
		mov		rdi, 1
		syscall
		mov		rax, rsi
		ret

get_len:
		mov		rdx, rax
	nextchar:
		cmp		byte [rax], 0
		jz		end_of_string
		inc		rax
		jmp		nextchar
	end_of_string:
		sub		rax, rdx
		ret

exit_program:
		mov		rax, 60
		xor		rdi, rdi
		syscall
		ret