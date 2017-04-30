#include "I2CModeInitializing.h"

I2CControllerMode* I2CModeInitiazling::sInstance = NULL;

I2CControllerMode* I2CModeInitiazling::getInstance()
{
	if (sInstance == NULL)
	{
		sInstance = new I2CModeInitiazling();
	}
	return sInstance;
}