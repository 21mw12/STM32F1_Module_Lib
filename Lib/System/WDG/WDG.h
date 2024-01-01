#ifndef __WDG_H
#define __WDG_H

///////////////////////////////////////////////////////////

// 文件功能：看门狗的相关功能解释
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2024/01/01
//
// 注：独立看门狗超时时间 = 1 / 40KHz * 分频系数 * （IWDG_ARR + 1）
//		 窗口看门狗超时时间 = 1 / 36MHz * 4096 * 分频系数 * （IWDG_TValue + 1）
//		 窗口看门狗窗口时间 = 1 / 36MHz * 4096 * 分频系数 * （IWDG_TValue - IWDG_WValue）
//
//		独立看门狗分频系数默认为16
//		窗口看门狗分频系数默认为8
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

#define IWDG_ARR			2499		// 独立看门狗的重装载值
#define IWDG_TValue		54			// 窗口看门狗的控制寄存器
#define IWDG_WValue		21			// 窗口看门狗的配置寄存器

enum ResetStatus {
	NoReset = 0,
	Reset
};

/**
  * @brief 独立看门狗初始化
  * @return 无
  */
void IWDG_Init(void);

/**
  * @brief 检查是否是独立看门狗引起的复位
  * @return 复位状态
  */
enum ResetStatus IWDG_isReset(void);

/**
  * @brief 独立看门狗喂狗
  * @return 无
  */
#define IWDG_FeedDog()		IWDG_ReloadCounter()


/**
  * @brief 窗口看门狗初始化
  * @return 无
  */
void WWDG_Init(void);

/**
  * @brief 检查是否是窗口看门狗引起的复位
  * @return 复位状态
  */
enum ResetStatus WWDG_isReset(void);

/**
  * @brief 窗口看门狗喂狗
  * @return 无
	* 注：不能离初始化函数太近
  */
#define WWDG_FeedDog()		WWDG_SetCounter(0x40 | IWDG_TValue)

#endif
