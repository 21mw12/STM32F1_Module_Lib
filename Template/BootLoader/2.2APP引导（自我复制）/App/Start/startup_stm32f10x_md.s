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
                 IMPORT	APP_CopyToRAM
				 IMPORT	|Image$$ER_IROM1$$Length|
				
				 ; 得到当前地址并清除低8位，结果为0x08005000
				 ADR	r0, Reset_Handler
				 BIC	r0, r0, #0xFF
				 ; 拷贝的目的地址
				 ldr	r1, =__Vectors
				 ; 拷贝的目的长度
				 ldr	r2, =|Image$$ER_IROM1$$Length|
				 ; 执行拷贝函数
				 BL		APP_CopyToRAM
				 
                 BL     app_main
				 
                 ENDP

                 END
