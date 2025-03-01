# STM32F1模块库

## 项目背景

STM32F1型号单片机在网络上资料最丰富，但依然有部分缺点，比如

1. 模块和功能繁多导致找一个可以使用的库并不容易。
2. 代码来自于不同的作者，每个作者的代码风格不同对小白并不友好。
3. 多数代码中的注释并没有很好的解释性，即使拿到代码可能也不会使用。
4. 在网上购买的模块商家会提供源代码，但绝大多数的代码并不能直接使用，而且代码格式并不美观，想使用会有一定的门槛。

基于以上的问题，我计划整理并发布所有我接触过的模块和功能的库函数，争取让绝大部分小白在掌握基础的开发能力后就能直接上手使用我提供的所有库函数。



## 关于项目名

这里暂定为`STM32F1XX模块库`，主要原因是我接触这系列单片机最多也最熟悉。其他型号并没有过多的接触，暂时并不能保证其他型号的单片机也可以正常使用。如果有能力你也可以将其改写以适应更多的型号。



## 项目意义

1. 将我使用过的模块功能近一步整理，这样可以让我进一步学习底层原理，也可以在二次开发的时候提供便利。
2. 会有很多人并没有时间去深入的学习其中的知识，但迫于种种原因由需要上手实践，可以使用我提供的代码快速进行开发。
3. 能让更多的人轻松的上手学习单片机的开发，享受并体验单片机的乐趣。



# 项目内容

## 项目结构

- Demo：示例工程文件夹
  
- Document：文档文件夹，所有模块的介绍说明书存放于此。
  - STM32F103C8T6：关于项目主控的相关文档
  - Algorithm：关于算法的文档
  - Hardware：关于硬件模块的文档
  - System：关于片上或系统级资源的文档
  
- Lib：模块库文件夹，所有的模块的`.c`和`.h`源代码存放于此。
  - Algorithm：关于算法的源代码
  - Component：关于功能类组件的源代码
  - Hardware：关于硬件模块的源代码
  - System：关于片上或系统级资源的源代码
- Template：
  - Bare：STM32F1裸机空白工程模板。
  - FreeRTOS：基于FreeRTOS操作系统的STM32F1空白工程模板。
- Tool：相关工具软件




## 项目开发过程

1. 在计划：有开发这个功能的想法，开发已提上日程。
2. 在整理：正在整理资料。
3. 在编写：正在编写或改写代码。
4. 在测试：正在测试代码是否有bug。
5. 完善注释：开发已完成但注释没有写完。
6. 已完成：一切均已完成已经上传。



## 项目进度

### 模块

| 模块名            | 完成时间   | 进度   | 备注                                                         |
| ----------------- | ---------- | ------ | ------------------------------------------------------------ |
| LED灯             | 2023/04/21 | 已完成 | 兼用两种硬件连接方式                                         |
| 独立按键          | 2023/04/25 | 已完成 | 实现了普通查询，中断以及状态机三种实现方式                   |
| 矩阵按键          | 2023/05/06 | 已完成 |                                                              |
| OLED显示屏        | 2023/07/07 | 已完成 | 支持0.96寸和0.91寸OLED显示屏，同时支持I2C和SPI，提供绘图函数 |
| 旋转编码器        | 2023/06/26 | 已完成 | 可选中断形式的不准确测量和定时器形式的准确测量               |
| DHT11温湿度传感器 | 2023/04/26 | 已完成 |                                                              |
| 蜂鸣器            | 2023/05/02 | 已完成 |                                                              |
| 数码管显示        | 2023/05/12 | 已完成 | 支持74HC系列和MAX7219两种芯片驱动                            |
| 舵机              | 2023/06/15 | 已完成 |                                                              |
| MPU6050           | 2023/07/07 | 已完成 | 支持新的I2C库                                                |
| 电机              | 2023/07/12 | 已完成 | 包含有编码器和无编码器                                       |
| 超声波传感器      | 2023/07/12 | 已完成 |                                                              |
| W25QXX系列        | 2023/12/27 | 已完成 | 支持快速切换软件SPI和硬件SPI                                 |
| PS2               | 2023/12/30 | 已完成 |                                                              |
| AHT10             | 2024/01/06 | 已完成 |                                                              |
| GT24（nRF24L01）  |            | 在计划 |                                                              |
| SD卡读写模块      |            | 在计划 |                                                              |
| 激光传感测距模块  |            | 在计划 |                                                              |
| RC552射频模块     |            | 在计划 |                                                              |
| HX711称重传感器   | 2024/01/26 | 已完成 |                                                              |
| 三色墨水屏        | 2024/11/17 | 已完成 |                                                              |



### 功能

| 功能名      | 完成时间   | 进度   | 备注                                  |
| ----------- | ---------- | ------ | ------------------------------------- |
| 延时功能    | 2023/04/21 | 已完成 |                                       |
| 串口功能    | 2023/06/13 | 已完成 | 实现了不定长数据包的接收和发送        |
| 软件模拟I2C | 2023/07/07 | 已完成 |                                       |
| 硬件I2C     | 2023/07/07 | 已完成 |                                       |
| 软件模拟SPI | 2023/12/27 | 已完成 |                                       |
| 硬件SPI     | 2023/12/27 | 已完成 |                                       |
| 定时器      | 2023/07/12 | 已完成 | 定时器的定时功能、PWM功能、编码器接口 |
| ADC         | 2023/05/02 | 已完成 |                                       |
| DAC         |            |        |                                       |
| BKP         | 2023/12/30 | 已完成 |                                       |
| RTC         | 2023/12/30 | 已完成 |                                       |
| 低功耗模式  | 2023/12/31 | 已完成 |                                       |
| 看门狗      | 2023/01/01 | 已完成 | 包括独立和窗口看门狗                  |
| Flash       | 2023/01/02 | 已完成 |                                       |
| DMA         | 2024/01/23 | 已完成 | 集成在ADC库中                         |
| CRTP        | 2024/10/29 | 已完成 | 只支持在FreeRTOS环境下                |



### 算法

| 算法名       | 完成时间   | 进度   | 备注 |
| ------------ | ---------- | ------ | ---- |
| 卡尔曼滤波器 | 2023/07/14 | 已完成 |      |
| PID          | 2023/08/24 | 已完成 |      |



## 代码版本

使用`Vx.x`进行标记：

- 一个大版本的更新表示代码有较大的重构。

- 一个小版本的更新表示对该模块添加了新的功能，或修复了某个bug。

详细的更新日志将记录在第二个版本开始的`.h`文件的最后。



## 代码来源

为了加快编写代码的周期，可能会有很多代码并不是由本人完全编写而成。

代码可能来自于以下作者，包括但不限于`洋桃电子`、`江协科技(原名：江科大自化协)`、`中景园电子`、`野火`。

也可以来自于各个平台，包括但不限于`CSDN`、`博客园`、`私人博客`。

若是从其他地方整理上传会标明出处。



# 注意：可能出现的问题

~~目前所有文件均以ANSI编码编写，以其他编码方式打开可能会出现乱码。关于编码问题目前还没有彻底搞懂，之后可能会完善。~~

使用Keil打开如果中文有乱码可以在Edit>Configuration>Editor>Encoding中选择GB2312编码方式。
