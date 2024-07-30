
# Programa de Leitura de Acelerômetro LIS3DH

Este programa é uma aplicação para leitura e transmissão de dados de um acelerômetro LIS3DH utilizando a interface SPI. As leituras de aceleração são convertidas para miligravidade (mg) e transmitidas via UART.

## Requisitos

- Microcontrolador STM32
- Acelerômetro LIS3DH
- Interface SPI configurada
- Interface UART configurada

## Descrição do Código

### Inicialização

1. **HAL_Init**: Inicializa a biblioteca HAL.
2. **SystemClock_Config**: Configura o clock do sistema.
3. **MX_GPIO_Init**: Inicializa os pinos GPIO.
4. **MX_SPI1_Init**: Inicializa a interface SPI1.
5. **MX_USART1_UART_Init**: Inicializa a interface UART1.
6. **LIS3DH_Init**: Inicializa o acelerômetro LIS3DH com a seguinte configuração:
   - Taxa de amostragem de 100Hz
   - Ativação dos eixos X, Y e Z
   - Escala de ±4g

## Funções

### `void LIS3DH_Init(void)`
Inicializa o acelerômetro LIS3DH configurando os registros necessários para definir a taxa de amostragem e ativar os eixos.

### `void LIS3DH_ReadAccel(int16_t *acceleration)`
Lê os dados brutos de aceleração do LIS3DH e armazena nos parâmetros fornecidos.

### `uint8_t LIS3DH_ReadReg(uint8_t address)`
Lê um registro específico do LIS3DH.

### `void LIS3DH_WriteReg(uint8_t address, uint8_t data)`
Escreve um valor em um registro específico do LIS3DH.

## Exemplo de Uso

```c
int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_SPI1_Init();
    MX_USART1_UART_Init();
    
    // Inicializa o LIS3DH
    LIS3DH_Init();

    while (1)
    {
        int16_t accel[3];
        LIS3DH_ReadAccel(accel);

        // Transmite valores brutos
        sprintf(acel_buf, "Leitura Bruta - X: %i, Y: %i, Z: %i\r\n", accel[0], accel[1], accel[2]);
        HAL_UART_Transmit(&huart1, (uint8_t *)acel_buf, strlen(acel_buf), 1000);
        HAL_Delay(1000);

        // Conversão para mg
        int32_t accel_x_mg = (int32_t)accel[0] * 1000 / 16384;
        int32_t accel_y_mg = (int32_t)accel[1] * 1000 / 16384;
        int32_t accel_z_mg = (int32_t)accel[2] * 1000 / 16384;

        // Transmite valores convertidos
        sprintf(acel_buf, "Aceleracao (mg) - X: %ld, Y: %ld, Z: %ld\r\n", accel_x_mg, accel_y_mg, accel_z_mg);
        HAL_UART_Transmit(&huart1, (uint8_t *)acel_buf, strlen(acel_buf), 1000);
        HAL_Delay(1000);
    }
}
```






