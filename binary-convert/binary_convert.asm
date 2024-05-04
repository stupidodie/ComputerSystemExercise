section .text
global binary_convert
binary_convert:
	xor eax, eax
._loop:
	movzx ecx, byte [rdi]
	cmp ecx, 0
	je ._exit
	shl eax, 1
	inc rdi
	sub ecx, '0'
	add eax, ecx
	jmp ._loop
._exit:
	ret