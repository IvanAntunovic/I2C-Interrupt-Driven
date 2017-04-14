#include "I2COpened.h"
#include "I2CStartTransmitted.h"
#include "I2CRepeatedStartSent.h"

I2CState* I2COpened::_instance = 0;

I2CState* I2COpened::getInstance()
{
	if (_instance == 0)
	{
		_instance = new I2COpened();
	}
	return _instance;
}

void I2COpened::handleStatusRegSignal(I2CTransmitter* transmitter, uint8_t statusRegCode)
{
	if (statusRegCode == START_TRANSMITTED_SUCCESFULLY)
	{
		this->sendStartSignal(transmitter);
	}
}

void I2COpened::sendStartSignal(I2CTransmitter* transmitter)
{
	cout << "Sending Start Signal" << endl;
	changeState(transmitter, I2CStartTransmitted::getInstance());	
}