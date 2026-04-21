#ifndef __COMMAND_H_
#define __COMMAND_H_

///////////////////////////////////////////////////////////
//
// 文件功能：实现Shell的命令部分基本功能
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2025/05/11
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* 命令结构体 */
typedef struct {
  char *name;				// 命令名
  char *short_help;	// 简短的提示信息
  char *long_help;	// 详细的提示信息
  int (*function)(int argc, char **argv);	// 命令执行的函数
} command;


/**
 * @brief 获取所有命令的结构体数组
 * @return 所有命令的结构体数组
 */
command** Command_Get_Struct(void);

/**
 * @brief 通过命令名查找命令结构体
 * @param name 命令名
 * @return 命令结构体
 */
command* Command_Find(char* name);

#endif
