//
// Created by crysd on 2026/10/19.
//

#include "task.h"
#include "main.h"
#include "usart.h"
#include "stream.h"
#include "stm32_u8g2.h"


static u8g2_t oled;
static StreamProcessor Serial(&huart1);

void SystemClock_Config(void);
void StreamOutCallback(uint8_t *data, uint16_t size, void *handle);
void SerialRunCallback(void *handle);

void MainTask(void)
{
    u8g2Init(&oled);

    Serial.RegisterStreamOutCallback(StreamOutCallback);
    Serial.RegisterStreamRunCallback(SerialRunCallback);
    HAL_UARTEx_ReceiveToIdle_DMA((UART_HandleTypeDef *)Serial.GetHandle(), Serial.payload_, DEFAULT_STREAM_PAYLOAD_SIZE);

    for (;;)
    {
        Serial.Run();
        LED1_OUTPUT(1);
        delay_ms(200);
        LED1_OUTPUT(0);
        delay_ms(200);
    }
}

void StreamOutCallback(uint8_t *data, uint16_t size, void *handle)
{
    HAL_UART_Transmit_DMA((UART_HandleTypeDef *)handle, data, size);
}

void SerialRunCallback(void *handle)
{
    Serial.Print(Serial.payload_, Serial.size_);
    HAL_UARTEx_ReceiveToIdle_DMA((UART_HandleTypeDef *)handle, Serial.payload_, DEFAULT_STREAM_PAYLOAD_SIZE);
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    if (huart == Serial.GetHandle())
    {
        Serial.ReceiveComplete(Size);
    }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart == Serial.GetHandle())
    {
        Serial.SendComplete();
    }
}

// void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c)
// {
//     // to do
// }