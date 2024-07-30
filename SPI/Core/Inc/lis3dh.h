
#include <stdint.h>

#define LIS3DH_CTRL_REG1        0x20
#define LIS3DH_CTRL_REG4        0x23
#define LIS3DH_WHO_AM_I         0x0F
#define LIS3DH_OUT_X_L          0x28
#define LIS3DH_OUT_X_H          0x29
#define LIS3DH_OUT_Y_L          0x2A
#define LIS3DH_OUT_Y_H          0x2B
#define LIS3DH_OUT_Z_L          0x2C
#define LIS3DH_OUT_Z_H          0x2D
#define LIS3DH_DATARATE_100HZ   0x50  // 100Hz data rate, all axes enabled
#define LIS3DH_CTRL_REG4_BDU    0x80  // Block data update
#define LIS3DH_CTRL_REG4_FS_2G  0x00  // +/- 2g full scale

/* Public APIs */
void LIS3DH_Init(void);
uint8_t LIS3DH_ReadReg(uint8_t address);
void LIS3DH_WriteReg(uint8_t address, uint8_t data);
void LIS3DH_ReadAccel(int16_t *acceleration);
