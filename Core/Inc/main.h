/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "spi.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define KEY_DOWN_Pin GPIO_PIN_0
#define KEY_DOWN_GPIO_Port GPIOA
#define KEY_LEFT_Pin GPIO_PIN_1
#define KEY_LEFT_GPIO_Port GPIOA
#define KEY_RIGHT_Pin GPIO_PIN_2
#define KEY_RIGHT_GPIO_Port GPIOA
#define AS01_NSS_Pin GPIO_PIN_4
#define AS01_NSS_GPIO_Port GPIOA
#define AS01_SCK_Pin GPIO_PIN_5
#define AS01_SCK_GPIO_Port GPIOA
#define AS01_MISO_Pin GPIO_PIN_6
#define AS01_MISO_GPIO_Port GPIOA
#define AS01_MOSI_Pin GPIO_PIN_7
#define AS01_MOSI_GPIO_Port GPIOA
#define LED1_Pin GPIO_PIN_0
#define LED1_GPIO_Port GPIOB
#define LED2_Pin GPIO_PIN_1
#define LED2_GPIO_Port GPIOB
#define AS01_CE_Pin GPIO_PIN_10
#define AS01_CE_GPIO_Port GPIOB
#define AS01_IRQ_Pin GPIO_PIN_11
#define AS01_IRQ_GPIO_Port GPIOB
#define BUZZER_Pin GPIO_PIN_5
#define BUZZER_GPIO_Port GPIOB
#define OLED_SCL_Pin GPIO_PIN_6
#define OLED_SCL_GPIO_Port GPIOB
#define OLED_SDA_Pin GPIO_PIN_7
#define OLED_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define AS01_SPI hspi1

#define LED1_OUTPUT(x) HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, (GPIO_PinState)(x))
#define LED2_OUTPUT(x) HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, (GPIO_PinState)(x))
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
