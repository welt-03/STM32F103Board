//
// Created by Fir on 2024/2/12.
//
#include "../hal_dreamCore.h"
#include "main.h"
#include "dma.h"
#include "spi.h"
#include "gpio.h"

void HALDreamCore::_stm32_hal_init() { //NOLINT
  HAL_Init();
}

void HALDreamCore::_sys_clock_init() { //NOLINT
	
}

void HALDreamCore::_gpio_init() { //NOLINT

}

void HALDreamCore::_timer_init() { //NOLINT

}

void HALDreamCore::_spi_init() { //NOLINT

}

void HALDreamCore::_dma_init() { //NOLINT

}

void HALDreamCore::_adc_init() { //NOLINT

}

void HALDreamCore::_delay(unsigned long _mill) {
  HAL_Delay(_mill);
}

unsigned long HALDreamCore::_millis() {
  return HAL_GetTick();
}

unsigned long HALDreamCore::_getTick() {
  return (uwTick * 1000 + (SysTick->LOAD - SysTick->VAL) / (SystemCoreClock/1000000U));
}

unsigned long HALDreamCore::_getRandomSeed() {
  static uint32_t seed = 0;
  
  return seed;
}



