#include "I2CStartTransmitted.h"
#include "I2CAdrWTransmittedACKRec.h"
#include "I2CAddressRTransmittedACKReceivedState.h"
#include "I2CModeMasterTransmitter.h"
#include "MasterReceiverI2CMode.h"
#include <stdio.h>

I2CState* I2CStartTransmitted::sInstance = NULL;

I2CState* I2CStartTransmitted::getInstance()
{
	if (sInstance == NULL)
	{
		sInstance = new I2CStartTransmitted();
	}
	return sInstance;
}

void I2CStartTransmitted::handleStatusRegSignal(I2CController& controller, uint8_t statusRegCode)
{
	if (controller.currentMode == MasterReceiverI2CMode::getInstance())
	{
		statusRegCode = 2;
	}

	if (statusRegCode == ADR_W_TRANSMITTED_ACK_REC)
	{
		// Load TWDR with SLA + W
		if (controller.currentMode == I2CModeMasterTransmitter::getInstance())
		{
			uint8_t TWDR;
			TWDR = controller.address << 1;
			controller.i2cTransmitter->sendTransmitSignal();
			printf("Sending ADDRESS + W: %d\n", TWDR);
			controller.changeState(I2CAdrWTransmittedACKRec::getInstance());
		}
		else
		{
			// Handle Error
		}
		
	}
	else if (statusRegCode == ADR_W_TRANSMITTED_NACK_REC)
	{
		//this->changeState(transmitter, I2CAdrWTransmittedNACKRec::getInstance());
	}
	else if (statusRegCode == ADR_R_TRANSMITTED_ACK_REC)
	{
		if (controller.currentMode == MasterReceiverI2CMode::getInstance())
		{
			uint8_t TWDR;
			TWDR = controller.address << 1 | 0x01;
			printf("Sending ADDRESS + R: %d\n", TWDR);
			controller.i2cTransmitter->sendTransmitSignal();
			controller.changeState(I2CAddressRTransmitterACKReceivedState::getInstance());
		}
	}
	else if (statusRegCode == ADR_R_TRANSMITTED_NACK_REC)
	{
		controller.i2cReceiver->sendNACKSignal();
	}
}

