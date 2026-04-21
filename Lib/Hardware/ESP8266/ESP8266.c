#include "esp8266.h"
#include "string.h"
#include "stdio.h"
#include "delay.h"
#include "USART1.h"

// ===== 配置 =====
#define RX_BUFFER_SIZE 512
#define LINE_BUFFER_SIZE 128

// ===== 环形缓冲区 =====
typedef struct {
    char buf[RX_BUFFER_SIZE];
    volatile uint16_t head;
    volatile uint16_t tail;
} RingBuffer;

static RingBuffer rx_rb;

/**
  * @brief 清空缓冲区
  * @return 无
  */
void ESP_ClearBuffer(void)
{
    rx_rb.head = 0;
    rx_rb.tail = 0;
    memset(rx_rb.buf, 0, RX_BUFFER_SIZE);
}

/**
  * @brief 发送AT指令
  * @return 无
  */
static void ESP_SendCmd(char *cmd)
{
    USART1_SendString(cmd);
    USART1_SendString("\r\n");
}

// ===== 读取一行 =====
static int RB_ReadLine(char *line, int max_len)
{
    int i = 0;

    while (rx_rb.tail != rx_rb.head)
    {
        char c = rx_rb.buf[rx_rb.tail];
        rx_rb.tail = (rx_rb.tail + 1) % RX_BUFFER_SIZE;

        if (c == '\n')
        {
            line[i] = '\0';
            return 1;
        }

        if (c != '\r') // 过滤 \r
        {
            if (i < max_len - 1)
                line[i++] = c;
        }
    }

    return 0;
}

/**
  * @brief 等待响应（按行）
  * @param target  目标字段
  * @param timeout 超时时间
  * @return 无
  */
uint8_t ESP_WaitResponse(char *target, uint32_t timeout)
{
    char line[LINE_BUFFER_SIZE];
    uint32_t t = 0;

    while (t < timeout)
    {
        if (RB_ReadLine(line, sizeof(line)))
        {
            // printf("DBG: %s\r\n", line); // 调试用

            if (strstr(line, target))
                return 1;

            if (strstr(line, "ERROR"))
                return 0;
        }

        Delay_ms(10);
        t += 10;
    }

    return 0;
}

/**
  * @brief USART1 中断
  * @return 无
  */
void USART1_IRQHandler(void)
{
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        uint8_t data = USART_ReceiveData(USART1);

        uint16_t next = (rx_rb.head + 1) % RX_BUFFER_SIZE;

        // 防止溢出
        if (next != rx_rb.tail)
        {
            rx_rb.buf[rx_rb.head] = data;
            rx_rb.head = next;
        }

        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }
}

uint8_t ESP8266_Init(void)
{
    char cmd[128];
    ESP_ClearBuffer();

    ESP_SendCmd("AT");
    if (!ESP_WaitResponse("OK", 1000)) return 0;

    ESP_SendCmd("ATE0");
    if (!ESP_WaitResponse("OK", 1000)) return 0;

    ESP_SendCmd("AT+CWMODE=1");
    if (!ESP_WaitResponse("OK", 1000)) return 0;

    sprintf(cmd, "AT+CWJAP=\"%s\",\"%s\"", WIFI_ACCOUNT, WIFI_PASSWORD);
    ESP_SendCmd(cmd);
    if (!ESP_WaitResponse("WIFI GOT IP", 10000)) return 0;

    return 1;
}

uint8_t ESP8266_Reset(void) {
    ESP_ClearBuffer();

    ESP_SendCmd("AT+RST");
    if (!ESP_WaitResponse("ready", 1000)) return 0;

    return 1;
}

uint8_t ESP8266_GetIP(char *ip)
{
    char line[LINE_BUFFER_SIZE];

    ESP_ClearBuffer();
    ESP_SendCmd("AT+CIFSR");

    uint32_t t = 0;

    while (t < 3000)
    {
        if (RB_ReadLine(line, sizeof(line)))
        {
            // 找 IP 行
            if (strstr(line, "STAIP"))
            {
                char *start = strchr(line, '\"');
                char *end = strrchr(line, '\"');

                if (start && end && end > start)
                {
                    int len = end - start - 1;
                    strncpy(ip, start + 1, len);
                    ip[len] = '\0';
                }
            }

            // 结束标志
            if (strstr(line, "OK"))
                return 1;

            if (strstr(line, "ERROR"))
                return 0;
        }

        Delay_ms(10);
        t += 10;
    }

    return 0;
}

uint8_t ESP8266_MQTT_Init(void)
{
    char cmd[128];

    // ===== 防止脏状态=====
    ESP_ClearBuffer();
    ESP_SendCmd("AT+MQTTCLEAN=0");
    ESP_WaitResponse("OK", 1000);

    // ===== MQTT USERCFG =====
    ESP_ClearBuffer();
    sprintf(cmd,
        "AT+MQTTUSERCFG=0,1,\"%s\",\"%s\",\"%s\",0,0,\"\"",
        MQTT_Client_NAME,
        MQTT_USERNAME,
        MQTT_PASSWORD
    );
    ESP_SendCmd(cmd);
    if (!ESP_WaitResponse("OK", 1000)) return 0;

    // ===== MQTT连接=====
    ESP_ClearBuffer();
    sprintf(cmd,
        "AT+MQTTCONN=0,\"%s\",%d,0",
        MQTT_SERVER_IP,
        MQTT_SERVER_PORT
    );
    ESP_SendCmd(cmd);
    if (!ESP_WaitResponse("OK", 1000)) return 0;

    return 1;
}

uint8_t ESP_MQTTPublish(char *topic, char *json)
{
    char cmd[128];

    sprintf(cmd, "AT+MQTTPUBRAW=0,\"%s\",%d,0,0", topic, strlen(json));
    ESP_SendCmd(cmd);
    // 等待 '>'
    Delay_ms(100);
    
    USART1_SendString(json);

    // 等待发布成功
    return ESP_WaitResponse("+MQTTPUB:OK", 2000);
}
