#include "I2CModeMasterTransmitter.h"

I2CControllerMode* I2CModeMasterTransmitter::sInstance = NULL;

I2CControllerMode* I2CModeMasterTransmitter::getInstance()
{
	if (sInstance == NULL)
	{
		sInstance = new I2CModeMasterTransmitter();
	}
	return sInstance;
}