#include "I2CStartTransmitted.h"
#include "I2CAdrWTransmittedACKRec.h"
#include <stdio.h>

I2CState* I2CStartTransmitted::i2cStartTransmittedInstance = 0;

I2CState* I2CStartTransmitted::getInstance()
{
	if (i2cStartTransmittedInstance == 0)
	{
		i2cStartTransmittedInstance = new I2CStartTransmitted();
	}
	return i2cStartTransmittedInstance;
}

void I2CStartTransmitted::handleStatusRegSignal(I2CTransmitter* transmitter, uint8_t statusRegCode)
{
	if (statusRegCode == ADR_W_TRANSMITTED_ACK_REC)
	{
	    this->sendTransmitSignal(transmitter);
	}
	else if (statusRegCode == ADR_W_TRANSMITTED_NACK_REC)
	{
		/*this->changeState(transmitter, I2CAdrWTransmittedNACKRec::getInstance());*/
	}
	else if (statusRegCode == ADR_R_TRANSMITTED_NACK_REC)
	{
		
	}
	else if (statusRegCode == ADR_R_TRANSMITTED_NACK_REC)
	{

	}
}

void I2CStartTransmitted::sendTransmitSignal(I2CTransmitter* transmitter)
{
	// Load TWDR with SLA + W
	uint8_t TWDR = transmitter->getAddress();
	printf("Sending ADDRESS + W: %d\n", TWDR);
	this->changeState(transmitter, I2CAdrWTransmittedACKRec::getInstance());
}