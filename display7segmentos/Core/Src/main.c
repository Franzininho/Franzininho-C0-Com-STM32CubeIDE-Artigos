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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
void numero(uint32_t a, uint32_t b,uint32_t c,uint32_t d,uint32_t e, uint32_t f, uint32_t g);
void atualizaDisplay(int valor);
int debounceBotao(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
  int valor = 0;
  atualizaDisplay(valor);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    /* USER CODE BEGIN 3 */
	 if (debounceBotao(GPIOB, SOMA_Pin)){
         valor = (valor + 1) % 10; //assegurar que permaneça dentro do intervalo de 0 a 9
		 atualizaDisplay(valor);
	 }

	 if (debounceBotao(GPIOB, SUBTRAI_Pin)){
		  valor = (valor - 1 + 10) % 10; //assegurar que permaneça dentro do intervalo de 0 a 9
		  atualizaDisplay(valor);
	 }
  }
  /* USER CODE END 3 */
}

void numero(uint32_t a, uint32_t b,uint32_t c,uint32_t d,uint32_t e, uint32_t f, uint32_t g){
	HAL_GPIO_WritePin(GPIOA, A_Pin, a);
	HAL_GPIO_WritePin(GPIOA, B_Pin, b);
	HAL_GPIO_WritePin(GPIOA, C_Pin, c);
	HAL_GPIO_WritePin(GPIOA, D_Pin, d);
	HAL_GPIO_WritePin(GPIOA, E_Pin, e);
	HAL_GPIO_WritePin(GPIOA, F_Pin, f);
	HAL_GPIO_WritePin(GPIOA, G_Pin, g);
}

void atualizaDisplay(int valor)
{
    // Configurações dos segmentos para cada dígito de 0 a 9
    switch(valor)
    {
        case 0: numero(1, 1, 1, 1, 1, 1, 0); break;
        case 1: numero(0, 1, 1, 0, 0, 0, 0); break;
        case 2: numero(1, 1, 0, 1, 1, 0, 1); break;
        case 3: numero(1, 1, 1, 1, 0, 0, 1); break;
        case 4: numero(0, 1, 1, 0, 0, 1, 1); break;
        case 5: numero(1, 0, 1, 1, 0, 1, 1); break;
        case 6: numero(1, 0, 1, 1, 1, 1, 1); break;
        case 7: numero(1, 1, 1, 0, 0, 0, 0); break;
        case 8: numero(1, 1, 1, 1, 1, 1, 1); break;
        case 9: numero(1, 1, 1, 1, 0, 1, 1); break;
    }
}

int debounceBotao(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    uint32_t debounce_inicio = HAL_GetTick();
    // Aguarda até que o botão seja liberado
    while (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == GPIO_PIN_RESET)
    {
        if (HAL_GetTick() - debounce_inicio >= 50) // Espera 50ms
        {
            // Botão pressionado por tempo suficiente
            while (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == GPIO_PIN_RESET); // Espera o botão ser solto
            return 1; // Retorna verdadeiro
        }
    }

    return 0; // Retorna falso se o botão não foi pressionado por tempo suficiente
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
  HAL_GPIO_WritePin(GPIOA, E_Pin|D_Pin|C_Pin|B_Pin
                          |A_Pin|F_Pin|G_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : SUBTRAI_Pin SOMA_Pin */
  GPIO_InitStruct.Pin = SUBTRAI_Pin|SOMA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : E_Pin D_Pin C_Pin B_Pin
                           A_Pin F_Pin G_Pin */
  GPIO_InitStruct.Pin = E_Pin|D_Pin|C_Pin|B_Pin
                          |A_Pin|F_Pin|G_Pin;
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
