#include "sys.h"

void System_Reset(void)
{
    __set_FAULTMASK(1); // disable all interrupts
    HAL_NVIC_SystemReset();
}

void HAL_Delay_us(__IO uint32_t delay)
{
    uint32_t ticks;
    uint32_t told, tnow, reload, tcnt = 0;

    reload = SysTick->LOAD;                      //获取重装载寄存器值
    ticks = delay * (SystemCoreClock / 1000000); //计数时间值   括号里的代表1us秒嘀嗒定时器的value会向下降多少值
    told = SysTick->VAL;                         //获取当前数值寄存器值（开始时数值）

    while (1)
    {
        tnow = SysTick->VAL; //获取当前数值寄存器值
        if (tnow != told)    //当前值不等于开始值说明已在计数
        {
            if (tnow < told)                  //当前值小于开始数值，说明未计到0
                tcnt += told - tnow;          //计数值=开始值-当前值
            else                              //当前值大于开始数值，说明已计到0并重新计数
                tcnt += reload - tnow + told; //计数值=重装载值-当前值+开始值（已从开始值计到0）
            told = tnow;                      //更新开始值
            if (tcnt >= ticks)
                break; //时间超过/等于要延迟的时间,则退出.
        }
    }
}

uint8_t Flash_Erase(void)
{
    static uint32_t PageError;
    FLASH_EraseInitTypeDef erase_init;
    erase_init.TypeErase = FLASH_TYPEERASE_PAGES;
    erase_init.PageAddress = FLASH_START_ADDR;
    erase_init.NbPages = (FLASH_END_ADDR - FLASH_START_ADDR) / FLASH_PAGE_SIZE;
    HAL_FLASH_Unlock();
    if (HAL_FLASHEx_Erase(&erase_init, &PageError) != HAL_OK)
    {
        HAL_FLASH_Lock();
        return 1;
    }
    return 0;
}

uint8_t Flash_Write(uint32_t address, uint32_t *data, uint16_t size)
{
    if (Flash_Erase())
        return 1;

    HAL_FLASH_Unlock();
    for (uint16_t i = 0; i < size; i++)
    {
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address + (i * sizeof(uint32_t)), data[i]) != HAL_OK)
        {
            HAL_FLASH_Lock();
            return 1;
        }
    }
    HAL_FLASH_Lock();
    return 0;
}

void Flash_Read(uint32_t address, uint32_t *data, uint16_t size)
{
    for (uint16_t i = 0; i < size; i++)
    {
        data[i] = *((__IO uint32_t *)address + i);
    }
}

uint8_t ADD8_Calculation(uint8_t *array, uint16_t size)
{
    uint8_t i, add = 0;
    for (i = 0; i < size; i++)
    {
        add += array[i];
    }
    array[size] = add;
    return add;
}

uint8_t ADD8_Check(uint8_t *array, uint16_t size)
{
    uint8_t add = 0;
    for (uint8_t i = 0; i < size - 1; i++)
    {
        add += array[i];
    }
    if (add == array[size - 1])
        return 0;
    else
        return 1;
}

uint16_t CRC_Calculation(uint8_t *data, uint16_t size)
{
    uint16_t i, crc = 0xFFFF;

    for (i = 0; i < size; i++)
    {
        crc ^= data[i];
        for (uint8_t j = 0; j < 8; j++)
        {
            if (crc & 0x0001)
            {
                crc >>= 1;
                crc ^= 0xA001;
            }
            else
            {
                crc >>= 1;
            }
        }
    }
    data[size] = crc;
    data[size + 1] = crc >> 8;
    return crc;
}

uint8_t CRC_Check(uint8_t *data, uint16_t size)
{
    uint16_t crc = (uint16_t)data[size - 1] << 8;
    crc |= data[size - 2];

    if (crc == CRC_Calculation(data, size - 2))
        return 0;
    else
        return 1;
}
