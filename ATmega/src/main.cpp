/*
 * I2C_Port_Interrupt_Driven_V3.cpp
 *
 * Created: 8/4/2017 9:13:16 PM
 * Author : fairenough
 */ 

#include <util/delay.h>
#include <avr/io.h>
#include "I2CPort.h"
#include <string.h>

I2CPort i2cPort;

#define TWI_targetSlaveAddress 0x3F

int main(void)
{
	DDRA |= (1 << PINA0);
	uint8_t txBuffer[3];
	uint8_t rxBuffer[3];
	memset(rxBuffer, 0, 3);
	
	txBuffer[0] = 0x00 ;

	DDRA = 0xFF;
	DDRB = 0x00;
	PORTA = 0x00;
	
	i2cPort.open();
	i2cPort.selectSlaveDevice(0x3F, false);
	
    while (1) 
    {
		i2cPort.requestData();
		
		if (i2cPort.available())
		{
			i2cPort.readBytes(rxBuffer, 0, 1);
			PORTA = rxBuffer[0];
		}	
		
		if (PINB & (1 << PINB0))
		{
			i2cPort.writeBytes(txBuffer, 0, 1);
		}
    }
}

