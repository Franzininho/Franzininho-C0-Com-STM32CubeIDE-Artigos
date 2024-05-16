# MedindoEventos com FranzinhoC0

Neste projeto está configurado o Franzininho C0 utilizando as ferramentas STM32CUBE e CubeMx para realizar a contagem de tempo entre dois eventos. 


## Material Necessário

- 1 Franzininho C0
- 1 cabo micro usb


## Funções 

```
/* Função lidar com debouce botao */
void debounce_button(void) {
    HAL_TIM_Base_Start(&htim3);
    uint32_t current_time = HAL_GetTick();
    if (current_time - debounce_time >= 50) { // Tempo de debounce
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET) {
            if (!button_state) { // Primeiro pressionamento
                start_time = HAL_GetTick(); // Inicia a contagem de tempo
        		HAL_UART_Transmit(&huart1, msg_start, (sizeof(msg_start)-1), 1000);	// Transmite mensagem serial pela UART
                button_state = 1;
            } else { // Segundo pressionamento
                end_time = HAL_GetTick(); // Finaliza a contagem de tempo
                time = end_time - start_time; // Calcula a diferença de tempo
                sprintf(uart_tx_buffer, "Tempo decorrido: %lu ms\r\n", time); // Formata mensagem
                HAL_UART_Transmit(&huart1, (uint8_t *)uart_tx_buffer, strlen(uart_tx_buffer), 1000); // Transmite mensagem serial pela UART
                button_state = 0;
            }
        }
        debounce_time = current_time;
    }
}

/* Funções de configuração da interrupção externa */

void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == GPIO_PIN_8) { // Botão pressionado
        debounce_button();
    }
}

```