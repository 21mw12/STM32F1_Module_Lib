#include "Shell.h"
#include <string.h>
#include "delay.h"
#include "USART1.h"
#include "Command.h"

/* 方向键判别状态枚举 */
typedef enum {
	WAIT_NORMAL,
	WAIT_SPEC_KEY,
	WAIT_FUNC_KEY,
} Shell_Spectial_Key;

/* Shell功能信息结构体 */
typedef struct{
	Shell_Spectial_Key SKey_state;				// 方向键状态枚举

	uint8_t echo_mode:		1;							// 回显
	uint8_t prompt_mode:	1;							// 提示

	uint16_t current_history;							// 当前历史领命位置
	uint16_t history_count;								// 当前历史命令数量
	char cmd_history[SHELL_HISTORY_LINES][SHELL_CMD_SIZE];	// 历史命令

	char line[SHELL_CMD_SIZE + 1];	// 当前输入的命令
	uint16_t line_position;					// 当前命令结束的位置
	uint16_t line_curpos;						// 当前命令输入的位置
} Shell_Info;
Shell_Info shell_info;

/**
  * @brief 记录历史命令
  * @return 无
  */
void Shell_RecordHistory(void) {
	/* 当前输入命令的长度为0，则不记录 */
	if (shell_info.line_position == 0) {
			shell_info.current_history = shell_info.history_count;
			return ;
	}
	/* 确保字符串正确终止 */
	shell_info.line[shell_info.line_position] = '\0';
	
	/* 当前输入命令的长度为0，则不记录 */
	if (shell_info.line_position == 0) {
		shell_info.current_history = shell_info.history_count;
		return ;
	}
	
	/* 存储的历史记录高于上限时 */
	if (shell_info.history_count >= SHELL_HISTORY_LINES) {
		/* 新输入的命令和上一条记录不一样 =》 才会被记录 */
		if (memcmp(&shell_info.cmd_history[SHELL_HISTORY_LINES - 1], shell_info.line, SHELL_CMD_SIZE)) {
			/* 覆盖掉最早的历史记录 */
			int index;
			for (index = 0; index < SHELL_HISTORY_LINES - 1; index ++) {
					memcpy(&shell_info.cmd_history[index][0], &shell_info.cmd_history[index + 1][0], SHELL_CMD_SIZE);
			}
			/* 记录最新的命令 */
			memset(&shell_info.cmd_history[index][0], 0, SHELL_CMD_SIZE);
			memcpy(&shell_info.cmd_history[index][0], shell_info.line, shell_info.line_position);

			shell_info.history_count = SHELL_HISTORY_LINES;
		}
	}
	/* 存储的历史记录低于上限时，直接存储 */
	else {
		/* 历史命令记录为0 or 新输入的命令和上一条记录不一样 =》 才会被记录 */
		if (shell_info.history_count == 0 || memcmp(&shell_info.cmd_history[shell_info.history_count - 1], shell_info.line, SHELL_CMD_SIZE)) {
			shell_info.current_history = shell_info.history_count;
			/* 记录最新的命令 */
			memset(&shell_info.cmd_history[shell_info.history_count][0], 0, SHELL_CMD_SIZE);
			memcpy(&shell_info.cmd_history[shell_info.history_count][0], shell_info.line, shell_info.line_position);

			shell_info.history_count++;
		}
	}
	shell_info.current_history = shell_info.history_count;
}

/**
  * @brief 处理读取历史命令
  * @return 无
  */
void Shell_DealHistory(void) {
	/* 清除当前行的内容 */
	for (int i = 0; i < shell_info.line_position; i++) {
		USART1_SendByte('\b');
	}
	/* 清除整行（包括可能残留的字符） */
	for (int i = 0; i < shell_info.line_position; i++) {
			USART1_SendByte(' ');
	}
	/* 将光标移回行首 */
	for (int i = 0; i < shell_info.line_position; i++) {
			USART1_SendByte('\b');
	}

	/* 复制出历史命令 */
	memcpy(shell_info.line, &shell_info.cmd_history[shell_info.current_history][0], SHELL_CMD_SIZE);
	shell_info.line_curpos = strlen(shell_info.line);
	shell_info.line_position = strlen(shell_info.line);
	
	/* 打印历史命令 */
	USART1_SendString(shell_info.line);
}

/**
  * @brief 处理方向上键操作
  * @return 无
  */
void Shell_DealUpKey(void) {
	if (shell_info.current_history > 0) {
			shell_info.current_history--;
	}
	else {
			shell_info.current_history = 0;
			return ;
	}
	
	Shell_DealHistory();
}

/**
  * @brief 处理方向下键操作
  * @return 无
  */
void Shell_DealDownKey(void) {
	if (shell_info.current_history < shell_info.history_count - 1) {
			shell_info.current_history ++;
	}
	else {
			/* set to the end of history */
			if (shell_info.history_count != 0)
				shell_info.current_history = shell_info.history_count - 1;
			else
				return ;
	}
	
	Shell_DealHistory();
}

/**
  * @brief 处理方向左键操作
  * @return 无
  */
void Shell_DealLeftKey(void) {
	if (shell_info.line_curpos) {
			USART1_SendByte('\b');
			shell_info.line_curpos--;
	}
}

/**
  * @brief 处理方向右键操作
  * @return 无
  */
void Shell_DealRightKey(void) {
	if (shell_info.line_curpos < shell_info.line_position) {
			USART1_SendByte(shell_info.line[shell_info.line_curpos]);
			shell_info.line_curpos++;
	}
}

 
/**
 * @brief 分割命令行参数
 * @param cmd 输入的命令行字符串
 * @param length 命令行长度
 * @param argv 参数数组
 * @return 参数数量
 * 效果：
 * 		输入 "load file.bin 0x8000000"
 * 		输出 argv = ["load", "file.bin", "0x8000000"]
 */
static int Shell_parser_split_param(char *cmd, uint32_t length, char *argv[SHELL_CMD_PARAM_SIZE]) {
	char *ptr = cmd;
	uint32_t position = 0;
	uint32_t argc = 0;

	while (position < length) {
		/* 跳过空格和制表符 */
		while ((*ptr == ' ' || *ptr == '\t') && position < length) {
			*ptr = '\0';
			ptr++;
			position++;
		}

		/* 参数数量超过 FINSH_ARG_MAX 发出警告 */
		if(argc >= SHELL_CMD_PARAM_SIZE) {
			USART1_SendString("Too many args ! We only Use:\n");
			for(uint32_t i = 0; i < argc; i++) {
				USART1_SendString(argv[i]);
			}
			USART1_SendString("\r\n");
			break;
		}
		if (position >= length) break;

		/* 引号包裹的字符串处理 */
		if (*ptr == '"') {
			ptr++;
			position++;
			argv[argc] = ptr;
			argc++;

			/* 跳过整个引号字符串，支持转义 \" */
			while (*ptr != '"' && position < length) {
				if (*ptr == '\\' && *(ptr + 1) == '"') {
					ptr ++;
					position ++;
				}
				ptr++;
				position++;
			}
			if (position >= length) break;

			/* skip '"' */
			*ptr = '\0';
			ptr++;
			position++;
		}
		/* 非引号参数按空格/制表符分割 */
		else {
			argv[argc] = ptr;
			argc++;
			
			while((*ptr != ' ' && *ptr != '\t') && position < length) {
				ptr++;
				position++;
			}
			if (position >= length) break;
		}
	}
	return argc;
}

/**
 * @brief 解析并执行命令
 * @param cmd 输入的命令行字符串
 * @param length 命令行长度
 * @return 执行结果
 */
int Shell_parser_exec(char *cmd, uint32_t length) {
	char cmd_name[SHELL_CMD_NAME_SIZE + 1] = {0};
	command* command_t = NULL;
	char *argv[SHELL_CMD_PARAM_SIZE] = {0};
	int argc = 0;

	/* 跳过命令前的所有空白字符 */
	while ((*cmd == ' ' || *cmd == '\t') && length > 0) {
		cmd++;
		length--;
	}
	if (length == 0) return 0;

	/* 分割整个命令行，包括命令名 */
	argc = Shell_parser_split_param(cmd, length, argv);
	if (argc == 0) return -1;

	/* 从分割结果中获取命令名 */
	strncpy(cmd_name, argv[0], SHELL_CMD_NAME_SIZE);
	cmd_name[SHELL_CMD_NAME_SIZE] = '\0';

	/* 查找命令 */
	command_t = Command_Find(cmd_name);
	if (command_t == NULL) {
		USART1_SendString(cmd_name);
		USART1_SendString(": command not found.");
		return -1;
	}

	/* 执行命令 */
	return command_t->function(argc, argv);
}

void Shell_Run(void) {
	uint8_t ch;
	/* 默认开启回显 */
	shell_info.echo_mode = 1;
	
	USART1_SendString(Shell_Custom_Prompt);
	
	while(1) {
		/* 读取输入字符 */
		if (USART1_GetRxFlag() == 1) {
			ch = USART1_GetRxData();
		} else {
			continue;
		}
		
		/*
		 * 判别方向键
		 * up key  : 0x1b 0x5b 0x41
		 * down key: 0x1b 0x5b 0x42
		 * right key:0x1b 0x5b 0x43
		 * left key: 0x1b 0x5b 0x44
		 */
		if (ch == 0x1b) {
				shell_info.SKey_state = WAIT_SPEC_KEY;
				continue;
		}
		else if (shell_info.SKey_state == WAIT_SPEC_KEY) {
				if (ch == 0x5b) {
						shell_info.SKey_state = WAIT_FUNC_KEY;
						continue;
				}

				shell_info.SKey_state = WAIT_NORMAL;
		}
		else if (shell_info.SKey_state == WAIT_FUNC_KEY) {
				shell_info.SKey_state = WAIT_NORMAL;

				/* up key */
				if (ch == 0x41) {
#if Show_Spectial_Key_Echo == 1
					USART1_SendString("up key");
#endif
					Shell_DealUpKey();
					continue;
				}
				/* down key */
				else if (ch == 0x42) {
#if Show_Spectial_Key_Echo == 1
					USART1_SendString("down key");
#endif
					Shell_DealDownKey();
					continue;
				}
				/* left key */
				else if (ch == 0x44) {
#if Show_Spectial_Key_Echo == 1
					USART1_SendString("left key");
#endif
					Shell_DealLeftKey();					
					continue;
				}
				/* right key */
				else if (ch == 0x43) {
#if Show_Spectial_Key_Echo == 1
					USART1_SendString("right key");
#endif
					Shell_DealRightKey();
					continue;
				}
		}

		/* 收到空值或错误值 */
		if (ch == '\0' || ch == 0xFF){
#if Show_Spectial_Key_Echo == 1
			USART1_SendString("NULL or ERR");
#endif
			continue;
		}
		/* 命令补全（未实现） */
		else if (ch == '\t') {
#if Show_Spectial_Key_Echo == 1
			USART1_SendString("TAB");
#endif
		}
		/* 处理退格键 */
		else if (ch == 0x7f || ch == 0x08) {
#if Show_Spectial_Key_Echo == 1
			USART1_SendString("BACK");
#endif
			
			/* note that shell_info.line_curpos >= 0 */
			if (shell_info.line_curpos == 0)
					continue;

			shell_info.line_position--;
			shell_info.line_curpos--;

			if (shell_info.line_position > shell_info.line_curpos) {
				int i;

				memmove(&shell_info.line[shell_info.line_curpos],
									 &shell_info.line[shell_info.line_curpos + 1],
									 shell_info.line_position - shell_info.line_curpos);
				shell_info.line[shell_info.line_position] = 0;

				//putstr("\b%s  \b", &shell_info.line[shell_info.line_curpos]);
				USART1_SendByte('\b');
				USART1_SendString(&shell_info.line[shell_info.line_curpos]);
				USART1_SendString("  \b");


				/* move the cursor to the origin position */
				for (i = shell_info.line_curpos; i <= shell_info.line_position; i++)
					USART1_SendString("\b");
			}
			else {
					USART1_SendString("\b \b");
					shell_info.line[shell_info.line_position] = 0;
			}

			continue;
		}

		/* 回车 */
		if (ch == '\r' || ch == '\n') {
#if Show_Spectial_Key_Echo == 1
			USART1_SendString("RETURN");
#endif
			Shell_RecordHistory();
			USART1_SendString("\r\n");
			Shell_parser_exec(shell_info.line, shell_info.line_position);
			USART1_SendString(Shell_Custom_Prompt);
			
			if (shell_info.echo_mode) {
				memset(shell_info.line, 0, sizeof(shell_info.line));
				shell_info.line_curpos = shell_info.line_position = 0;
				continue;
			}
		}
		
		/* 命令长度超过上限，移除 */
		if (shell_info.line_position >= SHELL_CMD_SIZE)
				shell_info.line_position = 0;

		/* 输入了普通字符 */
		if (shell_info.line_curpos < shell_info.line_position) {
				int i;

				memmove(&shell_info.line[shell_info.line_curpos + 1],
									 &shell_info.line[shell_info.line_curpos],
									 shell_info.line_position - shell_info.line_curpos);
				shell_info.line[shell_info.line_curpos] = ch;
				if (shell_info.echo_mode)
						USART1_SendString(&shell_info.line[shell_info.line_curpos]);

				/* move the cursor to new position */
				for (i = shell_info.line_curpos; i < shell_info.line_position; i++)
						USART1_SendByte('\b');
		}
		else {
				shell_info.line[shell_info.line_position] = ch;
				if (shell_info.echo_mode)
						USART1_SendByte(ch);
		}

		ch = 0x00;
		shell_info.line_position++;
		shell_info.line_curpos++;
		if (shell_info.line_position >= SHELL_CMD_SIZE) {
				/* clear command line */
				shell_info.line_position = 0;
				shell_info.line_curpos = 0;
		}
		
	}
}
