#ifndef __W25QXX_REGISTER_H
#define __W25QXX_REGISTER_H

///////////////////////////////////////////////////////////
//
// 文件功能：MPU6050相关寄存器
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2023/12/27
//
///////////////////////////////////////////////////////////

#define W25QXX_WRITE_ENABLE												0x06
#define W25QXX_WRITE_DISABLE											0x04
#define W25QXX_READ_STATUS_REGISTER_1							0x05
#define W25QXX_READ_STATUS_REGISTER_2							0x35
#define W25QXX_WRITE_STATUS_REGISTER							0x01
#define W25QXX_PAGE_PROGRAM												0x02
#define W25QXX_QUAD_PAGE_PROGRAM									0x32
#define W25QXX_BLOCK_ERASE_64KB										0xD8
#define W25QXX_BLOCK_ERASE_32KB										0x52
#define W25QXX_SECTOR_ERASE_4KB										0x20
#define W25QXX_CHIP_ERASE													0xC7
#define W25QXX_ERASE_SUSPEND											0x75
#define W25QXX_ERASE_RESUME												0x7A
#define W25QXX_POWER_DOWN													0xB9
#define W25QXX_HIGH_PERFORMANCE_MODE							0xA3
#define W25QXX_CONTINUOUS_READ_MODE_RESET					0xFF
#define W25QXX_RELEASE_POWER_DOWN_HPM_DEVICE_ID		0xAB
#define W25QXX_MANUFACTURER_DEVICE_ID							0x90
#define W25QXX_READ_UNIQUE_ID											0x4B
#define W25QXX_JEDEC_ID														0x9F
#define W25QXX_READ_DATA													0x03
#define W25QXX_FAST_READ													0x0B
#define W25QXX_FAST_READ_DUAL_OUTPUT							0x3B
#define W25QXX_FAST_READ_DUAL_IO									0xBB
#define W25QXX_FAST_READ_QUAD_OUTPUT							0x6B
#define W25QXX_FAST_READ_QUAD_IO									0xEB
#define W25QXX_OCTAL_WORD_READ_QUAD_IO						0xE3

#define W25QXX_DUMMY_BYTE													0xFF

#endif
