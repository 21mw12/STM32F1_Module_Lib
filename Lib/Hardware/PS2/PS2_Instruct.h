#ifndef __PS2_INSTRUCT_H
#define __PS2_INSTRUCT_H

///////////////////////////////////////////////////////////
//
// 文件功能：PS2指令文件
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2023/12/30
//
///////////////////////////////////////////////////////////

#define PS2_DUMMY_BYTE							0xFF

/* PS2手柄命令 */
#define PS2_START_CMD								0x01  // 开始命令
#define PS2_ASK_DATA_CMD						0x42  // 请求数据

/* PS2手柄模式 */
#define PS2_RED_MODE_INSTRUCT				0x73	// 红灯模式
#define PS2_GREEN_MODE_INSTRUCT			0x41	// 绿灯模式

#endif
