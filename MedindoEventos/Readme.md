# Meddição de Intervalos

Este projeto utiliza a placa STM32 para medir o tempo decorrido entre dois pressionamentos de um botão. A contagem de tempo é iniciada no primeiro pressionamento do botão e parada no segundo pressionamento. O tempo decorrido é exibido via UART.



## Estrutura do Código

1. **Inclusão de Bibliotecas e Definições**

   Inclui as bibliotecas necessárias e define variáveis globais, como o temporizador e o estado do botão.

2. **Função main**

   - Inicializa os periféricos.
   - Entra em um loop infinito, aguardando eventos.

   ```c
   int main(void)
   {
     HAL_Init();
     SystemClock_Config();
     MX_GPIO_Init();
     MX_USART1_UART_Init();
     MX_TIM3_Init();

     while (1) {
       // Loop principal
     }
   }
   ```

3. **Função HAL_GPIO_EXTI_Falling_Callback**

   Esta função é chamada quando ocorre uma interrupção externa (botão pressionado). Ela verifica o estado do botão e inicia ou para o temporizador, enviando mensagens via UART.

   ```c
   void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
   {
       if (GPIO_Pin == GPIO_PIN_8) { 
           if (!button_state) { // Primeiro pressionamento
               HAL_TIM_Base_Start_IT(&htim3);
               HAL_UART_Transmit(&huart1, msg_start, (sizeof(msg_start)-1), 1000);
               button_state = 1;
           } else { // Segundo pressionamento
               HAL_TIM_Base_Stop_IT(&htim3);
               sprintf(uart_tx_buffer, "Tempo decorrido: %lu ms\r\n", time);
               HAL_UART_Transmit(&huart1, (uint8_t *)uart_tx_buffer, strlen(uart_tx_buffer), 1000);
               time = 0;
               button_state = 0;
           }
       }
   }
   ```


## Licença

Este projeto é licenciado sob os termos encontrados no arquivo LICENSE no diretório raiz deste software. Se não houver um arquivo LICENSE, o software é fornecido "COMO ESTÁ", sem garantias ou condições de qualquer tipo, expressas ou implícitas.