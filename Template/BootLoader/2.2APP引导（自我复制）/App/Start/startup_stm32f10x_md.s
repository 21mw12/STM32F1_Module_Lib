                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors

__Vectors       DCD     0x20000000+0x5000       ; Top of Stack
				; ��Ҫ�ڷ����������ҵ�Reset Handler���ڴ��ַ�����޸�ΪFlash��ַ+1
                DCD     0x08005029               ; Reset Handler

                AREA    |.text|, CODE, READONLY

; Reset handler
Reset_Handler    PROC
                 EXPORT  Reset_Handler             [WEAK]
				 IMPORT  app_main 
                 IMPORT	APP_CopyToRAM
				 IMPORT	|Image$$ER_IROM1$$Length|
				
				 ; �õ���ǰ��ַ�������8λ�����Ϊ0x08005000
				 ADR	r0, Reset_Handler
				 BIC	r0, r0, #0xFF
				 ; ������Ŀ�ĵ�ַ
				 ldr	r1, =__Vectors
				 ; ������Ŀ�ĳ���
				 ldr	r2, =|Image$$ER_IROM1$$Length|
				 ; ִ�п�������
				 BL		APP_CopyToRAM
				 
                 BL     app_main
				 
                 ENDP

                 END
