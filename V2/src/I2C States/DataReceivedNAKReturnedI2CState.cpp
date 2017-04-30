#include "DataReceivedNAKReturnedI2CState.h"
#include "I2CRepeatedStartSent.h"
#include "I2COpened.h"

I2CState* DataReceivedNAKReturnedI2CState::sInstance = NULL;

I2CState* DataReceivedNAKReturnedI2CState::getInstance()
{
	if (DataReceivedNAKReturnedI2CState::sInstance == NULL)
	{
		DataReceivedNAKReturnedI2CState::sInstance = new DataReceivedNAKReturnedI2CState();
	}
	return DataReceivedNAKReturnedI2CState::sInstance;
}

void DataReceivedNAKReturnedI2CState::handleStatusRegSignal(I2CController& controller, uint8_t statusRegisterCode)
{
	if (controller.isRepeatedStartEnabled)
	{
		controller.i2cTransmitter->sendStartSignal();
		controller.changeState(I2CRepeatedStartSent::getInstance());
	}
	else
	{
		controller.i2cTransmitter->sendStopSignal();
		controller.changeState(I2COpened::getInstance());
	}
}