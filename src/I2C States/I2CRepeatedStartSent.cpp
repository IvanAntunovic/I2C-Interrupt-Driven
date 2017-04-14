#include "I2CRepeatedStartSent.h"
#include "I2CDataTransmittedACKRec.h"

I2CState* I2CRepeatedStartSent::repeatedStartSentInstance = nullptr;

I2CState* I2CRepeatedStartSent::getInstance()
{
	if (repeatedStartSentInstance == 0)
	{
		repeatedStartSentInstance = new I2CRepeatedStartSent();
	}
	return repeatedStartSentInstance;
}

void I2CRepeatedStartSent::handleStatusRegSignal(I2CTransmitter* transmitter, uint8_t statusRegCode)
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

void I2CRepeatedStartSent::sendTransmitSignal(I2CTransmitter* transmitter)
{
	uint8_t TWDR = transmitter->getAddress();
	printf("Sending ADDRESS + W: %d\n", TWDR);
	changeState(transmitter, I2CDataTransmittedACKRec::getInstance());
}

void I2CRepeatedStartSent::sendStartSignal(I2CTransmitter* transmitter)
{
	cout << "Sending Start Signal" << endl;
	changeState(transmitter, I2CRepeatedStartSent::getInstance());
}

//void I2CRepeatedStartSent::sendStopSignal(I2CTransmitter* transmitter)
//{
//	cout << "Sending Stop Signal" << endl;
//	changeState(transmitter, I2COpened::getInstance());
//}