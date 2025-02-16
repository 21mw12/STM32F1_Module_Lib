# 1XIP

- 烧录过程：
  - Boot代码效果一样实现方式不同，可以用Keil直接烧录。
  - APP代码也可直接用Keil烧录。
- 效果：Boot阶段C14引脚LED会亮，APP阶段C13引脚LED闪烁。
- 原理：Boot程序执行完，直接跳转到APP程序的地址执行。



# 2APP引导

## 2.1修改链接地址

- 烧录过程：
  - Boot可以用Keil直接烧录。
  - APP代码需要使用烧录工具（如STM32 ST-LINK Utility），指定烧录在0x08005000的位置。
- 效果：Boot阶段C14引脚LED会亮，APP阶段C13引脚LED闪烁。
- 原理：Boot程序执行完，跳转到APP程序的地址，但APP程序的链接地址在内存中，所以修改链接地址到Flash执行（仅能执行相对跳转的代码）。整个代码执行还是在Flash中完成的。



## 2.2自我复制

- 烧录过程：
  - Boot可以用Keil直接烧录。
  - APP代码需要使用烧录工具（如STM32 ST-LINK Utility），指定烧录在0x08005000的位置。
- 效果：Boot阶段C14引脚LED会亮，APP阶段C13引脚LED闪烁。
- 原理：Boot程序执行完，跳转到APP程序的地址，APP程序会先将程序复制到内存中，再到内存中执行。



# 3BootLoader引导

- 烧录过程
  - Boot可以用Keil直接烧录。
  - APP代码需要使用烧录工具（如STM32 ST-LINK Utility），指定烧录在0x08005000的位置。
- 效果：Boot阶段C14引脚LED会亮，APP阶段C13引脚LED闪烁。
- 原理：Boot程序读取APP的头部信息并分析，将APP程序复制到内存中，再到内存中执行。

- 给APP添加头部信息

  ```shell
  ./mkimage.exe -n "stm32f103_app" -a 0x20000000 -e 0x20000029 -d project.bin app.bin
  ```



# 调试内存程序

- 调试内存中运行的程序模板

