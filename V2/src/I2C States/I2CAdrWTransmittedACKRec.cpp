#include "I2CAdrWTransmittedACKRec.h"
#include "I2CDataTransmittedACKRec.h"
#include "I2COpened.h"

I2CState* I2CAdrWTransmittedACKRec::sInstance = NULL;

I2CState* I2CAdrWTransmittedACKRec::getInstance()
{
	if (sInstance == NULL)
	{
		sInstance = new I2CAdrWTransmittedACKRec();
	}
	return sInstance;
}

void I2CAdrWTransmittedACKRec::handleStatusRegSignal(I2CController& controller, uint8_t statusRegCode)
{
	if (statusRegCode == DATA_TRANSMITTED_ACK_REC)
	{
		static uint8_t TWDR;
		controller.txQueue.dequeue(&TWDR);

		cout << "Sending Data Byte" << endl;
		controller.changeState(I2CDataTransmittedACKRec::getInstance());
	}
	else if (statusRegCode == DATA_TRANSMITTED_NACK_REC)
	{
		controller.i2cTransmitter->sendStopSignal();
		controller.changeState(I2COpened::getInstance());
	}
}


