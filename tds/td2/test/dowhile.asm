        SECTION .data		; Data section, initialized variables

fmt_int:   	db "%ld", 0	
fmt_char:   	db "%c", 0	
fmt_char_in:	db "%c", 0	
fmt_cr:    	db 10, 0	
fmt_string:    	db "%s", 0	

        SECTION .bss

	global main	        ; the standard gcc entry point

				; Declare external C functions, to be called
        extern	printf		
	extern	__isoc99_scanf
	extern	scanf
        extern	malloc		
        extern	free		
	default rel

	SECTION .text           ; Code section.

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Runtime x86
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Usage:
; push int
; call print_int
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
print_int:			
	push 	rbp
	mov  	rbp,rsp
	
	lea	rdi,[fmt_int]	; format for printf
	mov	esi,[rbp+16]    ; first parameter for printf
	xor	rax,rax		; no xmm registers
        call    printf		; call C function

	pop	rbp		; restore stack			
	ret	8		; return

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Usage:
; push char
; call print_char
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
print_char:
	push 	rbp
	mov  	rbp,rsp
	
	mov	rdi,fmt_char	; format for printf
	mov	rsi,[rbp+16]    ; first parameter for printf
	mov	rax,0		; no xmm registers
        call    printf		; call C function

	pop	rbp		; restore stack			
	ret	8		; return

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Usage:
; call print_newline
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
print_newline:	
	mov	rdi,fmt_cr	; format for printf
	mov	rsi,fmt_cr      ; first parameter for printf
	mov	rax,0		; no xmm registers
        call    printf		; call C function
	ret			; return
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Usage:
; push @base_string
; call print_string
; string should be ASCIIZ 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
print_string:
        push    rbp
	mov  	rbp,rsp
	
	mov	rdi,fmt_string	; format for printf
	mov	rsi,[rbp+16]    ; first parameter for printf
	mov	rax,0		; no xmm registers
        call    printf		; call C function

	pop	rbp		; restore stack
	ret	8		; return

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Usage:
; call input_char
; return rax: input char 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
input_char:	
        push    rbp
	mov  	rbp,rsp
	sub	rsp,32		; allocate space for input char
	
	; format for scanf
	lea	rdi,[fmt_char_in]	; format for scanf
	lea	rsi,[rbp-32]
        xor 	rax,rax
        call    scanf	; call scanf

	xor	rax,rax
	mov	al,byte[rbp-32]	; get the result in rax

	mov	rsp,rbp
	pop	rbp		; restore stack
	ret			; return

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Usage:
; call input_int
; return rax: input int 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
input_int:	
        push    rbp
	mov  	rbp,rsp
	sub	rsp,32		; allocate space for input char
	
	; format for scanf
	lea	rdi,[fmt_int]	; format for scanf
	lea	rsi,[rbp-32]
        xor 	rax,rax
        call    scanf	        ; call scanf

	mov	rax,[rbp-32]	; get the result in rax

	mov	rsp,rbp
	pop	rbp		; restore stack
	ret			; return

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Usage:
; push size
; call _malloc
; return rax: base address
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
_malloc:
	push	rbp
	mov	rbp,rsp
	
	mov 	rdi,[rbp+16]
	call 	malloc
	; rax is a pointer to the allocated space

	mov	rbx,[rbp+16]
	cmp	rbx,8
	je 	end_malloc	; scalar type (one word) => exit

	;;  prepare allocated memory for digcc struct types
	mov 	rdi,rax	
	add	rdi,rbx
	sub	rdi,8		; rdi points to the last word
	mov	[rax],rdi	; first word := pointer to last word	
	
end_malloc:	
	pop	rbp
	ret	8

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Usage:
; push  @base
; push size //compatibility with digmips
; call _free
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
_free:
	push	rbp
	mov	rbp,rsp

	mov	rdi,[rbp+24]
	call 	free	

	pop	rbp
	ret	16

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Main program
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	call	main
	mov	rax,0
	ret	0
main:
	push	rbp
	mov	rbp,rsp
	sub	rsp,16
	mov	rax,3
	push	rax
	pop	rax
	mov	[rbp - 8],rax
	mov	rax,1
	push	rax
	pop	rax
	mov	[rbp - 16],rax
while_0:
	mov	rax,[rbp - 16]
	push	rax
	mov	rax,[rbp - 8]
	push	rax
	pop	rbx
	pop	rax
	mul	rbx
	push	rax
	pop	rax
	mov	[rbp - 16],rax
	mov	rax,[rbp - 8]
	push	rax
	mov	rax,1
	push	rax
	pop	rbx
	pop	rax
	sub	rax,rbx
	push	rax
	pop	rax
	mov	[rbp - 8],rax
	mov	rax,[rbp - 8]
	push	rax
	mov	rax,0
	push	rax
	pop	rbx
	pop	rax
	cmp	rax,rbx
	mov	rax,0
	setg	al
	push	rax
	pop	rax
	cmp	rax,0
	jne	end_cmp_0
	jmp	endwhile_0
end_cmp_0:
endwhile_0:
	mov	rax,[rbp - 16]
	push	rax
	call	print_int
	call	print_newline
	mov	rsp,rbp
	pop	rbp
	ret	0
