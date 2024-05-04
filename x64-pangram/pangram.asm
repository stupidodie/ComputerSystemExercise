section .text
global pangram
pangram:
	; rdi: source string
	
	xor edx, edx
	xor ecx, ecx
._LOOP:
	mov cl,[rdi]
	INC rdi
	cmp cl, 0
	je ._compare
	cmp cl, '@'
	jl ._LOOP
	bts edx, ecx
	jmp ._LOOP
._compare:
	and edx,0x07fffffe
	cmp edx, 0x07fffffe 
	sete al
	movzx eax, al
	ret
