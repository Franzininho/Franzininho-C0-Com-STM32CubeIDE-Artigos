# Driver identificar Queda Lire com LIS3DH com SPI

Este projeto é um driver para o acelerômetro LIS3DH utilizando a interface SPI do microcontrolador STM32. O código configura o LIS3DH para detectar quedas livres e transmite uma mensagem via UART quando uma queda livre é detectada.

## Arquivos

- **`lis3dh.c`**: Código-fonte do driver LIS3DH.
- **`lis3dh.h`**: Cabeçalho do driver LIS3DH (não incluído no código fornecido).


## Funções Principais

- **`LIS3DH_FreeFallConfig`**: Configura o LIS3DH para detecção de queda livre. Define os registros de controle e configuração do acelerômetro.
  
  ```c
  void LIS3DH_FreeFallConfig(void) {
      LIS3DH_WriteReg(LIS3DH_CTRL_REG1, 0x97); // CTRL_REG1: Ativar XYZ, 50 Hz ODR
      LIS3DH_WriteReg(LIS3DH_CTRL_REG3, 0x88); // CTRL_REG4: High resolution, BDU enabled, ±2g
      LIS3DH_WriteReg(LIS3DH_CTRL_REG4, 0x40); // CTRL_REG3: AOI1 interrupt on INT1 pin
      LIS3DH_WriteReg(LIS3DH_INT1_CFG, 0x95); // INT1_CFG: 6 direction movement recognition
      LIS3DH_WriteReg(LIS3DH_INT1_THS, 0x16); // INT1_THS: Threshold = 350 mg
      LIS3DH_WriteReg(LIS3DH_INT1_DURATION, 0x03); // INT1_DURATION: Minimum event duration = 1/OD
  }
  ```

- **`freeFallStatus`**: Verifica o status da interrupção de queda livre. Se uma queda livre é detectada, uma mensagem é transmitida pela UART e o LED é alternado.

  ```c
  void freeFallStatus() {
      uint8_t int1Src;
      int1Src = LIS3DH_ReadReg(LIS3DH_INT1_SRC);

      // Verifica se o bit de queda livre foi ativado
      if (int1Src & 0x40) {
          // Verifique se todos os bits XLow, YLow e ZLow estão setados
          if ((int1Src & 0x01) && (int1Src & 0x04) && (int1Src & 0x10)) {
              // Queda livre detectada: Todos os eixos estão abaixo do limiar configurado
              HAL_UART_Transmit(&huart1, msg, (sizeof(msg)-1), 1000); // Transmite mensagem serial pela UART
              HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_6); // Muda estado do LED
          }
      }
  }
  ```

- **`LIS3DH_ReadReg`**: Lê um registro do LIS3DH via SPI.
  
  ```c
  uint8_t LIS3DH_ReadReg(uint8_t address) {
      uint8_t txData[2];
      uint8_t rxData[2];
      txData[0] = address | 0x80 ; // Set read bit (MSB = 1)
      txData[1] = 0x00; // Dummy byte

      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); // CS low

      // delay to ensure CS is correctly registered
      HAL_Delay(1);

      if (HAL_SPI_TransmitReceive(&hspi1, txData, rxData, 2, HAL_MAX_DELAY) != HAL_OK) {
          char error_msg[] = "SPI Transmit/Receive Error\r\n";
          HAL_UART_Transmit(&huart1, (uint8_t *)error_msg, strlen(error_msg), 1000);
      }

      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET); // CS high

      return rxData[1]; // The second byte received is the actual data
  }
  ```

- **`LIS3DH_WriteReg`**: Escreve um valor em um registro do LIS3DH via SPI.

  ```c
  void LIS3DH_WriteReg(uint8_t address, uint8_t data) {
      uint8_t txData[2];
      txData[0] = address;
      txData[1] = data;

      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); // CS low

      // delay to ensure CS is correctly registered
      HAL_Delay(1);

      if (HAL_SPI_Transmit(&hspi1, txData, 2, HAL_MAX_DELAY) != HAL_OK) {
          char error_msg[] = "SPI Write Error\r\n";
          HAL_UART_Transmit(&huart1, (uint8_t *)error_msg, strlen(error_msg), 1000);
      }

      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);   // CS high
  }
  ```

## Configuração e Inicialização

1. **Inicialização do Hardware**:
   - O driver SPI1 e UART1 são inicializados.

2. **Configuração do LIS3DH**:
   - A função `LIS3DH_FreeFallConfig` é chamada para configurar o acelerômetro.

3. **Loop Principal**:
   - A função `freeFallStatus` é chamada continuamente para verificar a detecção de queda livre.

## Compilação e Execução

1. Compile o código usando o STM32CubeIDE ou outro ambiente de desenvolvimento compatível com STM32.
2. Faça o upload do código para o microcontrolador STM32.
3. Monitore a saída UART usando um terminal serial para ver as mensagens de detecção de queda livre.

