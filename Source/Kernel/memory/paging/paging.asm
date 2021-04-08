
BITS 32

global _enablePaging

_enablePaging:
	push ebp
	mov ebp, esp
	mov eax, [ebp + 8]
    mov cr3, eax
    mov eax, cr0
    or eax, 0x80000001
    mov cr0, eax   
    mov esp, ebp
	pop ebp
	ret

