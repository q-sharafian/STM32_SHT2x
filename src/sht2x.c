
#include "sht2x.h"
#include "stm32f10x_i2c.h"

float SHT_ReadTemp(I2C_TypeDef* I2Cx)
{
	unsigned char a = 121, b = 83, c = 0;
	unsigned int all = 0;

	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
	I2C_AcknowledgeConfig(I2Cx, ENABLE); // enable acknowledge

	I2C_GenerateSTART(I2Cx, ENABLE);
	while(!I2C_GetFlagStatus(I2Cx, I2C_FLAG_SB));// wait generate start condition

	I2C_Send7bitAddress(I2Cx, 0x80, I2C_Direction_Transmitter); // send address sht2x
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)); // waitsend address sht2x

	I2C_SendData(I2Cx, 0xE3); // send command Measurement temperature
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));// wait send command(data)

	I2C_GenerateSTART(I2Cx, ENABLE);
	while(!I2C_GetFlagStatus(I2Cx, I2C_FLAG_SB));// wait generate start condition

	I2C_Send7bitAddress(I2Cx, 0x80, I2C_Direction_Receiver);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)); // wait send address sht2x

	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED)); // check received data
	a = I2C_ReceiveData(I2Cx);

	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED)); // check received data
	b = I2C_ReceiveData(I2Cx);

	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED)); // check received data
	c = I2C_ReceiveData(I2Cx);

	I2C_NACKPositionConfig(I2Cx, I2C_NACKPosition_Current); // send not acknowledge
	I2C_AcknowledgeConfig(I2Cx, DISABLE);// disable acknowledge

	I2C_GenerateSTOP(I2Cx, ENABLE);
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_STOPF)); // wait generate stop condition

	I2C_AcknowledgeConfig(I2Cx, ENABLE); // enable acknowledge

	all = (a << 8) + (b << 0);
	return ( -46.85 + (175.72 * ( (float)all / 65536) ) ); // calculate temperature
};
float SHT_ReadHumidity(I2C_TypeDef* I2Cx)
{
	unsigned char a = 0, b = 0, c = 0;
	unsigned int all = 0;

	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
	I2C_AcknowledgeConfig(I2Cx, ENABLE); // enable acknowledge

	I2C_GenerateSTART(I2Cx, ENABLE);
	while(!I2C_GetFlagStatus(I2Cx, I2C_FLAG_SB));// wait generate start condition

	I2C_Send7bitAddress(I2Cx, 0x80, I2C_Direction_Transmitter); // send address sht2x
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)); // waitsend address sht2x

	I2C_SendData(I2Cx, 0xE5); // send command Measurement humidity
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));// wait send command(data)

	I2C_GenerateSTART(I2Cx, ENABLE);
	while(!I2C_GetFlagStatus(I2Cx, I2C_FLAG_SB));// wait generate start condition

	I2C_Send7bitAddress(I2Cx, 0x80, I2C_Direction_Receiver);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)); // wait send address sht2x

	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED)); // check received data
	a = I2C_ReceiveData(I2Cx);

	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED)); // check received data
	b = I2C_ReceiveData(I2Cx);

	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED)); // check received data
	c = I2C_ReceiveData(I2Cx);

	I2C_NACKPositionConfig(I2Cx, I2C_NACKPosition_Current); // send not acknowledge
	I2C_AcknowledgeConfig(I2Cx, DISABLE);// disable acknowledge

	I2C_GenerateSTOP(I2Cx, ENABLE);
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_STOPF)); // wait generate stop condition

	I2C_AcknowledgeConfig(I2Cx, ENABLE); // enable acknowledge

	all = (a << 8) + (b << 0);
	return ( (float)-6 + ( (float)125 * ( (float)all / 65536) ) ); // calculate humidity

};
void SHT_Reset(I2C_TypeDef* I2Cx)
{
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
	I2C_AcknowledgeConfig(I2Cx, ENABLE);

	I2C_GenerateSTART(I2Cx, ENABLE);
	while(!I2C_GetFlagStatus(I2Cx, I2C_FLAG_SB));// wait generate start

	I2C_Send7bitAddress(I2Cx, 0x80, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	I2C_SendData(I2Cx, 0xFE);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));// wait send command for soft reset

	I2C_GenerateSTOP(I2Cx, ENABLE);
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_STOPF));// wait generate stop bit
}
