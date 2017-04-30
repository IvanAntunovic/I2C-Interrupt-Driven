#include "I2CRepeatedStartSent.h"
#include "I2CDataTransmittedACKRec.h"
#include "I2COpened.h"

I2CState* I2CRepeatedStartSent::s_intance = NULL;

I2CState* I2CRepeatedStartSent::getInstance()
{
	if (s_intance == NULL)
	{
		s_intance = new I2CRepeatedStartSent();
	}
	return s_intance;
}

void I2CRepeatedStartSent::handleStatusRegSignal(I2CController& controller, uint8_t statusRegCode)
{
	if (statusRegCode == ADR_W_TRANSMITTED_ACK_REC)
	{
		uint8_t TWDR = controller.address << 1;
		controller.i2cTransmitter->sendTransmitSignal();
		printf("Sending ADDRESS + W: %d\n", TWDR);
		changeState(controller, I2CDataTransmittedACKRec::getInstance());
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



