section .text
global binary_convert
binary_convert:
	xor eax, eax
	xor ecx, ecx
._loop:
	mov cl, [rdi]
	cmp cl, 0
	je ._exit
	shl eax, 1
	inc rdi
	sub cl, '0'
	add eax, ecx
	jmp ._loop
._exit:
	ret