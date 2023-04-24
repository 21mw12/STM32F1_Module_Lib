#include "stm32f10x.h"
#include "delay.h"

///////////////////////////////////////////////////////////
//
// 文件功能：软件模拟I2C的基础功能
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2023/04/21
//
///////////////////////////////////////////////////////////

/* I2C默认的端口信息 */
#define I2C_PORT		GPIOB
#define SCL_PIN			GPIO_Pin_8
#define SDA_PIN			GPIO_Pin_9

/**
  * @brief  SCL写数据
  * @param  state ： 数据内容
  * @retval 无
  */
void SCL_Write(uint8_t state);

/**
  * @brief  SDA写数据
  * @param  state ： 数据内容
  * @retval 无
  */
void SDA_Write(uint8_t state);

/**
  * @brief  SDA读数据
  * @retval 读取到的数据
  */
uint8_t SDA_Read(void);

/**
  * @brief  I2C开始
  * @param  GPIOx ： IO端口组
  * @param  GPIO_Pin ： IO端口
  * @retval 无
  */
void I2C_Start(void);

/**
  * @brief  I2C停止
  * @param  GPIOx ： IO端口组
  * @param  GPIO_Pin ： IO端口
  * @retval 无
  */
void I2C_Stop(void);

/**
  * @brief  I2C发送一个字节
  * @param  Byte 要发送的一个字节
  * @retval 无
  */
void I2C_SendByte(uint8_t Byte);

/**
  * @brief  I2C接收一个字节
  * @retval 接收到的数据
  */
uint8_t I2C_ReceiveByte(void);

/**
  * @brief  发送应答
  * @param  应答信息
  * @retval 无
  */
void I2C_SendAck(uint8_t AckBit);

/**
  * @brief  接收应答
  * @retval 应答信息
  */
uint8_t I2C_ReceiveAck(void);
