/** @file lis3dh.c
 * LIS3DH accelerometer device driver. Uses SPI interface.
 */


#include "stm32c0xx.h"
#include "lis3dh.h"
#include "stdio.h"
#include "string.h"
extern SPI_HandleTypeDef hspi1;
extern UART_HandleTypeDef huart1;

/** @brief Initializes LIS3DH device with following configuration:
 * 100Hz sampling rate
 * Enable all axis
 * @retval None
 */
void LIS3DH_Init(void) {
	// delay to ensure LIS3DH is ready after power-up
	 HAL_Delay(10);
	 // Write to CTRL_REG1 to set data rate and enable all axes
	 LIS3DH_WriteReg(LIS3DH_CTRL_REG1, 0x57); // 100Hz, enable X, Y, Z
	 // Write to CTRL_REG4 to set scale default 2g and high-resolution mode
	 LIS3DH_WriteReg(LIS3DH_CTRL_REG4, 0xC8);
	 // Write to CTRL_REG2 to No high-pass filter
	 LIS3DH_WriteReg(LIS3DH_CTRL_REG2, 0x00);


    uint8_t who_am_i = LIS3DH_ReadReg(LIS3DH_WHO_AM_I);
    char status[50];
    sprintf(status, "WHO_AM_I: 0x%02X\r\n", who_am_i);
    HAL_UART_Transmit(&huart1, (uint8_t *)status, strlen(status), 1000);
}


void LIS3DH_ReadAccel(int16_t *acceleration) {
    uint8_t x_l = LIS3DH_ReadReg(LIS3DH_OUT_X_L);
    uint8_t x_h = LIS3DH_ReadReg(LIS3DH_OUT_X_H);
    uint8_t y_l = LIS3DH_ReadReg(LIS3DH_OUT_Y_L);
    uint8_t y_h = LIS3DH_ReadReg(LIS3DH_OUT_Y_H);
    uint8_t z_l = LIS3DH_ReadReg(LIS3DH_OUT_Z_L);
    uint8_t z_h = LIS3DH_ReadReg(LIS3DH_OUT_Z_H);

    acceleration[0] = ((int16_t)x_h << 8) | x_l;  // X-axis
    acceleration[1] = ((int16_t)y_h << 8) | y_l;  // Y-axis
    acceleration[2] = ((int16_t)z_h << 8) | z_l;  // Z-axis
}

/** @brief Reads given amount of data from sensor
 * @param reg: Register address to read from
 * @retval data receive
 */

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

/** @brief Writes given amount of data to sensor
 * @param reg: Register address to write to
 * @param value: Number of bytes to be written
 * @retval Zero on success, -1 otherwise
 */
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
