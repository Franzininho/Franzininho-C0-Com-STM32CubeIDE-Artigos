# Franzininho C0: Entradas e Saídas no STMcubeIDE

Configurando as entradas e saídas digitais do Franzininho C0 por meio do controle de LEDs com um botão (pushbutton) utilizando o STMcubeIDE e o CubeMX.

## Hardware Necessário

- 1 Franzininho C0
- 2 resistores 300 ohms
- 2 leds (cores a sua escolha)
- 1 push-button

## Código principal

nosso objetivo é alternar os estados do LED1 e LED2 a cada 1 segundo, enquanto o botão estiver pressionado. Para isso, usaremos as HAL_GPIO_ReadPin, HAL_GPIO_TogglePin e HAL_Delay(uint32_t delay).

```
while (1)
   {
   /* USER CODE END WHILE */
   /* USER CODE BEGIN 3 */
      if(HAL_GPIO_ReadPin(BOTAO_GPIO_Port, BOTAO_Pin)==0){ //leitura botao
          HAL_GPIO_TogglePin(GPIOB, LED1_Pin|LED2_Pin); //alterna estado pinos
          HAL_Delay(1000); //espera 1 segundo
      }
   }
 /* USER CODE END 3 */
```




