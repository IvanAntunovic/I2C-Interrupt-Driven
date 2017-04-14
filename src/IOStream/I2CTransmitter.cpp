#include "I2CTransmitter.h"
#include "I2COpened.h"
#include "I2CRepeatedStartSent.h"
#include "I2CClosed.h"

//
//#ifndef extern "C" { void __cxa_pure_virtual() { while (1); }}
//#endif

I2CTransmitter::I2CTransmitter()
{
	this->state = I2CClosed::getInstance();
}

void I2CTransmitter::setMode(uint8_t _address, int _clockFrequency, bool _isRepeatedStartEnabled)
{
	address = _address;
	clockFrequency = _clockFrequency;
	isRepeatedStartEnabled = _isRepeatedStartEnabled;
}

void I2CTransmitter::setMode(bool _isRepeatedStartEnabled)
{
	isRepeatedStartEnabled = _isRepeatedStartEnabled;
}

void I2CTransmitter::setTransmitterState(I2CState* state)
{
	this->state = state;
}

void I2CTransmitter::changeState(I2CState* state)
{
	this->state = state;
}

uint8_t I2CTransmitter::getAddress()
{
	return address;
}

CircularQueue& I2CTransmitter::getTxQueue()
{
	return txQueue;
}

unsigned int I2CTransmitter::write(unsigned char* bytes, unsigned char offset, unsigned char length)
{
	unsigned char bytesWrittenCnt = 0;

	for (int i = offset; i < length; i++)
	{
		if (txQueue.enqueue(bytes[i]))
		{
			bytesWrittenCnt++;
		}
	}

	static char status = 0;
	while (status != 1)
	{
		this->state->handleStatusRegSignal(this, status);
		if (this->state == I2COpened::getInstance() || this->state == I2CRepeatedStartSent::getInstance())
		{
			break;
		}
	}
	
	return bytesWrittenCnt;
}

unsigned char I2CTransmitter::availableForWrite()
{
	return BUFFER_SIZE - txQueue.getAvailableItems();
}
