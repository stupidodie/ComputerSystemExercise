section .text
global index
index:
	; rdi: matrix
	; esi: rows
	; edx: cols
	; ecx: rindex
	; r8d: cindex
	imul ecx, edx
	Add ecx, r8d
	imul ecx, 4
	Add rdi, rcx
	mov rax, [rdi]
	ret
