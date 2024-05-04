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
	mov rax, [rdi + 4 * rcx]
	ret
