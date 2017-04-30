#include "I2CDataTransmittedACKRec.h"
#include "I2CRepeatedStartSent.h"
#include "I2COpened.h"

I2CState* I2CDataTransmittedACKRec::sInstance = NULL;

I2CState* I2CDataTransmittedACKRec::getInstance()
{
	if (sInstance == NULL)
	{
		sInstance = new I2CDataTransmittedACKRec();
	}
	return sInstance;
}

void I2CDataTransmittedACKRec::handleStatusRegSignal(I2CController& controller, uint8_t statusRegCode)
{
	if (statusRegCode == DATA_TRANSMITTED_ACK_REC)
	{
		if (!controller.txQueue.isEmpty())
		{
			static uint8_t TWDR;
			controller.txQueue.dequeue(&TWDR);

			cout << "Sending Data Byte" << endl;
			controller.changeState(I2CDataTransmittedACKRec::getInstance());
		}
		else if (controller.isRepeatedStartEnabled)
		{
			controller.i2cTransmitter->sendStartSignal();
			controller.changeState(I2CRepeatedStartSent::getInstance());
		}
		else if (!(controller.isRepeatedStartEnabled))
		{
			controller.i2cTransmitter->sendStopSignal();
			controller.changeState(I2COpened::getInstance());
		}
	}
	else if (statusRegCode == REPEATED_START_SENT)
	{

	}
	else if (statusRegCode == DATA_TRANSMITTED_NACK_REC || statusRegCode == ARBITRATION_LOST)
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
	
}
