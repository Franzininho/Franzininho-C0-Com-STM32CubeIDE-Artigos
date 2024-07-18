# Explorando Infravermelho: Controle Remoto e Receptor com Franzininho C0

Este projeto implementa um sistema de controle remoto infravermelho (IR) utilizando a placa STM32. O código principal está no arquivo `main.c`, que gerencia a inicialização dos periféricos, a captura e a decodificação dos sinais IR, e a transmissão dos comandos via UART.


#### Função `main()`

A função `main()` é o ponto de entrada do programa. Suas principais responsabilidades são:

1. Inicializar a biblioteca HAL.
2. Configurar o clock do sistema.
3. Inicializar os periféricos configurados.
4. Entrar no loop principal onde verifica a disponibilidade de códigos IR e os converte para comandos UART.

```c
int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_TIM3_Init();
  MX_USART1_UART_Init();
  NEC_Init();

  while (1)
  {
    if(NEC_Available() > 0){
      code = NEC_Get_Code();
      char uart_tx_buffer[50];
      sprintf(uart_tx_buffer, "\r\n\Code: 0x%lX\r\n", code);
      HAL_UART_Transmit(&huart1, (uint8_t *)uart_tx_buffer, strlen(uart_tx_buffer), 1000);
      convert_code(code);
    }
  }
}
```


#### Funções de Controle IR

- `NEC_Init()`: Inicializa o protocolo NEC para comunicação IR.
- `NEC_Available()`: Verifica se há um código IR disponível.
- `NEC_Get_Code()`: Obtém o código IR capturado.
- `HAL_GPIO_EXTI_Falling_Callback()`: Callback para interrupção na borda de descida do pino GPIO, usada para capturar o sinal IR.
- `convert_code(uint32_t code)`: Converte o código IR para um comando específico e o envia pela UART.

```c
void NEC_Init(void){
  HAL_TIM_Base_Start(&htim3);
  __HAL_TIM_SetCounter(&htim3, 0);
}

uint8_t NEC_Available(){
  return flag_ir;
}

uint32_t NEC_Get_Code(){
  flag_ir = 0;
  return code_temp;
}

void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin) {
  if(GPIO_Pin == GPIO_PIN_4)
  {
    if(__HAL_TIM_GetCounter(&htim3) > 8000)
    {
      code_temp = 0;
      bit_counter = 0;
    }
    else if (__HAL_TIM_GetCounter(&htim3) > 1700)
    {
      code_temp |= (1UL << (31-bit_counter));
      bit_counter++;
    }
    else if (__HAL_TIM_GetCounter(&htim3) > 1000)
    {
      code_temp &= ~(1UL << (31-bit_counter));
      bit_counter++;
    }

    if(bit_counter == 32)
    {
      cmd_l = ~code_temp;
      cmd_h = code_temp >> 8;
      if(cmd_l == cmd_h)
      {
        flag_ir = 1;
      }
      bit_counter = 0;
    }
    __HAL_TIM_SetCounter(&htim3, 0);
  }
}

void convert_code(uint32_t code) {
  uint8_t mensagem[2] = {'\0', '\0'};
  switch (code) {
    case 0xFFA25D: mensagem[0] = '1'; break;
    case 0xFF629D: mensagem[0] = '2'; break;
    case 0xFFE21D: mensagem[0] = '3'; break;
    case 0xFF22DD: mensagem[0] = '4'; break;
    case 0xFF02FD: mensagem[0] = '5'; break;
    case 0xFFC23D: mensagem[0] = '6'; break;
    case 0xFFE01F: mensagem[0] = '7'; break;
    case 0xFFA857: mensagem[0] = '8'; break;
    case 0xFF906F: mensagem[0] = '9'; break;
    case 0xFFB04F: mensagem[0] = '#'; break;
    case 0xFF6897: mensagem[0] = '*'; break;
    case 0xFF9867: mensagem[0] = '0'; break;
    case 0xFF38C7: mensagem[0] = 'K'; break;
    case 0xFF18E7: mensagem[0] = '^'; break;
    case 0xFF10EF: mensagem[0] = '<'; break;
    case 0xFF5AA5: mensagem[0] = '>'; break;
    case 0xFF4AB5: mensagem[0] = 'u'; break;
    default: return;
  }
  HAL_UART_Transmit(&huart1, mensagem, 1, 1000);
}
```


## Dependências

- STM32CubeIDE
- Biblioteca HAL da STMicroelectronics

## Licença

Este projeto está licenciado sob os termos descritos no arquivo LICENSE, que pode ser encontrado no diretório raiz deste software.

---