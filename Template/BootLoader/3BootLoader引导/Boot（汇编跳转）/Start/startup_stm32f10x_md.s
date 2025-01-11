                PRESERVE8
                THUMB

; Vector Table Mapped to Address 0 at Reset
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors

__Vectors       DCD     0x20000000+0x5000          ; Top of Stack
                DCD     Reset_Handler              ; Reset Handler

                AREA    |.text|, CODE, READONLY

; Reset handler
Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
				IMPORT  main
				
                BL      main
				 
                ENDP
					 
App_Start   	PROC
				EXPORT  App_Start
				
				; set vector base address as param
				LDR		r3, =0xE000ED08
				STR		r0, [r3]
				
				; set sp val
				LDR		SP, [r0]		; read val from addr param
				LDR		r1, [r0, #4]	; read val from addr param 4
				
				; skip
				BX		r1
				 
                ENDP

                END