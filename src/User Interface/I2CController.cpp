#include "I2CController.h"
#include "I2COpened.h"

#define DEFAULT_ADDRESS -1

I2CController::I2CController()
{
	cout << "Opened state running!" << endl;
	i2cTransmitter.setTransmitterState(I2COpened::getInstance());
}

I2CTransmitter* I2CController::getWritter()
{
	return &i2cTransmitter;
}

I2CReceiver* I2CController::getReader()
{
	return &i2cReceiver;
}

void I2CController::setMode(uint8_t _address, int _clockFrequency, bool _isRepeatedStartEnabled)
{
	this->clockFrequency = _clockFrequency;
	this->i2cTransmitter.setMode(_address, _clockFrequency, _isRepeatedStartEnabled);
	this->i2cReceiver.setMode(_address, _clockFrequency, _isRepeatedStartEnabled);
}

void I2CController::setMode(uint8_t _address, bool _isRepeatedStartEnabled)
{
	if (_address == DEFAULT_ADDRESS)
	{
		this->i2cTransmitter.setMode(_isRepeatedStartEnabled);
		this->i2cReceiver.setMode(_isRepeatedStartEnabled);
	}
	else
	{
		this->i2cTransmitter.setMode(_address, this->clockFrequency, _isRepeatedStartEnabled);
		this->i2cReceiver.setMode(_address, this->clockFrequency, _isRepeatedStartEnabled);
	}
}


unsigned char I2CController::available()
{
	return i2cReceiver.available();
}

unsigned char I2CController::availableForWrite()
{
	return i2cTransmitter.availableForWrite();
}

bool I2CController::readByte(unsigned char* byte)
{
	if (i2cReceiver.readByte(byte))
	{
		return true;
	}
	return true;
}

unsigned int I2CController::write(unsigned char* bytes, unsigned char offset, unsigned char length)
{
	return i2cTransmitter.write(bytes, offset, length);
}


