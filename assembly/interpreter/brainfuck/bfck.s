global _start
section .bss
	input:		RESB 255
	output:		RESB 15

section .text
_start:
	prompt:
		mov	rsi, prmpt
		mov	rdx, 5
		mov	rdi, 1
		mov	rax, 1
		syscall

		mov	rsi, input
		mov	rdx, 255
		xor	rdi, rdi
		xor	rax, rax
		syscall

		mov	rsi, input
		cmp	byte [rsi], 120
		je	exit
		cmp	byte [rsi], 10
		je	help
		cmp	byte [rsi], 0
		je	help

		call	run_bfck
		xor	rax, rax
		xor	rdi, rdi
		mov	rsi, input
		mov	rdx, 255
		syscall

		jmp	prompt
	help:
		mov	rsi, help_msg
		mov	rdx, help_msg.length
		mov	rdi, 1
		mov	rax, 1
		syscall
		jmp	prompt
	exit:
		xor	rdi, rdi
		mov	rax, 60
		syscall

run_bfck:
		call	wipe_cells
		mov	r10, 0
		mov	r8, input
		mov	esi, stack
	run_cmd:
		cmp	byte [r8], '>'
		je	inc_ptr
		cmp	byte [r8], '<'
		je	dec_ptr
		cmp	byte [r8], '+'
		je	inc_cell
		cmp	byte [r8], '-'
		je	dec_cell
		cmp	byte [r8], '.'
		je	print_cell
		cmp	byte [r8], ','
		je	input_cell
		cmp	byte [r8], '['
		je	jmp_fwd
		cmp	byte [r8], ']'
		je	jmp_bkwd
		cmp	byte [r8], '0'
		jb	pre_step
		cmp	byte [r8], '9'
		ja	pre_step
		jmp	process_nums
	    pre_step:
		xor	r10, r10
	step:
		inc	r8
		cmp	byte [r8], 0
		je	return
		cmp	byte [r8], 10
		je	return
		jmp	run_cmd

	inc_ptr:
		inc	esi
		mov	rax, stack
		add	rax, 16383
		mov	r9, stack
		cmp	esi, eax
		cmovae	esi, r9d
		mov	r10, 3
		jmp	step
	dec_ptr:
		dec	esi
		mov	rax, stack
		xor	rdx, rdx
		mov	r9, 16384
		cmp	eax, esi
		cmova	rdx, r9
		add	esi, edx
		mov	r10, 4
		jmp	step
	inc_cell:
		inc	byte [esi]
		mov	r10, 1
		jmp	step
	dec_cell:
		dec	byte [esi]
		mov	r10, 2
		jmp	step
	print_cell:
		mov	rdx, 1
		mov	rax, 1
		mov	rdi, 1
		syscall
		mov	r10, 0
		jmp	step
	input_cell:
		mov	rdx, 1
		xor	rdi, rdi
		xor	rax, rax
		syscall
		mov	r10, 0
		jmp	step
	jmp_fwd:
		mov	r10, 0
		cmp	byte [esi], 0
		jne	step
	    fwd:
	    	inc	r8
	    	cmp	byte [r8], 0
	    	je	step
	    	cmp	byte [r8], ']'
	    	jne	fwd
		jmp	step
	jmp_bkwd:
		mov	r10, 0
		cmp	byte [esi], 0
		je	step
	    bkwd:
	    	dec	r8
	    	mov	rax, input
	    	cmp	rax, r8
	    	ja	step
	    	cmp	byte [r8], '['
	    	jne	bkwd
		jmp	step
	return:
		ret

wipe_cells:
		mov	esi, stack
	begin:
		mov	byte [esi], 0
		inc	esi
		mov	rax, stack
		add	rax, 16383
		cmp	esi, eax
		jb	begin
		ret

process_nums:
		xor	rax, rax
	start_loop:
		mov	ecx, 10
		mul	ecx
		add	eax, dword [r8]
		sub	eax, 48
		inc	r8
		cmp	byte [r8], '0'
		jb	end_loop
		cmp	byte [r8], '9'
		ja	end_loop
		jmp	start_loop
	end_loop:
		dec	r8
		cmp	r10, 0
		je	set_cell
		cmp	r10, 1
		je	add_cell
		cmp	r10, 2
		je	sub_cell
		cmp	r10, 3
		je	add_ptr
		cmp	r10, 4
		je	sub_ptr
		jmp	pre_step
	set_cell:
		mov	byte [esi], al
		jmp	pre_step
	add_cell:
		add	byte [esi], al
		jmp	pre_step
	sub_cell:
		sub	byte [esi], al
		jmp	pre_step
	add_ptr:
		add	esi, eax
		;mov	eax, stack
		;add	eax, 16383
		;sub	eax, esi
		;js	ptr_overflow
		;jmp	pre_step
	    ;ptr_overflow:
	    	;mov	esi, stack
	    	;add	esi, eax
	    	jmp	pre_step
	sub_ptr:
		sub	esi, eax
		;mov	eax, stack
		;sub	eax, esi
		;jns	ptr_underflow
		;jmp	pre_step
	    ;ptr_underflow:
	    	;mov	esi, stack
	    	;add	esi, 16384
	    	;sub	esi, eax
	    	jmp	pre_step

section .data
	prmpt		DB 32,32,32,32,0
	help_msg:	DB "This is a simple brainfuck interpreter.",10,"There are 16,383 cells to work with.",10,"If the first character of input is 'x' the program will exit.",10,"Cells are wiped in between lines",10,"Use numbers to shorten strings of +'s and -'s: '++++' is equivalent to '+3'",10,"Input taken on next line",10,0
	.length:	EQU $-help_msg
	stack		TIMES 16384 DB 0
	dec_ptr_test:	DB "Subtracting from pointer... ",0
	.length:	EQU $-dec_ptr_test

