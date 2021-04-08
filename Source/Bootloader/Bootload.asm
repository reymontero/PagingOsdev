
[ORG 0x7c00]
[BITS 16]

global _boot

_boot:

	; Clearing segments ;
	xor ax, ax          ;
	mov es, ax          ;
	mov ds, ax          ; 
	; ------------------;
	
	; Setting the stack ;
	mov ax, 0x9000      ;
	mov sp, ax          ;
	mov ss, ax          ;
	mov bp, ax          ;
	; ------------------;
	
	; Move drive number ;
	mov [dev], dl       ;
	; ------------------;
	
ReadDisk:	
	
	; Adress on RAM ----;
	mov ax, 0x07e0      ;
	mov es, ax          ;
	mov bx, 0           ;
	; ------------------;
	
	; Disk Read Int ----;
	mov ah, 0x02        ; BIOS Command
	mov al, 4           ; Number of Sectors to read
	mov ch, 0x00        ; Low Eight bit of cylinder number
	mov cl, 0x02        ; 0-5 bits sector number to start from 6-7 bits high two bits of cylinder number
	mov dh, 0x00        ; Head Number
	mov dl, [dev]       ; Drive Number
	int 13h             ;
	; ------------------;
	
	; Disk Errors ------;
	jc disk_error       ;	
	; ------------------;
	
CheckA20:
	
	; Check A20 Stat----;
	mov ax, 2402h       ;
	int 15h             ;
	                    ;
	cmp al, 1           ;
	je A20Enabled       ;
	; ------------------;
	
EnableA20:
	
	; Enable A20---------------;
	mov ax, 2401               ;
	int 15h                    ;
	                           ;
	cmp al, 1                  ;
	je A20Enabled              ;
	                           ;
	mov bx, A20_error_msg      ;
	call print_string          ;
	; -------------------------;
	
A20Enabled:
	
	; -------------------------;
	mov bx, A20_msg            ;
	call print_string          ;
	; -------------------------;
	
JumpToSecondStage:

	; -------------------------;     
	mov dl, [dev]              ; Give the second stage bootloader the drive number
	call 0x7e00                ; Lets go
	; -------------------------;
	
	jmp $
	

; Definitions -------------;
                           ;
disk_error:                ;
	mov bx, disk_error_msg ;
	call print_string      ;
	jmp $                  ;
	                       ;
print_string:	           ;
                           ;	
.loop:                     ;
    mov al,[bx]            ; 
	cmp al,0               ;
	je return              ;
	push bx                ;
	mov ah,0Eh             ;
	                       ;
	int 10h                ;
	pop bx                 ;
	inc bx                 ;
	jmp .loop              ;
	                       ;
return:                    ;
	ret	                   ;
; -------------------------;

; Vars ---------------------------------;
dev: db 0                               ;
disk_error_msg db "Disk Error",13,10,0  ;-----------;
A20_error_msg db "A20 cannot be enabled...",13,10,0 ; 
A20_msg db "A20 enabled",13,10,0        ;-----------; 
; --------------------------------------;

; -------------------------;
times 510-($-$$) db 0      ;
dw 0xaa55                  ;
; -------------------------;
 

