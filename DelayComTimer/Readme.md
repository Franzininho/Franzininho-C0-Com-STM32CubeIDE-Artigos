# Utilizando Timers: aprendar a criar delay e trabalhar com interrupções no Franzininho C0 

Os temporizadores são um dos recursos mais importantes dos microcontroladores modernos. Eles nos permitem medir quanto tempo algo leva para ser executado, controlar com precisão o tempo dos pinos e até mesmo a implementação de sistemas operacionais.
Neste projeto foi configurado o STM32CubeIDE para utilização de Timers, além de demonstrar a criação de atrasos e interrupções através desse recurso.

## Hardware Necessário

- 1 Franzininho C0
- 1 led (cor a sua escolha)
- 1 resistor 300 ohms


## Código principal

Nosso objetivo é piscar um LED, conectado ao PB6, a cada 0,5s (500ms) utilizando a criação de atraso com o Timer 3.
- Clock do sistema: interno 48 MHz
- Prescaler escolhido para o exemplo: 48000 - 1 
- contador: 500-1

```
int main(void)
{


 HAL_Init();
 SystemClock_Config();
 MX_GPIO_Init();
 MX_TIM3_Init();
 HAL_TIM_Base_Start(&htim3); //inicia contagem
 /* USER CODE BEGIN WHILE */
 while (1)
 {
	  if(__HAL_TIM_GET_FLAG(&htim3, TIM_FLAG_UPDATE)){
	    __HAL_TIM_CLEAR_FLAG(&htim3, TIM_FLAG_UPDATE);
	    HAL_GPIO_TogglePin(GPIOB, LED_Pin);
	  }
   /* USER CODE END WHILE */
   /* USER CODE BEGIN 3 */
 }
 /* USER CODE END 3 */
}

```