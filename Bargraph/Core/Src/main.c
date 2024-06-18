/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
/* USER CODE BEGIN PFP */
void desligaLeds();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void desligaLeds(){
	HAL_GPIO_WritePin(GPIOA, LED_UM_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, LED_DOIS_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, LED_TRES_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, LED_QUATRO_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, LED_CINCO_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, LED_SEIS_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, LED_SETE_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, LED_OITO_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, LED_NOVE_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, LED_DEZ_Pin, GPIO_PIN_RESET);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
  uint32_t leituraPotenciometro = HAL_ADC_GetValue(&hadc1);
  int ledCount = leituraPotenciometro * 10 / 4095; // 10 LEDs e 2^12-1
  desligaLeds();
  if(ledCount >= 1) HAL_GPIO_WritePin(GPIOA, LED_UM_Pin, GPIO_PIN_SET);
  if(ledCount >= 2) HAL_GPIO_WritePin(GPIOA, LED_DOIS_Pin, GPIO_PIN_SET);
  if(ledCount >= 3) HAL_GPIO_WritePin(GPIOA, LED_TRES_Pin, GPIO_PIN_SET);
  if(ledCount >= 4) HAL_GPIO_WritePin(GPIOA, LED_QUATRO_Pin, GPIO_PIN_SET);
  if(ledCount >= 5) HAL_GPIO_WritePin(GPIOA, LED_CINCO_Pin, GPIO_PIN_SET);
  if(ledCount >= 6) HAL_GPIO_WritePin(GPIOA, LED_SEIS_Pin, GPIO_PIN_SET);
  if(ledCount >= 7) HAL_GPIO_WritePin(GPIOA, LED_SETE_Pin, GPIO_PIN_SET);
  if(ledCount >= 8) HAL_GPIO_WritePin(GPIOA, LED_OITO_Pin, GPIO_PIN_SET);
  if(ledCount >= 9) HAL_GPIO_WritePin(GPIOB, LED_NOVE_Pin, GPIO_PIN_SET);
  if(ledCount >= 10) HAL_GPIO_WritePin(GPIOB, LED_DEZ_Pin, GPIO_PIN_SET);
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* MCU Configuration--------------------------------------------------------*/
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  /* Configure the system clock */
  SystemClock_Config();
  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
  HAL_ADCEx_Calibration_Start(&hadc1); // Rotina de calibração do ADC
  /* USER CODE END 2 */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    /* USER CODE BEGIN 3 */
	HAL_ADC_Start_IT(&hadc1); // Inicia ADC interrupcao
  }
  /* USER CODE END 3 */
}


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}


/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.LowPowerAutoPowerOff = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc1.Init.SamplingTimeCommon1 = ADC_SAMPLETIME_1CYCLE_5;
  hadc1.Init.SamplingTimeCommon2 = ADC_SAMPLETIME_1CYCLE_5;
  hadc1.Init.OversamplingMode = DISABLE;
  hadc1.Init.TriggerFrequencyMode = ADC_TRIGGER_FREQ_HIGH;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_8;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLINGTIME_COMMON_1;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED_DEZ_Pin|LED_NOVE_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_OITO_Pin|LED_SETE_Pin|LED_SEIS_Pin|LED_CINCO_Pin
                          |LED_QUATRO_Pin|LED_TRES_Pin|LED_DOIS_Pin|LED_UM_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED_DEZ_Pin LED_NOVE_Pin */
  GPIO_InitStruct.Pin = LED_DEZ_Pin|LED_NOVE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_OITO_Pin LED_SETE_Pin LED_SEIS_Pin LED_CINCO_Pin
                           LED_QUATRO_Pin LED_TRES_Pin LED_DOIS_Pin LED_UM_Pin */
  GPIO_InitStruct.Pin = LED_OITO_Pin|LED_SETE_Pin|LED_SEIS_Pin|LED_CINCO_Pin
                          |LED_QUATRO_Pin|LED_TRES_Pin|LED_DOIS_Pin|LED_UM_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
