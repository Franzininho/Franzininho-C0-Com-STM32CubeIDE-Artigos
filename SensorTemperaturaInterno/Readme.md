# Utilizando o sensor de temperatura interno da Franzininho C0

## Descrição

Este código configura Franzininho C0 para ler a temperatura usando um sensor conectado ao ADC (Conversor Analógico-Digital) e transmitir os dados via UART para um PC. O código usa periféricos como ADC, DMA, TIM e UART.

## Estrutura do Código

1. **Includes**: Importa bibliotecas necessárias.
2. **Definições**: Define constantes para cálculos de temperatura.
3. **Variáveis Globais**: Declara variáveis usadas pelo ADC e UART.
4. **Prototipagem de Funções**: Declaração antecipada de funções.
5. **Função `main`**: Contém a lógica principal do programa.

## Detalhamento do Código

1. **Includes**:
   ```c
   #include "main.h"
   #include "stdio.h"
   #include "string.h"
   ```

2. **Definições**:
   ```c
   #define AVG_SLOPE (0.00253F) // 2.53 mV/°C
   #define V_AT_30C  (0.76F)   // 0.76V at 30°C
   #define V_REF_INT (1.12F)    // reference voltage
   ```

3. **Variáveis Globais**:
   ```c
   ADC_HandleTypeDef hadc1;
   DMA_HandleTypeDef hdma_adc1;
   TIM_HandleTypeDef htim1;
   UART_HandleTypeDef huart1;

   uint8_t UpdateEvent = 0;
   uint16_t AD_RES[2];
   float Temperature, V_Sense, V_Ref;
   char TxBuffer[30];
   ```

4. **Prototipagem de Funções**:
   ```c
   void SystemClock_Config(void);
   static void MX_GPIO_Init(void);
   static void MX_DMA_Init(void);
   static void MX_ADC1_Init(void);
   static void MX_TIM1_Init(void);
   static void MX_USART1_UART_Init(void);
   ```

5. **Função `main`**:
   - Inicializa o microcontrolador.
   - Configura o clock do sistema.
   - Inicializa os periféricos GPIO, DMA, ADC, TIM e UART.
   - Inicia o Timer1, ADC e calibração do ADC.
   - Loop principal onde:
     - Inicia a conversão ADC com DMA.
     - Calcula a temperatura usando as leituras do ADC.
     - Transmite a temperatura via UART para o PC.
     ```c
     int main(void)
     {
       HAL_Init();
       SystemClock_Config();
       MX_GPIO_Init();
       MX_DMA_Init();
       MX_ADC1_Init();
       MX_TIM1_Init();
       MX_USART1_UART_Init();

       HAL_TIM_Base_Start(&htim1);
       HAL_ADCEx_Calibration_Start(&hadc1);

       while (1)
       {
         HAL_ADC_Start_DMA(&hadc1, (uint32_t*)AD_RES, 2);
         if(UpdateEvent){
           V_Ref = (float)((V_REF_INT * 4095.0) / AD_RES[0]);
           V_Sense = (float)(AD_RES[1] * V_Ref) / 4095.0;
           Temperature = (((V_AT_30C  - V_Sense) * 1000.0) / AVG_SLOPE) + 30.0;
           int parte_inteira = (int)Temperature/1000.0;
           int parte_decimal = (int)((Temperature - parte_inteira) * 100.0);

           sprintf(TxBuffer, "Temperatura: %d.%02d\r\n", parte_inteira, parte_decimal);
           HAL_UART_Transmit(&huart1, (uint8_t*)TxBuffer, strlen(TxBuffer), 100);
           UpdateEvent = 0;
         }
       }
     }
     ```

## Funcionalidade

- **Inicialização**: Configura o microcontrolador e periféricos.
- **Loop Infinito**: Lê a temperatura do sensor, calcula o valor em graus Celsius e transmite via UART.


## Como Usar

1. Carregue o código no seu microcontrolador STM32.
2. Conecte um sensor de temperatura ao ADC1.
3. Conecte o microcontrolador a um PC via UART.
4. Verifique a leitura da temperatura no terminal serial do PC.
