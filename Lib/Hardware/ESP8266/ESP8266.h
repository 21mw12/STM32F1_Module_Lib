#ifndef __ESP8266_H
#define __ESP8266_H

///////////////////////////////////////////////////////////
//
// 文件功能：ESP8266 AT指令功能
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2026/04/21
//
///////////////////////////////////////////////////////////

#include "stm32f10x.h"

/* WIFI配置 */
#define WIFI_ACCOUNT        "your wifi name"
#define WIFI_PASSWORD       "your wifi password"

/* MQTT配置 */
#define MQTT_Client_NAME    "mqtt device name"
#define MQTT_SERVER_IP      "mqtt server ip address"
#define MQTT_SERVER_PORT    1883
#define MQTT_USERNAME       ""
#define MQTT_PASSWORD       ""

/**
  * @brief ESP8266初始化（WiFi连接）
  * @return 是否成功
  */
uint8_t ESP8266_Init(void);

/**
  * @brief ESP8266重启
  * @return 是否成功
  */
uint8_t ESP8266_Reset(void);

/**
  * @brief ESP8266获取IP地址
  * @return 是否成功
  */
uint8_t ESP8266_GetIP(char *ip);

/**
  * @brief ESP8266初始化MQTT
  * @return 是否成功
  */
uint8_t ESP8266_MQTT_Init(void);

/**
  * @brief ESP8266初始化MQTT
  * @param topic 主题
  * @param json 消息（支持JSON格式）
  * @return 是否成功
  */
uint8_t ESP_MQTTPublish(char *topic, char *json);

#endif
