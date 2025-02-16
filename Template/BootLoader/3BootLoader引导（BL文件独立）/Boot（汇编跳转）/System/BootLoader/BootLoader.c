#include "BootLoader.h"

/* APP头部信息结构体 */
typedef struct image_header {
    uint32_t		ih_magic;
    uint32_t		ih_hcrc;
    uint32_t		ih_time;
    uint32_t		ih_size;
    uint32_t		ih_load;
    uint32_t		ih_ep;
    uint32_t		ih_dcrc;
    uint8_t			ih_os;
    uint8_t			ih_arch;
    uint8_t			ih_type;
    uint8_t			ih_comp;
    uint8_t			ih_name[32];
} image_header_t;

/**
  * @brief 32位大端转小端
  * @param be32 32位大端数据
  * @return 32位小端数据
  */
uint32_t be32_to_le32(uint32_t be32) {
	uint32_t le32;
	
	uint8_t* p = (uint8_t*) &be32;
	le32 = (p[0] << 24) + (p[1] << 16) + (p[2] << 8) + p[3];
	return le32;
}

/**
  * @brief APP启动（汇编编写 startup_stm32f10x_md.s）
  * @param App_Vector　APP的烧录起始地址
  */
extern void App_Start(uint32_t App_Vector);

/**
  * @brief 将APP程序拷贝到内存
  * @param from 起始地址
  * @param to 目标地址
  * @param len 拷贝长度
  */
void APP_CopyToRAM(uint32_t* from, uint32_t* to, uint32_t len) {
	int i = 0;
	
	for (i = 0; i < len/4+1; i++) {
		to[i] = from[i];
	}
}

void BootLoader_LoadAPP(uint32_t App_Vector) {
	image_header_t* head;
	uint32_t target = App_Vector + sizeof(image_header_t);
	uint32_t load;
	uint32_t size;
	
	/* 读出头部 */
	head = (image_header_t*)App_Vector;
	
	/* 解析头部 */
	load = be32_to_le32(head->ih_load);
	size = be32_to_le32(head->ih_size);
	
	/* 把程序复制到ROM */
	APP_CopyToRAM((uint32_t*)target, (uint32_t*)load, size);
	
	/* 跳转执行 */
	App_Start(target);
}
