#include "I2COpened.h"
#include "I2CStartTransmitted.h"


I2CState* I2COpened::sInstance = NULL;

I2CState* I2COpened::getInstance()
{
	if (sInstance == NULL)
	{
		sInstance = new I2COpened();
	}
	return sInstance;
}

void I2COpened::handleStatusRegSignal(I2CController& controller, uint8_t statusRegCode)
{
	if (statusRegCode == START_TRANSMITTED_SUCCESFULLY)
	{
		controller.i2cTransmitter->sendStartSignal();
		controller.changeState(I2CStartTransmitted::getInstance());
	}
	else
	{
		controller.i2cTransmitter->sendStartSignal();
		// No need to change State as we are already in Opened State
	}
}

