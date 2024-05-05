section .text
global fib
fib:
	cmp edi,2
	jl .basic_case
	jmp .cal
.cal:
	dec edi
	push rdi
	call fib ; fib(n-1)
	pop rdi
	push rax
	dec edi
	call fib ; fib(n-2)
	pop rdx
	add eax, edx
	ret 
.basic_case:
	mov eax, edi 
	ret
