# Aprendendo a trabalhar com interrupções externas e UART no Franzininho C0.

Neste projeto está configurado o Franzininho C0 utilizando as ferramentas STM32CUBE e CubeMx para lidar com interrupções externas e comunicação UART. Em que ao pressionar um botão, uma interrupção será acionada, e uma mensagem será transmitida pela UART indicando se ocorreu uma borda de subida ou descida. 


## Material Necessário

- 1 Franzininho C0
- 1 cabo micro usb


## Funções de callback


```
void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)	// Função de callback para tratamento da interrupção externa (descida)
{
	if(GPIO_Pin == GPIO_PIN_8)
	{
		HAL_UART_Transmit(&huart1, msg_descida, (sizeof(msg_descida)-1), 1000);	// Transmite mensagem serial pela UART
	}
}
void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin)	// Função de callback para tratamento da interrupção externa (subida)
{
	if(GPIO_Pin == GPIO_PIN_8)
	{
		HAL_UART_Transmit(&huart1, msg_subida, (sizeof(msg_subida)-1), 1000);	// Transmite mensagem serial pela UART
	}
}

```