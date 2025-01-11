                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors

__Vectors       DCD     0x20000000+0x5000       ; Top of Stack
				; 需要在反汇编代码中找到Reset Handler的内存地址，再修改为Flash地址+1
                DCD     0x08005029               ; Reset Handler

                AREA    |.text|, CODE, READONLY

; Reset handler
Reset_Handler    PROC
                 EXPORT  Reset_Handler             [WEAK]
				 IMPORT  app_main
					 
                 ;LDR     SP, =(0x20000000+0x5000)
                 BL      app_main
				 
                 ENDP

                 END
