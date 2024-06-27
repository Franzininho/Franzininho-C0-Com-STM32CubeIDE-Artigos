# Aprendendo a usar RTC (real timer) da Franzininho C0

## Descrição

Este código configura um microcontrolador STM32 para ler a data e hora do RTC (Real-Time Clock) e transmitir esses dados via UART para um PC. O código usa periféricos como RTC e UART.

## Estrutura do Código

1. **Includes**: Importa bibliotecas necessárias.
2. **Variáveis Globais**: Declara variáveis usadas pelo RTC e UART.
3. **Prototipagem de Funções**: Declaração antecipada de funções.
4. **Função `main`**: Contém a lógica principal do programa.

## Detalhamento do Código

1. **Includes**:
   ```c
   #include "main.h"
   #include "stdio.h"
   #include "string.h"
   ```

   Declaração de variáveis globais adicionais:
   ```c
   uint8_t dia, mes, ano, horas, segundos, minutos;
   char uart_tx_buffer[50];
   ```

2. **Variáveis Globais**:
   ```c
   RTC_HandleTypeDef hrtc;
   UART_HandleTypeDef huart1;

   RTC_DateTypeDef data;
   RTC_TimeTypeDef tempo;
   ```

3. **Prototipagem de Funções**:
   ```c
   void SystemClock_Config(void);
   static void MX_GPIO_Init(void);
   static void MX_RTC_Init(void);
   static void MX_USART1_UART_Init(void);
   ```

4. **Função `main`**:
   - Inicializa o microcontrolador.
   - Configura o clock do sistema.
   - Inicializa os periféricos GPIO, RTC e UART.
   - Ajusta a data e a hora do RTC.
   - Loop principal onde:
     - Lê a data e a hora do RTC.
     - Formata os dados de data e hora.
     - Transmite os dados via UART para o PC.
     ```c
     int main(void)
     {
       HAL_Init();
       SystemClock_Config();
       MX_GPIO_Init();
       MX_RTC_Init();
       MX_USART1_UART_Init();

       /* Ajuste a data e a hora aqui */
       data.Year = 24;  // 2024
       data.Month = RTC_MONTH_JUNE;
       data.Date = 25;
       data.WeekDay = RTC_WEEKDAY_TUESDAY;
       tempo.Hours = 9;
       tempo.Minutes = 5;
       tempo.Seconds = 0;
       HAL_RTC_SetDate(&hrtc, &data, RTC_FORMAT_BIN);
       HAL_RTC_SetTime(&hrtc, &tempo, RTC_FORMAT_BIN);

       while (1)
       {
         HAL_RTC_GetDate(&hrtc, &data, RTC_FORMAT_BIN);
         HAL_RTC_GetTime(&hrtc, &tempo, RTC_FORMAT_BIN);

         horas = tempo.Hours;
         minutos = tempo.Minutes;
         segundos = tempo.Seconds;
         dia = data.Date;
         mes = data.Month;
         ano = data.Year;

         sprintf(uart_tx_buffer, "Data: %02d/%02d/%04d Tempo: %02d:%02d:%02d\r\n", dia, mes, 2000+ano, horas, minutos, segundos);
         HAL_UART_Transmit(&huart1, (uint8_t *)uart_tx_buffer, strlen(uart_tx_buffer), 1000);
       }
     }
     ```

## Funcionalidade

- **Inicialização**: Configura o microcontrolador e periféricos.
- **Ajuste de Data e Hora**: Define a data e hora iniciais do RTC.
- **Loop Infinito**: Lê a data e hora do RTC, formata e transmite via UART para o PC.

## Como Usar

1. Carregue o código no seu microcontrolador STM32.
2. Conecte o microcontrolador a um PC via UART.
3. Verifique a leitura de data e hora no terminal serial do PC.
