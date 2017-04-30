#include "MasterReceiverI2CMode.h"

I2CControllerMode* MasterReceiverI2CMode::sInstance = NULL;

I2CControllerMode* MasterReceiverI2CMode::getInstance()
{
	if (MasterReceiverI2CMode::sInstance == NULL)
	{
		MasterReceiverI2CMode::sInstance = new MasterReceiverI2CMode();
	}
	return MasterReceiverI2CMode::sInstance;
}