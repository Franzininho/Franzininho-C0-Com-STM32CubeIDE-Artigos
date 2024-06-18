# Medindo temperatura com NTC e Franzinho C0

### README: Temperature Monitoring System

#### Descrição
Este código implementa um sistema de monitoramento de temperatura utilizando um termistor NTC (Negative Temperature Coefficient) e uma equação de Steinhart-Hart para calcular a temperatura em graus Celsius. A temperatura medida é exibida através de LEDs coloridos (azul, verde e vermelho) e também transmitida via comunicação UART.

#### Componentes Principais
- **Termistor NTC:** Um componente que varia sua resistência com a temperatura.
- **Equação Steinhart-Hart:** Utilizada para converter a resistência do termistor em temperatura.
- **Microcontrolador STM32:** Controla a leitura do ADC (Conversor Analógico-Digital), cálculo da temperatura, controle dos LEDs e buzzer, e transmissão da temperatura via UART.

#### Constantes e Variáveis
- **resistor:** Valor fixo do resistor de referência utilizado no circuito (10kΩ).
- **Constantes A, B, C:** Coeficientes da equação Steinhart-Hart para o termistor específico.
- **leitura:** Variável que armazena o valor digital lido pelo ADC.
- **temperatura:** Variável que armazena a temperatura calculada em graus Celsius.

#### Funcionalidades
1. **calcular_temperatura():** Calcula a temperatura usando a equação de Steinhart-Hart com base na leitura analógica do termistor.
2. **controlar_leds_e_buzzer():** Controla os LEDs (azul, verde, vermelho) e o buzzer com base na temperatura medida:
   - Temperatura <= 15°C: LED azul ligado.
   - 15°C < Temperatura <= 30°C: LED verde ligado.
   - Temperatura > 30°C: LED vermelho ligado e buzzer ativado.
3. **transmitir_temperatura():** Transmite a temperatura medida via UART, formatada com uma casa decimal.


#### Implementação
O código está configurado para executar em um microcontrolador STM32 com suporte a HAL, utilizando interrupções para ADC e UART, garantindo leituras precisas e comunicação confiável da temperatura medida.

#### Notas
Certifique-se de ajustar as configurações do projeto (como pinos GPIO, baud rate da UART, etc.) de acordo com seu hardware específico antes de compilar e carregar o código no microcontrolador.

```c
#define resistor 10000.0f

/* contantes equacao Steinhart-Hart  */
#define A 0.001125308852122f
#define B 0.000234711863267f
#define C 0.000000085663516f

uint32_t leitura;
float temperatura;

/* Protótipos de função */
float calcular_temperatura();
void controlar_leds_e_buzzer();
void transmitir_temperatura();

int main(void)
{
    // Inicializações e configurações omitidas para brevidade...
    
    while (1)
    {
        // Leitura ADC, cálculo de temperatura, controle de LEDs/buzzer e transmissão via UART
        HAL_ADC_Start(&hadc1);
        HAL_ADC_PollForConversion(&hadc1, 1000);
        leitura = HAL_ADC_GetValue(&hadc1);
        HAL_ADC_Stop(&hadc1);
        
        temperatura = calcular_temperatura();
        controlar_leds_e_buzzer();
        transmitir_temperatura();
    }
}
```
