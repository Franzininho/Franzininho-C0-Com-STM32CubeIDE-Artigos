
#include <stdint.h>

#define LIS3DH_CTRL_REG1       0x20
#define LIS3DH_CTRL_REG3       0x22
#define LIS3DH_CTRL_REG4       0x23
#define LIS3DH_INT1_CFG        0x30
#define LIS3DH_INT1_SRC        0x31
#define LIS3DH_INT1_THS        0x32
#define LIS3DH_INT1_DURATION   0x33

/* Public APIs */
uint8_t LIS3DH_ReadReg(uint8_t address);
void LIS3DH_WriteReg(uint8_t address, uint8_t data);
void LIS3DH_FreeFallConfig();
void freeFallStatus();
