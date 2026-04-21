#ifndef __SHELL_H_
#define __SHELL_H_

///////////////////////////////////////////////////////////
//
// 文件功能：实现Shell的基本功能
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2025/05/11
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

// 是否开启特殊按键回显（用于调试）
#define Show_Spectial_Key_Echo		0

#define SHELL_CMD_NAME_SIZE		20	// 命令名最大长度
#define SHELL_CMD_PARAM_SIZE	8		// 每条命令最多可以有的参数数量
#define SHELL_CMD_SIZE      	80	// 每条命令最长长度
#define SHELL_HISTORY_LINES 	5		// 历史命令记忆数量

/* Shell头部信息 */
static char* Shell_Custom_Prompt = "\r\nmsh >";

/**
  * @brief Shell启动
  * @return 无
  */
void Shell_Run(void);

#endif
