.586
.model flat, stdcall

includelib kernel32.lib
includelib libucrt.lib

includelib STD.lib
.stack 4096

.const
ExitProcess PROTO : DWORD
writenote PROTO : DWORD
writeidle PROTO : DWORD
writeunit PROTO : DWORD
copynote PROTO : DWORD, : DWORD
notelength PROTO : DWORD
comprnotes PROTO : DWORD, : DWORD
cncatnotes PROTO : DWORD, : DWORD
powerunit PROTO : DWORD, : DWORD

	overflow db 'ERROR: VARIABLE OVERFLOW', 0 
	null_division db 'ERROR: DIVISION BY ZERO', 0
	__BigData DWORD 17, 7, 21, 16, 32, 15
	_L1 BYTE "First step is done...", 0dh, 0ah, 0dh, 0ah, 0
	_L2 BYTE "My name is ", 0
	_L3 BYTE 0dh, 0ah, 0
	_L4 BYTE "End.", 0
	_L5 BYTE "perfect", 0
	_L6 BYTE " almost got it!", 0
	_L7 BYTE ":) ", 0dh, 0ah, "End of test.", 0dh, 0ah, 0
	_L8 BYTE 0dh, 0ah, "----- Test starts! -----", 0dh, 0ah, 0
	main_array DWORD 322, 28, 4, 13, 0
	_L9 BYTE "Kirill", 0
	_L10 BYTE "Go to the case #1", 0dh, 0ah, 0
	_L11 BYTE "Go to the bad choice", 0dh, 0ah, 0
	_L12 BYTE "it is fail..", 0dh, 0ah, 0
	_L13 BYTE "Value of Z is : ", 0
	_L14 BYTE "Powered ", 0
	_L15 BYTE "by POIT ", 0
	_L16 BYTE "String1 equal to string2 ? -> ", 0
	_L17 BYTE "string with 124*0+5;", 0
	_L18 BYTE 0dh, 0ah, 0dh, 0ah, 0
	_L19 BYTE "Array: ", 0
	_L20 BYTE ", ", 0
	_L21 BYTE " >> last check?", 0

.data
	__globalUn DWORD 244
	__globalIdl BYTE 1
	__globalNote BYTE "First step is done...", 0dh, 0ah, 0dh, 0ah, 232 DUP(0)
	main_start BYTE 255 DUP(0)
	main_x DWORD 0
	main_z DWORD 0
	main_comment BYTE 255 DUP(0)
	main_Str BYTE 255 DUP(0)
	main_cmpr BYTE 0
	main_i DWORD 0
	_c01_h DWORD 0

.code

proc_SimpleFunc PROC p: DWORD
	push 296

	jmp EXIT
EXIT_DIV_ON_NULL:
	push offset null_division
	call writenote
	push -1
	call ExitProcess
EXIT_OVERFLOW:
	push offset overflow
	call writenote
	push -2
	call ExitProcess
EXIT:
	pop eax
	ret 4
proc_SimpleFunc ENDP

proc_VoidParmCall PROC 
	push offset __globalNote

	jmp EXIT
EXIT_DIV_ON_NULL:
	push offset null_division
	call writenote
	push -1
	call ExitProcess
EXIT_OVERFLOW:
	push offset overflow
	call writenote
	push -2
	call ExitProcess
EXIT:
	pop eax
	ret 0
proc_VoidParmCall ENDP

proc_PrintName PROC n: DWORD
	push offset _L2
	call writenote

	push n
	call writenote

	push offset _L3
	call writenote

	push offset _L4
	pop n

	push 1
	call proc_VoidParmCall
	push eax

	pop eax

	call proc_VoidParmCall
	push eax


	jmp EXIT
EXIT_DIV_ON_NULL:
	push offset null_division
	call writenote
	push -1
	call ExitProcess
EXIT_OVERFLOW:
	push offset overflow
	call writenote
	push -2
	call ExitProcess
EXIT:
	pop eax
	ret 4
proc_PrintName ENDP

proc_GetTestMessage PROC a: DWORD, b: DWORD
	push offset _L5
	push a
	call comprnotes
	push eax

	pop eax
	test eax, eax
	jz NEXT0
	push offset _L6
	push a
	call cncatnotes
	push eax

	pop b
	jmp ENDC0
NEXT0:
	push offset _L7
	push b
	call cncatnotes
	push eax

	pop b

NEXT1:
ENDC0:

	push b
	call writenote

	push 17
	call proc_SimpleFunc
	push eax


	jmp EXIT
EXIT_DIV_ON_NULL:
	push offset null_division
	call writenote
	push -1
	call ExitProcess
EXIT_OVERFLOW:
	push offset overflow
	call writenote
	push -2
	call ExitProcess
EXIT:
	pop eax
	test eax, eax
	jz IDLE0
	mov eax, 1
	jmp ENDI0
IDLE0:
	mov eax, 0
ENDI0:
	ret 8
proc_GetTestMessage ENDP

main PROC 
	push offset _L8
	push offset main_start
	call copynote

	push offset main_start
	call writenote

	push offset main_start
	call notelength
	push eax

	push 33
	push 10
	pop ebx
	pop eax
	mov edx, 0
	test ebx,ebx
	jz EXIT_DIV_ON_NULL
	cdq
	idiv ebx
	push edx
	push 156
	push 27
	pop ebx
	pop eax
	test ebx, ebx
	jz EXIT_DIV_ON_NULL
	cdq
	idiv ebx
	push eax
	pop ebx
	pop eax
	add eax, ebx
	jo EXIT_OVERFLOW
	push eax
	pop ebx
	pop eax
	imul eax, ebx
	jo EXIT_OVERFLOW
	push eax
	pop main_x

	push offset _L9
	call proc_PrintName
	push eax

	call writenote

	push 1046
	push main_x
	pop ebx
	pop eax
	test ebx, ebx
	jz EXIT_DIV_ON_NULL
	cdq
	idiv ebx
	push eax
	push 3
	pop ebx
	pop eax
	cmp eax, ebx
	jle NGRTRX0
	mov eax, 1
	jmp ENDX0
NGRTRX0:
	mov eax, 0
ENDX0:
	push eax
	pop eax
	test eax, eax
	jz NEXT2
	push offset _L10
	call writenote
	jmp ENDC1
NEXT2:
	push main_x
	push 0
	pop ebx
	pop eax
	cmp eax, ebx
	jle NGRTRX1
	mov eax, 1
	jmp ENDX1
NGRTRX1:
	mov eax, 0
ENDX1:
	push eax
	pop eax
	test eax, eax
	jz NEXT3
	push offset _L11
	call writenote
	jmp ENDC1
NEXT3:
	push offset _L12
	call writenote

NEXT4:
ENDC1:

	push 2
	push 3
	mov ebx, offset main_array
	pop eax
	imul eax, 4
	add ebx, eax
	jo EXIT_OVERFLOW
	push [ebx]
	call powerunit
	push eax

	push 11
	push 2
	pop ebx
	pop eax
	imul eax, ebx
	jo EXIT_OVERFLOW
	push eax
	pop ebx
	pop eax
	sub eax, ebx
	jo EXIT_OVERFLOW
	push eax
	push main_x
	push 513
	push 3
	pop ebx
	pop eax
	test ebx, ebx
	jz EXIT_DIV_ON_NULL
	cdq
	idiv ebx
	push eax
	pop ebx
	pop eax
	sub eax, ebx
	jo EXIT_OVERFLOW
	push eax
	pop ebx
	pop eax
	test ebx, ebx
	jz EXIT_DIV_ON_NULL
	cdq
	idiv ebx
	push eax
	pop main_z

	push offset _L13
	call writenote

	push main_z
	call writeunit

	push offset _L3
	call writenote

	push offset _L14
	push offset main_comment
	call copynote

	push offset _L15
	push offset main_comment
	call cncatnotes
	push eax

	push offset main_Str
	call copynote

	push offset _L16
	call writenote

	push offset _L17
	push offset main_Str
	call comprnotes
	push eax

	pop eax
	test eax, eax
	jz IDLE1
	mov eax, 1
	jmp ENDI1
IDLE1:
	mov eax, 0
ENDI1:
	mov main_cmpr, al

	movzx eax, main_cmpr
	push eax
	call writeidle

	push offset _L18
	call writenote

	push offset _L19
	call writenote

	movzx eax, main_cmpr
	push eax
	pop main_i

	push 2
	mov ebx, offset main_array
	pop eax
	imul eax, 4
	add ebx, eax
	jo EXIT_OVERFLOW
	push [ebx]
	push 1
	pop ebx
	pop eax
	add eax, ebx
	jo EXIT_OVERFLOW
	push eax
	push main_i
CYCLE0:
	pop eax
	pop ecx
	cmp eax, ecx
	jz ENDS0
	push ecx

	push main_i
	mov ebx, offset main_array
	pop eax
	imul eax, 4
	add ebx, eax
	jo EXIT_OVERFLOW
	push [ebx]
	call writeunit

	push main_i
	mov ebx, offset main_array
	pop eax
	imul eax, 4
	add ebx, eax
	jo EXIT_OVERFLOW
	push [ebx]
	push 5
	mov ebx, offset __BigData
	pop eax
	imul eax, 4
	add ebx, eax
	jo EXIT_OVERFLOW
	push [ebx]
	pop ebx
	pop eax
	cmp eax, ebx
	jge NLESSX2
	mov eax, 1
	jmp ENDX2
NLESSX2:
	mov eax, 0
ENDX2:
	push eax
	pop eax
	test eax, eax
	jz NEXT5
	jmp ENDS0

NEXT5:
ENDC2:

	push main_i
	push 2
	call powerunit
	push eax

	pop _c01_h

	push main_i
	mov ebx, offset main_array
	pop eax
	imul eax, 4
	add ebx, eax
	jo EXIT_OVERFLOW
	push [ebx]
	movzx eax, __globalIdl
	push eax
	pop ebx
	pop eax
	test ebx, ebx
	jz EXIT_DIV_ON_NULL
	cdq
	idiv ebx
	push eax
	push 2
	push 333
	push __globalUn
	pop ebx
	pop eax
	sub eax, ebx
	jo EXIT_OVERFLOW
	push eax
	pop ebx
	pop eax
	imul eax, ebx
	jo EXIT_OVERFLOW
	push eax
	pop ebx
	pop eax
	add eax, ebx
	jo EXIT_OVERFLOW
	push eax
	push _c01_h
	push main_z
	push 44
	pop ebx
	pop eax
	add eax, ebx
	jo EXIT_OVERFLOW
	push eax
	pop ebx
	pop eax
	imul eax, ebx
	jo EXIT_OVERFLOW
	push eax
	push 25
	pop ebx
	pop eax
	sub eax, ebx
	jo EXIT_OVERFLOW
	push eax
	pop ebx
	pop eax
	cmp eax, ebx
	jz EQUALX3
	mov eax, 1
	jmp ENDX3
EQUALX3:
	mov eax, 0
ENDX3:
	push eax
	pop eax
	test eax, eax
	jz NEXT6
	push offset _L20
	call writenote

NEXT6:
ENDC3:

	push main_i
	pop eax
	inc eax
	push eax
	pop main_i

	push eax
	jmp CYCLE0
ENDS0:

	push offset _L3
	call writenote

	push offset main_Str
	push offset _L21
	call proc_GetTestMessage
	push eax

	pop eax


	jmp EXIT
EXIT_DIV_ON_NULL:
	push offset null_division
	call writenote
	push -1
	call ExitProcess
EXIT_OVERFLOW:
	push offset overflow
	call writenote
	push -2
	call ExitProcess
EXIT:
	push 0
	call ExitProcess
main ENDP
end main