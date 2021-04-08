
extern _kmain

bits 32

global _kentry

_kentry:
	
	
	push ebp    
    mov ebp, esp
    mov eax, [ ebp +8 ]  
	;mov  edi, [ ebp +8 ] 	    
	;mov  eax, 0xFFFFFFFF   
	;stosd

	push eax

	call _kmain
	add esp, 4
	
	pop ebp     ; minimal cleanup
	ret
	
	jmp $
