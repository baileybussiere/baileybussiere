global _start:
section .text
_start:
		cmp		rax, 1
		je		err_no_args
		cmp		rax, 3
		jg		err_too_many_args
		mov		rsi, O_CREAT
		and		rsi, O_WRONLY
		je		spec_output
		mov		rax, [rsp + bc*2]
		call		app_out_ext
		mov		rax, testfile_name
		call		open_file
		jmp		end_spec_output
	spec_output:
		mov		rax, [rsp + bc*3]
		call		open_file
	end_spec_output:
		cmp		ecx, -1
		je		err_file_create
		mov		r13, rax
		mov		rax, [rsp + bc*2]
		mov		rsi, O_RDONLY
		call		open_file
		mov		r12, rax
		call		read_file
		mov		rdi, r13
		call		write
		mov		rax, r12
		call		close_file
		mov		rax, r13
		call		close_file
		call		exit
	err_no_args:
		mov		rax, msg_no_args
		call		print
		call		exit
	err_too_many_args:
		mov		rax, msg_too_many_args
		call		print
		call		exit
	err_file_create:
		mov		rax, msg_err_create
		call		print
		call		exit
	err_file_read:
		mov		rax, msg_err_read
		call		print
		call		exit
	made_it:
		mov		rax, msg_made_it
		call		print
		call		exit

write:						;args: rax - char* to write, rdi - filenumber to write to; returns: ?
		mov		rsi, rax
		call		get_length
		mov		rdx, rax
		mov		rax, 1
		syscall
		ret

close_file:					;args: rax - filenumber (from sys_open): returns: nothing?
		mov		rdi, rax
		mov		rax, 3
		syscall
		ret

read_file:					;args: rax - filenumber (from sys_open); returns: rax - file contents.
		mov		rdi, rax
		xor		rax, rax
		mov		rsi, buffer
		mov		rdx, 255
		syscall
		mov		rax, rsi
		ret

open_file:					;args: rax - filename; returns: rax - filenumber
		mov		rdi, rax
		mov		rax, 2
		mov		rdx, 0666o
		syscall
		ret

app_out_ext:
		call		copy_to_buff
		mov		byte [rax + rcx - 1], '.'
		mov		byte [rax + rcx], 'o'
		mov		byte [rax + rcx + 1], 0
		ret

copy_to_buff:
		xor		rcx, rcx
		mov		rdx, buffer
	loop3:
		movzx		rdx, byte [rax + rcx]
		mov		[buffer + rcx], rdx
		inc		rcx
		cmp		byte [rax + rcx - 1], 0
		jne		loop3
		mov		rax, buffer
		ret

int_to_string:
		xor		rdx, rdx
		lea		rcx, [buffer+254]
		mov		[rcx], rdx
		mov		r8, 10
	loop2:
		xor		rdx, rdx
		idiv		r8
		add		rdx, '0'
		dec		rcx
		mov		[rcx], dl
		test		rax, rax
		jnz		loop2
		mov		rax, rcx
		ret

print:						;args: rax - char* to print; returns: ?
		mov		rsi, rax
		call		get_length
		mov		rdx, rax
		mov		rax, 1
		mov		rdi, 1
		syscall
		mov		rax, rsi
		ret

get_length:
		mov		rdx, rax
	loop1_s:
		cmp		byte[rax], 0
		jz		loop1_e
		inc		rax
		jmp		loop1_s
	loop1_e:
		sub		rax, rdx
		ret

exit:
		mov		rax, 60
		xor		rdi, rdi
		syscall
		ret

section .bss
	buffer:
		RESW		255
section .data
	msg_success:
		DB		"Program compiled.", 0xA, 0xD, 0
	msg_invld_char:
		DB		"Invalid character on line ", 0
	msg_no_args:
		DB		"Too few args. Usage: # bfck [src file] <output file>, [] is mandatory, <> is optional.", 0xA, 0xD, 0
	msg_too_many_args:
		DB		"Too many args. Usage: # bfck	[src file] <output file>, [] is mandatory, <> is optional.", 0xA, 0xD, 0
	msg_err_create:
		DB		"Error creating output file.", 0xA, 0xD, 0
	msg_err_read:
		DB		"Error opening file. Does it even exist?", 0xA, 0xD, 0
	msg_made_it:
		DB		"Made it...", 0xA, 0xD, 0
	testfile_name:
		DB		"test.out", 0
	O_RDONLY		EQU 00o
	O_WRONLY		EQU 01o
	O_CREAT			EQU 0100o
	O_APPEND		EQU 02000o
	args_max		EQU 3
	args_min		EQU 2
	bc			EQU 8
