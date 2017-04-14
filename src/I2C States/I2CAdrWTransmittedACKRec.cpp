#include "I2CAdrWTransmittedACKRec.h"
#include "I2CDataTransmittedACKRec.h"
#include "I2COpened.h"

I2CState* I2CAdrWTransmittedACKRec::i2cAdrWTransmittedAckRecInstance = 0; 

I2CState* I2CAdrWTransmittedACKRec::getInstance()
{
	if (i2cAdrWTransmittedAckRecInstance == 0)
	{
		i2cAdrWTransmittedAckRecInstance = new I2CAdrWTransmittedACKRec();
	}
	return i2cAdrWTransmittedAckRecInstance;
}

void I2CAdrWTransmittedACKRec::handleStatusRegSignal(I2CTransmitter* transmitter, uint8_t statusRegCode)
{
	if (statusRegCode == DATA_TRANSMITTED_ACK_REC)
	{
		this->sendTransmitSignal(transmitter);
	}
	else if (statusRegCode == DATA_TRANSMITTED_NACK_REC)
	{
		this->sendStopSignal(transmitter);
	}
}

void I2CAdrWTransmittedACKRec::sendTransmitSignal(I2CTransmitter* transmitter) 
{
	static uint8_t TWDR;
	transmitter->getTxQueue().dequeue(&TWDR);

	cout << "Sending Data byte" << endl;
	changeState(transmitter, I2CDataTransmittedACKRec::getInstance());
}

void I2CAdrWTransmittedACKRec::sendStopSignal(I2CTransmitter* transmitter)
{
	cout << "Sending Stop Signal" << endl;
	changeState(transmitter, I2COpened::getInstance());
}
