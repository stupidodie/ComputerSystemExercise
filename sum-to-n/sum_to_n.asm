section .text
global sum_to_n
sum_to_n:
	; without LOOP 
	; MOV rax, rdi
	; ADD rax, 1
	; IMUL rax, rdi
	; SHR  rax, 1
	; ret
	xor rax, rax
	xor rdx, rdx 
	ADD rax, rdx
	CMP rdx, rdi
	JNE .LP
	JMP .exit
.LP:	
	INC rdx
	ADD rax, rdx
	CMP rdx, rdi
	JNE .LP
.exit:
	ret