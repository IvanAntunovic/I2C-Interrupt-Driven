#include "I2CClosed.h"

I2CState* I2CClosed::sInstance = NULL;

I2CState* I2CClosed::getInstance()
{
	if (sInstance == NULL)
	{
		sInstance = new I2CClosed();
	}
	return sInstance;
}


