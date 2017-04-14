#include "I2CDataTransmittedACKRec.h"
#include "I2CRepeatedStartSent.h"
#include "I2COpened.h"

I2CState* I2CDataTransmittedACKRec::i2cDataTransmittedACKRecInstance = 0;

I2CState* I2CDataTransmittedACKRec::getInstance()
{
	if (i2cDataTransmittedACKRecInstance == 0)
	{
		i2cDataTransmittedACKRecInstance = new I2CDataTransmittedACKRec();
	}
	return i2cDataTransmittedACKRecInstance;
}

void I2CDataTransmittedACKRec::handleStatusRegSignal(I2CTransmitter* transmitter, uint8_t statusRegCode)
{
	if (statusRegCode == DATA_TRANSMITTED_ACK_REC)
	{
		if (!transmitter->txQueue.isEmpty())
		{
			this->sendTransmitSignal(transmitter);
		}
		else if (transmitter->isRepeatedStartEnabled)
		{
			this->sendStartSignal(transmitter);
		}
		else if (!(transmitter->isRepeatedStartEnabled))
		{
			this->sendStopSignal(transmitter);
		}			
	}
	else if (statusRegCode == DATA_TRANSMITTED_NACK_REC)
	{
		/*if (repStartEnabled)
		{
			this->sendStartSignal(transmitter);
		}*/
		
		this->sendStopSignal(transmitter);
		
	}
	else if (statusRegCode == REPEATED_START_SENT)
	{

	}
}

void I2CDataTransmittedACKRec::sendTransmitSignal(I2CTransmitter* transmitter)
{
	static uint8_t TWDR;
	transmitter->getTxQueue().dequeue(&TWDR);

	cout << "Sending Data Byte" << endl;
	changeState(transmitter, I2CDataTransmittedACKRec::getInstance());
}

void I2CDataTransmittedACKRec::sendStartSignal(I2CTransmitter* transmitter)
{
	cout << "Sending Start Signal" << endl;
	changeState(transmitter, I2CRepeatedStartSent::getInstance());
}

void I2CDataTransmittedACKRec::sendStopSignal(I2CTransmitter* transmitter)
{
	cout << "Sending Stop Signal" << endl;
	changeState(transmitter, I2COpened::getInstance());
}
