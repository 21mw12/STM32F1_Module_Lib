#ifndef __LOWPOWER_H
#define __LOWPOWER_H

///////////////////////////////////////////////////////////

// 文件功能：低功耗的相关功能解释
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2023/12/31
//
// 注：STM32进入低功耗时，不会直接响应下载程序
//		 需要按住RESET按键，再点击Download，再松开按键
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/**
  * 系统主频
	*
	* 1. 通过引用 SystemCoreClock 用于获取当前系统主频
	* 2. 修改主频再 system_stm32f10x.c 文件中的第106行区域进行修改
	*
	* 注：修改主频后所有计时功能都会受影响，不建议修改
  */

/**
  * @brief 低功耗模式初始化
  * @return 无
  */
void LowerPower_Init(void);

/**
  * 睡眠模式
	*
	* 1. 调用 __WFI(); 进入睡眠模式，使用任意中断唤醒（推荐使用）
	* 2. 调用 __WFE(); 进入睡眠模式，使用唤醒事件唤醒
	*
	* 流程：中断唤醒后先执行中断处理函数，在执行主循环直到下一次睡眠
	*
	* 注：可以写在主循环的最后面
  */

/**
  * 停止模式
	* 
	* 在任意外部中断后会唤醒
  */
/**
  * @brief 进入停止模式
  * @return 无
  */
void LowerPower_EnterStop(void);

/**
  * 待机模式
	*
	* 仅在 WKUP引脚（PA0）上升沿、RTC闹钟事件、复位、独立看门狗复位 触发时会唤醒
	*
	* 注：写在主循环的最后面，进入待机模式后的代码将永远不会执行
  */
/**
  * @brief 进入待机模式
  * @return 无
  */
void LowerPower_EnterSandBY(void);

/**
  * @brief WakeUP引脚初始化
  * @return 无
  */
void LowerPower_SandBY_WakeUpPin_Init(void);


#endif
