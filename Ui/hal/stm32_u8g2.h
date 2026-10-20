//
// Created by crysd on 2026/10/19.
//

#ifndef STM32F103BOARD_STM32_U8G2_H
#define STM32F103BOARD_STM32_U8G2_H

#include "u8g2.h"

#define MAX_LEN    128  //
#define OLED_ADDRESS  0x78 // oled
#define OLED_CMD   0x00  //
#define OLED_DATA  0x40  //

#ifdef __cplusplus
extern "C" {
#endif

uint8_t u8x8_byte_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
uint8_t u8x8_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
void u8g2Init(u8g2_t *u8g2);
void draw(u8g2_t *u8g2);
void testDrawPixelToFillScreen(u8g2_t *u8g2);

#ifdef __cplusplus
}
#endif

#endif //STM32F103BOARD_STM32_U8G2_H
