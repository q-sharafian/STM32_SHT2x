
#include "stm32f10x_i2c.h"

#ifndef MY_LIBRARY_SHT2X_H_
#define MY_LIBRARY_SHT2X_H_

float SHT_ReadTemp(I2C_TypeDef* I2Cx);
float SHT_ReadHumidity(I2C_TypeDef* I2Cx);
void SHT_Reset();

#endif /* MY_LIBRARY_SHT2X_H_ */
