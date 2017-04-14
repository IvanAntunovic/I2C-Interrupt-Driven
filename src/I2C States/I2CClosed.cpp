#include "I2CClosed.h"

I2CState* I2CClosed::i2cClosedInstance = 0;

I2CState* I2CClosed::getInstance()
{
	if (i2cClosedInstance == 0)
	{
		i2cClosedInstance = new I2CClosed();
	}
	return i2cClosedInstance;
}


