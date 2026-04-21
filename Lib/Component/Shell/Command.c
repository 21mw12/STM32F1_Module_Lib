#include "Command.h"
#include <string.h>
#include "USART1.h"

/* help 命令相关声明 */
extern command help_cmd;
static int help_func(int argc, char **argv);

/* 所有命令结构体 */
static command* g_commands[] = {
	&help_cmd,
	NULL
};

command** Command_Get_Struct(void) {
	return g_commands;
}

command* Command_Find(char *name) {
	int i = 0;
	while (g_commands[i]) {
		if (strcmp(g_commands[i]->name, name) == 0)
			return g_commands[i];
		i++;
	}
	return NULL;
}

/* 定义 help_cmd 结构体 */
command help_cmd = {
	.name = "help",
	.short_help = "Print help information",
	.long_help = "Usage: help [command]\r\nPrints help for all commands or a specific command.",
	.function = help_func,
};
/* help 命令功能 */
static int help_func(int argc, char **argv) {
	uint32_t i = 0;
	
	if (argc == 1) {
		while(g_commands[i]) {
			USART1_SendString(g_commands[i]->name);
			USART1_SendString(" - ");
			USART1_SendString(g_commands[i]->short_help);
			i++;
		}
	}
	else if (argc == 2) {
		command* cmd = Command_Find(argv[1]);
		if (cmd) {
			USART1_SendString(cmd->name);
			USART1_SendString(":\r\n");
			USART1_SendString(cmd->long_help);
		} else {
			USART1_SendString(cmd->name);
			USART1_SendString(" command not found.");
		}
	}
	return 0;
}
