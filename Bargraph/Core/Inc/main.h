/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32c0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
#define LED_DEZ_Pin GPIO_PIN_7
#define LED_DEZ_GPIO_Port GPIOB
#define LED_OITO_Pin GPIO_PIN_0
#define LED_OITO_GPIO_Port GPIOA
#define LED_SETE_Pin GPIO_PIN_1
#define LED_SETE_GPIO_Port GPIOA
#define LED_SEIS_Pin GPIO_PIN_2
#define LED_SEIS_GPIO_Port GPIOA
#define LED_CINCO_Pin GPIO_PIN_3
#define LED_CINCO_GPIO_Port GPIOA
#define LED_QUATRO_Pin GPIO_PIN_4
#define LED_QUATRO_GPIO_Port GPIOA
#define LED_TRES_Pin GPIO_PIN_5
#define LED_TRES_GPIO_Port GPIOA
#define LED_DOIS_Pin GPIO_PIN_6
#define LED_DOIS_GPIO_Port GPIOA
#define LED_UM_Pin GPIO_PIN_7
#define LED_UM_GPIO_Port GPIOA
#define LED_NOVE_Pin GPIO_PIN_6
#define LED_NOVE_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
