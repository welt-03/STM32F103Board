#ifndef __SYS_H__
#define __SYS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stm32f1xx_hal.h>

#define ENABLE_OS_SUPPORT 0

#if ENABLE_OS_SUPPORT == 1
#include "FreeRTOS.h"
#include "task.h"

#define delay_ms(x) vTaskDelay(x / portTICK_RATE_MS)
#else
#define delay_ms(x) HAL_Delay(x)
#endif
#define delay_us(x) HAL_Delay_us(x)

/* flash写入地址 */
#define FLASH_START_ADDR (FLASH_BASE + (FLASH_PAGE_SIZE * 63)) // flash写入起始地址
#define FLASH_END_ADDR (FLASH_BASE + (FLASH_PAGE_SIZE * 64)) // flash写入结束地址

/* bit操作 */
#define BIT_SET(REG, BIT) ((REG) |= (1 << (BIT)))
#define BIT_CLEAR(REG, BIT) ((REG) &= ~(1 << (BIT)))
#define BIT_READ(REG, BIT) ((REG >> (BIT)) & 1)
#define REG_MODIFY(REG, MASK, VAL) ((REG) = ((REG) & ~(MASK)) | (VAL))

    void System_Reset(void);
    /**
     * @brief HAL微妙延时函数
     * @param delay
     */
    void HAL_Delay_us(__IO uint32_t delay);
    /**
     * @brief 擦除内部FALSH
     * @note 0: 成功 1: 失败
     * @return uint8_t
     */
    uint8_t Flash_Erase();
    /**
     * @brief 写内部FLASH
     * @note 0: 成功 1: 失败
     * @param address   起始地址
     * @param data      数据地址
     * @param length    数据长度
     * @return uint8_t
     */
    uint8_t Flash_Write(uint32_t address, uint32_t *data, uint16_t size);
    /**
     * @brief 读内部FLASH
     * @param address   起始地址
     * @param data      数据地址
     * @param length    数据长度
     */
    void Flash_Read(uint32_t address, uint32_t *data, uint16_t size);
    /**
     * @brief 计算校验和并追加到数据尾部
     *
     * @param array
     * @param size
     * @return uint8_t
     */
    uint8_t ADD8_Calculation(uint8_t *array, uint16_t size);

    /**
     * @brief 校验和
     * @note 0: 成功 1: 失败
     * @param array
     * @param size
     * @return uint8_t
     */
    uint8_t ADD8_Check(uint8_t *array, uint16_t size);

    /**
     * @brief 计算CRC16并追加到数据尾部
     *
     * @param data
     * @param size
     * @return uint16_t
     */
    uint16_t CRC_Calculation(uint8_t *data, uint16_t size);

    /**
     * @brief 校验CRC16
     * @note 0: 成功 1: 失败
     * @param data
     * @param size
     * @return uint8_t
     */
    uint8_t CRC_Check(uint8_t *data, uint16_t size);
#ifdef __cplusplus
}
#endif

#endif