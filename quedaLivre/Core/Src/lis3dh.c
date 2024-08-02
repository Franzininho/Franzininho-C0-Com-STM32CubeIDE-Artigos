/** @file lis3dh.c
 * LIS3DH accelerometer device driver. Uses SPI2 interface.
 */


#include "stm32c0xx.h"
#include "lis3dh.h"
#include "stdio.h"
#include "string.h"
extern SPI_HandleTypeDef hspi1;
extern UART_HandleTypeDef huart1;
uint8_t msg[] = "Queda livre detectada! \r\n";

// Função para configurar o LIS3DH para detecção de queda livre
void LIS3DH_FreeFallConfig(void) {
    LIS3DH_WriteReg(LIS3DH_CTRL_REG1, 0x97); // CTRL_REG1: Ativar XYZ, 50 Hz ODR
    LIS3DH_WriteReg(LIS3DH_CTRL_REG3, 0x88); // CTRL_REG4: High resolution, BDU enabled, ±2g
    LIS3DH_WriteReg(LIS3DH_CTRL_REG4, 0x40); // CTRL_REG3: AOI1 interrupt on INT1 pin
    LIS3DH_WriteReg(LIS3DH_INT1_CFG, 0x95); // INT1_CFG: 6 direction movement recognition
    LIS3DH_WriteReg(LIS3DH_INT1_THS, 0x16); // INT1_THS: Threshold = 350 mg
    LIS3DH_WriteReg(LIS3DH_INT1_DURATION, 0x03); // INT1_DURATION: Minimum event duration = 1/OD
}


// Função para verificar o status da interrupção de queda livre
void freeFallStatus() {
    uint8_t int1Src;
    int1Src = LIS3DH_ReadReg(LIS3DH_INT1_SRC);


    // Verifica se o bit de queda livre foi ativado
    if (int1Src & 0x40) {
    	// Verifique se todos os bits XLow, YLow e ZLow estão setados
    	if ((int1Src & 0x01) && (int1Src & 0x04) && (int1Src & 0x10)) {
    		// Queda livre detectada: Todos os eixos estão abaixo do limiar configurado
    		HAL_UART_Transmit(&huart1, msg, (sizeof(msg)-1), 1000);	// Transmite mensagem serial pela UART
             HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_6); //muda estado led
    	}
    }
}


// Leitura por SPI
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

// Escrita por SPI
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

/**
 * @}
 */

