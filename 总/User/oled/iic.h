#ifndef __IIC_H__
#define __IIC_H__

void InitI2C0(void);
void I2CSendSingleByte(uint8_t slave_addr, char data);
void I2CSendDataBlock(uint8_t slave_addr, uint8_t *data, uint32_t num_bytes);

#endif
