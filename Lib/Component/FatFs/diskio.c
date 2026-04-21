/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2016        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		/* FatFs lower layer API */
#include "sdio_sd.h"

#define SD_Card		0	//SD卡 
#define SPI_Flash		1	//SPI Flash

#define SD_BLOCKSIZE     512 
extern  SD_CardInfo SDCardInfo;

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat = STA_NOINIT;

	switch (pdrv) {
		
		case SD_Card :
			stat &= ~STA_NOINIT;
			return stat;

		case SPI_Flash :
			return stat;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat = STA_NOINIT;

	switch (pdrv) {
		
		case SD_Card :
			if( SD_Init()==SD_OK )	//SD卡初始化
			{
				stat &= ~STA_NOINIT;
				return stat;
			}

		case SPI_Flash :
			return stat;

	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	SD_Error SD_state = SD_OK;

	switch (pdrv) {
		
		case SD_Card:		
			SD_state=SD_ReadMultiBlocks(buff,sector*SD_BLOCKSIZE,SD_BLOCKSIZE,count);
			if(SD_state==SD_OK)
			{
				SD_state=SD_WaitReadOperation();
				while(SD_GetStatus() != SD_TRANSFER_OK);
			}
			if(SD_state==SD_OK)
				return RES_OK;
			else
				return RES_PARERR;			

		case SPI_Flash :
			return RES_PARERR;
	}
	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	SD_Error SD_state = SD_OK;

	switch (pdrv) {
		
		case SD_Card:						
			SD_state=SD_WriteMultiBlocks((uint8_t *)buff,sector*SD_BLOCKSIZE,SD_BLOCKSIZE,count);
			if(SD_state==SD_OK)
			{
				SD_state=SD_WaitWriteOperation();
				while(SD_GetStatus() != SD_TRANSFER_OK);		

				if(SD_state==SD_OK)
					return RES_OK;
				else
					return RES_PARERR;
			}
					
		case SPI_Flash :
			return RES_PARERR;
	}
	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res = RES_PARERR;

	switch (pdrv) {
		case SD_Card :
			switch (cmd) 
			{
				case GET_SECTOR_COUNT:
					*(DWORD * )buff = SDCardInfo.CardCapacity/SD_BLOCKSIZE;
					break;				
				
				// Get R/W sector size (WORD) 
				case GET_SECTOR_SIZE :    
					*(WORD * )buff = SD_BLOCKSIZE;
				break;
				
				// Get erase block size in unit of sector (DWORD)
				case GET_BLOCK_SIZE :      
					*(DWORD * )buff = SD_BLOCKSIZE;
				break;

			}
			return  RES_OK;

		case SPI_Flash :
			return res;
	}
	return RES_PARERR;
}
/*-----------------------------------------------------------------------*/
/* 时间获取函数，在这里不使用，返回0                                      */
/*-----------------------------------------------------------------------*/
DWORD get_fattime(void) {

	return 0;

}
