#include "I2CModeIdle.h"

I2CControllerMode* I2CModeIdle::sInstance = NULL;

I2CControllerMode* I2CModeIdle::getInstance()
{
	if (sInstance == NULL)
	{
		sInstance = new I2CModeIdle();
	}
	return sInstance;
}


