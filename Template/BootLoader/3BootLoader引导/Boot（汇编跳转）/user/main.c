#include "stm32f10x.h"
#include "LED.h"

typedef uint32_t __be32;
#define IH_NMLAN		32

typedef struct image_header {
    __be32		ih_magic;
    __be32		ih_hcrc;
    __be32		ih_time;
    __be32		ih_size;
    __be32		ih_load;
    __be32		ih_ep;
    __be32		ih_dcrc;
    uint8_t		ih_os;
    uint8_t		ih_arch;
    uint8_t		ih_type;
    uint8_t		ih_comp;
    uint8_t		ih_name[IH_NMLAN];
} image_header_t;

/* 参数为APP的烧录起始地址 */
extern void App_Start(uint32_t App_Vector);

void APP_CopyToRAM(uint32_t* from, uint32_t* to, uint32_t len) {
	int i = 0;
	
	for (i = 0; i < len/4+1; i++) {
		to[i] = from[i];
	}
}

uint32_t be32_to_le32(uint32_t be32) {
	uint32_t le32;
	
	uint8_t* p = (uint8_t*) &be32;
	le32 = (p[0] << 24) + (p[1] << 16) + (p[2] << 8) + p[3];
	return le32;
}

void App_Load(uint32_t App_Vector) {
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

int main(void) {	
	LED_Init();
	LED_Flash(200);
	
	App_Load(0x08005000);
	
	return 0;
}
